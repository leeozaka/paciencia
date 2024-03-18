#include <corecrt.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "c.h"
#include "window.h"

const info_t expect = {0, 0, 0, 0, 130, 34};

const card_placing_t cards[] = {
    {6, 2},   {68, 2},  {83, 2},  {98, 2},  {107, 2}, {113, 2}, {28, 11},
    {42, 11}, {56, 11}, {67, 11}, {85, 11}, {99, 11}, {107, 11}};

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
      gettextinfo(&window);
      _getch();
    }
  } while (window.screenwidth < expect.screenwidth ||
           window.screenheight < expect.screenheight);

  return window;
}

uint8_t window_verify() {
  info_t w;

  gettextinfo(&w);
  return w.screenwidth == expect.screenwidth &&
         w.screenheight == expect.screenheight;
}

void window_draw() {
  info_t w;
  int padding_x, padding_y;

  wchar_t col_w = 0x2500;
  wchar_t row_w = 0x2502;
  gettextinfo(&w);

  system("cls");

  padding_x = (w.screenwidth - 130) / 2;
  padding_y = (w.screenheight - 34) / 2;

  // draw col
  for (int i = 1; i <= expect.screenheight; i++) {
    gotoxy(padding_x, i + padding_y);
    wprintf(L"%lc", col_w);
    gotoxy(padding_x + expect.screenwidth, i + padding_y);
    wprintf(L"%lc", col_w);
  }

  // draw row
  for (int i = 1; i <= expect.screenwidth; i++) {
    gotoxy(padding_x, i + padding_y);
    wprintf(L"%lc", row_w);
    gotoxy(padding_x + expect.screenwidth, i + padding_y);
    wprintf(L"%lc", row_w);
  }
}
