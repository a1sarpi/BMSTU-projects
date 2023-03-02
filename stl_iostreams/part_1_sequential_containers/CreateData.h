#pragma once
#include <string>

using namespace std;

struct CD_my_flag_t{};
inline constexpr CD_my_flag_t my_flag_CD{};

void createData(const string &path);

void createData(const string &path, CD_my_flag_t);

