//
// Created by Rainy Memory on 2021/4/13.
//

#include "Administrator.h"

void Administrator::initialize() {
    Ptilopsis = new Parser;
    Saria     = new UserManager(UserIndexPath, UserStoragePath, defaultOut);
    Silence   = new TrainManager(TrainIndexPath, TrainStoragePath, TrainTicketPath, TicketStoragePath, TrainStationPath, defaultOut);
    Ifrit     = new OrderManager(Saria, Silence, OrderIndexPath, OrderPendingPath, defaultOut);
}

void Administrator::clean() {
    Saria   -> clear();
    Silence -> clear();
    Ifrit   -> clear();
}

Administrator::Administrator() {
    runProgramme();
}

Administrator::~Administrator() {
    delete Ptilopsis;
    delete Saria;
    delete Silence;
    delete Ifrit;
}

void Administrator::runProgramme() {
    std::ios::sync_with_stdio(false);
    initialize();
    const int CMD_SIZE = 5000;
    char cmd[CMD_SIZE];
    bool flag = true;
    while (flag) {
        memset(cmd, 0, sizeof(cmd));
        fgets(cmd, CMD_SIZE, stdin);
        Ptilopsis -> resetBuffer(cmd);
        defaultOut << "[" << Ptilopsis -> getTimeStamp() << "] ";
        switch (Ptilopsis -> getType()) {
            case Parser::ADDUSER:
                Saria   -> addUser(*Ptilopsis);
                break;
            case Parser::LOGIN:
                Saria   -> login(*Ptilopsis);
                break;
            case Parser::LOGOUT:
                Saria   -> logout(*Ptilopsis);
                break;
            case Parser::QUERYPROFILE:
                Saria   -> queryProfile(*Ptilopsis);
                break;
            case Parser::MODIFYPROFILE:
                Saria   -> modifyProfile(*Ptilopsis);
                break;
            case Parser::ADDTRAIN:
                Silence -> addTrain(*Ptilopsis);
                break;
            case Parser::RELEASETRAIN:
                Silence -> releaseTrain(*Ptilopsis);
                break;
            case Parser::QUERYTRAIN:
                Silence -> queryTrain(*Ptilopsis);
                break;
            case Parser::DELETETRAIN:
                Silence -> deleteTrain(*Ptilopsis);
                break;
            case Parser::QUERYTICKET:
                Silence -> queryTicket(*Ptilopsis);
                break;
            case Parser::QUERYTRANSFER:
                Silence -> queryTransfer(*Ptilopsis);
                break;
            case Parser::BUYTICKET:
                Ifrit   -> buyTicket(*Ptilopsis);
                break;
            case Parser::QUERYORDER:
                Ifrit   -> queryOrder(*Ptilopsis);
                break;
            case Parser::REFUNDTICKET:
                Ifrit   -> refundTicket(*Ptilopsis);
                break;
            case Parser::CLEAN:
                clean();
                defaultOut << "0" << endl;
                break;
            case Parser::EXIT:
                flag = false;
                defaultOut << "bye" << endl;
                break;
            default:
                defaultOut << "[Error]Invalid command." << endl;
                break;
        }
    }
}
