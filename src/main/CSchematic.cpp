#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<map>
#include "POINTER_CAST.h"
//#include"CSchematic.h"


template<class T>
void CSchematic<T>::testData(){
    void* ptr;
    POINTER_CAST<T>  pc = (*this.*getPct()[typeid(T)])(ptr); 
    const std::type_info &p = typeid(ptr);
    const std::type_info &c = typeid(pc.objP);
    std::cout<<p.name()<<std::endl;
    std::cout<<c.name()<<std::endl;
}


template<class T>
CSchematic<T>::CSchematic(){
    //this->classFile = classFile;
    this->generatePCT();
    std::cout<<"we doing it"<<std::endl;
}

template<typename T>
void CSchematic<T>::genereateScheme(){

}

template<typename T>
void CSchematic<T>::generateSizeMap(){

}

template<typename T>
std::map<std::type_info,  POINTER_CAST<T>(CSchematic<T>::*)(void*)> CSchematic<T>::getPct(){
    return this->pointerCastTable;
}

template<typename T>
void CSchematic<T>::generatePCT(){
    //std::pair<std::type_info, FP>(typeid(int), &CSchematic<T>::castInt);
    pointerCastTable[typeid(int)] = &CSchematic<T>::castInt;
    pointerCastTable[typeid(double)] = &CSchematic<T>::castDouble;
    pointerCastTable[typeid(float)] = &CSchematic<T>::castFloat;
    pointerCastTable[typeid(char)] = &CSchematic<T>::castChar;
    pointerCastTable[typeid(std::string)] = &CSchematic<T>::castString;
    pointerCastTable[typeid(T)] = &CSchematic<T>::castObj;
}

template<typename T>
POINTER_CAST<T> castInt(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.intP = static_cast<int*>(location);
    return pointerCast;
}

template<typename T>
POINTER_CAST<T> castDouble(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.dubP = static_cast<double*>(location);
    return pointerCast;
}

template<typename T>
POINTER_CAST<T> castFloat(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.floP = static_cast<float*>(location);
    return pointerCast;
}

template<typename T>
POINTER_CAST<T> castChar(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.chrP = static_cast<char*>(location);
    return pointerCast;
}

template<typename T>
POINTER_CAST<T> castString(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.chrP = static_cast<std::string*>(location);
    return pointerCast;
}

template<typename T>
POINTER_CAST<T> castObj(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.chrP = static_cast<T*>(location);
    return pointerCast;
}