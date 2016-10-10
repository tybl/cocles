#ifndef TBL_INTEGER_HPP
#define TBL_INTEGER_HPP

#include <string>

namespace tbl {

struct integer_t {

   integer_t(long value);

   bool operator==(const integer_t& other) const;

   integer_t& operator+=(integer_t other);

   integer_t& operator-=(integer_t other);

   integer_t& operator*=(integer_t other);

   integer_t& operator/=(integer_t other);

   bool is_negative() const;

private:
   std::unique_ptr<unsigned long[]> mantissa;
   long size;
};

} // namespace tbl

#endif // TBL_INTEGER_HPP
