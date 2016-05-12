//
//  CSafeCout.h
//  client
//
//  Created by Sergey Proforov on 13.05.16.
//  Copyright (c) 2016 Proforov Inc. All rights reserved.
//

#ifndef __client__CSafeCout__
#define __client__CSafeCout__

#include <iostream>

namespace safe {
    
    class CSafeCout;
    extern CSafeCout cout;
    
    //потокобезопасный вывод на консоль
    class CSafeCout{
        public:
            void operator <<(const char * str);
    };
}

#endif /* defined(__client__CSafeCout__) */
