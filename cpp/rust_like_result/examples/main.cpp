#include <iostream>
#include <vector>
#include "result.hpp"
#include "option.hpp"

using namespace IonOH::Result;
using namespace IonOH::Option;

Result<int, const char *> divide(int a, int b)
{
    if (b == 0)
    {
        return Result<int, const char *>::Err("failed to divide by zero");
    }
    else
    {
        return Result<int, const char *>::Ok(a / b);
    }
}

Option<int> divide_option(int a, int b)
{
    if (b == 0)
    {
        return Option<int>::None();
    }
    else
    {
        return Option<int>::Some(a / b);
    }
}

int main()
{

    auto result_success = divide(10, 2);
    if (result_success.is_ok())
    {
        std::cout << "result_success is success: " << result_success.get_ok() << std::endl;
    }
    else
    {
        std::cout << "result_success is error: " << result_success.get_err() << std::endl;
    }

    auto result_error = divide(10, 0);
    if (result_error.is_ok())
    {
        std::cout << "result_error is success: " << result_error.get_ok() << std::endl;
    }
    else
    {
        std::cout << "result_error is error: " << result_error.get_err() << std::endl;
    }

    auto option_success = divide_option(10, 2);
    if (option_success.is_some())
    {
        std::cout << "option_success is some: " << option_success.get() << std::endl;
    }
    else
    {
        std::cout << "option_success is none" << std::endl;
    }

    auto option_error = divide_option(10, 0);
    if (option_error.is_some())
    {
        std::cout << "option_error is some: " << option_error.get() << std::endl;
    }
    else
    {
        std::cout << "option_error is none" << std::endl;
    }

    return 0;
}
