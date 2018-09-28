// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Pf management

#ifndef MARKET_PF_H
  # define MARKET_PF_H

#include <stdlib.h>
#include <dmc/Json.h>

/*.-.*/

#include "dmc/Json.h"

///
typedef struct pfEntry_PfEntry PfEntry;

///
PfEntry *pfEntry_new(size_t nick, size_t stocks, double price);

///
size_t pfEntry_nick(PfEntry *this);

///
size_t pfEntry_stocks(PfEntry *this);

///
double pfEntry_price(PfEntry *this);

///
Json *pfEntry_to_json(PfEntry *this);

///
PfEntry *pfEntry_from_json(Json *s);

/*.-.*/

///
typedef struct pf_Pf Pf;

///
Pf *pf_new(void);

///
Pf *pf_copy(Pf *this);

///
void pf_add(Pf *this, size_t nick, size_t stocks, double price);

///
void pf_remove(Pf *this, size_t nick, size_t stocks);

/// pf_get returns the entry of a nick or NULL if it does not exist.
PfEntry *pf_get(Pf *this, size_t nick);

/// pf_get returns the stock number of a nick.
size_t pf_stocks(Pf *this, size_t nick);

///  pf_nicks returns an array of size 'pf_size', with all the nicks of 'this'.
size_t *pf_nicks(Pf *this);

///
size_t pf_size(Pf *this);

///
Json *pf_to_json(Pf *this);

///
Pf *pf_from_json(Json *s);

#endif


