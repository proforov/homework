//
//  CSafeCout.cpp
//  client
//
//  Created by Sergey Proforov on 13.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#include "CSafeCout.h"

namespace safe {
    std::mutex g_mutex;
    CSafeCout cout;
    
    void CSafeCout::operator<<(const char *str){
        g_mutex.lock();
        std::cout << str;
        g_mutex.unlock();
    }
}