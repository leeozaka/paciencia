#ifndef WINDOW_H
#define WINDOW_H

#include "c.h"
#include "decks.h"
#include "piles.h"
#include <stdint.h>

enum CARDS_PLACE {
  DECK,
  GAME_1,
  GAME_2,
  GAME_3,
  GAME_4,
  TABLE_1,
  TABLE_2,
  TABLE_3,
  TABLE_4,
  TABLE_5,
  TABLE_6,
  TABLE_7
};

typedef struct text_info info_t;

typedef struct CARD_PLACING {
  uint8_t x;
  uint8_t y;
} card_placing_t;

typedef struct CARD_SIZE {
  uint8_t width;
  uint8_t height;
} card_size_t;

typedef struct WINDOW_TEXT_POS {
  uint8_t x;
  uint8_t y;
} wtext;

info_t bootstrap_window();
uint8_t window_verify();
void window_draw(pile_t *table_decks, pile_t *game_decks, pile_t *discard_deck,
                 const char **cval, const char **csuit);
void window_print_msg(const char *msg, COLORS color);

#endif
