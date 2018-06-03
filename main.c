#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void game(void);
void initialize_deck(int players_amount);
void set_trump_suit(void);
void translate(void);
void turn_manage(int players_amount);
void make_attack(int player_id);
void make_additional_attack(int defender_id, int card_restriction);
int count_players_cards(int player_id);
void counter_attack(int defender_id, int attacker_id);
void game_description(void);
void action_menu(void);
int random(int n);
void delay(int number_of_seconds);
void repeat_program(void);

int card_deck[36][4];
int turn_array[6];

int turn_array_counter = 0;

int main()
{
    int choice = 0;

    printf("Welcome!\n");
    delay(1);
    printf("Please choose action from list below\n");
    delay(1);
    action_menu();
}

void game(void)
{
    int players_amount = 0;

    printf("Choose number of players\n");
    printf("1. 2 Players\n");
    printf("2. 3 Players\n");
    printf("3. 4 Players\n");
    printf("4. 6 Players\n");

    if(scanf("%d", &players_amount) != 1 || players_amount < 2 || players_amount > 6 || players_amount == 5)
    {
        do
        {
            printf("Sorry. You can only choose 2, 3, 4, or 6 players");
            fflush(stdin);
        }
        while(scanf("%d", &players_amount) != 1 || players_amount < 2 || players_amount > 6 || players_amount == 5);
    }

    printf("Let us begin!\n");
    delay(1);


    initialize_deck(players_amount);
    turn_manage(players_amount);
}

void initialize_deck(int players_amount)
{
    system("cls");
    srand(time(NULL));

    int rand_min = 0;
    int rand_max = 35;
    int counter = 0;
    int card = 6;
    int suit = 0;
    int counter_player_cards = 0;
    int card_per_player = 0;
    int rand_number = 0;


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

   set_trump_suit();

   translate();
}


void make_attack(int player_id)
{
  int min_card_id = 0;
  int turn_array_card_id = 0;
  int min_card = 100;
  int min_card_suit = 0;
  int counter = 0;
  int temp_player_array_counter = 0;


  /*GET ID OF THE SMALLEST CARD*/
  for(counter = 0;counter < 36;counter++)
  {
      if(card_deck[counter][0] <= min_card && card_deck[counter][2] == player_id)
      {
        min_card_id = counter;
        min_card = card_deck[min_card_id][0];
      }

  }

  turn_array_counter = 0;
  /*SEARCH FOR PLAYERS CARD WHICH HP ARE THE SAME AS THE SMALLEST AND FULLFIL TEMP PLAYER'S ARRAY*/
  for(counter = 0;counter < 36;counter++)
  {
      if(card_deck[counter][0] == card_deck[min_card_id][0] && card_deck[counter][2] == player_id)
      {
        turn_array_card_id = turn_array[turn_array_counter];
        turn_array[turn_array_counter] = counter;
        turn_array_counter++;
        card_deck[counter][2] = 11;
      }

  }


  //printf("Min card for Player %d is %d\n", player_id, card_deck[min_card_id][0]);
}

