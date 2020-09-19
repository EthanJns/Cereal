#include<iostream>
#include<stdlib.h>
#include"CSchematic.h"
#include<fstream>
#include<stack>
#ifndef SERIALIZER_H
#define SERIALIZER_H

template<class T>
class Serializer{
private:

    std::ofstream objFile;
    CSchematic<T> schematic;
    std::stack<CSchematic<T>> schematicStack;

public:
    Serializer(std::ofstream objFile, CSchematic<T> schematic){
        this->objFile = objFile;
        this->schematic = schematic;
    }

    void write(T obj){
        
    }


};

#endif
