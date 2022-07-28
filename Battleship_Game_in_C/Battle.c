
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
#include<time.h>


// Game title Display
char game_title[33][40] =
  {
    {' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ','*',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*','*','*','*'},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ','*','*','*',' ',' ','#','#',' ','*','*','*','*','*','*','*','*',' ','*','*',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','*','*','*','*','*',' ','#','#',' ','*','*','*','*','*','*','*','*',' ','*','*',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ',' ',' ',' ','*','*',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#','#',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',' ',' ',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ',' ','*','*','*','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#','#',' ','*','*','*','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*','*','*','*','*'},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ','*','*',' ','#','#',' ',' ',' ',' ','*','*',' ','#','#',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#','#',' ','*','*',' ','*','*',' ',' ',' ',' ',' ',' ',' ','*','*',' ','#','#',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ','*','*',' ','*','*',' ',' ',' ',' ',' ',' ',' ','*','*',' ','#','#','#','#','#','#','#',' ',' '},
    {' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',' ',' ',' ','*',' ',' ','*',' ',' ','#','#','#','#','#','#','#','#',' ','*','*','*','*','*',' ',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#',' ',' ','*','*',' ',' ','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*','*','*','*','*',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ','*','*',' ',' ','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*',' ',' ','*','*',' ',' '},
    {' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*',' ',' ','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*',' ',' ','*','*',' ',' '},
    {' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','*','*',' ',' ','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*',' ',' ','*','*',' ',' '},
    {' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#',' ',' ',' ','*','*',' ',' ','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*',' ',' ','*','*',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#',' ',' ','*','*','*','*','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*','*','*','*','*',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ','*','*','*','*','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*','*','*','*',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ',' ','*','*',' ',' ',' ',' ','#','#',' ',' ',' ',' ','*','*',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ',' ','*','*',' ','#','#','#','#','#','#','#','#',' ','*','*',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#','#',' ','*','*',' ',' ','*','*',' ',' ','#','#','#','#','#','#',' ',' ','*','*',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',' ',' ','*','*',' ',' ','*','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ','*',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*',' ',' ',' ',' ',' ',' '}

  };

//  For my Battlefield
char MyBattlefieldArray[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'b','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'c','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'd','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'e','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'f','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'g','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'h','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'i','.','.','.','.','.','.','.','.','.','.',' '},
    { 'j','.','.','.','.','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}

     };

// for my Friend's Battlefield
char MyFriendsBattlefieldArray[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'b','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'c','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'd','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'e','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'f','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'g','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'h','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'i','.','.','.','.','.','.','.','.','.','.',' '},
    { 'j','.','.','.','.','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };

 // Empty battle field for the user to guess position while attacking opponent ships
char EmptyFieldMine[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'b','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'c','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'd','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'e','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'f','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'g','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'h','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'i','.','.','.','.','.','.','.','.','.','.',' '},
    { 'j','.','.','.','.','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
char EmptyFieldFriend[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'b','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'c','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'd','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'e','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'f','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'g','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'h','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'i','.','.','.','.','.','.','.','.','.','.',' '},
    { 'j','.','.','.','.','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
char EmptyFieldPc[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'b','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'c','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'd','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'e','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'f','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'g','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'h','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'i','.','.','.','.','.','.','.','.','.','.',' '},
    { 'j','.','.','.','.','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };

//Below: pre defined battlefields and ships for the pc. A.I selects any one of the Battlefield(including ships) randomely.
char a[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','O','O','O','.','.','.','.','.','.','O',' '},
	{ 'b','.','.','.','O','.','.','.','.','.','O',' '},
	{ 'c','O','.','.','O','.','.','.','.','.','O',' '},
	{ 'd','O','.','O','.','O','O','.','.','.','O',' '},
	{ 'e','O','.','O','.','.','.','.','.','.','O',' '},
	{ 'f','.','.','.','O','O','.','.','.','.','.',' '},
	{ 'g','O','O','O','.','.','.','.','.','.','.',' '},
	{ 'h','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'i','.','.','.','.','O','O','O','O','.','.',' '},
    { 'j','O','O','O','O','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
char b[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','O','O','O','.','O','O',' '},
	{ 'b','.','.','.','O','.','.','.','.','.','.',' '},
	{ 'c','.','.','.','O','.','O','O','O','.','.',' '},
	{ 'd','.','.','.','O','.','.','.','.','O','O',' '},
	{ 'e','.','.','.','O','.','O','.','.','.','.',' '},
	{ 'f','.','.','.','.','.','O','.','O','O','.',' '},
	{ 'g','.','.','.','O','.','O','.','.','.','.',' '},
	{ 'h','.','.','.','O','.','.','.','O','O','.',' '},
	{ 'i','.','.','.','O','.','.','.','.','.','.',' '},
    { 'j','.','.','.','O','.','O','O','O','O','O',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
char c[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'b','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'c','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'd','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'e','O','.','.','O','.','O','.','O','.','.',' '},
	{ 'f','.','.','.','O','.','O','.','O','.','.',' '},
	{ 'g','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'h','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'i','O','.','O','.','O','.','O','O','.','.',' '},
    { 'j','.','.','.','.','.','.','.','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
char d[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','O','O','O','O','.','.','.','.','.',' '},
	{ 'b','.','.','.','.','.','.','.','O','O','O',' '},
	{ 'c','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'd','.','O','O','O','O','O','.','O','O','O',' '},
	{ 'e','.','.','.','.','.','.','.','.','.','.',' '},
	{ 'f','O','.','.','.','.','.','.','O','O','O',' '},
	{ 'g','O','.','O','.','.','.','.','.','.','.',' '},
	{ 'h','O','.','O','.','O','.','.','.','.','.',' '},
	{ 'i','O','.','.','.','O','.','.','.','.','.',' '},
    { 'j','.','.','O','O','.','O','O','.','.','.',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };

char e[12][12] = {

	{ ' ','0','1','2','3','4','5','6','7','8','9',' '},
	{ 'a','.','.','.','.','.','O','O','O','.','.',' '},
	{ 'b','.','O','.','.','.','.','.','.','.','.',' '},
	{ 'c','.','O','.','O','.','O','O','O','.','.',' '},
	{ 'd','.','.','.','O','.','.','.','.','.','.',' '},
	{ 'e','.','O','.','.','.','O','O','O','.','.',' '},
	{ 'f','.','O','.','.','.','.','.','.','.','O',' '},
	{ 'g','.','.','.','O','.','O','.','.','.','O',' '},
	{ 'h','.','.','.','O','.','O','.','.','.','O',' '},
	{ 'i','.','O','.','O','.','O','.','.','.','O',' '},
    { 'j','.','O','.','O','.','O','.','.','.','O',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };


char u[12][12];// After selecting a random battlefield , that random battlefield will be copied in this array


// for counting purpose, So that user cant go over the game rules
int TotalshipsMine=0;
int TotalshipsFriends=0;
int Box2CountMine=0;
int Box3CountMine=0;
int Box4CountMine=0;
int Box5CountMine=0;
int Box2CountFriend=0;
int Box3CountFriend=0;
int Box4CountFriend=0;
int Box5CountFriend=0;
int MeCount=0;
int FriendCount=0;
int MCount=0;
int PcCount=0;

// indication for the compiler that whole function is written after main() function;
void print_game_title(); // function to display game title
void MainMenu(); // function to display mainmenu
void Friends(); // function to display the menu for two user game play
void DifficultyLevel(); // function for difficulty levbel selection
int StartGamePc(); // function for Gameplay with A.I
int SelfTurn(); // function for attacking ships playing with A.I
int PcTurn(); // Function for attacking my aships by A.I
int MyTurn();// function for attacking opponent ships while playing with friends
int FriendsTurn();// functions for attacking my ships by my friend while playing with friends
int clear (); // function to clear all input in the battle field
int StartGame(); // function for gamplay between two friends
int ForwardPlace(int,int,int,int);// function to place ships forward
int BackwardPlace(int,int,int,int);// function to place ship backward
int UpwardPlace(int,int,int,int);// function to place ship upwaard
int DownwardPlace(int,int,int,int);// function to place ship downward
int Counter(int,int); // a function to handle all counting activity
int Placeshipcontrol(int,int); // function for placing ship piurpose
void PrintBattlefield(int);   // a function to display battlefield ground
void Placeships(int); // function to place ships
void ForwardBox(int,int); // for placing ships forward
void BackwardBox(int,int); // for placing ships backward
void UpwardBox(int,int); // for placing ships Upward
void DownwardBox(int,int); // for placing ships Downward

// Starting the main function
int main()
{
    print_game_title();
    sleep(4);
    printf("\n\n");
	MainMenu();
	getch();
}


void MainMenu()                   // functiion declaration for main Menu.
{
    system("cls");
	int UserInput;
	//  main menu option list
	printf("(1)Play with A.I (Artificial intelligence)\n");
	printf("(2)Play with a friend\n");
	printf("(3)Clear all Battlefield\n");
	printf("(4)Difficulty level selection\n");
	printf("(5)Quit Game\n\n");
	printf("Please, enter an option number to select it . \n"); // instruction for user to select options.
	scanf("%d", &UserInput);
	while (getchar() != '\n'); // for avoiding input buffer problem in C
	printf("\n");

    if(UserInput==1)
                {
                   int k;
                   system("cls");
                   printf("(1) Place your ships\n");
                   printf("(2) View Your Battlefield\n");
                   printf("(3) Start Game\n(4) Back \n");
                   scanf("%d",&k);
                   if(k==1){
                       Placeships(1);
                      }

                   else if (k==2)
			        	{
				        system("cls");   // to clean the console display
			            PrintBattlefield(1);
			            sleep(5);  // to wait function execution for a moment.
			            system("cls");
			            MainMenu();
				            }
                   else if(k==3) {
                      StartGamePc();
                   }
                   else if(k==4) {
                      MainMenu();
                   }
                   else {
                       MainMenu();}
                     }
	else if (UserInput == 2)
	{
		printf("\n\n");
		system("cls");
		Friends();
	}
	else if (UserInput == 3)
	{
		printf("\n");
		system("cls");
		clear();
		system("cls");
	    printf("All Battlefield data are Cleared\n\n");
	    sleep(2);
	    MainMenu();

	}
	else if (UserInput == 4)
	{
		printf("\n\n");
		system("cls");
		DifficultyLevel();
	}
	else if (UserInput == 5)
	{
		exit(0);
	}
	else {
		system("cls");
		printf("Try Again\n\n");
		MainMenu();
	}


}


void Friends()        // to display the options if user selects "Play with a friend mode"
{

	int FriendOption;

	printf("(1) Place your ships\n");
	printf("(2) Place your friend's ships\n");
	printf("(3) Start the Game\n");
	printf("(4) View your Battlefield\n");
	printf("(5) View your friend's Battlefield\n");
	printf("(6) Back\n\n");

	printf("Please, enter an option number to select it . \n"); // instruction for user to select options.
	scanf("%d", &FriendOption);
	while (getchar() != '\n');
	printf("\n");


	if (FriendOption == 1)   //  opening My BattleField
	            {
	        	Placeships(1);
	            }

	else if (FriendOption==2)
				{
				Placeships(2);
				}
	else if (FriendOption==3)
				{
				StartGame();
				}
	else if (FriendOption==4)
				{
				system("cls");
			    PrintBattlefield(1);
			    sleep(5);
			    system("cls");
			    Friends();
				}
	else if (FriendOption==5)
				{
				system("cls");
			    PrintBattlefield(2);
			    sleep(5);
			    system("cls");
			    Friends();
				}
	else if (FriendOption == 6)    // Going back to main menu
	        {
	    	printf("\n\n");
	    	MainMenu();
	}


	else {
		printf("\n\n");
		system("cls");
		printf("Try again \n\n");
		Friends();
	    }

}

void DifficultyLevel()     // display the options to select difficulty level
{
	int difficulty;
	printf("(1) Easy\n");
	printf("(2) Medium\n");
	printf("(3) Hard\n");
	printf("(4) Back\n\n");

	printf("Please, enter an option number to select it . \n"); // instruction for user to select options.
	scanf("%d", &difficulty);
	while (getchar() != '\n');

	if (difficulty == 1)
	{
	    system("cls");
		printf("Difficulty level \"Easy \" selected\n\n");
		sleep(2);
		MainMenu(); // Go back to the main menu
	}
	else if (difficulty == 2)
	{   system("cls");
		printf("Difficulty level \"Medium \" selected\n\n");
		sleep(2);
		MainMenu(); // Go back to the main menu

	}


	else if (difficulty == 3)
	{   system("cls");
		printf("Difficulty level \"Hard \" selected\n\n");
		sleep(2);
		MainMenu(); // Go back to the main menu

	}
	else if (difficulty == 4)
	{
		MainMenu(); // Go back to the main menu

	}
	else {
	    system("cls");
	    printf("Invalid Input. Please try again.\n");
	    sleep(2);
	    system("cls");
		DifficultyLevel();
	}

}



void Placeships(int r)   // for placing ships in my battlefield and in y friends battlefield . r=1 for my battlefield & r= 2 for my friends battlefield
{

 if(r==1)  {  system("cls");

 if(TotalshipsMine<10)   // checking total ship count to avoid exceeding the limit
       {
        PrintBattlefield(1);
        int t;
	    printf("Please select your ship's size from the list\n");
	    printf("(1) Ships that occupies 2 boxes in the battlefield (total 4 ships)\n");
    	printf("(2) Ships that occupies 3 boxes in the battlefield (total 3 ships)\n");
    	printf("(3) Ships that occupies 4 boxes in the battlefield (total 2 ships)\n");
    	printf("(4) Ships that occupies 5 boxes in the battlefield (total 1 ships)\n");
    	scanf("%d",&t);
	    while (getchar() != '\n');
	    if(t==1)
	            {
	                if(Box2CountMine<4){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	            }
	    else if(t==2)
	                {
	                if(Box3CountMine<3){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	                }
	    else if (t==3)
	                {
	                if(Box4CountMine<2){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	                }
	    else if (t==4)
	                {
	                if(Box5CountMine==0){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	                }
	    else{
	              system("cls");
	              printf("Invalid input. Please Try again\n\n");
	              sleep(3);
	              Placeships(r);
	              }
       }
  else {
      system("cls");
      printf("All ships are placed. Going back to the main menu\n");

      sleep(3);
      MainMenu();

         }
  }




 if(r==2)  {  system("cls");

 if(TotalshipsFriends<10)
  {

        int t;
        PrintBattlefield(2);
	    printf("Please select your ship's size from the list\n");
	    printf("(1) Ships that occupies 2 boxes in the battlefield (total 4 ships)\n");
    	printf("(2) Ships that occupies 3 boxes in the battlefield (total 3 ships)\n");
    	printf("(3) Ships that occupies 4 boxes in the battlefield (total 2 ships)\n");
    	printf("(4) Ships that occupies 5 boxes in the battlefield (total 1 ships)\n");
    	scanf("%d",&t);
	    while (getchar() != '\n');
	    if(t==1)
	            {
	                if(Box2CountFriend<4){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	            }
	    else if(t==2)
	                {
	                if(Box3CountFriend<3){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	                }
	    else if (t==3)
	                {
	                if(Box4CountFriend<2){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	                }
	    else if (t==4)
	                {
	                if(Box5CountFriend==0){
	                             Placeshipcontrol(t,r);}
	             	else{
	             	       system("cls");
	             	       printf("Maximum limit reached , Please select another ship with different size\n\n");
	             	       sleep(3);
	                       Placeships(r);
	                     }
	                }
	    else{
	              system("cls");
	              printf("Invalid input. Please Try again\n\n");
	              sleep(3);
	              Placeships(r);
	              }
  }
  else {
        system("cls");
        printf("All ships are placed. Going back to the main menu\n\n\n");
        sleep(3);
        MainMenu();
                }
}

}
void ForwardBox(int t, int r)  // placing ship forward from the starting position
{
	char p;
	int q, x, y;

	printf("keeping minimum 1 box distance from another ship please enter your ship's starting position on this sequence: ( raw --> column)\n");
	scanf("%c%d", &p, &q); // user input (position) are kept in p and q variable
	while (getchar() != '\n');

	if(q>=0 && q<=9 )
	{
    if(q>=0 || q<=9)
     	{

	y = q + 1;  // this is to avoid confusion working with array, instead of q, we work with y for the rest of the program

	switch (p) {
	case 'a':
	    x = 1; // this is to avoid confusion working with array, instead of p, we work with x for the rest of the program
          ForwardPlace(x,y,t,r);
		  break;
	case 'b':
		x = 2;
          ForwardPlace(x,y,t,r);
		break;
	case 'c':
		x = 3;
          ForwardPlace(x,y,t,r);
		break;
	case 'd':
		x = 4;
          ForwardPlace(x,y,t,r);
		break;
	case 'e':
		x = 5;
          ForwardPlace(x,y,t,r);
		break;
	case 'f':
		x = 6;
          ForwardPlace(x,y,t,r);
		break;
	case 'g':
		x = 7;
          ForwardPlace(x,y,t,r);
		break;
	case 'h':
		x = 8;
          ForwardPlace(x,y,t,r);
		break;
	case 'i':
		x = 9;
          ForwardPlace(x,y,t,r);
		break;
	case 'j':
		x = 10;
          ForwardPlace(x,y,t,r);
		break;

	default:
	    system("cls");
		printf("invalid input \n");
		sleep(2);
		break;
	}
     	}

	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    ForwardBox(t,r);
      	}
      }
	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    ForwardBox(t,r);
      	}
}

void BackwardBox(int t,int r)  // for placing ship backward
{
	char p;
	int i, q, x, y;

	printf("keeping minimum 1 box distance from another ship please enter your ship's starting position on this sequence: ( raw --> column)\n");
	scanf("%c%d", &p, &q);
	while (getchar() != '\n');

	if(q>=0 && q<=9 )
	{
    if(q>=0 || q<=9)
     	{

	y = q + 1;
	switch (p) {
	case 'a':
		x = 1;
            BackwardPlace(x,y,t,r);
		break;
	case 'b':
		x = 2;
            BackwardPlace(x,y,t,r);
		break;
	case 'c':
		x = 3;
            BackwardPlace(x,y,t,r);
		break;
	case 'd':
		x = 4;
            BackwardPlace(x,y,t,r);
		break;
	case 'e':
		x = 5;
            BackwardPlace(x,y,t,r);
		break;
	case 'f':
		x = 6;
            BackwardPlace(x,y,t,r);
		break;
	case 'g':
		x = 7;
            BackwardPlace(x,y,t,r);
		break;
	case 'h':
		x = 8;
            BackwardPlace(x,y,t,r);
		break;
	case 'i':
		x = 9;
            BackwardPlace(x,y,t,r);
		break;
	case 'j':
	    x = 10;
            BackwardPlace(x,y,t,r);
		break;

	default:
	    system("cls");
		printf("invalid input \n");
		sleep(2);
		break;
	    }
     	}

	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    BackwardBox(t,r);

      	}
       }
	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    BackwardBox(t,r);

      	}
}

void DownwardBox(int t,int r)   // for placinf ships downward
{
	char p;
	int i, q, x, y;

	printf("keeping minimum 1 box distance from another ship please enter your ship's starting position on this sequence: ( raw --> column)\n");
	scanf("%c%d", &p, &q);

	if(q>=0 && q<=9 )
	{
	while (getchar() != '\n');
	if(q>=0 || q<=9)
	   {
	y = q + 1;
	switch (p) {
	case 'a':
		x = 1;
            DownwardPlace(x,y,t,r);

		break;
	case 'b':
	    x = 2;
            DownwardPlace(x,y,t,r);
		break;
	case 'c':
		x = 3;
            DownwardPlace(x,y,t,r);
		break;
	case 'd':
		x = 4;
            DownwardPlace(x,y,t,r);
		break;
	case 'e':
		x = 5;
            DownwardPlace(x,y,t,r);
		break;
	case 'f':
		x = 6;
            DownwardPlace(x,y,t,r);
		break;
	case 'g':
		x = 7;
            DownwardPlace(x,y,t,r);
		break;
	case 'h':
		x = 8;
            DownwardPlace(x,y,t,r);
		break;
	case 'i':
		x = 9;
            DownwardPlace(x,y,t,r);
		break;
	case 'j':
		x = 10;
            DownwardPlace(x,y,t,r);
		break;

	default:
	    system("cls");
		printf("invalid input \n");
		sleep(2);
		break;
	       }
	}

	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    DownwardBox(t,r);
      	}
   }
else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    DownwardBox(t,r);
      	}
}

void UpwardBox(int t,int r)   // for placing ships upward
{
	char p;
	int i, q, x, y;

	printf("keeping minimum 1 box distance from another ship please enter your ship's starting position on this sequence: ( raw --> column)\n");
	scanf("%c%d", &p, &q);
	while (getchar() != '\n');
	if(q>=0 && q<=9 )
	{

	if(q>=0 || q<=9)
	{

	y = q + 1;
	switch (p) {
	case 'a':
		x = 1;
            UpwardPlace(x,y,t,r);
		break;
	case 'b':
		x = 2;
            UpwardPlace(x,y,t,r);
		break;
	case 'c':
		x = 3;
            UpwardPlace(x,y,t,r);
		break;
	case 'd':
		x = 4;
            UpwardPlace(x,y,t,r);
		break;
	case 'e':
		x = 5;
            UpwardPlace(x,y,t,r);
		break;
	case 'f':
	      x=6;
            UpwardPlace(x,y,t,r);
		break;
	case 'g':
		x = 7;
            UpwardPlace(x,y,t,r);
		break;
	case 'h':
		x = 8;
            UpwardPlace(x,y,t,r);
		break;
	case 'i':
		x = 9;
            UpwardPlace(x,y,t,r);
		break;
	case 'j':
		x = 10;
            UpwardPlace(x,y,t,r);
		break;

	default:
	    system("cls");
		printf("invalid input \n");
		sleep(2);
		break;
	}

	}

	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    UpwardBox(t,r);
      	}

    }
	else {
	    system("cls");
	    printf("Invalid Input, Please try again \n\n");
	    sleep(2);
	    PrintBattlefield(r);
	    UpwardBox(t,r);
      	}
}


int Counter(int t, int r)     // counting part is handled with this function
     {
       	if(r==2){
		         TotalshipsFriends = TotalshipsFriends+1;
		         if(t==1){Box2CountFriend=Box2CountFriend+1;}
		         if(t==2){Box3CountFriend=Box3CountFriend+1;}
		         if(t==3){Box4CountFriend=Box4CountFriend+1;}
		         if(t==4){Box5CountFriend=Box5CountFriend+1;}
		         }
		if(r==1){
		         TotalshipsMine=TotalshipsMine+1;
		         if(t==1){Box2CountMine = Box2CountMine+1;}
		         if(t==2){Box3CountMine = Box3CountMine+1;}
		         if(t==3){Box4CountMine = Box4CountMine+1;}
		         if(t==4){Box5CountMine = Box5CountMine+1;}
		         }

     }


int Placeshipcontrol(int t, int r)   // this function is calledin ship placing part
        {
                char VHInput;
                printf("Ship type ");
            	printf("(%d) is selected\n",t);
            	printf("Enter \'h\' to put your ship horizontally or \'v\' to place your ship vertically\n");
            	VHInput = getchar();
            	while (getchar() != '\n');
    	        if (VHInput == 'h')
                            	{
	                        	char forback;
	                        	printf("Enter \'f\' to place your ship forward or Enter  \'b\' to place backward from your desired position\n");
		                        forback = getchar();
		                        while (getchar() != '\n');
	        	                switch (forback) {
        		                            case 'f':
		            	                             ForwardBox(t,r);
			                                         Placeships(r);
		              	                             break;
	        	                            case 'b':
		                                             BackwardBox(t,r);
		                                             Placeships(r);
		            	                             break;
		                                    default:
		                                             system("cls");
		        	                                 printf("Invalid input. Please Try again.\n");
	        	                                     sleep(2);
		                                             Placeships(r);
		            	                             break;
		                                           }
	                              }
    	         else if (VHInput == 'v')
            	                  {
	           	                    char UpDown;
		                            printf(" enter \'u\' to place your ship upward or enter \'d\' to place downward from your  desired starting position\n");
	        	                    UpDown = getchar();
		                            while (getchar() != '\n');
		                            switch (UpDown) {
	                                        case 'u':
		                                        	UpwardBox(t,r);
			                                        Placeships(r);
			                                        break;
	                                        case 'd':
		                                        	DownwardBox(t,r);
		                                         	Placeships(r);
		                                        	break;
	        	                            default:
	        	                                    system("cls");
	        	                                    printf("Invalid input. Please Try again.\n");
	        	                                    sleep(2);
		                                            Placeships(r);
			                                        break;
		                                              }
	                                 }

	              else{
	                    system("cls");
	                    printf("Invalid input. Please Try again\n\n");
	                    sleep(2);
	                    Placeships(r);
	                   }
	       }









void PrintBattlefield( int r)   // a function to display battlefield ground

{
	int i, j;
	for (i = 0; i<11; i++)
	{
		printf("                               ");
		for (j = 0; j<11; j++)
		{
			printf("  ");
			if(r==1){printf("%c", MyBattlefieldArray[i][j]);}
			if(r==2){printf("%c",MyFriendsBattlefieldArray[i][j]);}
			if(r==3){printf("%c",EmptyFieldMine[i][j]);}
			if(r==6){printf("%c",EmptyFieldFriend[i][j]);}
			if(r==7){printf("%c",EmptyFieldPc[i][j]);}


			printf("  ");
		}
		printf("\n\n");
	}
}


void print_game_title()  // a function to display the game title
        {

            printf("\n\n\n\n");
      for (int j = 0; j < 19; j++) {
                   printf("     ");
                for (int i = 0; i < 40; i++) {
                     printf(" ");
                     printf("%c",game_title[j][i]);
                                  }
                     printf("\n");
                     usleep(100000);
                        }
      sleep(1);

      for (int j = 19; j < 33; j++) {
              printf("                                                   ");

                for (int i = 0; i < 40; i++) {
                     printf(" ");
                     printf("%c",game_title[j][i]);
                                  }
                     printf("\n");
                     usleep(100000);
                        }
   }



 int ForwardPlace(int x, int y , int t, int r)   // forward ship place ment
                    {
        if((y+t)<=10)
		          {
		            if (t==1)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y+2]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x+1][y+1]!='O')
		                                {
		                                Counter(t,r);
		                                 for (int i = y; i <= (y + t); i++)
		                                     {
		                                   MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y+2]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i <= (y + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }

		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }
		            else if (t==2)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y+2]!='O'&& MyBattlefieldArray[x][y+3]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x+1][y+1]!='O' && MyBattlefieldArray[x-1][y+2]!='O' && MyBattlefieldArray[x+1][y+2]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = y; i <= (y + t); i++)
		                                     {
		                                    MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y+2]!='O'&& MyFriendsBattlefieldArray[x][y+3]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O'&&MyFriendsBattlefieldArray[x-1][y+2]!='O' && MyFriendsBattlefieldArray[x+1][y+2]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i <= (y + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }
		            else if(t==3)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y+2]!='O'&& MyBattlefieldArray[x][y+3]!='O'&& MyBattlefieldArray[x][y+4]!='O'&& MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y]!='O' &&MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x+1][y+1]!='O'&&MyBattlefieldArray[x-1][y+2]!='O' && MyBattlefieldArray[x+1][y+2]!='O'&&MyBattlefieldArray[x-1][y+3]!='O' && MyBattlefieldArray[x+1][y+3]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = y; i <= (y + t); i++)
		                                     {
		                                    MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y+2]!='O'&& MyFriendsBattlefieldArray[x][y+3]!='O'&& MyFriendsBattlefieldArray[x][y+4]!='O'&& MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O'&&MyFriendsBattlefieldArray[x-1][y+2]!='O' && MyFriendsBattlefieldArray[x+1][y+2]!='O'&&MyFriendsBattlefieldArray[x-1][y+3]!='O' && MyFriendsBattlefieldArray[x+1][y+3]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i <= (y + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }

		                }
		            else
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y+2]!='O'&& MyBattlefieldArray[x][y+3]!='O'&& MyBattlefieldArray[x][y+4]!='O' && MyBattlefieldArray[x][y+5]!='O'  && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x+1][y+1]!='O' && MyBattlefieldArray[x-1][y+2]!='O' && MyBattlefieldArray[x+1][y+2]!='O'&& MyBattlefieldArray[x-1][y+3]!='O' && MyBattlefieldArray[x+1][y+3]!='O'&& MyBattlefieldArray[x-1][y+4]!='O' && MyBattlefieldArray[x+1][y+4]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = y; i <= (y + t); i++)
		                                     {
		                                    MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y+2]!='O'&& MyFriendsBattlefieldArray[x][y+3]!='O'&& MyFriendsBattlefieldArray[x][y+4]!='O'&& MyFriendsBattlefieldArray[x][y+5]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O'&&MyFriendsBattlefieldArray[x-1][y+2]!='O' && MyFriendsBattlefieldArray[x+1][y+2]!='O'&&MyFriendsBattlefieldArray[x-1][y+3]!='O' && MyFriendsBattlefieldArray[x+1][y+3]!='O'&&MyFriendsBattlefieldArray[x-1][y+4]!='O' && MyFriendsBattlefieldArray[x+1][y+4]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i <= (y + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }


		                }
		          }


		else { system("cls");
		      printf(" You can't place your ship here, Please Try again\n");
		      sleep(2);
		      system("cls");
	          Placeships(r);
		 }
}

 int BackwardPlace(int x, int y, int t, int r) // backward ship place ment
                    {
        if((y-t)>0)
		       {
		            if (t==1)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y-2]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x-1][y-1]!='O')
		                                {
		                                Counter(t,r);
		                                 for (int i = y; i >= (y - t); i--)
		                                     {
		                                   MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y-2]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i >= (y - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }

		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }
		            else if (t==2)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y-2]!='O'&& MyBattlefieldArray[x][y-3]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x-1][y-1]!='O' && MyBattlefieldArray[x+1][y-2]!='O' && MyBattlefieldArray[x-1][y-2]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = y; i >= (y - t); i--)
		                                     {
		                                    MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y-2]!='O'&& MyFriendsBattlefieldArray[x][y-3]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O'&&MyFriendsBattlefieldArray[x+1][y-2]!='O' && MyFriendsBattlefieldArray[x-1][y-2]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i >= (y - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }
		            else if(t==3)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y-2]!='O'&& MyBattlefieldArray[x][y-3]!='O'&& MyBattlefieldArray[x][y-4]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y]!='O' &&MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x-1][y-1]!='O'&&MyBattlefieldArray[x+1][y-2]!='O' && MyBattlefieldArray[x-1][y-2]!='O'&&MyBattlefieldArray[x+1][y-3]!='O' && MyBattlefieldArray[x-1][y-3]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = y; i >= (y - t); i--)
		                                     {
		                                    MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y-2]!='O'&& MyFriendsBattlefieldArray[x][y-3]!='O'&& MyFriendsBattlefieldArray[x][y-4]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O'&&MyFriendsBattlefieldArray[x+1][y-2]!='O' && MyFriendsBattlefieldArray[x-1][y-2]!='O'&&MyFriendsBattlefieldArray[x+1][y-3]!='O' && MyFriendsBattlefieldArray[x-1][y-3]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i >= (y - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }

		                }
		            else
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y-2]!='O'&& MyBattlefieldArray[x][y-3]!='O'&& MyBattlefieldArray[x][y-4]!='O' && MyBattlefieldArray[x][y-5]!='O'  && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x-1][y-1]!='O' && MyBattlefieldArray[x+1][y-2]!='O' && MyBattlefieldArray[x-1][y-2]!='O'&& MyBattlefieldArray[x+1][y-3]!='O' && MyBattlefieldArray[x-1][y-3]!='O'&& MyBattlefieldArray[x+1][y-4]!='O' && MyBattlefieldArray[x-1][y-4]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = y; i >= (y - t); i--)
		                                     {
		                                    MyBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y-2]!='O'&& MyFriendsBattlefieldArray[x][y-3]!='O'&& MyFriendsBattlefieldArray[x][y-4]!='O'&& MyFriendsBattlefieldArray[x][y-5]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O'&&MyFriendsBattlefieldArray[x+1][y-2]!='O' && MyFriendsBattlefieldArray[x-1][y-2]!='O'&&MyFriendsBattlefieldArray[x+1][y-3]!='O' && MyFriendsBattlefieldArray[x-1][y-3]!='O'&&MyFriendsBattlefieldArray[x+1][y-4]!='O' && MyFriendsBattlefieldArray[x-1][y-4]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = y; i >= (y - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[x][i] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }


		                }
		        }

		  else {system("cls");
		      printf(" You can't place your ship here, Please Try again\n");
		      sleep(2);
		      system("cls");
	          Placeships(r);
		        }
                    }
 int UpwardPlace(int x , int y, int t, int r) // upward ship placement
                    {

		 if((x-t)>0)
		  {

		  		    if (t==1)
		  		         {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x-2][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x-1][y-1]!='O')
		                                {
		                                Counter(t,r);
		                                 for (int i = x; i >= (x - t); i--)
		                                     {
		                                   MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x-2][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i >= (x - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }

		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		  		         }
		            else if (t==2)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x-2][y]!='O'&& MyBattlefieldArray[x-3][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x-1][y-1]!='O' && MyBattlefieldArray[x-2][y+1]!='O' && MyBattlefieldArray[x-2][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = x; i >= (x - t); i--)
		                                     {
		                                    MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x-2][y]!='O'&& MyFriendsBattlefieldArray[x-3][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O'&&MyFriendsBattlefieldArray[x-2][y+1]!='O' && MyFriendsBattlefieldArray[x-2][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i >= (x - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }
		            else if(t==3)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x-2][y]!='O'&& MyBattlefieldArray[x-3][y]!='O'&& MyBattlefieldArray[x-4][y]!='O'&& MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y-1]!='O' &&MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x-1][y-1]!='O'&&MyBattlefieldArray[x-2][y+1]!='O' && MyBattlefieldArray[x-2][y-1]!='O'&&MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x-3][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = x; i >= (x - t); i--)
		                                     {
		                                    MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x-2][y]!='O'&& MyFriendsBattlefieldArray[x-3][y]!='O'&& MyFriendsBattlefieldArray[x-4][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O'&&MyFriendsBattlefieldArray[x-2][y+1]!='O' && MyFriendsBattlefieldArray[x-2][y-1]!='O'&&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x-3][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i >= (x - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }

		                }
		            else
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x-2][y]!='O'&& MyBattlefieldArray[x-3][y]!='O'&& MyBattlefieldArray[x-4][y]!='O' && MyBattlefieldArray[x-5][y]!='O'&& MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x-1][y+1]!='O' && MyBattlefieldArray[x-1][y-1]!='O' && MyBattlefieldArray[x-2][y+1]!='O' && MyBattlefieldArray[x-2][y-1]!='O'&& MyBattlefieldArray[x-3][y+1]!='O' && MyBattlefieldArray[x-3][y-1]!='O'&& MyBattlefieldArray[x-4][y+1]!='O' && MyBattlefieldArray[x-4][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = x; i >= (x - t); i--)
		                                     {
		                                    MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x-2][y]!='O'&& MyFriendsBattlefieldArray[x-3][y]!='O'&& MyFriendsBattlefieldArray[x-4][y]!='O'&& MyFriendsBattlefieldArray[x-5][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' &&MyFriendsBattlefieldArray[x-1][y+1]!='O' && MyFriendsBattlefieldArray[x-1][y-1]!='O'&&MyFriendsBattlefieldArray[x-2][y+1]!='O' && MyFriendsBattlefieldArray[x-2][y-1]!='O'&&MyFriendsBattlefieldArray[x-3][y+1]!='O' && MyFriendsBattlefieldArray[x-3][y-1]!='O'&&MyFriendsBattlefieldArray[x-4][y+1]!='O' && MyFriendsBattlefieldArray[x-4][y-1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i >= (x - t); i--)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }

		  }

		  else { system("cls");
		      printf(" You can't place your ship here, Please Try again\n");
		      sleep(2);
		      system("cls");
	          Placeships(r);
		        }
                    }
 int DownwardPlace(int x, int y, int t, int r)   // downward ship placement
                    {
        if((x+t)<=10)
		  {
		  		    if (t==1)
		  		         {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x+2][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x+1][y+1]!='O')
		                                {
		                                Counter(t,r);
		                                 for (int i = x; i <= (x + t); i++)
		                                     {
		                                   MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x+2][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i <= (x + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }

		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		  		         }
		            else if (t==2)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x+2][y]!='O'&& MyBattlefieldArray[x+3][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x+1][y+1]!='O' && MyBattlefieldArray[x+2][y-1]!='O' && MyBattlefieldArray[x+2][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = x; i <= (x + t); i++)
		                                     {
		                                    MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x+2][y]!='O'&& MyFriendsBattlefieldArray[x+3][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O'&&MyFriendsBattlefieldArray[x+2][y-1]!='O' && MyFriendsBattlefieldArray[x+2][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i <= (x + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }
		            else if(t==3)
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x+2][y]!='O'&& MyBattlefieldArray[x+3][y]!='O'&& MyBattlefieldArray[x+4][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y+1]!='O' &&MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x+1][y+1]!='O'&&MyBattlefieldArray[x+2][y-1]!='O' && MyBattlefieldArray[x+2][y+1]!='O'&&MyBattlefieldArray[x+3][y-1]!='O' && MyBattlefieldArray[x+3][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = x; i <= (x + t); i++)
		                                     {
		                                    MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x+2][y]!='O'&& MyFriendsBattlefieldArray[x+3][y]!='O'&& MyFriendsBattlefieldArray[x+4][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O'&&MyFriendsBattlefieldArray[x+2][y-1]!='O' && MyFriendsBattlefieldArray[x+2][y+1]!='O'&&MyFriendsBattlefieldArray[x+3][y-1]!='O' && MyFriendsBattlefieldArray[x+3][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i <= (x + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }

		                }
		            else
		                {
		                   if(r==1)
		                        {
		                            if( MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x][y]!='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x+2][y]!='O'&& MyBattlefieldArray[x+3][y]!='O'&& MyBattlefieldArray[x+4][y]!='O' && MyBattlefieldArray[x+5][y]!='O' && MyBattlefieldArray[x][y-1]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x+1][y-1]!='O' && MyBattlefieldArray[x+1][y+1]!='O' && MyBattlefieldArray[x+2][y-1]!='O' && MyBattlefieldArray[x+2][y+1]!='O'&& MyBattlefieldArray[x+3][y-1]!='O' && MyBattlefieldArray[x+3][y+1]!='O'&& MyBattlefieldArray[x+4][y-1]!='O' && MyBattlefieldArray[x+4][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                    for (int i = x; i <= (x + t); i++)
		                                     {
		                                    MyBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                   if(r==2)
		                        {
		                            if( MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x][y]!='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x+2][y]!='O'&& MyFriendsBattlefieldArray[x+3][y]!='O'&& MyFriendsBattlefieldArray[x+4][y]!='O'&& MyFriendsBattlefieldArray[x+5][y]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' &&MyFriendsBattlefieldArray[x+1][y-1]!='O' && MyFriendsBattlefieldArray[x+1][y+1]!='O'&&MyFriendsBattlefieldArray[x+2][y-1]!='O' && MyFriendsBattlefieldArray[x+2][y+1]!='O'&&MyFriendsBattlefieldArray[x+3][y-1]!='O' && MyFriendsBattlefieldArray[x+3][y+1]!='O'&&MyFriendsBattlefieldArray[x+4][y-1]!='O' && MyFriendsBattlefieldArray[x+4][y+1]!='O')
		                                {
		                                    Counter(t,r);
		                                     for (int i = x; i <= (x + t); i++)
		                                     {
		                                     MyFriendsBattlefieldArray[i][y] = 'O';

		                                     }
		                                }
		                            else{
		                                	 system("cls");
	                                         printf(" You didn't maintain one position distance with other ships. Please Try again\n");
	                                         sleep(2);
	                                         Placeships(r);
		                                }
		                        }
		                }

		  }

		  else { system("cls");
		      printf(" You can't place your ship here, Please Try again\n");
		      sleep(2);
		      system("cls");
	          Placeships(r);
		        }
                    }

