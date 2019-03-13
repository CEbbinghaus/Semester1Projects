#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<ctime>

using namespace std;

void PrintArray(vector<int> arr, bool clear = true) {
	if(clear)system("cls");
	string str = "";
	for (int i : arr) {
		cout << i << ", ";
	}
	cout << endl;
}
void PrintArray(vector<vector<int>> arr) {
	string str = "";
	for (vector<int> i : arr) {
		PrintArray(i);
	}
}

void swap(vector<int>* a, vector<int>* b) {
	auto c = *a;
	*a = *b;
	*b = c;
}

int highest(vector<int> arr) {
	int max = 0;
	for (int i : arr) {
		if (i < 0)throw "All Values must be greater or equal to 0";
		max = max < i ? i : max;
	}
	return  max;
}

int getDigit(int number, int digit) {
	int exp = pow(10, digit);
	return floor((number % exp * 10) / exp);
}

vector<int> countSort(vector<int> arr, int digit) {
 	vector<int> result(arr);
	vector<int> count(10);
	int i = 0;
	for (i = 0; i < arr.size(); i++)
		count[getDigit(arr[i], digit)]++;

	for (i = 1; i < count.size(); i++)
		count[i] += count[i - 1];

	for (i = arr.size() - 1; i >= 0; i--) {
		int countIndex = getDigit(arr[i], digit);
		int value = count[countIndex];
		result[value - 1] = arr[i];
		count[countIndex]--;
	}
	return result;
}

vector<int> RadixSort(vector<int> arr){
	int max = highest(arr);
	int count = to_string(max).length();
	
	for (int i = 0; i < count; i++)
		arr = countSort(arr, i);
	return arr;
}

int BinarySearch(vector<int> data, int min, int max, int value) {
	int half = floor(min + (max - min) / 2);
	if ((max - min) == 1 || half == 0)return -1;
	if (data[half] == value) {
		while (data[half - 1] == value) {
			half--;
		}
		return half;
	}
	if (value < data[half]) {
		return BinarySearch(data, min, half, value);
	}
	else {
		return BinarySearch(data, half, max, value);
	}
}

int main() {
	srand(time(0));
	int size = rand();
	vector<int> data;// = { 293,425246,26,246, 345, 6, 432456,32, 6345,7546 ,4 , 4, 67432, 543, 5, 634, 4, 5346, 5,342 ,367543, 5, 34, 578546, 8, 148, 21, 656, 678, 67, 6, 3, 53, 64, 652 ,62, 5, 2, 4, 5426, 25 };
	//                { 105, 103, 104, 101, 102 }; //
	for (int i = 0; i < size; i++) {
		data.push_back(rand());
	}
	vector<int> sorted = RadixSort(data);
	cout << "Sorted Data:" << endl;
	PrintArray(data);
	bool found = false;
	system("cls");
	while (!found) {
		_sleep(2000);
		system("cls");
		cout << "Enter a Value to Search For" << endl; 
		int value = 0;
		cin >> value;
		if (cin.bad()) { cout << "Invalid Variable"; continue;}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		int index = BinarySearch(sorted, 0, sorted.size(), value);
		if (index == -1) {
			cout << "Couldnt Find that number. Try again";
		}
		else {
			found = true;
			cout << "Index of The Element is: " << index << endl;
			break;
		}
	}
	system("pause");
}