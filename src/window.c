#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c.h"
#include "decks.h"
#include "window.h"

#define TL 218
#define TR 191
#define BL 192
#define BR 217
#define ROW 196
#define COL 179

const info_t expect = {0, 0, 0, 0, 131, 35};

const card_placing_t cards[] = {{6, 2},   {68, 2},  {82, 2},  {96, 2},
                                {110, 2}, {28, 11}, {41, 11}, {54, 11},
                                {67, 11}, {80, 11}, {93, 11}, {106, 11}};

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

inline uint8_t window_verify() {
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

  gettextinfo(&w);

  system("cls");

  padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  // draw cantinhos
  gotoxy(padding_x, padding_y);
  fputc(TL, stdout);
  gotoxy(padding_x + expect.screenwidth, padding_y);
  fputc(TR, stdout);
  gotoxy(padding_x, padding_y + expect.screenheight);
  fputc(BL, stdout);
  gotoxy(padding_x + expect.screenwidth, padding_y + expect.screenheight);
  fputc(BR, stdout);

  // draw col
  for (int i = 1; i <= expect.screenheight - 1; i++) {
    gotoxy(padding_x, i + padding_y);
    fputc(COL, stdout);

    gotoxy(padding_x + expect.screenwidth, i + padding_y);
    fputc(COL, stdout);
  }

  for (int i = 1; i <= expect.screenwidth - 1; i++) {
    gotoxy(i + padding_x, padding_y);
    fputc(ROW, stdout);

    gotoxy(i + padding_x, padding_y + expect.screenheight);
    fputc(ROW, stdout);
  }
  // draw table decks numbers
  for (int i = 0; i < 7; i++) {
    gotoxy(cards[i + 5].x + padding_x + 4, cards[i + 5].y + padding_y - 1);
    printf("[%d]", i + 1);
  }

  // draw cards: discard_deck
  int i = 0;
  gotoxy(cards[i].x + padding_x + 1, cards[i].y + padding_y);

  if (pile_empty(discard_deck)) {
    printf("Empty");
  } else {
    c = pile_peek(*discard_deck);
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y);
    printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
           ROW, TR);
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 1);
    printf("%c%s      %s %c", COL, cval[c.value], csuit[c.suit], COL);
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 2);
    printf("%c         %c", COL, COL);
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 3);
    printf("%c         %c", COL, COL);

    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 4);
    printf("%c         %c", COL, COL);

    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 5);
    printf("%c         %c", COL, COL);

    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 6);
    printf("%c%c%c%c%c%c%c%c%c%c%c", BL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
           ROW, BR);
    // printf("%s      %s", cval[c.value], csuit[c.suit]);
  }

  // draw cards: game_decks
  for (i = 1; i <= 4; i++) {
    gotoxy(cards[i].x + padding_x, cards[i].y + padding_y);
    if (pile_empty(&game_decks[i - 1])) {
      printf("Empty");
    } else {
      c = pile_peek(game_decks[i - 1]);
      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y);
      printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
             ROW, ROW, TR);
      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 1);
      printf("%c%s      %s %c", COL, cval[c.value], csuit[c.suit], COL);
      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 2);
      printf("%c         %c", COL, COL);
      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 3);
      printf("%c         %c", COL, COL);

      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 4);
      printf("%c         %c", COL, COL);

      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 5);
      printf("%c         %c", COL, COL);

      gotoxy(cards[i].x + padding_x, cards[i].y + padding_y + 6);
      printf("%c%c%c%c%c%c%c%c%c%c%c", BL, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
             ROW, ROW, BR);
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
        printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
               ROW, ROW, TR);
      }

      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + game_decks[i - 1].head);
      printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
             ROW, ROW, TR);
      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + 1 + game_decks[i - 1].head);
      printf("%c%s      %s %c", COL, cval[c.value], csuit[c.suit], COL);
      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + 2 + game_decks[i - 1].head);
      printf("%c         %c", COL, COL);
      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + 3 + game_decks[i - 1].head);
      printf("%c         %c", COL, COL);

      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + 4 + game_decks[i - 1].head);
      printf("%c         %c", COL, COL);

      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + 5 + game_decks[i - 1].head);
      printf("%c         %c", COL, COL);

      gotoxy(cards[i].x + padding_x,
             cards[i].y + padding_y + 6 + game_decks[i - 1].head);
      printf("%c%c%c%c%c%c%c%c%c%c%c", BL, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
             ROW, ROW, BR);
    }
  }
  gotoxy(padding_x + 1, padding_y + expect.screenheight - 1);
}

