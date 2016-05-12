//
//  IService.h
//  client
//
//  Created by Sergey Proforov on 09.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef client_IService_h
#define client_IService_h

#include <string>
#include <functional>

//Интерфейс взаимодействия с сервером, делаем независимость от протокола.
class IService{
public:
    virtual ~IService(){};
    virtual void get(unsigned int naturalNubmer,
                     std::function<void(unsigned int n, std::string)> callBack) = 0;
};

#endif
