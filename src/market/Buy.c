// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/* .+.
struct: @Buy
  nick: size_t: _uint
  stocks: size_t: _uint
  limit: bool: _bool
  price: double: _double 4
*/

#include "dmc/std.h"
#include "market/Buy.h"
#include "market/fees.h"

/*.-.*/
#include "dmc/ct/Ajson.h"

struct buy_Buy {
  size_t nick;
  size_t stocks;
  bool limit;
  double price;
};

Buy *_buy_new(
  size_t nick,
  size_t stocks,
  bool limit,
  double price
) {
  Buy *this = MALLOC(Buy);
  this->nick = nick;
  this->stocks = stocks;
  this->limit = limit;
  this->price = price;
  return this;
}

size_t buy_nick(Buy *this) {
  XNULL(this)
  return this->nick;
}

size_t buy_stocks(Buy *this) {
  XNULL(this)
  return this->stocks;
}

bool buy_limit(Buy *this) {
  XNULL(this)
  return this->limit;
}

double buy_price(Buy *this) {
  XNULL(this)
  return this->price;
}

Json *buy_to_json(Buy *this) {
  XNULL(this)
  Ajson *serial = ajson_new();
  jarr_auint(serial, this->nick);
  jarr_auint(serial, this->stocks);
  jarr_abool(serial, this->limit);
  jarr_adouble(serial, this->price,  4);
  return json_warray(serial);
}

Buy *buy_from_json(Json *js) {
  XNULL(js)
  Ajson *serial = json_rarray(js);
  Buy *this = MALLOC(Buy);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->stocks = jarr_guint(serial, i++);
  this->limit = jarr_gbool(serial, i++);
  this->price = jarr_gdouble(serial, i++);
  return this;
}
/*.-.*/

inline
Buy *buy_new(size_t nick, size_t stocks) {
  return _buy_new(nick, stocks, false, 0);
}

inline
Buy *buy_new_limit(size_t nick, size_t stocks, double price) {
  return _buy_new(nick, stocks, true, price);
}

double buy_do(Buy *this) {
  double r = ((double) this->stocks) * this->price;
  return r + fees_app(r);
}

size_t buy_calc(double money, double price) {
  if (price < 0.01) THROW("") "price (%2f) < 0.01", price _THROW

  double order_money = money - fees_app(money);
  size_t stocks = (size_t)(order_money / price);
  for(;;) {
    double cost = stocks * price;
    cost += fees_app(cost);
    if (cost <= money) {
      return stocks;
    }
    --stocks;
  }
}
