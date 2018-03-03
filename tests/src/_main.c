// Copyright 04-Feb-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "dm/dm.h"

#include "quoteTest.h"
#include "feesTest.h"
#include "buyTest.h"
#include "sellTest.h"
#include "pfTest.h"

int main (int argc, char **argv) {

  puts("marketTest. v201803\n");
  sys_init("marketTest");

  quote_test();
  fees_test();
  buy_test();
  pf_test();

  return(0);
}
