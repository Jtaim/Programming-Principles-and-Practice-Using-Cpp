#pragma once

class Rational
{
public:
	Rational();
	Rational(int n, int d);

	//operator overload functions
	Rational& operator=(const Rational& a);

	//implicit conversion
	operator double() const { return static_cast<double>(m_numerator) / m_denominator; }

	//Helper functions getters
	int get_numerator() const { return m_numerator; }
	int get_denominator() const { return m_denominator; }

private:
	int m_numerator;
	int m_denominator;
	int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
};

//operator overload functions
Rational operator+(const Rational& a, const Rational& b);
Rational operator-(const Rational& a, const Rational& b);
Rational operator*(const Rational& a, const Rational& b);
Rational operator/(const Rational& a, const Rational& b);
bool operator==(const Rational& a, const Rational& b);


