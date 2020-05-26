#include "QInt.h"
#include"lib.h"
#include<iostream>

QInt::QInt()
{
	for (int i = 0; i < QInt_Size; i++)
		this->arrayBits[i] = 0;
}

QInt::~QInt()
{
}
QInt::QInt(const QInt &Q){
	for (int i = 0; i < QInt_Size; i++)
		this->arrayBits[i] = Q.arrayBits[i];
}
//--------------------Kiem tra cac gia tri dac biet--------------------
//Kiem tra QInt co phai la so 0 
bool QInt::IsZero()const{
	if (arrayBits[0] == 0 && arrayBits[1] == 0 && arrayBits[2] == 0 && arrayBits[3] == 0)
		return true;
	return false;
}
//Kiem tra QInt co phai la so 1 
bool QInt::IsOne()const{
	if (arrayBits[0] == 0 && arrayBits[1] == 0 && arrayBits[2] == 0&&arrayBits[3] == 1)
	return true;
	return false;
}
//Kiem tra QInt co phai la so am
bool QInt::SoAm()const{
	int bitdau = this->GetBit(0);
	if (bitdau == 0)
		return false;
	return true;
}
//--------------------Thao tac voi Bit --------------------------------

//Lay gia tri cua bit o vi tri n (n -> 0 -> 127)
int QInt::GetBit(int n)const{
	int byte = n / 32; 
	int sodu = 31 - n % 32;
	return (this->arrayBits[byte] >> sodu) & 1;
}
//Dat gia tri value cho bit o vi tri n
void QInt::SetBit(int n, bool value){
	int byte = n / 32;
	int sodu = 31 - n % 32;
	if (value == 0){
		this->arrayBits[byte] = this->arrayBits[byte] & (~(1 << sodu));
	}
	else{
		this->arrayBits[byte] = this->arrayBits[byte] | (1 << sodu);
	}
}

//Ham lay chieu dai chuoi bit // So am chieu dai mac dinh se la 128
int QInt::GetLength()const{
	for (int i = 0; i < 128; i++){
		if (this->GetBit(i) == 1)
			return 128 - i;
	}
	return 0;
}

//--------------------------------Nhap Xuat So QINT----------------------------------------------------------------------------
void QInt::Nhap(std::string str, int base){
	switch (base)
	{
	case 2:
		SaveBit(str);
		break;
	case 10:
		*this = this->DecToBin(str);//Chuyen he co so 10 -> 2
		break;
	case 16:
		str = this->HexToBin(str);//Chuyen he co so 16 -> 2
		SaveBit(str);
		break;
	default:
		std::cout << "\nDu lieu nhap vao khong hop le";
		break;
	}
}

std::string QInt::Xuat(int base){

	if (base == 2){
		std::string str = this->PrintBit();
		while (str.length() > 1 && str[0] == '0')
		{
			str.erase(0, 1);
		}
		return str;
	}
	else if (base == 10){
		return this->BinToDec();
	}
	else  if (base == 16){
		std::string str = this->BinToHex();
		while (str.length() > 1 && str[0] == '0')
		{
			str.erase(0, 1);
		}
		return str;
	}
	else{
		std::cout << "\nDdu lieu xuat khong hop le.";
		return NULL;
	}
}

void QInt::SaveBit(std::string bin){
	bin = DinhDang_Bi(bin);
	//Chia ra 4 chuoi co do dai 32 bit
	for (int i = 0; i < 128; i++){
		if (bin[i] == '0')
			this->SetBit(i, 0);
		else
			this->SetBit(i, 1);
	}
}
std::string QInt::PrintBit(){
	std::string ans;
	for (int i = 0; i < 128; i++){
		ans += this->GetBit(i) + 48;
	}
	return ans;
}

//--------------------------------Chuyen doi he co so----------------------------------------------------------------------------

