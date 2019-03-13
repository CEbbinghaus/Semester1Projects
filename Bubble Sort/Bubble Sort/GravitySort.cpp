#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

void PrintArray(vector<int> arr) {
	string str = "";
	for (int i : arr) {
		cout << i << ", ";
	}
	cout << endl;
}

vector<int> GravitySort(vector<int> arr) {
	int max = 0;
	for (int i : arr) {
		if (i <= 0)throw "All Values must be more than 0";
		max = max < i ? i : max;
	}
	vector<int> sorting(max);	
	for (int i : arr) {
		for (int j = 0; j < i; j++) {
			sorting[j]++;
		}
	}
	int size = sorting[0];
	for (int i = 0; i < size; i++) {
		int index = sorting[0];
		if (index == 0)break;
		int cursor = 0;
		int result = 0;
		while (sorting[cursor] == index) {
			result++;
			sorting[cursor]--;
			if(cursor < max - 1)cursor++;
		}
		arr[i] = result;
	}
	return arr;
}

int main() {
	vector<int> test = {314, 23154,342, 1531, 5346, 3, 5632, 543215,324, 624, 6234,5, 432, 4, 213, 213, 523, 1, 5132, 51342, 65341, 6, 452, 6, 425, 62345, 6, 2345, 6, 4235, 6, 4256, 2546, 42};
	PrintArray(test);
	PrintArray(GravitySort(test));
	system("pause");
	return 0;
}