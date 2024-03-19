#include "game.h"
#include "c.h"
#include "cards.h"
#include "piles.h"
#include "window.h"

#include <stdlib.h>
#include <string.h>

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

void ui_victory_handler() {
  system("cls");

  const char *va[] = {
      "                                        .",
      "             . .                     -:-             .  .  .",
      "            .'.:,'.        .  .  .     ' .           . \\ | / .",
      "            .'.;.`.       ._. ! ._.       \\          .__\\:/__.",
      "             `,:.'         ._\\!/_.                     .';`.      . ' "
      ".",
      "             ,'             . ! .        ,.,      ..======..       .:.",
      "            ,                 .         ._!_.     ||::: : | .        ',",
      "     .====.,                  .           ;  .~.===: : : :|   ..===.",
      "     |.::'||      .=====.,    ..=======.~,   |'|: :|::::::|   "
      "||:::|=====| ",
      "  ___| :::|!__.,  |:::::|!_,   |: :: ::|'|l_l|'|:: |:;;:::|___!| ::|: : "
      ":|",
      " |: :|::: |:: |!__|; :: |: |===::: :: :|'||_||'| : |: :: :|: : |:: "
      "|:::::|",
      " |:::| _::|: :|:::|:===:|::|:::|:===F=:|'!/|\\!''|::F|:====:|::_:|: "
      ":|::__:|",
      " !_[]![_]_!_[]![]_!_[__]![]![_]![_][I_]!//"
      "_:_\\![]I![_][_]!_[_]![]_!_[__]!",
      " -----------------------------------'---''''```---'---------------------"
      "--",
      " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |= _ _:_ _ =| _ _ _ _ _ _ _ _ _ _ "
      "_ _",
      "                                     |=    :    =|                      "
      "  ",
      "_____________________________________L___________J______________________"
      "__",
      "- "
      "------------------------------------------------------------------------"
      "-"};

  info_t w;
  info_t expect = {0, 0, 0, 0, 131, 35};
  gettextinfo(&w);

  int draw_x = (expect.screenwidth - strlen(va[17])) / 2;
  int draw_y = (expect.screenheight - 17) / 2;

  int padding_x = 0;
  int padding_y = 0;

  padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  textcolor(PURPLE);

  for (int i = 0; i < 4; i++) {
    flashbackground(GREEN, 200);
  }

  for (int i = 0; i < 17; i++) {
    gotoxy(draw_x + padding_x, draw_y + padding_y + i);
    cputs(va[i]);
  }

  char *msg = "Parabens! Voce venceu!";
  gotoxy(((expect.screenwidth - strlen(msg)) / 2) + padding_x,
         draw_y + padding_y + 17);
  cputs(msg);

  _getch();
  exit(0);
}
