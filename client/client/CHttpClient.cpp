//
//  CHttpClient.cpp
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "CHttpClient.h"
#include "CHttpRequest.h"
#include <string>

CHttpClient::CHttpClient( IConnection * connection, const char * address, uint16_t port ) :
    _conn(connection),
    _address(address)
{
    _port = port;
}

CHttpClient::~CHttpClient(){
}

void CHttpClient::get(unsigned int naturalNubmer,
                      std::function<void(unsigned int n, std::string)> callBack){
    
    std::string path = "/expandNumber/" + std::to_string(naturalNubmer);
    std::shared_ptr<CHttpRequest> req(new CHttpRequest( _address.c_str(), path.c_str() ));
    req->addHeader(H_USER_AGENT, "simple agent");
    req->addHeader(H_ACCEPT, "text/html, application/json");
    req->addHeader(H_ACCEPT_CHARSET, "utf-8");
    req->addHeader(H_CONNECTION, "keep-alive");
    req->addHeader(H_KEEP_ALIVE, "100");
}

