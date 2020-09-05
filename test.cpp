#include "calc.hpp"

#define CATCH_CONFIG_MAIN

#include <catch.hpp>

bool listsAreEqual(list<string> l1, list<string> l2)
{
    bool equal = true;
    
    auto it1 = l1.begin(); 
    auto it2 = l2.begin();

    while (it1 != l1.end() && it2 != l2.end())
    {
        if ((*it1).compare(*it2) != 0)
        {
            equal = false;
            break;
        }
        ++it1;
        ++it2;
    }
    if (!(it1 == l1.end() && it2 == l2.end()))
        equal = false;

    return equal;
}

TEST_CASE( "Split string by symbol into words") {
    string str = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
    list<string> targetList({"1", "+", "(2", "*", "(2.5", "+", "2.5", "+", "(3", "-", "2)))", "-", "(3", "/", "1.5)"});

    list<string> resultList = splitString(str);

    REQUIRE(resultList.size() == targetList.size());
    REQUIRE(listsAreEqual(resultList, targetList));

}

TEST_CASE( "Split brackets from numbers"){

    list<string> inputList({"((5", "+", "6)", "-", "3)"});

    list<string> targetList({
        "(", "(", "5", 
        "+", 
        "6", ")", 
        "-", 
        "3", ")"});

    trimBrackets(inputList);

    REQUIRE(inputList.size() == targetList.size());
    REQUIRE(listsAreEqual(inputList, targetList));
}


TEST_CASE( "Compute") {

    list<string> data;
    
    data =  splitString("-1 + 5 - 3");
    trimBrackets(data); 
    REQUIRE(compute(data, data.begin(), data.end()) == 1);

    data = splitString("-10 + (8 * 2.5) - (3 / 1,5)");
    trimBrackets(data);  
    REQUIRE(compute(data, data.begin(), data.end()) == 8);

    data = splitString("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)");
    trimBrackets(data);  
    REQUIRE(compute(data, data.begin(), data.end()) == 11);
}   