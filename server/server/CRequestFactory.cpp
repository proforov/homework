//
//  CRequestFactory.cpp
//  server
//
//  Created by Sergey Proforov on 17.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include <ostream>
#include "CRequestFactory.h"
#include "../../common/CSafeCout.h"

const char * HTTP_NOT_FOUND =
"<!DOCTYPE html> \
<html>\
<body>\
    <h1>The Page Not FOUNd</h1>\
    <p>There is only one valid path: /expandNumber/%number%</p>\
</body>\
</html>";


HTTPRequestHandler * CRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest & req)
{
    safe::cout << "Handling request: ";
    safe::cout << req.getURI().c_str();
    safe::cout << "\n";
    
    Poco::URI uri(req.getURI());
    if( uri.getPath().find("/expandNumber/") == 0 ){
        return new CExpandRequestHandler();
    }
    else{
        return new CNotFoundRequestHandler();
    }
}

//handle number expanding
void CExpandRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp){
    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("application/json");
    std::ostream& out = resp.send();
    int number = 1;
    out << "{ \"number\": " << number << ",\n";
    out << "\"expand\": [";
    //for
    out << "]}";
    out.flush();
}

//handle not found
void CNotFoundRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp){
    resp.setStatus(HTTPResponse::HTTP_NOT_FOUND);
    resp.setContentType("text/html");
    std::ostream& out = resp.send();
    out << HTTP_NOT_FOUND;
    out.flush();
}