//
//  IConnection.h
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef client_IConnection_h
#define client_IConnection_h

//Интерфейс соединения с хостом,
//делаем независимость от платформы и протокола
class IConnection{

public:
    virtual         ~IConnection(){};
    virtual bool    connect(const char * address, int port) = 0;
    
    //send recieve timeout
    virtual void    setTimeout( int seconds ) = 0;
    
    //return true if there is some more data
    virtual bool     read( char * buffer, uint32_t * size) = 0;
    
    //returns count of sent bytes
    virtual ssize_t     write( const char * buffer, uint32_t size) = 0;
};

#endif
