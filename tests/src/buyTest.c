// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "buyTest.h"
#include "dm/dm.h"
#include "market/Buy.h"
#include "market/fees.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void buy_test() {
  puts("Buy test:");

  Buy *b1 = buy_new(1, 20000.0);
  assert(buy_nick(b1) == 1);
  assert(eq(buy_money(b1), 20000));
  Json *js = buy_serialize(b1);
  assert(!strcmp(js, "[1,20000.00]"));

  uint stocks;
  double cost;
  buy_do(&stocks, &cost, b1, 1.2);
  assert(cost < 20000);
  double vstocks1 = (stocks + 1) * 1.2;
  assert(vstocks1 + fees_app(vstocks1) > 20000);
  double vstocks = stocks * 1.2;
  assert(eq(vstocks + fees_app(vstocks), cost));

  puts("  Finished");
}
