//
//  CClient.cpp
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "CClient.h"
#include "CLinuxConnection.h"
#include "CHttpClient.h"
#include <unistd.h>
#include "CSafeCout.h"


CClient::CClient( std::string ip, int16_t port ) :
    _stopFlag(true),
    _services(),
    _thread(NULL)
{
}

CClient::~CClient(){
    stop();
    if( _thread != NULL ){
        if( _thread->joinable() )
            _thread->join();
        delete _thread;
    }
}

void CClient::getRandomNatNumbers(){
    try {
        while (!_stopFlag) {
            sleep(1);
            safe::cout << "thread\n";
        }
        safe::cout << "thread exit\n";
    } catch (std::exception & ex) {
        //something wrong
        safe::cout << ex.what();
        safe::cout << "\n";
    }
}

void CClient::start(){
    if( _thread != NULL )
        return;
    
    _stopFlag = false;
    _thread = new std::thread(&CClient::getRandomNatNumbers, this);
}

void CClient::stop(){
    _stopFlag = true;
}