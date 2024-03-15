#ifndef CARDS_H
#define CARDS_H

#include <stdint.h>

typedef enum CARD_VALUE {
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
} cvalue;

typedef enum CARD_SUIT { HEART, DIAMONDS, CLUBS, SPADES } csuit;

typedef struct CARD_TYPE {
  csuit suit;
  cvalue value;
} card_t;

#endif
