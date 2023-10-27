#ifndef __generator_hpp__
#define __generator_hpp__

#include <random>

namespace gen {
  template <typename T>
  class Random_Generator {
  public:
    Random_Generator();
    Random_Generator(T _min, T _max, size_t seed = std::mt19937::default_seed);

    T generate();
    T generate(T _min, T _max);

  private:
    std::mt19937 gen;
    std::uniform_int_distribution<T> distance;
  };

  template <typename T>
  inline gen::Random_Generator<T>::Random_Generator()
    : distance((T)0, (T)0), gen(std::mt19937::default_seed) {}

  template <typename T>
  inline Random_Generator<T>::Random_Generator(T _min, T _max, size_t seed)
    : distance(_min, _max), gen(seed) {}

  template <typename T>
  inline T Random_Generator<T>::generate() {
    return distance(gen);
  }

  template <typename T>
  inline T Random_Generator<T>::generate(T _min, T _max) {
    distance = std::uniform_int_distribution<T>(_min, _max);
    return distance(gen);
  }

}  // namespace gen

#endif  // !__generator_hpp__
