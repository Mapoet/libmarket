// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Market quote of day

#ifndef MARKET_QUOTE_H
  # define MARKET_QUOTE_H

#include "Json.h"

/*.-.*/

///
typedef struct quote_Quote Quote;

///
Quote *quote_new(
  double open,
  double close,
  double max,
  double min,
  size_t vol
);

///
double quote_open(Quote *this);

///
double quote_close(Quote *this);

///
double quote_max(Quote *this);

///
double quote_min(Quote *this);

///
size_t quote_vol(Quote *this);

///
Json *quote_serialize(Quote *this);

///
Quote *quote_restore(Json *s);

/*.-.*/

#endif
