// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Buy operation

#ifndef MARKET_BUY_H
  # define MARKET_BUY_H

#include "dmc/Json.h"

/*.-.*/

///
typedef struct buy_Buy Buy;

///
size_t buy_nick(Buy *this);

///
size_t buy_stocks(Buy *this);

///
bool buy_limit(Buy *this);

///
double buy_price(Buy *this);

///
Json *buy_serialize(Buy *this);

///
Buy *buy_restore(Json *s);

/*.-.*/

/// buy_new makes a marker order. Its buy_limit() value is false and
/// its buy_price() value is 0
Buy *buy_new(size_t nick, size_t stocks);

/// buy_new_limit makes a limit order. Its buy_limit() value is true and
/// its buy_price() value is 'price'
Buy *buy_new_limit(size_t nick, size_t stocks, double price);

/// buy_do makes a buy and returns its cost adding fees.
double buy_do(Buy *this);

/// buy_calc returns the number of stocks which can be bought given the
/// available money.
///   money: Money available
///   price: Price of one stock
size_t buy_calc(double money, double price);

#endif
