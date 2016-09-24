#include "money.hpp"

#include <iostream>

amount_t::amount_t(std::string new_value) {
   mpz_init(value);
}

amount_t::amount_t(double new_value) {
   mpz_init_set_d(value, new_value * 100);
}

amount_t::amount_t(const amount_t &other) {
   mpz_init_set(value, other.value);
}

amount_t::~amount_t(void) {
   mpz_clear(value);
}

std::string amount_t::ToString(void) const {
   std::string result(mpz_sizeinbase(value, 10) + 3, '\0');
   mpz_get_str(&result.front(), 10, value);
   // TODO: Insert decimal place
   return result;
}

amount_t& amount_t::operator = (amount_t other) {
   mpz_swap(value, other.value);
   return *this;
}

amount_t& amount_t::operator += (const amount_t &other) {
   mpz_add(value, value, other.value);
   return *this;
}

std::ostream& operator << (std::ostream &out, const amount_t &a) {
   return out << a.ToString();
}

amount_t operator + (amount_t lhs, const amount_t &rhs) {
   return lhs += rhs;
}
