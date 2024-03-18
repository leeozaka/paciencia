// Patience o jogo

// nao fecho com quem copiar e colar,
// mas se for usar, pelo menos entenda o
// que esta fazendo

// Leonardo Neves, 262310406

#include "src/c.h"
#include "src/cards.h"
#include "src/decks.h"
#include "src/game.h"
#include "src/piles.h"
#include "src/user.h"
#include "src/window.h"

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
    textbackground(BLACK);
    textcolor(WHITE);

    // check if the window is valid
    if (!window_verify())
      bootstrap_window();

    // check if the game is over
    if (game_rule_check(game_decks) == 4) {
      ui_victory_handler(cvalue_str_br, csuit_str_br);
    }

    // screen update here
    window_draw(table_decks, game_decks, &discard_deck, cvalue_str_br_short,
                csuit_str_br_short);

    int pe = 0, pd = 0;
    window_print_msg("Comandos: [M]over O[l]har [Q]uit: ", WHITE);

    // event handler
    switch (user_get_input()) {
    case UI_CHEAT:
      window_print_msg("Cheat code!", PURPLE);
      ui_cheat_handler(game_decks);
      _getch();
      continue;

    case UI_EXIT:
      system("cls");
      exit(1);

    // user input pick
    case UI_PICK:
      window_print_msg(
          "[1] Deck de jogo, [2] Deck de mesa, [3] Baralho de descarte: ",
          WHITE);
      uint8_t n = user_deck_input_handler();
      switch (n) {
      case DECK_GAME:
        window_print_msg("Selecione um deck de jogo: ", WHITE);
        pe = user_input_handler();

        if (user_game_card_handler(pe, game_decks)) {
          window_print_msg("Deck invalido", RED);
          _getch();
          continue;
        }

        // store the card to be moved
        c = pile_peek(table_decks[pe]);

        window_game_card_highlight(game_decks[pe], GAME_1 + pe, GREEN,
                                   cvalue_str_br_short, csuit_str_br_short);
        break;

      case DECK_TABLE:
        window_print_msg("Selecione um deck de mesa: ", WHITE);
        pe = user_input_handler();

        if (user_table_card_handler(pe, table_decks)) {
          window_print_msg("Deck invalido", RED);
          _getch();
          continue;
        }

        // store the card to be moved
        c = pile_peek(table_decks[pe]);

        window_table_card_highlight(table_decks[pe], TABLE_1 + pe, GREEN,
                                    cvalue_str_br_short, csuit_str_br_short);

        break;

      case DECK_DISCARD:
        if (pile_empty(&discard_deck)) {
          window_print_msg("Baralho de descarte vazio!", RED);
          _getch();
          continue;
        }

        c = pile_peek(discard_deck);
        window_discard_card_highlight(discard_deck, DECK, GREEN,
                                      cvalue_str_br_short, csuit_str_br_short);
        break;

      case DECK_ERR:
      default:
        window_print_msg("Comando invalido", RED);
        _getch();
        continue;
      }

      window_print_msg("[1]-Deck de jogo - [2]-Deck de mesa: ", WHITE);

      switch (user_choice_handler()) {
      case C_GAME:
        if (user_dest_handler_game(c.suit, game_decks, c)) {
          window_print_msg("Deck invalido", RED);
          _getch();
          continue;
        }

        switch (n) {
        case DECK_GAME:
          pile_push(&game_decks[c.suit], pile_pop(&game_decks[pe]));
          break;
        case DECK_TABLE:
          pile_push(&game_decks[c.suit], pile_pop(&table_decks[pe]));
          break;
        case DECK_DISCARD:
          pile_push(&game_decks[c.suit], pile_pop(&discard_deck));
          break;
        }

        break;

      case C_TABLE:
        window_print_msg("Selecione um deck de mesa: ", WHITE);
        pd = user_input_handler();

        if (user_dest_handler_table(pd, table_decks, c)) {
          window_print_msg("Deck invalido", RED);
          _getch();
          continue;
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
        window_print_msg("Comando invalido", RED);
        _getch();
        continue;
      }
      break;

    case UI_LOOK:
      if (deck_is_empty(deck)) {
        window_print_msg("Baralho vazio!", RED);
        _getch();
        continue;
      }
      c = deck_get_card(deck);
      window_deck_peek_handler(c, WHITE, cvalue_str_br, csuit_str_br);

      if (user_choice_handler() == C_YES) {
        pile_push(&discard_deck, deck_pop(&deck));
      }
      break;

    case UI_INVALID:
      window_print_msg("Comando invalido", RED);
      break;
    }
  }
  return 0;
}
