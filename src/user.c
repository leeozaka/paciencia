#include "user.h"
#include "cards.h"
#include "decks.h"
#include "piles.h"

#include "c.h"
#include <ctype.h>
#include <stdint.h>

uint8_t user_deck_input_handler() {
  fflush(stdin);
  switch (tolower(_getche())) {
  case '1':
    return DECK_GAME;
  case '2':
    return DECK_TABLE;
  case '3':
    return DECK_DISCARD;
  default:
    return DECK_ERR;
  }
}

// get user input and return the value fixed
uint8_t user_choice_handler() {
  fflush(stdin);
  switch (tolower(_getche())) {
  case '1':
    return C_GAME;
  case '2':
    return C_TABLE;
  case 's':
    return C_YES;
  case 'n':
    return C_NO;
  default:
    return C_ERR;
  }
}

// get user input and return the value fixed
int user_get_input() {
  fflush(stdin);
  switch (tolower(_getche())) {
  case 'q':
    return UI_EXIT;
  case 'm':
    return UI_PICK;
  case 'l':
    return UI_LOOK;
  case 'x':
    return UI_CHEAT;
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
inline uint8_t user_game_card_handler(int pe, pile_t *game_decks) {
  if ((pe < 0 || pe > 3) || pile_empty(&game_decks[pe]))
    return 1;

  return 0;
}

// check if user got from a valid pile position
// then check if the pile is empty
inline uint8_t user_table_card_handler(int pe, pile_t *table_decks) {
  if ((pe < 0 || pe > 6) || pile_empty(&table_decks[pe]))
    return 1;

  return 0;
}

// check if user got a valid pile position
// check if the pile is empty
// check if the card order is valid
inline uint8_t user_dest_handler_game(int pd, pile_t *game_decks, card_t c) {
  if (pd < 0 || pd > 3)
    return 1;

  if (pile_empty(&game_decks[pd]))
    return c.value == ACE ? 0 : 1;

  if (c.value > pile_peek(game_decks[pd]).value)
    return 0;

  return 1;
}

inline uint8_t user_dest_handler_table(int pd, pile_t *table_decks, card_t c) {
  if (pd < 0 || pd > 6)
    return 1;

  if (pile_empty(&table_decks[pd]))
    return 0;

  if (c.value - 1 == pile_peek(table_decks[pd]).value)
    return 0;

  return 1;
}
