#include <gtest/gtest.h>
#include <cstdint>
#include <random>
#include "params/params.hpp"
#include "operator/Montgomery.hpp" 
#include "structure/galoisfield.hpp"
#include "structure/torus.hpp"
#include "utility/log.hpp"

class MontgomeryTest : public ::testing::Test {
  protected:
    void SetUp() override {
        if (Params::q == 0) {
            throw std::runtime_error("Params::P is not set");
        }
        std::cout << "param = {\n";
        std::cout << "  q = " << Params::q << ",\n";
        std::cout << "  R = " << MontgomeryParams::R << ",\n";
        std::cout << "  μ = " << MontgomeryParams::mu << ",\n";
        std::cout << "  R^2 = " << MontgomeryParams::R2 << ",\n";
        std::cout << "}" << std::endl;
    }
  private:
    int seed;

  public:
    MontgomeryTest() {
        if (std::getenv("TEST_SEED") != nullptr) {
            seed = std::stoi(std::getenv("TEST_SEED"));
        }
        return;
    }
    int getseed() const { return seed; }
};

// テストケース
TEST_F(MontgomeryTest, MultiplyTest1) {
  std::mt19937 gen(MontgomeryTest::getseed());
  std::uniform_int_distribution<uint32_t> dis(0, Params::q-1);
  DiscreteTorus a(dis(gen));

  Log::debug("a =", a.val());
  Log::debug("k =", 1);

  DiscreteTorus c = 1 * a;

  uint32_t result = c.val();
  uint32_t expected = a.val();

  EXPECT_EQ(result, expected);
}

TEST_F(MontgomeryTest, MultiplyTest2) {
  std::mt19937 gen(MontgomeryTest::getseed());
  std::uniform_int_distribution<uint32_t> dis(0, Params::q-1);
  DiscreteTorus a(dis(gen));

  std::uniform_int_distribution<uint32_t> disN(0, std::numeric_limits<uint32_t>::max());
  uint32_t k = disN(gen);

  Log::debug("a =", a.val());
  Log::debug("k =", k);

  DiscreteTorus c =  k * a;

  uint32_t result = c.val();
  uint32_t expected = ((uint64_t)(k) * a.val()) % Params::q;

  EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]).find("--P=") == 0) {
            std::string value = std::string(argv[i]).substr(4);
            Params::q = std::stoul(value);
        }
        else if (std::string(argv[i]).find("--r=") == 0) {
            std::string value = std::string(argv[i]).substr(4);
            MontgomeryParams::R = 1 << std::stoul(value);
        }
        else if (std::string(argv[i]).find("--seed=") == 0) {
            std::string seed = std::string(argv[i]).substr(7);
            setenv("TEST_SEED", seed.c_str(), 1);
        }
    }

    MontgomeryParams::mu = constMontgomeryMu();
    MontgomeryParams::R2 = constMontgomeryR2();

    return RUN_ALL_TESTS();
}
