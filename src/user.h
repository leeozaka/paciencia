#ifndef USER_H
#define USER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piles.h"

enum USER_INPUT { UI_EXIT, UI_PICK, UI_LOOK, UI_DECK, UI_INVALID };
enum CHOICES { C_ERR, C_GAME, C_TABLE, C_YES, C_NO };

int user_get_input();
int8_t user_input_handler();
uint8_t user_choice_handler();
uint8_t user_card_handler(int pe, pile_t *table_decks);
uint8_t user_dest_handler_game(int pd, pile_t *game_decks, card_t c);
uint8_t user_dest_handler_table(int pd, pile_t *table_decks, card_t c);

#endif
