//
// Created by liu on 16-7-4.
//

#include "deck.h"

Deck::Deck()
{
    this->reset();
}

void Deck::reset()
{
    for (int suit = SPADES; suit < SUIT_SIZE; suit++)
    {
        for (int spot = TWO; spot < SPOT_SIZE; spot++)
        {
            int index = suit * SPOT_SIZE + spot;
            this->deck[index].suit = Suit(suit);
            this->deck[index].spot = Spot(spot);
        }
    }
    this->next = 0;
}

void Deck::shuffle(int n)
{
    int leftNum = n, rightNum = DeckSize - n;
    auto leftCards = new Card[leftNum + 1], rightCards = new Card[rightNum + 1];
    for (int i = 0; i < leftNum; i++)
    {
        leftCards[i] = this->deck[i];
    }
    for (int i = 0; i < rightNum; i++)
    {
        rightCards[i] = this->deck[leftNum + i];
    }
    int left = 0, right = 0;
    while (left < leftNum || right < rightNum)
    {
        if (right < rightNum)
        {
            this->deck[left + right] = rightCards[right];
            right++;
        }
        if (left < leftNum)
        {
            this->deck[left + right] = leftCards[left];
            left++;
        }
    }
    this->next = 0;
    delete[] leftCards;
    delete[] rightCards;
}

Card Deck::deal()
{
    if (this->next < DeckSize)
    {
        return this->deck[this->next++];
    }
    throw DeckEmpty();
}

int Deck::cardsLeft()
{
    return DeckSize - this->next;
}
