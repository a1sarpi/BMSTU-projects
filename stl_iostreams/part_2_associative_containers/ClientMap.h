#pragma once
#include "Client.h"
#include <iostream>
#include <map>
#include <string>

class ClientMap {
private:
    map<unsigned int, Client> clientMap;

public:
    ClientMap(const string& path);
    ClientMap() = default;

    void LoadData(const string& path);

    void SearchByClientSurname(const string& surname, const string &path);
    void SearchByCoachSurname(const string& surname, const string &path);
    void SearchBySportActivity(const string &activity, const string &path);
    void SearchByStartDate(const string &date, const string &path);
    void SearchByDurationTime(bool biggerThen, unsigned int value, const string &path);

    void OutputTextTable(const string &path) const;

    void ReplaceInFile(const string &path, unsigned int id, const Client &client);

};
