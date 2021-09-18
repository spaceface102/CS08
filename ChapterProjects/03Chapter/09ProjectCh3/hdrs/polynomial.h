#ifndef POLYNOMIAL_CLASS_H
#define POLYNOMIAL_CLASS_H

#include <vector>
#include <iostream>
#include <cstdint>
#include "term.h"

class Polynomial
{
public:
    Polynomial(void);
    Polynomial(std::initializer_list<Term>&& basic_polynomial) noexcept;
    Polynomial(std::initializer_list<double>&& coefficients) noexcept;
    Polynomial(Polynomial&& that) noexcept;
    Polynomial(const Polynomial& that) noexcept = default;

    Polynomial& operator=(std::initializer_list<Term>&& basic_polynomial) noexcept;
    Polynomial& operator=(std::initializer_list<double>&& coefficients) noexcept;
    Polynomial& operator=(Polynomial&& that) noexcept;
    Polynomial& operator=(const Polynomial& that) noexcept = default;

    Term& getTerm(uint64_t term_number) noexcept(false);
    const Polynomial& sort(void) noexcept; //Greatest term on left, constant on right

    uint64_t getNumberOfTerms(void) const noexcept;
    const Term& getTerm(uint64_t term_number) const noexcept(false);
    double evaluate(double value) const noexcept;
    double operator()(double value) const noexcept; //same as evaluate

private:
    std::vector<Term> internal_polynomial;
};

std::ostream& operator<<(std::ostream& out, const Polynomial& poly) noexcept;

#endif //POLYNOMIAL_CLASS_H