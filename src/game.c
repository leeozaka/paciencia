#include "game.h"
#include "cards.h"
#include "piles.h"

uint8_t game_rule_check(pile_t *game_pile) {
  uint8_t sq = 0;

  for (int i = 0; i < 4; i++) {
    if (pile_empty(&game_pile[i]))
      continue;

    if (pile_peek(game_pile[i]).value == KING) {
      sq++;
    }
  }

  return sq;
}
