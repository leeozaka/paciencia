#ifndef CARDS_H
#define CARDS_H

#include <stdint.h>
typedef enum CARD_VALUE {
  KING,
  QUEEN,
  JACK,
  TEN,
  NINE,
  EIGHT,
  SEVEN,
  SIX,
  FIVE,
  FOUR,
  THREE,
  TWO,
  ACES
} cvalue;

typedef enum CARD_SUIT { HEART, DIAMONDS, CLUBS, SPADES } csuit;

typedef struct CARD_TYPE {
  csuit suit;
  cvalue value;
} card_t;

#endif
