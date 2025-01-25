#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "structure/intpoly.hpp"
#include "structure/toruspoly.hpp"

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // ソケットの作成
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // サーバーアドレスの設定
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // サーバーに接続
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }
    else {
      Log::info("Connected to server");
    }

    // 多項式の作成
    std::vector<uint32_t> coeffs1 = {1, 2, 3, 4};
    std::vector<uint32_t> coeffs2 = {5, 6, 7, 8};

    // データのシリアライズ
    size_t size1 = coeffs1.size();
    size_t size2 = coeffs2.size();
    char dataBuffer[1024] = {0};
    memcpy(dataBuffer, &size1, sizeof(size_t));
    memcpy(dataBuffer + sizeof(size_t), &size2, sizeof(size_t));
    memcpy(dataBuffer + 2 * sizeof(size_t), coeffs1.data(), size1 * sizeof(uint32_t));
    memcpy(dataBuffer + 2 * sizeof(size_t) + size1 * sizeof(uint32_t), coeffs2.data(), size2 * sizeof(uint32_t));

    // サーバーにデータを送信
    send(sock, dataBuffer, sizeof(size_t) * 2 + size1 * sizeof(uint32_t) + size2 * sizeof(uint32_t), 0);

    // サーバーから結果を受信
    read(sock, buffer, 1024);

    // 結果のデシリアライズ
    size_t resultSize;
    memcpy(&resultSize, buffer, sizeof(size_t));
    std::vector<uint32_t> resultCoeffs(resultSize);
    memcpy(resultCoeffs.data(), buffer + sizeof(size_t), resultSize * sizeof(uint32_t));

    // 結果の表示
    std::cout << "Result: ";
    for (const auto& coeff : resultCoeffs) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;

    close(sock);
    return 0;
}