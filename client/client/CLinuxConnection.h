//
//  CConnection.h
//  client
//
//  Created by Sergey Proforov on 06.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef __client__CConnection__
#define __client__CConnection__

#include <iostream>
#include <string>
#include <vector>
#include "IConnection.h"

class CLinuxConnection : public IConnection{
private:
    int         _socket;
    int32_t     _port;
    std::string _address;
    int32_t     _sockTimeout;
    
private:
    CLinuxConnection();
    CLinuxConnection(const CLinuxConnection & anotherConnection);
    
public:
    CLinuxConnection( std::string addres, int32_t port );
    virtual ~CLinuxConnection();
    
    virtual bool    connect();
    virtual void    setTimeout( int32_t seconds );
    virtual int     read(unsigned char * buffer);
    virtual int     write(unsigned char * buffer);
};

#endif /* defined(__client__CConnection__) */
