// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Buy operation

#ifndef MARKET_BUY_H
  # define MARKET_BUY_H

#include "dm/Json.h"

/*.-.*/

///
typedef struct buy_Buy Buy;

///
Buy *buy_new(size_t nick, double money);

///
size_t buy_nick(Buy *this);

///
double buy_money(Buy *this);

///
Json *buy_serialize(Buy *this);

///
Buy *buy_restore(Json *s);

/*.-.*/

/// buy_do makes buy and returns actual stocks bought (stocks_r) and its cost
/// (cost_r)
void buy_do(
  size_t *stocks_r,
  double *cost_r,
  Buy *this,
  double price
);

#endif
