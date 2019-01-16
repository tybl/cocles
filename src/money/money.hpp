/*****************************************************************************
ISC License
Copyright (c) 2016, Timothy Lyons
Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.
THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/
#ifndef COCLES_MONEY_MONEY_HPP
#define COCLES_MONEY_MONEY_HPP

namespace money {

struct money_t {

   money_t(void);

   explicit money_t(const std::string new_value);

   money_t(money_t const& other);

   std::string to_string(void) const;

   money_t& operator = (money_t other);

   money_t& operator == (money_t const& other) const;

   money_t& operator += (money_t const& other);

   money_t& operator -= (money_t const& other);

   money_t& operator %= (money_t const& other);

   money_t& operator /= (money_t const& other);

private:
   int64_t value;
}; // struct money_t

money_t operator + (money_t, money_t);
money_t operator - (money_t, money_t);
money_t operator * (money_t, int);
money_t operator * (int, money_t); // Can't implement in class
money_t operator % (money_t, int);
money_t operator % (money_t, money_t);
money_t operator / (money_t, int);
int operator / (money_t, money_t);

} // namespace money

#endif // COCLES_MONEY_MONEY_HPP

