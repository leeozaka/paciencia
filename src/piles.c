#include "piles.h"
#include "cards.h"

#include <stdint.h>
#include <stdio.h>

void pile_init(pile_t *p) { p->head = -1; }

void pile_push(pile_t *p, card_t c) { p->card[++p->head] = c; }

card_t pile_pop(pile_t *p) { return p->card[p->head--]; }

card_t pile_peek(pile_t p) { return p.card[p.head]; }

uint8_t pile_empty(pile_t *p) { return p->head == -1; }

uint8_t pile_full(pile_t *p) { return p->head == 51; }

void pile_print(pile_t p, const char *t[], const char *s[]) {
  while (!pile_empty(&p)) {
    card_t aux = pile_pop(&p);
    printf("%s %s\n", t[aux.value], s[aux.suit]);
  }
}

// #include <stdio.h>
// #include <stdlib.h>
//
// void pile_init(pile_t **p) {
//   *p = (pile_t *)malloc(sizeof(pile_t));
//   (*p)->head = NULL;
//   (*p)->size = 0;
// }
//
// void pile_push(pile_t **p, card_t c) {
//   data_t *n = (data_t *)malloc(sizeof(data_t));
//   n->card = c;
//   n->next = (*p)->head;
//   (*p)->head = n;
//   (*p)->size++;
// }
//
// // POP removendo a carta e a retornando
// // em caso de devolucao de deck
// card_t pile_pop(pile_t **p) {
//   data_t *n = (*p)->head;
//
//   if (!n)
//     return (card_t){0, 0};
//
//   card_t c = n->card;
//
//   (*p)->head = n->next;
//   free(n);
//   (*p)->size--;
//   return c;
// }
//
// card_t pile_peek(pile_t **p) {
//   data_t *n = (*p)->head;
//
//   if (!n)
//     return (card_t){0, 0};
//
//   return n->card;
// }
//
// uint64_t pile_size(pile_t **p) { return (*p)->size; }
//
// void pile_clear(pile_t **p) {
//   data_t *n = (*p)->head;
//
//   while (n) {
//     data_t *t = n;
//     n = n->next;
//     free(t);
//   }
//
//   (*p)->head = NULL;
//   (*p)->size = 0;
// }
//
