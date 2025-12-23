#pragma once

#include "map.hpp"
#include "convert.hpp"

#include <cstdlib>
#include <utility>

namespace saucer::bindings
{
    namespace detail
    {
        template <typename T, tuple U>
        constexpr auto concat(T &&, U &&);

        template <typename T, typename U>
        constexpr auto concat(T &&, U &&);

        template <typename T>
        constexpr auto arguments_impl(T &&);

        template <typename T, typename U, typename... Us>
        constexpr auto arguments_impl(T &&, U &&, Us &&...);

        template <typename... Us>
        constexpr auto arguments(Us &&...);
    } // namespace detail

    template <typename T, detail::tuple U>
    constexpr auto detail::concat(T &&current, U &&other)
    {
        return std::tuple_cat(std::forward<T>(current), std::forward<U>(other));
    }

    template <typename T, typename U>
    constexpr auto detail::concat(T &&current, U &&other)
    {
        return std::tuple_cat(std::forward<T>(current), std::make_tuple(std::forward<U>(other)));
    }

    template <typename T>
    constexpr auto detail::arguments_impl(T &&current)
    {
        return std::forward<T>(current);
    }

    template <typename T, typename U, typename... Us>
    constexpr auto detail::arguments_impl(T &&current, U &&value, Us &&...args)
    {
        return arguments_impl(concat(std::forward<T>(current), std::forward<U>(value)), std::forward<Us>(args)...);
    }

    template <typename... Us>
    constexpr auto detail::arguments(Us &&...args)
    {
        return arguments_impl(std::tuple<>{}, std::forward<Us>(args)...);
    }

    template <auto From, auto To>
    struct map
    {
        static constexpr auto from = From;
        static constexpr auto to   = To;
    };

    template <typename... Ts>
    struct map_events<Ts...>::impl
    {
        using tuple = std::tuple<Ts...>;

        template <typename Return, std::size_t I = 0, typename F, typename R, typename T, typename U>
            requires(I < sizeof...(Ts))
        static auto visit(F &&visitor, R &&registrar, T &instance, const U &value)
        {
            using element              = std::tuple_element_t<I, tuple>;
            static constexpr auto from = static_cast<T::event>(element::from);

            if (std::to_underlying(value) != std::to_underlying(from))
            {
                return visit<Return, I + 1>(std::forward<F>(visitor), std::forward<R>(registrar), instance, value);
            }

            auto fn = [visitor = std::forward<F>(visitor)]<typename... Us>(Us &&...args) mutable
            {
                using result = T::events::template event<from>::result;

                auto arguments = detail::arguments(
                    element::to, converter<std::remove_cvref_t<Us>>::convert(std::forward<Us>(args))...);

                if constexpr (std::is_void_v<result>)
                {
                    std::apply(visitor, std::move(arguments));
                }
                else
                {
                    return converter<result>::convert(std::apply(visitor, std::move(arguments)));
                }
            };

            return registrar(std::integral_constant<decltype(from), from>{}, std::move(fn));
        }

        template <typename Return, std::size_t I>
            requires(I >= sizeof...(Ts))
        static Return visit(auto &&...)
        {
            std::abort();
            std::unreachable();
        }
    };

    template <typename... Ts>
    template <typename F, typename T, typename U>
    auto map_events<Ts...>::on(F &&visitor, T &instance, const U &value, bool clearable)
    {
        auto registrar = [clearable, &instance]<typename C, typename D>(C, D &&fn)
        {
            return instance.template on<C::value>({{.func = std::forward<D>(fn), .clearable = clearable}});
        };

        return impl::template visit<std::size_t>(std::forward<F>(visitor), registrar, instance, value);
    }

    template <typename... Ts>
    template <typename F, typename T, typename U>
    auto map_events<Ts...>::once(F &&visitor, T &instance, const U &value)
    {
        auto registrar = [&instance]<typename C, typename D>(C, D &&fn)
        {
            return instance.template once<C::value>(std::forward<D>(fn));
        };

        return impl::template visit<void>(std::forward<F>(visitor), registrar, instance, value);
    }

} // namespace saucer::bindings
