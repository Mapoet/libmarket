// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "market/Buy.h"
#include "market/fees.h"

/* .
-Buy: serial
  nick: int
  stocks: int
  limited: int:: _b
  price: double:: _d4
*/

/*--*/

struct buy_Buy {
  int nick;
  int stocks;
  int limited;
  double price;
};

Buy *_buy_new(
  int nick,
  int stocks,
  int limited,
  double price
) {
  Buy *this = malloc(sizeof(Buy));
  this->nick = nick;
  this->stocks = stocks;
  this->limited = limited;
  this->price = price;
  return this;
}

void buy_free(Buy *this) {
  free(this);
};

int buy_nick(Buy *this) {
  return this->nick;
}

int buy_stocks(Buy *this) {
  return this->stocks;
}

int buy_limited(Buy *this) {
  return this->limited;
}

double buy_price(Buy *this) {
  return this->price;
}

Js *buy_to_js_new(Buy *this) {
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

Buy *buy_from_js_new(Js *js) {
  Buy *this = malloc(sizeof(Buy));
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

Buy *buy_new(int nick, int stocks, double price) {
  return _buy_new(nick, stocks, 0, price);
}

Buy *buy_limited_new(int nick, int stocks, double price) {
  return _buy_new(nick, stocks, 1, price);
}

double buy_do(Buy *this, double price) {
  if (price < 0.01) FAIL(str_f_new("price (%2f) < 0.01", price))

  if (this->limited && price > this->price) {
    return 0;
  }
  double r = ((double) this->stocks) * price;
  return r + fees_app(r);
}

int buy_calc(double money, double price) {
  if (price < 0.01) FAIL(str_f_new("price (%2f) < 0.01", price))

  double order_money = money - fees_app(money);
  int stocks = (int)(order_money / price);
  for(;;) {
    double cost = stocks * price;
    cost += fees_app(cost);
    if (cost <= money) {
      return stocks;
    }
    --stocks;
  }
}
