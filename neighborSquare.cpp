#include "neighborSquare.h"
#include "NeigborHood.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

neighborSquare::neighborSquare(string str, string str2, string str3) {
	thresHold = str;
	infectiousPeriod = str2;
	int a = str3[8] - '0'; //using ASCII to convert a character representation of a integer to a integer.
	setDisplay(a);
	//a and b help us keep track of the position in the 2d array in other functions. 
	a = 0;
	b = 0;
	day = 0;
	numInfected = 0;
}

void neighborSquare::setDisplay(int x) {
	display = x;
}

void neighborSquare::fileString(string str) {


	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',') {
			//Do nothing, which is like skipping the ","
		}
		else {
			lineString.push_back(str[i]);//adding all characters to a vector except for the coma
			
		}
		
	}

}
	

void neighborSquare::lineSize() {
	lineLength = sqrt(lineString.size());//The square root of the lineString vector will be a integer since we
	//are reading from a file that has a square of characters.
}

void neighborSquare::set2dVector() {


	int x = 0;
	for (int z = 0; z < lineLength; z++) {
		
		vector<neighbor> temp;
		for (int j = 0; j < lineLength; j++) {

			neighbor fg(thresHold, infectiousPeriod); //this object will be added to the temp vector, which is of neighbor type
			fg.setState(lineString[x]); //setting the neighbor object's state to the current character in the squareString.
			temp.push_back(fg);//adding the neighbor object to the neighbor vector
			x++;//incrementing to the next character in the lineString vector
			
		}
		nb.push_back(temp);//adding the neighbor vector (temp) to another neighbor vector, nb. This creates a 2d vector.
		
	}
	
}
void neighborSquare::setSquare() {
	cout << "Day " << day << endl;
	for (int x = 0; x < lineLength; x++) {
		for (int j = 0; j < lineLength; j++) {
			cout << nb[x][j].getState();
		}
		cout << endl;
	}
	status();
	day++;
}

void neighborSquare::status() {

	//below are the counts of the neighbor status. We traverse through the 2d vector and test each index's state. 
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
	
	if (numInfected == 0) {
		cout << "Infected: " << numInfected << endl;
		cout << "Vacinated: " << numVacinated << endl;
		cout << "Recovered: " << numRecovered << endl;
		cout << "Susceptible: " << numSusceptible << endl;
		cout << endl;
	}
	//setting the number of susceptible and recovered agents equal to 0. We wont know the final number of suceptible
	//and recovered agents until the outbreak ends. 
	numSusceptible = 0;
	numRecovered = 0;
	numVacinated = 0;
	//day++;
}

void neighborSquare::outBreak() {

	while (numInfected !=0) {
		numInfected = 0;
		//_ItoR();

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
		
		_Itoi();
		//day is now over. Time to check if the infected agents will go from state i to r.
		_ItoR();
		//checking to see if there are any infected agents left.
		infectedLeft();  
		
		if (numInfected ==0) {
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
				status();
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
	cout << "The outbreak day was day " << outBreakDay << " with " << outBreakInfected << " infected agents. " << endl;
	cout << endl;
}

void neighborSquare::corners() {
	//The corners are a function since there are only 5 agents that can come into contact with any corner. 
	//The other side of the square that is in contact with the corner is checked.  

	if(a == 0 && b == 0) {
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

void neighborSquare::topLeftCorner() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		//numInfected++;
	}
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a+1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a+1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][lineLength-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a+1][lineLength-1].getState() == 'i')
				nb[a][b].incrementThreshold();
 
			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				//We change state s to I initially to prevent a chain effect of recently changed suceptible agents. 
				//If we do not change to 'I', then a chain effect will occur that will cause incorrect output. We change
				//all 'I's to 'i' when the day is over.
				nb[a][b].setState('I');
				
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void neighborSquare::topRightCorner() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		
	}
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b -1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[0][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[1][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('I');
				
			}
			else
				nb[a][b].resetThreshold();
		
		}
	}

}

void neighborSquare::bottomLeftCorner() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		
	}

	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a-1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a -1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b+1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][lineLength-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a-1][lineLength-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('I');
				
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void neighborSquare::bottomRightCorner() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		
	}
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a-1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][0].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('I');
				
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void neighborSquare::topAndBottom() {
	//The top and bottom of the square have 5 checks, but does not check the other side of the square like the corners do. 

	if (a == 0 && (b > 0 && b < lineLength - 1)) {
		top();
	}
	else if (a == lineLength - 1 && (b > 0 && b < lineLength - 1)) {
		bottom();
	}
}

void neighborSquare::top() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		
	}
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b - 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a+1][b+1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b+1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('I');
				
			}
			else
				nb[a][b].resetThreshold();
		}
	}
}

void neighborSquare::bottom() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		//numInfected++;
	}

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
				nb[a][b].setState('I');
				//numInfected++;
			}
			else
				nb[a][b].resetThreshold();
		}
	}
	
}

void neighborSquare::sides() {
	//The sides of the square have 8 total checks. The difference between the sides and the inside of the square is 
	//the sides check the other side of the square that is in contact with the current neighborhood. 

	if (a > 0 && a < lineLength - 1 && b == 0)
		left();
	if (a > 0 && a < lineLength - 1 && b == lineLength - 1)
		right();
}

void neighborSquare::left() {
	
	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		//numInfected++;
	}
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b+1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b+1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b+1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][lineLength-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][lineLength-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][lineLength -1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('I');
				//numInfected++;
			}
			else
				nb[a][b].resetThreshold();
		}

	}
}

void neighborSquare::right() {

	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		//numInfected++;
	}
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
				nb[a][b].setState('I');
				
			}
			else
				nb[a][b].resetThreshold();
		}

	}
}

void neighborSquare::insideSquare() {


	if (nb[a][b].getState() == 'i') {
		nb[a][b].incrementInfectionPeriod();
		
	}
	else {

		if (nb[a][b].getState() == 's') {

			if (nb[a - 1][b-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a - 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a-1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b + 1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a + 1][b].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a+1][b-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b-1].getState() == 'i')
				nb[a][b].incrementThreshold();

			if (nb[a][b].getIncrementThreshold() >= nb[a][b].getThrsehold()) {
				nb[a][b].setState('I');
				//numInfected++;
			}
			else
				nb[a][b].resetThreshold();
		}

	}
}

void neighborSquare::_ItoR() {
	//Checking to see if the infected agent's infection period is greater than or equal to the default infection period. 
	//If the nfected agent's infection period is greater than or equal to the default infection period, the state changes
	//from i to r. 

	for (int i = 0; i < lineLength; i++) {
		//a = i;
		for (int x = 0; x < lineLength; x++) {
			//b = x;
			if (nb[i][x].getState() == infected) {

				if (nb[i][x].getIncrementInfectionPeriod() >= nb[i][x].getInfectiousPeriod())
					nb[i][x].setState(recovered);
			}
		}
	}
}

void neighborSquare::_Itoi() {
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

void neighborSquare::infectedLeft() {
	
	for (int i = 0; i < lineLength; i++) {
		a = i;
		for (int x = 0; x < lineLength; x++) {
			b = x;
			if (nb[a][b].getState() == infected)
				numInfected++;

		}
	}
}

void neighborSquare::isMaxOutbreak() {
	//Checking to see if the current day has more infected agents than the previous day. 

	if (numInfected > outBreakInfected) {
		outBreakInfected = numInfected;
		outBreakDay = day;
	}
}