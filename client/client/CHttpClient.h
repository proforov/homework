//
//  CHttpClient.h
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef __client__CHttpClient__
#define __client__CHttpClient__

#include <memory>
#include "IConnection.h"
#include "IService.h"

//Класс для работы с HTTP севером
class CHttpClient : public IService{

private:
    std::shared_ptr<IConnection> _conn;
    std::string                 _address;
    int16_t                     _port;
    
private:
    CHttpClient(const CHttpClient & copy);
    
public:
    CHttpClient(IConnection * connection, const char * address, uint16_t port);
    virtual ~CHttpClient();
    
    virtual void get(unsigned int naturalNubmer,
                            std::function<void(unsigned int n, std::string)> callBack );
};

#endif /* defined(__client__CHttpClient__) */
