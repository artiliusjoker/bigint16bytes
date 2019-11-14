#include "pch.h"
#include "QInt.h"

QInt::QInt()
{
}

// Đưa dãy bool bit vào block unsigned int data[4]
void QInt::SetBit(bool *X)
{
	for (int j = 0; j < 128; j++)
	{
		int k = j % 32;
		int m = j / 32;
		if (X[j]) data[m] |= 1UL << k; // bật bit
		else data[m] &= ~(1UL << k); // tắt bit
	}
}

// đưa số về dạng bù 2
void QInt::TwoComplement()
{
	QInt A;
	A.ScanQInt("1", 10); // cộng thêm 1
	*this = ~(*this); // Not bit
	*this = *this + A; 
}

// Hàm scan nhận QInt từ chuỗi char *
void QInt::ScanQInt(string number, int kieuDL)
{
	Tool tool;
	string hexnum,ONE = "1";
	bool temp[128], flagN = false;
	int i = 127, j = 0, n;

	n = number.size() - 1;
	switch (kieuDL)
	{
	case 2:
	{
		//vòng while này đưa chuỗi số nhị phân phân về bool temp
		while (n >= 0)
		{
			temp[i] = number[n] - '0';
			n--;
			i--;
		}
		break;
	}
	case 10:
	{
		if (number[0] == '-') {
			number.erase(0, 1);
			flagN = true;
		}
		//vòng while này đưa chuỗi số thập phân về bool temp
		while (1)
		{
			temp[i] = (number.back() - '0') % 2;
			i--;
			if (number.compare(ONE) == 0)break;
			number = tool.StrDiv2(number);
		}
		break;
	}
	case 16:
	{
		hexnum = tool.ConvertHexLetter(number[j]);
		j++;

		//vòng while này đưa chuỗi số thập lục phân về bool temp
		while (j <= n) {
			hexnum += tool.ConvertHexLetter(number[j]);
			j++;
		}

		int indexHex = hexnum.size() - 1;
		while (indexHex >= 0)
		{
			temp[i] = hexnum[indexHex] - '0';
			indexHex--;
			i--;
		}
		break;
	}
	default:
		break;
	}
	// Điền vào những số 0 phía trước cho đủ 128 bit
	for (i; i >= 0; i--)
		temp[i] = 0;

	// Nếu số nhập vào là số âm phải đưa về số bù 2
	int indexCarry = 126;
	if (flagN)
	{
		for (int h = 0; h < 128; h++)
		{
			if (temp[h])temp[h] = 0;
			else temp[h] = 1;
		}
		if (!temp[127])temp[127] = 1;
		else {
			temp[127] = 0;
			while (1) {
				if (!temp[indexCarry]) { temp[indexCarry] = 1; break; }
				temp[indexCarry] = 0;
				indexCarry--;
			}
		}
	}
	(*this).SetBit(temp);
}

// Hàm xuất QInt dưới 1 trong 3 dạng
void QInt::PrintQInt(int kieuDLinRa)
{
	bool *BIN = DecToBin(*this);
	char *HEX = BinToHex(BIN);
	string DEC = BinToDec(*this);
	string kq(HEX);
	cout << DEC;
	delete[]BIN;
	delete[]HEX;
}

// Toán tử gán bằng
QInt& QInt::operator =(const QInt& X)
{
	for (int i = 0; i < 4; i++)
		data[i] = X.data[i];
	return *this;
}

// Toán tử so sánh bằng
bool QInt::operator ==(const QInt& X)
{
	for (int i = 0; i < 4; i++)
	{
		if(X.data[i]!=data[i])
		return false;
	}
	return true;
}

// Toán tử so sánh lớn hơn bằng
bool QInt::operator >=(const QInt& X)
{
	if (*this == X)return true;
	if (*this > X)return true;
	return false;
}

// Toán tử so sánh bé hơn bằng
bool QInt::operator <=(const QInt& X)
{
	if (*this == X)return true;
	if (*this < X)return true;
	return false;
}

// Toán tử so sánh lớn hơn
bool QInt::operator >(const QInt& X)
{
	Tool tool;
	bool flag = 0;
	bool NegativeA, NegativeB;
	unsigned int tempA[4], tempB[4];

	NegativeA = (data[0] >> 0) & 1U; // bien de kiem tra 2 so am hay khong
	NegativeB = (X.data[0] >> 0) & 1U;
	if (!NegativeA && NegativeB)return true; // số A dương số X âm nên A lớn hơn k cần so sánh
	if (NegativeA && !NegativeB)return false; // số A âm số X dương nên X lớn hơn k cần so sánh

	// đảo ngược dãy bit lại so sánh cho dễ
	for (int i = 0; i < 4; i++)
	{
		tempA[i] = tool.reverseBits(data[i]);
		tempB[i] = tool.reverseBits(X.data[i]);
	}

	// bắt đầu so sánh 2 số
	for (int i = 0; i < 4; i++)
	{
		if (tempA[i] < tempB[i])return false;
		if (tempA[i] > tempB[i])return true;
	}
	return false;
}

