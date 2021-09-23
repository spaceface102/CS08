#ifndef POLYNOMIAL_CLASS_H
#define POLYNOMIAL_CLASS_H

#include <list>
#include <iostream>
#include <cstdint>
#include "term.h"

class Polynomial
{
public:
    Polynomial(void);
    Polynomial(std::initializer_list<Term>&& basic_polynomial);
    Polynomial(std::initializer_list<double>&& coefficients);
    Polynomial(const Polynomial& that) = default;

    Polynomial& operator=(std::initializer_list<Term>&& basic_polynomial);
    Polynomial& operator=(std::initializer_list<double>&& coefficients);
    Polynomial& operator=(const Polynomial& that) = default;

    const Polynomial& simplify(void);
    Polynomial& operator+=(const Polynomial& that);
    Polynomial& operator*=(const Polynomial& that);
    double evaluate(double value) const;
    double operator()(double value) const; //same as evaluate
    Polynomial operator+(const Polynomial& that) const;
    Polynomial operator*(const Polynomial& that) const;

    friend std::ostream& operator<<(std::ostream& out, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& out, const Polynomial& poly);

private:
    void mergeLikeTerms(void);
    void sort(void);

    std::list<Term> internal_polynomial;
    bool isSorted;
    bool isMerged;
};


#endif //POLYNOMIAL_CLASS_H