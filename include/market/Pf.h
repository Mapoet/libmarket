// Copyright 03-Mar-2018 ºDeme
// GNU General Public License - V3 <http://www.gnu.org/licenses/>

/// Pf management

#ifndef MARKET_PF_H
  # define MARKET_PF_H

#include <stdlib.h>
#include <dm/Json.h>

/*.-.*/

///
typedef struct pf_entry_Pf_entry Pf_entry;

///
Pf_entry *pf_entry_new(size_t nick, size_t stocks);

///
size_t pf_entry_nick(Pf_entry *this);

///
size_t pf_entry_stocks(Pf_entry *this);

///
Json *pf_entry_serialize(Pf_entry *this);

///
Pf_entry *pf_entry_restore(Json *s);

/*.-.*/

///
typedef Arr/*Pf_entry*/ Pf;

///
Pf *pf_new(void);

///
Pf *pf_copy(Pf *this);

///
void pf_add(Pf *this, size_t nick, size_t stocks);

///
void pf_remove(Pf *this, size_t nick, size_t stocks);

/// pf_get returns the stock number of a nick.
size_t pf_get(Pf *this, size_t nick);

///  pf_nicks returns an array of size 'pf_size', with all the nicks of 'this'.
size_t *pf_nicks(Pf *this);

///
size_t pf_size(Pf *this);

///
Json *pf_serialize(Pf *this);

///
Pf *pf_restore(Json *s);

#endif


