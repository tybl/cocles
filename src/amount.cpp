#include "amount.hpp"

amount_t::amount_t(std::string new_value)
   : value(std::stod(new_value))
{
}

std::string amount_t::ToString(void) const {
   return std::to_string(value);
}

std::ostream& operator << (std::ostream &out, const amount_t &a) {
   return out << a.ToString();
}

amount_t operator + (amount_t lhs, const amount_t &rhs) {
   return lhs += rhs;
}
