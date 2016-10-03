#ifndef COCLES_DECIMAL_HPP
#define COCLES_DECIMAL_HPP

#include <string>

struct decimal_t {
   decimal_t(double value, uint8_t decimal_places);
   decimal_t(std::string value);
   bool operator == (const decimal_t &other) const;
   decimal_t& operator += (decimal_t other);
   decimal_t& operator -= (decimal_t other);
   decimal_t& operator *= (const decimal_t &other);
   std::string to_string(void) const;
   decimal_t& round(uint8_t decimal_places);
   void shrink(void);
private:
   int64_t m_value;
   int64_t m_factor;
};
#endif // COCLES_DECIMAL_HPP
