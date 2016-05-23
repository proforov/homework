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


CClient::CClient( const char * ip, int16_t port ) :
    _stopFlag(true),
    _service(),
    _thread(),
    _done(true)
{
    _service.reset( IService::createService( ip, port) );
}

CClient::~CClient(){
    stop();
}

void CClient::numberExpandResultHandler(unsigned int num, std::string result){
    safe::cout << result.c_str();
    safe::cout << "\n";
}

//генерим случайное натуральное число
//генерим случайный интервал времени
//ждем события выхода или истечения случайного интервала в милисекундах
void CClient::getRandomNatNumbers(){
    try {
        while (!_stopFlag) {
            
            safe::cout << "generating new number\n";
            
            unsigned int randNum = getRandomNatural(0);
            
            std::function<void(unsigned int, std::string)> cb = std::bind(&CClient::numberExpandResultHandler,
                                                                          this,
                                                                          std::placeholders::_1,
                                                                          std::placeholders::_2);
            _service->get(randNum, cb);
            
            unsigned int randPeriod = getRandomMilliseconds(randNum);
            
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point end = start + std::chrono::milliseconds( randPeriod );
            
            while ( !_stopFlag ) {
                
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                
                if( (end - now).count() > 0 ){
                    std::unique_lock<std::mutex> lock(_waiterMutex);
                    _waiter.wait_for( lock, end - now );
                }
                else{
                    //time is out
                    break;
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

//may be exceptions, should catch them (to-do)
void CClient::stop(){
    _stopFlag = true;
    
    std::unique_lock<std::mutex> lock(_waiterMutex);
    _waiter.notify_one();
    lock.unlock();
    
    if( _thread.joinable() )
        _thread.join();
}