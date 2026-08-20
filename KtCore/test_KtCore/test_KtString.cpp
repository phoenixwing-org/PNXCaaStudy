/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        test_KtString.cpp
 * @version		V1.0
 */
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

#include <KtCore/KtString.h>

//---------------------------------------------------------------------------------------
TEST_CASE("Test KtString", "[KtString]") {

    SECTION("KtString") {
        KtString ks;
        ks.append("Hello, World!");
        REQUIRE(ks.size() == 13);
        REQUIRE(ks.capacity() == 13);
        REQUIRE(ks.to_lower() == "hello, world!");
        REQUIRE(ks.to_upper() == "HELLO, WORLD!");
        std::cout << " - ks.str() = " << ks.str() << std::endl;
    }

    SECTION("trim string") {
        KtString ks;
        ks.append(" \t Hello, World!\r\n");
        REQUIRE(ks.size() == 18);
        REQUIRE(ks.capacity() == 18);
        REQUIRE(ks.trim() == "Hello, World!"); // 第1次
        REQUIRE(ks.trim() == "Hello, World!"); // 第2次
        std::cout << " - ks.str() = " << ks.str() << std::endl;
    }
}
