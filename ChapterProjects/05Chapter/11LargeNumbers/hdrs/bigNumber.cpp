#ifndef BIG_NUMBER_CLASS_CPP
#define BIG_NUMBER_CLASS_CPP

#include "bigNumber.h"
#include <cmath>
#include <iomanip>
#include <cassert>

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(void)
    : number_list(1) //initialize to size 1, fill with 0
{}

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(const std::initializer_list<std::int64_t>& digits)
{
    for (std::int64_t one_digit : digits)
    {
        assert(std::abs(one_digit) < Tbase && "Each digit must be less than the define base!");
        number_list.push_back(one_digit);
    }
        
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(BigNumber&& that)
    : number_list(std::move(that.number_list))
{}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator=(BigNumber&& that)
{
    this->number_list = std::move(that.number_list);
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator+=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator-=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator*=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator/=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator%=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator&=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator|=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator^=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator<<=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator>>=(const BigNumber& that)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator++(void)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator++(int)
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator--(void)
{

}
//EOF


template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator--(int)
{

}
//EOF






template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator+(const BigNumber& that) const
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator-(const BigNumber& that) const
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator*(const BigNumber& that) const
{

}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator/(const BigNumber& that) const
{
    BigNumber<Tbase> result{0};
    BigNumber<Tbase> currentNumber = this;

    while (currentNumber > BigNumber<Tbase>{0})
        {currentNumber -= that; ++result;}

    if (currentNumber == BigNumber<Tbase>{0})
        return result;
    else
        return result - BigNumber<Tbase>{-1};
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator%(const BigNumber& that) const
{
    BigNumber<Tbase> currentNumber = this;

    while (currentNumber > BigNumber<Tbase>{0})
        currentNumber -= that;

    if (currentNumber == BigNumber<Tbase>{0})
        return BigNumber<Tbase>{0};
    else
        return currentNumber + that;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator~(void) const
{
    BigNumber<Tbase> result = *this;
    for (int64_t& digit : result.number_list)
        digit = ~digit;
    return result;
}

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator&(const BigNumber& that) const
{
    if (that == BigNumber<Tbase>{0})
        return BigNumber<Tbase>{0};
    
    BigNumber<Tbase> temp = *this;
    
    auto thatNode = that.number_list.begin();
    std::size_t that_numberOfNodes = that.number_list.size();

    //implied that.number_list has all zeros in front
    while (temp.number_list.size() > that.number_list.size())
        temp.number_list.pop_front();
    while (that_numberOfNodes > temp.number_list.size())
        {++thatNode; that_numberOfNodes -= 1;}

    //at this point tempNode and thatNode will be pointing to the same
    //relative node
    auto tempNode = temp.number_list.begin();
    for (std::size_t i = 0; i < that_numberOfNodes; i++, ++tempNode, ++thatNode)
        *tempNode &= *thatNode;
    
    return temp;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator|(const BigNumber& that) const
{
    //I love demorgans!
    return ~( (~(*this)) & (~that) );
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator^(const BigNumber& that) const
{
            //(A OR B)     AND  NOT(A AND)
    return ((*this) | that) & (~((*this) & that));
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator<<(const BigNumber& that) const
{
    BigNumber<Tbase> temp = *this;
    for (BigNumber<Tbase> i{0}; i < that; ++i)
        temp /= BigNumber<Tbase>{2};
    return temp;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator>>(const BigNumber& that) const
{
    BigNumber<Tbase> temp = *this;
    for (BigNumber<Tbase> i{0}; i < that; ++i)
        temp *= BigNumber<Tbase>{2};
    return temp;
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator==(const BigNumber& that) const
{
    if (this->number_list.size() != that.number_list.size())
        return false;

    //they have the same number of nodes
    auto thisNode = this->number_list.begin();
    auto thatNode = that.number_list.begin();

    for (; thisNode != this->number_list.end(); ++thisNode, ++thatNode)
    {
        if (*thisNode != *thatNode)
            return false;
    }

    return true;
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator!=(const BigNumber& that) const
{
    return !((*this) == that);
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator>(const BigNumber& that) const
{
    if (this->number_list.size() > that.number_list.size())
        return true;
    else if (this->number_list.size() < that.number_list.size())
        return false;

    //they have the same number of nodes
    auto thisNode = this->number_list.begin();
    auto thatNode = that.number_list.begin();

    for (; thisNode != this->number_list.end(); ++thisNode, ++thatNode)
    {
        if (*thisNode < *thatNode)
            return false;
    }

    return true;
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator>=(const BigNumber& that) const
{
    return ((*this) > that) || ((*this) == that);
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator<(const BigNumber& that) const
{
    return !((*this) >= that);
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator<=(const BigNumber& that) const
{
    return !((*this) > that);
}
//EOF

template<std::int64_t base>
std::ostream& operator<<(std::ostream& out, const BigNumber<base>& big_number)
{
    static const std::int64_t NUMBER_OF_DIGITS_MAX = std::ceil(std::log10(base));

    for (int64_t node : big_number.number_list)
        out 
        << std::setw(NUMBER_OF_DIGITS_MAX) 
        << std::setfill('0') 
        << node;

    return out;
}

#endif //BIG_NUMBER_CLASS_CPP