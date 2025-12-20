#pragma once

#include "utils.hpp"

#include <saucer/utils/overload.hpp>

#include <memory>
#include <utility>
#include <type_traits>

namespace saucer::cutils
{
    template <typename T, typename U>
    U *opaque<T, U>::ptr()
    {
        return std::visit(
            overload{
                [](U &value) { return std::addressof(value); },
                [](U *value) { return value; },
            },
            value);
    }

    template <typename T, typename U>
    U &opaque<T, U>::operator*() noexcept
    {
        return *ptr();
    }

    template <typename T, typename U>
    U *opaque<T, U>::operator->() noexcept
    {
        return ptr();
    }

    template <typename T, typename U>
    T *opaque<T, U>::view(U &value)
    {
        return new T{std::addressof(value)};
    }

    template <typename T, typename U>
    T *opaque<T, U>::from(U &&value)
    {
        return new T{std::move(value)};
    }

    template <typename T, typename U>
    template <typename... Ts>
    T *opaque<T, U>::make(Ts &&...args)
    {
        return new T{U{std::forward<Ts>(args)...}};
    }

    template <typename T>
    struct converter
    {
        template <typename U>
        static decltype(auto) convert(U &&value)
        {
            return std::forward<U>(value);
        };
    };

    template <std::ranges::sized_range T, typename V>
    void return_range(T &&values, V *result, std::size_t *size)
    {
        using value_type = std::remove_cvref_t<T>::value_type;
        using converter  = cutils::converter<value_type>;

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

    template <auto From, typename To>
    struct map
    {
        static constexpr auto from = From;
        using to                   = To;
    };

    template <typename... Ts>
    struct event_mapper<Ts...>::impl
    {
        using tuple = std::tuple<Ts...>;

        template <std::size_t I, typename Return, typename F, typename R, typename T, typename U>
            requires(I < sizeof...(Ts))
        static auto visit(F &&visitor, R &&registrar, T &instance, const U &value)
        {
            using element              = std::tuple_element_t<I, tuple>;
            static constexpr auto from = static_cast<T::event>(element::from);

            if (std::to_underlying(value) != std::to_underlying(from))
            {
                return visit<I + 1, Return>(std::forward<F>(visitor), std::forward<R>(registrar), instance, value);
            }

            auto fn = [visitor = std::forward<F>(visitor)]<typename... Us>(Us &&...args) mutable
            {
                using result             = T::events::template event<from>::result;
                static constexpr auto id = std::type_identity<typename element::to>{};

                if constexpr (std::is_void_v<result>)
                {
                    visitor(id, converter<std::remove_cvref_t<Us>>::convert(std::forward<Us>(args))...);
                }
                else
                {
                    return converter<result>::convert(
                        visitor(id, converter<std::remove_cvref_t<Us>>::convert(std::forward<Us>(args))...));
                }
            };

            return registrar(std::integral_constant<decltype(from), from>{}, std::move(fn));
        }

        template <std::size_t I, typename Return>
            requires(I >= sizeof...(Ts))
        static Return visit(auto &&...)
        {
            std::abort();
            std::unreachable();
        }
    };

    template <typename... Ts>
    template <typename F, typename T, typename U>
    auto event_mapper<Ts...>::on(F &&visitor, T &instance, const U &value, bool clearable)
    {
        auto registrar = [clearable, &instance]<typename C, typename D>(C, D &&fn)
        {
            return instance.template on<C::value>({{.func = std::forward<D>(fn), .clearable = clearable}});
        };

        return impl::template visit<0, std::size_t>(std::forward<F>(visitor), registrar, instance, value);
    }

    template <typename... Ts>
    template <typename F, typename T, typename U>
    auto event_mapper<Ts...>::once(F &&visitor, T &instance, const U &value)
    {
        auto registrar = [&instance]<typename C, typename D>(C, D &&fn)
        {
            return instance.template once<C::value>(std::forward<D>(fn));
        };

        return impl::template visit<0, void>(std::forward<F>(visitor), registrar, instance, value);
    }
} // namespace saucer::cutils
