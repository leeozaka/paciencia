#include "game.h"
#include "cards.h"
#include "piles.h"
#include "window.h"

#include <stdlib.h>

uint8_t game_rule_check(pile_t *game_pile) {
  uint8_t sq = 0;

  for (int i = 0; i < 4; i++) {
    if (pile_empty(&game_pile[i]))
      continue;

    if (pile_peek(game_pile[i]).value == KING)
      sq++;
  }

  return sq;
}

void bootstrap(deck_t *deck, pile_t table_decks[], pile_t game_decks[],
               pile_t *discard_deck) {
  // inicializa o baralho ordenado e mistura
  deck_init(deck);

  // inicializa as pilhas
  for (int i = 0; i < 7; i++)
    pile_init(&table_decks[i]);
  for (int i = 0; i < 4; i++)
    pile_init(&game_decks[i]);
  pile_init(discard_deck);

  // inicializa as pilhas do jogo
  deck_populate(deck, table_decks);
}

void ui_cheat_handler(pile_t game_decks[]) {
  for (int i = 0; i < 4; i++) {
    game_decks[i].head = 1;
    game_decks[i].card[game_decks[i].head].suit = i;
    game_decks[i].card[game_decks[i].head].value = KING;
  }
}

void ui_victory_handler(const char **cvstr, const char **csstr) {
  system("cls");
  printf("Voce venceu! (y)\n");
  for (int i = 0; i < 4; i++) {
    printf("Deck %d: %s de %s\n", i + 1, cvstr[KING], csstr[i]);
  }

  system("pause");
  exit(0);
}
