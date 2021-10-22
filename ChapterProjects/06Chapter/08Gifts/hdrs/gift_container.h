#ifndef GIFT_CONTAINER_H
#define GIFT_CONTAINER_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <iomanip>

typedef std::string person_name;
typedef std::string gift_idea;
typedef std::unordered_map<person_name, std::unordered_set<gift_idea>> gift_container;

std::ostream& operator<<(std::ostream& out, const gift_container& container) noexcept
{
    for (auto&& gift_person_ideas_pair : container)
    {
        out << std::setw(10) << std::left 
        << gift_person_ideas_pair.first << ":";
        for (auto&& a_gift_idea : gift_person_ideas_pair.second)
            out << ' ' << a_gift_idea << ',';
        out << '\n';
    }

    return out;
}

#endif //GIFT_CONTAINER_H