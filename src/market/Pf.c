// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "market/Pf.h"

/* .
PfEntry: serial
  -nick: int
  -stocks: int
  -price: double:: _d4
*/

typedef struct pf_PfEntry PfEntry;

struct pf_PfEntry {
  int nick;
  int stocks;
  double price;
};

static PfEntry *pfEntry_new(int nick, int stocks, double price) {
  PfEntry *this = malloc(sizeof(PfEntry));
  this->nick = nick;
  this->stocks = stocks;
  this->price = price;
  return this;
}

static Js *pfEntry_to_js_new(PfEntry *this) {
  // Arr[Js]
  Arr *a = arr_new(free);
  arr_push(a, js_wi_new(this->nick));
  arr_push(a, js_wi_new(this->stocks));
  arr_push(a, js_wd_new(this->price, 4));
  Js *r = js_wa_new(a);
  arr_free(a);
  return r;
}

static PfEntry *pfEntry_from_js_new(Js *js) {
  PfEntry *this = malloc(sizeof(PfEntry));
  // Arr[Js]
  Arr *a = js_ra_new(js);
  int i = 0;
  this->nick = js_ri(arr_get(a, i++));
  this->stocks = js_ri(arr_get(a, i++));
  this->price = js_rd(arr_get(a, i++));
  arr_free(a);
  return this;
}

Pf *pf_new(void) {
  return (Pf *)arr_new(free);
}

void pf_free(Pf *this) {
  arr_free((Arr *)this);
}

Pf *pf_copy_new(Pf *this) {
  Arr *r = arr_new(free);
  EACH(this, PfEntry, e)
    arr_push(r, pfEntry_new(e->nick, e->stocks, e->price));
  _EACH
  return (Pf *)r;
}

void pf_add(Pf *this, int nick, int stocks, double price) {
  if (stocks < 1) FAIL(str_f_new("Try of add %d stock", stocks))

  int not_added = 1;
  EACH(this, PfEntry, e)
    if (e->nick == nick) {
      e->price = (e->price * e->stocks + stocks * price) / (e->stocks + stocks);
      e->stocks += stocks;
      not_added = 0;
      break;
    }
  _EACH
  if (not_added) {
    arr_push((Arr *)this, pfEntry_new(nick, stocks, price));
  }
}

int pf_size(Pf *this) {
  return arr_size((Arr *)this);
}

void pf_get(int *stocks, double *price, Pf *this, int nick) {
  *stocks = 0;
  EACH(this, PfEntry, e)
    if (e->nick == nick) {
      *stocks = e->stocks;
      *price = e->price;
      break;
    }
  _EACH
}

/// Returns the stock number of a nick or NULL if it does not exist.
int pf_stocks(Pf *this, int nick) {
  EACH(this, PfEntry, e)
    if (e->nick == nick) {
      return e->stocks;
    }
  _EACH
  return 0;
}

Iarr *pf_nicks_new(Pf *this) {
  Iarr *r = iarr_new();
  EACH(this, PfEntry, e)
    iarr_push(r, e->nick);
  _EACH
  return r;
}

void pf_remove_stocks(Pf *this, int nick, int stocks) {
  int fix(PfEntry *e) { return e->nick == nick; }

  int ix = arr_index((Arr *)this, (FPRED)fix);
  if (ix != -1) {
    PfEntry *e = arr_get((Arr *)this, ix);
    if (e->stocks < stocks) {
      FAIL(str_f_new(
        "Try to remove %d stocks when there are only %d", stocks, e->stocks
      ))
    } else if (e->stocks > stocks) {
      e->stocks -= stocks;
    } else {
      arr_remove((Arr *)this, ix);
    }
  }
}

void pf_remove(Pf *this, int nick) {
  int fix(PfEntry *e) { return e->nick == nick; }

  int ix = arr_index((Arr *)this, (FPRED)fix);
  if (ix != -1) {
    arr_remove((Arr *)this, ix);
  }
}

Js *pf_to_js_new(Pf *this) {
  return arr_to_js_new((Arr *)this, (FTO)pfEntry_to_js_new);
}

Pf *pf_from_js_new(Js *s) {
  return (Pf *)arr_from_js_new(s, (FFROM)pfEntry_from_js_new, free);
}
