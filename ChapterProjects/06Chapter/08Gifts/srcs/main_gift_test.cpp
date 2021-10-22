#include "gift_container.h"
#include <iostream>
#include<vector>

template<typename E>
const E& get_random(const std::vector<E>& vect) noexcept
{
    return vect.at(std::rand()%vect.size());
}

void give_random_gifts(
    gift_container& gift_tracker,
    const std::vector<person_name>& people,
    const std::vector<gift_idea>& ideas)
{
    auto get_number_of_gifts = []() -> std::size_t 
    {
        const std::size_t min_num = 2;
        const std::size_t max_num = 3;

        return min_num + std::rand()%(1 + max_num - min_num);
    };

    for (auto&& person : people)
        for (std::size_t k = get_number_of_gifts(); k > 0; --k)
            gift_tracker[person].insert(get_random(ideas));
}

int main(void)
{
    std::srand(time(nullptr));
    std::vector<gift_idea> my_gift_ideas = 
    {
        "A suit", "A tootsie pop", "The center of the earth",
        "The falkland islands", "A tricycle",
        "A Ticonderoga #2 pencil", "A scan tron",
        "A mouse ball", "A usb powered washing machine", "A physical bitcoin",
        "Three quarters of a screwdriver", "The Golden Gate Bridge",
        "A government bond and a pack of trident gum", 
        "SAT waiver", "Bribed entrance to Ivy League of choice",
        "A backpack made up out of iron on patches", "A cat"
    };
    std::vector<person_name> my_friends = 
    {
        "You", "#42", "Redacted", "Mono", "W"
    };
    gift_container gift_tracker;

    give_random_gifts(gift_tracker, my_friends, my_gift_ideas);
    std::cout << gift_tracker << '\n';

    //erase random gift
    {
        auto&& temp_person = get_random(my_friends);
        auto&& temp_gift = *gift_tracker[temp_person].begin();
    
        std::cout << "\nRemoved: " << temp_gift << " from " 
        << temp_person << "'s gift list.\n\n";

        gift_tracker[temp_person].erase(temp_gift);
    }

    std::cout << gift_tracker << '\n';


    //duplicate random gift
    {
        auto&& temp_person = get_random(my_friends);
        auto&& temp_gift = *gift_tracker[temp_person].begin();
    
        std::cout << "\nTried to duplicate: " << temp_gift << " from " 
        << temp_person << "'s gift list.\n\n";

        gift_tracker[temp_person].insert(temp_gift);
    }

    std::cout << gift_tracker << '\n';
    return 0;
}