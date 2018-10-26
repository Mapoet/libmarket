// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#include "market/Quote.h"

/* .
Quote:serial
  open: double:: _d4
  close: double:: _d4
  max: double:: _d4
  min: double:: _d4
  vol: int
*/

/*--*/

struct quote_Quote {
  double open;
  double close;
  double max;
  double min;
  int vol;
};

Quote *quote_new(
  double open,
  double close,
  double max,
  double min,
  int vol
) {
  Quote *this = malloc(sizeof(Quote));
  this->open = open;
  this->close = close;
  this->max = max;
  this->min = min;
  this->vol = vol;
  return this;
}

void quote_free(Quote *this) {
  free(this);
};

double quote_open(Quote *this) {
  return this->open;
}

double quote_close(Quote *this) {
  return this->close;
}

double quote_max(Quote *this) {
  return this->max;
}

double quote_min(Quote *this) {
  return this->min;
}

int quote_vol(Quote *this) {
  return this->vol;
}

Js *quote_to_js_new(Quote *this) {
  // Arr[Js]
  Arr *a = arr_new(free);
  arr_push(a, js_wd_new(this->open, 4));
  arr_push(a, js_wd_new(this->close, 4));
  arr_push(a, js_wd_new(this->max, 4));
  arr_push(a, js_wd_new(this->min, 4));
  arr_push(a, js_wi_new(this->vol));
  Js *r = js_wa_new(a);
  arr_free(a);
  return r;
}

Quote *quote_from_js_new(Js *js) {
  Quote *this = malloc(sizeof(Quote));
  // Arr[Js]
  Arr *a = js_ra_new(js);
  int i = 0;
  this->open = js_rd(arr_get(a, i++));
  this->close = js_rd(arr_get(a, i++));
  this->max = js_rd(arr_get(a, i++));
  this->min = js_rd(arr_get(a, i++));
  this->vol = js_ri(arr_get(a, i++));
  arr_free(a);
  return this;
}

/*--*/
