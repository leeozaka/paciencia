// Patience o jogo

// nao fecho com quem copiar e colar,
// mas se for usar, pelo menos entenda o
// que esta fazendo

// Leonardo Neves, 262310406

#include <conio.h>
#include <stdio.h>

// #include "./src/c.h"
#include "./src/cards.h"
#include "./src/decks.h"
#include "./src/piles.h"
#include "./src/user.h"

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
  for (int i = 0; i < 7; i++)
    pile_init(&table_decks[i]);
  for (int i = 0; i < 4; i++)
    pile_init(&game_decks[i]);

  // inicializa as pilhas do jogo
  deck_populate(&deck, table_decks);

  for (int i = 0; i < 7; i++) {
    card_t c = pile_peek(table_decks[i]);
    printf("Pilha %d: %s%s\n", i + 1, cvalue_str_br_short[c.value],
           csuit_str_br_short[c.suit]);
  }

  // imprime a carta do topo do baralho
  card_t c = deck_get_card(deck);
  printf("A carta do topo do baralho restando eh: %s %s",
         cvalue_str_br[c.value], csuit_str_br[c.suit]);

  // main game loop here
  while (1) {

    // event handler
    switch (user_get_input()) {
    case UI_EXIT:
      exit(1);
      break;

    case UI_PICK:
      int pe, pd, p;
      printf("Selecione uma pilha: ");
      scanf_s("%d", &pe, sizeof(int));

      if (user_card_handler(pe, table_decks)) {
        printf("Pilha invalida\n");
        break;
      }

      printf("Pilha de jogo [1] Pilha de mesa [2]");
      scanf_s("%d", &p, sizeof(int));

      switch (p) {
      case C_GAME:
        printf("Selecione uma pilha de jogo: ");
        scanf_s("%d", &pd, sizeof(int));

        if (user_dest_handler_game(pd, game_decks)) {
          printf("Pilha invalida\n");
          break;
        }

        break;

      case C_TABLE:

        break;

      default:
        break;
      }

      break;
    }
  }

  _getch();
  return 0;
}
