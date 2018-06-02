#include <stdio.h>
#include <stdlib.h>

void greetings(void);
void game(void);
void initialize_deck(int players_amount);
void set_trump_suit(void);
void initialize_player_list(int players_amount);
void full_translate(void);
void translate(int face, int suit);
void temp_translate(int counter, int face, int suit, int player, int trump_suit);
void turn_manage(int players_amount);
void temp_turn_manage(int players_amount);
void find_min_card(int player_id);
void make_additional_attack(int defender_id, int card_restriction);
int count_players_cards(int player_id);
void counter_turn(int player_id);

int random(int n);

int card_deck[36][4];
int turn_array[6];

int turn_array_counter = 0;

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
    int players_amount = 0;

    printf("Enter number of players: ");
    scanf("%d", &players_amount);


    initialize_deck(players_amount);
    //turn_manage(players_amount);
    temp_turn_manage(players_amount);
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

    for(counter = 0;counter < 36;counter++)
    {
        //printf("%d\t%d\t%d\t%d\n", counter, card_deck[counter][0], card_deck[counter][1], card_deck[counter][2]);
        //printf("\n");
        temp_translate(counter, card_deck[counter][0], card_deck[counter][1], card_deck[counter][2], card_deck[counter][3]);
    }



}

void initialize_player_list(int players_amount)
{
  int counter = 0;
  int players_list[players_amount];


  for(counter = 0;counter < players_amount;counter++)
  {
       players_list[counter] = 1;
  }

}

void translate(int face, int suit)
{
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
}

void temp_translate(int counter, int face, int suit, int player, int trump_suit)
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

  switch(suit)
  {
      case 1:printf("Hearts\t\t");break;
      case 2:printf("Diamonds\t");break;
      case 3:printf("Clubs\t\t");break;
      case 4:printf("Spades\t\t");break;
  }
  printf("%d\t", player);

  printf("%d\n", trump_suit);
}

void turn_manage(int players_amount)
{
  int attacker_id = 0;
  int defender_id = 0;
  int turn_counter = 0;
  int counter = 0;
  int players_in_game_counter = 0;
  int players_list[players_amount];


  for(counter = 1;counter <= players_amount;counter++)
  {
     players_list[counter] = 1;
  }

  //players_list[players_amount - 1] = 0;

  for(turn_counter = 1;turn_counter <= players_amount;turn_counter++)
  {
      players_in_game_counter = 0;
      /*CHECK HOW MANY PLAYERS ARE IN GAME*/

      for(counter = 0;counter < players_amount;counter++)
      {

        if(players_list[counter] != 0)
        {
            players_in_game_counter++;
        }
      }



       /*IF THERE ARE MORE THAN 1 PLAYER CONTINUE GAME*/
      if(players_in_game_counter > 1)
      {

        if(turn_counter == players_amount)
        {
          attacker_id = turn_counter;
          turn_counter = 0;
          defender_id = turn_counter + 1;
          printf("Player %d on Player %d\n", attacker_id, defender_id);
        }
        else
        {
            attacker_id = turn_counter;
            defender_id = turn_counter + 1;

            printf("Player %d on Player %d\n", attacker_id, defender_id);
        }
      }
      else
      {
          printf("GAME OVER");
          break;
      }

  }

  find_min_card(attacker_id);

}

void find_min_card(int player_id)
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

