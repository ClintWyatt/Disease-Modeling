#ifndef H_NeighborHood
#define H_NeighborHood
#include <iostream>
#include <string>

using namespace std;

class neighbor {

public:
	
	neighbor();
	//no-Arg constructor. Sets The state to a empty character
	neighbor(string str, string str1);
	//Constructor sets the string value of threshold, infectious period and display to strings.
	//Then, all charactrers at the end of each string are numbers(Example would be display:2, 2 is 
	//converted to a integer).
	void setState(char s);
	//function will set the state of the neighbor object. 
	void setThreshold(int x);
	//function sets the current threshold 
	void setInfectionRate(int x);
	//function sets the infection rate
	int getThrsehold();
	//function returns the value of threshold
	int getInfectiousPeriod();
	//function returns the value of the infectious period.
	char getState();
	//function returns the state of the neighbor object
	void incrementInfectionPeriod();
	//function will increment the infection varaible. If Infection is greater than the infectious period, the state will
	//change from 'i' to r. 
	int getIncrementInfectionPeriod();
	//function returns the value of the infection variable
	void incrementThreshold();
	//incrementes the threshold
	int getIncrementThreshold();
	//returns the value of the tHold
	void resetThreshold();
	//function will reset the tHold if the number of infectious agents in a neighbor hood is not greater than or equal to the 
	//threshold. 

private:
	int infection;//will be constantly incremented. 
	char state;
	int threshold =0;
	int tHold;
	int infectousPeriod;
	string infect;
	string thold;
};
#endif // !H_NeighborHood 

