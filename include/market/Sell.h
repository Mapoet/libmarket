// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Sell operation

#ifndef MARKET_SELL_H
  # define MARKET_SELL_H

#include "dmc/Json.h"

/*.-.*/

#include "dmc/Json.h"

///
typedef struct sell_Sell Sell;

///
size_t sell_nick(Sell *this);

///
size_t sell_stocks(Sell *this);

///
bool sell_limited(Sell *this);

///
double sell_price(Sell *this);

///
Json *sell_to_json(Sell *this);

///
Sell *sell_from_json(Json *s);

/*.-.*/

/// sell_new makes a marker order. Its sell_limit() value is false and
/// its sell_price() value is 0
Sell *sell_new(size_t nick, size_t stocks);

/// buy_new_limit makes a limit order. Its sell_limit() value is true and
/// its sell_price() value is 'price'
Sell *sell_new_limited(size_t nick, size_t stocks, double price);

/// seell_do makes sell and returns its income.
double sell_do(Sell *this, double price);

/// seel_income returns net income for selling a number of stocks ('stocks')
double sell_income(size_t stocks, double price);

#endif
