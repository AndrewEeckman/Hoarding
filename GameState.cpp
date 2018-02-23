//
// Created by Andrew Eeckman on 2/4/18.
//

//**********************************************************************************************************************************

#include "GameState.h"
#include <cmath>

using namespace Monopoly;

//**********************************************************************************************************************************

void GameState::getMove(Board& board, int currentPlayer, ifstream& randomStream) {
    int playerAction = 0;
    bool turnOver = false;
    bool rolledDoubles = false;
    int rerolls = -1;

    while (!turnOver) {
        if (!board.players.at(currentPlayer).getInGame()) {
            turnOver = true;
            printf("\n");
            continue;
        }

        board.displayBoard(board);

        cout << board.players.at(currentPlayer).getName() << " please enter your move" << endl;
        cout << "1 to roll dice" << endl
             << "2 to upgrade a property with a house or hotel " << endl
             << "3 to sell a house or hotel " << endl
             << "4 to leave the game " << endl
             << "Your move: ";


        cin >> playerAction;

        if (playerAction == 1) {
            turnOver = movePlayer(board, currentPlayer, randomStream);
            rerolls++;

            if(rerolls == board.rules.getMaxReRolls()) {
                turnOver = true;
            }

        } else if(playerAction == 2) { //Buying houses and hotels
            std::vector <int> upgradable;
            bool canUpgrade = true;
            for (int i = 0; i <  board.boardSpaces.size(); i++) { //Cycles throught the properties looking for the upgradeable ones
                canUpgrade = true; //reset the value before execution of loop
                    if (board.boardSpaces.at(i).propertySpace.getNumHotels() == 1) {
                        canUpgrade = false;
                        continue;
                    }
                if(board.boardSpaces.at(i).propertySpace.getNumHouses() < 4){
                    if (board.boardSpaces.at(i).propertySpace.getHouseCost() <= board.players.at(currentPlayer).getCashAmount()) {
                        canUpgrade = false;
                        continue;  //Checks for enough cash
                    }
                } else if ( board.boardSpaces.at(i).propertySpace.getNumHouses() == 4) {
                    if (board.boardSpaces.at(i).propertySpace.getHotelCost() <= board.players.at(currentPlayer).getCashAmount()) {
                        canUpgrade = false;
                        continue;  //Checks for enough cash
                    }
                }
                if (board.boardSpaces.at(i).propertySpace.getOwnedBy() == currentPlayer) {
                    for(int j = 0; j < board.boardSpaces.size(); j++){
                        if(board.boardSpaces.at(i).propertySpace.getSetID() == board.boardSpaces.at(j).propertySpace.getSetID()){
                            if(board.boardSpaces.at(i).propertySpace.getOwnedBy() != board.boardSpaces.at(j).propertySpace.getOwnedBy()) {
                                canUpgrade = false;
                                break; //checks for owning all properties
                            }
                            if(board.rules.getBuildEvenly()) {
                                if(board.boardSpaces.at(j).propertySpace.getNumHotels() == 1) {
                                    //Just to make sure that it can catch if a propety has a hotel and no houses
                                } else if (board.boardSpaces.at(i).propertySpace.getNumHouses() > board.boardSpaces.at(j).propertySpace.getNumHouses()) {
                                    canUpgrade = false;
                                    break; //checks for even building
                                }
                            }
                        }
                    }
                    if(canUpgrade) {
                        upgradable.push_back(i);
                    }

                }

            }
            if(upgradable.size() == 0){
                std::cout << "You don't have any properties that you can upgrade";
            } else {
                int userChoice;
                for (int i = 0; i < upgradable.size(); i++) {
                    if (board.boardSpaces.at(i).propertySpace.getNumHouses() < 4) {
                        std::cout << i << ". " << board.boardSpaces.at(i).propertySpace.getName() << " [$"
                                  << board.boardSpaces.at(i).propertySpace.getHouseCost() << "]" << std::endl;
                    }
                    if (board.boardSpaces.at(i).propertySpace.getNumHouses() == 4) {
                        std::cout << i << ". " << board.boardSpaces.at(i).propertySpace.getName() << " [$"
                                  << board.boardSpaces.at(i).propertySpace.getHotelCost() << "]" << std::endl;
                    }
                }
                std::cout << "Your choice: ";
                cin >> userChoice;
                if (board.boardSpaces.at(userChoice).propertySpace.getNumHouses() < 4) {
                    board.boardSpaces.at(userChoice).propertySpace.setNumHouses(board.boardSpaces.at(userChoice).propertySpace.getNumHouses() + 1);
                    board.players.at(currentPlayer).setCashAmount(board.players.at(currentPlayer).getCashAmount() - board.boardSpaces.at(userChoice).propertySpace.getHouseCost());
                    board.boardSpaces.at(userChoice).propertySpace.setRent(board.boardSpaces.at(userChoice).propertySpace.getRentHouse() * (int)pow(2, (board.boardSpaces.at(userChoice).propertySpace.getNumHouses() - 1)));
                } else if (board.boardSpaces.at(userChoice).propertySpace.getNumHouses() == 4) {
                    board.boardSpaces.at(userChoice).propertySpace.setNumHouses(0);
                    board.boardSpaces.at(userChoice).propertySpace.setNumHotels(1);
                    board.players.at(currentPlayer).setCashAmount(board.players.at(currentPlayer).getCashAmount() - board.boardSpaces.at(userChoice).propertySpace.getHotelCost());
                    board.boardSpaces.at(userChoice).propertySpace.setRent(board.boardSpaces.at(userChoice).propertySpace.getRentHotel());
                }
            }

            //Print out the choice and get the choice and change info

            turnOver = false;
        }

        else if(playerAction == 3) {
            //FIXME: ADD SELL FUNCTION
            turnOver = false;
        }

        else if (playerAction == 4) {
            for(int i = 1; i < board.getSpaces(); i++) {
                if(board.boardSpaces.at(i).propertySpace.getOwnedBy() == board.players.at(currentPlayer).getNumIdentifier()) {
                    board.boardSpaces.at(i).propertySpace.setOwnedBy(-1);
                    board.boardSpaces.at(i).propertySpace.setOwned(false);
                }
            }
            leaveGame(board, currentPlayer);
            turnOver = true;
        }

        else {
            cout << "Unrecognized move number " << playerAction << " in Move constructor " << endl;
        }
    }
}

