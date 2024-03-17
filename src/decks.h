#ifndef DECKS_H
#define DECKS_H

#include "cards.h"
#include "piles.h"

#define CARD_COUNT 52

typedef struct DECK_TYPE {
  card_t card[CARD_COUNT];
  int head;
} deck_t;

void deck_init(deck_t deck[]);
void deck_shuffle(deck_t *deck);
void deck_populate(deck_t decks[], pile_t table_deck[]);
card_t deck_get_card(deck_t deck);
card_t deck_pop(deck_t *deck);
uint8_t deck_is_empty(deck_t deck);

#endif
