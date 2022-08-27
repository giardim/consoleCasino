/******************************
    Author: Michael Giardina
    Date created: 23 Aug 2022
    Date updated: 27 Aug 2022
    Purpose: A program that allows the
                user to gamble 
    Language: C++ 12.1.0
    Known bugs: 
        None   
******************************/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <unordered_map>
#include <ctime>
#include <fstream>

class casino
{
    public:
    void startUp()
    {
        //Getting the chips for the user from the file attached
        std::string tempMoney;
        std::ifstream money("chips.txt");
        getline(money, tempMoney);
        chips = stoi(tempMoney);
        money.close();

        //Greeting the user and setting up the seed so the outcomes are random
        std::cout << "Welcome to the casino! You have " << chips << " chips, what do you want to play?\n";
        unsigned int seed = static_cast <unsigned int>(time(nullptr));
        srand(seed);
        
        //creating a hashmap for blackjack
        for (int i = 2; i < 11; ++i)
        {
            deck[i] = std::__cxx11::to_string(i);
        }
        deck [1] = "Ace";
        deck [11] = "Jack";
        deck [12] = "Queen";
        deck [13] = "King";
    }
    void slots()
    {
        int first = 0, second = 0, third = 0;

        //Explaining the rules to the user
        std::cout << "Welcome to the slots, take a seat\n";
        std::cout << "Rules: Before spinning, you will have the opportunity to place a bet.\n";
        std::cout << "The machine will then spin, giving three random numbers.\n";
        std::cout << "If the first and second number match, you will get 1.25x your original bet.\n";
        std::cout << "If all three numbers match, you will get 3x your original bet. Good luck!\n";
        
        do
        {
            //Allow the user to place their bets
            std::cout << "Please place your bets: ";
            std::cin >> bet;

            //Make sure the user has enough money to bet
            while (bet > chips)
            {
                std::cout << "Sorry, you do not have enough money to place that bet, please enter a new bet: ";
                std::cin >> bet; 
            }

            //Generate 3 random numbers for the slot and show them to the user
            first = rand() % 4 + 1;
            second = rand() % 4 + 1;
            third = rand() % 4 + 1;
            std::cout << "-----------------------------------------\n   ";
            std::cout << first;
            usleep(100000);
            std::cout << "\t\t " << second;
            usleep(100000);
            std::cout << "\t\t " << third;
            std::cout << "\n-----------------------------------------";

            //If all three reels are the same, the user wins 3x their bet
            if (first == second && second == third)
            {
                chips += (bet * 3);
                std::cout << " \nYou won 3x your bet! New balance: " << chips;
            }

            //If the first and second reel are the same, the user wins 1.5x their bet
            else if (first == second)
            {
                chips += (bet * 1.5);
                std::cout << " \nYou won 1.5x your bet! New balance: " << chips;
            }

            //The user lost so subtract their bet from the chips
            else
            {
                chips -= bet;
                std::cout << " \nNew balance: " << chips;
            }

            //Check if the user wants to play again
            std::cout << "\nDo you want to play again (y/n): ";
            std::cin >> again;    
        }
        while (again == "y" || again == "Y");
        
        return;
    }

