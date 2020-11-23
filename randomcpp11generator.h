#ifndef RANDOMCPP11GENERATOR_H
#define RANDOMCPP11GENERATOR_H

#include <random>

namespace details
{
    /// True if type T is applicable by a std::uniform_int_distribution
    template<class T>
    struct is_uniform_int {
        static constexpr bool value =
                std::is_same<T,              short>::value ||
                std::is_same<T,                int>::value ||
                std::is_same<T,               long>::value ||
                std::is_same<T,          long long>::value ||
                std::is_same<T,     unsigned short>::value ||
                std::is_same<T,       unsigned int>::value ||
                std::is_same<T,      unsigned long>::value ||
                std::is_same<T, unsigned long long>::value;
    };

    /// True if type T is applicable by a std::uniform_real_distribution
    template<class T>
    struct is_uniform_real {
        static constexpr bool value =
                std::is_same<T,       float>::value ||
                std::is_same<T,      double>::value ||
                std::is_same<T, long double>::value;
    };
}

class RandomCpp11Generator
{
    template <class T> using IntDist = std::uniform_int_distribution<T>;
    template <class T> using RealDist = std::uniform_real_distribution<T>;

public:
 // RandomCpp11Generator();
    template <class T>
    static typename std::enable_if<details::is_uniform_int<T>::value, T>::type get(T from = std::numeric_limits<T>::min(), T to = std::numeric_limits<T>::max())
    {
        if (from > to) std::swap(from, to);
        IntDist<T> dist{from, to};
        return dist(instance().engine());
    }

    template <class T>
    static typename std::enable_if<details::is_uniform_real<T>::value, T>::type get(T from = std::numeric_limits<T>::min(), T to = std::numeric_limits<T>::max())
    {
        if (from > to) std::swap(from, to);
        RealDist<T> dist{from, to};
        return dist(instance().engine());
    }

    std::mt19937& engine() { return m_mt; }

protected:
    static RandomCpp11Generator& instance()
    {
        static RandomCpp11Generator inst;
        return inst;
    }

private:
    std::random_device m_rd; // Устройство генерации случайных чисел
    std::mt19937 m_mt;       // Стандартный генератор случайных чисел

    RandomCpp11Generator() : m_mt(m_rd()) {}
    ~RandomCpp11Generator() {}
    RandomCpp11Generator(const RandomCpp11Generator&) = delete;
    RandomCpp11Generator& operator = (const RandomCpp11Generator&) = delete;
};

#endif // RANDOMCPP11GENERATOR_H