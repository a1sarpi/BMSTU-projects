#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

struct LD_my_flag_t{};
inline constexpr LD_my_flag_t my_flag_LD{};

template <typename Container>
Container loadData(const std::string& path) {
    Container my_data;
    ifstream file(path);
    if (file.is_open()) {
        cout << "file successfully opened" << endl;
        while(!file.eof()) {
            string number;
            file >> number;
            //cout << number;
            if (file.eof()) break;
            my_data.push_back(stoi(number));
        }
    }
    else cout << "error while opening file" << endl;
    return my_data;
}

template <typename Container>
Container loadData(const string& path, LD_my_flag_t) {
    Container my_data;
    ifstream file(path);
    if (file.is_open()) {
        cout << "file successfully opened" << endl;
        istream_iterator<typename Container::value_type> iter(file);
        copy_n(iter, 100, back_inserter(my_data));
    }
    else cout << "error while opening file" << endl;
    return my_data;
}