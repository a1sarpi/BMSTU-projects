#include "Time.h"
#include <iomanip>

Time::Time() : Hours(0), Minutes(0)
{}

Time::Time(unsigned int pHours, unsigned int pMinutes) : Hours(pHours), Minutes(pMinutes)
{}

Time::Time(const string &pTime) {
    Hours = stoi(pTime.substr(0, 2));
    Minutes = stoi(pTime.substr(3, 2));
}

bool Time::operator==(const Time &otherTime) const {
    return (Hours   == otherTime.Hours) and
           (Minutes == otherTime.Minutes);
}

bool Time::operator<(const Time &otherTime) const {
    if (Hours < otherTime.Hours) {
        return true;
    }
    else if (Hours > otherTime.Hours) {
        return false;
    }
    else {
        if (Minutes < otherTime.Minutes) {
            return true;
        }
        else if (Minutes > otherTime.Minutes) {
            return false;
        }
    }
}

bool Time::operator>(const Time &otherTime) const {
    return !((*this == otherTime) || (*this < otherTime));
}

Time Time::operator+(int pMinutes) const {
    Time result(*this);
    result.Minutes += pMinutes;
    unsigned int i = result.Hours;
    while (result.Minutes >= 60) {
        result.Minutes -= 60;
        if (i + 1 > 24) {
            i = 0;
            result.Hours++;
        }
        i++;
    }
    return result;
}

ostream& operator<<(ostream& out, const Time &pTime)
{
    out.fill('0');
    out << setw(2) << pTime.Hours << ":"
        << setw(2) << pTime.Minutes;
    out.fill(' ');
    return out;
}

