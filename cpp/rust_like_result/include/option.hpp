#pragma once
#ifndef _OPTION_H_INCLUDED
#define _OPTION_H_INCLUDED

#include <cassert>

namespace IonOH
{
    namespace Option
    {
        template <typename T>
        struct Option
        {

            Option(Option const &&r) : type(r.type)
            {
                switch (type)
                {
                case OptionType::SOME:
                    new (&some_) T(std::move(r.some_));
                    break;
                case OptionType::NONE:
                    break;
                }
            }

            ~Option() noexcept
            {
                switch (type)
                {
                case OptionType::SOME:
                    some_.~T();
                    break;
                case OptionType::NONE:
                    break;
                }
            }

            T &get()
            {
                if (type != OptionType::SOME)
                    throw std::runtime_error("Option is not some");
                return some_;
            }

            const T &get() const
            {
                if (type != OptionType::SOME)
                    throw std::runtime_error("Option is not some");
                return some_;
            }

            static Option<T> Some(const T &value) noexcept
            {
                auto option = Option<T>(OptionType::SOME);
                new (&option.some_) T(value);
                return option;
            }
            static Option<T> Ok(const T &&value) noexcept
            {
                auto option = Option<T>(OptionType::SOME);
                new (&option.some_) T(std::move(value));
                return option;
            }

            static Option<T> None() noexcept
            {
                auto option = Option<T>(OptionType::NONE);
                return option;
            }

            bool is_some() const noexcept
            {
                return type == OptionType::SOME;
            }

            bool is_none() const noexcept
            {
                return type == OptionType::NONE;
            }

        private:
            enum class OptionType
            {
                SOME,
                NONE,
            };
            Option(OptionType type) : type(type) {}

            Option(Option const &r) = delete;
            Option &operator=(Option const &r) = delete;

            OptionType type;
            union
            {
                struct
                {
                    T some_;
                };
                struct
                {
                } type_of_none_;
            };
        };
    } // namespace Option
} // namespace IonOH

#endif // !_OPTION_H_INCLUDED