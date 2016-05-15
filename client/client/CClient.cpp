//
//  CClient.cpp
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include <chrono>
#include <random>
#include "CClient.h"
#include "CLinuxConnection.h"
#include "CHttpClient.h"
#include "CSafeCout.h"


CClient::CClient( std::string ip, int16_t port ) :
    _stopFlag(true),
    _services(),
    _thread(),
    _done(true)
{
}

CClient::~CClient(){
    stop();
}


//генерим случайное натуральное число
//генерим случайный интервал времени
//ждем события выхода или истечения случайного интервала в милисекундах
void CClient::getRandomNatNumbers(){
    try {
        while (!_stopFlag) {
            
            safe::cout << "generating new number\n";
            
            unsigned int randNum = getRandomNatural(0);
            unsigned int randPeriod = getRandomMilliseconds(randNum);
            
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point end = start + std::chrono::milliseconds( randPeriod );
            
            while ( !_stopFlag ) {
                
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                
                if( (end - now).count() > 0 ){
                    std::unique_lock<std::mutex> lock(_waiterMutex);
                    _waiter.wait_for( lock, end - now );
                }
            }
        }
        safe::cout << "thread exit\n";
    } catch (std::exception & ex) {
        //something wrong
        safe::cout << ex.what();
        safe::cout << "\n";
    }
    _done = true;
}

unsigned int CClient::getRandomNatural(unsigned int seed){
    return 20;
}

unsigned int CClient::getRandomMilliseconds(unsigned int seed){
    return 10000;
}

void CClient::start(){
    if( _done == false ){
        safe::cout << "another client thread already running\n";
        return;
    }
    
    _done = false;
    _stopFlag = false;
    _thread = std::thread(&CClient::getRandomNatNumbers, this);
}

void CClient::stop(){
    _stopFlag = true;
    
    std::unique_lock<std::mutex> lock(_waiterMutex);
    _waiter.notify_one();
    lock.unlock();
    
    if( _thread.joinable() )
        _thread.join();
}