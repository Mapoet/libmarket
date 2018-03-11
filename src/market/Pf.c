// Copyright 17-Feb-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include <dmc/all.h>
#include "market/Pf.h"

/*.+
struct: Pf_entry
  nick: size_t: _uint
  stocks: size_t: _uint
  price:double: _double4
*/

/*.-.*/
struct pf_entry_Pf_entry {
  size_t nick;
  size_t stocks;
  double price;
};

Pf_entry *pf_entry_new(size_t nick, size_t stocks, double price) {
  Pf_entry *this = MALLOC(Pf_entry);
  this->nick = nick;
  this->stocks = stocks;
  this->price = price;
  return this;
}

inline
size_t pf_entry_nick(Pf_entry *this) {
  return this->nick;
}

inline
size_t pf_entry_stocks(Pf_entry *this) {
  return this->stocks;
}

inline
double pf_entry_price(Pf_entry *this) {
  return this->price;
}

Json *pf_entry_serialize(Pf_entry *this) {
  Arr/*Json*/ *serial = arr_new();
  jarr_auint(serial, this->nick);
  jarr_auint(serial, this->stocks);
  jarr_adouble(serial, this->price, 4);
  return json_warray(serial);
}

Pf_entry *pf_entry_restore(Json *s) {
  Arr/*Json*/ *serial = json_rarray(s);
  Pf_entry *this = MALLOC(Pf_entry);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->stocks = jarr_guint(serial, i++);
  this->price = jarr_gdouble(serial, i++);
  return this;
}
/*.-.*/

inline
Pf *pf_new(void) {
  return arr_new();
}

inline
Pf *pf_copy(Pf *this) {
  /**/FNM(copy, Pf_entry, e) {
  /**/  return pf_entry_new(e->nick, e->stocks, e->price);
  /**/}_FN
  return it_to(it_map(it_from(this), copy));
}

void pf_add(Pf *this, size_t nick, size_t stocks, double price) {
  bool new = true;
  EACH(this, Pf_entry, e) {
    if (e->nick == nick) {
      e->price = (e->price * e->stocks + stocks * price) / (e->stocks + stocks);
      e->stocks += stocks;
      new = false;
      break;
    }
  }_EACH
  if (new) {
    arr_add(this, pf_entry_new(nick, stocks, price));
  }
}

void pf_remove(Pf *this, size_t nick, size_t stocks) {
  size_t n = 0;
  bool error = true;
  int index = -1;
  EACH(this, Pf_entry, e) {
    if (e->nick == nick) {
      if (e->stocks == stocks) {
        index = _i;
        error = false;
      } else if (e->stocks >= stocks) {
        e->stocks -= stocks;
        error = false;
      } else {
        n = e->stocks;
      }
      break;
    }
  }_EACH
  if (error) {
    THROW
      "Try of selling %d stocks when only are %d in portfolio",
      stocks, n
    _THROW
  }
  if (index != -1) {
    arr_remove(this, index);
  }
}

Pf_entry *pf_get(Pf *this, size_t nick) {
  EACH(this, Pf_entry, e) {
    if (e->nick == nick) {
      return e;
    }
  }_EACH
  return 0;
}

size_t *pf_nicks(Pf *this) {
  size_t size = arr_size(this);
  size_t *r = ATOMIC(sizeof(size_t) * size);
  size_t *p = r;
  Pf_entry **es = (Pf_entry **)arr_es(this);
  RANGE0(i, size) {
    *p++ = (*es++)->nick;
  }_RANGE
  return r;
}

inline
size_t pf_size(Pf *this) {
  return arr_size(this);
}

Json *pf_serialize(Pf *this) {
  Arr/*Json*/ *jr = arr_new();

  EACH(this, Pf_entry, pe) {
    arr_add(jr, pf_entry_serialize(pe));
  }_EACH

  return json_warray(jr);
}

Pf *pf_restore(Json *s) {
  Pf *this = arr_new();
  EACH(json_rarray(s), Json, js) {
    arr_add(this, pf_entry_restore(js));
  }_EACH
  return this;
}
