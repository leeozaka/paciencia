#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdio.h>

#include "decks.h"
#include "piles.h"

uint8_t game_rule_check(pile_t *game_pile);
void bootstrap(deck_t *deck, pile_t table_decks[], pile_t game_decks[],
               pile_t *discard_deck);
void ui_victory_handler(const char **cvstr, const char **csstr);
void ui_cheat_handler(pile_t *game_decks);
#endif
