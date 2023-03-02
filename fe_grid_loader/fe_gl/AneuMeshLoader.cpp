#include "AneuMeshLoader.h"
#include <iostream>
#include <string>
#include <fstream>
//#include <vector>

using namespace std;

void AneuMeshLoader::loadMesh(const string &path)
{
    //!!! Где проверка, что файл открыт нормально? Исправил.

	string line;
    ifstream file(path);

    if (file.is_open()) {
        int nodesCount, dimCount;

        file >> nodesCount >> dimCount;
        for (auto i = 1; i <= nodesCount; ++i) {
            unsigned int ID = i;
            vector<double> coord(dimCount);
            for (auto j = 1; j <= dimCount; ++j) {
                file >> coord[j - 1];
            }
            Nodes.emplace_back(ID, coord);
        }

        file >> nodesCount >> dimCount;
        for (auto i = 1; i <= nodesCount; ++i) {
            unsigned int ID = i;
            vector<unsigned int> coord(dimCount);
            unsigned int materialID = 0;
            file >> materialID;
            for (auto j = 1; j <= dimCount; ++j) {
                file >> coord[j - 1];
            }
            FinElems.emplace_back(ID, materialID, coord);
        }

        file >> nodesCount >> dimCount;
        for (auto i = 1; i <= nodesCount; ++i) {
            unsigned int ID = i;
            vector<unsigned int> coord(dimCount);
            unsigned int materialID = 0;
            file >> materialID;
            for (auto j = 1; j <= dimCount; ++j) {
                file >> coord[j - 1];
            }
            BoundFinElems.emplace_back(ID, materialID, coord);
        }
        cout << ".aneu file was successfully read." << endl;
    }
    else cout << ".aneu file wasn't read." << endl;
	//m_File.close(); //!!! Файл и так закрывается деструктором ifstream (при условии, что вы его объявите в этом методе)
}