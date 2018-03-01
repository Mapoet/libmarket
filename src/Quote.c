// Copyright 01-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/*.+
+struct:Quote
  open: double: double
  close: double: double
  max: double: double
  min: double: double
  vol: size_t: _uint
*/

#include "Quote.h"
#include "dm.h"

static Json *double_serialize(double n) {
  return json_wdouble(n, 4);
}

static double double_restore(Json *serial) {
  return json_rdouble(serial);
}

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
  arr_add(serial, double_serialize(this->open));
  arr_add(serial, double_serialize(this->close));
  arr_add(serial, double_serialize(this->max));
  arr_add(serial, double_serialize(this->min));
  jarr_auint(serial, this->vol);
  return json_warray(serial);
}

Quote *quote_restore(Json *s) {
  Arr/*Json*/ *serial = json_rarray(s);
  Quote *this = MALLOC(Quote);
  size_t i = 0;
  this->open = double_restore(arr_get(serial, i++));
  this->close = double_restore(arr_get(serial, i++));
  this->max = double_restore(arr_get(serial, i++));
  this->min = double_restore(arr_get(serial, i++));
  this->vol = jarr_guint(serial, i++);
  return this;
}
/*.-.*/

