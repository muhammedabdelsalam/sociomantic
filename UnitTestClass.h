#ifndef _UnitTestClass_h_
#define _UnitTestClass_h_

#include <string>

using namespace std;

class Range;
class UnitTestClass
{
public:
    UnitTestClass() {}
    ~UnitTestClass() {}


    void Testing_replaceDashInRange_Function(); // Testing function (replaceDashInRange) with replace dash '-' with index based on the size of the input string in a given line
    void Testing_maskCreator_Function();        // Testing the mask generation function (maskCreator)
    void Testing_isValidRange_Function();       // Testing the function (isValidRange), so this function test the range after the evluation, so we should not face dash '-' at this step
    void Testing_select_Function();             // Testing the main select function

// Each function respresents test point for select function
    void select_testPoint0();
    void select_testPoint1();
    void select_testPoint2();
    void select_testPoint3();
    void select_testPoint4();
    void select_testPoint5();
    void select_testPoint6();
    void select_testPoint7();
    void select_testPoint8();
    void select_testPoint9();
    void select_testPoint10();
    void select_testPoint11();
    void select_testPoint12();
    void select_testPoint13();
    void select_testPoint14();
    void select_testPoint15();
    void select_testPoint16();
    void select_testPoint17();
    void select_testPoint18();
    void select_testPoint19();
    void select_testPoint20();
    void select_testPoint21();

// Each function respresents test point for maskCreator function
    void maskCreator_testPoint1();
    void maskCreator_testPoint2();
    void maskCreator_testPoint3();
    void maskCreator_testPoint4();
    void maskCreator_testPoint5();
    void maskCreator_testPoint6();

// Each function respresents test point for isValidRange function
    void isValidRange_testPoint1(bool isPositiveTestCase);
    void isValidRange_testPoint2(bool isPositiveTestCase);
    void isValidRange_testPoint3(bool isPositiveTestCase);
    void isValidRange_testPoint4(bool isPositiveTestCase);
    void isValidRange_testPoint5(bool isPositiveTestCase);
    void isValidRange_testPoint6(bool isPositiveTestCase);
    void isValidRange_testPoint7(bool isPositiveTestCase);
    void isValidRange_testPoint8(bool isPositiveTestCase);

// Each function respresents test point for replaceDashInRange function
    void replaceDashInRange_testPoint1();
    void replaceDashInRange_testPoint2();
    void replaceDashInRange_testPoint3();
    void replaceDashInRange_testPoint4();
    void replaceDashInRange_testPoint5();
    void replaceDashInRange_testPoint6();


    int* generateExpectedData(string str);

// Functions below used to compare expected results with actual resuts and print the result.
    void GetResult(string functionName, string testPointID, bool actualResult, bool expectedResult);
    void GetResult(string functionName, string testPointID, string actualResult, string expectedResult);
    void GetResult(string functionName, string testPointID, Range actualResult, Range expectedResult);
    void GetResult(string functionName, string testPointID, int* actualResult, int* expectedResult, int size);
    string messageCreator(string funcName, string ID, string result);
};

#endif
