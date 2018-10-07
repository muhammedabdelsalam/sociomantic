#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Range.h"
#include "UnitTestClass.h"
#include <boost/algorithm/string.hpp>
#include "boost/lexical_cast.hpp" 
#include <bits/stdc++.h>
using boost::lexical_cast;
using boost::bad_lexical_cast;
using namespace std;

// Evaluate The Range, so it replaces "-" dash with the new index.
// Example :
//------------
// Input  : Range = {2 , -},  SizeOfLine = 10
// Output : Range = {2 , 9}
Range replaceDashInRange(Range range, int sizeOfLine) {

    string newRightValue = "";
    string newLeftValue  = "";
    if (range.isLeftDash() && range.isRightDash()) {
        newLeftValue  = to_string((long long int)0);
        newRightValue = to_string((long long int)(sizeOfLine - 1));
    } 
    else if (range.isLeftDash()) {
        newLeftValue  = to_string((long long int)0);
        newRightValue = range.getRight();
    }
    else if (range.isRightDash()) {
        newLeftValue  = range.getLeft();
        newRightValue = to_string((long long int)(sizeOfLine - 1));
    }
    else {
        newLeftValue  = range.getLeft();
        newRightValue = range.getRight();
    }

    Range newRange(newLeftValue, newRightValue);
    return newRange;
}

//Range we will be considerd invalid in the following cases :
// 1. if left index > right index
// 2. if we found negative number on the left or the right side index.
// 3. if we found non integer value on the left or the right index.
// 4. if we found spaces in the left or the right index.
//
// Notes :
// ------
// 1. Range greater than the length of the string line will be considered valid range.
// 2. If we found invalid range we will drop it and continue working with the remaining ranges.
// 3. This step run after replacing dash, so we should not face dash here, if that happen so its invalid range
bool isValidRange(Range range) {
    try {
        int leftRange = lexical_cast<int>(range.getLeft());
        int rightRange = lexical_cast<int>(range.getRight());
	
        if (leftRange < 0 || rightRange < 0) return false;

        if (leftRange > rightRange) return false;

    } catch (bad_lexical_cast &e) {
        return false;
    }
    return true;
}

// This function used to create mask which will be used later to know which bits should appear in the result
// The result is mask contains 1s at the locations that will be shown
// Example :
//----------
// input :
//     str = "abcdefghi"
//   range = {1,2} and {4,5}
// output :
//    mask = "011011000"
int* maskCreator(vector<Range> ranges, int maskSize) {
	
    int* mask =new int[maskSize];
    // initialize the mask by zeros
    for (int i = 0; i < maskSize; i++) {
        mask[i] = 0;
    }


    for (int rangeIndex = 0; rangeIndex < ranges.size(); rangeIndex++) {
		
        Range range = replaceDashInRange(ranges[rangeIndex], maskSize); //This step responsible for replace '-' (dash) in range by correct integer index.

        bool valid = isValidRange(range); //At this step we are making sure that we have valid range, otherwise the invalid range will be dropped.
        if (!valid) continue;    // drop invalid ranges and continue normally

        int leftRange = stoi(range.getLeft());
        int rightRange = stoi(range.getRight());

        for (int i = leftRange; i <= rightRange; i++) {
            if (i >  (maskSize - 1)) {    //If the current index of the range is greater than the size of the string line, so we are done with the mask, no need to waste time.
                break;
            }
            mask[i] = 1;
        }
    }
    return mask;
}

// select bytes based on the 'ranges' provided, and 'complement' flag value
string selectStringByBytes(string str, vector<Range> ranges, bool complement) {
    string result = "";

    std::istringstream f(str);
    std::string line;

    //Read Line by Line
    while (std::getline(f, line)) {
		
        int sizeOfLine = line.size();
        int* mask = maskCreator(ranges, sizeOfLine);  //Create mask to be used in determining which bits will be shown in the result

        string newLineContent = "";

        //iterate over each character to decide if it will appear of not.
        for (int i = 0; i < sizeOfLine; i++) {
            if (mask[i] == complement) continue;      //Using complement flag we will decide to should bits which is corresponding to '1' or '0' in our mask
            newLineContent += line[i];
        }
        result += newLineContent;
        result += "\n";
    }
    return result;
}

// select words based on the 'ranges' provided, and 'complement' flag value
string selectStringBySeparatedStrings(string str, vector<Range> ranges, bool complement) {
    string result = "";

    std::istringstream f(str);
    std::string line;
	
    while (std::getline(f, line)) {

        std::vector<std::string> words;
        boost::split(words, line, boost::is_any_of(" "));

        int numberOfWords = words.size();
        int* mask = maskCreator(ranges, numberOfWords);  //Create mask to be used in determining which bits will be shown in the result

        string newLineContent = "";
        bool firstTime = true;

        //iterate over each word to decide if it will appear of not.
        for (int i = 0; i < numberOfWords; i++) {
            if (mask[i] == complement) continue;      //Using complement flag we will decide to should bits which is corresponding to '1' or '0' in our mask
            if (!firstTime) {
                newLineContent += " ";
            }
            firstTime = false;
            newLineContent += words[i];

        }
        result += newLineContent;
        result += "\n";
    }
    return result;
}

string select(string str, vector<Range> ranges, bool bytes, bool complement) {
    string result = "";
    if (bytes) {
        result = selectStringByBytes(str, ranges, complement);
    }
    else {
        result = selectStringBySeparatedStrings(str, ranges, complement);
    }
    return result;
}

int main()
{

    // 'select' function call example //

    // prepare function input
    string str = "abcdefghijklmnopqrstuvwxyz\n";
    bool bytes = true;
    bool complement = false;
    vector<Range> ranges;
    Range r1("1", "2");
    Range r2("5", "7");
    ranges.push_back(r1);
    ranges.push_back(r2);

    // call the function
    string actualResult = select(str, ranges, bytes, complement);
    cout << "Example Result : " << actualResult << endl;


    // Run unit tests on my functions and print the results
    UnitTestClass unitTest;
    unitTest.Testing_select_Function();
    unitTest.Testing_isValidRange_Function();
    unitTest.Testing_replaceDashInRange_Function();
    unitTest.Testing_maskCreator_Function();
    return 0;
}

