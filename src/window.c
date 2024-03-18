#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c.h"
#include "decks.h"
#include "window.h"

const info_t expect = {0, 0, 0, 0, 131, 35};

const card_placing_t cards[] = {{6, 2},   {68, 2},  {82, 2},  {96, 2},
                                {110, 2}, {28, 11}, {41, 11}, {54, 11},
                                {67, 11}, {80, 11}, {93, 11}, {106, 11}};

const card_size_t card_size = {12, 6};

const struct errtext {
  char *msg;
  char *confirmdialog;
  char *msg2;
} errtext = {"Por favor, aumente a resolucao da tela para 130x40 ou mais",
             "Pressione qualquer tecla para atualizar",
             "Pressione 'q' para sair"};

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

      int x = (window.screenwidth - strlen(errtext.msg)) / 2;
      int y = window.screenheight / 2;
      textcolor(RED);
      gotoxy(x, y);
      cputs(errtext.msg);
      textcolor(WHITE);
      x = (window.screenwidth - strlen(errtext.confirmdialog)) / 2;
      y++;
      gotoxy(x, y);
      cputs(errtext.confirmdialog);
      x = (window.screenwidth - strlen(errtext.msg2)) / 2;
      y++;
      gotoxy(x, y);
      cputs(errtext.msg2);
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
      for (int j = 0; j < game_decks[i - 1].head; j++) {
        gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + j);
        printf("-----");
      }
      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + game_decks[i - 1].head);
      printf("%s %s", cval[c.value], csuit[c.suit]);
    }
  }
  gotoxy(padding_x + 1, padding_y + expect.screenheight - 1);
}

void window_print_msg(const char *msg, COLORS color) {
  info_t w;
  gettextinfo(&w);

  wtext wt = {2, 33};

  uint8_t padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  uint8_t padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  // clearline
  for (int i = wt.x + padding_x; i < expect.screenwidth; i++) {
    textbackground(DARK_GREY);
    gotoxy(i + padding_x, 33 + padding_y);
    fputc(' ', stdout);
  }

  textcolor(color);
  gotoxy(wt.x + padding_x, wt.y + padding_y);
  cputs(msg);
}
