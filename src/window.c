#include <corecrt.h>
// #include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "c.h"
#include "decks.h"
#include "window.h"

const info_t expect = {0, 0, 0, 0, 130, 34};

const card_placing_t cards[] = {{6, 2},   {68, 2},  {83, 2},  {98, 2},
                                {107, 2}, {28, 11}, {42, 11}, {56, 11},
                                {67, 11}, {85, 11}, {99, 11}, {107, 11}};

const card_size_t card_size = {12, 6};

info_t bootstrap_window() {
  system("title Solitaire");
  info_t window;
  gettextinfo(&window);

  do {
    system("cls");
    if (window.screenwidth < expect.screenwidth ||
        window.screenheight < expect.screenheight) {

      for (int i = 0; i < 3; i++)
        flashbackground(RED, 100);

      char *msgres =
          "Por favor, aumente a resolucao da tela para 130x40 ou mais";
      char *confirmDialog = "Pressione qualquer tecla para atualizar";
      char *msg = "Pressione 'q' para sair";
      int x = (window.screenwidth - strlen(msgres)) / 2;
      int y = window.screenheight / 2;
      textcolor(RED);
      gotoxy(x, y);
      cputs(msgres);
      textcolor(WHITE);
      x = (window.screenwidth - strlen(confirmDialog)) / 2;
      y++;
      gotoxy(x, y);
      cputs(confirmDialog);
      x = (window.screenwidth - strlen(msg)) / 2;
      y++;
      gotoxy(x, y);
      cputs(msg);
      gettextinfo(&window);
      if (_getch() == 'q') {
        system("cls");
        exit(1);
      }
    }
  } while (window.screenwidth < expect.screenwidth ||
           window.screenheight < expect.screenheight);

  return window;
}

uint8_t window_verify() {
  info_t w;

  gettextinfo(&w);
  return w.screenwidth >= expect.screenwidth + 1 &&
         w.screenheight >= expect.screenheight + 1;
}

void window_draw(pile_t *table_decks, pile_t *game_decks, pile_t *discard_deck,
                 const char **cval, const char **csuit) {
  info_t w;
  int padding_x, padding_y;

  card_t c;

  char col = '|';
  char row = '-';

  gettextinfo(&w);

  system("cls");

  padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  // draw col
  for (int i = 1; i <= expect.screenheight; i++) {
    gotoxy(padding_x, i + padding_y);
    fputc(col, stdout);

    gotoxy(padding_x + expect.screenwidth, i + padding_y);
    fputc(col, stdout);
  }

  // draw row
  for (int i = 1; i <= expect.screenwidth; i++) {
    gotoxy(i + padding_x, padding_y);
    fputc(row, stdout);

    gotoxy(i + padding_x, padding_y + expect.screenheight);
    fputc(row, stdout);
  }

  // draw cards: discard_deck
  int i = 0;
  gotoxy(cards[i].x + padding_x, cards[i].y + padding_y);

  if (pile_empty(discard_deck)) {
    printf("Empty");
  } else {
    c = pile_peek(*discard_deck);
    printf("%s %s", cval[c.value], csuit[c.suit]);
  }

  // draw cards: game_decks
  for (i = 1; i <= 4; i++) {
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y);
    if (pile_empty(&game_decks[i - 1])) {
      printf("Empty");
    } else {
      c = pile_peek(game_decks[i - 1]);
      printf("%s %s", cval[c.value], csuit[c.suit]);
    }
  }

  // draw cards: table_decks
  for (i = 5; i <= 11; i++) {
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y);
    if (pile_empty(&table_decks[i - 5])) {
      printf("Empty");
    } else {
      c = pile_peek(table_decks[i - 5]);
      printf("%s %s", cval[c.value], csuit[c.suit]);
    }
  }

  gotoxy(padding_x + 1, padding_y + expect.screenheight - 1);
}
