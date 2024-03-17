// Patience o jogo

// nao fecho com quem copiar e colar,
// mas se for usar, pelo menos entenda o
// que esta fazendo

// Leonardo Neves, 262310406

#include <conio.h>
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
  pile_t table_decks[7], game_decks[4], discard_deck;
  card_t c;

  // init the game
  bootstrap(&deck, table_decks, game_decks, &discard_deck);

  for (int i = 0; i < 7; i++) {
    c = pile_peek(table_decks[i]);
    printf("Deck %d: %s%s\n", i + 1, cvalue_str_br_short[c.value],
           csuit_str_br_short[c.suit]);
  }

  // main game loop here
  while (1) {
    int pe, pd;
    system("cls");
    printf("[1] Decks de jogo\n");

    for (int i = 0; i < 4; i++) {
      if (pile_empty(&game_decks[i])) {
        printf("Deck %d: vazio\n", i + 1);
        continue;
      }

      c = pile_peek(game_decks[i]);
      printf("Deck %d: %s%s\n", i + 1, cvalue_str_br_short[c.value],
             csuit_str_br_short[c.suit]);
    }
    printf("\n");

    printf("[2] Decks de mesa\n");
    for (int i = 0; i < 7; i++) {
      if (pile_empty(&table_decks[i])) {
        printf("Deck %d: vazio\n", i + 1);
        continue;
      }

      c = pile_peek(table_decks[i]);
      printf("Deck %d: %s%s\n", i + 1, cvalue_str_br_short[c.value],
             csuit_str_br_short[c.suit]);
    }
    printf("\n");

    if (pile_empty(&discard_deck)) {
      printf("[3] Baralho de descarte: vazio\n");
    } else {
      c = pile_peek(discard_deck);
      printf("[3] Baralho de descarte: %s de %s\n", cvalue_str_br[c.value],
             csuit_str_br[c.suit]);
    }

    printf("Comandos: [M]over O[l]har [Q]uit: ");

    // event handler
    switch (user_get_input()) {
    case UI_EXIT:
      exit(1);
      break;

    // user input pick
    case UI_PICK:
      printf("\n[1] Deck de jogo, [2] Deck de mesa, [3] Baralho de descarte: ");
      uint8_t n = user_deck_input_handler();
      switch (n) {
      case DECK_GAME:
        printf("\nSelecione um deck de jogo: ");
        pe = user_input_handler();

        if (user_game_card_handler(pe, game_decks)) {
          printf("\nDeck invalido\n");
          _getch();
          break;
        }

        // store the card to be moved
        c = pile_peek(table_decks[pe]);

        printf("\nCarta selecionada: %s de %s", cvalue_str_br[c.value],
               csuit_str_br[c.suit]);
        break;

      case DECK_TABLE:
        printf("\nSelecione um deck de mesa: ");
        pe = user_input_handler();

        if (user_table_card_handler(pe, table_decks)) {
          printf("\nDeck invalido\n");
          _getch();
          break;
        }

        // store the card to be moved
        c = pile_peek(table_decks[pe]);

        printf("\nCarta selecionada: %s de %s", cvalue_str_br[c.value],
               csuit_str_br[c.suit]);
        break;

      case DECK_DISCARD:
        if (pile_empty(&discard_deck)) {
          printf("Baralho de descarte vazio!\n");
          _getch();
          break;
        }

        c = pile_peek(discard_deck);
        break;

      case DECK_ERR:
        break;

      default:
        printf("Comando invalido\n");
        _getch();
        break;
      }

      printf("\n[1]-Deck de jogo - [2]-Deck de mesa: ");

      switch (user_choice_handler()) {
      case C_GAME:
        printf("\nSelecione um deck de jogo: ");
        pd = user_input_handler();

        if (user_dest_handler_game(pd, game_decks, c)) {
          printf("Deck invalida\n");
          _getch();
          break;
        }

        switch (n) {
        case DECK_GAME:
          pile_push(&game_decks[pd], pile_pop(&game_decks[pe]));
          break;
        case DECK_TABLE:
          pile_push(&game_decks[pd], pile_pop(&table_decks[pe]));
          break;
        case DECK_DISCARD:
          pile_push(&game_decks[pd], pile_pop(&discard_deck));
          break;
        }

        break;

      case C_TABLE:
        printf("\nSelecione um deck de mesa: ");
        pd = user_input_handler();

        if (user_dest_handler_table(pd, table_decks, c)) {
          printf("\nDeck invalida\n");
          _getch();
          break;
        }

        switch (n) {
        case DECK_GAME:
          pile_push(&table_decks[pd], pile_pop(&game_decks[pe]));
          break;
        case DECK_TABLE:
          pile_push(&table_decks[pd], pile_pop(&table_decks[pe]));
          break;
        case DECK_DISCARD:
          pile_push(&table_decks[pd], pile_pop(&discard_deck));
          break;
        }

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
      printf("\nCarta do topo do baralho: %s de %s\n", cvalue_str_br[c.value],
             csuit_str_br[c.suit]);
      printf("Pegar carta? [S]im [N]ao\n");
      if (user_choice_handler() == C_YES) {
        pile_push(&discard_deck, deck_pop(&deck));
      }
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
