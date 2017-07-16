#include <iostream>
#include <fstream>
#include <cstdlib>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "rand.h"

using namespace std;

string getCardName(const Card &card)
{
    return string(SpotNames[card.spot]) + " of " + SuitNames[card.suit];
}

void shuffle(Deck &deck, Player *player)
{
    cout << "# Shuffling the deck\n";
    for (int i = 0; i < 7; i++)
    {
        int cut = get_cut();
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
    player->shuffled();
}

void shuffle(Deck &deck, Player *player, const char *filename)
{
    fstream input(filename);
    cout << "# Shuffling the deck\n";
    while (!input.eof())
    {
        string cut;
        input >> cut;
        if (cut.empty()) break;
        deck.shuffle(atoi(cut.c_str()));
        cout << "cut at " << cut << endl;
    }
    player->shuffled();
}

Card deal(Deck &deck, Hand &hand, Player *player, bool isPlayer, bool isExposed)
{
    Card card = deck.deal();
    hand.addCard(card);
    if (isExposed)
    {
        player->expose(card);
        cout << (isPlayer ? "Player" : "Dealer") << " dealt " << getCardName(card) << endl;
    }
    return card;
}

int main(int argc, char *argv[])
{
    int bankroll = atoi(argv[1]);
    int minimum_bet = atoi(argv[2]);
    int hands = atoi(argv[3]);
    int thishand = 0;

    Deck deck;
    Player *player;
    if (string(argv[4]) == "simple")
    {
        player = get_Simple();
    } else
    {
        player = get_Counting();
    }

    if (argc > 5)shuffle(deck, player, argv[5]);
    else shuffle(deck, player);


    Hand handDealer, handPlayer;
    while (bankroll >= minimum_bet && thishand < hands)
    {
        cout << "# Hand " << ++thishand << " bankroll " << bankroll << endl;
        if (deck.cardsLeft() < 20)
        {
            shuffle(deck, player);
        }
        int wager = player->bet(bankroll, minimum_bet);
        cout << "# Player bets " << wager << endl;
        handPlayer.discardAll();
        handDealer.discardAll();
        deal(deck, handPlayer, player, true, true);
        auto dealerCard = deal(deck, handDealer, player, false, true);
        deal(deck, handPlayer, player, true, true);
        auto holeCard = deal(deck, handDealer, player, false, false);
        if (handPlayer.handValue().count == 21)
        {
            cout << "# Player dealt natural 21\n";
            bankroll += 1.5 * wager;
            continue;
        }
        while (player->draw(dealerCard, handPlayer))
        {
            deal(deck, handPlayer, player, true, true);
        }
        int player_count = handPlayer.handValue().count;
        cout << "Player's total is " << player_count << endl;
        if (player_count <= 21)
        {
            cout << "Dealer's hole card is " << getCardName(holeCard) << endl;
            player->expose(holeCard);
            int dealer_count = handDealer.handValue().count;
            while (dealer_count < 17)
            {
                deal(deck, handDealer, player, false, true);
                dealer_count = handDealer.handValue().count;
            }
            cout << "Dealer's total is " << dealer_count << endl;
            if (dealer_count > 21)
            {
                cout << "# Dealer busts\n";
                bankroll += wager;
            } else if (dealer_count > player_count)
            {
                cout << "# Dealer wins\n";
                bankroll -= wager;
            } else if (dealer_count < player_count)
            {
                cout << "# Player wins\n";
                bankroll += wager;
            } else
            {
                cout << "# Push\n";
            }
        } else
        {
            cout << "# Player busts\n";
            bankroll -= wager;
        }
    }

    cout << "# Player has " << bankroll << " after " << thishand << " hands\n";
    return 0;
}