//**********************************************************************************************************************************

bool GameState::movePlayer(Board& board, int currentPlayer, ifstream& randomStream) {

    int currentCashAmount = board.players.at(currentPlayer).getCashAmount();
    int currentBoardPosition = board.players.at(currentPlayer).getBoardPosition();

    DiceRoller diceRoller;

    int diceRoll = diceRoller.rollDice(randomStream);

    cout << board.players.at(currentPlayer).getName() << ", you rolled a " << diceRoll << endl;

    if(diceRoll + currentBoardPosition < board.getSpaces()) {
        board.players.at(currentPlayer).setBoardPosition(currentBoardPosition + diceRoll);
        currentBoardPosition = board.players.at(currentPlayer).getBoardPosition();

    } else if((diceRoll + currentBoardPosition) >= board.getSpaces()) { //FIXME: INACCURATELY ADDING GO VALUES
        board.players.at(currentPlayer).setBoardPosition((diceRoll + currentBoardPosition) % board.getSpaces());
        currentBoardPosition = board.players.at(currentPlayer).getBoardPosition();
        currentCashAmount = board.players.at(currentPlayer).getCashAmount();
        /*
        cout << endl;
        cout << "currentCashAmount: " << currentCashAmount << endl;
        cout << "True Cash: " << board.players.at(currentPlayer).getCashAmount()  << endl;
         */

        int numTimesAroundGo = ((currentBoardPosition) + diceRoll) / board.getSpaces();

        if(board.players.at(currentPlayer).getBoardPosition() == 0) {
            for(int i = 0; i < numTimesAroundGo-1; i++) {
                board.players.at(currentPlayer).setCashAmount(currentCashAmount + board.boardSpaces.at(0).goSpace.getMoneyAroundGo());
                currentCashAmount = board.players.at(currentPlayer).getCashAmount();
            }
            board.players.at(currentPlayer).setCashAmount(currentCashAmount + (board.boardSpaces.at(0).goSpace.getMoneyAroundGo() * board.rules.getSalMultiGo()));
            currentCashAmount = board.players.at(currentPlayer).getCashAmount();
            /*
            cout << endl;
            cout << "numTimesAroundGo: " << numTimesAroundGo << endl;
            cout << "currentCashAmount (Now): " << currentCashAmount << endl;
            cout << "True Cash (Now): " << board.players.at(currentPlayer).getCashAmount();
            cout << endl;
             */

        } else {

            for(int i = 0; i < numTimesAroundGo; i++) {
                board.players.at(currentPlayer).setCashAmount(currentCashAmount + board.boardSpaces.at(0).goSpace.getMoneyAroundGo());
                currentCashAmount = board.players.at(currentPlayer).getCashAmount();
            }
            /*
            cout << endl;
            cout << "numTimesAroundGo: " << numTimesAroundGo << endl;
            cout << "currentCashAmount (Now): " << currentCashAmount << endl;
            cout << "True Cash (Now): " << board.players.at(currentPlayer).getCashAmount();
            cout << endl;
             */
        }

        numTimesAroundGo = 0;

    } else {
        board.players.at(currentPlayer).setBoardPosition(board.getSpaces()-1);
        currentBoardPosition = board.players.at(currentPlayer).getBoardPosition();
    }

    board.players.at(currentPlayer).setCashAmount(currentCashAmount);

    ///---///

    ///---///

    int rentOfPos = board.boardSpaces.at(currentBoardPosition).propertySpace.getRent();
    char choice = ' ';

    if(currentBoardPosition != 0) {
        if (board.boardSpaces.at(currentBoardPosition).propertySpace.getOwned()) {

            if (board.boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy() == currentPlayer) {
                cout << board.players.at(currentPlayer).getName() << ", you landed on "
                     << board.boardSpaces.at(currentBoardPosition).propertySpace.getName()
                     << " which you already own" << endl;
            } else {

                int setMulti = 1; //Checks to see if the property set is owned by one person
                for (int position = 1; position < board.getSpaces(); position++) {

                    if (board.boardSpaces.at(position).propertySpace.getSetID() ==
                        board.boardSpaces.at(currentBoardPosition).propertySpace.getSetID()) {

                        if (board.boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy() ==
                            board.boardSpaces.at(position).propertySpace.getOwnedBy()) {

                            setMulti = board.rules.getSetMulti();

                        } else {

                            setMulti = 1;
                            break;
                        }
                    }
                }


                if ((currentCashAmount - (rentOfPos * setMulti)) < 0) {

                    cout << board.players.at(currentPlayer).getName() << " went bankrupt to " <<
                         board.players.at(board.boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).getName()
                         << " for landing on " << board.boardSpaces.at(currentBoardPosition).propertySpace.getName()
                         << endl;

                    board.players.at(
                            board.boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).setCashAmount(
                            board.players.at(board.boardSpaces.at(
                                    currentBoardPosition).propertySpace.getOwnedBy()).getCashAmount()
                            + currentCashAmount
                    );

                    for (int i = 1; i < board.getSpaces(); i++) {
                        if (board.boardSpaces.at(i).propertySpace.getOwnedBy()
                            == board.players.at(currentPlayer).getNumIdentifier()) {
                            board.boardSpaces.at(i).propertySpace.setOwnedBy(board.players.at(
                                    board.boardSpaces[currentBoardPosition].propertySpace.getOwnedBy()).getNumIdentifier());
                        }
                    }

                    leaveGame(board, currentPlayer);
                    return true;

                } else {
                    currentCashAmount -= (rentOfPos * setMulti);
                    board.players.at(currentPlayer).setCashAmount(currentCashAmount);
                    currentCashAmount = board.players.at(currentPlayer).getCashAmount();

                    board.players.at(
                            board.boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).setCashAmount(
                            board.players.at(board.boardSpaces.at(
                                    currentBoardPosition).propertySpace.getOwnedBy()).getCashAmount()
                            + (rentOfPos) * setMulti
                    );

                    cout << board.players.at(currentPlayer).getName() << " paid " <<
                         board.players.at(
                                 board.boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).getName() <<
                         " $" << (rentOfPos * setMulti) << " for landing on "
                         << board.boardSpaces[currentBoardPosition].propertySpace.getName() <<
                         endl;
                }
            }

        } else if(!board.boardSpaces.at(currentBoardPosition).propertySpace.getOwned()) {

            if(board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() > board.players.at(currentPlayer).getCashAmount()) {

                cout << board.players.at(currentPlayer).getName() << " you do not have enough money to purchase " <<
                     board.boardSpaces.at(currentBoardPosition).propertySpace.getName() << endl;

                cout << board.boardSpaces.at(currentBoardPosition).propertySpace.getName() << " costs $" <<
                     board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() << " but you only have $" <<
                     board.players.at(currentPlayer).getCashAmount() << endl;

            } else {

                cout << "Would you like to buy " << board.boardSpaces.at(currentBoardPosition).propertySpace.getName()
                     << " for $" << board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() << "?" << endl;

                cout << "Rent on " << board.boardSpaces.at(currentBoardPosition).propertySpace.getName() << " is $" << board.boardSpaces.at(currentBoardPosition).propertySpace.getRent() << endl;

                cout << "Enter y for yes or n for no: " << endl;

                cin >> choice;
            }

            if (choice == 'Y' || choice == 'y') {

                board.players.at(currentPlayer).setCashAmount(
                        currentCashAmount - board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost()
                );

                currentCashAmount = board.players.at(currentPlayer).getCashAmount();

                board.boardSpaces.at(currentBoardPosition).propertySpace.setOwned(true);

                board.boardSpaces.at(currentBoardPosition).propertySpace.setOwnedBy(board.players.at(currentPlayer).getNumIdentifier());

                board.players.at(currentPlayer).setNetWorth(
                        board.players.at(currentPlayer).getNetWorth() + board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost()
                );

                cout << board.players.at(currentPlayer).getName() << " bought "
                     << board.boardSpaces.at(currentBoardPosition).propertySpace.getName()
                     << " for $" << board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() << endl;
            }

            else if(choice == 'N' || choice == 'n') {

                auctionProperty(board, currentPlayer, currentBoardPosition);
            }
        }

        cout << endl;
    }
    if (diceRoller.getRoll1() == diceRoller.getRoll2()){
            return false;
    } else {
        return true;
    }
}

