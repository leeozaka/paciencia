#include "piles.h"
#include "cards.h"
#include "decks.h"

#include <stdint.h>
#include <stdio.h>

void pile_init(pile_t *p) { p->head = -1; }

void pile_push(pile_t *p, card_t c) { p->card[++p->head] = c; }

card_t pile_pop(pile_t *p) { return p->card[p->head--]; }

card_t pile_peek(pile_t p) { return p.card[p.head]; }

uint8_t pile_empty(pile_t *p) { return p->head == -1; }

uint8_t pile_full(pile_t *p) { return p->head == CARD_COUNT - 1; }

void pile_print(pile_t p, const char *t[], const char *s[]) {
  while (!pile_empty(&p)) {
    card_t aux = pile_pop(&p);
    printf("%s %s\n", t[aux.value], s[aux.suit]);
  }
}
