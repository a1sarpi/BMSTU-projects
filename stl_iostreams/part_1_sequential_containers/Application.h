#pragma once
#include "CreateData.h"
#include "LoadData.h"
#include "Modify.h"
#include "OutputResult.h"

template <typename Container>
void run_test(Container& cont) {
    const string file_name("../test.txt");
    const string result_file_name("../result.txt");
    cont.reserve(100);

    bool flag = true;
    bool flag_1 = true;
    bool flag_2 = true;
    bool flag_3 = true;
    bool flag_4 = true;

    unsigned int chosen_option;
    char c_opt_1;
    char c_opt_2;
    char c_opt_3;
    char c_opt_4;

    while (flag) {
        cout << endl;
        cout << "Chose option to test: " << endl
             << "1) Create Data"         << endl
             << "2) Load Data"           << endl
             << "3) Modify"              << endl
             << "4) Output Result"       << endl
             << "5) Print Container"     << endl
             << "6) Finish Testing"      << endl;

        cin >> chosen_option;

        switch (chosen_option) {
            case 1:
                while (flag_1) {
                    cout << "a) Create Data by using file streams" << endl
                         << "b) Create Data by using generate and copy algorithms" << endl;

                    cin >> c_opt_1;

                    switch (c_opt_1) {
                        case 'a':
                            createData(file_name);
                            flag_1 = false;
                            break;

                        case 'b':
                            createData(file_name, my_flag_CD);
                            flag_1 = false;
                            break;

                        default:
                            cout << "there's no such option" << endl;
                            break;

                    }
                }
                flag_1 = true;
                break;


            case 2:
                while (flag_2) {
                    cout << "a) Load Data by using file streams"                 << endl
                         << "b) Load Data by using generate and copy algorithms" << endl;

                    cin >> c_opt_2;

                    switch (c_opt_2) {
                        case 'a':
                            cont = loadData<Container>(file_name);
                            flag_2 = false;
                            break;

                        case 'b':
                            cont = loadData<Container>(file_name, my_flag_LD);
                            flag_2 = false;
                            break;

                        default:
                            cout << "there's not such option" << endl;
                            break;

                    }
                }
                flag_2 = true;
                break;


            case 3:
                while (flag_3) {
                    cout << "a) Modify" << endl
                         << "b) Modify by using iterators " << endl
                         << "c) Modify by using for_each() " << endl
                         << "d) Modify by using transform() " << endl;

                    cin >> c_opt_3;

                    switch (c_opt_3) {
                        case 'a':
                            Modify(cont);
                            flag_3 = false;
                            break;

                        case 'b':
                            Modify(cont.begin(), cont.end());
                            flag_3 = false;
                            break;

                        case 'c':
                            Modify(cont, my_flag_M);
                            flag_3 = false;
                            break;

                        case 'd':
                            Modify<Container>(file_name, result_file_name);
                            flag_3 = false;
                            break;

                        default:
                            cout << "there's no such option" << endl;
                            break;
                    }
                }
                flag_3 = true;
                break;


            case 4:
                while (flag_4) {
                    cout << "a) Output Result by using file streams" << endl
                         << "b) Output Result by using algorithm copy()" << endl;

                    cin >> c_opt_4;

                    switch (c_opt_4) {
                        case 'a':
                            outputResult(cont, result_file_name);
                            flag_4 = false;
                            break;

                        case 'b':
                            outputResult(cont, result_file_name, my_flag_OR);
                            flag_4 = false;
                            break;

                        default:
                            cout << "there's no such option" << endl;
                            break;

                    }
                }
                flag_4 = true;
                break;


            case 5:
                cout << "Your container" << endl;
                for (auto i: cont) {
                    cout << i << " ";
                }
                cout << endl;
                break;

            case 6:
                cout << "test ended." << endl;
                flag = false;
                break;

            default:
                cout << "there's no such option" << endl;
                break;

        }
    }
}
