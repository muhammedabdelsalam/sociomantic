#include "UnitTestClass.h"
#include <string>
#include <iostream>
#include <vector>
#include "Range.h"


extern Range replaceDashInRange(Range range, int sizeOfLine);
extern bool isValidRange(Range range);
extern int* maskCreator(vector<Range> ranges, int maskSize);
extern string select(string str, vector<Range> ranges, bool bytes, bool complement);

// Testing the main select function
void UnitTestClass::Testing_select_Function() {

    // TestPoints description written in the comments beside functions calls

    select_testPoint0();  // run testcase with big input string.
    select_testPoint1();  // Each word in the line is only one character and the ranges cover all the line.
    select_testPoint2();  // Invalid input but try to make sure that no crashes will happen
    select_testPoint3();  // Lines without words at all.
    select_testPoint4();  // empty line even without line terminator \n
    select_testPoint5();  // no ranges at all given in the input
    select_testPoint6();  // no ranges at all given in the input, but the complement flag is true.
    select_testPoint7();  // no ranges at all given in the input, but bytes flag is true
    select_testPoint8();  // no ranges at all given in the input, but both bytes and complement flags is true
    select_testPoint9();  // input string contains more than one space between two words, and also more than one range where left and right index are the same, exampple {1 ,1} {2, 2}
    select_testPoint10(); // same as no.9 but comlement flag is true, also it tests the behaviour when we give more than one/two ranges
    select_testPoint11(); // select last bit and first bit only
    select_testPoint12(); // ignore last bit and first bit only
    select_testPoint13(); // part of input string is selected more than once by multiple ranges, this one was given in the problem description examples
    select_testPoint14(); // ignore first and last work in each line, which means complement is true
    select_testPoint15(); // select first and last work in each line, which means complement is false
    select_testPoint16(); // open ranges is working correctly, this one was given in the problem description examples
    select_testPoint17(); // open ranges is working correctly with complement 
    select_testPoint18(); // this one was given in the problem description examples
    select_testPoint19(); // this one was given in the problem description examples
    select_testPoint20(); // this one was given in the problem description examples
    select_testPoint21(); // this one was given in the problem description examples
}

// Testing the mask generation function (maskCreator)
void UnitTestClass::Testing_maskCreator_Function() {
    maskCreator_testPoint1(); // normal testcase
    maskCreator_testPoint2(); // select first  index and last index and one in the middle
    maskCreator_testPoint3(); // select certain part by more than one range, and add range with right index greater than the size of the input string
    maskCreator_testPoint4(); // add two ranges which cover all the string line
    maskCreator_testPoint5(); // add range that covers all the string line except one bit.
    maskCreator_testPoint6(); // select only the bit in the beginning
}

// Testing the function (isValidRange), so this function test the range after the evluation, so we should not face dash '-' at this step
void UnitTestClass::Testing_isValidRange_Function() {
    bool positive = true;
    bool negative = false;

    // TestPoints description written in the comments beside functions calls

    //positive testcases
    isValidRange_testPoint1(positive);  // valid range as left index is smaller than right index
    isValidRange_testPoint2(positive);  // valid range as left index equals to right index

    //negative testcases
    isValidRange_testPoint3(negative);  // invalid because right index smaller than left index
    isValidRange_testPoint4(negative);  // one negative index found
    isValidRange_testPoint5(negative);  // both right and left are negative
    isValidRange_testPoint6(negative);  // left index contains non integer value
    isValidRange_testPoint7(negative);  // right index value is dash '-'
    isValidRange_testPoint8(negative);  // right index value is space ' '
}

// Testing the function (replaceDashInRange) which replaces dash '-' with index based on the size of the input string in a given line
void UnitTestClass::Testing_replaceDashInRange_Function() {
    replaceDashInRange_testPoint1();   // range contains dash on the left index and dash on the right index
    replaceDashInRange_testPoint2();   // range contains only one dash on the left index
    replaceDashInRange_testPoint3();   // range contains only one dash on the right index
    replaceDashInRange_testPoint4();   // range does not contains dash and the values of the left and right is greater than the size of the string line
    replaceDashInRange_testPoint5();   // range contains alphabet on the left index and space on the right index, which is both is invalid
    replaceDashInRange_testPoint6();   // range contains alphabet on the left index and integer on the right index
}

