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

void bootstrap(deck_t *deck, pile_t table_decks[], pile_t game_decks[]) {
  // inicializa o baralho ordenado e mistura
  deck_init(deck);

  // inicializa as pilhas
  for (int i = 0; i < 7; i++)
    pile_init(&table_decks[i]);
  for (int i = 0; i < 4; i++)
    pile_init(&game_decks[i]);

  // inicializa as pilhas do jogo
  deck_populate(deck, table_decks);
}