// Toán tử so sánh A nhỏ hơn B
bool QInt::operator <(const QInt& X)
{
	Tool tool;
	bool flag = 0;
	bool NegativeA, NegativeB;
	unsigned int tempA[4], tempB[4];

	NegativeA = (data[0] >> 0) & 1U; // bien de kiem tra 2 so am hay khong
	NegativeB = (X.data[0] >> 0) & 1U;
	if (!NegativeA && NegativeB)return false; // số A dương số X âm nên X nhỏ hơn k cần so sánh
	if (NegativeA && !NegativeB)return true; // số A âm số X dương nên X lớn hơn k cần so sánh

	// đảo ngược dãy bit lại so sánh cho dễ
	for (int i = 0; i < 4; i++)
	{
		tempA[i] = tool.reverseBits(data[i]);
		tempB[i] = tool.reverseBits(X.data[i]);
	}

	// bắt đầu so sánh 2 số
	for (int i = 0; i < 4; i++)
	{
		if (tempA[i] > tempB[i])return false;
		if (tempA[i] < tempB[i])return true;
	}
	return false;
}

// Toán tử phép tính +
const QInt QInt::operator +(const QInt &x)
{
	QInt kq;
	bool *A = DecToBin(*this); bool ketqua[128]; bool *B = DecToBin(x); // Chuyển các số thành mảng bool rồi tính
	int i = 127, j = 127, k = 127; // chỉ số index của 2 số A và B và mảng kết quả
	int temp=0; // biến tạm để cộng
	while (i >= 0 || j >= 0 || temp == 1)
	{
		temp += A[i];
		temp +=B[j];
		ketqua[k] = temp % 2 ;
		temp/= 2;
		if (k == 0) break; // chống overload
		i--; j--; k--;
	}
	kq.SetBit(ketqua);
	delete[]A;
	delete[]B;
	return kq;
}

// Toán tử phép tính - , đưa x về bù 2 rồi thực hiện phép cộng
const QInt QInt::operator -(const QInt &x) 
{
	QInt kq, B = x;
	B.TwoComplement();
	kq = (*this) + B;
	return kq;
}

// Toán tử phép tính * (theo thuật toán nhân cải tiến trong file lí thuyết )
const QInt QInt::operator *(const QInt &x) 
{
	Tool tool;
	int k = 0;
	QInt kq, hold;
	bool temp[257]; 
	bool *ketqua = new bool[128];
	bool *Q = DecToBin(x);
	// tạo thanh ghi AQQ(-1) gồm 128*2+1 phần tử (257)
	// vòng for tạo phần A chỉ có số 0
	for (int i = 0; i < 128; i++)
		temp[i] = 0;
	// vòng for tạo phần Q trong thanh ghi
	for (int i = 128; i < 256; i++)
	{
		temp[i] = Q[k];
		k++;
	}
	// phần Q(-1) là số 0 thôi
	temp[256] = 0;
	//xong phần khởi tạo thanh ghi temp gồm AQQ(-1)
	k = 128;
	// bắt đầu chạy thuật toán
	while (k>0)
	{
		// 2 bit cuối là 10 thì A-M -> A
		if (temp[255] && !temp[256])
			MulSupport(*this, temp, 1);
		else
		{
			// 2 bit cuối là 01 thì A+M -> A
			if (!temp[255] && temp[256])
				MulSupport(*this, temp, 0);
			// còn 00 và 11 thì ko làm gì chỉ shift phải temp
		}
		// shift phải thanh ghi temp
		int temp1, temp2;
		temp1 = temp[256];
		for (int i = 0; i < 257; i++) {
			temp2 = temp[i];
			temp[i] = temp1;
			temp1 = temp2;
		}
		if (temp[1])temp[0] = 1; else temp[0] = 0; // bit đầu sau khi shift phải giữ bit đánh dấu
		k--;
	}
	int index = 0;
	// nhân xong rồi đưa kq vào biến kq thôi
	for (int i = 128; i < 256; i++) 
	{
		ketqua[index] = temp[i];
		index++;
	}
	kq.SetBit(ketqua); // đưa vào lưu trữ kq sau khi nhân
	delete[]ketqua;
	delete[]Q;
	return kq;
}

