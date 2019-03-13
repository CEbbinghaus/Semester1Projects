#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <functional>

#include "Process.h"

using namespace std;

string formatText(string text, int color = 31) {
	return "\033[1;" + to_string(color) + "m" + text + "\033[0m";
}
Process p;
int main() {
	p.init();
	return 0;
}