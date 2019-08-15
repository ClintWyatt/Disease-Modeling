#include "seirsSquare.h"
#include "seirsNeighborHood.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std; 

seirsSquare::seirsSquare(string str, string str1, string str2, string str3, string str4, string str5) {
	thresHold = str;
	infectiousPeriod = str1;
	latentPeriod = str2;
	recoveredPeriod = str3;
	int a = str4[8] - '0';
	setDisplay(a);
	//below is for getting the max days.
	if (str5.length() == 6) {
		int b = str5[5] - '0';
		setMaxDays1Digit(b);
	}
	else if (str5.length() == 7) {
		int b = str5[5] - '0';
		int c = str5[6] - '0';
		setMaxDays2Digit(b, c);
	}
	//a and b help us keep track of the position in the 2d array in other functions. 
	a = 0;
	b = 0;
	day = 0;
	numInfected = 0;

}
void seirsSquare::setMaxDays1Digit(int x) {
	maxDays = x;
}

void seirsSquare::setMaxDays2Digit(int x, int y) {

	maxDays = x * pow(10, 1) + y * pow(10, 0);
}

void seirsSquare::setDisplay(int x) {
	display = x;
}

void seirsSquare::fileString(string str) {


	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',') {
			//Do nothing, which is like skipping the ","
		}
		else {
			lineString.push_back(str[i]);

		}

	}

}


void seirsSquare::lineSize() {
	lineLength = sqrt(lineString.size());
}

void seirsSquare::set2dVector() {


	int x = 0;
	for (int z = 0; z < lineLength; z++) {

		vector<seirsNeighborHood> temp;
		for (int j = 0; j < lineLength; j++) {

			seirsNeighborHood fg(thresHold, infectiousPeriod, latentPeriod, recoveredPeriod); //this object will be added to the temp vector, which is of neighbor type
			fg.setState(lineString[x]); //setting the neighbor object's state to the current character in the squareString.
			temp.push_back(fg);//adding the neighbor object to the neighbor vector
			x++;

		}
		nb.push_back(temp);//adding the neighbor vector (temp) to another neighbor vector, nb. This creates a 2d vector.

	}

}

void seirsSquare::setSquare() {
	cout << "Day " << day << endl;
	for (int x = 0; x < lineLength; x++) {
		for (int j = 0; j < lineLength; j++) {
			cout << nb[x][j].getState();
		}
		cout << endl;
	}
	
	day++;
}

void seirsSquare::status() {

	//below are the counts of the neighbor status. We traverse through the 2d vector and test each indexe's state. 
	for (int i = 0, x = 0; i < lineLength; i++) {
		for (int j = 0; j < lineLength; j++) {

			if (nb[i][j].getState() == infected) {
				numInfected++;
			}
			else if (nb[i][j].getState() == vacinated) {
				numVacinated++;
			}
			else if (nb[i][j].getState() == recovered) {
				numRecovered++;
			}
			else if (nb[i][j].getState() == suceptible) {
				numSusceptible++;
			}
		}
	}

	
		cout << "Infected: " << numInfected << endl;
		cout << "Vacinated: " << numVacinated << endl;
		cout << "Recovered: " << numRecovered << endl;
		cout << "Susceptible: " << numSusceptible << endl;
		cout << "Exposed: " << numExposed << endl;
		cout << endl;
	
	//setting the number of susceptible and recovered agents equal to 0. We wont know the final number of suceptible
	//and recovered agents until the outbreak ends. 
	numSusceptible = 0;
	numRecovered = 0;
	numVacinated = 0;

	//day++;
}

void seirsSquare::outBreak() {

	while ((numInfected > 0 && numExposed > 0) || day < maxDays) {
		numInfected = 0;
		numExposed = 0;

		for (int i = 0; i < lineLength; i++) {
			a = i;
			for (int x = 0; x < lineLength; x++) {
				b = x;
				//checking each part of the square. 

				corners();
				topAndBottom();
				sides();
				if ((a > 0 && a < lineLength - 1) && (b > 0 && b < lineLength - 1)) {

					insideSquare();
				}
			}
		}
		
		_EtoI();
		_Itoi();
		//day is now over. Time to check if the infected agents will go from state i to r.
		_ItoR();
		//checking to see if there are any infected agents left.
		_RtoS();
		infectedLeft();

		if (numInfected == 0 && numExposed ==0) {
			cout << endl;
			cout << "Day " << day << endl;
			for (int x = 0; x < lineLength; x++) {
				for (int j = 0; j < lineLength; j++) {
					cout << nb[x][j].getState();
				}
				cout << endl;
			}
			cout << endl;
			cout << "Outbreak ends on day " << day << endl;
			
			break;
		}

		else if (day % display == 0) {
			cout << endl;
			cout << "Day " << day << endl;
			for (int x = 0; x < lineLength; x++) {
				for (int j = 0; j < lineLength; j++) {
					cout << nb[x][j].getState();
				}
				cout << endl;
			}
		}
		//Now time to check to see if the current day has more infected agents than previous days.
		isMaxOutbreak();
		day++;
		
	}
	cout << endl;
	if(day == maxDays)
	cout << "Outbreak ended on day " << day-1 << endl;

	status();
	cout << "The outbreak day was day " << outBreakDay << " with " << outBreakInfected << " infected agents. " << endl;
	
}

