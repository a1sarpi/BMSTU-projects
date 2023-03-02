#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct OR_my_flag_t{};
inline constexpr OR_my_flag_t my_flag_OR{};

template <typename Container>
void outputResult(Container my_cont, const string& path)
{
    ofstream output_file(path);
    if (output_file.is_open()) {
        for (auto value: my_cont) {
            output_file << value << " ";
        }
        output_file << endl;
    }
    else cout << "error" << endl;
}

template <typename Container>
void outputResult(Container my_cont, const string& path, OR_my_flag_t)
{
    ofstream output_file(path);
    if (output_file.is_open()) {
        ostream_iterator<typename Container::value_type> iter(output_file, " ");
        copy(my_cont.begin(), my_cont.end(), iter);
    }
    else cout << "error" << endl;
}