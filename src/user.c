#include "user.h"
#include "piles.h"

#include "c.h"
#include <ctype.h>
#include <stdint.h>

// get user input and return the value fixed
uint8_t user_choice_handler() {
  fflush(stdin);
  switch (tolower(_getch())) {
  case '1':
    return C_GAME;
  case '2':
    return C_TABLE;
  default:
    return C_ERR;
  }
}

// get user input and return the value fixed
int user_get_input() {
  fflush(stdin);
  switch (tolower(_getch())) {
  case 'q':
    return UI_EXIT;
  case 'm':
    return UI_PICK;
  case 'l':
    return UI_LOOK;
  default:
    return UI_INVALID;
  }
}

// get user input and return the value fixed
inline int8_t user_input_handler() {
  uint8_t i;
  fflush(stdin);

  i = _getche();
  if (!isdigit(i)) {
    return -1;
  }

  i = (tolower(i)) - 48;
  i -= 1;

  return i;
}

// check if user got from a valid pile position
// then check if the pile is empty
inline uint8_t user_card_handler(int pe, pile_t *table_decks) {
  if ((pe < 0 || pe > 6) || pile_empty(&table_decks[pe])) {
    return 1;
  }

  return 0;
}

// check if user got a valid pile position
// check if the pile is empty
// check if the card order is valid
inline uint8_t user_dest_handler_game(int pd, pile_t *game_decks, card_t c) {
  if (pd < 0 || pd > 3)
    return 1;

  if (pile_empty(&game_decks[pd]))
    return 0;

  if (c.value == pile_peek(game_decks[pd]).value - 1)
    return 0;

  return 1;
}

inline uint8_t user_dest_handler_table(int pd, pile_t *table_decks, card_t c) {
  if (pd < 0 || pd > 6)
    return 1;

  if (pile_empty(&table_decks[pd]))
    return 0;

  if (c.value == pile_peek(table_decks[pd]).value - 1)
    return 0;

  return 1;
}
