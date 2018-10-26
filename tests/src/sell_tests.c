// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "sell_tests.h"
#include "dmc/Dec.h"
#include "market/Sell.h"
#include "market/fees.h"
#include "assert.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void sell_tests() {
  puts("Sell test:");

  Sell *s1 = sell_new(1, 21556);
  assert(sell_nick(s1) == 1);
  assert(sell_stocks(s1) == 21556);
  Js *js = sell_to_js_new(s1);
  assert(str_eq((char *)js, "[1,21556,false,0.0000]"));

  double r = sell_do(s1, 1.2);
  double vstocks = 21556 * 1.2;
  assert(eq(r, vstocks - fees_app(vstocks)));

  sell_free(s1);
  free(js);

  puts("  Finished");
}

