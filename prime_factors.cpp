#include <iostream>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>
#include <math.h>

using namespace std;

//Program to find the prime factors of a positive integer.
//Should work up to the maximum range of the int datatype.
//If the user enters nothing, a negative number, or anything that fails to parse to an int
//the program terminates with an error message

int main ()
{	
	while (true) {
		vector<int> primes;
		string from_user;
		cout << "Please enter an integer. ";
		getline(cin,from_user);

		int target;
		try   {
			target = boost::lexical_cast<int>(from_user);
		}
		catch( boost::bad_lexical_cast & e ){
			cout << "ERROR: Could not convert user input to integer, exiting with exception:\n"
					<< e.what() << '\n';
			return -1;
		}
		if (target < 0) {
			cout << "ERROR: Only positive integers allowed, exiting\n";
			return -1;
		}
		
		//special case for 0 and 1, no need to do all the fancy nonsense below
		if (target == 0 || target == 1) {
			cout << target << " = " << target << '\n';
			continue;
		}

		//make a copy so have the original for later
		int tmp = target;

		//first get all the 2's the target is divisible by
		//(special case for the efficiency reasons below)
		while (tmp % 2 == 0)
		{
			tmp = tmp/2;
			primes.push_back(2);
		}
		//could just iterate through all the integers, but separating out all the 2's first
		//means we get to skip all the even numbers, so this is faster.
		//Starts at 3 because we already checked 2 in the special case above.
		//iterate 2 at a time because we don't need to check numbers that are divisible by 2
		for (int i = 3; i <= sqrt(tmp); i += 2)
		{
			while (tmp % i == 0)
			{
				tmp = tmp/i;
				primes.push_back(i);
			}
		}
		// whatever's left should be a prime number (ignore it if it's just 1)
		if (tmp > 1) {
			primes.push_back(tmp);
		}

		cout << target << " = ";

		//now print the results
		int i = 0;
		int last_num = -1; //start as invalid so it doesn't match anything
		while(i < primes.size()) {

			int num = primes[i];
			int power = 1;
			//increment i and power if the next number is the same,
			//also checking to make sure we don't overrun the length of the vector
			while(i+1 < primes.size() && num == primes[i+1]) {
				power++;
				i++;
			}

			if (i+1 == primes.size()) {
				//this is the last one so don't print the * after it
				if (power > 1) {
					cout << num << '^' << power << "\n";
				}
				else {
					cout << num << "\n";
				}
			}
			else {
				if (power > 1) {
					cout << num << '^' << power << " * ";
				}
				else {
					cout << num << " * ";
				}
			}
			i++;
		}
	}
	return 0; //never gets here with the infinite loop
}