void GameState::auctionProperty(Board &board, int currentPlayer, int currentBoardPosition) {

    int highestBid = 0; // Money Value

    int highestBidder = 0; // Num Identifier

    int playersInAuction = board.getNumOfPlayersLeft();

    bool auctionOver = false;

    cout << "Starting the auction for " << board.boardSpaces.at(currentBoardPosition).propertySpace.getName() << endl;

    if(highestBid != 0) {



    } else {
        cout << "No one has bid on " << board.boardSpaces.at(currentBoardPosition).propertySpace.getName()
             << " [" << board.boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() << "] "
             << endl;
    }
}

void GameState::leaveGame(Board& board, int currentPlayer) {

    board.players.at(currentPlayer).setInGame(false);

    board.players.at(currentPlayer).setNumIdentifier(-99);
    board.players.at(currentPlayer).setBoardPosition(-99);
    board.players.at(currentPlayer).setNetWorth(0);
    board.players.at(currentPlayer).setCashAmount(0);

    board.setNumOfPlayersLeft(board.getNumOfPlayersLeft() - 1);

    //board.decreasePlayerNumber();
}

bool GameState::gameOver(Board& board, int currentTurnNumber, int playersLeft) {
    if(board.rules.getTurnLimit() == currentTurnNumber){
        return true;
    } else if(board.rules.getPlayersToEndGame() == playersLeft) {
        return true;
    } else {
        return false;
    }
}

