// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "buyTest.h"
#include "dmc/std.h"
#include "dmc/Dec.h"
#include "market/Buy.h"
#include "market/fees.h"
#include "assert.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void buy_test() {
  puts("Buy test:");

  size_t n1 = buy_calc(20000.0, 1.2);
  Buy *b1 = buy_new_limited(1, n1, 1.2);
  assert(buy_nick(b1) == 1);
  assert(buy_stocks(b1) == n1);
  assert(eq(buy_price(b1), 1.2));
  Json *js = buy_to_json(b1);
  assert(str_eq((char *)js, str_printf("[1,%d,true,1.2000]", n1)));

  double cost = buy_do(b1, 1.2);
  assert(cost < 20000);
  double vstocks1 = (buy_stocks(b1) + 1) * 1.2;
  assert(vstocks1 + fees_app(vstocks1) > 20000);
  double vstocks = buy_stocks(b1) * 1.2;
  assert(eq(vstocks + fees_app(vstocks), cost));

  puts("  Finished");
}
