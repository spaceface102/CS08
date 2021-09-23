#include "polynomial.h"
#include <list>
#include <cmath>
#include <cassert>

Polynomial::Polynomial(void)
    : isSorted(false), isMerged(false)
{}
//EOF

Polynomial::Polynomial(std::initializer_list<Term>&& basic_polynomial)
    {*this = std::move(basic_polynomial);}
//EOF

Polynomial::Polynomial(std::initializer_list<double>&& coefficients)
    {*this = std::move(coefficients);}
//EOF

Polynomial& Polynomial::operator=(std::initializer_list<Term>&& basic_polynomial)
{
    for (const Term& single_term : basic_polynomial)
        internal_polynomial.push_back(single_term);
    
    isSorted = false;
    isMerged = false;

    return *this;
}
//EOF

Polynomial& Polynomial::operator=(std::initializer_list<double>&& coefficients)
{
    uint64_t expo = coefficients.size() - 1;

    for (double coeff : coefficients)
        internal_polynomial.push_back({coeff, (double)expo--});

    isSorted = false;
    isMerged = false;

    return *this;
}
//EOF

const Polynomial& Polynomial::simplify(void)
{
    if (!isSorted)
        this->sort();

    if (!isMerged)
        this->mergeLikeTerms();

    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& that)
{
    for (const Term& term : that.internal_polynomial)
        internal_polynomial.push_back(term);

    isSorted = isMerged = false;
    this->simplify();

    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& that)
{
    std::list<Term> new_polynomail;

    for (const auto& thisTerm : this->internal_polynomial)
        for (const auto& thatTerm : that.internal_polynomial)
            new_polynomail.push_back(thisTerm * thatTerm);

    this->internal_polynomial = std::move(new_polynomail);
    this->isMerged = this->isSorted = false;
    this->simplify();

    return *this;
}

double Polynomial::evaluate(double value) const
{
    double total = 0;
    for (const auto& aTerm : internal_polynomial)
        total += std::pow(value, aTerm.exponent) 
                * aTerm.coefficient;
    return total;
}
//EOF

double Polynomial::operator()(double value) const
    {return this->evaluate(value);}
//EOF

Polynomial Polynomial::operator+(const Polynomial& that) const
{
    Polynomial output_poly;
         
    output_poly.internal_polynomial = this->internal_polynomial;
    for (const Term& term : that.internal_polynomial)
        output_poly.internal_polynomial.push_back(term);

    output_poly.simplify();

    return output_poly;
}
//EOF

Polynomial Polynomial::operator*(const Polynomial& that) const
{
    Polynomial new_polynomail;

    for (const auto& thisTerm : this->internal_polynomial)
        for (const auto& thatTerm : that.internal_polynomial)
            new_polynomail.internal_polynomial.push_back(thisTerm * thatTerm);

    new_polynomail.simplify();
    return new_polynomail;
}

void Polynomial::mergeLikeTerms(void)
{  
    assert(isSorted && "Make sure to sort the internal_polynomial before merging!");
    std::list<Term> new_polynomial;
    std::list<Term>::const_iterator aTerm = internal_polynomial.begin();

    while (aTerm != internal_polynomial.end())
    {
        new_polynomial.push_back(*aTerm);
        for
        (
            ++aTerm; //go to the term after surviving term
            aTerm != internal_polynomial.end()
            && (*aTerm).exponent == new_polynomial.back().exponent;
            ++aTerm
        )
            new_polynomial.back().coefficient += (*aTerm).coefficient;
    }

    isMerged = true;
    internal_polynomial = std::move(new_polynomial);
}
//EOF

void Polynomial::sort(void)
{
    this->internal_polynomial.sort(
        [](const Term& lhs, const Term& rhs) -> bool {return lhs > rhs;}
    );
    isSorted = true;
}

std::ostream& operator<<(std::ostream& out, Polynomial& poly)
{
    if (poly.internal_polynomial.size() == 0)
        return out;

    if (!poly.isMerged || !poly.isSorted)
        poly.simplify();

    std::list<Term>::const_iterator aTerm = poly.internal_polynomial.begin();
    for (std::size_t i = 0; i < poly.internal_polynomial.size() - 1; i++, ++aTerm)
        out << *aTerm << " + ";
    out << *aTerm;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& poly)
{
    if (poly.internal_polynomial.size() == 0)
        return out;

    std::list<Term>::const_iterator aTerm = poly.internal_polynomial.begin();
    for (std::size_t i = 0; i < poly.internal_polynomial.size() - 1; i++, ++aTerm)
        out << *aTerm << " + ";
    out << *aTerm;
    return out;
}
//EOF