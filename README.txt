To run, make sure you are in a command line interface and have C++14 installed onto your device. The following program 
simulates disease modeling and how diseases spread throughout a neighborhood. There are 4 states that
each neighborhood can have:
1. suceptible (s)
2. exposed (e)
3. infected (i)
4. vacinated (v)
5. recovered (r)

The other input files have instructions below:
Threshold:
Infectious Period:
Latent Period:
Recovered Period:
Display:
Max Days:

The infectious period describes how long a neighborhood will be infected. Latent period explains 
how long a neighborhood will in the exposed state. The threshold describes how many adjacent neighbors need
to be infected for one neighborhood to be exposed. The recovered period is how many days a neighborhood is 
recovered. All of the neighborhoods are in a 2d array and will appear as a square.

Follow the instructions below to run the program. 
1. To compile the program, type g++ -std=c++14 *.cpp
2. To run the program, type ./a.out
