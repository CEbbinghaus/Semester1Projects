#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//Smallest Implementation of FizzBuzz
void smallFizzBuzz(int n) {

	//Declares the intergers C and I and sets them both to 0
	int c = 0, i = 0;

	//Loops Through N Iterations
	while(i < n) {

		//A bunch of Tenerary Operators Checking for every Case and couting it. Using to_string to convert from Int to String
		cout<<(i%3?(i%5?to_string(i):"buzz"):(i%5?"fizz":"fizzbuzz"))<<endl;

		// More Tenerary Operators to check if the number is Neither a Multiple of 3 or 5. If so add it to the count;
		c+=(i%3?(i%5?0:i):i);i++;

		//Writing the Total to the Console.
	}cout<<"Total Is: "<<c<<endl;
}

//Compact Implementation of Fizzbuzz
void bigFizzBuzz(int n) {
	//Initializes the int I and sets it to 0
	int i = 0;

	//Loops Through N Iterations
	while (i < n) {

		//creates a String and StringStream. the String is kept Empty but the StringStream is getting the current iteration number added to it to be transformed to a String
		string t = "";stringstream s; s << i;

		//Checks if I is a Multiple of 3 and adds Fizz to the String
		t += !(i % 3) ? "Fizz" : "";

		//Checks if I is a Multiple of 5 and adds Buzz to the String
		t += !(i % 5) ? "Buzz" : "";

		//If the string is Empty (e.g no Fizz or Buzz) it sets it to the current Iteration count
		t += t == "" ? s.str() : "";

		//Writes the current String to console
		cout << t << endl;

		//Increses Iteration Count
		i++;
	}
}

//Readable Implementation of Fizzbuzz
void biggerFizzBuzz(int n) {
	//Initializes the int I and sets it to 0
	int i = 0;
	//Loops Through N Iterations

	while (i < n) {

		//creates a String and StringStream. the String is kept Empty but the StringStream is getting the current iteration number added to it to be transformed to a String
		string t = ""; stringstream s; s << i;

		//Check if i is  a Multiple of 3. instead of using `i % 3 == 0` i use `!(i % 3 != 0)` which can be Shortened to `!(i %3)`
		if(!(i % 3))
			//If so add Fizz to the String
			t += "Fizz";

		//Check if i is  a Multiple of 5. instead of using `i % 5 == 0` i use `!(i % 5 != 0)` which can be Shortened to `!(i % 5)`
		if(!(i % 5))
			//If so add Buzz to the String
			t += "Buzz";

		//Checks if the String is Empty. this only occurs when there is neither a fizz nor buzz nor fizzbuzz
		if(t == "")
			//If so it adds the current Iteration to the string. AKA the Number e.g 5
			t += s.str();

		//Output the Current String to console.
		cout << t << endl;

		//Increase Iteration Count
		i++;
	}
}
void Menu(bool fromStart = false) {
	if(!fromStart)system("pause");
	system("CLS");
	cout << "Main Menu" << endl << endl 
	<< "1. Smallest FizzBuzz (Includes Total Count of 3's and 5's)" << endl
	<< "2. Smaller FizzBuzz" << endl
	<< "3. Small FizzBuzz" << endl
	<< "4. Exit" << endl;

	int choice = 0;
	cin >> choice;
	if (choice <= 0 || choice > 3 || cin.fail()) {
		cin.clear();
		return Menu(true);
	}
	switch (choice) {
		case 1:
			smallFizzBuzz(1000);
			break;
		case 2:
			bigFizzBuzz(1000);
			break;
		case 3:
			biggerFizzBuzz(1000);
			break;
		case 4:
			return;
		default:
			return Menu();
	}


}
int main() {
	Menu(true);
}