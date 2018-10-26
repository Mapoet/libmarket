// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#ifndef MARKET_QUOTE_H
  #define MARKET_QUOTE_H

#include "dmc/std.h"

/*--*/

///
typedef struct quote_Quote Quote;

///
Quote *quote_new(
  double open,
  double close,
  double max,
  double min,
  int vol
);

///
void quote_free(Quote *this);

///
double quote_open(Quote *this);

///
double quote_close(Quote *this);

///
double quote_max(Quote *this);

///
double quote_min(Quote *this);

///
int quote_vol(Quote *this);

///
Js *quote_to_js_new(Quote *this);

///
Quote *quote_from_js_new(Js *js);

/*--*/

#endif
