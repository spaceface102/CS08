#ifndef HISTORY_CAPABLE_TYPES_H
#define HISTORY_CAPABLE_TYPES_H

#include <variant>
#include "History_Capable_Type_Wrapper.h"
#include <SFML/Graphics.hpp>

/*
In order to avoid having to force each implemenation of
a GUI component to have a specific Snapshot implementation
We will have in essence a union wrapper type, that will allow
specified types to be stored. PLEASE ONLY INPUT TYPES THAT WILL
BE USING THE HISTORY CLASS STORE SNAPSHOTS!

In order to allow any type of your choosing to be used with
History, you will need to follow this pattern:

1) LEAVE EmptyClass ALONE
    a) this is needed since the type wrapper does not have a
       default constructor

2) USE the History_TypeWrapper to wrap your type like so:
    a) History_TypeWrapper<*your gui type*>
    NOTE: DON'T make an instance of the type, just create the type
    ANOTHER NOTE: Don't add extra qualifiers to the type such as
    const, or &, or volatile, though having a pointer type is fine.

3) Add it to the variant template parameter list

That it! Still Confused? Just look at the typedef below.
Remember, every single time you want to use a new type
with History class, you must FIRST add it here.
*/


//This class NEEDS to have the same facilities like
//History_TypeWrapper, in order so History class
//can use std::visit with a generic lambda
class EmptyClass : public History_TypeWrapper<std::monostate>
{
public:
    //used to enable default constructor for the first varaint
    //type, necessary if you want to use an array of
    //History_Capable_Types!
    EmptyClass(void) noexcept
        : History_TypeWrapper<std::monostate>{throw_away}
    {}

private:
    std::monostate throw_away;
};


//MODIFY HERE!!!!!!!
typedef std::variant<
    EmptyClass, //LEAVE THIS CLASS ALONE!
    History_TypeWrapper<sf::CircleShape>
> History_Capable_Type;

#endif //HISTORY_CAPABLE_TYPES_H