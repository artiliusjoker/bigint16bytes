// 1712695.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include"QInt.h"
void ReadFile(string fileIn, string fileOut);

void main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cout << "Khong du arguments\n";
		return;
	}
	string IN(argv[1]);
	string OUT(argv[2]);
	string MODE(argv[3]);
	int value = stoi(MODE);
	ReadFile(IN, OUT);
}

void ReadFile(string fileIn, string fileOut)
{
	int heso1, heso2;// heso1 là hệ số nhận từ chuỗi số còn heso2 là hệ số sẽ xuất ra file Output
	string p, p2, toantu, s1;
	fstream IN;
	ofstream OUT(fileOut);
	IN.open(fileIn, ios::in);
	while (!IN.eof())
	{
		QInt A, B, AB;
		int toantuDacBiet; // số int để dịch bit << >> hoặc xoay trái xoay phải ( ror và rol)
		getline(IN, p, ' '); // lấy hệ số
		if (p == "2")heso1 = 2;
		if (p == "10")heso1 = 10;
		if (p == "16")heso1 = 16;
		getline(IN, p2, ' '); // lấy phần tiếp theo
		if (p2 == "2" || p2 == "10" || p2 == "16"|| p2 == "~")
		{
			// đây là trường hợp chuyển đổi cơ số hoặc trường hợp toán tử NOT
			getline(IN, s1, '\n');
			A.ScanQInt(s1, heso1);
			if (p2 == "~") {
				A = ~(A);
				A.WriteFile(heso1, OUT);
				continue;
			}
			if (p2 == "2")heso2 = 2;
			if (p2 == "10")heso2 = 10;
			if (p2 == "16")heso2 = 16;
			A.WriteFile(heso2, OUT);
		}
		else
		{
			heso2 = heso1;
			A.ScanQInt(p2, heso1);
			getline(IN, toantu, ' ');
			getline(IN, s1, '\n');
			if (toantu == "<<" || toantu == ">>" || toantu == "ror" || toantu == "rol")
			{
				toantuDacBiet = stoi(s1);
				if (toantu == "<<")A << toantuDacBiet;
				if (toantu == ">>")A >> toantuDacBiet;
				if (toantu == "ror")A.Ror(toantuDacBiet);
				if (toantu == "rol")A.Ror(toantuDacBiet);
				A.WriteFile(heso1, OUT);
				continue;
			}
			B.ScanQInt(s1, heso1);
			if (toantu == "+")AB = A + B;
			if (toantu == "-")AB = A - B;
			if (toantu == "*")AB = A * B;
			if (toantu == "|")AB = A | B;
			if (toantu == "/")AB = A / B;
			if (toantu == "^")AB = A ^ B;
			if (toantu == "&")AB = A & B;
			if (toantu == "^")AB = A ^ B;
			AB.WriteFile(heso1, OUT);
		}
	}
	IN.close();
	OUT.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
