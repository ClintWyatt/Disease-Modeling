#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "NeigborHood.h"
#include "neighborSquare.h"
#include "seirsSquare.h"
#include "seirsNeighborHood.h"

using namespace std;

int main() {
	string fileName, line, threshold, infect, period, display, latent, recovered, maxDays;
	string garbage1, garbage2, garbage3, garbage4;
	int choice;
	
	ifstream inFile; 

		cout << "Which model would you like to use: SIRS or SEIRS? Press 1 for SIRS, 2 for SEIRS. " << endl;
		cin >> choice;

		while (choice <1 || choice >2) {
			cout << "Enter 1 for SIRS, 2 for SEIRS. " << endl;
			cin >> choice;
		}
		if (choice == 1) {

			cout << "Enter the name of a text file that can simulate a Moore neighborhood disease model. " << endl;
			cin >> fileName;
			inFile.open(fileName);

			//valadating whether the input file exists. If it doesnt exist, then the program will prompt
			//the user to enter a valid file name. The user can end the program by pressing "q".
			while (!inFile) {
				cout << fileName << " Does not exist. " << endl;
				cout << "Make sure that the file you are trying to access" <<
					" is in the same directory this program is in. " << endl;
				cout << "press 'q' to quit or enter a vaild file name " << endl;
				cin >> fileName;
				if (fileName == "q") {
					return 1;
				}
				inFile.open(fileName);
			}

			inFile >> threshold;
			inFile >> infect >> period;
			inFile >> display;
			neighborSquare ns(threshold, period, display);

			//reading each line from the input text file.
			while (getline(inFile, line)) {

				ns.fileString(line);
			}

			//sending all characters from the input file and the threshold, infectious period, and display into the
			//neighborSquare class

			cout << endl;
			ns.lineSize();
			ns.set2dVector();
			ns.setSquare();
			ns.outBreak();
		}

		else if (choice == 2) {
			cout << "Enter the name of a text file that can simulate a SEIRS disease model. " << endl;
			cin >> fileName;
			inFile.open(fileName);

			//valadating whether the input file exists. If it doesnt exist, then the program will prompt
			//the user to enter a valid file name. The user can end the program by pressing "q".
			while (!inFile) {
				cout << fileName << " Does not exist. " << endl;
				cout << "Make sure that the file you are trying to access" <<
					" is in the same directory this program is in. " << endl;
				cout << "press 'q' to quit or enter a vaild file name " << endl;
				cin >> fileName;
				if (fileName == "q") {
					return 1;
				}
				inFile.open(fileName);
			}

			inFile >> threshold;
			inFile >> garbage1 >> infect;
			inFile >> garbage2 >> latent;
			inFile >> garbage3 >> recovered;
			inFile >> display;
			inFile >> garbage4 >> maxDays;
			seirsSquare sq(threshold, infect, latent, recovered, display, maxDays);

			//reading each line from the input text file.
			while (getline(inFile, line)) {

				sq.fileString(line);
			}

			//sending all characters from the input file and the threshold, infectious period, and display into the
			//neighborSquare class

			cout << endl;
			sq.lineSize();
			sq.set2dVector();
			sq.setSquare();
			sq.outBreak();
		}

	inFile.close();
	system("pause");
	return 0;
	
}