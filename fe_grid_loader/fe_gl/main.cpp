#include <iostream>
#include "AneuMeshLoader.h"

using namespace std;

namespace output {
    ostream &operator<<(ostream &out, const vector<unsigned int> &Res) {
        for (const auto &i: Res) {
            out << i << " ";
        }
        return out;
    }

    ostream &operator<<(ostream &out, const vector<FiniteElement> &Res) {
        for (const auto &i: Res) {
            out << i << endl;
        }
        return out;
    }

    /*ostream &operator<<(ostream &out, const vector<BoundaryFiniteElement> &Res) {
        for (const auto &i: Res) {
            out << i << endl;
        }
        return out;
    }*/

    ostream &operator<<(ostream &out, const unordered_set<unsigned int> &Res) {
        for (const auto &i: Res) {
            out << i << " ";
        }
        return out;
    }
}

using namespace output;

int main(int argc, char *argv[]) 
{
    AneuMeshLoader Loader;
    //Loader.loadMesh(argv[1]);
    Loader.loadMesh("../../MeshExample.txt");

    auto result_1 = Loader.FindByNodesID(79, 67, 74);
    cout << endl << "FindByNodesID(79, 67, 74): "             << endl << result_1    << endl;

    auto result_2 = Loader.FindByEdge(79, 67);
    cout << endl << "FindByEdge(79, 67): "                    << endl << result_2    << endl;

    auto result_3 = Loader.GetVertFromAreaID(22);
    cout << endl << "GetVertFromAreaID(22): "                 << endl << result_3    << endl;

    auto result_4 = Loader.GetFiniteElementsByMaterialID(2);
    cout << endl << "GetFiniteElementByMaterialID(2): "       << endl << result_4    << endl;

    auto result_5 = Loader.GetBoundaryFiniteElementsByAreaID(22);
    cout << endl << "GetBoundaryFiniteElementsByAreaID(22): " << endl << result_5    << endl;

    auto result_6 = Loader.GetNeighbours();
    cout << endl << "GetNeighbours()[6]: "                    << endl << result_6[6] << endl;

    Loader.TASK("../test.txt");

    Loader.SplitInHalf();
}