#include<iostream>
#include<string>
#include <vector>
#include<sstream>
#include<fstream>
#include <Windows.h>

using namespace std;

class WS {
public:
	WS() {}
	WS &&addField(string s) {
		return move(*this);
	}
};

int main() {
	cout << ("world" > "hello") << endl;
	//cout << "\033[1;31m[textgoeshere]\033[0m" << endl;
	system("pause");
	return 0;
}

/*
	HKEY key;
	if (RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\"), &key) != ERROR_SUCCESS)
	{
			cout << "Unable to open registry key";
	}
	if (RegSetValueEx(key, TEXT("Wallpaper"), 0, REG_SZ, (LPBYTE)"1", strlen("1") * sizeof(char)) != ERROR_SUCCESS)
	{
		RegCloseKey(key);
		cout << "Unable to set registry value value_name";
	}
	else
	{
		cout << "value_name was set" << endl;
		RegCloseKey(key);
	}
*/

/*
	vector<int> b = { 1, 2, 3, 4, 5 };

	int arr[5];
	memcpy(arr, b.data(), sizeof(int) * 5);

	for (int i = 0; i < 5; ++i)
	{
		cout << arr[i] << endl;
	}
*/