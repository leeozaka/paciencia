// Patience o jogo

// nao fecho com quem copiar e colar,
// mas se for usar, pelo menos entenda o
// que esta fazendo

// Leonardo Neves, 262310406

#include <conio.h>
#include <ctype.h>
#include <stdio.h>

// #include "src/c.h"
#include "src/cards.h"
#include "src/decks.h"
#include "src/game.h"
#include "src/piles.h"
#include "src/user.h"

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

  // main game loop here
  while (1) {
    system("cls");
    printf("Pilhas de jogo\n");

    for (int i = 0; i < 4; i++) {
      if (pile_empty(&game_decks[i])) {
        printf("Pilha %d: vazia\n", i + 1);
        continue;
      }

      card_t c = pile_peek(game_decks[i]);
      printf("Pilha %d: %s%s\n", i + 1, cvalue_str_br_short[c.value],
             csuit_str_br_short[c.suit]);
    }
    printf("\n");

    printf("Pilhas de mesa\n");
    for (int i = 0; i < 7; i++) {
      if (pile_empty(&table_decks[i])) {
        printf("Pilha %d: vazia\n", i + 1);
        continue;
      }

      card_t c = pile_peek(table_decks[i]);
      printf("Pilha %d: %s%s\n", i + 1, cvalue_str_br_short[c.value],
             csuit_str_br_short[c.suit]);
    }
    printf("\n");

    printf("Comandos: [M]over O[l]har [Q]uit\n");
    // event handler
    switch (user_get_input()) {
    case UI_EXIT:
      exit(1);
      break;

    // user input pick
    case UI_PICK:
      int pe, pd;
      printf("Selecione uma pilha: \n");
      pe = user_input_handler();

      if (user_card_handler(pe, table_decks)) {
        printf("Pilha invalida\n");
        _getch();
        break;
      }

      card_t c = pile_peek(table_decks[pe]);

      printf("[1]-Pilha de jogo - [2]-Pilha de mesa\n");

      switch (user_choice_handler()) {
      case C_GAME:
        printf("Selecione uma pilha de jogo: ");
        pd = user_input_handler();

        if (user_dest_handler_game(pd, game_decks, c)) {
          printf("Pilha invalida\n");
          _getch();
          break;
        }

        pile_push(&game_decks[pd], pile_pop(&table_decks[pe]));
        break;

      case C_TABLE:
        printf("Selecione uma pilha de mesa: ");
        pd = user_input_handler();

        if (user_dest_handler_table(pd, table_decks, c)) {
          printf("Pilha invalida\n");
          _getch();
          break;
        }
        pile_push(&table_decks[pd], pile_pop(&table_decks[pe]));
        break;

      case C_ERR:
        printf("Comando invalido\n");
        _getch();
        break;
      }
      break;

    case UI_LOOK:
      if (deck_is_empty(deck)) {
        printf("Baralho vazio!\n");
        _getch();
        break;
      }
      c = deck_get_card(deck);
      printf("Carta do topo do baralho: %s de %s\n", cvalue_str_br[c.value],
             csuit_str_br[c.suit]);
      _getch();
      break;

    case UI_INVALID:
      printf("Comando invalido\n");
      break;
    }

    // check if the game is over
    if (game_rule_check(game_decks) == 4) {
      printf("Voce venceu!\n");
      break;
    }
  }

  _getch();
  return 0;
}
