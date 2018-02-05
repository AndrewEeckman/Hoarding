//
// Created by Andrew Eeckman on 2/4/18.
//

//**********************************************************************************************************************************

#include "GameState.h"

//**********************************************************************************************************************************

void Monopoly::GameState::getMove(Monopoly::Board *board, int currentPlayer) {
    int playerAction = 0;

    bool turnOver = false;

    while (!turnOver) {

        if (!(*board).players.at(currentPlayer).getInGame()) {
            turnOver = true;
            printf("\n");
            continue;
        }

        (*board).displayBoard(*(&board));

        cout << (*board).players.at(currentPlayer).getName() << " please enter your move" << endl;
        cout << "1 to roll dice" << endl << "2 to leave the game ";

        cin >> playerAction;

        if (playerAction == 1) {
            movePlayer(&(*board), currentPlayer);
            turnOver = true;

        } else if (playerAction == 2) {
            leaveGame(&(*board), currentPlayer);
            turnOver = true;
        }
    }
}

//**********************************************************************************************************************************

void Monopoly::GameState::movePlayer(Board *board, int currentPlayer) {

    int currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();
    int currentBoardPosition = (*board).players.at(currentPlayer).getBoardPosition();

    int diceRoll1 = (rand() % 6) + 1;
    int diceRoll2 = (rand() % 6) + 1;
    int diceRoll = diceRoll1 + diceRoll2;

    cout << "You rolled a " << diceRoll1 << endl; ///

    if(diceRoll + currentBoardPosition < (*board).getSpaces()) {
        (*board).players.at(currentPlayer).setBoardPosition(currentBoardPosition + diceRoll);
        currentBoardPosition = (*board).players.at(currentPlayer).getBoardPosition();


    } else if(diceRoll + currentBoardPosition >= (*board).getSpaces()) { //FIXME: INACCURATELY ADDING GO VALUES
        (*board).players.at(currentPlayer).setBoardPosition((diceRoll + currentBoardPosition) / (*board).getSpaces()); ///
        currentBoardPosition = (*board).players.at(currentPlayer).getBoardPosition();

        int numTimesAroundGo = (currentBoardPosition + diceRoll) / (*board).getSpaces();

        if(currentBoardPosition == 0) {
            currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();
            for(int i = 0; i < numTimesAroundGo-1; i++) {
                (*board).players.at(currentPlayer).setCashAmount(currentCashAmount + (*board).boardSpaces.at(0).goSpace.getMoneyAroundGo());
                currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();
            }
            (*board).players.at(currentPlayer).setCashAmount(currentCashAmount + ((*board).boardSpaces.at(0).goSpace.getMoneyAroundGo() * (*board).rules.getSalMultiGo()));
            currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();
        } else {
            for(int i = 0; i < numTimesAroundGo; i++) {
                (*board).players.at(currentPlayer).setCashAmount(currentCashAmount + (*board).boardSpaces.at(0).goSpace.getMoneyAroundGo());
                currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();
            }
        }

        numTimesAroundGo = 0;

    } else {
        (*board).players.at(currentPlayer).setBoardPosition((*board).getSpaces()+1); ///
        currentBoardPosition = (*board).players.at(currentPlayer).getBoardPosition();
    }

    (*board).players.at(currentPlayer).setCashAmount(currentCashAmount);




    /////// SOMETHING NEW TO WORK ON WHILE WE WAIT FOR GO TO FIX ITSELF YEAH?





    int rentOfPos = (*board).boardSpaces.at(currentBoardPosition).propertySpace.getRent();
    char choice = ' ';

    if(currentBoardPosition != 0) {
        if ((*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwned()) {

            if ((*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy() == currentPlayer) {
                //nothing because the player is paying themselves
            } else {

                int setMulti = 1; //Checks to see if the property set is owned by one person
                for (int position = 1; position < (*board).getSpaces(); position++) {

                    if ((*board).boardSpaces.at(position).propertySpace.getSetID() ==
                        (*board).boardSpaces.at(currentBoardPosition).propertySpace.getSetID()) {

                        if ((*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy() ==
                            (*board).boardSpaces.at(position).propertySpace.getOwnedBy()) {

                            setMulti = (*board).rules.getSetMulti();

                        } else {

                            setMulti = 1;
                            break;
                        }
                    }
                }


                if ((currentCashAmount - (rentOfPos * setMulti)) < 0) {

                    cout << (*board).players.at(currentPlayer).getName() << " went bankrupt to " <<
                         (*board).players.at(
                                 (*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).getName()
                         << endl;

                    (*board).players.at(
                            (*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).setCashAmount(
                            (*board).players.at((*board).boardSpaces.at(
                                    currentBoardPosition).propertySpace.getOwnedBy()).getCashAmount()
                            + currentCashAmount);

                    for (int i = 1; i < (*board).getSpaces(); i++) {
                        if ((*board).boardSpaces.at(i).propertySpace.getOwnedBy()
                            == (*board).players.at(currentPlayer).getNumIdentifier()) {
                            (*board).boardSpaces.at(i).propertySpace.setOwnedBy((*board).players.at(
                                    (*board).boardSpaces[currentBoardPosition].propertySpace.getOwnedBy()).getNumIdentifier());
                        }
                    }
                    //FIXME: ADD LEAVE GAME FUNCTION;
                    //leaveGame(board, rules, numOfSpaces, player, &(*numOfPlayersLeft));
                    return;

                } else {
                    currentCashAmount -= (rentOfPos * setMulti);
                    (*board).players.at(currentPlayer).setCashAmount(currentCashAmount);
                    currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();

                    (*board).players.at(
                            (*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).setCashAmount(
                            (*board).players.at((*board).boardSpaces.at(
                                    currentBoardPosition).propertySpace.getOwnedBy()).getCashAmount()
                            + (rentOfPos) * setMulti
                    );

                    cout << (*board).players.at(currentPlayer).getName() << " payed " <<
                         (*board).players.at(
                                 (*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwnedBy()).getName() <<
                         " $" << rentOfPos << " for landing on "
                         << (*board).boardSpaces[currentBoardPosition].propertySpace.getName() <<
                         endl;
                }
            }

        } else if(!(*board).boardSpaces.at(currentBoardPosition).propertySpace.getOwned()) {

            if((*board).boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() > (*board).players.at(currentPlayer).getCashAmount()) {

                cout << (*board).players.at(currentPlayer).getName() << "you do not have enough money to purchase " <<
                     (*board).boardSpaces.at(currentBoardPosition).propertySpace.getName() << endl;

                cout << (*board).boardSpaces.at(currentBoardPosition).propertySpace.getName() << " costs $" <<
                     (*board).boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() << " but you only have $" <<
                     (*board).players.at(currentPlayer).getCashAmount() << endl;

            } else {

                cout << (*board).players.at(currentPlayer).getName() << " would you like to buy " << (*board).boardSpaces.at(currentBoardPosition).propertySpace.getName()
                     << " for $" << (*board).boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost() << "?" << endl;

                cout << "The rent on this property is $" << (*board).boardSpaces.at(currentBoardPosition).propertySpace.getRent() << endl;

                cout << "You currently have $" << (*board).players.at(currentPlayer).getCashAmount() << endl;

                cout << "Y for yes, N for no: " << endl;

                cin >> choice;
            }

            if (choice == 'Y' || choice == 'y') {

                (*board).players.at(currentPlayer).setCashAmount(
                        currentCashAmount - (*board).boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost()
                );

                currentCashAmount = (*board).players.at(currentPlayer).getCashAmount();

                (*board).boardSpaces.at(currentBoardPosition).propertySpace.setOwned(true);

                (*board).boardSpaces.at(currentBoardPosition).propertySpace.setOwnedBy((*board).players.at(currentPlayer).getNumIdentifier());

                (*board).players.at(currentPlayer).setNetWorth(
                        (*board).players.at(currentPlayer).getNetWorth() + (*board).boardSpaces.at(currentBoardPosition).propertySpace.getPropertyCost()
                );
            }
        }

        cout << endl;
    }
}

void Monopoly::GameState::leaveGame(Monopoly::Board *board, int currentPlayer) {
    for(int i = 1; i < (*board).getSpaces(); i++) {
        if((*board).boardSpaces.at(i).propertySpace.getOwnedBy() == (*board).players.at(currentPlayer).getNumIdentifier()) {
            (*board).boardSpaces.at(i).propertySpace.setOwnedBy(-1);
            (*board).boardSpaces.at(i).propertySpace.setOwned(false);
        }
    }

    (*board).players.at(currentPlayer).setInGame(false);

    (*board).players.at(currentPlayer).setNumIdentifier(-99);
    (*board).players.at(currentPlayer).setBoardPosition(-99);
    (*board).players.at(currentPlayer).setNetWorth(0);
    (*board).players.at(currentPlayer).setCashAmount(0);

    (*board).setNumOfPlayersLeft((*board).getNumOfPlayersLeft() - 1);

    //(*board).decreasePlayerNumber();
}

bool Monopoly::GameState::gameOver(Monopoly::Board *board, int currentTurnNumber, int playersLeft) {
    if((*board).rules.getTurnLimit() == currentTurnNumber){
        return true;
    } else if ((*board).rules.getPlayersToEndGame() == playersLeft) {
        return true;
    } else {
        return false;
    }
}

void Monopoly::GameState::declareWinner(Monopoly::Board *board, int playersLeft) {

    std::vector<int>vectorOfPlayersLeft((*board).getPlayerNumber());

    int vectorCounter = 0;

    for(int i = 0; i < (*board).getPlayerNumber(); i++) {
        if((*board).players.at(i).getInGame()) {
            vectorOfPlayersLeft.at(vectorCounter) = (*board).players.at(i).getNumIdentifier();
            vectorCounter++;
        }
    }


    if(playersLeft == 1) {
        cout << "The winners are " << endl << (*board).players.at(vectorOfPlayersLeft.at(0)).getName();
        cout << endl;
        return;

    } else {

        /*

        for(int j = 0; j < playersLeft; j++) {
            (*board).players.at(vectorOfPlayersLeft.at(j)).

            board.player[arrayOfPlayersLeft[j]].netWorth += board.player[arrayOfPlayersLeft[j]].cashAmount;
        }*/

        int numOfWinners = 1;

        int maxPlayer = 0;

        for(int k = 1; k < playersLeft; k++) {

            if((*board).players.at(vectorOfPlayersLeft.at(k)).getNetWorth() > (*board).players.at(maxPlayer).getNetWorth()) {

                maxPlayer = (*board).players.at(vectorOfPlayersLeft.at(k)).getNumIdentifier();

            } else if((*board).players.at(vectorOfPlayersLeft.at(k)).getNetWorth() == (*board).players.at(vectorOfPlayersLeft.at(k-1)).getNetWorth()) {

                numOfWinners++;
            }
        }

        if(numOfWinners == 1) {
            cout << "The winners are " << endl << (*board).players.at(maxPlayer).getNumIdentifier();

        } else {

            std::vector<int>vectorWinners(numOfWinners);

            for(int k = 1; k < playersLeft; k++) {

                if((*board).players.at(vectorOfPlayersLeft.at(k)).getNetWorth() == (*board).players.at(vectorOfPlayersLeft.at(k-1)).getNetWorth()) {
                    vectorWinners.at(k) = (*board).players.at(vectorOfPlayersLeft.at(k)).getNumIdentifier();
                    vectorWinners.at(k-1) = (*board).players.at(vectorOfPlayersLeft.at(k-1)).getNumIdentifier();
                }
            }

            cout << "The winners are " << endl;

            for(int i = 0; i < numOfWinners; i++) {
                cout << (*board).players.at(vectorWinners.at(i)).getName() << endl;
            }
            cout << endl;
        }

    }
}

//**********************************************************************************************************************************