void turn_manage(int players_amount)
{
  int attacker_id = 0;
  int defender_id = 0;
  int turn_counter = 0;
  int card_to_beat_id = 0;
  int beaten_card_id = 0;
  int player_id = 0;
  int counter = 0;
  int cards_on_hand = 0;
  int players_in_game_counter = 0;
  int free_space = 0;
  int amount_to_make_move = 0;
  int card_move_restriction = 0;
  int players_list[players_amount];

  for(counter = 0;counter <= players_amount;counter++)
  {
     players_list[counter] = 1;
  }

  players_list[0] = 0;



  for(turn_counter = 1;turn_counter <= players_amount;turn_counter++)
  {
      players_in_game_counter = players_amount;
      for(counter = 1;counter <= players_amount;counter++)
      {
        player_id = counter;
        cards_on_hand = count_players_cards(player_id);
        if(cards_on_hand == 0)
        {
            printf("Player %d is out\n", player_id);
            players_list[counter] = 0;
            players_in_game_counter--;
        }

      }



       /*IF THERE ARE MORE THAN 1 PLAYER CONTINUE GAME*/
      if(players_in_game_counter > 1)
      {
        if(players_list[turn_counter] == 0)
        {
             do
             {
               turn_counter++;
               if(turn_counter == players_amount && players_list[turn_counter] == 0)
               {
                  turn_counter = 1;
               }
             }
             while(players_list[turn_counter] == 0);
        }

        if(turn_counter == players_amount)
        {
          attacker_id = turn_counter;
          turn_counter = 0;
          defender_id = turn_counter + 1;
          printf("Player %d on Player %d\n", attacker_id , defender_id);
          delay(3);
        }
        else
        {
            attacker_id = turn_counter;
            defender_id = turn_counter + 1;
            printf("Player %d on Player %d\n", attacker_id, defender_id);
            delay(3);
        }

        make_attack(attacker_id);
        counter_attack(defender_id, attacker_id);

        free_space = (12 - turn_array_counter)/2;

        amount_to_make_move = count_players_cards(defender_id);

        if(amount_to_make_move >= free_space)
            {
                card_move_restriction = free_space;
            }

            if(free_space > amount_to_make_move)
            {
                card_move_restriction = amount_to_make_move;
            }

            make_additional_attack(defender_id, card_move_restriction);
            counter_attack(defender_id, attacker_id);


        translate();

        printf("DELAY\n");
        delay(1);
        system("cls");

        for(counter = 0;counter < 12;counter++)
        {
          beaten_card_id = turn_array[counter];
          card_deck[beaten_card_id][2] = 0;
          turn_array[counter] = 0;
        }

      }
      else
      {
          printf("GAME OVER");
          repeat_program();
      }

  }



}

void set_trump_suit(void)
{
   int counter = 0;
   int rand_number = 0;
   int rand_min = 1;
   int rand_max = 4;
   srand(time(NULL));

   rand_number = random(rand_max-rand_min+1) + rand_min;


   for(counter = 0;counter < 36;counter++)
   {
       card_deck[counter][3] = 0;

       if(card_deck[counter][1] == rand_number)
       {
         card_deck[counter][3] = 1;
         card_deck[counter][0] += 9;
       }

   }

}

void counter_attack(int defender_id, int attacker_id)
{
  int counter = 0;
  int search_counter = 0;
  int min_card = 100;
  int min_card_id = 0;
  int card_id = 0;
  int card_to_beat_id = 0;


  for(counter = 0;counter < 12;counter++)
  {
     card_to_beat_id = turn_array[counter];

     /*IF CARD HAS NOT BEEN BEAT YET*/

     if(card_deck[card_to_beat_id][2] == 11)
     {

         for(search_counter = 0;search_counter < 36;search_counter++)
         {
          /*FIRSTLY SEARCH NOT TRUMP CARD TO BEAT*/
          if(card_deck[search_counter][0] < min_card && card_deck[search_counter][0] > card_deck[card_to_beat_id][0]
              && card_deck[search_counter][1] == card_deck[card_to_beat_id][1] &&
              card_deck[search_counter][2] == defender_id
              && card_deck[search_counter][3] != 1)
             {
                min_card_id = search_counter;
                min_card = card_deck[min_card_id][0];

                /*IF THERE ARE NO CARD TO BEAT - SEARCH THE SMALLEST TRUMP CARD*/
             }
         }
         if(min_card_id == 0 && min_card == 100)
         {
            for(search_counter = 0;search_counter < 36;search_counter++)
            {
               if(card_deck[search_counter][0] < min_card && card_deck[search_counter][0] > card_deck[card_to_beat_id][0]
                   && card_deck[search_counter][2] == defender_id)
               {
                 min_card_id = search_counter;
                 min_card = card_deck[min_card_id][0];
               }
            }
         }

         if(min_card == 100 && min_card_id == 0)
         {
           printf("Ooops.Can't beat\n");
           for(counter = 0;counter < turn_array_counter;counter++)
           {
              card_id = turn_array[counter];
              card_deck[card_id][2] = defender_id;
            }
          }

         turn_array[turn_array_counter] = min_card_id;
         card_deck[card_to_beat_id][2] = 10;
         card_deck[min_card_id][2] = 10;
         printf("BEAT %d WITH %d%\n", card_to_beat_id, min_card_id);
         min_card_id = 0;
         min_card = 100;
         turn_array_counter++;
     }

  }

}

