#include <iostream>
#include <string>  // For strings (used to draw the dice)
#include <time.h>  // For time, to set our random seed as close to true random as possible
#include <conio.h> // For getch, just to do the "press any key to continue..." bit

void clearcin();
int RollDice();
int WinCheck(int Check, int Point);

std::string Dice[6]{ "-------\n|     |\n|  o  |\n|     |\n-------",
                     "-------\n|    o|\n|     |\n|o    |\n-------",
                     "-------\n|o    |\n|  o  |\n|    o|\n-------",
                     "-------\n|o   o|\n|     |\n|o   o|\n-------",
                     "-------\n|o   o|\n|  o  |\n|o   o|\n-------",
                     "-------\n|o   o|\n|o   o|\n|o   o|\n-------" };

int main() {

    int DiceResult{};
    int Point{};
    int WinCon{};
    bool RepeatGame{};
    char RepeatAns{};
    char RepeatQuestion{};



    srand(time(NULL)); // Set the random seed to current system time, so we don't get the exact same pattern of dice every time
    
    do {
        system("cls"); // Clear the screen of any potential previous game
        Point = 0; // Set the point to 0, so WinCheck works for the first roll
        std::cout << "Hello, and welcome to Craps!\n"
            << Dice[5] << "\n"
            << "You will throw two dice, and your score will be the sum of these dice.\n"
            << "If you score 7 or 11, you win! But if you score 2, 3 or 12, you lose.\n"
            << "If you score anything other than that, your score will become your \"point\" and you will throw the dice again.\n"
            << "If you then get a 7, you lose! But if you roll the same score as your point, you will win!\n"
            << "You will then keep throwing the dice until you either win or lose. Good luck!\n"
            << "Press any key to make your first throw.\n";
        _getch(); // Simply pauses the program until you press a button, simply ignores the return value
        DiceResult = RollDice();
        WinCon = DiceResult;
        if (WinCheck(DiceResult, Point) == 2) {
            Point = WinCon;
            do {
                std::cout << "This means you neither won nor lost, and have to roll again.\n" << "Your point is " << WinCon << ".\n"
                    << "If you roll this number again, you win! But if you roll 7, you lose. Good luck!\n"
                    << "Press any key to throw the dice again.\n";
                _getch();
                DiceResult = RollDice();
            } while (WinCheck(DiceResult, Point) == 2);
        }
        switch (WinCheck(DiceResult, Point)) {
        case 0:
            std::cout << "Sadly, this means you lose! Better luck next time.\n";
            break;
        case 1:
            std::cout << "This means you win the game! Congratulations!\n";
            break;
        default:
            std::cout << "Something went wrong, please tell me how you broke my program!";
            EXIT_FAILURE;
        }
        do {
            // Ask if the game should be repeated, and set RepeatGame accordingly
            std::cout << "Would you like to play again?\n"; /* No need to tell them to use Y / N format, since
                                                            we store the answer in a char variable, it will only
                                                            take the first letter anyway*/
            std::cin >> RepeatAns;
            clearcin();
            RepeatAns = toupper(RepeatAns); /* We set the character to its uppercase equivalent, so we only get
                                            2 condition checks instead of 4*/
            switch (RepeatAns) {
            case 'Y':
                RepeatQuestion = false;
                RepeatGame = true;
                break;
            case 'N':
                RepeatQuestion = false;
                RepeatGame = false;
                std::cout << "Very well, goodbye for now!";
                break;
            default:
                std::cout << "That's not a valid answer! Please answer yes or no.\n";
                RepeatQuestion = true;
                break;
            }
        } while (RepeatQuestion);


    } while (RepeatGame);
}

int RollDice() {
    
    int Result{};
    int FirstDie{};
    int SecondDie{};

    FirstDie = rand() % 6 + 1; // Roll a random number between 1 and 6
    SecondDie = rand() % 6 + 1;
    Result = FirstDie + SecondDie;
    system("cls");
    std::cout << Dice[FirstDie - 1] << "\n";  // We have to subtract 1 from the result, since arrays start at 0, not 1
    std::cout << Dice[SecondDie - 1] << "\n"; // Could also have done random number from 0 to 5 and added 2 to the result, same end result with both methods
    std::cout << "You've rolled " << Result << "!\n";

    return Result;
}

int WinCheck(int Check, int Point) {

    if (Point == 0) {
        if (Check == 7 || Check == 11) {
            return 1;
        }
        else if (Check == 2 || Check == 3 || Check == 12) {
            return 0;
        }
        else {
            return 2;
        }
    }
    else {
        if (Check == Point) {
            return 1;
        }
        else if (Check == 7) {
            return 0;
        }
        else {
            return 2;
        }
    }
}

/* Function to clear out the buffer of cin, ensuring we don't take in more than one word and get weird inputs
(or worse, infinite loops)*/
void clearcin() {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
}