void window_print_msg(const char *msg, COLORS color) {
  info_t w;
  gettextinfo(&w);

  wtext wt = {1, 34};

  uint8_t padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  uint8_t padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  // clearline
  // for (int i = wt.x + padding_x; i < expect.screenwidth; i++) {
  //   textcolor(BLACK);
  //   textbackground(DARK_GREY);
  //   gotoxy(i + padding_x, wt.y + padding_y);
  //   putc(32, stdout);
  // }

  // em minha defesa isso aqui é mto feio porém é muito mais
  // rapido em tempo de execucao
  gotoxy(wt.x + padding_x, wt.y + padding_y);
  textbackground(DARK_GREY);
  printf("                                                                     "
         "                                                             ");

  textcolor(color);
  gotoxy(wt.x + padding_x, wt.y + padding_y);
  printf("%s", msg);

  textcolor(WHITE);
  textbackground(BLACK);
}

void window_game_card_highlight(pile_t p, enum CARDS_PLACE place, COLORS color,
                                const char **cval, const char **csuit) {
  info_t w;
  gettextinfo(&w);

  card_t c = pile_peek(p);

  uint8_t padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  uint8_t padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y);
  textcolor(color);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y);
  printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
         ROW, TR);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 1);
  printf("%c%s      %s %c", COL, cval[c.value], csuit[c.suit], COL);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 2);
  printf("%c         %c", COL, COL);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 3);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 4);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 5);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 6);
  printf("%c%c%c%c%c%c%c%c%c%c%c", BL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
         ROW, BR);

  textcolor(WHITE);
}

void window_table_card_highlight(pile_t p, enum CARDS_PLACE place, COLORS color,
                                 const char **cval, const char **csuit) {
  info_t w;
  gettextinfo(&w);

  card_t c = pile_peek(p);

  uint8_t padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  uint8_t padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  gotoxy(cards[place].x + padding_x + 1, cards[place].y + padding_y + p.head);
  textcolor(color);

  // printf("%s      %s", cval[c.value], csuit[c.suit]);
  //

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + p.head);
  printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
         ROW, TR);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 1 + p.head);
  printf("%c%s      %s %c", COL, cval[c.value], csuit[c.suit], COL);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 2 + p.head);
  printf("%c         %c", COL, COL);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 3 + p.head);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 4 + p.head);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 5 + p.head);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 6 + p.head);
  printf("%c%c%c%c%c%c%c%c%c%c%c", BL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
         ROW, BR);

  textcolor(WHITE);
}

void window_discard_card_highlight(pile_t p, enum CARDS_PLACE place,
                                   COLORS color, const char **cval,
                                   const char **csuit) {
  info_t w;
  gettextinfo(&w);

  card_t c = pile_peek(p);

  uint8_t padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  uint8_t padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  textcolor(color);
  textbackground(BLACK);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y);
  printf("%c%c%c%c%c%c%c%c%c%c%c", TL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
         ROW, TR);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 1);
  printf("%c%s      %s %c", COL, cval[c.value], csuit[c.suit], COL);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 2);
  printf("%c         %c", COL, COL);
  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 3);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 4);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 5);
  printf("%c         %c", COL, COL);

  gotoxy(cards[place].x + padding_x, cards[place].y + padding_y + 6);
  printf("%c%c%c%c%c%c%c%c%c%c%c", BL, ROW, ROW, ROW, ROW, ROW, ROW, ROW, ROW,
         ROW, BR);
}

void window_deck_peek_handler(card_t c, COLORS color, const char **cval,
                              const char **csuit) {
  info_t w;
  gettextinfo(&w);

  wtext wt = {1, 34};

  uint8_t padding_x = w.screenwidth > 130 ? (w.screenwidth - 130) / 2 : 0;
  uint8_t padding_y = w.screenwidth > 34 ? (w.screenheight - 34) / 2 : 0;

  // clearline
  // for (int i = wt.x + padding_x; i < expect.screenwidth; i++) {
  //   textbackground(DARK_GREY);
  //   gotoxy(i + padding_x, 33 + padding_y);
  //   fputc(' ', stdout);
  // }

  gotoxy(wt.x + padding_x, wt.y + padding_y);
  textbackground(DARK_GREY);
  printf("                                                                     "
         "                                                             ");

  textcolor(color);
  gotoxy(wt.x + padding_x, wt.y + padding_y);

  printf("Carta do topo do baralho: %s de %s, ", cval[c.value], csuit[c.suit]);
  textbackground(YELLOW);
  printf("Pegar carta? [S]im [N]ao");
}
