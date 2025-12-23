#pragma once

#include "range.hpp"
#include "convert.hpp"

#include <utility>

namespace saucer::bindings
{
    template <std::ranges::sized_range T, typename V>
    void return_range(T &&values, V *result, std::size_t *size)
    {
        using value_type = std::remove_cvref_t<T>::value_type;

        using converter   = bindings::converter<value_type>;
        using converted_t = decltype(converter::convert(std::declval<value_type>()));

        static_assert(not detail::tuple<converted_t>);

        if (!result && !size)
        {
            return;
        }

        if (!result)
        {
            *size = values.size();
            return;
        }

        auto count = *size;

        for (auto it = values.begin(); it != values.end() && count > 0; ++it, count--)
        {
            result[*size - count] = converter::convert(std::forward_like<T>(*it));
        }
    }

    template <std::ranges::sized_range T, typename V>
    void return_range(std::optional<T> value, V *result, std::size_t *size)
    {
        if (!result && !size)
        {
            return;
        }

        if (!value.has_value())
        {
            *size = 0;
            return;
        }

        return return_range(std::move(*value), result, size);
    }
} // namespace saucer::bindings
