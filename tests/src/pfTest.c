// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "pfTest.h"
#include "dm/dm.h"
#include "market/Pf.h"

void pf_test() {
  puts("Pf test:");

  Pf *pf1 = pf_new();
  assert(arr_size(pf1) == 0);
  pf_add(pf1, 0, 5);
  assert(arr_size(pf1) == 1);
  assert(pf_get(pf1, 0) == 5);

  Pf *pf2 = pf_copy(pf1);
  pf_add(pf2, 0, 10);
  pf_add(pf2, 1, 10);

  assert(arr_size(pf1) == 1);
  assert(pf_get(pf1, 0) == 5);
  assert(arr_size(pf2) == 2);
  assert(pf_get(pf2, 0) == 15);
  assert(pf_get(pf2, 1) == 10);

  assert(!strcmp(pf_serialize(pf1), "[[0,5]]"));
  assert(!strcmp(pf_serialize(pf2), "[[0,15],[1,10]]"));

  Pf *pf3 = pf_restore(pf_serialize(pf2));
  assert(!strcmp(pf_serialize(pf3), "[[0,15],[1,10]]"));

  pf_remove(pf3, 1, 10);
  assert(!strcmp(pf_serialize(pf3), "[[0,15]]"));

  size_t *nicks = pf_nicks(pf2);
  RANGE0(i, pf_size(pf2)) {
    assert(nicks[i] == i);
  }_RANGE

  puts("  Finished");
}
