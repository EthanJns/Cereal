#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<map>
#include <typeindex>
#include <typeinfo>
#include<regex>
#include"POINTER_CAST.h"

template<class T>
class CSchematic{
    
private:

    typedef POINTER_CAST<T>(CSchematic<T>::*FP)(void*);       //Function pointer for class CSchematic that returns a POINTER_CAST, based on data types we know what to get from POINTER_CAST type
    std::vector<std::string> dataTypeOrder;             //Vector of data types inside the CLASS.H file, holds the order in which the data is
    std::map<std::string, size_t> dataTypeSize;         //Map of strings(DATA_TYPES) to their respective type sizes
    std::map<std::type_index, FP>  pointerCastTable;
    std::string classFile;

public:
    CSchematic<T>();
    void loadScheme(std::string filepath);
    bool isVariable(std::string line);
    void genereateScheme();
    void generateSizeMap();
    void generatePCT();
    void testData();
    std::map<std::type_info, FP> getPct();
    POINTER_CAST<T> castInt(void* location);
    POINTER_CAST<T> castDouble(void* location);
    POINTER_CAST<T> castFloat(void* location);
    POINTER_CAST<T> castChar(void* location);
    POINTER_CAST<T> castString(void* location);
    POINTER_CAST<T> castObj(void* location);

};

template <class T>
void CSchematic<T>::loadScheme(std::string filepath){
    std::ifstream inputFile(filepath, std::ios::in);
    if(inputFile){
        std::cout<<"Creating Scheme..."<<std::endl;
        std::string line;
        while(getline(inputFile, line)){
            std::cout<<line<<" ";
            if(isVariable(line)){
                std::cout<<" is a variable\n";
            }
        }
    }else{
        std::cout<<"Could not open file, please make sure the\nfile name or path to file was entered correctly"<<std::endl;
    }
}

template<class T>
CSchematic<T>::CSchematic(){
    generatePCT();
}

template<class T>
void CSchematic<T>::testData(){
    void* ptr;
    POINTER_CAST<T>pc = (*this.*pointerCastTable[typeid(int)])(ptr);
    std::cout<<"Should be a void pointer type: ";
    std::cout<<typeid(ptr).name()<<std::endl;
    std::cout<<"should now be an int pointer type: ";
    std::cout<<typeid(pc.intP).name()<<std::endl;
}




template<class T>
void CSchematic<T>::genereateScheme(){

}

template<class T>
void CSchematic<T>::generateSizeMap(){

}

template<class T>
std::map<std::type_info,  POINTER_CAST<T>(CSchematic<T>::*)(void*)> CSchematic<T>::getPct(){
    return this->pointerCastTable;
}

template<class T>
void CSchematic<T>::generatePCT(){
    
    //pointerCastTable[t] = &CSchematic<T>::castInt;
    //std::pair<std::type_info, FP>(typeid(int), &CSchematic<T>::castInt);
    pointerCastTable[typeid(int)] = &CSchematic<T>::castInt;
    pointerCastTable[typeid(double)] = &CSchematic<T>::castDouble;
    pointerCastTable[typeid(float)] = &CSchematic<T>::castFloat;
    pointerCastTable[typeid(char)] = &CSchematic<T>::castChar;
    pointerCastTable[typeid(std::string)] = &CSchematic<T>::castString;
    pointerCastTable[typeid(T)] = &CSchematic<T>::castObj;
}

template<class T>
POINTER_CAST<T> CSchematic<T>::castInt(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.intP = static_cast<int*>(location);
    return pointerCast;
}

template<class T>
POINTER_CAST<T> CSchematic<T>::castDouble(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.dubP = static_cast<double*>(location);
    return pointerCast;
}

template<class T>
POINTER_CAST<T> CSchematic<T>::castFloat(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.floP = static_cast<float*>(location);
    return pointerCast;
}

template<class T>
POINTER_CAST<T> CSchematic<T>::castChar(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.chrP = static_cast<char*>(location);
    return pointerCast;
}

template<class T>
POINTER_CAST<T> CSchematic<T>::castString(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.strP = static_cast<std::string*>(location);
    return pointerCast;
}

template<class T>
POINTER_CAST<T> CSchematic<T>::castObj(void* location){
    POINTER_CAST<T> pointerCast;
    pointerCast.objP = static_cast<T*>(location);
    return pointerCast;
}

template <class T>
bool CSchematic<T>::isVariable(std::string line){
    std::regex r("( )*[a-z]+( )+[a-zA-Z0-9]+[,a-zA-Z0-9]*;$");
    if(std::regex_match(line, r)){
        return true;
    }

    return false;
}