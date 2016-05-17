//
//  CRequestFactory.h
//  server
//
//  Created by Sergey Proforov on 17.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef __server__CRequestFactory__
#define __server__CRequestFactory__

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"

using namespace Poco::Net;

//класс обработки входящих запросов
class CRequestHandlerFactory : public HTTPRequestHandlerFactory{
public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &);
};

//класс обработки запроса на разложение на множители
class CExpandRequestHandler : public HTTPRequestHandler{
    virtual void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};

//обработка неизвестного запроса
class CNotFoundRequestHandler : public HTTPRequestHandler{
    virtual void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};

#endif