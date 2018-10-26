// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "market/Sell.h"
#include "market/fees.h"

/* .
-Sell: serial
  nick: int
  stocks: int
  limited: int:: _b
  price: double:: _d4
*/

/*--*/

struct sell_Sell {
  int nick;
  int stocks;
  int limited;
  double price;
};

Sell *_sell_new(
  int nick,
  int stocks,
  int limited,
  double price
) {
  Sell *this = malloc(sizeof(Sell));
  this->nick = nick;
  this->stocks = stocks;
  this->limited = limited;
  this->price = price;
  return this;
}

void sell_free(Sell *this) {
  free(this);
};

int sell_nick(Sell *this) {
  return this->nick;
}

int sell_stocks(Sell *this) {
  return this->stocks;
}

int sell_limited(Sell *this) {
  return this->limited;
}

double sell_price(Sell *this) {
  return this->price;
}

Js *sell_to_js_new(Sell *this) {
  // Arr[Js]
  Arr *a = arr_new(free);
  arr_push(a, js_wi_new(this->nick));
  arr_push(a, js_wi_new(this->stocks));
  arr_push(a, js_wb_new(this->limited));
  arr_push(a, js_wd_new(this->price, 4));
  Js *r = js_wa_new(a);
  arr_free(a);
  return r;
}

Sell *sell_from_js_new(Js *js) {
  Sell *this = malloc(sizeof(Sell));
  // Arr[Js]
  Arr *a = js_ra_new(js);
  int i = 0;
  this->nick = js_ri(arr_get(a, i++));
  this->stocks = js_ri(arr_get(a, i++));
  this->limited = js_rb(arr_get(a, i++));
  this->price = js_rd(arr_get(a, i++));
  arr_free(a);
  return this;
}

/*--*/

Sell *sell_new(int nick, int stocks) {
  return _sell_new(nick, stocks, 0, 0);
}

Sell *sell_new_limited(int nick, int stocks, double price) {
  return _sell_new(nick, stocks, 1, price);
}

double sell_do(Sell *this, double price) {
  if (this->limited && price < this->price) {
    return 0;
  }
  return sell_income(this->stocks, price);
}

double sell_income(int stocks, double price) {
  if (price < 0.01) FAIL(str_f_new("price (%2f) < 0.01", price))

  double inc = stocks * price;
  return inc - fees_app(inc);
}
