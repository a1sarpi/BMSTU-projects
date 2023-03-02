#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum class Months : unsigned int {
	jan = 1,
	feb,
	mar,
	apr,
	may,
	jun,
	jul,
	aug,
	sep,
	oct,
	nov,
	dec
};

class Date
{
private: 
	unsigned int mDay;
	unsigned int mMonth;
	unsigned int mYear;

	int daysInMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

public: 
	//Убрал деструктор
	Date();
	Date(unsigned int pYear, Months pMonth, unsigned int pDay);
	
	explicit Date(const string& pDate); //!!! Строки передаются по ссылке на константу. Исправил
	
	Date(const Date& pDate);

	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;

	bool isLeap();

	bool operator==(const Date& otherDate);
	bool operator<(const Date& otherDate);
	bool operator>(const Date& otherDate);

	Date operator+(const int pDay);
	Date operator-(const int pDay);

	unsigned int datesDifference(const Date& otherDate) const;
	
	friend ostream& operator<<(ostream& os, const Date &pDate);
};
