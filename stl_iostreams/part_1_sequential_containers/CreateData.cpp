#include "CreateData.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <fstream>

int random()
{
    return (-50 + rand() % 1001) * 0.1 / 100;
}

void createData(const string &path)
{
    srand(time(nullptr));
    ofstream output_file(path);
    if (output_file.is_open()) {
        cout << "file successfully opened" << endl;
        for (auto i = 0; i < 100; ++i) {
            output_file << random() << endl;
        }
    }
    else cout << "error while opening file" << endl;
}

void createData(const string &path, CD_my_flag_t)
{
    srand(time(nullptr));
    ofstream output_file(path);
    ostream_iterator<int> iter(output_file, " ");
    vector<int> result(100);
    generate(result.begin(), result.end(), random);
    copy(result.begin(), result.end(), iter);
    //generate_n(iter, 100, random);
}


