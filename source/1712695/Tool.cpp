#include "pch.h"
#include "Tool.h"


Tool::Tool()
{
}

// hàm chia 2 số phục vụ cho việc chuyển hệ 10 thành hệ 2
string Tool::StrDiv2(string number)
{
	int index = 0;
	string ketqua;
	int temp = number[index] - '0';
	while (temp < 2)
		temp = temp * 10 + (number[++index] - '0');
	int l = number.size();
	while (l > index)
	{
		ketqua += (temp / 2) + '0';
		temp = (temp %2 )* 10 + number[++index] - '0';
	}
	if (ketqua.length()==0)
		return "0";
	return ketqua;
}

// hàm đổi số trong hệ 16 thành dãy số hệ 2
string Tool::ConvertHexLetter(char letter)
{
	string kq;
	switch (letter)
	{
	case '0':{kq = "0000"; break;}
	case '1': {kq = "0001"; break; }
	case '2': {kq = "0010"; break; }
	case '3': {kq = "0011"; break; }
	case '4': {kq = "0100"; break; }
	case '5': {kq = "0101"; break; }
	case '6': {kq = "0110"; break; }
	case '7': {kq = "0111"; break; }
	case '8': {kq = "1000"; break; }
	case '9': {kq = "1001"; break; }
	case 'A': {kq = "1010"; break; }
	case 'B': {kq = "1011"; break; }
	case 'C': {kq = "1100"; break; }
	case 'D': {kq = "1101"; break; }
	case 'E': {kq = "1110"; break; }
	case 'F': {kq = "1111"; break; }
	default:
	{kq = "0000"; break; }
	}
	return kq;
}

// Hàm đổi dãy 2 thành kí tự hệ 16
char Tool::ConvertBinToHex(string bin)
{
	int somu=0;
	char kq;
	int temp=0;
	for (int i = 3; i >= 0; i--) {
		temp += ((bin[i] - '0')*pow(2.0, double(somu)));
		somu++;
	}
	switch (temp)
	{
	case 10: {kq = 'A'; break; }
	case 11: {kq = 'B'; break; }
	case 12: {kq = 'C'; break; }
	case 13: {kq = 'D'; break; }
	case 14: {kq = 'E'; break; }
	case 15: {kq = 'F'; break; }
	default: {
		kq = temp + '0'; break; }
	}
	return kq;
}

// hàm đảo ngược dãy bit lại
unsigned int Tool::reverseBits(register unsigned int x)
{
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));

	return((x >> 16) | (x << 16));
}

// hàm nhân chuỗi cho 2
string Tool::StrMul2(string number)
{
	int carry = 0, temp;
	int n = number.size();
	string kq(n + 1, '0');
	int m = n;
	for (int i = n - 1; i >= 0; i--)
	{
		temp = (number[i] - '0')*2 + carry;
		if (temp >= 10 && i == 0)
		{
			kq[m] = (temp - 10) + '0';
			kq[m - 1] = 1+'0';
			break;
		}
		if (temp >= 10)
		{
			kq[m] = (temp - 10) + '0';
			carry = 1;
		}
		else
		{
			kq[m] = temp  + '0';
			carry = 0;
		}
		m--;
	}
	if (kq[0] == '0')
		kq.erase(0, 1);
	return kq;
}

// hàm cộng chuỗi cho 1
string Tool::AddOne(string number)
{
	int n = number.size();
	int m = n;
	int carry = 0, temp;
	string kq(n + 1, '0');
	for (int i = n-1; i >= 0; i--)
	{
		if(i==n-1)temp = (number[i] - '0') + 1;
		else temp = (number[i] - '0') + carry;
		if (temp == 10 &&i==0)
		{
			kq[0] = '1';
			kq[1] = '0';
			break;
		}
		if (temp==10)
		{
			kq[m] = '0';
			carry = 1;
		}
		else
		{
			kq[m] = temp + '0';
			carry = 0;
		}
		m--;
	}
	if (kq[0] == '0')
		kq.erase(0, 1);
	return kq;
}

Tool::~Tool()
{
}
