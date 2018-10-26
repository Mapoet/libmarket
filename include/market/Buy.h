// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#ifndef MARKET_BUY_H
  #define MARKET_BUY_H

#include "dmc/std.h"

/*--*/

///
typedef struct buy_Buy Buy;

///
void buy_free(Buy *this);

///
int buy_nick(Buy *this);

///
int buy_stocks(Buy *this);

///
int buy_limited(Buy *this);

///
double buy_price(Buy *this);

///
Js *buy_to_js_new(Buy *this);

///
Buy *buy_from_js_new(Js *js);

/*--*/

/// buy_new makes a 'marker order'. Its buy_limited() value is 'false' and
/// its buy_price() is a approximative value based in quotes of day.
Buy *buy_new(int nick, int stocks, double price);

/// buy_new_limit makes a 'limited order'. Its buy_limited() value is 'true' and
/// its buy_price() value is 'price'
Buy *buy_limited_new(int nick, int stocks, double price);

/// buy_do makes a buy and returns its cost adding fees. If the operation
/// can not be done, it returns 0.
double buy_do(Buy *this, double price);

/// buy_calc returns the number of stocks which can be bought given the
/// available money.
///   money: Money available
///   price: Price of one stock
int buy_calc(double money, double price);

#endif
