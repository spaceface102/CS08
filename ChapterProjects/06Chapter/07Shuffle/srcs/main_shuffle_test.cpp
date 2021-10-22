#include "shuffle.h"
#include <iostream>
#include <vector>
#include <array>
#include <list>

template<typename E>
std::ostream& operator<<(std::ostream& out, const std::vector<E>& container)
{
    for (auto&& node : container)
        out << node << ", ";
    out << '\n';
    return out;
}

template<typename E, std::size_t Tsize>
std::ostream& operator<<(std::ostream& out, const std::array<E, Tsize>& container)
{
    for (auto&& node : container)
        out << node << ", ";
    out << '\n';
    return out;
}

template<typename E>
std::ostream& operator<<(std::ostream& out, const std::list<E>& container)
{
    for (auto&& node : container)
        out << node << ", ";
    out << '\n';
    return out;
}

struct Custom
{
public:
    Custom(void) = default;
    Custom(int number) : number((number << std::rand()%5) | 42) {}
    int number;
};

std::ostream& operator<<(std::ostream& out, const Custom& obj)
{
    out << "Custom#" << obj.number;
    return out;
}

int main(void)
{
    std::srand(time(nullptr));
    std::vector<int> vect = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<int, 9> array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<Custom> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << vect;
    std::cout << array;
    std::cout << list;

    std::cout << "\nShuffling...\n";
    shuffle(vect);
    shuffle(array);
    shuffle(list);

    std::cout << "Done!\n\n";
    std::cout << vect;
    std::cout << array;
    std::cout << list;
}