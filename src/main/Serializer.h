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

    void serialize(T &obj);
    void init(std::string filePath);

};

template<class T>
void Serializer<T>::init(std::string filePath){
    CSchematic<T> schematic_temp;
    schematic_temp.loadScheme(filePath);
    this->schematic = schematic_temp;
}

template<class T>
void Serializer<T>::serialize(T &obj){
    std::map<std::string, size_t> dataTypeSize = this->schematic.getDataTypeSizeMap();
    std::vector<std::string> dataTypeOrder = this->schematic.getDataTypeOrder();
    std::string fileName = typeid(obj).name();
    fileName = fileName.substr(1);
    fileName+="_obj.dat";
    std::ofstream outFile(fileName, std::ios::out|std::ios::binary);
    if(!outFile){
        std::cout<<"Could not create and open file, exiting now...";
        exit(1);
    }
    void* it = &obj;
    for(int i = 0; i < dataTypeOrder.size(); i++){
        std::cout<<"Location of it: "<<it<<std::endl;
        std::string dataType = dataTypeOrder[i];
        if(dataType == "string"){
            std::string s = *(string*)it;
            size_t size = (*(string*)it).size();
            outFile.write((char*)&size, sizeof(size));
            outFile.write((char*)s.c_str(), size);
        }else{
            size_t size = dataTypeSize[dataType];
            outFile.write((char*)&size, sizeof(size));
            outFile.write((char*)it, size);
        }
        it = schematic.iterate(i, it);
    }

    outFile.close();
}

#endif