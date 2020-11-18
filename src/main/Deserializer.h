#include<iostream>
#include<stdlib.h>
#include"CSchematic.h"
#include<fstream>
#include<sys/mman.h>

#ifndef DESERIALIZER_H
#define DESERIALIZER_H

template<class T>
class Deserializer{
private:
    CSchematic<T> schematic;

public:
    T deserialize(std::string filePath);
    void init(std::string classFile);

};

template<class T>
void Deserializer<T>::init(std::string classFile){
    CSchematic<T> schematic_temp;
    schematic_temp.loadScheme(classFile);
    this->schematic = schematic_temp;
}

template<class T>
T Deserializer<T>::deserialize(std::string filePath){
    
    std::map<std::string, size_t> dataTypeSize = this->schematic.getDataTypeSizeMap();
    std::vector<std::string> dataTypeOrder = this->schematic.getDataTypeOrder();
    std::ifstream inputFile(filePath, std::ios::in | std::ios::binary);
    if(!inputFile){
        std::cout<<"Could not open file..."<<std::endl;
        exit(1);
    }
    T myObj;
    void* objLoc = & myObj;
    void* it = objLoc;
    for(int i = 0; i < dataTypeOrder.size(); i++){
        std::string dataType = dataTypeOrder[i];
        size_t size;
        inputFile.read((char*)&size, sizeof(size_t));
        if(dataType == "string"){
            char* cvrtToString = new char[size];
            inputFile.read((char*)cvrtToString, size);
            cvrtToString[size] = '\0';
            *(std::string*)it = cvrtToString;
            delete[] cvrtToString;
        }else{
            inputFile.read((char*)it, size);
        }
        it = schematic.iterate(i, it);
    }
    return myObj;
}

#endif
