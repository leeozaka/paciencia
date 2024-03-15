// Patience o jogo

// nao fecho com quem copiar e colar,
// mas se for usar, pelo menos entenda o
// que esta fazendo

// Leonardo Neves, 262310406

#include <stdio.h>

#include "./src/c.h"
#include "./src/cards.h"
#include "./src/decks.h"
#include "./src/piles.h"

// const char *cvalue_str[] = {"KING",  "QUEEN", "JACK", "TEN",  "NINE",
//                             "EIGHT", "SEVEN", "SIX",  "FIVE", "FOUR",
//                             "THREE", "TWO",   "ACES"};
// const char *csuit_str[] = {"HEARTS", "DIAMONDS", "CLUBS", "SPADES"};

const char *cvalue_str_br[] = {"REI",  "DAMA", "VALETE", "DEZ",   "NOVE",
                               "OITO", "SETE", "SEIS",   "CINCO", "QUATRO",
                               "TRES", "DOIS", "AS"};
const char *csuit_str_br[] = {"COPAS", "OUROS", "PAUS", "ESPADAS"};

int main() {
  card_t deck[52];
  pile_t decks[7];
  // pile_t *stacks[4];

  // inicializa o baralho ordenado e mistura
  deck_init(deck);

  // inicializa as pilhas
  for (int i = 0; i < 7; i++) {
    pile_init(&decks[i]);
  }

  // inicializa as pilhas do jogo
  deck_populate(decks, deck);

  // imprime as pilhas
  for (int i = 0; i < 7; i++) {
    printf("Pilha %d\n", i + 1);
    pile_print(decks[i], cvalue_str_br, csuit_str_br);
    printf("\n----------------\n");
  }

  _getch();
  return 0;
}
