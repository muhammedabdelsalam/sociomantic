#ifndef _Range_h_
#define _Range_h_

#include <string>
using namespace std;

class Range {

private:
    string left;
    string right;

public:

    Range(string _left, string _right) {
        left = _left;
        right = _right;
    }

    string getLeft() {
        return left;
    }

    string getRight() {
        return right;
    }

    void setLeft(string _value) {
        left = _value;
    }

    void setRight(string _value) {
        right = _value;
    }
	
    bool isLeftDash() {
        if (left == "-") return true;
        return false;
    }

    bool isRightDash() {
        if (right == "-") return true;
        return false;
    }
};

#endif
