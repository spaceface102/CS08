#include "term.h"

Term::Term(void)
    : Term(0, 0)
{}
//EOF

Term::Term(double coefficient, double exponent)
    : coefficient(coefficient), exponent(exponent)
{}


bool Term::operator==(const Term& that) const
{
    return (exponent == that.exponent) && (coefficient == that.coefficient);
}
//EOF

bool Term::operator>(const Term& that) const
{
    return
        (exponent > that.exponent) ||
        ((exponent == that.exponent) && (coefficient > that.coefficient));
}
//EOF

bool Term::operator>=(const Term& that) const
{
    return 
        (exponent > that.exponent) ||
        ((exponent == that.exponent) && (coefficient >= that.coefficient));
}
//EOF

bool Term::operator<(const Term& that) const
{
    return 
        (exponent < that.exponent) ||
        ((exponent == that.exponent) && (coefficient < that.coefficient));
}
//EOF

bool Term::operator<=(const Term& that) const
{
    return 
        (exponent < that.exponent) ||
        ((exponent == that.exponent) && (coefficient <= that.coefficient));
}
//EOF

Term Term::operator*(const Term& that) const
{
    Term result = *this;
    result.coefficient *= that.coefficient;
    result.exponent += that.exponent;

    return result;
}

std::ostream& operator<<(std::ostream& out, const Term& a_term)
{
    if (a_term.coefficient == 0)
        return out;

    if (a_term.exponent == 0)
    {
        out << a_term.coefficient;
        return out;
    }

    if (a_term.coefficient  != 1)
        out << a_term.coefficient;

    if (a_term.exponent == 1)
    {
        out << "x";
        return out;
    }

    out << "x^" << a_term.exponent;

    return out;
}