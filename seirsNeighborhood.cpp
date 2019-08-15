#include "seirsNeighborHood.h"
#include <iostream>
#include <string>
using namespace std;

seirsNeighborHood::seirsNeighborHood() {
	state = ' ';
}

seirsNeighborHood::seirsNeighborHood(string str, string str1, string str2, string str3) {
	
	tHold = 0;
	infection = 0;
	latentPeriod = 0;
	recoveredPeriod = 0;
	int a = str[10] - '0'; //here we are using ASCII code. The -'0' converts a character to its integer representation. 
	setThreshold(a); //setting the threshold 
	int b = str1[7] - '0';
	setInfectionPeriod(b);
	int c = str2[7] - '0';
	setLatentPeriod(c);
	int d = str3[7] - '0';
	setDefaultRecovered(d);
}

void seirsNeighborHood::setState(char s) {
	state = s;
}

char seirsNeighborHood::getState() {
	return state;
}

void seirsNeighborHood::setThreshold(int x) {
	threshold = x;
}


int seirsNeighborHood::getThrsehold() {
	return threshold;
}

void seirsNeighborHood::incrementThreshold() {
	tHold++;
}

int seirsNeighborHood::getIncrementThreshold() {
	return tHold;
}
void seirsNeighborHood::resetThreshold() {
	tHold = 0;
}

void seirsNeighborHood::setInfectionPeriod(int x) {
	infectousPeriod = x;
}

int seirsNeighborHood::getInfectiousPeriod() {
	return infectousPeriod;
}

void seirsNeighborHood::incrementInfection() {
	infection++;
}

int seirsNeighborHood::getIncrementInfectionPeriod() {
	return infection;
}

void seirsNeighborHood::resetInfectiousPeriod() {
	infection = 0;
}


void seirsNeighborHood::setLatentPeriod(int x) {
	latentPeriod = x;
}

int seirsNeighborHood::getLatentPeriod() {
	return latentPeriod;
}

void seirsNeighborHood::incrementExposed() {
	exposure++;
}

int seirsNeighborHood::getIncrementExposed() {
	return exposure;
}

void seirsNeighborHood::resetExposedRate() {
	exposure = 0;
}

void seirsNeighborHood::setDefaultRecovered(int x) {
	recoveredPeriod = x;
}

void seirsNeighborHood::incrementRecoveredRate() {
	recovered++;
}

int seirsNeighborHood::getDefaultRecoveredRate() {
	return recoveredPeriod;
}

int seirsNeighborHood::getIncrementRecoveredRate() {
	return recovered;
}

void seirsNeighborHood::resetRecoveredRate() {
	recovered = 0;
}

