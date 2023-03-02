#include "Date.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

bool Date::isLeap()
{
    if (mYear % 4 == 0) {
        daysInMonths[1] = 29;
        return true;
    }
    else return false;
}

Date::Date() : mYear(2022), mMonth(static_cast<unsigned int>(Months::may)), mDay(15)
{
    isLeap();
}

Date::Date(unsigned int pYear, Months pMonth, unsigned int pDay)
        : mYear(pYear), mMonth(static_cast<unsigned int>(pMonth)), mDay(pDay)
{
    isLeap();
}

Date::Date(const string& pDate)
{
    isLeap();
    mYear  = stoi(pDate.substr(0, 4));
    mMonth = stoi(pDate.substr(5, 2));
    mDay   = stoi(pDate.substr(8, 2));
}

Date::Date(const Date& pDate)
{
    isLeap();
    mYear  = pDate.mYear;
    mMonth = pDate.mMonth;
    mDay   = pDate.mDay;
}

unsigned int Date::getDay() const
{
    return mDay;
}

unsigned int Date::getMonth() const
{
    return mMonth;
}

unsigned int Date::getYear() const
{
    return mYear;
}

bool Date::operator==(const Date& otherDate) const
{
    return (mYear == otherDate.mYear) &&
           (mMonth == otherDate.mMonth) &&
           (mDay == otherDate.mDay);
}

bool Date::operator<(const Date& otherDate) const
{
    if (mYear < otherDate.mYear) {
        return true;
    }
    else if (mYear > otherDate.mYear) {
        return false;
    }
    else {
        if (mMonth < otherDate.mMonth) {
            return true;
        }
        else if (mMonth > otherDate.mMonth) {
            return false;
        }
        else {
            if (mDay <= otherDate.mDay) {
                return true;
            }
            else return false;
        }
    }
}

bool Date::operator>(const Date& otherDate) const
{
    return !((*this == otherDate) || (*this < otherDate));
}

Date Date::operator+(const int pDay) const
{
    Date result(*this);
    result.mDay += pDay;
    unsigned int i = result.mMonth;
    while (result.mDay > result.daysInMonths[i - 1]) {
        result.mDay -= result.daysInMonths[i - 1];
        if (i + 1 > 12) {
            i = 0;
            result.mYear++;
            result.isLeap();
        }
        i++;
    }
    result.mMonth = i;
    return result;
}

Date Date::operator-(const int pDay) const
{
    Date result(*this);
    unsigned int temp = pDay - result.mDay;
    result.mDay = result.daysInMonths[result.mMonth - 1];
    int i = result.mMonth;
    while (temp >= result.mMonth) {
        temp -= result.daysInMonths[i - 1];
        if (i - 1 <= 0) {
            i = 12;
            result.mYear--;
            result.isLeap();
        }
    }
    result.mMonth = i;
    result.mDay -= temp - 1;
    return result;
}

unsigned int Date::datesDifference(const Date& otherDate) const
{
    int result = 0;
    result += (mDay - otherDate.mDay);
    int month = mMonth - otherDate.mMonth;
    int year = mYear - otherDate.mYear;
    if (month != 0) {
        int m = month / abs(month);
        for (unsigned int i = mMonth; i != otherDate.mMonth; i -= m) {
            result += m * daysInMonths[i - 1];
        }
    }
    if (year != 0) {
        int y = year / abs(year);
        for (unsigned int i = mYear; i != otherDate.mYear; i -= y) {
            if ((i + 1) % 4 == 0) {
                result += 366 * y;
            }
            else {
                result += 365 * y;
            }
        }
    }
    return abs(result);
}

ostream& operator<<(ostream& os, const Date &pDate)
{
    os.fill('0');
    os << setw(4) << pDate.getYear()  << "."
       << setw(2) << pDate.getMonth() << "."
       << setw(2) << pDate.getDay();
    os.fill(' ');
    return os;
}
