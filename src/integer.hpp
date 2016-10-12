#ifndef TBL_INTEGER_HPP
#define TBL_INTEGER_HPP

#include <cmath>
#include <limits>
#include <string>

namespace tbl {

struct integer_t {

   integer_t(long value);

   integer_t(std::string value)
      : mantissa()
      , buffer_length(/*log10(strlen(value))*/)
      , mantissa_length()
   {
      // ceil(log10(num)) == num_string.length()
      constexpr double log10_max_uint32 = 9.632959861146281183071;
      size_t requested_length = static_cast<size_t>(std::lround(value.length() / log10_max_uint32));
      allocate_at_least(requested_length);
      for (auto c : value) {
         if (isdigit(c)) {
            multiply_mantissa_by_ui(10);
            add_to_mantissa_at_index_ui(0, static_cast<uint32_t>(c - '0'));
         } else {
            break;
         }
      }
   }

   bool operator==(const integer_t& other) const;

   integer_t& operator+=(integer_t other);

   integer_t& operator-=(integer_t other);

   integer_t& operator*=(integer_t other);

   integer_t& operator/=(integer_t other);

   bool is_negative() const;

//private:

   void multiply_mantissa_by_ui(uint32_t value) {
      // multiply from msb to lsb so we don't multiply the carries
      for (size_t i = buffer_length; 0 < i; --i) {
         multiply_mantissa_at_index_by_ui(i - 1, value);
      }
   }

   void multiply_mantissa_at_index_by_ui(size_t index, uint32_t value) {
      uint64_t result = static_cast<uint64_t>(mantissa[index]) * value;
      mantissa[index] = result & 0xFFFFFFFF;
      uint32_t next_value = result >> 32;
      if (0 != next_value) {
         add_to_mantissa_at_index_ui(index + 1, next_value);
      }
   }

   void add_to_mantissa_at_index_ui(size_t index, uint32_t value) {
      if (buffer_length < index) throw nullptr;
      if (buffer_length == index) {
         allocate_at_least(buffer_length + 1);
      }
      uint32_t carry;
      mantissa[index] = __builtin_addc(mantissa[index], value, 0, &carry);
      if (0 < carry) {
         add_to_mantissa_at_index_ui(index + 1, carry);
      }
   }

   void allocate_at_least(size_t requested_length) {
      // Do nothing if requested_length <= buffer_length
      if (buffer_length < requested_length) {
         auto temp = std::make_unique<uint32_t[]>(requested_length);
         if (mantissa) {
            for (size_t i = 0; i < buffer_length; ++i) {
               temp[i] = mantissa[i];
            }
         }
         buffer_length = requested_length;
         mantissa.swap(temp);
      }
   }

   std::unique_ptr<uint32_t[]> mantissa;
   size_t buffer_length; // Tracks the length of the allocated buffer
   size_t mantissa_length; // Tracks index of the most significant bit
   //bool is_negative;
};

} // namespace tbl

#endif // TBL_INTEGER_HPP
