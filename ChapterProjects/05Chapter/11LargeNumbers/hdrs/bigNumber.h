#ifndef BIG_NUMBER_CLASS_H
#define BIG_NUMBER_CLASS_H

#include <list>
#include <iostream>
#include <cstdint>

template<int64_t Tbase>
class BigNumber
{
static_assert(Tbase > 1, "Base must be larger than 1!!!!");

public:
    BigNumber(void);
    BigNumber(int64_t normal_number);
    BigNumber(const std::initializer_list<int64_t>& digits);
    BigNumber(const BigNumber& that) = default;
    BigNumber(BigNumber&& that);

    //state mutating methods
    BigNumber<Tbase>& operator=(const BigNumber& that) = default;
    BigNumber<Tbase>& operator=(BigNumber&& that);
    BigNumber<Tbase>& operator+=(const BigNumber& that);
    BigNumber<Tbase>& operator-=(const BigNumber& that);
    BigNumber<Tbase>& operator*=(const BigNumber& that);
    BigNumber<Tbase>& operator/=(const BigNumber& that);
    BigNumber<Tbase>& operator%=(const BigNumber& that);
    BigNumber<Tbase>& operator&=(const BigNumber& that);
    BigNumber<Tbase>& operator|=(const BigNumber& that);
    BigNumber<Tbase>& operator^=(const BigNumber& that);
    BigNumber<Tbase>& operator<<=(const BigNumber& that);
    BigNumber<Tbase>& operator>>=(const BigNumber& that);
    BigNumber<Tbase>& operator++(void);
    BigNumber<Tbase>& operator++(int);
    BigNumber<Tbase>& operator--(void);
    BigNumber<Tbase>& operator--(int);

    //const methods
    BigNumber<Tbase> operator+(const BigNumber& that) const;
    BigNumber<Tbase> operator-(const BigNumber& that) const;
    BigNumber<Tbase> operator*(const BigNumber& that) const;
    BigNumber<Tbase> operator/(const BigNumber& that) const;
    BigNumber<Tbase> operator%(const BigNumber& that) const;
    BigNumber<Tbase> operator~(void) const;
    BigNumber<Tbase> operator&(const BigNumber& that) const;
    BigNumber<Tbase> operator|(const BigNumber& that) const;
    BigNumber<Tbase> operator^(const BigNumber& that) const;
    BigNumber<Tbase> operator<<(const BigNumber& that) const;
    BigNumber<Tbase> operator>>(const BigNumber& that) const;
    bool operator==(const BigNumber& that) const;
    bool operator!=(const BigNumber& that) const;
    bool operator>(const BigNumber& that) const;
    bool operator>=(const BigNumber& that) const;
    bool operator<(const BigNumber& that) const;
    bool operator<=(const BigNumber& that) const;

    //display
    template<int64_t base>
    friend std::ostream& operator<<(std::ostream& out, const BigNumber<base>& number);

private:
    std::list<int64_t> number_list;
    bool isNegative;
};

#include "bigNumber.cpp"

#endif //BIG_NUMBER_CLASS_H