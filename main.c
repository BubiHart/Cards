#include <stdio.h>
#include <stdlib.h>

void greetings(void);
void game(void);
void initialize_deck(void);
void translate(int counter, int face, int suit, int player);
int random(int n);

int main()
{
  greetings();
}

void greetings(void)
{
    int choice = 0;
    printf("1.Play\n");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:game();break;
    }
}

void game(void)
{
    initialize_deck();
}

void initialize_deck(void)
{
    system("cls");
    srand(time(NULL));

    int rand_min = 0;
    int rand_max = 35;
    int players_amount = 0;
    int counter = 0;
    int card = 6;
    int suit = 0;
    int counter_player_cards = 0;
    int card_per_player = 0;
    int rand_number = 0;
    int card_deck[36][3];

    printf("Enter number of players: ");
    scanf("%d", &players_amount);

    card_per_player = 36 / players_amount;


    for(counter = 0; counter < 36;counter++)
    {
       if(counter % 9 != 0)
       {
         card += 1;
       }
       else
       {
         card = 6;
       }
      card_deck[counter][0] = card;

     if(counter % 9 == 0 && counter != 1)
       {
         suit += 1;
         card_deck[counter][1] = suit;

       }
       else
       {
        card_deck[counter][1] = suit;
       }

       card_deck[counter][2] = 0;
   }

   for(counter = 1;counter <= players_amount;counter++)
   {
       for(counter_player_cards = 1;counter_player_cards <= card_per_player;counter_player_cards++)
       {
           do
           {
             rand_number = random(rand_max-rand_min+1) + rand_min;
             fflush(stdin);
           }
           while(card_deck[rand_number][2] != 0);

           card_deck[rand_number][2] = counter;
       }

   }
    for(counter = 0;counter < 36;counter++)
    {
        translate(counter, card_deck[counter][0], card_deck[counter][1], card_deck[counter][2]);
    }


}

void translate(int counter, int face, int suit, int player)
{


  printf("%d\t", counter);
  switch(face)
  {
      case 6:printf("Six\t\t");break;
      case 7:printf("Seven\t\t");break;
      case 8:printf("Eight\t\t");break;
      case 9:printf("Ten\t\t");break;
      case 10:printf("Jack\t\t");break;
      case 11:printf("Jack\t\t");break;
      case 12:printf("Queen\t\t");break;
      case 13:printf("King\t\t");break;
      case 14:printf("Ace\t\t");break;
  }

  switch(suit)
  {
      case 1:printf("Hearts\t\t");break;
      case 2:printf("Diamonds\t");break;
      case 3:printf("Clubs\t\t");break;
      case 4:printf("Spades\t\t");break;
  }
  printf("%d\n", player);
}

int random(int n)
{
    return rand() % n;
}

