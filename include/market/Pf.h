// Copyright 26-Oct-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

#ifndef MARKET_PF_H
  #define MARKET_PF_H

#include "dmc/std.h"
#include "dmc/Iarr.h"

///
typedef struct pf_Pf Pf;

///
Pf *pf_new(void);

///
void pf_free(Pf *this);

///
Pf *pf_copy_new(Pf *this);

///
void pf_add(Pf *this, int nick, int stocks, double price);

///
int pf_size(Pf *this);

/// Returns stocks and price of a nick. if this does not exist, it returns
/// stocks = 0.
void pf_get(int *stocks, double *price, Pf *this, int nick);

/// Returns the stock number of a nick or 0 if this does not exist.
int pf_stocks(Pf *this, int nick);

///  Returns an array with the nicks of 'this'.
Iarr *pf_nicks_new(Pf *this);

/// Removes a 'stocks' number of nick.
void pf_remove_stocks(Pf *this, int nick, int stocks);

/// Removes all stocks of nick.
void pf_remove(Pf *this, int nick);

///
Js *pf_to_js_new(Pf *this);

///
Pf *pf_from_js_new(Js *s);

#endif
