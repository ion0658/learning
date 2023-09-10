#include "gtest/gtest.h"
#include "option.hpp"

TEST(test_option, is_some)
{
    using namespace IonOH::Option;
    auto o = Option<std::string>::Some("some");
    EXPECT_TRUE(o.is_some());
    EXPECT_FALSE(o.is_none());
}

TEST(test_option, is_none)
{
    using namespace IonOH::Option;
    auto o = Option<std::string>::None();
    EXPECT_FALSE(o.is_some());
    EXPECT_TRUE(o.is_none());
}

TEST(test_option, get_some)
{
    using namespace IonOH::Option;
    auto o = Option<std::string>::Some("some");
    EXPECT_EQ(o.get(), "some");
    auto o2 = Option<std::string>::None();
    EXPECT_THROW(o2.get(), std::runtime_error);
}
