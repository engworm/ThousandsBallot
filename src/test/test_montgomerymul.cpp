#include <gtest/gtest.h>
#include <cstdint>
#include <random>
#include "params/params.hpp"
#include "include/operator/Montgomery.hpp" 
#include "include/structure/torus.hpp"

class MontgomeryTest : public ::testing::Test {
protected:
    void SetUp() override {
        if (Params::P == 0) {
            throw std::runtime_error("Params::P is not set");
        }
        std::cout << "param = {\n";
        std::cout << "  P = " << Params::P << ",\n";
        std::cout << "  R = " << MontgomeryParams::R << ",\n";
        std::cout << "  μ = " << MontgomeryParams::mu << ",\n";
        std::cout << "  R^2 = " << MontgomeryParams::R2 << ",\n";
        std::cout << "}" << std::endl;
    }
};

// テストケース
TEST_F(MontgomeryTest, MultiplyTest1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, Params::P-1);
  DiscreteTorus a(dis(gen));

  DiscreteTorus c = 1 * a;

  uint32_t result = c.val();
  uint32_t expected = a.val();

  EXPECT_EQ(result, expected);
}

TEST_F(MontgomeryTest, MultiplyTest2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, Params::P-1);
  DiscreteTorus a(dis(gen));

  std::uniform_int_distribution<uint32_t> disN(0, std::numeric_limits<uint32_t>::max());
  uint32_t k = disN(gen);

  DiscreteTorus c =  k * a;

  uint32_t result = c.val();
  uint32_t expected = ((uint64_t)(k) * a.val()) % Params::P;

  EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]).find("--P=") == 0) {
            std::string p_value = std::string(argv[i]).substr(4);
            Params::P = std::stoul(p_value);
        }
        else if (std::string(argv[i]).find("--r=") == 0) {
            std::string p_value = std::string(argv[i]).substr(4);
            MontgomeryParams::R = 1 << std::stoul(p_value);
        }
    }

    MontgomeryParams::mu = constMontgomeryMu();
    MontgomeryParams::R2 = constMontgomeryR2();

    return RUN_ALL_TESTS();
}
