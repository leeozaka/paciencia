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

const char *cvalue_str_br[] = {"AS",     "DOIS", "TRES", "QUATRO", "CINCO",
                               "SEIS",   "SETE", "OITO", "NOVE",   "DEZ",
                               "VALETE", "DAMA", "REI"};
const char *cvalue_str_br_short[] = {"A", "2", "3", "4", "5", "6", "7",
                                     "8", "9", "X", "J", "Q", "K"};

const char *csuit_str_br[] = {"COPAS", "OUROS", "PAUS", "ESPADAS"};
const char *csuit_str_br_short[] = {"C", "O", "P", "E"};

int main() {
  deck_t deck;
  pile_t table_decks[7], game_decks[4];

  // inicializa o baralho ordenado e mistura
  deck_init(&deck);

  // inicializa as pilhas
  for (int i = 0; i < 7; i++) {
    pile_init(&table_decks[i]);
  }

  // inicializa as pilhas do jogo
  deck_populate(&deck, table_decks);

  // imprime as pilhas
  for (int i = 0; i < 7; i++) {
    printf("Pilha %d\n", i + 1);
    pile_print(table_decks[i], cvalue_str_br_short, csuit_str_br_short);
    printf("\n----------------\n");
  }

  // imprime a carta do topo do baralho
  card_t c = deck_get_card(deck);
  printf("A carta do topo do baralho restando eh: %s %s",
         cvalue_str_br[c.value], csuit_str_br[c.suit]);

  _getch();
  return 0;
}
