#ifndef DECKS_H

#include "cards.h"
#include "piles.h"

void deck_init(card_t deck[]);
void deck_shuffle(card_t deck[]);
void deck_populate(pile_t decks[], card_t deck[]);

#endif
