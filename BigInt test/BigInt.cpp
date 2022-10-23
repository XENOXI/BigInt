#include "BigInt.h"
using namespace std;

BigInt::BigInt()
{
	NUMBER = new std::vector<unsigned char>;
	neg = new bool;
	*neg = false;
}

BigInt::BigInt(int num)
{
	NUMBER = new std::vector<unsigned char>;
	neg = new bool;
	*neg = false;
	if (num < 0)
	{
		*neg = true;
		num = -num;
	}
	while (num > 0)
	{
		NUMBER->push_back(num % 256);
		num >>= 8;
	}
}

BigInt::BigInt(std::string str)
{
	vector<char> buff;
	this->NUMBER = new std::vector<unsigned char>;
	neg = new bool;
	*neg = false;
	if (str[0] == '-')
	{
		*neg = true;
		str = &str[1];
	}

	for (char c : str)
	{
		if (c < '0' || c>'9')
			throw std::invalid_argument("Invalid syntax.");
		buff.push_back(c - '0');
	}

	int supbuf = 0;
	vector<char> buff2;
	int cnt = 0;

	while (buff.size() != 0)
	{
		cnt = 0;
		supbuf = 0;
		while (supbuf < 256)
		{
			supbuf *= 10;
			supbuf += buff[cnt];
			cnt++;
			if (cnt > (int)buff.size() - 1)
				break;
		}
		for (int i = cnt; i < (int)buff.size(); i++)
		{
			buff2.push_back((supbuf >> 8));
			supbuf %= 256;
			supbuf *= 10;
			supbuf += buff[i];
			while (supbuf < 256)
			{
				buff2.push_back(0);
				i++;
				if (i > (int)buff.size() - 1)
					break;
				supbuf *= 10;
				supbuf += buff[i];
			}

		}
		if (supbuf >= 256)
		{
			buff2.push_back((supbuf >> 8));
			supbuf %= 256;
		}
		NUMBER->push_back(supbuf);
		buff = buff2;
		buff2.clear();
	}
}

BigInt::BigInt(const BigInt& sec)
{
	if (this->NUMBER == NULL)
	{
		this->NUMBER = new vector<unsigned char>;
		this->neg = new bool;
	}
	*this = sec;
}



BigInt::~BigInt()
{
	delete NUMBER;
	delete neg;
}