int clear()   // clearing all data given by the user
                {
                    TotalshipsMine=0;
                    TotalshipsFriends=0;
                    Box2CountMine=0;
                    Box3CountMine=0;
                    Box4CountMine=0;
                    Box5CountMine=0;
                    Box2CountFriend=0;
                    Box3CountFriend=0;
                    Box4CountFriend=0;
                    Box5CountFriend=0;
                    MeCount=0;
                    FriendCount=0;
                    MCount=0;
                    PcCount=0;

                     for(int i =1; i<11;i++)
                     {
                         for( int j=1; j<11;j++)
                         {
                             if( EmptyFieldFriend[i][j] == 'X')
                             {
                                 EmptyFieldFriend[i][j] = '.';
                             }

                         }
                     }

                     for(int i =1; i<11;i++)
                     {
                         for( int j=1; j<11;j++)
                         {
                             if( EmptyFieldMine[i][j] == 'X')
                             {
                                 EmptyFieldMine[i][j] = '.';
                             }

                         }
                     }
                     for(int i =1; i<11;i++)
                     {
                         for( int j=1; j<11;j++)
                         {
                             if( EmptyFieldPc[i][j] == 'X')
                             {
                                 EmptyFieldPc[i][j] = '.';
                             }

                         }
                     }



                     for(int i =1; i<11;i++)
                     {
                         for( int j=1; j<11;j++)
                         {
                             if( MyBattlefieldArray[i][j] == 'O')
                             {
                                 MyBattlefieldArray[i][j] = '.';
                             }

                         }
                     }

                    for(int i =1; i<11;i++)
                     {
                         for( int j=1; j<11;j++)
                         {
                             if( MyFriendsBattlefieldArray[i][j] == 'O')
                             {
                                MyFriendsBattlefieldArray[i][j] = '.';
                             }

                         }
                     }


                }