    void blackjack()
    {
        //Explain the rules to the user
        std::cout << "Welcome to Blackjack, take a seat.\n";
        std::cout << "Rules: Before the dealer deals cards, you will have the opportunity to place a bet.\n";
        std::cout << "The goal is to get as close to 21 as possible without going over.\n";
        std::cout << "The dealer will always hit until he hits 16 and must stand over 17. Good luck!\n";

        do
        {
            //Reset all the variables
            int playerTotal = 0, dealerTotal = 0, dealerSecond = 0, playerCard = 0;
            choice = "";

            //Allow the user to place their bets
            std::cout << "Please place your bets: ";
            std::cin >> bet;
            while (bet > chips)
                {
                    std::cout << "Sorry, you do not have enough money to place that bet, please enter a new bet: ";
                    std::cin >> bet; 
                }
            std::cout << "Good Luck!\n";

            //Give the dealer their showing card
            dealerSecond = rand() % 13 + 1;
            std::cout << "Dealer showing: " << deck[dealerSecond] << "\n";

            //If the dealer got a 1 (ace) make the dealer get 11
            if (dealerSecond == 1) dealerSecond = 11;
            
            //If the dealer got 11, 12 or 13 (Jack, Queen, or King) make the dealer get 10
            if (dealerSecond == 11 || dealerSecond == 12 || dealerSecond == 13) dealerSecond = 10;\

            //Give the dealer their second card
            dealerTotal = dealerSecond + (rand() % 10 + 1);

            //Give the player their first card
            playerCard = rand() % 13 + 1;
            std::cout << "First card: " << deck[playerCard] << "\n";

            //If the player got a 1 (ace) make the player get 11
            if (playerCard == 1) playerCard = 11;

            //If the dealer got 11, 12 or 13 (Jack, Queen, or King) make the dealer get 10
            if (playerCard == 11 || playerCard == 12 || playerCard == 13) playerCard = 10;

            //Give the dealer their second card and show them their total
            playerTotal = playerCard + (rand() % 10 + 1);
            std::cout << "Player total: " << playerTotal;

            //If the player got blackjack, they win
            if (playerTotal == 21)
            {
                std::cout << "Winner winner chicken dinner!\n";
                chips += (bet * 1.5);
                choice == "2";
            }

            while (choice != "2")
            {
                //Ask the user if they want to get another card or stop
                std::cout << "\nDo you want to hit?\n1) Yes\n2) No\n";
                std::cin >> choice;

                //Make sure the user gave a valid choice
                if (choice != "1" && choice != "2")
                {
                    std::cout << "That is not a valid choice, please try again\n";
                }

                //If the use wants another card, add a card to their total
                if (choice == "1")
                {
                    playerTotal += (rand() % 10 + 1);
                    std::cout << "Player total: " << playerTotal;
                }

                //If the player's total is greater than 21, they lose
                if (playerTotal > 21)
                    {
                        std::cout << "\nSorry, you lose\n";
                        choice = "2";
                    }
            } 

            //Now show the dealer's total
            std::cout << "Dealers turn!\n";
            std::cout << dealerTotal << "\n";

            //While the dealer has less than 16 and less than 21, they must hit
            while (dealerTotal < 16 && dealerTotal < 21)
            {
                dealerTotal += rand() % 10 + 1;
                std::cout << dealerTotal << "\n";
            }

            //If the player's total is greater than the dealer's and
            //  is less than 21, they win
            if (playerTotal <= 21 && playerTotal > dealerTotal)
            {
                chips += bet;
                std::cout << "Congratulations!\nNew balance: " << chips << "\n";
            }

            // //If the player's total is equal to the dealer's and
            //  is less than 21, it is a push
            else if (playerTotal <= 21 && playerTotal == dealerTotal)
            {
                std::cout << "Sorry, thats a push!\nNew balance: " << chips << "\n";
            }
            
            //Else, they player loses
            else
            {
                chips -= bet;
                std::cout << "Better luck next time!\nNew balance: " << chips << "\n";
            }

            //Check if the user wants to play again
            std::cout << "Do you want to play again? (y/n): ";
            std::cin >> again;

        }while (again == "y" || again == "Y");
        return;
    }