QInt QInt::DecToBin(std::string dec){
	QInt ans;
	//Chuyen tu he co so 10 ----------> 2
	//TH1: So duong 
	if (dec[0] != '-'){
		std::string bi;
		while (dec != ""){
			Chia2(dec, bi);
		}
		//Dinh dang theo kieu dao chuoi va du 128 bit
		std::reverse(bi.begin(), bi.end());
		bi = DinhDang_Bi(bi);
		ans.Nhap(bi, 2);
	}
	else{
		//TH2: So Am 
		dec.erase(0, 1);
		ans = -DecToBin(dec);
	}
	return ans;
}
std::string QInt::HexToBin(std::string hex){
	std::string bi;
	hex = DinhDang_Hex(hex);
	std::string Hex_Bin[2][16] = {
		{ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" },
		{ "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" }
	};
	for (int i = 0; i < 32; i++){
		std::string tam;
		tam.push_back(hex[i]);
		for (int j = 0; j < 16; j++)
		{
			if (tam == Hex_Bin[0][j])
			{
				bi += Hex_Bin[1][j];
				break;
			}
		}
	}

	return bi;
}

std::string QInt::BinToHex(){
	//Lay chuoi nhi phan 
	std::string bi = this->PrintBit();
	
	std::string hex;
	std::string Hex_Bin[2][16] = {
		{ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" },
		{ "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" }
	};
	for (int i = 0; i < 32; i++){
		std::string tam;
		for (int j = 0; j < 4; j++){
			tam.push_back(bi[i * 4 + j]);
		}
		for (int j = 0; j < 16; j++)
		if (Hex_Bin[1][j] == tam)
		{
			hex += Hex_Bin[0][j];
			break;
		}
	}


	return hex;
}
std::string QInt::BinToDec(){
	//Lay chuoi nhi phan
	std::string bi = this->PrintBit();

	int len = bi.length();
	std::string dec = "0";
	if (len < 128 || bi[0] == '0'){
		//TH1: So Duong
		for (int i = 0; i < len; i++){
			dec = Nhan2(dec);
			dec = Cong(dec, bi[i]);
		}
	}
	else{
		//TH2: So Am
		QInt q = *this;
		q = -q;
		dec = q.BinToDec();
		dec.insert(0, "-");
	}
	return dec;
}

//--------------------------------Phep Toan AND OR XOR NOT----------------------------------------------------------------------
QInt QInt::operator&(const QInt& Q)const{
	QInt ans;
	for (int i = 0; i <QInt_Size; i++)
	{
		ans.arrayBits[i] = this->arrayBits[i] & Q.arrayBits[i];
	}
	return ans;
}
QInt QInt::operator|(const QInt& Q)const{
	QInt ans;
	for (int i = 0; i <QInt_Size; i++)
	{
		ans.arrayBits[i] = this->arrayBits[i] | Q.arrayBits[i];
	}
	return ans;
}
QInt QInt::operator^(const QInt& Q)const{
	QInt ans;
	for (int i = 0; i <QInt_Size; i++)
	{
		ans.arrayBits[i] = this->arrayBits[i] ^ Q.arrayBits[i];
	}
	return ans;
}
QInt QInt::operator~()const{
	QInt ans;
	for (int i = 0; i <QInt_Size; i++)
	{
		ans.arrayBits[i] = ~this->arrayBits[i];
	}
	return ans;
}
//----------------PHep dich Bit << >> -------------------------------
//Phep dich phai
QInt QInt::operator>>(int nums)const{
	
	int bitphai1 = 0;
	int bitphai2 = 0;
	QInt ans = *this;

	while (nums > 0){
		bitphai1 = (ans.arrayBits[0]) & 1;
		ans.arrayBits[0] = ans.arrayBits[0] >> 1;
		for (int i = 1; i <QInt_Size ; i++){
			//Lay Bit
			bitphai2 = (ans.arrayBits[i]) & 1;
			//Dich bit
			ans.arrayBits[i] = ans.arrayBits[i] >> 1;
			//Set bit 
			if (bitphai1 == 1){
				//TH1 : phai = 1
				ans.arrayBits[i] = (ans.arrayBits[i]) | (1 << 31);
			}
			else{
				//TH2 : bit phai = 0
				ans.arrayBits[i] = (ans.arrayBits[i]) & (~(1<<31));
			}
			bitphai1 = bitphai2;
		}
		nums--;
	}
	return ans;
}
//Phep dich trai
QInt QInt::operator<<(int nums)const{
	int bittrai1 = 0;
	int bittrai2 = 0;

	QInt ans = *this;

	while (nums > 0){
		//Lay bit trai nhat cua Int4
		bittrai1 = (ans.arrayBits[QInt_Size-1] >> 31) & 1;
		//Dich bit Int 4
		ans.arrayBits[QInt_Size - 1] = ans.arrayBits[QInt_Size - 1] << 1;

		for (int i = QInt_Size - 2; i >= 0; i--){
			//Lay bit
			bittrai2 = (ans.arrayBits[i] >> 31) & 1;
			//Dich bit
			ans.arrayBits[i] = ans.arrayBits[i] << 1;
			//Set bit 
			if (bittrai1 == 1){
				//TH1 : bit trai 1 = 1
				ans.arrayBits[i] = (ans.arrayBits[i]) | 1;
			}
			else{
				//TH2 : bit trai 1 = 0
				ans.arrayBits[i] = (ans.arrayBits[i]) & (~1);
			}
			bittrai1 = bittrai2;
		}
		nums--;
	}
	return ans;
}


//----------------Phep xoay bit ror va rol --------------------------
//Phep xoay trai
QInt QInt::rol(int nums)const{
	QInt ans = *this;
	while (nums > 0){

		//B1: lay gia tri bit trai nhat cua Int1
		int Bit = (ans.arrayBits[0] >> 31) & 1;
		// B2 : Dich trai <<
		ans = ans << 1;
		//B3 : Bit phai nhat cua Int 4 = Bit Trai nhat cua Int1
		if (Bit == 1){
			//TH1 : bit trai 1 = 1
			ans.arrayBits[QInt_Size - 1] = (ans.arrayBits[QInt_Size - 1]) | 1;
		}
		else{
			//TH2 : bit trai 1 = 0
			ans.arrayBits[QInt_Size - 1] = (ans.arrayBits[QInt_Size - 1]) & (~1);
		}
		nums--;
	}
	return ans;
}
//Phep xoay phai
QInt QInt::ror(int nums)const{
	QInt ans = *this;
	while (nums > 0){

		//B1: Lay gia tri bit phai nhat cua Int 4
		int Bit = (ans.arrayBits[QInt_Size-1]) & 1;
		// B2 : Dịch phai >>
		ans = ans >> 1;
		//B3 : Bit trai nhat cua Int 1 = bit phai nhat cua Int4
		if (Bit == 1){
			//TH1 : phai = 1
			ans.arrayBits[0] = (ans.arrayBits[0]) | (1 << 31);
		}
		else{
			//TH2 : bit phai = 0
			ans.arrayBits[0] = (ans.arrayBits[0]) & (~(1<<31));
		}

		nums--;
	}
	return ans;
}
//----------------Phep = + - * /-------------------------------------
QInt& QInt::operator=(const QInt& Q){
	for (int i = 0; i < QInt_Size; i++)
		this->arrayBits[i] = Q.arrayBits[i];
	return *this;
}

QInt QInt::operator+(const QInt& Q)const{
	QInt ans;
	int nho = 0;
	int bit1, bit2;
	int tong;
	for (int i = 127; i >= 0; i--){
		bit1 = this->GetBit(i);
		bit2 = Q.GetBit(i);
		tong = bit1 + bit2 + nho;
		if (tong == 3){
			ans.SetBit(i, 1); nho = 1;
		}
		else if (tong == 2){
			ans.SetBit(i, 0); nho = 1;
		}
		else if (tong == 1){
			ans.SetBit(i, 1); nho = 0;
		}
		else if (tong == 0){
			ans.SetBit(i, 0); nho = 0;
		}
	}
	//Kiem tra Tinh hop le
	bool Am1 = this->SoAm();
	bool Am2 = Q.SoAm();
	bool Am3 = ans.SoAm();

	if (Am1 == Am2){
		if (Am1 != Am3){
			std::cout << "\nDu lieu bi tran.";
			QInt errol; return errol;
		}
	}
	return ans;
}
QInt QInt::operator-(const QInt& Q)const{
	QInt ans = -Q;
	return *this + ans;
}
QInt QInt::operator-()const{
	QInt ans = *this;
	if (ans.IsZero() == 1)
		return ans;
	ans = ~ans;
	//Cong 1
	int flag = 0;
	for (int i = 127; i >= 0; i--)
	{
		if (ans.GetBit(i) == 0){
			ans.SetBit(i, 1);
			flag = 1;
			break;
		}
		else
		{
			ans.SetBit(i, 0);
		}
	}
	if (flag == 0)
		std::cout << "\nKhong co so am cua so nay: ";

	return ans;
}
QInt QInt::operator*(const QInt& Q)const{
	QInt ans,a1,a2;
	a1 = *this;
	a2 = Q;
	int flag = 0;
	if (a1.SoAm() == 1){
		a1 = -a1;
		flag ++;
	}
	if (a2.SoAm() == 1){
		a2 = -a2;
		flag ++;
	}
	//Kiem tra du lieu co bi tran hay khong
	int len1 = a1.GetLength();
	int len2 = a2.GetLength();
	int tong = len1 + len2 - 1;
	if (tong > 128){
		std::cout << "\nPhep nhan bi tran.";
		QInt errol; return errol;
	}


	for (int i = 127; i >= 0; i--){
		if (a1.GetBit(i) == 1)
		{
			ans = ans + a2;
		}
		a2 = a2 << 1;
	}
	if (flag == 1)
		ans = -ans;

	return ans;
}
 
QInt QInt::operator/(const QInt& Q)const{
	QInt ans, a1, a2;
//Cac TH Dac biet
	if (Q.IsZero() == 1){
		std::cout << "\nPhep toan chia khong hop le(Chia cho so 0) ";
		return ans;
	}
	if (a1 < a2)return ans;//return so 0

	a1 = *this;	a2 = Q;
	int flag = 0;
	if (a1.SoAm() == 1){
		a1 = -a1;
		flag++;
	}
	if (a2.SoAm() == 1){
		a2 = -a2;
		flag++;
	}
	//B1: Xac dinh chieu dai bit cua 2 so a1 va a2
	int flag1,flag2;//danh dau vi tri so 1 dau tien cua chuoi bit a1,a2
	flag1 = a1.GetLength();
	flag2 = a2.GetLength();
	int index = flag1 - flag2;
	QInt tam = a2 << (index);
	//B2: Xu lu phep chia
	std::string str;
	while (index>=0){
		if (a1 >= tam)
		{
			a1 = a1 - tam;
			str.push_back('1');
		}
		else{
			str.push_back('0');
		}
		index--;
		tam = tam >> 1;
	}
	ans.Nhap(str, 2);
	if (flag == 1)
		ans = -ans;
	return ans;
}

//---------------Phep toan so sanh > < = ------------------------------
bool QInt::operator>(const QInt& Q)const{
	QInt a = *this;
	QInt b = Q;
	QInt c = a - b;
	if (c.SoAm() == 1)
		return false;
	return true;

}
bool QInt::operator<(const QInt& Q)const{
	QInt a = *this;
	QInt b = Q;
	QInt c = a - b;
	if (c.SoAm() == 1)
		return true;
	return false;
}
bool QInt::operator==(const QInt& Q)const{
	QInt a = *this;
	QInt b = Q;
	QInt c = a - b;
	if (c.IsZero() == 1)
		return true;
	return false;
}
bool QInt::operator<=(const QInt& Q)const{
	return ((*this < Q) || (*this == Q));
}
bool QInt::operator>=(const QInt& Q)const{
	return (*this > Q) || (*this == Q);
}