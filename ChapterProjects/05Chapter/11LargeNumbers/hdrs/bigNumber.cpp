#ifndef BIG_NUMBER_CLASS_CPP
#define BIG_NUMBER_CLASS_CPP

#include "bigNumber.h"
#include <cmath>
#include <iomanip>
#include <cassert>

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(void)
    : number_list(1), isNegative(false) //initialize to size 1, fill with 0
{}

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(int64_t normal_number)
{
    isNegative = (normal_number < 0);
    while (normal_number > 0)
    {
        number_list.push_front(normal_number % Tbase);
        normal_number /= Tbase;
    }
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(const std::initializer_list<std::int64_t>& digits)
    : isNegative(false)
{
    for (std::int64_t one_digit : digits)
    {
        assert(std::abs(one_digit) < Tbase && "Each digit must be less than the define base!");
        number_list.push_back(std::abs(one_digit));
        isNegative = ((one_digit < 0) || isNegative);
    }
        
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>::BigNumber(BigNumber&& that)
    : number_list(std::move(that.number_list)), isNegative(that.isNegative)
{}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator=(BigNumber&& that)
{
    this->number_list = std::move(that.number_list);
    this->isNegative = that.isNegative;

    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator+=(const BigNumber& that)
{
    *this = std::move((*this) + that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator-=(const BigNumber& that)
{
    *this = std::move((*this) - that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator*=(const BigNumber& that)
{
    *this = std::move((*this) * that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator/=(const BigNumber& that)
{
    *this = std::move((*this) / that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator%=(const BigNumber& that)
{
    *this = std::move((*this) % that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator&=(const BigNumber& that)
{
    *this = std::move((*this) & that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator|=(const BigNumber& that)
{
    *this = std::move((*this) | that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator^=(const BigNumber& that)
{
    *this = std::move((*this) ^ that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator<<=(const BigNumber& that)
{
    *this = std::move((*this) << that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator>>=(const BigNumber& that)
{
    *this = std::move((*this) >> that);
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator++(void)
{
    *this = std::move((*this) + BigNumber<Tbase>{1});
    return *this;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator++(int)
{
    BigNumber<Tbase> temp = *this;
    ++(*this);
    return temp;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator--(void)
{
    *this = std::move((*this) - BigNumber<Tbase>{1});
    return *this;
}
//EOF


template<std::int64_t Tbase>
BigNumber<Tbase>& BigNumber<Tbase>::operator--(int)
{
    BigNumber<Tbase> temp = *this;
    --(*this);
    return temp;
}
//EOF






template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator+(const BigNumber& that) const
{
    //for now only working with positive numbers

    if (*this == BigNumber<Tbase>{0})
        return that;
    else if (that == BigNumber<Tbase>{0})
        return *this;

    BigNumber<Tbase> result;
    std::list<int64_t> number_list;
    
    std::list<int64_t>::const_reverse_iterator thisDigit = this->number_list.rbegin();
    std::list<int64_t>::const_reverse_iterator thatDigit = that.number_list.rbegin();
    bool carry = false;
    for (; thisDigit != this->number_list.rend() && thatDigit != that.number_list.rend(); ++thisDigit, ++thatDigit)
    {
        number_list.push_front((*thatDigit + *thisDigit + carry) % Tbase);
        carry = ((*thatDigit + *thisDigit + carry) >= Tbase);
    }

    //this was a bigger number
    for (; thisDigit != this->number_list.rend(); ++thisDigit)
    {
        number_list.push_front((*thisDigit + carry) % Tbase);
        carry = ((*thisDigit + carry) >= Tbase);
    }
    //that was a bigger number
    for (; thatDigit != that.number_list.rend(); ++thatDigit)
    {
        number_list.push_front((*thatDigit + carry) % Tbase);
        carry = ((*thatDigit + carry) >= Tbase);
    }

    //if there was a carry that persisted all the way through, add it to the front
    if (carry)
        number_list.push_front(carry);

    result.number_list = std::move(number_list);
    return result;    
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator-(const BigNumber& that) const
{
    BigNumber<Tbase> result;

    if (that == BigNumber<Tbase>{0})
        return *this;
    else if (*this == BigNumber<Tbase>{0})
    {
        result = that;
        result.isNegative = !that.isNegative;
        return result;
    }

    //the if statement also ensures that
    //*this will be greater than or equal to that for the
    //rest of the function
    if (*this < that)
    {
        //this assuming *this and that are both positive
        BigNumber<Tbase> result = that.operator-(*this);
        result.isNegative = true;
        return result;
    }

    std::list<int64_t> number_list;
    std::list<int64_t>::const_reverse_iterator thisDigit = this->number_list.rbegin();
    std::list<int64_t>::const_reverse_iterator thatDigit = that.number_list.rbegin();
    uint64_t internal_result;
    bool borrow = false;

    for (; thatDigit != that.number_list.rend(); ++thisDigit, ++thatDigit)
    {
        if (*thisDigit - borrow < *thatDigit)
        {
            internal_result = ((*thisDigit) + Tbase) - *thatDigit - borrow;
            borrow = true;
        }
        else
        {
            internal_result = *thisDigit - *thatDigit - borrow;
            borrow = false;
        }
        number_list.push_front(internal_result);
    }

    //carry over the rest of the digits
    for (; thisDigit != this->number_list.rend(); ++thisDigit)
    {
        if (*thisDigit - borrow < 0)
        {
            internal_result = ((*thisDigit) + Tbase) - borrow;
            borrow = true;
        }
        else
        {
            internal_result = *thisDigit - borrow;
            borrow = false;
        }

        number_list.push_front(internal_result);
    }

    //ensure that there are no leading zeros!
    while (number_list.front() == 0)
        number_list.pop_front();

    result.number_list = std::move(number_list);
    return result;
}
//EOF

//For next version maybe consider implementing Karatsuba's algorithim
//For even faster execution, it might be a good idea to implement some sort
//of Algorithim that uses a FFT.
template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator*(const BigNumber& that) const
{
    BigNumber<Tbase> result{0};
    const BigNumber<Tbase>* incrementor;
    const BigNumber<Tbase>* countUpTo;

    if (*this > that)
    {
        incrementor = this;
        countUpTo = &that;
    }
    else
    {
        incrementor = &that;
        countUpTo = this;
    }

    for (BigNumber<Tbase>i{0}; i < *countUpTo; ++i)
        result += *incrementor;
    
    //if signs are different, isNegative is set to true
    result.isNegative = (that.isNegative ^ this->isNegative);

    return result;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator/(const BigNumber& that) const
{
    BigNumber<Tbase> result{0};
    BigNumber<Tbase> currentNumber = *this;

    if (*this < that)
        return BigNumber<Tbase>{0};
    else if (*this == that)
        return BigNumber<Tbase>{1};

    BigNumber<Tbase> zero{0};
    while (currentNumber > zero)
        {currentNumber -= that; ++result;}

    if (currentNumber == BigNumber<Tbase>{0})
        return result;
    else
        return result - BigNumber<Tbase>{1};
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator%(const BigNumber& that) const
{
    if (that == BigNumber<Tbase>{1})
        return BigNumber<Tbase>{0};
    if (that == BigNumber<Tbase>{2})
        return BigNumber<Tbase>{(this->number_list.back()) % 2}; //check if even or odd quickly
    if (that > *this)
        return *this;

    BigNumber<Tbase> currentNumber = *this;

    while (currentNumber > that)
        currentNumber -= that;

    if (currentNumber == BigNumber<Tbase>{0})
        return BigNumber<Tbase>{0};
    else
        return currentNumber;
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
        temp *= BigNumber<Tbase>{2};
    return temp;
}
//EOF

template<std::int64_t Tbase>
BigNumber<Tbase> BigNumber<Tbase>::operator>>(const BigNumber& that) const
{
    BigNumber<Tbase> temp = *this;
    for (BigNumber<Tbase> i{0}; i < that; ++i)
        temp /= BigNumber<Tbase>{2};
    return temp;
}
//EOF

template<std::int64_t Tbase>
bool BigNumber<Tbase>::operator==(const BigNumber& that) const
{
    if (this->number_list.size() != that.number_list.size())
        return false;

    if (this->isNegative ^ that.isNegative)
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
    if (this->isNegative == false && that.isNegative == true)
        return true;
    else if (this->isNegative == true && that.isNegative == false)
        return false;

    if (this->number_list.size() > that.number_list.size())
        return true;
    else if (this->number_list.size() < that.number_list.size())
        return false;
    

    //they have the same number of nodes
    auto thisNode = this->number_list.begin();
    auto thatNode = that.number_list.begin();
    bool (*compare)(int64_t, int64_t);

    if (this->isNegative)
        compare = [](int64_t lhs, int64_t rhs) -> bool {return lhs >= rhs;};
    else
        compare = [](int64_t lhs, int64_t rhs) -> bool {return lhs <= rhs;};


    for (; thisNode != this->number_list.end(); ++thisNode, ++thatNode)
    {
        if (compare(*thisNode, *thatNode))
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

    auto digit = big_number.number_list.begin();
    
    out << ((big_number.isNegative) ? "-" : "");
    out << *digit++;

    for (; digit != big_number.number_list.end(); ++digit)
        out 
        << std::setw(NUMBER_OF_DIGITS_MAX)
        << std::setfill('0')
        << *digit;

    return out;
}

#endif //BIG_NUMBER_CLASS_CPP