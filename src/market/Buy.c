// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/*.+
struct: Buy
  nick: size_t: _uint
  money: double: _double2
*/

#include "dm/dm.h"
#include "market/Buy.h"
#include "market/fees.h"

/*.-.*/
struct buy_Buy {
  size_t nick;
  double money;
};

Buy *buy_new(size_t nick, double money) {
  Buy *this = MALLOC(Buy);
  this->nick = nick;
  this->money = money;
  return this;
}

inline
size_t buy_nick(Buy *this) {
  return this->nick;
}

inline
double buy_money(Buy *this) {
  return this->money;
}

Json *buy_serialize(Buy *this) {
  Arr/*Json*/ *serial = arr_new();
  jarr_auint(serial, this->nick);
  jarr_adouble(serial, this->money, 2);
  return json_warray(serial);
}

Buy *buy_restore(Json *s) {
  Arr/*Json*/ *serial = json_rarray(s);
  Buy *this = MALLOC(Buy);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->money = jarr_gdouble(serial, i++);
  return this;
}
/*.-.*/

void buy_do(
  size_t *stocks_r,
  double *cost_r,
  Buy *this,
  double price
) {
  if (price < 0.01) THROW "price (%2f) < 0.01", price _THROW

  double order_money = this->money;
  double money =  order_money - fees_app(order_money);
  size_t stocks = (size_t)(money / price);

  for (;;) {
    double cost = stocks * price;
    cost += fees_app(cost);
    if (cost <= order_money) {
      *stocks_r = stocks;
      *cost_r = cost;
      return;
    }
    --stocks;
  }
}
