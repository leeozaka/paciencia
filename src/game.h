#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdio.h>

#include "decks.h"
#include "piles.h"

uint8_t game_rule_check(pile_t *game_pile);
void bootstrap(deck_t *deck, pile_t table_decks[], pile_t game_decks[],
               pile_t *discard_deck);

#endif
