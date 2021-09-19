#include "polynomial.h"
#include <cmath>
#include <algorithm>

Polynomial::Polynomial(void)
    : internal_polynomial(1) //have just one zero
{}
//EOF

Polynomial::Polynomial(std::initializer_list<Term>&& basic_polynomial) noexcept
    {*this = std::move(basic_polynomial);}
//EOF

Polynomial::Polynomial(std::initializer_list<double>&& coefficients) noexcept
    {*this = std::move(coefficients);}
//EOF

Polynomial::Polynomial(Polynomial&& that) noexcept
    : internal_polynomial(std::move(that.internal_polynomial))
{}
//EOF

Polynomial& Polynomial::operator=(std::initializer_list<Term>&& basic_polynomial) noexcept
{
    internal_polynomial.reserve(basic_polynomial.size());
    for (const Term& single_term : basic_polynomial)
        internal_polynomial.push_back(single_term);
    return *this;
}
//EOF

Polynomial& Polynomial::operator=(std::initializer_list<double>&& coefficients) noexcept
{
    uint64_t expo = coefficients.size() - 1;

    internal_polynomial.reserve(coefficients.size());
    for (double coeff : coefficients)
        internal_polynomial.push_back({coeff, (double)expo--});

    return *this;
}
//EOF

Polynomial& Polynomial::operator=(Polynomial&& that) noexcept
{
    this->internal_polynomial = std::move(that.internal_polynomial);
    return *this;
}
//EOF

Term& Polynomial::getTerm(uint64_t term_number) noexcept(false)
    {return internal_polynomial.at(term_number);}
//EOF

const Polynomial& Polynomial::simplify(void) noexcept
{
    this->sort();
    this->mergeLikeTerms();

    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& that) noexcept
{
    internal_polynomial.reserve(
        internal_polynomial.size() + that.internal_polynomial.size()
    );

    for (const Term& term : that.internal_polynomial)
        internal_polynomial.push_back(term);

    this->simplify();
    return *this;
}

uint64_t Polynomial::getNumberOfTerms(void) const noexcept
    {return internal_polynomial.size();}
//EOF

const Term& Polynomial::getTerm(uint64_t term_number) const noexcept(false)
    {return internal_polynomial.at(term_number);}
//EOF

double Polynomial::evaluate(double value) const noexcept
{
    double total = 0;
    for (uint64_t i = 0; i < internal_polynomial.size(); i++)
        total += std::pow(value, internal_polynomial[i].exponent) 
                * internal_polynomial[i].coefficient;
    return total;
}
//EOF

double Polynomial::operator()(double value) const noexcept
    {return this->evaluate(value);}
//EOF

Polynomial Polynomial::operator+(const Polynomial& that) const noexcept
{
    Polynomial output_poly;

    output_poly.internal_polynomial.reserve(
        internal_polynomial.size() + that.internal_polynomial.size()
    );

    for (const Term& term : internal_polynomial)
        output_poly.internal_polynomial.push_back(term);

    for (const Term& term : that.internal_polynomial)
        output_poly.internal_polynomial.push_back(term);

    output_poly.simplify();
    return output_poly;
}
//EOF

void Polynomial::sort(void) noexcept
{
    std::sort(
        internal_polynomial.begin(),
        internal_polynomial.end(),
        [](const Term& lhs, const Term& rhs) -> bool {return lhs > rhs;}
    );
}
//EOF

void Polynomial::mergeLikeTerms(void) noexcept
{   //this->sort() must have been called before calling this function
    uint64_t numberOfSurvivingTerms = 0;

    for (uint64_t i = 0; i < internal_polynomial.size(); numberOfSurvivingTerms++)
    {
        Term& surviving_term = internal_polynomial[numberOfSurvivingTerms];

        surviving_term = internal_polynomial[i]; //shift actual term to the space occupied by surving_term
        for
        (
            i += 1; //go to the term after surviving term
            i < internal_polynomial.size()
            && internal_polynomial[i].exponent == surviving_term.exponent;
            i++ //only place where "i" is incremented
        )
            surviving_term.coefficient += internal_polynomial[i].coefficient;
    }

    internal_polynomial.resize(numberOfSurvivingTerms);
}
//EOF

std::ostream& operator<<(std::ostream& out, const Polynomial& poly) noexcept
{
    if (poly.getNumberOfTerms() > 0)
    {
        for (uint64_t i = 0; i < poly.getNumberOfTerms() - 1; i++)
            out << poly.getTerm(i) << " + ";
        out << poly.getTerm(poly.getNumberOfTerms() - 1);
    }

    return out;
}
//EOF