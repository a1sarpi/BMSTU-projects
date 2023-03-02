#include "Container.h"
#include "Algorithms.h"
#include <exception>

using std::cout;

struct Goods
{
    uint32_t m_id;                // Код товара
    string   m_name;              // Название
    string   m_manufacturer;      // Производитель
    string   m_warehouse_address; // Адрес склада
    double   m_weight;            // Вес
    
    Goods(uint32_t p_id = 0, const string& p_name = " ",
          const string& p_manufacturer            = " ",
          const string& p_warehouse_address       = " ",
          double p_weight = .0)
          : m_id(p_id), m_name(p_name),
          m_manufacturer(p_manufacturer),
          m_warehouse_address(p_warehouse_address),
          m_weight(p_weight)
    {}

    friend ostream& operator<<(ostream& os, const Goods& goods) 
    {
        os << "ID:                " << goods.m_id                << endl
           << "Name:              " << goods.m_name              << endl
           << "Manufacturer:      " << goods.m_manufacturer      << endl
           << "Warehouse address: " << goods.m_warehouse_address << endl
           << "Weight:            " << goods.m_weight            << endl;
        return os;
    }
};

class functor {
public: 
    auto operator()(const Goods& obj) {
        if (obj.m_name == "Jeans") {
            return true;
        }
        return false;
    }
};

int main()
{
    // TODO: Выполнить тестирование.
    //try {
        auto range = [](const auto& s) -> bool {
            return (25 < s.m_weight) && (s.m_weight < 200);
        };

        auto print = [](const auto& obj) {
            cout << "ID:                " << obj.m_id               << endl
                << "Name:              " << obj.m_name              << endl
                << "Manufacturer:      " << obj.m_manufacturer      << endl
                << "Warehouse address: " << obj.m_warehouse_address << endl
                << "Weight:            " << obj.m_weight    << endl << endl;
        };

        Vector<Goods> ContainerA{ {1, "Jeans",       "Levi's",          "San Francisco", 500},
                                  {2, "Smartphones", "Apple",           "Cupertino",      10},
                                  {3, "Tabi Shoes",  "Masion Margiela", "Paris",          50} };
        cout << "First batch of goods: " << endl;
        cout << "1) " << endl << ContainerA[0] << endl
             << "2) " << endl << ContainerA[1] << endl
             << "3) " << endl << ContainerA[2] << endl;

        Vector<Goods> ContainerB;
        Goods b0{ 4, "Cars",  "Audi", "Berlin",  1000 };
        Goods b1{ 5, "Pizza", "Dodo", "Syktyvkar", 20 };
        Goods b2{ 6, "Jeans", "Mech", "Moscow",    30 };
        ContainerB.pushBack(b0);
        ContainerB.pushBack(b1);
        ContainerB.pushBack(b2);
        //ContainerB.insert(ContainerB.end(), b2);
        //ContainerB.insert(ContainerB.end() - 1, b2);

        cout << "Second batch of goods: " << endl << endl;
        
        forEach(ContainerB.begin(), ContainerB.end(), print); // Убрал. !!! Никаких  ContainerB.end() + 1 быть не должно. end - это элемент, следующий за последним

        cout << "Range insert: " << endl;
        ContainerA.insert(ContainerA.begin(), ContainerB.begin(), ContainerB.end());
        forEach(ContainerA.begin(), ContainerA.end(), print);

        cout << "Test findIf 25 < weight < 200: " << endl;
        auto it = findIf(ContainerA.begin(), ContainerA.end(), range);
        cout << *it << endl;

        cout << "Test copyIf to get all manufactures, that produce jeans: " << endl;
        Vector<Goods> ContainerC(2);
        copyIf(ContainerA.begin(), ContainerA.end(), ContainerC.begin(), functor());
        unsigned int i = 0;
        for (const auto& elem : ContainerC) {
            cout << i + 1 << ") " << endl << elem << endl;
            ++i;
        }

        cout << "Change the address to new, using ->" << endl;
        ContainerA[1].m_warehouse_address = "Russia";
        forEach(ContainerA.begin(), ContainerA.end(), print);

    //}
    //catch (OutOfRangeException& exception) {
    //    cerr << exception.what() << endl;
    //}
    //catch (IteratorException& exception) {
    //    cerr << exception.what() << endl;
    //}
    //catch (exception& exception) {
    //    cerr << exception.what() << endl;
    //}
    //catch (...) {
    //    cout << "unpredictable error" << endl;
    //}
    return 0;
}