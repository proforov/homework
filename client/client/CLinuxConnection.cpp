//
//  CConnection.cpp
//  client
//
//  Created by Sergey Proforov on 06.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "CLinuxConnection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

CLinuxConnection::CLinuxConnection(){
    _socket = -1;
    _sockTimeout = 10;
}

bool CLinuxConnection::connect(const char * addres, int port){
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if( _socket < 0 ){
        return false;
    }
    
    struct timeval timeout = { _sockTimeout, 0 };
    
    if (setsockopt (_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0){
        return false;
    }
    
    struct sockaddr_in sin;
    bzero( &sin, sizeof(sin) );
    sin.sin_family = AF_INET;
    sin.sin_port = htons( port );
    
    inet_pton( AF_INET, addres, &sin.sin_addr );
    
    int res = ::connect(_socket, (struct sockaddr *)&sin, sizeof(sin));
    if( res < 0 ){
        return false;
    }
    return true;
}

void CLinuxConnection::setTimeout(int32_t seconds){
    _sockTimeout = seconds;
    if( _socket >= 0 ){
        struct timeval timeout = { _sockTimeout, 0 };
        setsockopt (_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout));
    }
}

CLinuxConnection::~CLinuxConnection(){
    if( _socket >= 0 ){
        close(_socket);
    }
}

int32_t CLinuxConnection::read( unsigned char * buffer ){
    return 0;
}

int32_t CLinuxConnection::write( unsigned char * buffer ){
    return 0;
}
