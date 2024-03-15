#include "decks.h"
#include "cards.h"
#include <stdint.h>
#include <stdlib.h>

void deck_init(card_t deck[]) {
  int i = 0;

  for (uint8_t s = 0; s < 4; s++) {
    for (uint8_t r = 0; r < 13; r++) {
      deck[i].suit = s;
      deck[i].value = r;
      i++;
    }
  }
  deck_shuffle(deck);
}

void deck_shuffle(card_t deck[]) {
  for (int i = 0; i < 52; i++) {
    int j = rand() % 52;
    card_t t = deck[i];
    deck[i] = deck[j];
    deck[j] = t;
  }
}

void deck_populate(pile_t decks[], card_t deck[]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < i + 1; j++) {
      pile_push(&decks[i], deck[i + j]);
    }
  }
}
