#include "Rational.h"
#include <stdexcept>

Rational::Rational()
	: m_numerator{0}, m_denominator{1}
{}

Rational::Rational(int n, int d)
	: m_numerator{n}, m_denominator{d}
{
	if(m_denominator == 0){
		throw std::invalid_argument("denominator=0");
	}
	int g{gcd(std::abs(n),std::abs(d))};
	if(g != 1){
		m_numerator /= g;
		m_denominator /= g;
	}
}

Rational& Rational::operator=(const Rational& a)
{
	// self-assignment guard
	if(this == &a){
		return *this;
	}

	// do the copy
	m_numerator = a.m_numerator;
	m_denominator = a.m_denominator;

	// return the existing object so we can chain this operator
	return *this;
}

Rational operator+(const Rational& a, const Rational& b)
{
	int numerator = a.get_numerator() * b.get_denominator() + a.get_denominator() * b.get_numerator();
	int denominator = a.get_denominator() * b.get_denominator();
	return Rational(numerator, denominator);
}

Rational operator-(const Rational& a, const Rational& b)
{
	int numerator = a.get_numerator() * b.get_denominator() - a.get_denominator() * b.get_numerator();
	int denominator = a.get_denominator() * b.get_denominator();
	return Rational(numerator, denominator);
}

Rational operator*(const Rational& a, const Rational& b)
{
	int numerator = a.get_numerator() * b.get_numerator();
	int denominator = a.get_denominator() * b.get_denominator();
	return Rational(numerator, denominator);
}

Rational operator/(const Rational& a, const Rational& b)
{
	if(b.get_numerator() == 0) throw std::invalid_argument("denominator=0");
	int numerator = a.get_numerator() * b.get_denominator();
	int denominator = a.get_denominator() * b.get_numerator();
	return Rational(numerator, denominator);
}

bool operator==(const Rational& a, const Rational& b)
{
	return a.get_numerator() == b.get_numerator() &&
		a.get_denominator() * b.get_denominator();
}
