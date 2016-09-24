#ifndef COCLES_AMOUNT_HPP
#define COCLES_AMOUNT_HPP

#include <ostream>
#include <string>
#include <gmp.h>

struct amount_t {
   amount_t(std::string new_value);

   amount_t(double new_value);

   amount_t(const amount_t &other);

   ~amount_t(void);

   std::string ToString(void) const;

   amount_t& operator = (amount_t other);

   amount_t& operator += (const amount_t &other);
private:
   mpz_t value;
};

std::ostream& operator << (std::ostream &out, const amount_t &a);

amount_t operator + (amount_t lhs, const amount_t &rhs);
#endif // COCLES_AMOUNT_HPP
