// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/* .+.
struct: @Sell
  nick: size_t: _uint
  stocks: size_t: _uint
  limit: bool: _bool
  price: double: _double 4
*/

#include "dmc/std.h"
#include "market/Sell.h"
#include "market/fees.h"

/*.-.*/
#include "dmc/ct/Ajson.h"

struct sell_Sell {
  size_t nick;
  size_t stocks;
  bool limit;
  double price;
};

Sell *_sell_new(
  size_t nick,
  size_t stocks,
  bool limit,
  double price
) {
  Sell *this = MALLOC(Sell);
  this->nick = nick;
  this->stocks = stocks;
  this->limit = limit;
  this->price = price;
  return this;
}

size_t sell_nick(Sell *this) {
  XNULL(this)
  return this->nick;
}

size_t sell_stocks(Sell *this) {
  XNULL(this)
  return this->stocks;
}

bool sell_limit(Sell *this) {
  XNULL(this)
  return this->limit;
}

double sell_price(Sell *this) {
  XNULL(this)
  return this->price;
}

Json *sell_to_json(Sell *this) {
  XNULL(this)
  Ajson *serial = ajson_new();
  jarr_auint(serial, this->nick);
  jarr_auint(serial, this->stocks);
  jarr_abool(serial, this->limit);
  jarr_adouble(serial, this->price,  4);
  return json_warray(serial);
}

Sell *sell_from_json(Json *js) {
  XNULL(js)
  Ajson *serial = json_rarray(js);
  Sell *this = MALLOC(Sell);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->stocks = jarr_guint(serial, i++);
  this->limit = jarr_gbool(serial, i++);
  this->price = jarr_gdouble(serial, i++);
  return this;
}
/*.-.*/

inline
Sell *sell_new(size_t nick, size_t stocks) {
  return _sell_new(nick, stocks, false, 0);
}

inline
Sell *sell_new_limit(size_t nick, size_t stocks, double price) {
  return _sell_new(nick, stocks, true, price);
}

double sell_do(Sell *this, double price) {
  if (price < 0.01) THROW("") "price (%2f) < 0.01", price _THROW

  return sell_income(this->stocks, price);
}

double sell_income(size_t stocks, double price) {
  double inc = stocks * price;
  return inc - fees_app(inc);
}