void GameState::declareWinner(Board& board, int playersLeft) {

    std::vector<int>vectorOfPlayersLeft;
    int i = 0;
    int winner = 0;

    board.displayBoard(board);

    if(playersLeft == 1) {
        for(i = 0; i < board.getPlayerNumber(); i++) {
            if(board.players.at(i).getInGame()) {
                winner = i;
            }
        }

        cout << "The winners are " << endl << board.players.at(winner).getName();
        cout << endl;
        return;

    } else {
        for(i = 0; i < board.getPlayerNumber(); i++) {
            if(board.players.at(i).getInGame()) {
                vectorOfPlayersLeft.push_back(i);
            }
        }

        for (unsigned int j = 0; j < vectorOfPlayersLeft.size(); j++) {
            board.players.at(j).setNetWorth(
                    board.players.at(j).getNetWorth() +
                            board.players.at(j).getCashAmount()
            );

            /*
            cout << board.players.at(j).getName() << ": " << endl
                 << "  Cash: " << board.players.at(j).getCashAmount()
                 << "  Net Worth: " << board.players.at(vectorOfPlayersLeft.at(j)).getNetWorth()
                 << "  Board Position: " << board.players.at(vectorOfPlayersLeft.at(j)).getBoardPosition()
                 << endl;*/
        }

        int numOfWinners = 1;

        int maxPlayer = 0;

        for(unsigned int k = 1; k < vectorOfPlayersLeft.size(); k++) {

            if(board.players.at(k).getNetWorth() > board.players.at(maxPlayer).getNetWorth()) {
                maxPlayer = board.players.at(k).getNumIdentifier();
            } else if(board.players.at(k).getNetWorth() == board.players.at(maxPlayer).getNetWorth()) {
                numOfWinners++;
            }
        }

        if(numOfWinners == 1) {
            cout << "The winners are " << endl << board.players.at(maxPlayer).getName();
        } else {

            std::vector<int>winners(numOfWinners);

            for(unsigned int k = 1; k < vectorOfPlayersLeft.size(); k++) {
                if(board.players.at(k).getNetWorth() == board.players.at(vectorOfPlayersLeft.at(k-1)).getNetWorth()) {
                    winners.at(k) = board.players.at(vectorOfPlayersLeft.at(k)).getNumIdentifier();
                    winners.at(k-1) = board.players.at(vectorOfPlayersLeft.at(k-1)).getNumIdentifier();
                }
            }

            cout << "The winners are " << endl;

            for(unsigned int i = 0; i < winners.size(); i++) {
                cout << board.players.at(winners.at(i)).getName() << endl;
            }
            printf("\n");
        }
    }
}

//**********************************************************************************************************************************
