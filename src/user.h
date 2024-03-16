#ifndef USER_H
#define USER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piles.h"

enum USER_INPUT { UI_EXIT, UI_PICK, UI_DROP, UI_LOOK, UI_DECK, UI_INVALID };
enum CHOICES { C_ERR, C_GAME, C_TABLE };

int user_get_input();
uint8_t user_card_handler(int pe, pile_t *table_decks);
uint8_t user_dest_handler_game(int pe, pile_t *game_decks);
uint8_t user_dest_handler_table(int pe, pile_t *table_decks);

#endif