// Toán tử phép tính /
const QInt QInt::operator /(const QInt &x) 
{
	Tool tool;
	int k = 1;
	QInt kq;
	bool temp[256], check;
	bool *Q = DecToBin(*this);
	bool *ketqua = new bool[128];
	check = (data[0] >> 0) & 1U;
	if (check)k = 1;else k = 0; // A có 2 trường hợp phụ thuộc vào dấu của Q
	// khởi tạo A trong thanh ghi temp gồm [A,Q]
	for (int i = 0; i < 128; i++)
		temp[i] = k;
	k = 0;
	// Khởi tạo Q trong thanh ghi temp gồm [A,Q]
	for (int i = 128; i < 256; i++) {
		temp[i] = Q[k];
		k++;
	}
	k = 128;
	// bắt đầu thuật toán
	while (k>0)
	{
		// shift trái thanh ghi temp
		int temp1, temp2;
		temp1 = temp[0];
		for (int i = 255; i >=0; i--) {
			temp2 = temp[i];
			temp[i] = temp1;
			temp1 = temp2;
		}
		temp[255] = 0; // shift trái thêm 0
		// bước quan trọng :
		DivSupport(x, temp);
		// A – M -> A
		// Nếu A < 0 : Q0 = 0 và A + M -> A
		// Ngược lại : Q0 = 1. Những bước này được thực hiện trong hàm DivSupport 
		k--;
	}
	k = 0;
	// Chia xong chép kết quả vào thôi rồi return
	for (int i = 128; i < 256; i++)
	{
		ketqua[k] = temp[i];
		k++;
	}
	kq.SetBit(ketqua);
	delete[]Q;
	return kq;
}

// Toán tử AND
const QInt QInt::operator &(const QInt & X)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = data[i] & X.data[i];
	return kq;
}

// Toán tử OR
const QInt QInt::operator |(const QInt & X) 
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = data[i] | X.data[i];
	return kq;
}

// Toán tử XOR
const QInt QInt::operator ^(const QInt & X) 
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = data[i] ^ X.data[i];
	return kq;
}

// Toán tử NOT
const QInt QInt::operator ~() 
{
	QInt kq;
	for (int i = 0; i < 4; i++)
		kq.data[i] = ~data[i];
	return kq;
}

// dịch phải i lần
void QInt::operator >>(int i)
{
	bool *temp = DecToBin(*this);	
	// shift phải
	for (int k = 0; k < i; k++)
	{
		int temp1, temp2;
		temp1 = temp[127];
		for (int j = 0; j <128; j++) {
			temp2 = temp[j];
			temp[j] = temp1;
			temp1 = temp2;
		}
		if (temp[1])temp[0] = 1; else temp[0] = 0; // bit đầu sau khi shift phải giữ bit đánh dấu
	}
	SetBit(temp);
}

// dịch trái i lần
void QInt::operator <<(int i)
{
	bool *temp = DecToBin(*this);
	// shift trái
	for (int k = 0; k < i; k++)
	{
		int temp1, temp2;
		temp1 = temp[127];
		for (int j = 127; j >= 0; j--) {
			temp2 = temp[j];
			temp[j] = temp1;
			temp1 = temp2;
		}
		temp[127] = 0; // shift trái thêm 0
	}
	SetBit(temp);
}

// xoay phải i lần
void QInt::Ror(int i)
{
	bool *temp = DecToBin(*this);
	// shift phải
	for (int k = 0; k < i; k++)
	{
		int temp1, temp2, temp3 = temp[127];
		temp1 = temp[127];
		for (int j = 0; j < 128; j++) {
			temp2 = temp[j];
			temp[j] = temp1;
			temp1 = temp2;
		}
		temp[0] = temp3;
	}
	SetBit(temp);
}

// xoay trái i lần
void QInt::Rol(int i)
{
	bool *temp = DecToBin(*this);
	// shift trái
	for (int k = 0; k < i; k++)
	{
		int temp1, temp2, temp3=temp[0];
		temp1 = temp[127];
		for (int j = 127; j >= 0; j--) {
			temp2 = temp[j];
			temp[j] = temp1;
			temp1 = temp2;
		}
		temp[127] = temp3; // bit trái nhất thành bit phải nhất
	}
	SetBit(temp);
}

QInt::~QInt()
{
}

