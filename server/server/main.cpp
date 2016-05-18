//
//  main.cpp
//  server
//
//  Created by Sergey Proforov on 17.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include <signal.h>
#include "../../common/CSafeCout.h"
#include "Poco/Net/HTTPServer.h"
#include "CRequestFactory.h"

using namespace Poco::Net;

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
    safe::cout << "Press \"ctrl+c\" to quit the SERVER\n";
    
    try {
        std::shared_ptr<HTTPServer> server( new HTTPServer( new CRequestHandlerFactory(),
                                                           ServerSocket(8080),
                                                           new HTTPServerParams()) );
        server->start();
        
        do{
            std::unique_lock<std::mutex> lock( g_mutex );
            g_waiter.wait(lock);
            safe::cout << "main wakeup\n";
        }
        while ( run );
        
        server->stop();
    } catch ( Poco::Exception & ex ) {
        safe::cout << ex.message().c_str();
    }
    
    std::cout << "Bye!" << std::endl;
    return 0;
}
