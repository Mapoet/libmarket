// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/* .+.
struct:Quote
  open: double: _double 4
  close: double: _double 4
  max: double: _double 4
  min: double: _double 4
  vol: size_t: _uint
*/

#include "market/Quote.h"
#include "dmc/std.h"


/*.-.*/
#include "dmc/ct/Ajson.h"

struct quote_Quote {
  double open;
  double close;
  double max;
  double min;
  size_t vol;
};

Quote *quote_new(
  double open,
  double close,
  double max,
  double min,
  size_t vol
) {
  Quote *this = MALLOC(Quote);
  this->open = open;
  this->close = close;
  this->max = max;
  this->min = min;
  this->vol = vol;
  return this;
}

double quote_open(Quote *this) {
  XNULL(this)
  return this->open;
}

double quote_close(Quote *this) {
  XNULL(this)
  return this->close;
}

double quote_max(Quote *this) {
  XNULL(this)
  return this->max;
}

double quote_min(Quote *this) {
  XNULL(this)
  return this->min;
}

size_t quote_vol(Quote *this) {
  XNULL(this)
  return this->vol;
}

Json *quote_to_json(Quote *this) {
  XNULL(this)
  Ajson *serial = ajson_new();
  jarr_adouble(serial, this->open,  4);
  jarr_adouble(serial, this->close,  4);
  jarr_adouble(serial, this->max,  4);
  jarr_adouble(serial, this->min,  4);
  jarr_auint(serial, this->vol);
  return json_warray(serial);
}

Quote *quote_from_json(Json *js) {
  XNULL(js)
  Ajson *serial = json_rarray(js);
  Quote *this = MALLOC(Quote);
  size_t i = 0;
  this->open = jarr_gdouble(serial, i++);
  this->close = jarr_gdouble(serial, i++);
  this->max = jarr_gdouble(serial, i++);
  this->min = jarr_gdouble(serial, i++);
  this->vol = jarr_guint(serial, i++);
  return this;
}
/*.-.*/

