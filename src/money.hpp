#ifndef COCLES_MONEY_HPP
#define COCLES_MONEY_HPP

#include <ostream>
#include <string>
#include <gmp.h>

struct money_t {
   money_t(std::string new_value);

   money_t(double new_value);

   money_t(const money_t &other);

   ~money_t(void);

   std::string ToString(void) const;

   money_t& operator = (money_t other);

   money_t& operator += (const money_t &other);
private:
   mpz_t value;
};

std::ostream& operator << (std::ostream &out, const money_t &a);

money_t operator + (money_t lhs, const money_t &rhs);
#endif // COCLES_MONEY_HPP