int StartGame()  // Gameplay
        {
          system("cls");
          int n;
          printf("Who wants to attack first?\n (1) Me\n (2) My Friend \n");
          scanf ("%d",&n);
          while (getchar() != '\n');
          if(n==1){MyTurn();}
          else if (n==2){FriendsTurn();}
          else
                {
                    system("cls");
                    printf("Invalid Input. Please Try again \n");
                    sleep(2);
                    system("cls");
                    StartGame();
                }

        }

int MyTurn()  // attack option for me
        {
            char w;
            int b,x,y;
            system("cls");
            PrintBattlefield(6);
            printf(" My Turn : Target the opponent ship & Fire-- -  -   -   -   - \n (type the target ship position)\n ");
            scanf("%c%d",&w,&b);
            while (getchar()!='\n');
            y=b+1;
            switch (w) {
	        case 'a':
	        	x = 1;
	        	break;
        	case 'b':
	        	x = 2;
		        break;
	        case 'c':
	        	x = 3;
	    	    break;
        	case 'd':
	        	x = 4;
	        	break;
	        case 'e':
	        	x = 5;
		        break;
	        case 'f':
	            x = 6;
	        	break;
	        case 'g':
	        	x = 7;
		        break;
	        case 'h':
	        	x = 8;
	        	break;
        	case 'i':
	        	x = 9;
	        	break;
        	case 'j':
	        	x = 10;
		        break;

        	default:
	             system("cls");
		         printf("invalid INPUT. Please try again. \n");
	             sleep(2);
	             system("cls");
	             MyTurn();
	             break;
         	}

        if(b>=0 && b<10)
                {
        if(MyFriendsBattlefieldArray[x][y]=='O' && MyFriendsBattlefieldArray[x+1][y]!='O' && MyFriendsBattlefieldArray[x-1][y]!='O' && MyFriendsBattlefieldArray[x][y+1]!='O' && MyFriendsBattlefieldArray[x][y-1]!='O')
                        {
                           FriendCount= FriendCount+1;
                           MyFriendsBattlefieldArray[x][y]='.';
                           EmptyFieldFriend[x][y]= 'X';
                           if(FriendCount==10)
                                {
                                  system("cls");
                                  printf("Congratulations..... . .  .  .   .    . You Have won the Game \n");
                                  sleep(4);
                                  system("cls");
                                  MainMenu();

                                }
                           else
                                {
                                system("cls");
                                printf("Attack Suucesfull.\n") ;
                                 printf("One Opponent ship is sunk\n") ;
                                 sleep(2);
                                 MyTurn();
                                }
                        }
        else if(MyFriendsBattlefieldArray[x][y]=='O' && (MyFriendsBattlefieldArray[x+1][y]=='O' || MyFriendsBattlefieldArray[x-1][y]=='O' || MyFriendsBattlefieldArray[x][y+1]=='O' || MyFriendsBattlefieldArray[x][y-1]=='O'))
                        {
                            MyFriendsBattlefieldArray[x][y]='.';
                            EmptyFieldFriend[x][y]= 'X';
                           system("cls");
                           printf("Attack Suucesfull.\n") ;
                           printf("Attack Again \n") ;
                           sleep(2);
                           MyTurn();
                        }
        else if(MyFriendsBattlefieldArray[x][y]!='O')
                {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your Opponent's try now\n") ;
                           sleep(2);
                           FriendsTurn();
                }
        else
            {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your Opponent's try now\n") ;
                           sleep(2);
                           FriendsTurn();
            }
                }
        else
            {
              	 system("cls");
		         printf("invalid INPUT. Please try again. \n");
	             sleep(2);
	             system("cls");
	             MyTurn();
            }



  }



