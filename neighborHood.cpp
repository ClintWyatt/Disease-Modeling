#include "NeigborHood.h"
#include <iostream>
#include <string>

using namespace std;

neighbor::neighbor() {
	state = ' ';
}

neighbor::neighbor(string str, string str1) {
	thold = str;
	infect = str1;
	tHold = 0;
	infection = 0;
	int x = str[10]-'0'; //here we are using ASCII code. The -'0' converts a character to its integer representation. 
	setThreshold(x); //setting the threshold 
	int y = str1[7] - '0';
	setInfectionRate(y);

}

void neighbor::setState(char s) {
	state = s;
}

void neighbor::setThreshold(int x) {
	threshold = x;
}

void neighbor::setInfectionRate(int x) {
	infectousPeriod = x;
}

int neighbor::getInfectiousPeriod() {
	return infectousPeriod;
}


int neighbor::getThrsehold() {
	return threshold;
}

char neighbor::getState() {
	return state;
}

void neighbor::incrementInfectionPeriod() {
	infection++;
}

int neighbor::getIncrementInfectionPeriod() {
	return infection;
}

void neighbor::incrementThreshold() {
	tHold++;
}

int neighbor::getIncrementThreshold() {
	return tHold;
}
void neighbor::resetThreshold() {
	tHold = 0;
}