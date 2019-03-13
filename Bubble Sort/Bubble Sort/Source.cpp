#include<ctime>
#include <sstream>
#include <iostream>

using namespace std;
const int Size = 10000;

void test() {
	void test1() {
	
	}
}

void fillArray(int *arr, int length)
{
 	for (int i = 0; i < length; i++)
	{
		arr[i] = (rand() % 10000);
	}
}
string arrayString(int *arr, int length)
{
	stringstream s;
	for (int i = 0; i < length; i++)
	{
		s << arr[i] << ", ";
	}
	return s.str();
}
void sortArray(int *arr, int length)
{
	int iteration = 0;
	bool wasSwapped = true;
	while (wasSwapped)
	{
		wasSwapped = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				wasSwapped = true;
				int swap = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = swap;
			}
		}
		++iteration;
	}
	cout << "Finished Sorting after " << iteration << " Iterations" << endl << endl;
		
}
int main1() {
	int values[Size];
	srand(time(0));
	fillArray(values, Size);
	cout << arrayString(values, Size) << endl;
	cout << "Sorting Array" << endl << endl << endl << endl;
	sortArray(values, Size);
	cout << arrayString(values, Size) << endl;
	system("pause");
	return 0;
}