int FriendsTurn()  // attack option for friends
        {
            char w;
            int b,x,y;
            system("cls");
            PrintBattlefield(3);
            printf("Friend's turn : Target the opponent ship & Fire-- -  -   -   -   - \n (type the target ship position)\n ");
            scanf("%c%d",&w,&b);
            while (getchar() != '\n');
            y=b+1;
            switch (w) {
	        case 'a':
	        	x = 1;
	        	break;
        	case 'b':
	        	x = 2;
		        break;
	        case 'c':
	        	x = 3;
	    	break;
        	case 'd':
	        	x = 4;
	        	break;
	        case 'e':
	        	x = 5;
		        break;
	        case 'f':
	            x = 6;
	        	break;
	        case 'g':
	        	x = 7;
		        break;
	        case 'h':
	        	x = 8;
	        	break;
        	case 'i':
	        	x = 9;
	        	break;
        	case 'j':
	        	x = 10;
		        break;

        	default:
	             system("cls");
		         printf("invalid INPUT. Please try again. \n");
	             sleep(2);
	             system("cls");
	             FriendsTurn();
	             break;
         	}
        if(b>=0 && b<10)
                {
        if(MyBattlefieldArray[x][y]=='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y-1]!='O')
                        {
                            MeCount=MeCount+1;
                            MyBattlefieldArray[x][y]='.';
                            EmptyFieldMine[x][y]= 'X';
                           if(MeCount==10)
                                {
                                  system("cls");
                                  printf("Congratulations..... . .  .  .   .    . Your Friend has won the Game \n");
                                  sleep(4);
                                  system("cls");
                                  MainMenu();

                                }
                            else
                                {
                                 system("cls");
                                 printf("Attack Suucesfull.\n") ;
                                 printf("One Opponent ship is sunk\n") ;
                                 sleep(2);
                                 FriendsTurn();
                                }
                        }
        else if(MyBattlefieldArray[x][y]=='O' && (MyBattlefieldArray[x+1][y]=='O' || MyBattlefieldArray[x-1][y]=='O' || MyBattlefieldArray[x][y+1]=='O' || MyBattlefieldArray[x][y-1]=='O'))
                        {
                           MyBattlefieldArray[x][y]='.';
                           EmptyFieldMine[x][y]= 'X';
                           system("cls");
                           printf("Attack Suucesfull.\n") ;
                           printf("Attack Again \n") ;
                           sleep(2);
                           FriendsTurn();
                        }
        else if(MyBattlefieldArray[x][y]!='O')
                {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your Opponent's try now\n") ;
                           sleep(2);
                           MyTurn();
                }
        else
            {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your Opponent's try now\n") ;
                           sleep(2);
                           MyTurn();
            }

                }
        else
            {
              	 system("cls");
		         printf("invalid INPUT. Please try again. \n");
	             sleep(2);
	             system("cls");
	             FriendsTurn();
            }


        }




int StartGamePc()  // Gameplay with A.I
        {
          system("cls");
          int n,l;

          srand(time(0));
          l = rand() % 5 + 1;


          if(l==1)
                    {
                     for(int i=0;i<12;i++)
                                {
                                  for( int j=0;j<12;j++)
                                                    {
                                                     u[i][j]=a[i][j];
                                                    }
                                }
                    }
          else if (l==2)
                    {
                     for(int i =0;i<12;i++)
                                {
                                  for( int j=0;j<12;j++)
                                                    {
                                                     u[i][j]=b[i][j];
                                                    }
                                }
                    }
          else if (l==3)
                    {
                      for(int i =0;i<12;i++)
                                {
                                  for( int j=0;j<12;j++)
                                                    {
                                                     u[i][j]=c[i][j];
                                                    }
                                }
                    }
          else if (l==4)
                    {
                      for(int i=0;i<12;i++)
                                {
                                  for( int j=0;j<12;j++)
                                                    {
                                                     u[i][j]=d[i][j];
                                                    }
                                }
                    }
          else
                    {
                      for(int i =0;i<12;i++)
                                {
                                  for( int j=0;j<12;j++)
                                                    {
                                                     u[i][j]=e[i][j];
                                                    }
                                }
                    }




          printf("Who wants to attack first?\n (1) Me\n (2) A.I \n");
          scanf ("%d",&n);
          while (getchar() != '\n');
          if(n==1){SelfTurn();}
          else if (n==2){PcTurn();}
          else
                {
                    system("cls");
                    printf("Invalid Input. Please Try again \n");
                    sleep(2);
                    system("cls");
                    StartGame();
                }


        }

int SelfTurn()  // my part to attack A.I ships
        {
            char w;
            int b,x,y;
            system("cls");
            PrintBattlefield(7);
            printf(" My Turn : Target the opponent ship & Fire-- -  -   -   -   - \n (type the target ship position)\n ");
            scanf("%c%d",&w,&b);
            while (getchar()!='\n');
            y=b+1;
            switch (w) {
	        case 'a':
	        	x = 1;
	        	break;
        	case 'b':
	        	x = 2;
		        break;
	        case 'c':
	        	x = 3;
	    	    break;
        	case 'd':
	        	x = 4;
	        	break;
	        case 'e':
	        	x = 5;
		        break;
	        case 'f':
	            x = 6;
	        	break;
	        case 'g':
	        	x = 7;
		        break;
	        case 'h':
	        	x = 8;
	        	break;
        	case 'i':
	        	x = 9;
	        	break;
        	case 'j':
	        	x = 10;
		        break;

        	default:
	             system("cls");
		         printf("invalid Input. Please try again. \n");
	             sleep(2);
	             system("cls");
	             SelfTurn();
	             break;
         	}

        if(b>=0 && b<10)
                {

        if(u[x][y]=='O' && u[x+1][y]!='O' && u[x-1][y]!='O' && u[x][y+1]!='O' && u[x][y-1]!='O')
                        {
                           PcCount= PcCount+1;
                           u[x][y]='.';
                           EmptyFieldPc[x][y]= 'X';
                           if(PcCount==10)
                                {
                                  system("cls");
                                  printf("Congratulations..... . .  .  .   .    . You Have won the Game \n");
                                  sleep(4);
                                  system("cls");
                                  MainMenu();

                                }
                           else
                                {
                                system("cls");
                                printf("Attack Succesfull.\n") ;
                                 printf("One Opponent ship is sunk\n") ;
                                 sleep(2);
                                 SelfTurn();
                                }
                        }
        else if(u[x][y]=='O' && (u[x+1][y]=='O' || u[x-1][y]=='O' || u[x][y+1]=='O' || u[x][y-1]=='O'))
                        {
                           u[x][y]='.';
                           EmptyFieldPc[x][y]= 'X';
                           system("cls");
                           printf("Attack Succesfull.\n") ;
                           printf("Attack Again \n") ;
                           sleep(2);
                           SelfTurn();
                        }
        else if(u[x][y]!='O')
                {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your Opponent's try now\n") ;
                           sleep(2);
                           PcTurn();
                }
        else
            {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your Opponent's try now\n") ;
                           sleep(2);
                           PcTurn();
            }
                }
        else
            {
              	 system("cls");
		         printf("invalid INPUT. Please try again. \n");
	             sleep(2);
	             system("cls");
	             SelfTurn();
            }


  }



int PcTurn()   // A.I turn to attack my ships
        {
            char w;
            int b,x,y;
            system("cls");
            PrintBattlefield(3);
            printf(" PC turn :  Fire-- -  -   -   -   - \n ");
            sleep(2);
            srand(time(0));
            x = rand() % 10 + 1;
            srand(time(0));
            y = rand() % 10 + 1;




        if(MyBattlefieldArray[x][y]=='O' && MyBattlefieldArray[x+1][y]!='O' && MyBattlefieldArray[x-1][y]!='O' && MyBattlefieldArray[x][y+1]!='O' && MyBattlefieldArray[x][y-1]!='O')
                        {
                            MCount=MCount+1;
                            MyBattlefieldArray[x][y]='.';
                           if(MCount==10)
                                {
                                  system("cls");
                                  printf("Unfortunately..... . .  .  .   .    . You have lost the Game \n");
                                  sleep(4);
                                  system("cls");
                                  MainMenu();

                                }
                            else
                                {
                                 system("cls");
                                 printf("Attack Suucesfull.\n") ;
                                 printf("Your one ship is sunk\n") ;
                                 sleep(2);
                                 PcTurn();
                                }
                        }
        else if(MyBattlefieldArray[x][y]=='O' && (MyBattlefieldArray[x+1][y]=='O' || MyBattlefieldArray[x-1][y]=='O' || MyBattlefieldArray[x][y+1]=='O' || MyBattlefieldArray[x][y-1]=='O'))
                        {
                           MyBattlefieldArray[x][y]='.';
                           system("cls");
                           printf("Attack Suucesfull.\n") ;
                           printf("Attacking Again \n") ;
                           sleep(2);
                           PcTurn();
                        }
        else if(MyBattlefieldArray[x][y]!='O')
                {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your  try now\n") ;
                           sleep(2);
                           SelfTurn();
                }
        else
            {
                           system("cls");
                           printf("Target Missed.\n") ;
                           printf("Your  try now\n") ;
                           sleep(2);
                           SelfTurn();
            }




        }




