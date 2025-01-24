#include <iostream>
#include <vector>
#include <cstring>
#include <boost/program_options.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "params/params.hpp"
#include "params/nttparams.hpp"
#include "structure/intpoly.hpp"
#include "structure/toruspoly.hpp"
#include "structure/galoisfieldpoly.hpp"
#include "strategy/ntt_multiplication_strategy.hpp"
#include "operator/ntt.hpp"
#include "utility/log.hpp"

#define PORT 8080

int server_fd = -1;

void handleClient(int clientSocket) {
    Log::info("Client connected");
    // 受信バッファ
    char buffer[1024] = {0};
    ssize_t bytesRead = read(clientSocket, buffer, 1024);

     if (bytesRead <= 0) {
        std::cerr << "Failed to read data from client or client disconnected" << std::endl;
        close(clientSocket);
        return;
    }

    std::vector<uint32_t> coeffs1;
    std::vector<DiscreteTorus> coeffs2;
    size_t size1, size2;
    memcpy(&size1, buffer, sizeof(size_t));
    memcpy(&size2, buffer + sizeof(size_t), sizeof(size_t));
    coeffs1.resize(size1);
    coeffs2.resize(size2);
    memcpy(coeffs1.data(), buffer + 2 * sizeof(size_t), size1 * sizeof(uint32_t));
    memcpy(coeffs2.data(), buffer + 2 * sizeof(size_t) + size1 * sizeof(uint32_t), size2 * sizeof(uint32_t));

    IntPoly intpoly1(coeffs1);
    DiscreteTorusPoly toruspoly2(coeffs2);

    GaloisFieldPoly gfpoly1 = std::move(intpoly1);
    GaloisFieldPoly gfpoly2 = std::move(toruspoly2);
    GaloisFieldPoly gfpoly3 = std::move(gfpoly1 * gfpoly2);
    Log::debug(gfpoly3);

    std::vector<GaloisFieldElement> resultCoeffs = gfpoly3.get_coeffs();
    size_t resultSize = resultCoeffs.size();
    char resultBuffer[1024] = {0};
    memcpy(resultBuffer, &resultSize, sizeof(size_t));
    memcpy(resultBuffer + sizeof(size_t), resultCoeffs.data(), resultSize * sizeof(uint32_t));

    send(clientSocket, resultBuffer, sizeof(size_t) + resultSize * sizeof(uint32_t), 0);

    close(clientSocket);
}

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received. Shutting down server." << std::endl;
    if (server_fd != -1) { 
        close(server_fd);
    }
    exit(signum);
}

int main(int argc, char* argv[]) {
  boost::program_options::options_description desc("Options");
  desc.add_options()
    ("help,h", "Help\n")
    ("param,P", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] TFHE Parameter.\nSpecify integer P and n, N, where P is a prime number and n is the length of secret key, N is degree of Polynomial.\ne.g. -P 12289 4 1024\n")
    ("mont,M", boost::program_options::value<std::vector<uint32_t>>()->multitoken(), "[REQUIRED] Montgomery Multiplication scaling factor R.\nSpecify integer r, so that R = 2^r > P.\ne.g. -M 18\n");
                                                                                                
  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  } catch (boost::program_options::error &e) {
    throw std::invalid_argument(e.what());
    return 1;
  }
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.count("param")) {
    std::vector<uint32_t> P = vm["param"].as<std::vector<uint32_t>>();
    Params::P = P[0];
    Params::n = P[1];
    Params::N = P[2];
  }
  else {
    return 1;
  }

  if (vm.count("mont")) {
    std::vector<uint32_t> M = vm["mont"].as<std::vector<uint32_t>>();
    MontgomeryParams::R = 1 << M[0];
    // P ans R should be coprime
    MontgomeryParams::mu = constMontgomeryMu();
    MontgomeryParams::R2 = constMontgomeryR2();
  }
  else {
    return 1;
  }

  Log::debug("param = {\n",
              "P =", Params::P, "\n", 
              "n =", Params::n, "\n", 
              "N =", Params::N, "\n}");

  Log::debug("Montgomery param = {\n",
              "R =", MontgomeryParams::R, "\n", 
              "μ =", MontgomeryParams::mu, "\n", 
              "R^2 =", MontgomeryParams::R2, "\n}");

  if (((uint64_t)MontgomeryParams::mu*Params::P)%MontgomeryParams::R != MontgomeryParams::R-1) {
    Log::error("Montgomery constant mismatched");
    return 1;
  }

#ifdef NTT
  Log::info("Polynomial Multiplication Method: [NTT]");
  if (!SetUpNttConstants::setup()) {
    Log::error("Failed to set up NTT constants");
  }
 #else
    Log::info("Polynomial Multiplication Method: [Naive]");
    Log::warn("Naive polynomial multiplication has been selected. This method is less efficient and may result in slower performance compared to NTT.");
#endif

    int server_fd, clientSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // ソケットの作成
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // ソケットオプションの設定
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // バインド
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // リッスン
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
       fd_set readfds;
        struct timeval timeout;

        // ファイルディスクリプタセットの初期化
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);

        // タイムアウトの設定（10秒）
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        int activity = select(server_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        } else if (activity == 0) {
            std::cout << "Timeout: No client connection within 10 seconds. Shutting down server." << std::endl;
            close(server_fd);
            exit(0);
        }

        // クライアント接続の受け入れ
        if ((clientSocket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // クライアントの処理
        handleClient(clientSocket);

        std::cout << "Client disconnected. Shutting down server." << std::endl;
        close(server_fd);
        exit(0);
    }

    return 0;
}