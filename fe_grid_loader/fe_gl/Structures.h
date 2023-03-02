#pragma once
#include <iostream>
#include <vector>

using namespace std;


//!!! Не надо разбивать структуры по отдельным файлам. Разбивают классы.
//!!! Все типы для загрузчика можно хранить в одном файле.

struct Node {
	unsigned int node_ID;
	vector<double> nodeCoord;
	//bool isVertices;
	
	Node(unsigned int p_ID, const vector<double>& p_coord /*, bool isVertices*/)
		: node_ID(p_ID), nodeCoord(p_coord)/*, isElementVertices(isElementVertices)*/
    {}

    //!!! Где const у node_1 и node_2

    Node(Node const &node_1, Node const &node_2, unsigned int p_node_ID) : node_ID(p_node_ID) {
        auto &c1 = node_1.nodeCoord;
        auto &c2 = node_2.nodeCoord;
        for (int i = 0; i < min(c1.size(), c2.size()); ++i) {
            //cout << "|* " << c1[i] << " | " << c2[i] << "*|    ";
            nodeCoord.push_back((c1[i] + c2[i]) / 2.0);
        }
    }

    bool operator==(const Node& p_node) const
    {
        /*return ((node_ID == p_node.node_ID) &&
                (nodeCoord == p_node.nodeCoord)); //!!! С каких пор double сравнивают через == ?*/
        for (auto i = 0; i < nodeCoord.size(); ++i) {
            if(abs(nodeCoord[i] - p_node.nodeCoord[i]) >= 0.000000001)  {
                return false;
            }
        }
        return true;
    }

	bool operator<(const Node& p_node) const
    {
        return (node_ID < p_node.node_ID);
    }

	friend ostream& operator<<(ostream& out, const Node& p_node)
    {
        for (const auto &i: p_node.nodeCoord) {
            out << i << " ";
        }
        return out;
    }

};

struct FiniteElement {
    unsigned int	      fin_elem_ID;
    unsigned int		  material_ID;
    vector<unsigned int>   nodes_IDs;

    FiniteElement(unsigned int p_fin_elem_ID, unsigned int p_material_ID,
                  const vector<unsigned int>& p_nodes_IDs)
            : fin_elem_ID(p_fin_elem_ID), material_ID(p_material_ID),
              nodes_IDs(p_nodes_IDs)
    {}

    friend ostream& operator<<(ostream& out, const FiniteElement& p_fin_elem) {
        for (const auto &i: p_fin_elem.nodes_IDs) {
            out << i << " ";
        }
        return out;
    }

};

template<typename _T>
inline void hashCombine(unsigned int &o_seed, const _T &p_val) {
    o_seed ^= hash<_T>()(p_val) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
}

template<typename _T>
inline void hashVal(unsigned int &o_seed, const _T &p_val) {
    hashCombine(o_seed, p_val);
}

template<typename _T, typename ... _Types>
inline void hashVal(unsigned int &o_seed, const _T &p_val, const _Types &... p_args) {
    hashCombine(o_seed, p_val);
    hashVal(o_seed, p_args ...);
}

template<typename ... _Types>
inline unsigned int hashVal(const _Types &... p_args) {
    unsigned int seed = 0;
    hashVal(seed, p_args ...);
    return seed;
}

struct edge {
    unsigned int from;
    unsigned int to;
    unsigned int middle = 0;

    edge(unsigned int p_from, unsigned int p_to, unsigned int p_middle)
            : from(p_from), to(p_to), middle(p_middle) {}

    bool operator==(const edge &rhs) const {
        return (from == rhs.from && to == rhs.to) ||
               (from == rhs.to && to == rhs.from);
    }

    bool operator!=(const edge &rhs) const {
        return !(rhs == *this);
    }

    friend ostream &operator<<(ostream &out, const edge &edge) {
        out << "from: " << edge.from
            << " to: " << edge.to
            << " middle: " << edge.middle
            << endl;
        return out;
    }
};

class edgeHash {
public:
    unsigned int operator()(const edge &rib) const {
        if (rib.from > rib.to) {
            return hashVal(rib.from, rib.to);
        } else return hashVal(rib.to, rib.from);
    }
};

class equalEdges {
public:
    bool operator()(const edge &rib1, const edge &rib2) const {
        return rib1 == rib2;
    }
};