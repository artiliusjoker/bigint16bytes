#ifndef _LIBHOTRO_H
#define _LIBHOTRO_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <sstream>

class QFloat;
using namespace std;

int ctoi(char c) {
	return c - 48;
}

char itoc(int i) {
	return i + 48;
}
//Chia chuoi cho 2 lay nguyen
string StrDivide2(string str)
{
	string result;
	int idx = 0;
	int temp = str[idx] - '0';
	if (str.length() == 1 && temp == 1)
		return "0";
	while (temp < 2)
		temp = temp * 10 + (str[++idx] - '0');
	while (str.size() > idx)
	{
		result += (temp / 2) + '0';

		// Take next digit of number 
		temp = (temp % 2) * 10 + str[++idx] - '0';
	}
	if (result.length() == 0)
		return "0";

	return result;
}
//Nhan chuoi cho 2
string StrMulti2(string str)
{
	string result;
	int temp;
	int save = 0;
	int n = str.length();
	if (n == 0)
		return "0";
	for (int i = n - 1; i >= 0; i--)
	{
		temp = (str[i] - '0') * 2+save;
		if (temp >= 10)
		{
			result = char('0' + temp - 10) + result;
			save = 1;
		}
		else
		{
			result = char('0' + temp) + result;
			save = 0;
		}

	}
	if (save > 0)
		result = "1" + result;
	return result;
}
//chuyen chuoi so nguyen tu he 10 sang he 2
string StringInt10to2(string he10)
{
	string result = "";
	string temp = he10;
	int idx;
	if (temp == "0")
	{
		return "0";
	}
	while (temp != "0")
	{
		idx = temp.length() - 1;
		if (ctoi(temp[idx]) % 2 == 0)
			result = "0" + result;
		else
			result = "1" + result;
		temp = StrDivide2(temp);
	}
	return result;	
}
//Kiem tra xem qua trinh chuyen phan thap phan co hoan tat chua
bool test(string strtest, int l)
{
	if ((strtest[0] == '1')&&(strtest.length()>l))
	{
		for (int i = 1; i < strtest.length(); i++)
		{
			if (strtest[i] != '0')
				return false;
		}
		return true;
	}
	else return false;
}
//Chuyen chuoi float tu he 10 sang he 2
string String10to2(string he10) 
{
	string nguyen = "";
	string dau = "";
	int i = 0;
	if (he10[i] == '-')
	{
		dau = dau + '-';
		i++;
	}
	while (he10[i] != '.')
	{
		nguyen = nguyen + he10[i];
		i++;
	}
	string he2nguyen = StringInt10to2(nguyen);
	i++;
	string thapphan = "";
	while (i != he10.length())
	{
		thapphan = thapphan + he10[i];
		i++;
	}
	string he2thapphan = "";
	int count = 0;
	string temp = StrMulti2(thapphan);
	int l = thapphan.length();
	while ((!test(temp, l))&&count<=113-he2nguyen.length())
	{
		
		if (temp.length() == l)
			he2thapphan = he2thapphan + "0";
		else
		{
			he2thapphan = he2thapphan + "1";
			temp.erase(temp.begin());
		}

		temp = StrMulti2(temp);
		count++;
	}
	if (test(temp,l))
		he2thapphan = he2thapphan + "1";
	string rt= dau + he2nguyen + "." + he2thapphan;
	return rt;
}
//chuyen so nguyen kieu int sang chuoi string
string inttostring(int a)
{
	string result = "";
	int temp = a;
	while (temp!= 0)
	{
		result = char(temp % 10 + '0') + result;
		temp = temp / 10;
	}
	return result;
}
//chuyen so nguyen kieu string sang int
int stringtoint(string str)
{
	int result = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result += ctoi(str[str.length() - i - 1])*pow(10.0, double(i));
	}
	return result;
}
//chuan hoa chuoi de dua vao bo nho 128 bit
string ChuanHoa(string str)
{
	string result="";
	int i, j, exp;
	char k;
	if (str[0] == '-')
	{
		i = 1;
		j = 1;
		k = '1';
	}
	else
	{
		i = 0;
		j = 0;
		k = '0';
	}
	while ((str[i] != '1') && (i<=112))
	{
		i++;
	}
	while (str[j] != '.')
	{
		j++;
	}
	if (i > j)
		exp = 16383 + (j - i);
	else
		exp = 16383 + (j - i - 1);
	for (int l = i + 1; l < str.length(); l++)
	{
		if (str[l] != '.')
			result = result + str[l];
	}
	string expHe2;
	expHe2 = StringInt10to2(inttostring(exp));
	while (expHe2.length() < 15)
	{
		expHe2 = '0' + expHe2;
	}
	result = k + expHe2 + result;
	while (result.length() < 128)
	{
		result = result + '0';
	}
	return result;
}

#endif