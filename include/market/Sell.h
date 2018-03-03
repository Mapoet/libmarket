// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Sell operation

#ifndef MARKET_SELL_H
  # define MARKET_SELL_H

#include "dm/Json.h"

/*.-.*/

///
typedef struct sell_Sell Sell;

///
Sell *sell_new(size_t nick, size_t stocks);

///
size_t sell_nick(Sell *this);

///
size_t sell_stocks(Sell *this);

///
Json *sell_serialize(Sell *this);

///
Sell *sell_restore(Json *s);

/*.-.*/

/// seell_do makes sell and returns its income.
double sell_do(Sell *this, double price);

/// seel_income returns net income for selling 'stocks'
double sell_income(size_t stocks, double price);

#endif
