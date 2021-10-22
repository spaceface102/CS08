#ifndef SHUFFLE_CPP
#define SHUFFLE_CPP

#include "shuffle.h"
#include <cstdlib>
#include <vector>
#include <array>

template<typename E>
void shuffle(std::vector<E>& container)
{
    for (E& node : container)
        std::swap(node, container[std::rand()%container.size()]);
}

template<typename E, std::size_t Tsize>
void shuffle(std::array<E, Tsize>& container)
{
    for (E& node : container)
        std::swap(node, container[std::rand()%container.size()]);
}

template<typename E>
void shuffle(E& container)
{
    std::size_t i;
    for (auto&& node : container)
    {
        auto it = std::begin(container);
        for (i = std::rand()%container.size(); i > 0; --i) {++it;}
        std::swap(node, *it);
    }
}

#endif //SHUFFLE_CPP