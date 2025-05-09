module;

#include <random>
#include <concepts>

export module toys.random;

using namespace std;

namespace toys {

export
template<integral T = int>
T random(const T min, const T max) noexcept
{
    static random_device engine{};
    static mt19937 generator{ engine() };
    uniform_int_distribution<T> distribution{ min, max };
    return distribution(generator);
}

export
template<floating_point T = double>
T random(const T min, const T max) noexcept
{
    static random_device engine{};
    static mt19937 generator{ engine() };
    uniform_real_distribution<T> distribution{ min, max };
    return distribution(generator);
}

} // namespace toys
