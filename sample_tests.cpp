//
// Created by MARK FONTENOT on 9/14/21.
//

/**
 * This file contains some simple tests.
 *
 * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
 * It is already in catch_setup.cpp
 *
 * Note that you can have more than one cpp file with tests in them.
 * For example, you could have a test file for your DSString and a
 * separate one for your DSVector.
 */

#include "catch.hpp"
#include "DSVector.h"
#include "DSString.h"
TEST_CASE("Testing Tests", "[multiplication]") {
    REQUIRE((2 * 2) == 4);
    REQUIRE((1 * 5) == 5);
}

TEST_CASE("DSVector of Integers", "[DSVec_Int]"){

    /**
     * Things that are at the top of a test case but not inside a section are re-declared before the running of
     * each section.
     */
    DSVector<int> empty_vector;
    DSVector<int> test_vector;
    test_vector.pushBack(10);
    test_vector.pushBack(20);

    SECTION("Testing Empty Vector") {
        REQUIRE(empty_vector.getSize() == 0);
        REQUIRE(test_vector.getSize() != 0);
    }

    SECTION("Testing 10 at first pos and 20 at second") {
        REQUIRE(test_vector[0] == 10);
        REQUIRE(test_vector[1] == 20);
    }

    SECTION("Testing that after pushing back a new element, it is in pos 3") {
        test_vector.pushBack(30);
        CHECK(test_vector[2] == 30);
    }

    SECTION("Push back 30 from above is not in test vector in new section") {
        REQUIRE(test_vector[1] == 20);
    }

}
TEST_CASE("testing DSStrings", "[DSString]") {
    DSString TA01 = "Kevin Leong";
    DSString me = "Vedant Nilabh";
    DSString Matt = "Matt Reno";
    SECTION("check if DSStrings contain what we want and =="){
        REQUIRE(TA01 == "Kevin Leong");
        REQUIRE(me == "Vedant Nilabh");
        REQUIRE(Matt == "Matt Reno");
    }
    SECTION("check that DSString != works"){
        REQUIRE(TA01 != "Vedant Nilabh");
        REQUIRE(TA01 != me);
    }
    SECTION("check DSString += operator"){
        TA01 += me;
        REQUIRE(TA01 == "Kevin LeongVedant Nilabh");
    }
    SECTION("check DSString remove punct"){
        DSString test("This. is[] a? test!");
        test.RemovePunct();
        REQUIRE(test == "This is a test");
    }
}

TEST_CASE("Testing DSVector Copy Constructor", "[DSVector CopyCon]"){
    SECTION("check copy constructor for integers (and eqaulity operator)"){
        DSVector<int> intVec;
        intVec.pushBack(1);
        intVec.pushBack(2);
        intVec.pushBack(3);
        DSVector<int> intVec2 = intVec;
        REQUIRE(intVec2 == intVec);
        intVec.Remove(0);
        REQUIRE(intVec2 != intVec);
    }
    SECTION("check on DSString objects"){
        DSVector<DSString> stringVec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        DSVector<DSString> testVec = stringVec;
        REQUIRE(stringVec == testVec);
        stringVec.Remove(0);
        REQUIRE(stringVec != testVec);
    }

}
TEST_CASE("check overloaded assignment operator") {
    SECTION("check overloaded assigmment for integers (and eqaulity operator)") {
        DSVector<int> intVec;
        intVec.pushBack(1);
        intVec.pushBack(2);
        intVec.pushBack(3);
        DSVector<int> intVec2;
        intVec2 = intVec;
        REQUIRE(intVec2 == intVec);
        intVec.Remove(0);
        REQUIRE(intVec2 != intVec);
    }
    SECTION("check on DSString objects") {
        DSVector<DSString> stringVec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        DSVector<DSString> testVec;
        testVec = stringVec;
        REQUIRE(stringVec == testVec);
        stringVec.Remove(0);
        REQUIRE(stringVec != testVec);
    }

}

TEST_CASE("check the Sort Function is DSVector"){
    SECTION("sorting a vector of integers"){
        DSVector<int> intVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        intVec.Sort();
        REQUIRE(intVec[0] == 3);
        REQUIRE(intVec[1] == 4);
        REQUIRE(intVec[2] == 5);
    }
    SECTION("checking on DSString"){
        DSVector<DSString> strVec;
        strVec.pushBack("zen");
        strVec.pushBack("azure");
        strVec.pushBack("abe");
        strVec.Sort();
        REQUIRE(strVec[0] == "abe");
        REQUIRE(strVec[1] == "azure");
        REQUIRE(strVec[2] == "zen");

    }
}

TEST_CASE("check Remove function - DSVector"){
    SECTION("check with ints"){
        DSVector<int> intVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        intVec.Remove(0);
        REQUIRE(intVec[0] == 4);
        REQUIRE(intVec[1] == 3);
        REQUIRE(intVec[0] != 5);

    }
    SECTION("check with DSString"){
        DSVector<DSString> stringVec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        stringVec.Remove(2);
        REQUIRE(stringVec[0] == "this");
        REQUIRE(stringVec[1] == "is");
        REQUIRE(stringVec.getSize() == 2);
    }
}

