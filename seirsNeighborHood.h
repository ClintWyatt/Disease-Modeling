#ifndef H_seirsNeighborHood
#define H_seirsNeighborHood
#include <iostream>


#include <string>

using namespace std;

class seirsNeighborHood {

public:

	seirsNeighborHood();
	//no-Arg constructor. Sets The state to a empty character
	seirsNeighborHood(string str, string str1, string str2, string str3);
	//Constructor sets the string value of threshold, infectious period and display to strings.
	//Then, all charactrers at the end of each string are numbers(Example would be display:2, 2 is 
	//converted to a integer).
	void setState(char s);
	//function will set the state of the neighbor object. 
	void setThreshold(int x);
	//function sets the current threshold 
	int getThrsehold();
	//function returns the value of threshold
	void incrementThreshold();
	//incrementes the threshold for state s. 
	int getIncrementThreshold();
	//returns the value of the tHold for state s. 
	void resetThreshold();
	//function will reset the tHold if the number of infectious agents in a neighbor hood is not greater than or equal to the 
	//threshold. 
	void setInfectionPeriod(int x);
	//function sets the infection rate
	int getInfectiousPeriod();
	//function returns the value of the infectious period.
	void incrementInfection();
	//function will increment the infection varaible. If Infection is greater than the infectious period, the state will
	//change from 'i' to r. 
	void resetInfectiousPeriod();
	//function will reset the infectious period when the infected neighbor goes to state r. 
	int getIncrementInfectionPeriod();
	//function returns the value of the infection variable
	void setLatentPeriod(int x);
	//function sets the exposed rate, state e. 
	int getLatentPeriod();
	//function returns the integer representation of the latent period. 
	void incrementExposed();
	//function increments the latnet period.
	int getIncrementExposed();
	//function will return the latent period.
	void resetExposedRate();
	//function resets the exposed rate if the exposed rate did not reach the required exposed rate that day.
	void setDefaultRecovered(int x);
	//function will take the last character 
	int getDefaultRecoveredRate();
	//function will return the recovered rate. 
	void incrementRecoveredRate();
	//function will increment the recovered rate. 
	int getIncrementRecoveredRate();
	//function returns the value of recoveredRate.
	void resetRecoveredRate();
	//funciton resets the recovered rate.
	
	
	
	
	char getState();
	//function returns the state of the neighbor object
private:
	int infection;//will be constantly incremented. 
	char state;
	int threshold = 0;
	int exposure = 0; //will test against the latentPeriod
	int latentPeriod;
	int tHold;
	int infectousPeriod;
	int recovered = 0;
	int recoveredPeriod;
	/*string infectedPeriod;
	string thold;
	string lPeriod;
	string rPeriod;*/
};

#endif // !H_seirsNeighborHood

