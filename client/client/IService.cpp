//
//  IService.cpp
//  client
//
//  Created by Sergey Proforov on 24.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "IService.h"
#include "CHttpClient.h"
#include "CLinuxConnection.h"

//factory
IService * IService::createService( const char * address, int16_t port ){
    IService * ret = new CHttpClient( address, port );
    return ret;
}

