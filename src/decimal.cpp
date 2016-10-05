#include "decimal.hpp"

static
int64_t
ipow10(uint8_t exponent) {
   int64_t result = 1;
   switch (exponent) {
      case 0: result = 1LL; break;
      case 1: result = 10LL; break;
      case 2: result = 100LL; break;
      case 3: result = 1000LL; break;
      case 4: result = 10000LL; break;
      case 5: result = 100000LL; break;
      case 6: result = 1000000LL; break;
      case 7: result = 10000000LL; break;
      case 8: result = 100000000LL; break;
      case 9: result = 1000000000LL; break;
      case 10: result = 10000000000LL; break;
      case 11: result = 100000000000LL; break;
      case 12: result = 1000000000000LL; break;
      case 13: result = 10000000000000LL; break;
      case 14: result = 100000000000000LL; break;
      case 15: result = 1000000000000000LL; break;
      case 16: result = 10000000000000000LL; break;
      case 17: result = 100000000000000000LL; break;
      case 18: result = 1000000000000000000LL; break;
   }
   return result;
}

static
int
ilog10(int64_t value) {
   int result = 1;
   switch (value) {
      case 1LL: result = 0; break;
      case 10LL: result = 1; break;
      case 100LL: result = 2; break;
      case 1000LL: result = 3; break;
      case 10000LL: result = 4; break;
      case 100000LL: result = 5; break;
      case 1000000LL: result = 6; break;
      case 10000000LL: result = 7; break;
      case 100000000LL: result = 8; break;
      case 1000000000LL: result = 9; break;
      case 10000000000LL: result = 10; break;
      case 100000000000LL: result = 11; break;
      case 1000000000000LL: result = 12; break;
      case 10000000000000LL: result = 13; break;
      case 100000000000000LL: result = 14; break;
      case 1000000000000000LL: result = 15; break;
      case 10000000000000000LL: result = 16; break;
      case 100000000000000000LL: result = 17; break;
      case 1000000000000000000LL: result = 18; break;
   }
   return result;
}

decimal_t::decimal_t(double value, uint8_t decimal_places)
   : m_value(static_cast<int64_t>(value * ipow10(decimal_places))),
   m_factor(ipow10(decimal_places))
{
   // Intentionally left blank
}

decimal_t::decimal_t(std::string value) {
}

bool
decimal_t::operator == (const decimal_t &other) const {
   return ((m_value == other.m_value) && (m_factor == other.m_factor));
}

decimal_t&
decimal_t::operator += (decimal_t other) {
   const bool fewer = (m_factor < other.m_factor);
   m_value = m_value * (fewer ? other.m_factor / m_factor : 1)
     + other.m_value * (fewer ? 1 : m_factor / other.m_factor);
   m_factor = (fewer ? other.m_factor : m_factor);
   return *this;
}

decimal_t&
decimal_t::operator -= (decimal_t other) {
   const bool fewer = (m_factor < other.m_factor);
   m_value = m_value * (fewer ? other.m_factor / m_factor : 1)
     - other.m_value * (fewer ? 1 : m_factor / other.m_factor);
   m_factor = (fewer ? other.m_factor : m_factor);
   return *this;
}

decimal_t&
decimal_t::operator *= (const decimal_t &other) {
   m_value *= other.m_value;
   m_factor *= other.m_factor;
   return *this;
}

std::string
decimal_t::to_string(void) const {
   auto decimal_places = ilog10(m_factor);
   if (1 == m_factor) {
      return std::to_string(m_value);
   }
   static_assert(sizeof(long) == sizeof(int64_t), "long is not 64 bits");
   long whole = m_value / m_factor;
   long fraction = m_value % m_factor;
   fraction *= (0 < whole) ? 1 : -1;
   const int ret_val = std::snprintf(nullptr, 0, "%ld.%0*ld", whole, decimal_places, fraction);
   size_t size = (0 < ret_val) ? static_cast<size_t>(ret_val) + 1 : 0UL;
   std::string result(size + 1, '\0');
   std::snprintf(&result[0], size, "%ld.%0*lu", whole, decimal_places, fraction);
   return result;
}

decimal_t&
decimal_t::round(uint8_t decimal_places) {
   int64_t factor = ipow10(decimal_places);
   if (m_factor > factor) {
      m_value /= (m_factor / factor) / 10;
      m_value += 5;
      m_value /= 10;
   } else {
      m_value *= factor / m_factor;
   }
   m_factor = factor;
   return *this;
}

void
decimal_t::shrink(void) {
   while (m_value && m_factor && (0 == m_value % 10)) {
      m_value /= 10;
      m_factor /= 10;
   }
}
