module;

#include <gsl/gsl>

#include <span>
#include <cstddef>
#include <algorithm>

export module toys.algorithm;

using namespace std;

namespace toys {

export
template<typename T, size_t N>
[[nodiscard]]
constexpr auto slide(span<T, N> view, size_t offset, size_t width)
{
    return view.subspan(offset, offset + width <= view.size() ? width : 0U);
}

export
template<typename T, size_t N, size_t M>
constexpr bool starts_with(span<T, N> view, span<T, M> prefix)
{
    return view.size() >= prefix.size()
        && equal(prefix.begin(), prefix.end(), view.begin());
}

export
template<typename T, size_t N, size_t M>
constexpr bool ends_with(span<T, N> view, span<T, M> suffix)
{
    return view.size() >= suffix.size()
        && equal(view.end() - suffix.size(), view.end(),
                      suffix.end() - suffix.size());
}

export
template<typename T, size_t N, size_t M>
constexpr bool contains(span<T, N> view, span<T, M> sub)
{
    return ranges::search(view, sub).begin() != view.end();
}

} // namespace toys
