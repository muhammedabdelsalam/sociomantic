Name :
----------------------
Muhammed Abdelsalam Thabet

Compilation Command :
----------------------
gcc -std=c++0x -o select.o main.cpp UnitTestClass.cpp -I . -I /esd/shared/mthabet/boost_Installation/prefix/include/ -L/esd/shared/mthabet/boost_Installation/prefix/lib/ -lstdc++


Running command :
-----------------
./select.o


Assumptions :
----------------
1. If one of the ranges is invalid so it will be dropped and we will continue normally, so it will not affect the result.
2. Ranges indexes can not be negative numbers and can not be anything other than integers and dash '-', any thing else will make the range invalid.
3. The right index in the range could be greater than the size of the input string, and this range will be considered as a valid range.


UnitTestClass :
-----------------
It contains unit test for my functions in main.cpp
Each function is tested and compare actual results with expected results to print if the test passed or failed