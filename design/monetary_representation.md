# Considerations
* Arithmetic
    * Addition: The majority of operations will be addition (may be addition of negative values)
    * Rounding: Only necessary for multiplication or division
* Fractionals: Most monetary representations have whole units and fractional units
* Currency representation/codes

# Standards
* IEEE 754-2008 Decimal Floating-Point Arithmetic specification: http://www.dsc.ufcg.edu.br/~cnum/modulos/Modulo2/IEEE754_2008.pdf
* ISO 4217 International Standard for currency codes: https://www.iso.org/iso-4217-currency-codes.html, https://en.wikipedia.org/wiki/ISO_4217
* ISO 3166 International Standard for country codes: https://www.iso.org/iso-3166-country-codes.html, https://en.wikipedia.org/wiki/ISO_3166

# Implementations
Intel Decimal Floating-Point Math Library (implementation of IEEE 754-2008): https://software.intel.com/en-us/articles/intel-decimal-floating-point-math-library

A C/C++ library for money and ISO 4217 currency codes: https://github.com/castedo/isomon, http://ref.castedo.com/isomon

Yet Another C++ Money class: http://www.di-mare.com/adolfo/p/money.htm

moneycpp: https://github.com/mariusbancila/moneycpp, https://mariusbancila.ro/blog/2018/11/13/moneycpp-a-cpp-library-for-handling-monetary-values/

Not sure what quantitative finance is, but here is a library for it: https://www.quantlib.org/

Also, it appears that the C++ standard added I/O Manipulation functions for money: https://en.cppreference.com/w/cpp/io/manip/get_money

A code review of a simple money class: https://codereview.stackexchange.com/questions/109821/simple-c-class-for-storing-and-manipulations-with-money
