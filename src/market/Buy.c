// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/*.+
struct: Buy
  nick: size_t: _uint
  stocks: size_t: _uint
  price: double: _double4
*/

#include "dmc/all.h"
#include "market/Buy.h"
#include "market/fees.h"

/*.-.*/
struct buy_Buy {
  size_t nick;
  size_t stocks;
  double price;
};

Buy *buy_new(size_t nick, size_t stocks, double price) {
  Buy *this = MALLOC(Buy);
  this->nick = nick;
  this->stocks = stocks;
  this->price = price;
  return this;
}

inline
size_t buy_nick(Buy *this) {
  return this->nick;
}

inline
size_t buy_stocks(Buy *this) {
  return this->stocks;
}

inline
double buy_price(Buy *this) {
  return this->price;
}

Json *buy_serialize(Buy *this) {
  Arr/*Json*/ *serial = arr_new();
  jarr_auint(serial, this->nick);
  jarr_auint(serial, this->stocks);
  jarr_adouble(serial, this->price, 4);
  return json_warray(serial);
}

Buy *buy_restore(Json *s) {
  Arr/*Json*/ *serial = json_rarray(s);
  Buy *this = MALLOC(Buy);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->stocks = jarr_guint(serial, i++);
  this->price = jarr_gdouble(serial, i++);
  return this;
}
/*.-.*/

double buy_do(Buy *this) {
  double r = ((double) this->stocks) * this->price;
  return r + fees_app(r);
}

size_t buy_calc(double money, double price) {
  if (price < 0.01) THROW "price (%2f) < 0.01", price _THROW

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
