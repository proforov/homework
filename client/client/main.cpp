//
//  main.cpp
//  client
//
//  Created by Sergey Proforov on 05.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include <signal.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "CClient.h"
#include "CSafeCout.h"

//condition to wait
std::condition_variable g_waiter;
std::mutex              g_mutex;

//check for spurious wakeup
bool run = true;

//handle ctrl+c
void handle_sigint(int sig){
    run = false;
    std::unique_lock<std::mutex> lock( g_mutex );
    g_waiter.notify_one();
}

int main(int argc, const char * argv[]) {
    
    struct sigaction sigIntHandler;
    
    sigIntHandler.sa_handler = handle_sigint;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    
    sigaction(SIGINT, &sigIntHandler, NULL);
    
    safe::cout << "Hi, %username%!\n";
    safe::cout << "Press \"ctrl+c\" to quit the program\n";
    
    //инициализация
    std::shared_ptr<CClient> client( new CClient("212.59.100.26", 80) );
    client->start();
    
    do{
        std::unique_lock<std::mutex> lock( g_mutex );
        g_waiter.wait(lock);
        safe::cout << "main wakeup\n";
    }
    while ( run );
    
    //остановка клиента
    client->stop();
    
    std::cout << "Bye!" << std::endl;
    return 0;
}
