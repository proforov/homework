//
//  CHttpRequest.h
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef __client__CHttpRequest__
#define __client__CHttpRequest__

#include <map>
#include <string>
#include <sstream>

const char * const H_USER_AGENT = "User-Agent: ";
const char * const H_ACCEPT = "Accept: ";
const char * const H_ACCEPT_CHARSET = "Accept-Charset: ";
const char * const H_CONNECTION = "Connection: ";
const char * const H_KEEP_ALIVE = "Keep-Alive: ";

class CHttpRequest{
private:
    std::map<const char *, std::string> _headers;
    std::stringstream _buffer;
    std::string _path;
    std::string _host;
    
private:
    CHttpRequest();
    CHttpRequest(const CHttpRequest & copy);
    
public:
    CHttpRequest(const char * host, const char * path);
    ~CHttpRequest();
    
    void addHeader(const char * header, const char * value);
    std::string httpGet();
};

#endif /* defined(__client__CHttpRequest__) */
