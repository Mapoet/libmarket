// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "pf_tests.h"
#include "dmc/Dec.h"
#include "market/Pf.h"
#include "assert.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void pf_tests() {
  puts("Pf test:");

  Pf *pf1 = pf_new();
  assert(pf_size(pf1) == 0);
  pf_add(pf1, 0, 5, 1.2);
  assert(pf_size(pf1) == 1);
  int stocks;
  double price;
  pf_get(&stocks, &price, pf1, 0);
  assert(stocks == 5);
  assert(eq(price, 1.2));

  Pf *pf2 = pf_copy_new(pf1);
  pf_add(pf2, 0, 10, 0.9);
  pf_add(pf2, 1, 10, 3.5);

  assert(pf_size(pf1) == 1);
  assert(pf_stocks(pf1, 0) == 5);
  assert(pf_size(pf2) == 2);
  assert(pf_stocks(pf2, 0) == 15);
  assert(pf_stocks(pf2, 1) == 10);

  Js *js1 = pf_to_js_new(pf1);
  Js *js2 = pf_to_js_new(pf2);
  assert(str_eq((char *)js1, "[[0,5,1.2000]]"));
  assert(str_eq((char *)js2, "[[0,15,1.0000],[1,10,3.5000]]"));

  Pf *pf3 = pf_from_js_new(js2);
  Js *js3 = pf_to_js_new(pf3);
  assert(str_eq((char *)js3, "[[0,15,1.0000],[1,10,3.5000]]"));

  pf_remove_stocks(pf3, 1, 10);
  free(js3);
  js3 = pf_to_js_new(pf3);
  assert(str_eq((char *)js3, "[[0,15,1.0000]]"));

  pf_remove_stocks(pf3, 0, 7);
  free(js3);
  js3 = pf_to_js_new(pf3);
  assert(str_eq((char *)js3, "[[0,8,1.0000]]"));

  Iarr *nicks = pf_nicks_new(pf2);
  RANGE0(i, pf_size(pf2)) {
    assert(iarr_get(nicks, i) == i);
    assert(iarr_start(nicks)[i] == i);
  }_RANGE

  pf_free(pf1);
  pf_free(pf2);
  pf_free(pf3);
  free(js1);
  free(js2);
  free(js3);
  iarr_free(nicks);

  puts("  Finished");
}

