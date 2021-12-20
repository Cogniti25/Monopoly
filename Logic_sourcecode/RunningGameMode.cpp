#include "RunningGameMode.h"
#include "CommandHandler.h"
#include "Command.h"
#include "Game.h"

RunningGameMode::RunningGameMode()
{
    mainWindow = nullptr;
    invoker = nullptr;
    game = nullptr;
}

RunningGameMode::RunningGameMode(int numPlayer)
{
    mainWindow = new GUI;
    invoker = new CommandHandler;
    game = new Game(numPlayer);

    invoker->addFixedCommand( new GoCommand(game, &game->_idTurnPlayer) );
    invoker->addFixedCommand( new PassCommand(game, &game->_idTurnPlayer) );
    invoker->addFixedCommand( new BuyCommand(game, &game->_idTurnPlayer) );
    invoker->addFixedCommand( new Build(game, &mainWindow->listIdChose) );
    invoker->addFixedCommand( new SellCommand(game, &mainWindow->listIdChose) );
    invoker->addFixedCommand( new Mortage(game, &mainWindow->listIdChose) );
    invoker->addFixedCommand( new Redeem(game, &mainWindow->listIdChose) );
}

RunningGameMode::~RunningGameMode()
{
    delete mainWindow;
    delete invoker;
    delete game;
}

CommandHandler* RunningGameMode::getCommandHandler()
{
    return invoker;
}

void RunningGameMode::debugAddIdChose(int idPlayer, int idCell)
{
    mainWindow->listIdChose.clear();
    mainWindow->listIdChose.push_back(idPlayer);
    mainWindow->listIdChose.push_back(idCell);
}