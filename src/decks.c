#include "decks.h"
#include "cards.h"
#include <stdlib.h>

void deck_init(deck_t *deck) {
  int i = 0;
  for (int s = 0; s < 4; s++) {
    for (int v = 0; v < 13; v++) {
      deck->card[i].suit = s;
      deck->card[i].value = v;
      i++;
    }
  }
  deck->head = CARD_COUNT - 1;
  deck_shuffle(deck);
}

void deck_shuffle(deck_t *deck) {
  for (int i = 0; i < CARD_COUNT; i++) {
    int j = rand() % CARD_COUNT;
    card_t t = deck->card[i];
    deck->card[i] = deck->card[j];
    deck->card[j] = t;
  }
}

void deck_populate(deck_t *deck, pile_t table_deck[]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < i + 1; j++) {
      pile_push(&table_deck[i], deck_pop(deck));
    }
  }
}

card_t deck_pop(deck_t *deck) {
  card_t c = deck->card[deck->head];
  deck->head--;
  return c;
}

card_t deck_get_card(deck_t deck) { return deck.card[deck.head]; }
