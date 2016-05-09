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
    virtual void    setTimeout( int seconds ) = 0;
    virtual int     read(unsigned char * buffer) = 0;
    virtual int     write(unsigned char * buffer) = 0;
};

#endif
