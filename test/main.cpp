/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ISC License
*
* Copyright (c) 2019, Timothy Lyons
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
* REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
* AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
* INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
* LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
* OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
* PERFORMANCE OF THIS SOFTWARE.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest/doctest.h"

static int run_unit_tests(int argc, const char* argv[]) {
   doctest::Context context; // Initialize doctest context

   // defaults
   context.setOption("abort-after", 5);
   context.setOption("sort", "name");

   context.applyCommandLine(argc, argv);

   context.setOption("no-breaks", true);

   int result = context.run();
   if (context.shouldExit()) {
      exit(result);
   }
   return result;
}

extern "C" int main(int argc, const char* argv[]) {
   return run_unit_tests(argc, argv);
}
