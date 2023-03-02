#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

struct M_my_flag_t{};
inline constexpr M_my_flag_t my_flag_M{};

template <typename Container>
//requires requires(typename Container::value_type value, typename Container::size_type size)
//{
//    {value + value} -> same_as<typename Container::value_type>;
//    {abs(value)}    -> same_as<typename Container::value_type>;
//    {value / size}  -> convertible_to<typename Container::value_type>;
//}
void Modify(Container& my_cont)
{
    auto sum = typename Container::value_type(); //!!! Я вное использование типа. Можно auto sum = typename Container::value_type();
                                                 //!!! Исправил.
    
    for(auto i: my_cont) {
        sum += abs(my_cont[i]);
    }
    my_cont.push_back(sum);
    my_cont.push_back(sum / my_cont.size());
}

template <std::forward_iterator Iter>
void Modify(Iter begin, Iter end)
{
    auto half_max = *(max_element(begin, end)) / 2;  //!!! Явное использование типа.
                                                     //!!! Исправил.
    while (begin != end) {
        *(begin) = (*(begin) / half_max);
        ++begin;
    }
}

template <typename Container>
void Modify(Container& my_cont, M_my_flag_t)
{
    for_each(my_cont.begin(), my_cont.end(), [&](const typename Container::value_type& element) {
        return (element / (*(max_element(my_cont.begin(), my_cont.end())) * 1.0 / 2));
    });
}

template <typename Container>
void Modify(const string& file_from, const string& file_to)
{
    ofstream output_file(file_from);
    ifstream input_file(file_to);
    if (output_file.is_open() and input_file.is_open()) {
        Container my_cont;
        my_cont.reserve(100);
        ostream_iterator<typename Container::value_type> ostream_iter(output_file, " ");
        istream_iterator<typename Container::value_type> istream_iter(input_file);
        transform(istream_iter, istream_iterator<typename Container::value_type>(), ostream_iter, [&](const typename Container::value_type &element) {
            return (element / (*(max_element(my_cont.begin(), my_cont.end())) * 1.0 / 2));
        });
    }
    else cout << "error" << endl;
}