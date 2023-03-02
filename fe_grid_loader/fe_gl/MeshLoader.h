#pragma once
#include "Structures.h"
//#include "FiniteElement.h"
//#include "BoundaryFiniteElement.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>



//!!! Задание на защиту (не удалять)
//!!! Реализовать на основе std::ranges 
//!!! 1. Получить контейнер КЭ из данной области (тетраэдров).
//!!! 2. За один pipeline вывести в файл списки ID узлов 10 первых КЭ,
//!!!    у которых радиус описанной окружности больше заданного значения.

using namespace std;

class MeshLoader {
private:

protected:
	vector<Node> Nodes;
	vector<FiniteElement> FinElems;
	vector<FiniteElement> BoundFinElems;

public:
    virtual ~MeshLoader() = default;

	virtual void loadMesh(const string &path);

    // Методы, позволяющие получить контейнеры узлов,
    // конечных элементов и граничных элементов
	const vector<Node>& getNodes() const;
	const vector<FiniteElement>& getFinElems() const;
	const vector<FiniteElement>& getBoundFinElems() const;

    // Метод, позволяющий найти КЭ по ID трех его
    // вершинных узлов через алгоритм find_if
    vector<unsigned int> FindByNodesID(unsigned int ID_x, unsigned int ID_y, unsigned int ID_z);

    // Метод, позволяющий найти КЭ по ребру, заданному
    // через ID двух узлов
    vector<unsigned int> FindByEdge(unsigned int ID_n1, unsigned int ID_n2);

    // Метод, возвращающий контейнер КЭ с заданными ID
    // границы
    unordered_set<unsigned int> GetVertFromAreaID(unsigned int areaID);

    // Метод, возвращающий контейнер КЭ по ID материала
    vector<unsigned int> GetFiniteElementsByMaterialID(unsigned int materialID);

    // Метод, возвращающий контейнер граничных КЭ по ID
    // границы
    vector<unsigned int> GetBoundaryFiniteElementsByAreaID(unsigned int ID);

    // Метод, производящий вставку новых узлов в середины
    // ребер существующих КЭ
    void SplitInHalf();

    // Метод, создающий контейнер, n-ый элемент которого
    // хранит контейнер всех "соседей" по ребрам для узла n

    unordered_map<unsigned int, unordered_set<unsigned int>> GetNeighbours() const;

    void TASK(const string& path) const;
};