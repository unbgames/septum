#include <random>

class Randomizer {
  public:
    std::uniform_real_distribution<> static CreateUniformGenerator(float min, float max);
    float static GenerateUniform(std::uniform_real_distribution<> distribution);

    std::normal_distribution<> static CreateNormalGenerator(float min, float max);
    float static GenerateNormal(std::normal_distribution<> distribution);

  private:
    static std::random_device device;
    static std::mt19937 gen;
};
