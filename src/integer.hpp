#ifndef TBL_INTEGER_HPP
#define TBL_INTEGER_HPP

#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <ostream>
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

template <typename TYPE>
struct next_largest { };

template <> struct next_largest<uint8_t> { using type = uint16_t; };
template <> struct next_largest<uint16_t> { using type = uint32_t; };
template <> struct next_largest<uint32_t> { using type = uint64_t; };
template <> struct next_largest<int8_t> { using type = int16_t; };
template <> struct next_largest<int16_t> { using type = int32_t; };
template <> struct next_largest<int32_t> { using type = int64_t; };

template <typename TYPE, size_t size>
struct basic_unsigned_integer {
   static_assert(std::is_unsigned<TYPE>::value, "basic_unsigned_integer must be instantiated with an unsigned type");
   static_assert(0 < size, "basic_unsigned_integer must be instantiated with a non-zero number of limbs");

   using larger_uint = typename next_largest<TYPE>::type;

   basic_unsigned_integer() : mantissa{} { }
   basic_unsigned_integer(TYPE seed) : mantissa{ { seed } } { }
   basic_unsigned_integer(const std::string& seed) : mantissa{} {
      for (auto character : seed) {
         if (!isdigit(character)) { break; }
         operator*=(10).operator+=(static_cast<TYPE>(character - '0'));
      }
   }
   basic_unsigned_integer(const basic_unsigned_integer& other) {
      std::copy(other.mantissa.begin(), other.mantissa.end(), mantissa.begin());
   }
   basic_unsigned_integer& operator=(basic_unsigned_integer other) {
      std::swap(mantissa, other.mantissa);
      return *this;
   }
   basic_unsigned_integer& operator+=(TYPE other) {
      //std::cerr << __func__ << ": " << static_cast<uint64_t>(other) << std::endl;
      larger_uint carry = other;
      for (size_t i = 0; i < size && 0 != carry; ++i) {
         carry = add_at_index(i, carry);
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator+=(const basic_unsigned_integer& other) {
      larger_uint carry = 0;
      for (size_t i = 0; i < size; ++i) {
         carry = add_at_index(i, carry + other.mantissa[i]);
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator-=(const basic_unsigned_integer& /*other*/) {
      return *this;
   }
   basic_unsigned_integer& operator*=(TYPE other) {
      larger_uint carry = 0;
      for (size_t i = 0; i < size; ++i) {
         larger_uint overflow = multiply_at_index(i, other);
         if (0 != carry) {
            overflow += add_at_index(i, carry);
         }
         carry = overflow;
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator*=(const basic_unsigned_integer& other) {
      larger_uint carry = 0;
      for (size_t i = 0; i < size; ++i) {
         for (size_t j = 0; j < size && (i + j) < size; ++j) {
            carry += multiply_at_index(i, other.mantissa[j]);
            carry = add_at_index(i, carry);
         }
      }
      if (0 != carry) std::cerr << __LINE__ << ": carry: " << carry << std::endl;
      return *this;
   }
   basic_unsigned_integer& operator/=(const basic_unsigned_integer& /*other*/) {
      return *this;
   }
   bool operator==(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin());
   }
   bool operator!=(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin(), std::not_equal_to<TYPE>());
   }
   bool operator<=(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin(), std::less_equal<TYPE>());
   }
   bool operator>=(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin(), std::greater_equal<TYPE>());
   }
   bool operator<(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin(), std::less<TYPE>());
   }
   bool operator>(const basic_unsigned_integer& other) const {
      return std::equal(mantissa.begin(), mantissa.end(), other.mantissa.begin(), std::greater<TYPE>());
   }
private:
   TYPE multiply_at_index(size_t index, larger_uint value) {
      larger_uint result = value * mantissa[index];
      mantissa[index] = result & std::numeric_limits<TYPE>::max();
      return result >> std::numeric_limits<TYPE>::digits;
   }
   TYPE add_at_index(size_t index, larger_uint value) {
      larger_uint result = value + mantissa[index];
      mantissa[index] = result & std::numeric_limits<TYPE>::max();
      return result >> std::numeric_limits<TYPE>::digits;
   }
public:
   std::array<TYPE, size> mantissa;
};

template <typename TYPE, size_t size>
std::ostream& operator<<(std::ostream& out, const basic_unsigned_integer<TYPE, size>& value) {
   out << std::hex;
   for (auto limb : value.mantissa) {
      out << static_cast<uint64_t>(limb) << " ";
   }
   return out;
}

} // namespace tbl

using uint24_t = tbl::basic_unsigned_integer<uint8_t, 3>;
static_assert(sizeof(uint24_t) == 3, "uint24_t is not 24bits long");
using uint40_t = tbl::basic_unsigned_integer<uint8_t, 5>;
static_assert(sizeof(uint40_t) == 5, "uint40_t is not 40bits long");
using uint48_t = tbl::basic_unsigned_integer<uint16_t, 3>;
static_assert(sizeof(uint48_t) == 6, "uint48_t is not 48bits long");
using uint56_t = tbl::basic_unsigned_integer<uint8_t, 7>;
static_assert(sizeof(uint56_t) == 7, "uint56_t is not 56bits long");
using uint96_t = tbl::basic_unsigned_integer<uint32_t, 3>;
static_assert(sizeof(uint96_t) == 12, "uint96_t is not 96bits long");
using uint128_t = tbl::basic_unsigned_integer<uint32_t, 4>;
static_assert(sizeof(uint128_t) == 16, "uint128_t is not 128bits long");
using uint256_t = tbl::basic_unsigned_integer<uint32_t, 8>;
static_assert(sizeof(uint256_t) == 32, "uint256_t is not 256bits long");
using uint512_t = tbl::basic_unsigned_integer<uint32_t, 16>;
static_assert(sizeof(uint512_t) == 64, "uint512_t is not 512bits long");

#endif // TBL_INTEGER_HPP
