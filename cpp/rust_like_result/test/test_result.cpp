#include "gtest/gtest.h"
#include "result.hpp"

TEST(test_result, is_ok)
{
    using namespace IonOH::Result;
    auto r = Result<std::string, std::string>::Ok("ok");
    EXPECT_TRUE(r.is_ok());
    EXPECT_FALSE(r.is_err());
}

TEST(test_result, is_err)
{
    using namespace IonOH::Result;
    auto r = Result<std::string, std::string>::Err("error");
    EXPECT_FALSE(r.is_ok());
    EXPECT_TRUE(r.is_err());
}

TEST(test_result, get_ok)
{
    using namespace IonOH::Result;
    auto r = Result<std::string, std::string>::Ok("ok");
    EXPECT_EQ(r.get_ok(), "ok");
    EXPECT_THROW(r.get_err(), std::runtime_error);
}

TEST(test_result, get_err)
{
    using namespace IonOH::Result;
    auto r = Result<std::string, std::string>::Err("error");
    EXPECT_THROW(r.get_ok(), std::runtime_error);
    EXPECT_EQ(r.get_err(), "error");
}