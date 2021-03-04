#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

class LongDouble {
	const size_t divDigits = 1000;
	const size_t sqrtDigits = 100;

	int sign;
	std::vector<int> digits;
	long exponent;

	void initFromString(const std::string& s);
	void removeZeroes();
	void normalize();

public:
	LongDouble();
	LongDouble(const LongDouble& x);
	LongDouble(long double value);
	LongDouble(const std::string& s);

	LongDouble& operator=(const LongDouble& x);

	bool operator>(const LongDouble& x) const;
	bool operator<(const LongDouble& x) const;
	bool operator>=(const LongDouble& x) const;
	bool operator<=(const LongDouble& x) const;
	bool operator==(const LongDouble& x) const;
	bool operator!=(const LongDouble& x) const;

	LongDouble operator-() const;

	LongDouble operator+(const LongDouble& x) const;
	LongDouble operator-(const LongDouble& x) const;
	LongDouble operator*(const LongDouble& x) const;
	LongDouble operator/(const LongDouble& x) const;

	LongDouble& operator+=(const LongDouble& x);
	LongDouble& operator-=(const LongDouble& x);
	LongDouble& operator*=(const LongDouble& x);
	LongDouble& operator/=(const LongDouble& x);

	LongDouble operator++(int);
	LongDouble operator--(int);

	LongDouble& operator++();
	LongDouble& operator--();

	LongDouble inverse() const;
	LongDouble sqrt() const;
	LongDouble pow(const LongDouble& n) const;
	LongDouble abs() const;

	bool isInteger() const;
	bool isEven() const;
	bool isOdd() const;
	bool isZero() const;


	int getSign() const;
	long getExponent() const;
	std::vector<int> getDigits() const;
	void setSign(int x);
	void setExponent(int x);
	void setDigits(int* x, int size);


	friend std::ostream& operator<<(std::ostream& os, const LongDouble& value);
};