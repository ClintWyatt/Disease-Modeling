#ifndef H_neighborSquare
#define H_neighborSquare

#include <iostream>
#include <string>
#include "NeigborHood.h"
#include <vector>
using namespace std;

class neighborSquare {

public:
	neighborSquare(string str, string str2, string str3);
	//constructor will accept the length of the string from the input file, the string representation
	//of display, threshold, and infection period from the input file. 
	void lineSize();
	//function eliminate all comas from the string.
	void set2dVector();
	//Function sets the 2d vector by using a temporary vector and pushing it onto the nb vector.
	void setSquare();
	//function will set the dimensions of the square. 
	void outBreak();
	//funciton will loop until there are no infected neighborhoods left. 
	void corners();
	//function will test to see if the 2d array's current position is any of the corners in the 2d array
	void topLeftCorner();
	//top left corner of the 2d array. 
	void topRightCorner();
	//top right corner of the 2d array.
	void bottomLeftCorner();
	//bottom left corner of the 2d array.
	void bottomRightCorner();
	//bottom right corner of the 2d array. 
	void topAndBottom();
	//function will test to see if the current position in the 2d array is the top row or bottom row.
	void top();
	//top row of the 2d array, excludes the top left corner and top right corner.
	void bottom();
	//bottom row of the 2d array, excludes the bottom left corner and bottom right corner. 
	void sides();
	//function tests to see if the current position in the 2d array is on the left or right side of the square. 
	void left();
	//function tests to see if the current position in the 2d array is on the first column, excluding the 
	//first and last row.
	void right();
	//function tests to see if the current position in the 2d array is on the last column, excluding the
	//first and last row. 
	void insideSquare();
	//function tests to see if the current position is inside the square. 
	void status();
	//function traverses through the 2d array and finds the number of infected 
	void fileString(string str);
	//function takes in the string representation from the input file. 
	void setDisplay(int x);
	//function will take in the integer representation of day. 
	void _ItoR();
	//function will change the infected state to a recovered state if the infected state's infected state is greater than
	//the infectious period
	void _Itoi();
	//function changes the state from I to i. We are doing this because if we change the suceptible to infected(i), some undesirable
	//chain reactions will happen in a day. 
	void infectedLeft();
	//function checks the number of infected left. 
	void isMaxOutbreak();
	//function checks to see which day was the outbreak day.
	
private:
	
	vector<vector<neighbor>> nb;
	vector<vector<neighbor>> tomorrow;
	int lineLength;
	int display;
	int numInfected =0;
	int numRecovered =0;
	int numVacinated =0;
	int numSusceptible =0;
	int day;
	int outBreakDay = 0;
	int outBreakInfected =0;
	int a;//used to keep track of the 2d vector index
	int b;//used to keep track of the 2d vector index
	//string line;
	string thresHold;
	string infectiousPeriod;
	vector<char> lineString;
	vector<char> stringSize;
	char infected = 'i';
	char recovered = 'r';
	char vacinated = 'v';
	char suceptible = 's';
};
#endif // !H_neighborSquare

