//
//  main.cpp
//  client
//
//  Created by Sergey Proforov on 05.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include <iostream>
#include <memory>
#include "CClient.h"

int main(int argc, const char * argv[]) {
    std::cout << "Hi, %username%!" << std::endl;
    std::cout << "Type \"exit\" to quit the program" << std::endl;
    char buffer[128];
    
    //инициализация
    const CClient & client = CClient("212.59.100.26", 80);
    client.start();
    
    bool bBreak = false;
    do{
        std::cin.getline(buffer, sizeof(buffer));
        std::string strBuf = buffer;
        if( strBuf.find("exit") != std::string::npos ){
            bBreak = true;
        }
        else{
            std::cout << "\"" << strBuf << "\" is unknown command." << std::endl;
        }
    }
    while ( !bBreak );
    
    //остановка клиента
    client.stop();
    
    std::cout << "Bye!" << std::endl;
    return 0;
}
