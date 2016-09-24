#ifndef COCLES_AMOUNT_HPP
#define COCLES_AMOUNT_HPP

#include <ostream>
#include <string>

struct amount_t {
   amount_t(std::string new_value);
   amount_t(double new_value)
      : value(new_value)
   {
   }

   std::string ToString(void) const;

   amount_t& operator += (const amount_t &other) {
      value += other.value;
      return *this;
   }
private:
   double value;
};

std::ostream& operator << (std::ostream &out, const amount_t &a);

amount_t operator + (amount_t lhs, const amount_t &rhs);
#endif // COCLES_AMOUNT_HPP
