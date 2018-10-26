// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "quote_tests.h"
#include "market/Quote.h"
#include "assert.h"

void quote_tests() {
  puts("Quote test:");

  Quote *q = quote_new(1.20,1.40,1.50,1.10,33);
  Js *js = quote_to_js_new(q);
  assert(str_eq(
    (char *)js,
    "[1.2000,1.4000,1.5000,1.1000,33]"
  ));
  assert(quote_open(q) == 1.20);
  assert(quote_close(q) == 1.4);
  assert(quote_max(q) == 1.5);
  assert(quote_min(q) == 1.1);
  assert(quote_vol(q) == 33);

  Quote *q2 = quote_from_js_new(js);
  assert(quote_open(q2) == 1.20);
  assert(quote_close(q2) == 1.4);
  assert(quote_max(q2) == 1.5);
  assert(quote_min(q2) == 1.1);
  assert(quote_vol(q2) == 33);

  quote_free(q);
  quote_free(q2);
  free(js);

  puts("  Finished");
}

