#include "RunningGameMode.h"
#include "CommandHandler.h"
#include "Command.h"
#include "Game.h"
//#include "mainwindow.h"

/* Remove mainwindow.h and all relevant class for running in VSCode */

RunningGameMode::RunningGameMode()
{
    mainWindow = nullptr;
    invoker = nullptr;
    game = nullptr;
}

RunningGameMode::RunningGameMode(int numPlayer)
{
    //mainWindow = new MainWindow;
    invoker = new CommandHandler;
    game = new Game(numPlayer);

    invoker->addFixedCommand( new GoCommand(game, &game->_idTurnPlayer) );
    invoker->addFixedCommand( new PassCommand(game, &game->_idTurnPlayer) );
    invoker->addFixedCommand( new BuyCommand(game, &game->_idTurnPlayer) );
    //invoker->addFixedCommand( new Build(game, &mainWindow->idChose) );
    //invoker->addFixedCommand( new SellCommand(game, &mainWindow->idChose) );
    //invoker->addFixedCommand( new Mortage(game, &mainWindow->idChose) );
    //invoker->addFixedCommand( new Redeem(game, &mainWindow->idChose) );
    invoker->addFixedCommand( new NotifyCommand(game, mainWindow) );
    invoker->addFixedCommand(new Update(game, mainWindow) );

    game->invoker = invoker;
    //mainWindow->invoker = invoker;

    game->notifyChange("cell", 17);
    game->notifyChange("cell", 16);
    game->notifyChange("player", 1);

    //mainWindow->show();
}

RunningGameMode::~RunningGameMode()
{
    //delete mainWindow;
    delete invoker;
    delete game;
}

CommandHandler* RunningGameMode::getCommandHandler()
{
    return invoker;
}

void RunningGameMode::debugAddIdChose(int idPlayer, int idCell)
{
    /*
    mainWindow->listIdChose.clear();
    mainWindow->listIdChose.push_back(idPlayer);
    mainWindow->listIdChose.push_back(idCell);
    */
}
