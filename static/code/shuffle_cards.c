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

  DeckShuffle();

  printf("cards: \n");
  for( i = 0; i < 52; ++i )
  {
    printf("%d ", Card[i]);
  }
  printf("\n");
}