void temp_turn_manage(int players_amount)
{
  int attacker_id = 0;
  int defender_id = 0;
  int turn_counter = 0;
  int card_to_beat_id = 0;
  int beaten_card_id = 0;
  int counter = 0;
  int players_in_game_counter = 3;
  int free_space = 0;
  int amount_to_make_move = 0;
  int card_move_restriction = 0;
  int players_list[players_amount];


  for(counter = 0;counter < 12;counter++)
  {
      turn_array[counter] = 0;
  }

  for(counter = 1;counter <= players_amount;counter++)
  {
     players_list[counter] = 1;
  }

  //players_list[players_amount - 1] = 0;

  for(turn_counter = 1;turn_counter <= players_amount;turn_counter++)
  {
      players_in_game_counter--;
      /*CHECK HOW MANY PLAYERS ARE IN GAME*/
      /*
      for(counter = 0;counter < players_amount;counter++)
      {

        if(players_list[counter] != 0)
        {
            players_in_game_counter++;
        }
      }
      */



       /*IF THERE ARE MORE THAN 1 PLAYER CONTINUE GAME*/
      if(players_in_game_counter > 1)
      {

        if(turn_counter == players_amount)
        {
          attacker_id = turn_counter;
          turn_counter = 0;
          defender_id = turn_counter + 1;
          printf("Player %d on Player %d\n", attacker_id, defender_id);
        }
        else
        {
            attacker_id = turn_counter;
            defender_id = turn_counter + 1;

            printf("Player %d on Player %d\n", attacker_id, defender_id);
        }

        find_min_card(attacker_id);
        counter_turn(defender_id);

        /*CALCULATING CARD RESTRICTION FOR ADDITIONAL ATTACK*/
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
        counter_turn(defender_id);

        full_translate();


        printf("PLAYER %d |AMOUNT OF CARDS IN HAND - %d\n", defender_id, amount_to_make_move);

        printf("BUSY - %d;FREE - %d\n", turn_array_counter, free_space);

        for(counter = 0;counter < 12;counter++)
        {
          printf("turn_array[%d] = %d\n", counter, turn_array[counter]);
          beaten_card_id = turn_array[counter];
          card_deck[beaten_card_id][2] = 0;
          turn_array[counter] = 0;
        }

      }
      else
      {
          printf("GAME OVER");
          break;
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

void counter_turn(int player_id)
{
  int counter = 0;
  int search_counter = 0;
  int min_card = 100;
  int min_card_id = 0;
  int card_to_beat_id = 0;


  for(counter = 0;counter < 12;counter++)
  {
     card_to_beat_id = turn_array[counter];

     /*IF CARD HAS NOT BEEN BEAT YET*/

     if(card_deck[card_to_beat_id][2] == 11)
     {

        /*
       if(counter > 0 && card_to_beat_id == 0)
         {
             printf("False call 0\n");
             break;
         }
         if(card_deck[card_to_beat_id][2] == player_id)
         {
             printf("False call BEAT CARD\n");
             break;
         }


         if(card_deck[card_to_beat_id][2] == 10 || card_deck[card_to_beat_id][2] == 0)
         {
             printf("10 PLAYER or 0 PLAYER\n");
             break;
         }
         */



         for(search_counter = 0;search_counter < 36;search_counter++)
         {
             /*FIRSTLY SEARCH NOT TRUMP CARD TO BEAT*/
             if(card_deck[search_counter][0] < min_card && card_deck[search_counter][0] > card_deck[card_to_beat_id][0]
                && card_deck[search_counter][1] == card_deck[card_to_beat_id][1] &&
                card_deck[search_counter][2] == player_id
                && card_deck[search_counter][3] != 1)
             {
                min_card_id = search_counter;
                min_card = card_deck[min_card_id][0];

                /*IF THERE ARE NO CARD TO BEAT - SEARCH THE SMALLEST TRUMP CARD*/
                if(min_card_id == 0 && min_card == 100)
                {
                    printf("OOOPS BEATING WITH TRUMP CARD\n");
                  if(card_deck[search_counter][0] < min_card && card_deck[search_counter][0] > card_deck[card_to_beat_id][0]
                      && card_deck[search_counter][1] == card_deck[card_to_beat_id][1]
                      && card_deck[search_counter][2] == player_id)
                  {
                    min_card_id = search_counter;
                    min_card = card_deck[min_card_id][0];
                  }
                }
             }
         }
         turn_array[turn_array_counter] = min_card_id;
         card_deck[card_to_beat_id][2] = 10;
         card_deck[min_card_id][2] = 10;
         printf("BEAT %d WITH %d\n", card_to_beat_id, min_card_id);
         min_card_id = 0;
         min_card = 100;
         turn_array_counter++;
     }

  }

}

void full_translate(void)
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
  int card_id = 0;

  for(counter = 0; counter < 12;counter++)
  {
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

