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
#include <list>
#include <future>
#include <mutex>

//собственно клиент, реализация требований
class CClient{
private:
    //services list
    std::list<std::shared_ptr<IService>>    _services;
    
    //check for stop flag
    std::atomic<bool> _stopFlag;
    
    //thread genereting numbers
    std::thread _thread;
    
    //thread done flag
    std::atomic<bool> _done;
    
    //waiter for random time period elapsed
    std::condition_variable _waiter;
    
    //mutex for condition
    std::mutex _waiterMutex;
    
    //max number to generate
    unsigned int _maxNatural;
    
    //max duration to generate
    unsigned int _maxPeriodMs;
    
private:
    //thread function
    void getRandomNatNumbers();
    
    //generate a pseudo random number
    unsigned int getRandomNatural( unsigned int seed );
    
    //generate a pseudo random number for a time period
    unsigned int getRandomMilliseconds( unsigned int seed );
    
public:
    CClient( std::string ip, int16_t port );
    ~CClient();
    
    //start generating numbers
    void start();
    
    //stop generating numbers
    void stop();
};

#endif /* defined(__client__CClient__) */
