// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "buy_tests.h"
#include "dmc/Dec.h"
#include "market/Buy.h"
#include "market/fees.h"
#include "assert.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void buy_tests() {
  puts("Buy test:");

  int n1 = buy_calc(20000.0, 1.2);
  Buy *b1 = buy_limited_new(1, n1, 1.2);
  assert(buy_nick(b1) == 1);
  assert(buy_stocks(b1) == n1);
  assert(eq(buy_price(b1), 1.2));
  Js *js = buy_to_js_new(b1);
  char *tmp = str_f_new("[1,%d,true,1.2000]", n1);
  assert(str_eq((char *)js, tmp));

  double cost = buy_do(b1, 1.2);
  assert(cost < 20000);
  double vstocks1 = (buy_stocks(b1) + 1) * 1.2;
  assert(vstocks1 + fees_app(vstocks1) > 20000);
  double vstocks = buy_stocks(b1) * 1.2;
  assert(eq(vstocks + fees_app(vstocks), cost));

  free(b1);
  free(js);
  free(tmp);

  puts("  Finished");
}

