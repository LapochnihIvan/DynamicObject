#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <DynamicObject.hpp>


GTEST_TEST(CastsTests, castLvalue)
{
    DynamicObject obj(0);

    ASSERT_NO_THROW([[maybe_unused]] int dest(std::move(obj)));
}

GTEST_TEST(CastsTests, castLvalueErrorT)
{
    DynamicObject obj(0);

    float dest;
    ASSERT_THROW(dest = std::move(obj), std::bad_any_cast);

    (void)dest;
}

GTEST_TEST(CastsTests, castRvalue)
{
    using namespace std::string_literals;

    DynamicObject obj("Some str"s);

    const std::string& src(obj);

    auto validateCast = [&obj, &src]()
    {
        const std::string dest = std::move(obj);
        ASSERT_TRUE(src.empty());
        ASSERT_STREQ(dest.c_str(), "Some str");
    };
    ASSERT_NO_THROW(validateCast());
}

GTEST_TEST(CastsTests, castRvalueTypeErr)
{
    DynamicObject obj(0);
    ASSERT_THROW(const std::string dest = std::move(obj), std::bad_any_cast);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
  
    return RUN_ALL_TESTS();
}
