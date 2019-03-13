#pragma once

#include <string>
#include <cmath>
#include <vector>

using namespace std;

namespace sort {
	//- Loops through the Array and returns the Highest Value
	int highest(int* arr, int size) {
		int max = 0;
		for (int i = 0; i < size; i++) {
			if (i < 0)throw "All Values must be greater or equal to 0";
			max = max < arr[i] ? arr[i] : max;
		}
		return  max;
	}

	//- Returns the Digit at the n'th position. e.g 4523, 2 will return 5;
	// this works by taking the position and raising 10 to the power of n. e.g 2 will be 100
	// it then modulo's it by the next higher exponent to cut of any excess. so 4523 will become 523.
	// Then it Divides it by the Exponent so 523 / 100. which comes to 5.23
	// Last of all floor it to get the digit 5
	int getDigit(int number, int position) {
		int exp = pow(10, position);
		return floor((number % exp * 10) / exp);
	}

	//- Sorts an array using Counting Sort.
	// References to Count sort can be found 
	// Here: https://en.wikipedia.org/wiki/Counting_sort
	// and Here: https://www.youtube.com/watch?v=7zuGmKfUt7s
	//--------------------IMPORTANT------------------------
	// This Sort Is Modified to use the N'th Digit of a Number
	// DO NOT USE FOR ANYTHING BUT RADIX SORTS
	void countSort(int* arr, int size, int digit) {
		int* previousState = arr;
		int* nextState = new int[size];
		int count[10] = {0};
		int i = 0;
		for (i = 0; i < size; i++)
			count[getDigit(previousState[i], digit)]++;

		for (i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (i = size - 1; i >= 0; i--) {
			int countIndex = getDigit(previousState[i], digit);
			int value = count[countIndex];
			nextState[value - 1] = previousState[i];
			count[countIndex]--;
		}
		memcpy(arr, nextState, size);
		delete[] nextState;
	}


	//- Sorts an Array by The Individual Digits. Does a CountSort for every Digit
	// References can be found Here: https://en.wikipedia.org/wiki/Radix_sort
	// and Here: https://en.wikipedia.org/wiki/Radix_sort
	void Radix(int* arr, int size) {

		int max = highest(arr, size);
		int count = to_string(max).length();

		for (int i = 0; i < count; i++)
			countSort(arr, size, i);
	}

	//- Overload to sort Vectors
	void Radix(vector<int>* arr) {
		Radix((*arr).data(), (*arr).size());
	}
}