#include "user.h"
#include "piles.h"
#include <stdint.h>

int user_get_input() {
  char input;
  printf("Digite um comando: ");

  input = fgetc(stdin);

  switch (input) {
  case 'q':
    return UI_EXIT;
  case 'm':
    return UI_PICK;
  case 'l':
    return UI_LOOK;
  case 'd':
    return UI_DECK;
  default:
    return UI_INVALID;
  }
}

inline uint8_t user_card_handler(int pe, pile_t *table_decks) {
  if (pe < 1 || pe > 7 && !pile_empty(&table_decks[pe - 1]))
    return 0;
  return 1;
}

inline uint8_t user_dest_handler_game(int pd, pile_t *game_decks) {}
