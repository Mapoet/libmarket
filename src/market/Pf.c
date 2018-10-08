// Copyright 17-Feb-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "market/Pf.h"
#include <dmc/std.h>

#define TY PfEntry
#define FN pfEntry
#include "dmc/tpl/topt.c"
#undef TY
#undef FN

/* .+.
struct: PfEntry
  nick: size_t: _uint
  stocks: size_t: _uint
  price:double: _double 4
*/

/*.-.*/
#include "dmc/ct/Ajson.h"

struct pfEntry_PfEntry {
  size_t nick;
  size_t stocks;
  double price;
};

PfEntry *pfEntry_new(size_t nick, size_t stocks, double price) {
  PfEntry *this = MALLOC(PfEntry);
  this->nick = nick;
  this->stocks = stocks;
  this->price = price;
  return this;
}

size_t pfEntry_nick(PfEntry *this) {
  XNULL(this)
  return this->nick;
}

size_t pfEntry_stocks(PfEntry *this) {
  XNULL(this)
  return this->stocks;
}

double pfEntry_price(PfEntry *this) {
  XNULL(this)
  return this->price;
}

Json *pfEntry_to_json(PfEntry *this) {
  XNULL(this)
  Ajson *serial = ajson_new();
  jarr_auint(serial, this->nick);
  jarr_auint(serial, this->stocks);
  jarr_adouble(serial, this->price,  4);
  return json_warray(serial);
}

PfEntry *pfEntry_from_json(Json *js) {
  XNULL(js)
  Ajson *serial = json_rarray(js);
  PfEntry *this = MALLOC(PfEntry);
  size_t i = 0;
  this->nick = jarr_guint(serial, i++);
  this->stocks = jarr_guint(serial, i++);
  this->price = jarr_gdouble(serial, i++);
  return this;
}
/*.-.*/

inline
Pf *pf_new(void) {
  return (Pf *)arr_new();
}

inline
Pf *pf_copy(Pf *this) {
  /**/FNM(copy, PfEntry, e) {
  /**/  XNULL(e)
  /**/  return pfEntry_new(e->nick, e->stocks, e->price);
  /**/}_FN
  return (Pf *)arr_from_it(it_map(arr_to_it((Arr *)this), copy));
}

void pf_add(Pf *this, size_t nick, size_t stocks, double price) {
  if (!stocks)
    THROW("") "Try of adding 0 stoks to porfolio" _THROW

  bool new = true;
  EACH(this, PfEntry, e) {
    XNULL(e)
    if (e->nick == nick) {
      e->price = (e->price * e->stocks + stocks * price) / (e->stocks + stocks);
      e->stocks += stocks;
      new = false;
      break;
    }
  }_EACH
  if (new) {
    arr_add((Arr *)this, pfEntry_new(nick, stocks, price));
  }
}

void pf_remove(Pf *this, size_t nick, size_t stocks) {
  size_t n = 0;
  bool error = true;
  int index = -1;
  EACH(this, PfEntry, e) {
    XNULL(e)
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
    THROW("")
      "Try of selling %d stocks when only are %d in portfolio",
      stocks, n
    _THROW
  }
  if (index != -1) {
    arr_remove((Arr *)this, index);
  }
}

OpfEntry *pf_get(Pf *this, size_t nick) {
  EACH(this, PfEntry, e) {
    XNULL(e)
    if (e->nick == nick) {
      return opfEntry_new(e);
    }
  }_EACH
  return opfEntry_null();
}

size_t pf_stocks(Pf *this, size_t nick) {
  OpfEntry *e = pf_get(this, nick);
  return opfEntry_is_null(e) ? 0 : opfEntry_value(e)->stocks;
}

size_t *pf_nicks(Pf *this) {
  size_t size = arr_size((Arr *)this);
  size_t *r = ATOMIC(sizeof(size_t) * size);
  size_t *p = r;
  EACH(this, PfEntry, e) {
    XNULL(e)
    *p++ = e->nick;
  }_EACH
  return r;
}

inline
size_t pf_size(Pf *this) {
  return arr_size((Arr *)this);
}

Json *pf_to_json(Pf *this) {
  Ajson *jr = ajson_new();

  EACH(this, PfEntry, pe) {
    ajson_add(jr, pfEntry_to_json(pe));
  }_EACH

  return json_warray(jr);
}

Pf *pf_from_json(Json *s) {
  Pf *this = (Pf *)arr_new();
  EACH(json_rarray(s), Json, js) {
    arr_add((Arr *)this, pfEntry_from_json(js));
  }_EACH
  return this;
}
