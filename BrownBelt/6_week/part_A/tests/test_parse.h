#pragma once 

#include "test_runner.h"
#include "../project/parse.h"

#include <sstream>
#include <string>
#include <utility>

void Test_Parse() {
    { // test DeleteWhiteSpace
        std::string one;
        std::string two = " ";
        std::string three = "a";
        std::string four = "a ";
        std::string five = " a ";
        std::string six = " a";

        ASSERT_EQUAL(DeleteWhiteSpace(one), one);
        ASSERT_EQUAL(DeleteWhiteSpace(two), one);
        ASSERT_EQUAL(DeleteWhiteSpace(three), "a");
        ASSERT_EQUAL(DeleteWhiteSpace(four), "a");
        ASSERT_EQUAL(DeleteWhiteSpace(five), "a");
        ASSERT_EQUAL(DeleteWhiteSpace(six), "a");
    }
    { // test SplitStrOpt
        std::string one = "";
        std::string two = "a";
        std::string three = "a b";
        std::string four = " a b";
        std::string five = " a b ";
        std::string six = "a b ";
        std:: string seven = "a, b";

        auto [one_head, one_tail] = SplitStrOpt(one);
        auto [two_head, two_tail] = SplitStrOpt(two);
        auto [three_head, three_tail] = SplitStrOpt(three);
        auto [four_head, four_tail] = SplitStrOpt(four);
        auto [five_head, five_tail] = SplitStrOpt(five);
        auto [six_head, six_tail] = SplitStrOpt(six);
        auto [seven_head, seven_tail] = SplitStrOpt(seven, ",");
        
        ASSERT_EQUAL(one_head, one);
        ASSERT_EQUAL(two_head, two);
        ASSERT_EQUAL(three_head, two);
        ASSERT_EQUAL(four_tail.value(), three);
        ASSERT_EQUAL(five_tail.value(), three);
        ASSERT_EQUAL(six_head, two);
        ASSERT_EQUAL(seven_head, two);

        ASSERT(one_tail == std::nullopt);
        ASSERT(two_tail == std::nullopt);
        ASSERT_EQUAL(three_tail.value(), "b");
        ASSERT_EQUAL(six_tail.value(), "b");
        ASSERT_EQUAL(seven_tail.value(), "b");
    }
    { // test SplitStrStr
        std::string one = "";
        std::string two = " ";
        std::string three = "a";
        std::string four = "a ";
        std::string five = " a ";
        std::string six = " a";
        std::string seven = "a b";
        std::string eight = "a b ";
        std::string nine = " a b";
        std::string ten = " a b ";

        ASSERT_EQUAL(SplieStrStr(one).first, "");
        ASSERT_EQUAL(SplieStrStr(two).second, "");
        ASSERT_EQUAL(SplieStrStr(three).second, "");
        ASSERT_EQUAL(SplieStrStr(four).first, "a");
        ASSERT_EQUAL(SplieStrStr(five).second, "a");
        ASSERT_EQUAL(SplieStrStr(six).first, "");
        ASSERT_EQUAL(SplieStrStr(seven).second, "b");
        ASSERT_EQUAL(SplieStrStr(eight).second, "b");
        ASSERT_EQUAL(SplieStrStr(nine).second, "a b");
        ASSERT_EQUAL(SplieStrStr(ten).second, "a b");
    }
    { // test ConvertStrToDouble
        std::string one = "65.78";
        std::string two = "0.0";
        std::string three = "7";
        std::string four = "0.5";
        std::string five = "0";
        std::string six = "-67.78";

        ASSERT_EQUAL(ConvertStrToDbl(one), 65.78);
        ASSERT_EQUAL(ConvertStrToDbl(two), 0.0);
        ASSERT_EQUAL(ConvertStrToDbl(three), 7.0);
        ASSERT_EQUAL(ConvertStrToDbl(four), 0.5);
        ASSERT_EQUAL(ConvertStrToDbl(five), 0.0);
        ASSERT_EQUAL(ConvertStrToDbl(six), -67.78);
    }
}