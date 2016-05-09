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


CClient::CClient( std::string ip, int16_t port ) :
    _thread( &CClient::getRandomNatumbers, this ),
    _condition(),
    _services()
{
    
}

void CClient::getRandomNatumbers(){
    std::cout<<"thread";
}

void CClient::start() const{
}

void CClient::stop() const{
    
}