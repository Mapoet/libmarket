// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Buy operation

#ifndef MARKET_BUY_H
  # define MARKET_BUY_H

#include "dmc/Json.h"

/*.-.*/

#include "dmc/Json.h"

///
typedef struct buy_Buy Buy;

///
size_t buy_nick(Buy *this);

///
size_t buy_stocks(Buy *this);

///
bool buy_limited(Buy *this);

///
double buy_price(Buy *this);

///
Json *buy_to_json(Buy *this);

///
Buy *buy_from_json(Json *s);

/*.-.*/

/// buy_new makes a 'marker order'. Its buy_limited() value is 'false' and
/// its buy_price() is a approximative value based in quotes of day.
Buy *buy_new(size_t nick, size_t stocks, double price);

/// buy_new_limit makes a 'limited order'. Its buy_limited() value is 'true' and
/// its buy_price() value is 'price'
Buy *buy_new_limited(size_t nick, size_t stocks, double price);

/// buy_do makes a buy and returns its cost adding fees. If the operation
/// can not be done, it returns 0.
double buy_do(Buy *this, double price);

/// buy_calc returns the number of stocks which can be bought given the
/// available money.
///   money: Money available
///   price: Price of one stock
size_t buy_calc(double money, double price);

#endif
