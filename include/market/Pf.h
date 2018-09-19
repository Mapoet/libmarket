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
typedef struct pf_entry_Pf_entry Pf_entry;

///
Pf_entry *pf_entry_new(size_t nick, size_t stocks, double price);

///
size_t pf_entry_nick(Pf_entry *this);

///
size_t pf_entry_stocks(Pf_entry *this);

///
double pf_entry_price(Pf_entry *this);

///
Json *pf_entry_to_json(Pf_entry *this);

///
Pf_entry *pf_entry_from_json(Json *s);

/*.-.*/

///
typedef Arr/*Pf_entry*/ Pf;

///
Pf *pf_new(void);

///
Pf *pf_copy(Pf *this);

///
void pf_add(Pf *this, size_t nick, size_t stocks, double price);

///
void pf_remove(Pf *this, size_t nick, size_t stocks);

/// pf_get returns the entry of a nick or NULL if it does not exist.
Pf_entry *pf_get(Pf *this, size_t nick);

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


