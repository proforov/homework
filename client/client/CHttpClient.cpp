//
//  CHttpClient.cpp
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "CHttpClient.h"
#include "CHttpRequest.h"
#include "CLinuxConnection.h"
#include <string>

CHttpClient::CHttpClient(const char * address, uint16_t port ) :
    _address(address)
{
    _port = port;
}

CHttpClient::~CHttpClient(){
}

void CHttpClient::get(unsigned int naturalNubmer,
                      std::function<void(unsigned int n, std::string)> callBack){
    
    if( _conn.get() == nullptr ){
        //нужно бы фабрику тут использовать
        _conn.reset(new CLinuxConnection());
    }
    
    if( !_conn->connect(_address.c_str(), _port) ){
        callBack( naturalNubmer, "Unable to expand number, connection error" );
        return;
    }
    
    std::string path = "/expandNumber/" + std::to_string(naturalNubmer);
    CHttpRequest req( _address.c_str(), path.c_str() );
    req.addHeader(H_USER_AGENT, "simple agent");
    req.addHeader(H_ACCEPT, "text/html, application/json");
    req.addHeader(H_ACCEPT_CHARSET, "utf-8");
    
    //keep alive заведомо больше, чем интервал между случайными моментами времени =)
    req.addHeader(H_CONNECTION, "keep-alive");
    req.addHeader(H_KEEP_ALIVE, "100");
    
    std::string getReq = req.httpGet();
    char buffer[1024] = {0};
    if( _conn->write( getReq.c_str(), (uint32_t)getReq.size() ) > 0 ){
        
        std::stringstream str;
        bool canRead = true;
        do {
            uint32_t bufSize = sizeof(buffer) - 1;
            canRead = _conn->read( buffer, &bufSize );
            if( canRead && bufSize > 0 ){
                str.write(buffer, bufSize );
            }
        } while (canRead);
        
        callBack( naturalNubmer, str.str() );
    }
    else{
        callBack( naturalNubmer, "Unable to expand number, send error" );
    }
}

