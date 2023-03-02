#include <iostream>
#include "ClientMap.h"

int main()
{
    //ClientMap client("test");
    ClientMap client;
    client.LoadData("../../part_2_associative_containers/test.dat");

    client.OutputTextTable("../../part_2_associative_containers/output_test.txt");

    cout << "----------Search By Client Surname----------" << endl;

    client.SearchByClientSurname("Kuprin", "result");

    cout << "----------Search By Coach Surname-----------" << endl;

    client.SearchByCoachSurname("Vlasov", "result");

    cout << "----------Search By Duration Time-----------" << endl;

    client.SearchByDurationTime(true, 10, "result");

    cout << "----------Search By Sport Activity----------" << endl;

    client.SearchBySportActivity("Weightlifting", "result");

    cout << "----------Search By Start Date----------" << endl;

    client.SearchByStartDate("2021.09.11", "result");

    client.ReplaceInFile("result", 7, {"Kortenko",
                                                     "Ciganenko",
                                                      "Running", 3,
                                                      Date("2021.09.11"), Time("12:20"),
                                                      90, 5});

    return 0;
}