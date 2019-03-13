#pragma once

#include <vector>
#include <string>
#include <functional>

using namespace std;

namespace BetterSort {

	static int getDigit(int number, int position) {
		int exp = pow(10, position);
		return floor((number % exp * 10) / exp);
	}

	template<class T>
	static int highest(T* arr, int size, function<int(T element)> functor) {
		int max = 0;
		for (int i = 0; i < size; i++) {
			int value = functor(arr[i]);
			max = ((max < value) ? value : max);
		}
		return  max;
	}
	
	template<class T>
	static void countSort(T* arr, int size, int digit, function<int(T element)> functor) {
		T* previousState = arr;
		T* nextState = new T[size];
		int count[10] = { 0 };
		int i = 0;
		for (i = 0; i < size; i++)
			count[getDigit(functor(previousState[i]), digit)]++;

		for (i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (i = size - 1; i >= 0; i--) {
			int countIndex = getDigit(functor(previousState[i]), digit);
			int value = count[countIndex];
			nextState[value - 1] = previousState[i];
			count[countIndex]--;
		}
		memcpy(arr, nextState, size);
		delete[] nextState;
	}

	template<class T>
	static void sort(T* arr, int size, function<int(T element)> functor) {
		int max = highest<T>(arr, size, functor);
		int count = to_string(max).length();

		for (int i = 0; i < count; i++)
			countSort<T>(arr, size, i, functor);
	}
}