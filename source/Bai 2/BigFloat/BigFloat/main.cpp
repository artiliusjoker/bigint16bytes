#include <iostream>
#include"libhotro.h"
#include"QFloat.h"
#include<ctime>
#include<bitset>
using namespace std;

int main(int Index, char* arg[]) {
	int count = 0; // counting number of lines in file
	bool check; // for isoperator func
	string* filestring = new string[300]; // array of lines in file

	//storing calculation
	string** StoringCalc = new string*[200];
	for (int i = 0; i < 200; i++)
	{
		StoringCalc[i] = new string[256];
	}
	//storing result
	string* StoringRes = new string[200];


	try
	{
		if (Index > 1)
		{
			ReadDataFromFile(arg[1], filestring, count);
		}
		else
		{
			ReadDataFromFile("QFloat_input.tx.txt", filestring, count);
		}

	}
	catch (string e)
	{
		cout << e;
		return 0;
	}
	for (int i = 0; i < count; i++)
	{
		check = ConvertOrInput(filestring[i]);
		if (check == true)
		{
			QFloat temp;
			int j = 0;
			int he = 0;
			string data = "";
			while ((j < filestring[i].length())&&(filestring[i][j]!=' '))
			{
				he += ctoi(filestring[i][j])*pow(10.0,double(j));
				j++;
			}
			j++;
			while (j < filestring[i].length())
			{
				data += filestring[i][j];
				j++;
			}
			temp.nhap(data, int(he));
			StoringRes[i] = temp.xuatBit();
		}
		else
		{
			string heChuyenDoi="", heCanChuyenDoiSang="";
			int j = 0, k = 0, hechuyendoi, hecanchuyendoisang;
			string data;
			QFloat temp;
			while ((j < filestring[i].length()) && (filestring[i][j] != ' '))
			{
				heChuyenDoi += filestring[i][j];
				j++;
			}
			hechuyendoi = stringtoint(heChuyenDoi);
			j++;
			k = 0;
			while ((j < filestring[i].length()) && (filestring[i][j] != ' '))
			{
				heCanChuyenDoiSang += filestring[i][j];
				j++;
			}
			hecanchuyendoisang = stringtoint(heCanChuyenDoiSang);
			j++;
			while (j < filestring[i].length())
			{
				data += filestring[i][j];
				j++;
			}
			if (hechuyendoi == 10 && hecanchuyendoisang == 2)
			{
				temp.nhap(data, 10);
				StoringRes[i] = temp.xuat(2);
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		cout << StoringRes[i] << endl;
	}
	if (Index == 3)
	{
		ofstream mFile(arg[2]);
		for (int i = 0; i < count; i++)
		{
			mFile << StoringRes[i] << endl;
		}
		mFile.close();
	}
	else
	{
		ofstream mFile("QFloat_output.tx.txt");
		for (int i = 0; i < count; i++)
		{
			mFile << StoringRes[i] << endl;
		}
		mFile.close();
	}
	//reading

	return 0;
}