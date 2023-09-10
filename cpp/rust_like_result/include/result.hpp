#pragma once
#ifndef _RESULT_H_INCLUDED
#define _RESULT_H_INCLUDED

#include <cassert>

namespace IonOH
{
    namespace Result
    {
        template <typename T, typename E>
        struct Result
        {

            Result(Result const &&r) : type(r.type)
            {
                switch (type)
                {
                case ResultType::OK:
                    new (&ok_) T(std::move(r.ok_));
                    break;
                case ResultType::ERR:
                    new (&err_) E(std::move(r.err_));
                    break;
                }
            }

            ~Result() noexcept
            {
                switch (type)
                {
                case ResultType::OK:
                    ok_.~T();
                    break;
                case ResultType::ERR:
                    err_.~E();
                    break;
                }
            }

            T &get_ok()
            {
                if (type != ResultType::OK)
                    throw std::runtime_error("Result is not ok");
                return ok_;
            }

            E &get_err()
            {
                if (type != ResultType::ERR)
                    throw std::runtime_error("Result is not error");
                return err_;
            }

            const T &get_ok() const
            {
                if (type != ResultType::OK)
                    throw std::runtime_error("Result is not ok");
                return ok_;
            }

            const E &get_err() const
            {
                if (type != ResultType::ERR)
                    throw std::runtime_error("Result is not error");
                return err_;
            }

            static Result<T, E> Ok(const T &value) noexcept
            {
                auto result = Result<T, E>(ResultType::OK);
                new (&result.ok_) T(value);
                return result;
            }
            static Result<T, E> Ok(const T &&value) noexcept
            {
                auto result = Result<T, E>(ResultType::OK);
                new (&result.ok_) T(std::move(value));
                return result;
            }

            static Result<T, E> Err(const E &value) noexcept
            {
                auto result = Result<T, E>(ResultType::ERR);
                new (&result.err_) E(value);
                return result;
            }
            static Result<T, E> Err(const E &&value) noexcept
            {
                auto result = Result<T, E>(ResultType::ERR);
                new (&result.err_) E(std::move(value));
                return result;
            }

            bool is_ok() const noexcept
            {
                return type == ResultType::OK;
            }

            bool is_err() const noexcept
            {
                return type == ResultType::ERR;
            }

        private:
            enum class ResultType
            {
                OK,
                ERR,
            };
            Result(ResultType type) : type(type) {}

            Result(Result const &r) = delete;
            Result &operator=(Result const &r) = delete;

            ResultType type;
            union
            {
                struct
                {
                    T ok_;
                };
                struct
                {
                    E err_;
                };
            };
        };
    } // namespace Result
} // namespace IonOH

#endif // !_RESULT_H_INCLUDED