    void roulette()
    {
        //Explain the rules to the user
        std::cout << "Welcome to Roulette, take a seat!\n";
        std::cout << "Rules: Before the wheel is spun, you will have the opportunity\n";
        std::cout << "to place a bet and pick a color (red, black or green). The host\n";
        std::cout << "will then spin the wheel, if you selected red or black correctly\n";
        std::cout << "you will win 2x your bet. If you pick green correctly, you will\n";
        std::cout << "win 30x your bet. Good luck!\n";
       
        do
        {
            //Reset the variables
            std::string choice = "";
            int outcome = 0, guess = 0, winning = 0;

            //Get the bet from the user
            std::cout << "Please place your bets: ";
            std::cin >> bet;
            while (bet > chips)
            {
                std::cout << "Sorry, you do not have enough money to place that bet, please enter a new bet: ";
                std::cin >> bet; 
            }

            //Get the player's color choice
            std::cout << "Please select your color\n1) Red\n2) Black\n3) Green\n";
            std::cin >> choice;

            //Make sure the player's choice is valid
            while (choice != "1" && choice != "2" && choice != "3")
            {
                std::cout << "That is not a valid color, please select a valid color\n1) Red\n2) Black\n3) Green\n";
                std::cin >> choice;
            }
            guess = stoi(choice);

            //Generate a random number between 0 and 36
            outcome = rand() % 37;

            //If the outcome is 0, the wheel lands on green
            if (outcome == 0)
            {
                std::cout << "The wheel lands on green!\n";
                winning = 3;
            }

            //If the outcome is greater than 0 but less than or equal to 18
            // the wheel lands on red
            if (outcome > 0 && outcome <= 18) 
            {
                std::cout << "The wheel lands on red!\n";
                winning = 1;
            }

            //If the outcome is greater than 18 but less than or equal to 36
            //  the wheel lands on black
            if (outcome > 18 && outcome <= 36) 
            {
                std::cout << "The wheel lands on black!\n";
                winning = 2;
            }

            //If the user guesses the color green correctly, add 30x bet to their chips
            if (guess == winning && winning == 3)
            {
                chips += (bet * 30);    
                std::cout << "Congratulations!\nNew balance: " << chips << "\n";            
            }

            //If the user guesses black or red correctly, add 2x their bet to their chips
            else if (guess == winning && winning != 3)
            {
                chips += (bet * 2);
                std::cout << "Congratulations!\nNew balance: " << chips << "\n";
            }

            //Otherwise, they lose
            else 
            {
                chips -= bet;
                std::cout << "Better luck next time!\nNew balance: " << chips << "\n";
            }
            
            //Check if the user wants to play again
            std::cout << "\nDo you want to play again (y/n): ";
            std::cin >> again;    
        }
        while (again == "y" || again == "Y");
        
        return;
    }

    void addFunds()
    {
        //Reset the variables
        std::string password = "12345", attempt = "", add = "";
        int adding;

        //Get the password from the user, if it is wrong
        //  return to the main program without letting them change their balance
        std::cout << "Please enter the password: ";
        std::cin >> attempt;
        if (attempt != password)
        {
            std::cout << "Sorry, password is incorrect\n";
            return;
        }

        //Ask how much the user wants to add to their balance and add it 
        //  to their chips
        std::cout << "How many chips do you want to add to your balance?: ";
        std::cin >> add;
        adding = stoi(add);
        chips += adding;
        std::cout << "New balance: " << chips << "\n";
        return;
    }
    
    void closing()
    {
        //Save the chips to a file
        std::string outMoney;
        std::ofstream money("chips.txt");
        outMoney = std::__cxx11::to_string(chips); 
        money << outMoney;
        money.close();
        std::cout << "Come again soon!\n";
    }

    private:
    int chips = 1000, bet = 0;
    std::string again, choice;
    std::unordered_map<int, std::string> deck;

};

int main (void)

{
    std::string choice;
    casino play;

    play.startUp();

    do{
    std::cout << "1) Slots\n2) Blackjack\n3) Roulette\n4) Add funds\n5) Cash out\n";
    std::cin >> choice;
    if (choice == "1")
    {
        play.slots();
    }
    else if (choice == "2")
    {
        play.blackjack();
    }
    else  if (choice == "3")
    {
        play.roulette();
    }
    else if (choice == "4")
    {
        play.addFunds();
    }
    else if (choice == "5")
    {
        
        play.closing();
    }
    else 
    {
        std::cout << "Sorry that is not a valid choice\n";
    }

    }while (choice != "5");

    return 0;
}