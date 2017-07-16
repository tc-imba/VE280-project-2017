#ifndef __CARD_H__
#define __CARD_H__

enum Suit {
    SPADES, HEARTS, CLUBS, DIAMONDS, SUIT_SIZE
};

extern const char *SuitNames[SUIT_SIZE];

enum Spot {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE, SPOT_SIZE
};

extern const char *SpotNames[SPOT_SIZE];

struct Card {
    Spot  spot;
    Suit  suit;
};

#endif /* __CARD_H__ */
