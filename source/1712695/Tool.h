#pragma once
#include<string>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<fstream>
using namespace std;
class Tool
{
public:
	Tool();
	string StrDiv2(string number); // hàm chia 2 số phục vụ cho việc chuyển hệ 10 thành hệ 2
	string ConvertHexLetter(char letter); // hàm đổi số trong hệ 16 thành dãy số hệ 2
	char ConvertBinToHex(string bin); // Hàm đổi dãy 2 thành kí tự hệ 16
	unsigned int reverseBits(unsigned int x); // hàm đảo ngược dãy bit lại
	string StrMul2(string number); // hàm nhân chuỗi cho 2
	string AddOne(string number); // hàm cộng chuỗi cho 1
	~Tool();
};

