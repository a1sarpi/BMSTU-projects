#include <ostream>
#include "MeshLoader.h"
#include <cmath>
#include <ranges>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

namespace std {
    ostream &operator<<(ostream &out, const vector<unsigned int> &Res) {
        for (const auto &i: Res) {
            out << i << " ";
        }
        return out;
    }
}

const vector<Node> &MeshLoader::getNodes() const {
    return Nodes;
}

const vector<FiniteElement> &MeshLoader::getFinElems() const {
    return FinElems;
}

const vector<FiniteElement> &MeshLoader::getBoundFinElems() const {
    return BoundFinElems;
}

vector<unsigned int> MeshLoader::FindByNodesID(unsigned int ID_x, unsigned int ID_y, unsigned int ID_z) {
    vector<unsigned int> result;
    auto begin = FinElems.begin();
    auto end = FinElems.end();
    while (begin != end) {
        begin = find_if(begin, end, [&](const FiniteElement &curFE) {
            auto beg = curFE.nodes_IDs.begin();
            auto fin = curFE.nodes_IDs.end();

            array<unsigned int, 3> IDs = {ID_x, ID_y, ID_z}; //!!! Вектор в данном случае - долго. Известно, что используется 3 элемента
                                                             //!!! Поэтому лучше std::array

            return all_of(IDs.begin(), IDs.end(), [&](auto eg) {
                return curFE.nodes_IDs[0] != eg ||
                       curFE.nodes_IDs[1] != eg ||
                       curFE.nodes_IDs[2] != eg ||
                       curFE.nodes_IDs[3] != eg;
                //return find(beg, fin, eg) != fin; //!!! Известно, что узлов 4. Почему нельзя явно проверить через ||
            });
        });
        if (begin != end) {
            result.push_back(begin->fin_elem_ID);
            ++begin;
        }
    }
    return result;
}

vector<unsigned int> MeshLoader::FindByEdge(unsigned int ID_n1, unsigned int ID_n2) {
    vector<unsigned int> result;
    auto begin = FinElems.begin();
    auto end = FinElems.end();
    while (begin != end) {
        begin = find_if(begin, end, [&](const FiniteElement &curFE) {
            auto beg = curFE.nodes_IDs.begin();
            auto fin = curFE.nodes_IDs.end();

            array<unsigned int, 2> IDs = {ID_n1, ID_n2}; //!!! Вектор в данном случае - долго. Известно, что используется 2 элемента
                                                         //!!! Поэтому лучше std::array

            return all_of(IDs.begin(), IDs.end(), [&](auto eg) {
                return curFE.nodes_IDs[0] != eg ||
                       curFE.nodes_IDs[1] != eg ||
                       curFE.nodes_IDs[2] != eg ||
                       curFE.nodes_IDs[3] != eg;
                //return find(beg, fin, eg) != fin; //!!! Известно, что узлов 4. Почему нельзя явно проверить через ||
            });

        });
        if (begin != end) {
            result.push_back(begin->fin_elem_ID);
            ++begin;
        }
    }
    return result;
}

unordered_set<unsigned int> MeshLoader::GetVertFromAreaID(unsigned int areaID) {
    unordered_set<unsigned int> result;
    for_each(BoundFinElems.begin(), BoundFinElems.end(), [&](const auto &b_fi_el) {
        if (b_fi_el.fin_elem_ID == areaID) {
            result.insert(b_fi_el.nodes_IDs.begin(), b_fi_el.nodes_IDs.end());
        }
    });
    return result;
}

vector<unsigned int> MeshLoader::GetFiniteElementsByMaterialID(unsigned int materialID) {
    vector<unsigned int> result;
    for_each(FinElems.cbegin(), FinElems.cend(), [&](const FiniteElement &curFE) {
        if (curFE.material_ID == materialID) 
            result.push_back(curFE.fin_elem_ID);
    });
    return result;
}

vector<unsigned int> MeshLoader::GetBoundaryFiniteElementsByAreaID(unsigned int areaID) {
    vector<unsigned int> result;
    for_each(BoundFinElems.cbegin(), BoundFinElems.cend(), [&](const FiniteElement &curFE) {
        if (curFE.material_ID == areaID) result.push_back(curFE.fin_elem_ID);
    });
    return result;
}

