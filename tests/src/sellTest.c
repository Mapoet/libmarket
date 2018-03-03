// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "sellTest.h"
#include "dmc/all.h"
#include "market/Sell.h"
#include "market/fees.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void sell_test() {
  puts("Sell test:");

  Sell *s1 = sell_new(1, 21556);
  assert(sell_nick(s1) == 1);
  assert(sell_stocks(s1) == 21556);
  Json *js = sell_serialize(s1);
  assert(!strcmp(js, "[1,21556]"));

  double r = sell_do(s1, 1.2);
  double vstocks = 21556 * 1.2;
  assert(eq(r, vstocks - fees_app(vstocks)));

  puts("  Finished");
}
