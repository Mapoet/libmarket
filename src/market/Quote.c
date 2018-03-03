// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/*.+
struct:Quote
  open: double: _double4
  close: double: _double4
  max: double: _double4
  min: double: _double4
  vol: size_t: _uint
*/

#include "market/Quote.h"
#include "dmc/all.h"

/*.-.*/
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

inline
double quote_open(Quote *this) {
  return this->open;
}

inline
double quote_close(Quote *this) {
  return this->close;
}

inline
double quote_max(Quote *this) {
  return this->max;
}

inline
double quote_min(Quote *this) {
  return this->min;
}

inline
size_t quote_vol(Quote *this) {
  return this->vol;
}

Json *quote_serialize(Quote *this) {
  Arr/*Json*/ *serial = arr_new();
  jarr_adouble(serial, this->open, 4);
  jarr_adouble(serial, this->close, 4);
  jarr_adouble(serial, this->max, 4);
  jarr_adouble(serial, this->min, 4);
  jarr_auint(serial, this->vol);
  return json_warray(serial);
}

Quote *quote_restore(Json *s) {
  Arr/*Json*/ *serial = json_rarray(s);
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