void translate(void)
{
    int counter = 0;
    for(counter = 0;counter < 36;counter++)
    {
        printf("%d\t", counter);
          switch(card_deck[counter][0])
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
              /*IN CASE OF TRUMP CARD*/
              case 15:printf("Six\t\t");break;
              case 16:printf("Seven\t\t");break;
              case 17:printf("Eight\t\t");break;
              case 18:printf("Ten\t\t");break;
              case 19:printf("Jack\t\t");break;
              case 20:printf("Jack\t\t");break;
              case 21:printf("Queen\t\t");break;
              case 22:printf("King\t\t");break;
              case 23:printf("Ace\t\t");break;
          }

          switch(card_deck[counter][1])
          {
              case 1:printf("Hearts\t\t");break;
              case 2:printf("Diamonds\t");break;
              case 3:printf("Clubs\t\t");break;
              case 4:printf("Spades\t\t");break;
          }
          printf("%d\t", card_deck[counter][2]);

          printf("%d\n", card_deck[counter][3]);
      }

}

void make_additional_attack(int defender_id, int card_restriction)
{
  int counter = 0;
  int deck_search_counter = 0;
  int last_element = 0;
  int card_id = 0;

  last_element = turn_array_counter;

  for(counter = 0; counter < 12;counter++)
  {
      if(counter == last_element)
      {
         break;
      }
      card_id = turn_array[counter];


      for(deck_search_counter = 0;deck_search_counter < 36;deck_search_counter++)
      {
         if(card_deck[deck_search_counter][0] == card_deck[card_id][0]
            && card_deck[deck_search_counter][2] != 0 && card_deck[deck_search_counter][2] != 10 && card_deck[deck_search_counter][2] != 11
            && card_deck[deck_search_counter][2] != defender_id
            && card_deck[deck_search_counter][3] != 1 && card_restriction >= 1)
         {
           card_deck[deck_search_counter][2] = 11;
           printf("A.ATTACK: %d\n", deck_search_counter);
           delay(3);
           turn_array[turn_array_counter] = deck_search_counter;
           turn_array_counter++;
           card_restriction--;
         }
      }
  }

}

int count_players_cards(int player_id)
{
   int counter = 0;
   int cards_in_hand = 0;

   for(counter = 0;counter < 36;counter++)
   {
       if(card_deck[counter][2] == player_id)
       {
         cards_in_hand++;
       }
   }

   return cards_in_hand;
}


int random(int n)
{
    return rand() % n;
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

void action_menu(void)
{
    int choice = 0;

    printf("1.Play\n");
    printf("2.Game description\n");
    printf("3.Exit\n");

    if(scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
    {
       do
       {
         printf("Choose from 1 to 3\n");
         fflush(stdin);
       }
        while(scanf("%d", &choice) != 1);
    }

     switch(choice)
     {
        case 1:game();break;
        case 2:game_description();break;
        case 3:exit(1);break;
     }




}

void game_description(void)
{
    int choice = 0;

    printf("Durak is a card game that is popular in post-Soviet states. The objective of the game is to get rid of all one's cards when there are no more cards left in the deck (see rules). At the end of the game, the last player with cards in their hand is the fool..\n");
    printf("\nDo you want to return to previous menu, or exit?\n");
    printf("1. Previous menu\n2. Exit from program\n");

    if(scanf("%d", &choice) != 1 || choice < 1 || choice > 2)
    {
       do
       {
         printf("Choose from 1 to 2\n");
         fflush(stdin);
       }
        while(scanf("%d", &choice) != 1 || choice < 1 || choice > 2);
    }

    switch(choice)
    {
        case 1:action_menu();break;
        case 2:exit(1);break;
    }
}

void repeat_program(void)
{
    int choice = 0;
    system("cls");
    printf("Whoa. Game over\nDo you want to run program one more time or to exit?\n");
    printf("1. Repeat\n2. Exit\n");

    if(scanf("%d", &choice) != 1 || choice < 1 || choice > 2)
    {
       do
       {
         printf("Choose from 1 to 2\n");
         fflush(stdin);
       }
        while(scanf("%d", &choice) != 1 || choice < 1 || choice > 2);
    }

    switch(choice)
    {
        case 1:main();break;
        case 2:exit(1);break;
    }
}



