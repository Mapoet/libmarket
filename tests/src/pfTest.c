// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "pfTest.h"
#include "dmc/std.h"
#include "dmc/Dec.h"
#include "market/Pf.h"
#include "assert.h"

#define eq(a, b) dec_eq_gap(a, b, 0.00001)

void pf_test() {
  puts("Pf test:");

  Pf *pf1 = pf_new();
  assert(arr_size(pf1) == 0);
  pf_add(pf1, 0, 5, 1.2);
  assert(arr_size(pf1) == 1);
  assert(pf_entry_stocks(pf_get(pf1, 0)) == 5);
  assert(eq(pf_entry_price(pf_get(pf1, 0)), 1.2));

  Pf *pf2 = pf_copy(pf1);
  pf_add(pf2, 0, 10, 0.9);
  pf_add(pf2, 1, 10, 3.5);

  assert(arr_size(pf1) == 1);
  assert(pf_stocks(pf1, 0) == 5);
  assert(arr_size(pf2) == 2);
  assert(pf_entry_stocks(pf_get(pf2, 0)) == 15);
  assert(pf_entry_stocks(pf_get(pf2, 1)) == 10);

  assert(str_eq((char *)pf_to_json(pf1), "[[0,5,1.2000]]"));
  assert(str_eq((char *)pf_to_json(pf2), "[[0,15,1.0000],[1,10,3.5000]]"));

  Pf *pf3 = pf_from_json(pf_to_json(pf2));
  assert(str_eq((char *)pf_to_json(pf3), "[[0,15,1.0000],[1,10,3.5000]]"));

  pf_remove(pf3, 1, 10);
  assert(str_eq((char *)pf_to_json(pf3), "[[0,15,1.0000]]"));

  pf_remove(pf3, 0, 7);
  assert(str_eq((char *)pf_to_json(pf3), "[[0,8,1.0000]]"));

  size_t *nicks = pf_nicks(pf2);
  RANGE0(i, pf_size(pf2)) {
    assert(nicks[i] == i);
  }_RANGE

  puts("  Finished");
}
