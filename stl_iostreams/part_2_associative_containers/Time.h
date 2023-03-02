#pragma once
#include <string>
#include <iostream>

using namespace std;

class Time {
private:
    unsigned int Hours;
    unsigned int Minutes;

public:
    Time();
    Time(unsigned int pHours, unsigned int pMinutes);

    explicit Time(const string& pTime);

    bool operator==(const Time& otherTime) const;
    bool operator<(const Time& otherTime)  const;
    bool operator>(const Time& otherTime)  const;

    Time operator+(int pMinutes) const;

    friend ostream& operator<<(ostream& out, const Time &pTime);

};