int* UnitTestClass::generateExpectedData(string str) {
    int* ptr = new int[str.size()];
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '1') {
            ptr[i] = 1;
        }
        else {
            ptr[i] = 0;
        }
    }
    return ptr;
}

void UnitTestClass::select_testPoint0() {
    string str = "Paragraphs are the building blocks of papers. Many students\n";
    str += "define paragraphs in terms of length: a paragraph\n";
    str += "is a group of at least five sentences, a paragraph is\n";
    str += "half a page long, etc. In reality, though, the unity and\n";
    str += "coherence of ideas among sentences is what constitutes a paragraph.\n";

    string expectedResult = "Paragraphs are the of Many students\n";
    expectedResult += "define paragraphs in length: paragraph\n";
    expectedResult += "is a group least sentences, a paragraph is\n";
    expectedResult += "half a page In though, the unity and\n";
    expectedResult += "coherence of ideas is constitutes a paragraph.\n";

    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "2");
    Range r2("5", "5");
    Range r3("7", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S0", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint1() {
    string str = "A B C D E F G H I J\n";
    string expectedResult = "A B C D E F G H I J\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "5");
    Range r2("6", "6");
    Range r3("7", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S1", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint2() {
    string str = "      \n";
    string expectedResult = "    \n";
    bool bytes = true;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "1");
    Range r2("4", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S2", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint3() {
    string str = "\n\n\n";
    string expectedResult = "\n\n\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("2", "2");
    Range r3("4", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S3", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint4() {
    string str = "";
    string expectedResult = "";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("2", "2");
    Range r3("4", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S4", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint5() {
    string str = "Hope you are fine now.\nAnd you family also\n";
    string expectedResult = "\n\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S5", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint6() {
    string str = "Hope you are fine now.\nAnd you family also\n";
    string expectedResult = "Hope you are fine now.\nAnd you family also\n";
    bool bytes = false;
    bool complement = true;
    vector<Range> ranges;

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S6", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint7() {
    string str = "Hope you are fine now.\nAnd you family also\n";
    string expectedResult = "\n\n";
    bool bytes = true;
    bool complement = false;
    vector<Range> ranges;

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S7", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint8() {
    string str = "Hope you are fine now.\nAnd you family also\n";
    string expectedResult = "Hope you are fine now.\nAnd you family also\n";
    bool bytes = true;
    bool complement = true;
    vector<Range> ranges;

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S8", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint9() {
    string str = "My Name is Abbas\nI Love My Children\nI Love Sports\nA B C D E F  G  H\n";
    string expectedResult = "My is\nI My\nI Sports\nA C E F  G  H\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("2", "2");
    Range r3("4", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S9", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint10() {
    string str = "My Name is Abbas\nI Love My Children\nI Love Sports\nA B C D E F  G  H\n";
    string expectedResult = "Name Abbas\nLove Children\nLove\nB D\n";
    bool bytes = false;
    bool complement = true;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("2", "2");
    Range r3("4", "-");

    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);

    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S10", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint11() {
    string str = "abcdefghijklmnopqrstuvwxyz\n";
    string expectedResult = "az\n";
    bool bytes = true;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("25", "25");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S11", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint12() {
    string str = "abcdefghijklmnopqrstuvwxyz\n";
    string expectedResult = "bcdefghijklmnopqrstuvwxy\n";
    bool bytes = true;
    bool complement = true;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("25", "25");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S12", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint13() {
    string str = "abcdefghijklmnopqrstuvwxyz\n";
    string expectedResult = "bcdefg\n";
    bool bytes = true;
    bool complement = false;
    vector<Range> ranges;
    Range r1("1", "4");
    Range r2("3", "6");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S13", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint14() {
    string str = "Can you test that line please\nif yes test it and respond\n";
    string expectedResult = "you test that line\nyes test it and\n";
    bool bytes = false;
    bool complement = true;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("5", "5");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S14", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint15() {
    string str = "Can you test that line please\nif yes test it and respond\n";
    string expectedResult = "Can please\nif respond\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("5", "5");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S15", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint16() {
    string str = "This is a longer string\nsplit over two lines\n";
    string expectedResult = "This is a string\nsplit over two\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("-", "2");
    Range r2("4", "-");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S16", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint17() {
    string str = "This is a longer string\nsplit over two lines\n";
    string expectedResult = "longer\nlines\n";
    bool bytes = false;
    bool complement = true;
    vector<Range> ranges;
    Range r1("-", "2");
    Range r2("4", "-");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S17", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint18() {
    string str = "abcdefghijklmnopqrstuvwxyz\n";
    string expectedResult = "bcfgh\n";
    bool bytes = true;
    bool complement = false;
    vector<Range> ranges;
    Range r1("1", "2");
    Range r2("5", "7");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S18", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint19() {
    string str = "abcdefghijklmnopqrstuvwxyz\n";
    string expectedResult = "adeijklmnopqrstuvwxyz\n";
    bool bytes = true;
    bool complement = true;
    vector<Range> ranges;
    Range r1("1", "2");
    Range r2("5", "7");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S19", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint20() {
    string str = "This is a longer string\nsplit over two lines\n";
    string expectedResult = "This a longer string\nsplit two lines\n";
    bool bytes = false;
    bool complement = false;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("2", "-");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S20", actualResult, expectedResult);
}

void UnitTestClass::select_testPoint21() {
    string str = "This is a longer string\nsplit over two lines\n";
    string expectedResult = "is\nover\n";
    bool bytes = false;
    bool complement = true;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("2", "-");
    ranges.push_back(r1);
    ranges.push_back(r2);
    string actualResult = select(str, ranges, bytes, complement);
    GetResult("select", "S21", actualResult, expectedResult);
}

void UnitTestClass::maskCreator_testPoint1() {
    int size = 10;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("1", "1");
    Range r3("8", "10");
    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);
    GetResult("maskCreator", "M1", maskCreator(ranges, size), generateExpectedData("1100000011"), size);
}

void UnitTestClass::maskCreator_testPoint2() {
    int size = 10;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("5", "5");
    Range r3("9", "9");
    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);
    GetResult("maskCreator", "M2", maskCreator(ranges, size), generateExpectedData("1000010001"), size);
}

void UnitTestClass::maskCreator_testPoint3() {
    int size = 10;
    vector<Range> ranges;
    Range r1("0", "3");
    Range r2("2", "5");
    Range r3("9", "37");
    ranges.push_back(r1);
    ranges.push_back(r2);
    ranges.push_back(r3);
    GetResult("maskCreator", "M3", maskCreator(ranges, size), generateExpectedData("1111110001"), size);
}

void UnitTestClass::maskCreator_testPoint4() {
    int size = 10;
    vector<Range> ranges;
    Range r1("0", "5");
    Range r2("6", "10");
    ranges.push_back(r1);
    ranges.push_back(r2);
    GetResult("maskCreator", "M4", maskCreator(ranges, size), generateExpectedData("1111111111"), size);
}

void UnitTestClass::maskCreator_testPoint5() {
    int size = 10;
    vector<Range> ranges;
    Range r1("0", "5");
    Range r2("7", "10");
    ranges.push_back(r1);
    ranges.push_back(r2);
    GetResult("maskCreator", "M5", maskCreator(ranges, size), generateExpectedData("1111110111"), size);
}

void UnitTestClass::maskCreator_testPoint6() {
    int size = 10;
    vector<Range> ranges;
    Range r1("0", "0");
    Range r2("10", "11");
    ranges.push_back(r1);
    ranges.push_back(r2);
    GetResult("maskCreator", "M6", maskCreator(ranges, size), generateExpectedData("1000000000"), size);
}


void UnitTestClass::isValidRange_testPoint1(bool isPositiveTestCase) {
    Range r1("1", "7");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I1", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint2(bool isPositiveTestCase) {
    Range r1("0", "0");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I2", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint3(bool isPositiveTestCase) {
    Range r1("7", "1");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I3", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint4(bool isPositiveTestCase) {
    Range r1("-1", "1");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I4", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint5(bool isPositiveTestCase) {
    Range r1("-2", "-1");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I5", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint6(bool isPositiveTestCase) {
    Range r1("AA", "7");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I6", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint7(bool isPositiveTestCase) {
    Range r1("7", "-");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I7", isValid, isPositiveTestCase);
}

void UnitTestClass::isValidRange_testPoint8(bool isPositiveTestCase) {
    Range r1("7", " ");
    bool isValid = isValidRange(r1);
    GetResult("isValidRange", "I8", isValid, isPositiveTestCase);
}

void UnitTestClass::replaceDashInRange_testPoint1(){
    Range r1("-", "-");
    Range actualNewRange = replaceDashInRange(r1, 10);
    Range expectedResultRange("0", "9");
    GetResult("replaceDashInRange", "R1", actualNewRange, expectedResultRange);
}

void UnitTestClass::replaceDashInRange_testPoint2(){
    Range r1("-", "1");
    Range actualNewRange = replaceDashInRange(r1, 10);
    Range expectedResultRange("0", "1");
    GetResult("replaceDashInRange", "R2", actualNewRange, expectedResultRange);
}

void UnitTestClass::replaceDashInRange_testPoint3(){
    Range r1("12", "-");
    Range actualNewRange = replaceDashInRange(r1, 10);
    Range expectedResultRange("12", "9");
    GetResult("replaceDashInRange", "R3", actualNewRange, expectedResultRange);
}

void UnitTestClass::replaceDashInRange_testPoint4(){
    Range r1("12", "12");
    Range actualNewRange = replaceDashInRange(r1, 10);
    Range expectedResultRange("12", "12");
    GetResult("replaceDashInRange", "R4", actualNewRange, expectedResultRange);
}

void UnitTestClass::replaceDashInRange_testPoint5(){
    Range r1("ABC", "  ");
    Range actualNewRange = replaceDashInRange(r1, 10);
    Range expectedResultRange("ABC", "  ");
    GetResult("replaceDashInRange", "R5", actualNewRange, expectedResultRange);
}

void UnitTestClass::replaceDashInRange_testPoint6(){
    Range r1("ABC", "-");
    Range actualNewRange = replaceDashInRange(r1, 10);
    Range expectedResultRange("ABC", "9");
    GetResult("replaceDashInRange", "R6", actualNewRange, expectedResultRange);
}

// Functions below used to compare expected result with actual results and print the status of this testpoint.
void UnitTestClass::GetResult(string functionName, string testPointID, string actualResult, string expectedResult) {
    string status = "";
    if (actualResult == expectedResult) status = "Passed";
    else status = "Failed";

    cout << messageCreator(functionName, testPointID, status) << endl;
}

void UnitTestClass::GetResult(string functionName, string testPointID, bool actualResult, bool expectedResult) {
    string status = "";
    if (actualResult == expectedResult) status = "Passed";
    else status = "Failed";
    
    cout << messageCreator(functionName, testPointID, status) << endl;
}

void UnitTestClass::GetResult(string functionName, string testPointID, Range actualResult, Range expectedResult) {
    string status = "";
    if (actualResult.getLeft() == expectedResult.getLeft() &&
        actualResult.getRight() == expectedResult.getRight()) {
        status = "Passed";
    }
    else {
        status = "Failed";
    }
    cout << messageCreator(functionName, testPointID, status) << endl;
}

void UnitTestClass::GetResult(string functionName, string testPointID, int* actualResult, int* expectedResult, int size) {
    string status = "Invalid Input So No Mask Created";
    for (int i = 0; i < size; i++) {
        if (actualResult[i] != expectedResult[i]) {
            status = "Failed";
            break;
        } else {
			status = "Passed";
		}
    }

    cout << messageCreator(functionName, testPointID, status) << endl;
}

string UnitTestClass::messageCreator(string funcName, string ID, string status) {
    string str = "Unit Test for Function " + funcName + "\n";
    str += "Testpoint ID = " + ID + "\n";
    str += "Result is : " + status + "\n";
    str += "------------------------\n";
    return str;
}
