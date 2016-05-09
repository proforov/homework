//
//  CHttpRequest.cpp
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "CHttpRequest.h"

CHttpRequest::CHttpRequest(const char * path, const char * host){
    _path = path;
    _host = host;
}

CHttpRequest::~CHttpRequest(){
    
}

void CHttpRequest::addHeader(const char * header, const char * value){
    _headers.insert( std::pair<const char *, std::string>( header, value ) );
}

//void CHttpRequest::fillBaseHeaders(){
//    addHeader(H_USER_AGENT, "simple agent");
//    addHeader(H_ACCEPT, "text/html, application/json");
//    addHeader(H_ACCEPT_CHARSET, "utf-8");
//    addHeader(H_CONNECTION, "keep-alive");
//    addHeader(H_KEEP_ALIVE, "100");
//}

const char * CHttpRequest::httpGet(){
    _buffer.str("");
    _buffer.clear();

    //basic
    _buffer << "GET " << _path << " HTTP/1.1" << std::endl;
    _buffer << "Host: " << _host << std::endl;
    
    //additional headers
    for( auto it : _headers ){
        _buffer << it.first << it.second << std::endl;
    }
    
    //end headers
    _buffer << std::endl;
    return _buffer.str().c_str();
}

