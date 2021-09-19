#include "term.h"

Term::Term(void)
    : Term(0, 0)
{}
//EOF

Term::Term(double coefficient, double exponent, const std::string& variable)
    : coefficient(coefficient), exponent(exponent), variable(variable)
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

std::ostream& operator<<(std::ostream& out, const Term& a_term)
{
    out << a_term.coefficient;
    if (a_term.exponent != 0.0)
         out << a_term.variable << '^' << a_term.exponent;

    return out;
}