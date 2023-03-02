#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "Date.h"
#include "Time.h"
#include <iomanip>
#include <sstream>

using namespace std;

//!!! Для корректной работы с бинарными файлами не совсем корректно использовать string.
//!!! Нужно статический массив char[]. В первом случае в файл выводится указатель на строку, а не сами данные.

// Исправил

class Client {
private:
    char clientSurname[100];
    char coachSurname[100];
    char sportActivity[100];
    unsigned int activityID;
    Date   beginDate;
    Time   beginTime;
    unsigned int duration;
    float       rate;

public:
    Client() = default;

    Client(const string& pClientSurname, const string& pCoachSurname, const string& pSportActivity,
           unsigned int pActivityID, const Date& pBeginDate, const Time& pBeginTime,
           unsigned int pDuration, float pRate) :
           activityID(pActivityID), beginDate(pBeginDate),
           beginTime(pBeginTime), duration(pDuration), rate(pRate) {
        strncpy(clientSurname, pClientSurname.c_str(), 100);
        strncpy(coachSurname, pCoachSurname.c_str(), 100);
        strncpy(sportActivity, pSportActivity.c_str(), 100);
    }

    // Для текстового файла
    static Client FromString(const string& data) {
        stringstream stream(data);

        char pClientSurname[100];
        char pCoachSurname[100];

        char pSportActivity[100];
        unsigned int pActivityID;

        string pBeginDateSTR;
        string pBeginTimeSTR;

        unsigned int pDuration;

        float pRate;

        stream >> pClientSurname >> pCoachSurname >> pSportActivity
               >> pActivityID    >> pBeginDateSTR >> pBeginTimeSTR
               >> pDuration      >> pRate;

        Date p_begin_date(pBeginDateSTR);
        Time p_begin_time(pBeginTimeSTR);

        Client result(pClientSurname, pCoachSurname, pSportActivity,
                      pActivityID, p_begin_date, p_begin_time,
                      pDuration, pRate);


        return result;
    }

    friend ostream& operator<<(ostream &out, const Client &client)
    {
        out << "____________________________________________"						                                                       << endl
            <<	  "|Client Surname      |" << setw(21) << client.clientSurname		                                            << "|" << endl
            <<    "|Coach  Surname      |" << setw(21) << client.coachSurname	   	                                            << "|" << endl
            <<    "|Sport Activity (ID) |" << setw(21) << client.sportActivity + (" " + to_string(client.activityID))        << "|" << endl
            <<    "|Begin Date and Time |" << setw(21) << (stringstream() << client.beginDate << " " << client.beginTime).str()  << "|" << endl
            <<    "|Duration            |" << setw(21) << client.duration                                                        << "|" << endl
            <<    "|Rate                |" << setw(21) << client.rate                                                            << "|" << endl
            << "|__________________________________________|"							                                                   << endl;
        return out;
    }

    const string_view getClientSurname() const {
        return {clientSurname};
    }

    const string_view getCoachSurname() const {
        return coachSurname;
    }

    const string_view getSportActivity() const {
        return sportActivity;
    }

    unsigned int getActivityId() const {
        return activityID;
    }

    const Date &getBeginDate() const {
        return beginDate;
    }

    const Time &getBeginTime() const {
        return beginTime;
    }

    unsigned int getDuration() const {
        return duration;
    }

    float getRate() const {
        return rate;
    }

};