void seirsSquare::corners() {
	//The corners are a function since there are only 5 agents that can come into contact with any corner. 
	//The other side of the square that is in contact with the corner is checked.  

	if (a == 0 && b == 0) {
		topLeftCorner();
	}
	else if (a == 0 && b == lineLength - 1) {
		topRightCorner();
	}
	else if (a == lineLength - 1 && b == 0) {
		bottomLeftCorner();
	}
	else if (a == lineLength - 1 && b == lineLength - 1) {
		bottomRightCorner();
	}
}

void seirsSquare::topLeftCorner() {
	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();

	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void seirsSquare::topRightCorner() {
	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();

	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[0][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[1][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();

		}
	}

}

void seirsSquare::bottomLeftCorner() {
	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();

	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();

	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void seirsSquare::bottomRightCorner() {

	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();

	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();

	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void seirsSquare::topAndBottom() {
	//The top and bottom of the square have 5 checks, but does not check the other side of the square like the corners do. 

	if (a == 0 && (b > 0 && b < lineLength - 1)) {
		top();
	}
	else if (a == lineLength - 1 && (b > 0 && b < lineLength - 1)) {
		bottom();
	}
}

void seirsSquare::top() {

	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();

	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void seirsSquare::bottom() {

	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();
		
	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	

	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}
	}

}

void seirsSquare::sides() {
	//The sides of the square have 8 total checks. The difference between the sides and the inside of the square is 
	//the sides check the other side of the square that is in contact with the current neighborhood. 

	if (a > 0 && a < lineLength - 1 && b == 0)
		left();
	if (a > 0 && a < lineLength - 1 && b == lineLength - 1)
		right();
}

void seirsSquare::left() {

	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();
		
	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][lineLength - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}

	}
}

void seirsSquare::right() {

	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();
		
	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}

	}
}

void seirsSquare::insideSquare() {

	if (nb[a][b].getState() == 'e')
		nb[a][b].incrementExposed();

	else if (nb[a][b].getState() == 'i') 
		nb[a][b].incrementInfection();

	else if (nb[a][b].getState() == 'r')
		nb[a][b].incrementRecoveredRate();
	
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a - 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('e');
				nb[a][b].resetThreshold();
			}
			else
				nb[a][b].resetThreshold();
		}

	}
}

void seirsSquare::_ItoR() {
	//Checking to see if the infected agent's infection period is greater than or equal to the default infection period. 
	//If the nfected agent's infection period is greater than or equal to the default infection period, the state changes
	//from i to r. 

	for (int i = 0; i < lineLength; i++) {
		//a = i;
		for (int x = 0; x < lineLength; x++) {
			//b = x;
			if (nb[i][x].getState() == infected) {

				if (nb[i][x].getIncrementInfectionPeriod() >= nb[i][x].getInfectiousPeriod()) {
					nb[i][x].setState(recovered);
					nb[i][x].resetInfectiousPeriod();
				}
			}
		}
	}
}

void seirsSquare::_EtoI() {

	for (int i = 0; i < lineLength; i++) {
		//a = i;
		for (int x = 0; x < lineLength; x++) {
			//b = x;
			if (nb[i][x].getState() == exposed) {

				if (nb[i][x].getIncrementExposed() >= nb[i][x].getLatentPeriod()) {
					nb[i][x].setState(infected);
					nb[i][x].resetExposedRate();
				}
			}
		}
	}

}

void seirsSquare::_RtoS() {

	for (int i = 0; i < lineLength; i++) {
		//a = i;
		for (int x = 0; x < lineLength; x++) {
			//b = x;
			if (nb[i][x].getState() == recovered) {

				if (nb[i][x].getIncrementRecoveredRate() >= nb[i][x].getDefaultRecoveredRate()) {
					nb[i][x].setState(suceptible);
					nb[i][x].resetRecoveredRate();
				}
			}
		}
	}

}

void seirsSquare::_Itoi() {
	//We are changing I to i so that in the _ItoR function we can determine if the infected state(i) can become
	//recovered(state r).
	for (int i = 0; i < lineLength; i++) {
		a = i;
		for (int x = 0; x < lineLength; x++) {
			b = x;
			if (nb[a][b].getState() == 'I')
				nb[a][b].setState(infected);

		}
	}
}

void seirsSquare::infectedLeft() {

	for (int i = 0; i < lineLength; i++) {
		a = i;
		for (int x = 0; x < lineLength; x++) {
			b = x;
			if (nb[a][b].getState() == infected)
				numInfected++;
			else if (nb[a][b].getState() == exposed)
				numExposed++;

		}
	}
}

void seirsSquare::isMaxOutbreak() {
	//Checking to see if the current day has more infected agents than the previous day. 

	if (numInfected > outBreakInfected) {
		outBreakInfected = numInfected;
		outBreakDay = day;
	}
}