#include "Randomizer.h"
#include <random>

std::random_device Randomizer::device;
std::mt19937 Randomizer::gen(Randomizer::device());

std::uniform_real_distribution<> Randomizer::CreateUniformGenerator(float min, float max) {
  std::uniform_real_distribution<> dist(min, max);
  return dist;
}

float Randomizer::GenerateUniform(std::uniform_real_distribution<> distribution) {
  return distribution(gen);
}

std::normal_distribution<> Randomizer::CreateNormalGenerator(float min, float max) {
  std::normal_distribution<> dist(min, max);
  return dist;
}

float Randomizer::GenerateNormal(std::normal_distribution<> distribution) {
  return distribution(gen);
}
