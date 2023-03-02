#include "ClientMap.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "Date.h"

using namespace std;

ClientMap::ClientMap(const string &path) {
    ifstream file(path, ios::binary);
    if (file.is_open()) {
        Client client;
        unsigned int i = 0;
        while (file.read(reinterpret_cast<char *>(&client), sizeof(client))) {
            clientMap.insert({i++, client});
            cout << (i + 1) << ") " << endl << client << endl;
        }
    } else cout << "part_2_associative_containers/ClientMap.cpp:12" << endl;
}

// Для текстового файла
void ClientMap::LoadData(const string &path) {
    ifstream file(path);
    if (file.is_open()) {
        unsigned int i = 0;
        while (!file.eof()) {
            string line;
            getline(file, line);
            clientMap.insert({i++, Client::FromString(line)});
            cout << i << ") " << endl << Client::FromString(line) << endl;
        }
    } else cout << "part_2_associative_containers/ClientMap.cpp:25" << endl;
}

//!!! А где, собственно, алгоритмы во всех методах ниже? Исправил.


void ClientMap::SearchByClientSurname(const string &surname, const string &path) {
    ofstream file_output(path, ios::binary);
    if (file_output.is_open()) {
//        for (auto &client: clientMap) {
//            if (client.second.getClientSurname() == surname) {
//                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
//                cout << client.first << ") " << endl << client.second << endl;
//            }
//        }
        for_each(clientMap.begin(), clientMap.end(), [&] (auto &client) {
            if (client.second.getClientSurname() == surname) {
                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
                cout << client.first << ") " << endl << client.second << endl;
            }
        });
    } else cout << "part_2_associative_containers/ClientMap.cpp:38" << endl;
}

void ClientMap::SearchByCoachSurname(const string &surname, const string &path) {
    ofstream file_output(path, ios::binary);
    if (file_output.is_open()) {
//        for (auto &client: clientMap) {
//            if (client.second.getCoachSurname() == surname) {
//                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
//                cout << client.first << ") " << endl << client.second << endl;
//            }
//        }
        for_each(clientMap.begin(), clientMap.end(), [&] (auto &client) {
            if (client.second.getCoachSurname() == surname) {
                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
                cout << client.first << ") " << endl << client.second << endl;
            }
        });
    } else cout << "part_2_associative_containers/ClientMap.cpp:56" << endl;
}

void ClientMap::SearchBySportActivity(const string &activity, const string &path) {
    ofstream file_output(path, ios::binary);
    if (file_output.is_open()) {
//        for (auto &client: clientMap) {
//            if (client.second.getSportActivity() == activity) {
//                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
//                cout << client.first << ") " << endl << client.second << endl;
//            }
//        }
        for_each(clientMap.begin(), clientMap.end(), [&] (auto &client) {
            if (client.second.getSportActivity() == activity) {
                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
                cout << client.first << ") " << endl << client.second << endl;
            }
        });
    } else cout << "part_2_associative_containers/ClientMap.cpp:74" << endl;
}

void ClientMap::SearchByStartDate(const string &dateSTR, const string &path) {
    ofstream file_output(path, ios::binary);
    if (file_output.is_open()) {
//        for (auto &client: clientMap) {
//            Date begin_date(dateSTR);
//            if (client.second.getBeginDate() == begin_date) {
//                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
//                cout << client.first << ") " << endl << client.second << endl;
//            }
//        }
        for_each(clientMap.begin(), clientMap.end(), [&] (auto &client) {
            Date begin_date(dateSTR);
            if (client.second.getBeginDate() == begin_date) {
                file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
                cout << client.first << ") " << endl << client.second << endl;
            }
        });
    } else cout << "part_2_associative_containers/ClientMap.cpp:92" << endl;
}

void ClientMap::SearchByDurationTime(bool biggerThen, unsigned int value, const string &path) {
    ofstream file_output(path, ios::binary);
    if (file_output.is_open()) {
//        if (biggerthen) {
//            for (auto &client: clientmap) {
//                if (client.second.getduration() > value) {
//                    file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
//                    cout << client.first << ") " << endl << client.second << endl;
//                }
//            }
//        } else {
//            for (auto &client: clientmap) {
//                if (client.second.getduration() < value) {
//                    file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
//                    cout << client.first << ") " << endl << client.second << endl;
//                }
//            }
//        }
        for_each(clientMap.begin(), clientMap.end(), [&] (auto &client) {
            if(biggerThen) {
                if (client.second.getDuration() > value) {
                    file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
                    cout << client.first << ") " << endl << client.second << endl;
                }
            }
            else {
                if (client.second.getDuration() < value) {
                    file_output.write(reinterpret_cast<char *>(&client), sizeof(client));
                    cout << client.first << ") " << endl << client.second << endl;
                }
            }
        });
    } else cout << "part_2_associative_containers/ClientMap.cpp:112" << endl;
}

void ClientMap::OutputTextTable(const string &path) const {
    ofstream file(path);
    file << setw(21) << "Client Surname" << "|"
         << setw(21) << "Coach Surname"  << "|"
         << setw(21) << "Sport Activity" << "|"
         << setw(21) << "Activity ID"    << "|"
         << setw(21) << "Begin Date"     << "|"
         << setw(21) << "Begin Time"     << "|"
         << setw(21) << "Duration"       << "|"
         << setw(21) << "Rate"           << "|"
         << endl;

    file
            << "---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+"
            << endl;

    for_each(clientMap.cbegin(), clientMap.cend(), [&](const std::pair<int, Client> &entry) {
        const auto &p = entry.second;
        file << setw(21) << p.getClientSurname() << "|" <<
                setw(21) << p.getCoachSurname()  << "|" <<
                setw(21) << p.getSportActivity() << "|" <<
                setw(21) << p.getActivityId()    << "|" <<
                setw(21) << (stringstream() << p.getBeginDate()).str() << "|" <<
                setw(21) << (stringstream() << p.getBeginTime()).str() << "|" <<
                setw(21) << p.getDuration()      << "|" <<
                setw(21) << p.getRate()          << "|" << endl;

        file
                << "---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+"
                << endl;
    });

}

void ClientMap::ReplaceInFile(const string &path, unsigned int id, const Client &client) {
    ofstream file(path, ios::in | ios::binary);
    if (file.is_open()) {
        file.seekp(id * sizeof(Client), ofstream::beg);
        file.write(reinterpret_cast<const char *>(&client), sizeof(Client));
    }
    else cout << "part_2_associative_containers/ClientMap.cpp:181";
}