void MeshLoader::SplitInHalf() {
    unordered_set<edge, edgeHash, equalEdges> edges;
    for_each(FinElems.begin(), FinElems.end(), [&](FiniteElement &fi_el) {
        auto size = fi_el.nodes_IDs.size();
        for (auto i = 0; i < size - 1; ++i) {
            for (auto j = i + 1; j < size; ++j) {
                auto ID_1 = fi_el.nodes_IDs[i];
                auto ID_2 = fi_el.nodes_IDs[j];
                edge insertedEdge(ID_1, ID_2, Nodes.size());
                auto [insertedIterator, flag] = edges.insert(insertedEdge);
                if (flag) {
                    auto midNode = Nodes.emplace_back(Nodes[ID_1 + 1], Nodes[ID_2 + 1], Nodes.size());
                    //cout << Nodes[ID_1 + 1] << " | " << Nodes[ID_2 + 1] << " -> " << midNode << endl;
                    fi_el.nodes_IDs.push_back(midNode.node_ID);
                    Nodes.push_back(midNode);
                } else {
                    fi_el.nodes_IDs.push_back(insertedIterator->middle);
                }
            }
        }
    });
    for_each(BoundFinElems.begin(), BoundFinElems.end(), [&](FiniteElement &b_fi_el) {
        auto size = b_fi_el.nodes_IDs.size();
        for (auto i = 0; i < size - 1; ++i) {
            for (auto j = i + 1; j < size; ++j) {
                auto ID_1 = b_fi_el.nodes_IDs[i];
                auto ID_2 = b_fi_el.nodes_IDs[j];
                edge edgeToFind(ID_1, ID_2, 0);
                auto foundEdge = edges.find(edgeToFind);
                b_fi_el.nodes_IDs.push_back(foundEdge->middle);
            }
        }
    });
}

unordered_map<unsigned int, unordered_set<unsigned int>> MeshLoader::GetNeighbours() const {
    unordered_map<unsigned int, unordered_set<unsigned int>> result;
    result.reserve(Nodes.size());
//    for_each(FinElems.begin(), FinElems.end(), [&](const auto &el) {
//        for_each(el.nodes_IDs.begin(), el.nodes_IDs.end(), [&](const auto &node) {
//            result[node].insert(el.nodes_IDs.begin(), el.nodes_IDs.end());
//        });
//    });
    for (const auto &el: FinElems) {
        for (const auto &node: el.nodes_IDs) {
            result[node].insert(el.nodes_IDs.begin(), el.nodes_IDs.end());
            result[node].erase(node);
            //!!! Случай "узел сам себе сосед" рассматривать не надо. Исправил.
        }
    }
    return result;
}

void MeshLoader::TASK(const string& path) const
{
    auto nodes = this->getFinElems();
    unsigned int radius;
    cout << "Enter radius: ";
    cin  >> radius;

    // R = abc/4√p (p – a) (p – b) (p – c)
    auto check = [&](const auto& elem) {
        unsigned int a = sqrt(abs(pow(elem.nodes_IDs[0], 2) - pow(elem.nodes_IDs[1], 2)));
        unsigned int b = sqrt(abs(pow(elem.nodes_IDs[0], 2) - pow(elem.nodes_IDs[2], 2)));
        unsigned int c = sqrt(abs(pow(elem.nodes_IDs[1], 2) - pow(elem.nodes_IDs[2], 2)));
        unsigned int p = (a + b + c) / 2;
        double r = a * b * c * 1.0 / (4 * sqrt(p * (p - a) * (p - b) * (p - c)));
        return r > radius;
    };

    auto result = nodes | ranges::views::filter(check) | ranges::views::take(10) |
                          ranges::views::transform([&] (const auto &element) {
                              return element.nodes_IDs;
    });

    ofstream file(path);

    ranges::copy(result, ostream_iterator<vector<unsigned int>>(cout, "\n"));
    //ranges::copy(result, ostream_iterator<vector<unsigned int>>(file, "\n")); Вывод в файл

    //!!! В задании сказано, что вывести нужно список узлов, а не FiniteElement.
    //!!! Где в pipeline преобразование FiniteElement -> nodes_IDs
}

