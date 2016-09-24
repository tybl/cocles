#include "money.hpp"

#include <iostream>

money_t::money_t(std::string new_value) {
   mpz_init(value);
}

money_t::money_t(double new_value) {
   mpz_init_set_d(value, new_value * 100);
}

money_t::money_t(const money_t &other) {
   mpz_init_set(value, other.value);
}

money_t::~money_t(void) {
   mpz_clear(value);
}

std::string money_t::ToString(void) const {
   std::string result(mpz_sizeinbase(value, 10) + 3, '\0');
   mpz_get_str(&result.front(), 10, value);
   // TODO: Insert decimal place
   return result;
}

money_t& money_t::operator = (money_t other) {
   mpz_swap(value, other.value);
   return *this;
}

money_t& money_t::operator += (const money_t &other) {
   mpz_add(value, value, other.value);
   return *this;
}

std::ostream& operator << (std::ostream &out, const money_t &a) {
   return out << a.ToString();
}

money_t operator + (money_t lhs, const money_t &rhs) {
   return lhs += rhs;
}
