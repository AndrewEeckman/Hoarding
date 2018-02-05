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

        } else if (playerAction == 2) {/*
            for(int i = 1; i < numOfSpaces; i++) {
                if((*board).(*board)Space[i].propertyType.ownedBy == (*board).player[player].numIdentifier) {
                    (*board).(*board)Space[i].propertyType.ownedBy = -1;
                    (*board).(*board)Space[i].propertyType.owned = false;
                }
            }
            leaveGame((*board), rules, numOfSpaces, player, &(*numOfPlayersLeft));
            turnOver = true;
        }*/
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

    cout << "You rolled a " << diceRoll << endl;

    if(diceRoll + currentBoardPosition < (*board).getSpaces()) {
        (*board).players.at(currentPlayer).setBoardPosition(currentBoardPosition + diceRoll);
        currentBoardPosition = (*board).players.at(currentPlayer).getBoardPosition();


    } else if(diceRoll + currentBoardPosition >= (*board).getSpaces()) { //FIXME: INACCURATELY ADDING GO VALUES
        (*board).players.at(currentPlayer).setBoardPosition((diceRoll + currentBoardPosition) % (*board).getSpaces());
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
        (*board).players.at(currentPlayer).setBoardPosition((*board).getSpaces()-1);
        currentBoardPosition = (*board).players.at(currentPlayer).getBoardPosition();
    }

    (*board).players.at(currentPlayer).setCashAmount(currentCashAmount);
}

//**********************************************************************************************************************************