TEST_CASE("check Insert function - DSVector"){
    SECTION("check with ints"){
        DSVector<int> intVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        intVec.Insert(0, 0);
        REQUIRE(intVec[0] == 0);
        REQUIRE(intVec[1] == 5);
        REQUIRE(intVec[2] == 4);
        REQUIRE(intVec[3] == 3);
        REQUIRE(intVec.getSize() == 4);

    }
    SECTION("check with DSString"){
        DSVector<DSString> stringVec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        stringVec.Insert(3, "for insert");
        REQUIRE(stringVec[0] == "this");
        REQUIRE(stringVec[1] == "is");
        REQUIRE(stringVec[2] == "a test");
        REQUIRE(stringVec[3] == "for insert");
        REQUIRE(stringVec.getSize() == 4);
    }
}

TEST_CASE("check search function - DSVector"){
    SECTION("check with ints"){
        DSVector<int> intVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        REQUIRE(intVec.Search(3) == 2);
        REQUIRE(intVec.Search(4) == 1);
        REQUIRE(intVec.Search(5) == 0);

    }

    SECTION("check with DSString"){
            DSVector<DSString> stringVec;
            stringVec.pushBack("this");
            stringVec.pushBack("is");
            stringVec.pushBack("a test");
            REQUIRE(stringVec.Search("this") == 0);
            REQUIRE(stringVec.Search("is") == 1);
            REQUIRE(stringVec.Search("a test") == 2);

    }
}

TEST_CASE("check at function - DSVector"){
    SECTION("check with ints"){
        DSVector<int> intVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        REQUIRE(intVec.at(0) == 5);
        REQUIRE(intVec.at(1) == 4);
        REQUIRE(intVec.at(2) == 3);
        REQUIRE(intVec.getSize() == 3);

    }
    SECTION("check with DSString"){
        DSVector<DSString> stringVec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        REQUIRE(stringVec.at(0) == "this");
        REQUIRE(stringVec.at(1) == "is");
        REQUIRE(stringVec.at(2) == "a test");
        REQUIRE(stringVec.getSize() == 3);
    }
}


TEST_CASE("check resize function - DSVector") {
    SECTION("check with ints") {
        DSVector<int> intVec;
        intVec.pushBack(0);
        intVec.pushBack(1);
        intVec.pushBack(2);
        intVec.pushBack(3);
        intVec.pushBack(4);
        intVec.pushBack(5);
        intVec.pushBack(6);
        intVec.pushBack(7);
        intVec.pushBack(8);
        intVec.pushBack(9);
        intVec.pushBack(10);
        REQUIRE(intVec.getSize() == 11);
        REQUIRE(intVec[10] == 10);
    }
}

TEST_CASE("check overloaded relational operators - DSVector"){
    SECTION("check with ints"){
        DSVector<int> intVec;
        DSVector<int> testVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        testVec.pushBack(5);
        testVec.pushBack(4);
        testVec.pushBack(3);
        REQUIRE(intVec[0] == 5);
        REQUIRE(intVec[1] == 4);
        REQUIRE(intVec[2] == 3);
        REQUIRE(intVec.getSize() == 3);
        REQUIRE(intVec == testVec);
        testVec.Remove(2);
        REQUIRE(intVec != testVec);

    }
    SECTION("check with DSString"){
        DSVector<DSString> stringVec;
        DSVector<DSString> string2Vec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        string2Vec.pushBack("this");
        string2Vec.pushBack("is");
        string2Vec.pushBack("a test");
        REQUIRE(stringVec[0] == "this");
        REQUIRE(stringVec[1] == "is");
        REQUIRE(stringVec[2] == "a test");
        REQUIRE(stringVec.getSize() == 3);
        REQUIRE(stringVec == string2Vec);
        string2Vec.Remove(0);
        REQUIRE(stringVec != string2Vec);
    }
}

TEST_CASE("check subscript operator - DSVector"){
    SECTION("check with ints"){
        DSVector<int> intVec;
        intVec.pushBack(5);
        intVec.pushBack(4);
        intVec.pushBack(3);
        REQUIRE(intVec[0] == 5);
        REQUIRE(intVec[1] == 4);
        REQUIRE(intVec[2] == 3);
        REQUIRE(intVec.getSize() == 3);

    }
    SECTION("check with DSString"){
        DSVector<DSString> stringVec;
        stringVec.pushBack("this");
        stringVec.pushBack("is");
        stringVec.pushBack("a test");
        REQUIRE(stringVec[0] == "this");
        REQUIRE(stringVec[1] == "is");
        REQUIRE(stringVec[2] == "a test");
        REQUIRE(stringVec.getSize() == 3);
    }
}