//
//  CClient.h
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef __client__CClient__
#define __client__CClient__

#include "IConnection.h"
#include "IService.h"
#include <thread>
#include <condition_variable>
#include <list>

//собственно клиент, реализация требований
class CClient{
private:
    std::list<std::shared_ptr<IService>>    _services;
    volatile bool _stopFlag;
    std::thread * _thread;
    
private:
    void getRandomNatNumbers();
    
public:
    CClient( std::string ip, int16_t port );
    ~CClient();
    
    //start generating numbers
    void start();
    
    //stop generating numbers
    void stop();
};

#endif /* defined(__client__CClient__) */
