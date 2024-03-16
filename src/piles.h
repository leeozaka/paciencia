#include "cards.h"
#include <stdint.h>

#ifndef PILES_H
#define PILES_H

#define PILE_SIZE 52

typedef struct PILE_TYPE {
  card_t card[PILE_SIZE];
  int head;
} pile_t;

void pile_init(pile_t *p);
void pile_push(pile_t *p, card_t c);
card_t pile_pop(pile_t *p);
card_t pile_peek(pile_t p);
uint8_t pile_empty(pile_t *p);
uint64_t pile_size(pile_t *p);
void pile_clear(pile_t *p);
void pile_print(pile_t p, const char *t[], const char *s[]);
void pile_shuffle(pile_t *p);
void pile_sort(pile_t *p);

#endif
