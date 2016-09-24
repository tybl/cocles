#ifndef COCLES_IDENTIFIER_HPP
#define COCLES_IDENTIFIER_HPP

#include <ostream>
#include <string>

struct identifier_t {
   identifier_t(unsigned long new_value);

   std::string
   ToString(void) const;

   unsigned long
   operator () (void) const;

   bool
   operator == (const identifier_t &other) const;

private:
   unsigned long value;
};

std::ostream& operator << (std::ostream &out, const identifier_t &id);

#endif // COCLES_IDENTIFIER_HPP
