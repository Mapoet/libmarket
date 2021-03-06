// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "fees_tests.h"
#include "market/fees.h"
#include "assert.h"

static int eq(double n1, double n2) {
  return n1 <= (n2 + 0.00001) && (n1 >= n2 - 0.00001);
}

void fees_tests() {
  puts("fees test:");

  assert(eq(fees_app(5000), 15));
  assert(eq(fees_app(7000), 15.24));
  assert(eq(fees_app(23000), 17.16));
  assert(eq(fees_app(25000), 17.4));
  assert(eq(fees_app(27000), 34.89));
  assert(eq(fees_app(35000), 43.85));
  assert(eq(fees_app(50000), 59.9));
  assert(eq(fees_app(75000), 86.45));
  assert(eq(fees_app(140000), 153.4));
  assert(eq(fees_app(150000), 163.4));

  puts("  Finished");
}

