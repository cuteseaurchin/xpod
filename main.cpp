/*
Driver program for xpod game. Things to note:
Default position for units is -1,-1. 0,0 is the bottom left square
*/

#include "Game.h"
#include "Pod.h"
#include "Arena.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    //Get player's names and pods they want to play with
    string player1Name;
    string player2Name;
    string player1Pod;
    string player2Pod;
    cout << "Player 1 Name: ";
    cin >> player1Name;
    cout << "Player 1 Pod: ";
    cin >> player1Pod;
    cout << "Player 2 Name: ";
    cin >> player2Name;
    cout << "Player 2 Pod: ";
    cin >> player2Pod;

    //Get preferred arena size
    int rowIn;
    int colIn;
    cout << "Arena Rows: ";
    cin >> rowIn;
    cout << "Arena Columns: ";
    cin >> colIn;

    //Create Game object
    Game game(player1Name, player1Pod, player2Name, player2Pod, rowIn, colIn);

    cout << "Game start:\n";

    //Get player's choices for starter kit
    cout << "Player 1:\n";
    game.starterKit(game.getPlayer(1));
    cout << "Player 2:\n";
    game.starterKit(game.getPlayer(2));

    //If no one has 3 points yet, keep playing
    while(game.playerWin() == 0) {
        //Print out player's turn
        cout << game.getActivePlayer()->getName() << "'s turn";
        //Print out player's active units and inactive units
        game.getActivePlayer()->printActive();
        game.getActivePlayer()->printInactive();
        cout << "Choose one of the following actions:\n[1]: Build\n[2]: Place\n[3]: Activate\n[4] Unfreeze\n[5]: Plansheet\n[6]: Board\n";
        //Variable to store player input
        int actionChoice;
        cin >> actionChoice;
        int choice;
        switch(actionChoice) {
            case 1 : {
                //Print out plansheet
                game.getActivePlayer()->printPlanSheet();
                //Ask for index of unit to build
                cout << "Enter index of unit you want to build:";
                cin >> choice;
                //TODO: Check if input is valid
                /*
                while(choice < 0 && choice >= activePlayer->getPlanSheet().size()) {
                    while(!enoughBricks(activePlayer->getPod().getPlanSheet().at(choice))) {
                        cout << "Invalid input, please enter index of unit you want to build again:";
                    }
                    cout << "Invalid input, please enter index of unit you want to build again:";
                }
                */
                //Build unit
                game.getActivePlayer()->buildUnit(choice);
                //End of turn
                game.changeTurn();
            }
            case 2 : {
                //Print out inactive units
                game.getActivePlayer()->printInactive();
                //Ask for index of unit to place
                cout << "Enter index of unit to place:";
                cin >> choice;
                cout << "Enter a position along your home row to place unit:";
                pair<int,int> placeChoice = make_pair(-1,-1);
                //TODO: Check that position input is valid. No other units and in own home row
                cin >> placeChoice.first >> placeChoice.second;
                //Place unit
                game.getActivePlayer()->getInactiveUnits().at(choice).setPosition(placeChoice.first, placeChoice.second);
                //End of turn
                game.changeTurn();
            }
            case 3 : {
                //Print out active units
                game.getActivePlayer()->printActive();
                //Ask for index of unit to activate
                cout << "Enter index of unit to activate:";
                int unitChoice;
                cin >> unitChoice;
                while(game.getActivePlayer()->getUnits().at(unitChoice).ifFrozen()) {
                    cout << game.getActivePlayer()->getUnits().at(unitChoice).getName() << " is frozen, choose another unit\n";
                    cin >> unitChoice;
                }
                //Print out unit's available actions
                game.printUnitActions(game.getActivePlayer()->getUnits().at(unitChoice));
                //Enact actions
                game.enactUnitActions(game.getActivePlayer()->getUnits().at(unitChoice));
                //End of turn
                game.changeTurn();
            }
            case 4 : {
                //Print out active units
                game.getActivePlayer()->printActive();
                //Ask for index of unit to unfreeze
                cout << "Enter index of unit to unfreeze:";
                cin >> choice;
                //Unfreeze selected unit
                game.unfreezeUnit(game.getActivePlayer()->getUnits().at(choice));
                //End of turn
                game.changeTurn();
            }
            case 5 : {
                //Print plansheet
                game.getActivePlayer()->printPlanSheet();
                //Do not change turn
            }
            case 6 : {
                //Print out board
                game.printBoard();
                //Do not change turn
            }                
        }
        //Check for units in home row, increment score, and remove unit
        game.ifScored();
    }
    //Once there is a winner, announce winner
    cout << "The winner is Player " << game.playerWin();

    return 0;
}
