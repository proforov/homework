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
#include "INetworkClient.h"

//Класс для работы с HTTP севером
class CHttpClient : public INetworkClient{

private:
    std::shared_ptr<IConnection *> _conn;
    
private:
    CHttpClient(const CHttpClient & copy);
    
public:
    CHttpClient( IConnection * connection );
    virtual ~CHttpClient();
    
    virtual std::string get();
};

#endif /* defined(__client__CHttpClient__) */
