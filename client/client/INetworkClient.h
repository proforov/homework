//
//  INetworkClient.h
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef client_INetworkClient_h
#define client_INetworkClient_h

//Интерфейс взаимодействия с сервером, делаем независимость от протокола.
class INetworkClient{
public:
    virtual ~INetworkClient(){};
    virtual std::string get();
};

#endif
