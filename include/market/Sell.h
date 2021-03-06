// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#ifndef MARKET_SELL_H
  #define MARKET_SELL_H

#include "dmc/std.h"

/*--*/

///
typedef struct sell_Sell Sell;

///
void sell_free(Sell *this);

///
int sell_nick(Sell *this);

///
int sell_stocks(Sell *this);

///
int sell_limited(Sell *this);

///
double sell_price(Sell *this);

///
Js *sell_to_js_new(Sell *this);

///
Sell *sell_from_js_new(Js *js);

/*--*/

/// sell_new makes a marker order. Its sell_limit() value is false and
/// its sell_price() value is 0
Sell *sell_new(int nick, int stocks);

/// buy_new_limit makes a limit order. Its sell_limit() value is true and
/// its sell_price() value is 'price'
Sell *sell_new_limited(int nick, int stocks, double price);

/// seell_do makes sell and returns its income.
double sell_do(Sell *this, double price);

/// seel_income returns net income for selling a number of stocks ('stocks')
double sell_income(int stocks, double price);

#endif
