#include <stdio.h>
#include <stdlib.h>

void greetings(void);
void play(void);
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
        case 1:play();break;
    }
}

void play(void)
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
   }


}

int random(int n)
{
    return rand() % n;
}

