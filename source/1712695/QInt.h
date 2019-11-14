#pragma once
#include"Tool.h"
#include<limits>
class QInt
{
private:
	unsigned int data[4];
	void SetBit(bool *X);
public:
	QInt();
	void TwoComplement(); // đưa số về dạng bù 2
	void ScanQInt(string number,int kieuDL);
	void PrintQInt(int kieuDLinRa);
	friend void DivSupport(const QInt &M, bool *temp); // hàm hỗ trợ cho thuật toán chia bên kia
	friend void MulSupport(const QInt &M, bool *AQQ, bool flag); // hàm hỗ trợ thuật toán nhân

	// Các hàm chuyển đổi giữa các cơ số
	friend bool* DecToBin(QInt x);
	friend char* DecToHex(QInt x);
	friend string BinToDec(QInt x);
	// Toán tử gán bằng
	QInt& operator =(const QInt& X);

	// Các toán tử so sánh
	bool operator ==(const QInt& X);
	bool operator >=(const QInt& X);
	bool operator <=(const QInt& X);
	bool operator >(const QInt& X);
	bool operator <(const QInt& X);

	// Các toán tử + - * /
	const QInt operator +(const QInt &x);
	const QInt operator -(const QInt &x);
	const QInt operator *(const QInt &x);
	const QInt operator /(const QInt &x);

	// Các phép thao tác BIT
	const QInt operator &(const QInt & X);
	const QInt operator |(const QInt & X);
	const QInt operator ^(const QInt & X);
	const QInt operator ~();
	void operator >>(int i); // dịch phải i lần
	void operator <<(int i); // dịch trái i lần
	void Ror(int i); // xoay phải i lần
	void Rol(int i); // xoay trái i lần

	void WriteFile(int hesoWrite, ofstream & fileOut);
	~QInt();
};

char*BinToHex(bool *bit);