// hàm hỗ trợ chia
void DivSupport(const QInt&M, bool *temp)
{
	int i = 127, j = 127,k=127, hold = 0;
	QInt tempM = M;
	tempM.TwoComplement();
	bool kq[128], *boolM = DecToBin(tempM);
	while (i >= 0 || j >= 0 || hold == 1)
	{
		hold +=boolM[i];
		hold +=temp[j] ;
		kq[k] = hold % 2;
		hold /= 2;
		if (k == 0) break; // chống overload
		i--; j--; k--;
	}
	if (kq[0])temp[255] = 0;
	else
	{
		for (int h = 0; h < 128; h++)
			temp[h] = kq[h];
		temp[255] = 1;
	}
	delete[]boolM;
}

// hàm hỗ trợ nhân
void MulSupport(const QInt &M, bool *AQQ, bool flag)
{
	bool *boolM;
	QInt tempM = M;
	int i = 127, j = 127, k = 127, temp = 0;
	if (flag) tempM.TwoComplement();
	boolM = DecToBin(tempM);
	while (i >= 0 || j >= 0 || temp == 1)
	{
		temp += boolM[i] ;
		temp += AQQ[j];
		AQQ[k] = temp % 2;
		temp /= 2;
		if (k == 0) break; // chống overload
		i--; j--; k--;
	}
	delete[]boolM;
}


//Cac ham chuyen doi giữa các hệ số

// Hệ 2 thành chuỗi hệ 6
char*BinToHex(bool *bit)
{
	Tool tool;
	int index = 0,count = 0;
	char hold; char* kq;
	string tempS;
	while (1)
	{
		if (bit[index]) break;
		if (index == 127)break;
		index++;
		count++;
	}
	index = 127;
	count--;
	while (1)
	{
		if (index ==count)break;
		string temp(4, '0');
		for (int i = 3; i >=0; i--)
		{
			if (index == count)break;
			temp[i] = (bit[index]+'0');
			index--;
		}
		hold = tool.ConvertBinToHex(temp);
		tempS.push_back(hold);
	}
	count = tempS.size();
	kq = new char[count+1];
	for (int i = 0; i < count; i++)
		kq[i] = tempS[count - i-1];
	kq[count] = '\0';
	return kq;
}

// Hệ 10 thành chuỗi bit hệ 2
bool* DecToBin(QInt x)
{
	bool *kq = new bool[128];
	bool flag;
	int i = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 32; k++)
		{
			flag = (x.data[j] >> k) & 1U;
			if (flag)kq[i] = 1; else kq[i] = 0;
			if (i == 127)break;
			i++;
		}
	}
	return kq;
}

// Hệ 2 thành chuỗi hệ 10
string BinToDec(QInt x)
{
	QInt t = x;
	int check = -1, flag = 0;
	Tool tool;
	string kq = "0";
	bool negative = (t.data[0] >> 0) & 1U;
	if (negative)
	{
		t.TwoComplement();
		flag = 1;
	}
	bool *bit = DecToBin(t);
	for (int i = 0; i < 128; i++)
	{
		if (bit[i])
		{
				check = i;
				break;
		}
	}
	if (check == -1)
	{
		kq = "0";
		return kq;
	}
	for (int i = check; i < 128; i++)
	{
		kq = tool.StrMul2(kq);
		if (bit[i]) kq = tool.AddOne(kq);
	}
	delete[]bit;
	if (flag)
		kq = "-" + kq;
	return kq;
}

// Hệ 10 thành chuỗi hệ 16
char* DecToHex(QInt x)
{
	bool *BIN = DecToBin(x);
	char *HEX = BinToHex(BIN);
	delete[]BIN;
	return HEX;
}

// hàm ghi số QInt kết quả lên fileOut
void QInt::WriteFile(int hesoWrite, ofstream & fileOut)
{
	bool *BIN = DecToBin(*this);
	char *HEX = BinToHex(BIN);
	string DEC = BinToDec(*this); // chuỗi thập phân ra màn hình hoặc file
	string HexOut(HEX); // Chuỗi hex ra màn hình hoặc file
	switch (hesoWrite)
	{
	case 2:
	{
		int temp=0;
		string BINOUT;
		for (int i = 0; i < 128; i++) {
			if (BIN[i])break;
			temp++;
		}
		if (temp == 127)BINOUT = "0";
		for (int i = temp; i < 128; i++) {
			if (BIN[i])BINOUT = BINOUT + '1';
			else BINOUT = BINOUT + '0';
		}
		fileOut << BINOUT << endl;
		break;
	}
	case 10: 
	{
		fileOut << DEC << endl;
		break;
	}
	case 16: {
		fileOut << HexOut << endl;
		break;
	}
	default:
		break;
	}
	delete[]BIN;
	delete[]HEX;
}