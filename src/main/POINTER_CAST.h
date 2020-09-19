#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<map>

#ifndef POINTER_CAST_H
#define POINTER_CAST_H

//Maybe make it templated? not sure
template<class T>
struct POINTER_CAST{
    public:
        int* intP;
        double* dubP;
        float* floP;
        char* chrP;
        std::string* strP;
        T* objP;
};


#endif