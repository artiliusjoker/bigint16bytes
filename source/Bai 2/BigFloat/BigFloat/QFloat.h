#ifndef _QFLOAT_H
#define _QFLOAT_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <sstream>
#include<cmath>
#include"libhotro.h"

using namespace std;
class QFloat
{
	bitset<128> _bit; //16 byte
public:
	QFloat(string sBit)
	{
		bitset<128> bit(sBit);
		_bit = bit;
	}
	QFloat()
	{
		this->_bit = NULL;
	}
	~QFloat(){}
	//Ham doc du lieu tu file
	void rDataFromFile(string name, int& he, string& data)
	{
		ifstream read(name);
		read >> he;
		read >> data;
		read.close();
	}
	//Ham nhap tu chuoi co the chon he 2 hoac 10, mac dinh he 2
	void nhap(string chuoiData, int he = 2)
	{
		if (he == 2)
		{
			string s = ChuanHoa(chuoiData);
			bitset<128> bit(s);
			this->_bit = bit;
		}
		else if (he == 10)
		{
			string s = ChuanHoa(String10to2(chuoiData));
			bitset<128> bit(s);
			this->_bit = bit;
		}
	}
	//Ham xuat QFloat o dang he 2 hoac 10, mac dinh he 2
	string xuat(int he = 2)
	{
		if (he == 2)
		{
			string bit = this->_bit.to_string();
			return bit;
		}
	}
	string xuatBit()
	{
		string bit = this->_bit.to_string();
		return bit;
	}
};
void docFileInPut(string tenFile) {

}

void xuatFileKQ(string tenFile) {

}

void ReadDataFromFile(string filename, string* strref, int& count)
{
	char* temp = new char[256];
	count = 0;
	ifstream mFile(filename);
	if (!mFile.is_open())
	{
		throw string("File input khong ton tai, xin kiem tra lai ten \n");
		mFile.close();
	}
	else
	{
		while (mFile.getline(temp, 256))
		{
			strref[count].assign(temp); //convert char* to string
			count++;
		}
		mFile.close();
	}
	//getting all lines
}
//kiem tra thao tac can thuc hien tu chuoi du lieu trong file. Tra ve true neu nhap, false neu chuyen duoi he
bool ConvertOrInput(string needCheck)
{
	int count = 0;
	for (int i = 0; i < needCheck.length(); i++)
	{
		if (needCheck[i] == ' ')
			count++;
	}
	if (count == 1)
		return true;
	else
		return false;
}

#endif