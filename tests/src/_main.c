// Copyright 04-Feb-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "dmc/std.h"

#include "quote_tests.h"
#include "fees_tests.h"
#include "buy_tests.h"
#include "sell_tests.h"
#include "pf_tests.h"

int main (int argc, char **argv) {

  puts("marketTest. v201810\n");
  sys_init("marketTest");
/*
  quote_tests();
  fees_tests();
  buy_tests();
  sell_tests();*/
  pf_tests();

  sys_end();
  return(0);
}
