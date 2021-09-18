#ifndef TERM_STRUCT_H
#define TERM_STRUCT_H

#include <cstdint>
#include <string>
#include <iostream>

struct Term
{
public:
    double coefficient;
    double exponent;
    std::string variable;

    Term(void);
    Term(double coefficient, double exponent, const std::string& variable = "x");

    bool operator==(const Term& that) const;
    //exponent value takes precedence as the more
    //important value in a term, therefore, if
    //comparing two terms and one has larger exponent,
    //no matter the coefficient, the term with the
    //larger exponent is treated as "larger"
    bool operator>(const Term& that) const;
    bool operator>=(const Term& that) const;
    bool operator<(const Term& that) const;
    bool operator<=(const Term& that) const;
};

std::ostream& operator<<(std::ostream& out, const Term& a_term);

#endif //TERM_STRUCT_H