BigInt& BigInt::operator=(const BigInt& sec)
{
	if (&sec == this)
		return *this;
	delete this->NUMBER;
	this->NUMBER = new std::vector<unsigned char>;
	for (int i = 0; i < sec.NUMBER->size(); i++)
		NUMBER->push_back(sec.NUMBER->data()[i]);
	*neg = *sec.neg;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt BigInt::operator~() const
{
	BigInt res;
	for (unsigned char c : *NUMBER)
		res.NUMBER->push_back(c ^ 0b11111111);
	*res.neg = !*neg;
	while (res.NUMBER->data()[(int)res.NUMBER->size() - 1] == 0)
		res.NUMBER->pop_back();
	return res;
}

BigInt& BigInt::operator++()
{
	if (*neg)
	{
		*neg = false;
		--(*this);
		if (NUMBER->size() != 0)
			*neg = true;
		return *this;
	}
	int buff = 0;
	for (int i = 0; i < this->NUMBER->size(); i++)
	{
		buff = NUMBER->data()[i];
		buff += 1;
		this->NUMBER->data()[i] = buff % 256;
		if (buff < 256)
			break;
	}
	if (buff >= 256)
		NUMBER->push_back(1);
	return *this;
	// TODO: вставьте здесь оператор return
}

const BigInt BigInt::operator++(int) const
{
	BigInt res = *this;
	if (*neg)
	{
		*neg = false;
		(*this)--;
		if (NUMBER->size() != 0)
			*neg = true;
		return res;
	}	
	int buff = 0;
	for (int i = 0; i < this->NUMBER->size(); i++)
	{
		buff = NUMBER->data()[i];
		buff += 1;
		this->NUMBER->data()[i] = buff % 256;
		if (buff < 256)
			break;
	}
	if (buff >= 256)
		NUMBER->push_back(1);
	return res;
}

BigInt& BigInt::operator--()
{
	if (*neg)
	{
		*neg = false;
		++(*this);
		*neg = true;
		return *this;
	}
	if (NUMBER->size() == 1 && NUMBER->data()[0] == 0)
	{
		NUMBER->data()[0] = 1;
		*neg = true;
		return *this;
	}
	if (NUMBER->size() == 0)
	{
		NUMBER->push_back(1);
		*neg = true;
		return *this;
	}
	int buff = 0;
	--(NUMBER->data()[0]);
	for (int i = 0; NUMBER->data()[i] == 255; i++)
		--(NUMBER->data()[i + 1]);
	if (NUMBER->data()[(int)NUMBER->size() - 1] == 0)
		NUMBER->pop_back();
	
	return *this;
	// TODO: вставьте здесь оператор return
}

const BigInt BigInt::operator--(int) const
{
	BigInt res = *this;
	if (*neg)
	{
		*neg = false;
		(*this)++;
		*neg = true;
		return res;
	}
	
	if (NUMBER->size() == 1 && NUMBER->data()[0] == 0)
	{
		NUMBER->data()[0] = 1;
		*neg = true;
		return res;
	}
	if (NUMBER->size() == 0)
	{
		NUMBER->push_back(1);
		*neg = true;
		return res;
	}
	int buff = 0;
	--(NUMBER->data()[0]);
	for (int i = 0; NUMBER->data()[i] == 255; i++)
		--(NUMBER->data()[i + 1]);
	if (NUMBER->data()[(int)NUMBER->size() - 1] == 0)
		NUMBER->pop_back();
	return res;
}

BigInt& BigInt::operator+=(const BigInt& sec)
{
	*this = *this + sec;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt& BigInt::operator*=(const BigInt& sec)
{
	*this = *this * sec;
	return *this;
	// TODO: вставьте здесь оператор return
}


BigInt::operator int() const
{
	int buff = 0;
	char* arr = (char*)&buff;
	int buffsize = std::min(sizeof(int), size());
	for (int i = 0; i < buffsize; i++)
		arr[i] = NUMBER->data()[i];
	if (*neg)
		buff = -abs(buff);
	return buff;
}

BigInt::operator std::string() const
{
	int supbuf = 0;
	vector<unsigned char> res;
	vector<unsigned char> buff2;

	vector<unsigned char> buff;
	for (int i = ((int)this->NUMBER->size() - 1); i >= 0; i--)
		buff.push_back(this->NUMBER->data()[i]);

	int cnt = 0;

	while (buff.size() != 0)
	{
		cnt = 0;
		supbuf = 0;
		while (supbuf < 10)
		{
			supbuf *= 256;
			supbuf += buff[cnt];
			cnt++;
			if (cnt > (int)buff.size() - 1)
				break;
		}
		for (int i = cnt; i < (int)buff.size(); i++)
		{
			buff2.push_back((supbuf / 10));
			supbuf %= 10;
			supbuf *= 256;
			supbuf += buff[i];
			while (supbuf < 10)
			{
				buff2.push_back(0);
				i++;
				if (i > (int)buff.size() - 1)
					break;
				supbuf *= 256;
				supbuf += buff[i];
			}

		}
		if (supbuf >= 10)
		{
			buff2.push_back((supbuf / 10));
			supbuf %= 10;
		}
		res.push_back(supbuf);
		buff = buff2;
		buff2.clear();
	}
	std::string str;
	if (*neg)
		str.push_back('-');
	for (int i = ((int)res.size() - 1); i >= 0; i--)
		str.push_back(res[i] + '0');
	if ((int)res.size() == 0)
		str.push_back('0');
	return str;
}


size_t BigInt::size() const
{
	return size_t(this->NUMBER->size());
}

BigInt operator*(const BigInt& bint, const int num)
{
	BigInt res;
	int buff, sup;
	bool one = false;
	int back = 0;
	for (int j = 0; j < bint.NUMBER->size(); j++)
	{
		buff = bint.NUMBER->data()[j];
		buff *= num;
		buff += back;
		if (j > (int)res.NUMBER->size() - 1)
			res.NUMBER->push_back(buff % 256);
		else
		{
			buff = res.NUMBER->data()[j] + buff;
			res.NUMBER->data()[j] = buff % 256;
		}
		back = buff >> 8;
	}
	for (int j = bint.NUMBER->size(); back > 0; j++)
	{
		if (j > (int)res.NUMBER->size() - 1)
			res.NUMBER->push_back(buff % 256);
		else
		{
			buff = res.NUMBER->data()[j] + buff;
			res.NUMBER->data()[j] = buff % 256;
		}
		back = back >> 8;
	}
	*res.neg = *bint.neg ^ (num < 0);
	return res;
}

BigInt operator+(const BigInt& t, const BigInt& s)
{
	if (*t.neg && !*s.neg)
		return s - t;
	if (!*t.neg && *s.neg)
		return t - s;
	BigInt res, thi = t, sec = s;
	if (*t.neg && *s.neg)
		*res.neg = true;
	if (thi.size() > sec.size())
		swap(thi, sec);
	int buff;
	bool one = false;
	for (int i = 0; i < thi.NUMBER->size(); i++)
	{
		buff = thi.NUMBER->data()[i];
		buff += sec.NUMBER->data()[i];
		buff += one;
		if (buff >= 256)
		{
			one = true;
			buff %= 256;
		}
		else
			one = false;
		res.NUMBER->push_back(buff);
	}
	for (int i = thi.NUMBER->size(); i < sec.NUMBER->size(); i++)
	{
		buff = sec.NUMBER->data()[i];
		buff += one;
		if (buff >= 256)
		{
			one = true;
			buff %= 256;
		}
		else
			one = false;
		res.NUMBER->push_back(buff);
	}
	if (one)
		res.NUMBER->push_back(1);
	return res;
}

BigInt operator-(const BigInt& t, const BigInt& s)
{
	if (*s.neg && !*t.neg)
		return t + (-s);
	if (*t.neg && !*s.neg)
		return -((-t) + s);
	if (*t.neg && *s.neg)
		return ((-s) - (-t));
	if (s > t)
		return -(s - t);

	// t>=s
	BigInt res;
	int buff;
	bool one = false;
	for (int i = 0; i < s.NUMBER->size(); i++)
	{
		buff = t.NUMBER->data()[i];
		buff -= s.NUMBER->data()[i];
		buff -= one;
		if (buff < 0)
		{
			one = true;
			buff += 256;
		}
		else
			one = false;
		res.NUMBER->push_back(buff);
	}
	for (int i = s.NUMBER->size(); i < t.NUMBER->size(); i++)
	{
		buff = t.NUMBER->data()[i];
		buff -= one;
		if (buff < 0)
		{
			one = true;
			buff += 256;
		}
		else
			one = false;
		res.NUMBER->push_back(buff);
	}
	for (int i = res.NUMBER->size() - 1; i >= 0 && res.NUMBER->data()[i] == 0; i--)
		res.NUMBER->pop_back();
	return res;
}

BigInt operator*(const BigInt& t, const BigInt& s)
{
	BigInt res;
	int buff, sup;
	bool one = false;
	int back = 0;
	for (int i = 0; i < s.NUMBER->size(); i++)
	{
		for (int j = 0; j < t.NUMBER->size(); j++)
		{
			buff = t.NUMBER->data()[j];
			buff *= s.NUMBER->data()[i];
			buff += back;
			if (i + j > (int)res.NUMBER->size() - 1)
				res.NUMBER->push_back(buff % 256);
			else
			{
				buff = res.NUMBER->data()[i + j] + buff;
				res.NUMBER->data()[i + j] = buff % 256;
			}
			back = buff >> 8;
		}
		for (int j = t.NUMBER->size(); back > 0; j++)
		{
			if (j > (int)res.NUMBER->size() - 1)
				res.NUMBER->push_back(back % 256);
			else
			{
				back = res.NUMBER->data()[j] + back;
				res.NUMBER->data()[j] = back % 256;
			}
			back = back >> 8;
		}
	}
	*res.neg = *s.neg ^ *t.neg;
	return res;
}

BigInt operator/(const BigInt& t, const BigInt& sec)
{
	BigInt s;
	*s.NUMBER = *sec.NUMBER;
	BigInt buff;
	BigInt res;
	int cnt = 0;
	int sup = 0;
	while (buff < s)
	{
		buff.NUMBER->insert(buff.NUMBER->begin(), (t.NUMBER->data()[(int)t.size() - 1 - cnt]));
		cnt++;
		if (cnt > (int)t.size() - 1)
			break;
	}
	for (int i = (int)t.size() - 1 - cnt; i >= 0; i--)
	{
		sup = 0;
		while (buff >= s)
		{
			buff -= s;
			sup++;
		}
		res.NUMBER->push_back(sup);
		buff.NUMBER->insert(buff.NUMBER->begin(), (t.NUMBER->data()[i]));
		while (buff < s)
		{
			res.NUMBER->push_back(0);
			i--;
			if (i < 0)
				break;
			buff.NUMBER->insert(buff.NUMBER->begin(), (t.NUMBER->data()[i]));
		}

	}
	if (buff >= s)
	{
		sup = 0;
		while (buff >= s)
		{
			buff -= s;
			sup++;
		}
		res.NUMBER->push_back(sup);
	}
	*res.neg = *t.neg ^ *sec.neg;
	return res;
}

BigInt operator^(const BigInt& t, const BigInt& s)
{
	BigInt res;
	if (t.NUMBER->size() > s.NUMBER->size())
		return (s ^ t);
	for (int i = 0; i < t.NUMBER->size(); i++)
		res.NUMBER->push_back(t.NUMBER->data()[i] ^ s.NUMBER->data()[i]);
	for (int i = t.NUMBER->size(); i < s.NUMBER->size(); i++)
		res.NUMBER->push_back(s.NUMBER->data()[i]);
	return res;
}

BigInt operator%(const BigInt& t, const BigInt& sec)
{
	BigInt s;
	*s.NUMBER = *sec.NUMBER;
	BigInt buff;
	int cnt = 0;
	int sup = 0;
	while (buff < s)
	{
		buff.NUMBER->insert(buff.NUMBER->begin(), (t.NUMBER->data()[(int)t.size() - 1 - cnt]));
		cnt++;
		if (cnt > (int)t.size() - 1)
			break;
	}
	for (int i = (int)t.size() - 1 - cnt; i >= 0; i--)
	{
		sup = 0;
		while (buff >= s)
		{
			buff -= s;
			sup++;
		}
		buff.NUMBER->insert(buff.NUMBER->begin(), (t.NUMBER->data()[i]));
		while (buff < s)
		{
			i--;
			if (i < 0)
				break;
			buff.NUMBER->insert(buff.NUMBER->begin(), (t.NUMBER->data()[i]));
		}

	}
	if (buff >= s)
	{
		sup = 0;
		while (buff >= s)
		{
			buff -= s;
			sup++;
		}
	}
	return buff;
}

BigInt operator&(const BigInt& t, const BigInt& s)
{
	BigInt res;
	if (t.NUMBER->size() > s.NUMBER->size())
		return (s & t);
	for (int i = 0; i < t.NUMBER->size(); i++)
		res.NUMBER->push_back(t.NUMBER->data()[i] & s.NUMBER->data()[i]);
	for (int i = t.NUMBER->size(); i < s.NUMBER->size(); i++)
		res.NUMBER->push_back(s.NUMBER->data()[i]);
	return res;
}

BigInt operator|(const BigInt& t, const BigInt& s)
{
	BigInt res;
	if (t.NUMBER->size() > s.NUMBER->size())
		return (s | t);
	for (int i = 0; i < t.NUMBER->size(); i++)
		res.NUMBER->push_back(t.NUMBER->data()[i] | s.NUMBER->data()[i]);
	for (int i = t.NUMBER->size(); i < s.NUMBER->size(); i++)
		res.NUMBER->push_back(s.NUMBER->data()[i]);
	return res;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i)
{
	return (o << std::string(i));
	// TODO: вставьте здесь оператор return
}


BigInt BigInt::operator+() const
{
	return *this;
}

BigInt BigInt::operator-() const
{
	BigInt res = *this;
	*res.neg = !*res.neg;
	return res;
}

bool BigInt::operator==(const BigInt& sec) const
{
	if (size() != sec.size())
		return false;
	if (*neg != *sec.neg)
		return false;
	for (int i = 0; i < size(); i++)
		if (NUMBER->data()[i] != sec.NUMBER->data()[i])
			return false;
	return true;
}

bool BigInt::operator!=(const BigInt& sec) const
{
	return !(*this == sec);
}

bool BigInt::operator<(const BigInt& sec) const
{
	if (*neg && !*sec.neg) //
		return true;
	if (!*neg && *sec.neg)
		return false;
	if (*neg && *sec.neg)
		return !((-(*this)) < (-sec));
	if (size() < sec.size())
		return true;
	if (size() > sec.size())
		return false;
	for (int i = size() - 1; i >= 0; i--)
	{
		if (NUMBER->data()[i] > sec.NUMBER->data()[i])
			return false;
		if (NUMBER->data()[i] < sec.NUMBER->data()[i])
			return true;
	}
	return false;
}

bool BigInt::operator>(const BigInt& sec) const
{
	if (*neg && !*sec.neg) //
		return false;
	if (!*neg && *sec.neg)
		return true;
	if (*neg && *sec.neg)
		return !((-(*this)) > (-sec));
	if (size() > sec.size())
		return true;
	if (size() < sec.size())
		return false;
	for (int i = size() - 1; i >= 0; i--)
	{
		if (NUMBER->data()[i] < sec.NUMBER->data()[i])
			return false;
		if (NUMBER->data()[i] > sec.NUMBER->data()[i])
			return true;
	}
	return false;
}

bool BigInt::operator<=(const BigInt& sec) const
{

	return !(*this > sec);
}

bool BigInt::operator>=(const BigInt& s) const
{
	return !(*this < s);
}

BigInt& BigInt::operator-=(const BigInt& s)
{
	*this = *this - s;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt& BigInt::operator/=(const BigInt& sec)
{
	*this = *this / sec;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt& BigInt::operator^=(const BigInt& sec)
{
	*this = *this ^ sec;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt& BigInt::operator%=(const BigInt& sec)
{
	*this = *this % sec;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt& BigInt::operator&=(const BigInt& sec)
{
	*this = *this & sec;
	return *this;
	// TODO: вставьте здесь оператор return
}

BigInt& BigInt::operator|=(const BigInt& sec)
{
	*this = *this | sec;
	return *this;
	// TODO: вставьте здесь оператор return
}
