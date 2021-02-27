#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

byte Card[52];
byte CurrentCard = 0;
byte JustShuffled = 0;

void DeckShuffle()
{
  byte ctr;
  byte tmp;
  byte random_number;

  /* Fill the deck with unique cards */
  for( ctr = 0; ctr < 52; ctr++ )
    Card[ctr] = ctr + 1;

  /* Generate a new seed based on the system clock */
  srand(time(NULL));

  /* Randomly rearrange each card */
  for( ctr = 0; ctr < 52; ctr++ )
  {
    random_number = rand() % 51;
    tmp = Card[random_number];
    Card[random_number] = Card[ctr];
    Card[ctr] = tmp;
  }

  CurrentCard = 0;
  JustShuffled = 1;
}

int main()
{
  byte i;
  byte player = 2;
  byte player1_card1, player1_card2;
  int player1_guess1, player1_guess2;

  DeckShuffle();

  printf("(for you) your cards, player#%d: %d %d\n", player, Card[3 + (player-1) * 2], Card[3 + (player-1) * 2 + 1]);
  printf("(for all) flop: %d %d %d\n", Card[0], Card[1], Card[2]);
  player1_card1 = Card[3];
  player1_card2 = Card[4];

  printf("do you know which cards have player #1? ");
  scanf("%d %d", &player1_guess1, &player1_guess2);
  if( player1_guess1 == player1_card1 && player1_guess2 == player1_card2 )
    printf("acerto, miseravi!\n");
  else
    printf("no no no, I am still secure!\n");
}

