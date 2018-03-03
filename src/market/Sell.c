// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/*.+
struct: Sell
  nick: size_t: _uint
  stocks: size_t: _uint
*/

#include "dmc/all.h"
#include "market/Sell.h"
#include "market/fees.h"

/*.-.*/
struct sell_Sell {
  size_t nick;
  size_t stocks;
};

Sell *sell_new(size_t nick, size_t stocks) {
  Sell *this = MALLOC(Sell);
  this->nick = nick;
  this->stocks = stocks;
  return this;
}

inline
size_t sell_nick(Sell *this) {
  return this->nick;
}

inline
size_t sell_stocks(Sell *this) {
  return this->stocks;
}

Json *sell_serialize(Sell *this) {
  Arr/*Json*/ *serial = arr_new();
  jarr_auint(serial, this->nick);
  jarr_auint(serial, this->stocks);
  return json_warray(serial);
}

Sell *sell_restore(Json *s) {
  Arr/*Json*/ *serial = json_rarray(s);
  Sell *this = MALLOC(Sell);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->stocks = jarr_guint(serial, i++);
  return this;
}
/*.-.*/

double sell_do(Sell *this, double price) {
  if (price < 0.01) THROW "price (%2f) < 0.01", price _THROW

  return sell_income(this->stocks, price);
}

double sell_income(size_t stocks, double price) {
  double inc = stocks * price;
  return inc - fees_app(inc);
}
