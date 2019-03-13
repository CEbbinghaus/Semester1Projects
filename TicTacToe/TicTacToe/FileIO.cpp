#include <iostream>
#include<fstream>


#include "FileIO.h"

using namespace std;

bool FileIO::read(stringstream& buffer) {
	ifstream fin(name, ios::in | ios::binary);
	if (fin.good()) {
		buffer << fin.rdbuf();
		fin.close();
		return true;
	}
	else
		fin.close();
	return false;
}
bool FileIO::write(stringstream& data) {
	system("cls");
	std::cout << data.str();
	//_sleep(20000);
	ofstream fout(name, ios::out | ios::binary);
	if (fout.good()) {
		fout << data.rdbuf();
		fout.close();
		return true;
	}
	else
		fout.close();
	return false;
}
bool FileIO::setSize(int size) {
	ofstream fed(name, ios::in | ios::out | ios::binary);
	if (fed.good()) {
		fed.seekp(sizeof(char[16]), ios::beg);
		fed.write((char*)&size, sizeof(size));
		return true;
	}
	else
		return false;
}