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
    std::map<std::string, FP>      pCastTable;
    std::map<std::string, int>     mapOfDataTypes;
    std::string classFile;

public:
    CSchematic<T>();
    
    void* iterate(int index, void* ptr);
    void loadScheme(std::string filepath);
    void loadSchemeMan();
    bool isVariable(std::string line);
    void genereateScheme();
    void generateSizeMap();
    void generatePCT();
    void testData();
    bool isDataType(std::string dataType);
    std::string ltrim(std::string&);
    std::string rtrim(std::string&);
    std::string  trim(std::string&);
    std::map<std::type_info, FP> getPct();
    POINTER_CAST<T> castInt(void* location);
    POINTER_CAST<T> castDouble(void* location);
    POINTER_CAST<T> castFloat(void* location);
    POINTER_CAST<T> castChar(void* location);
    POINTER_CAST<T> castString(void* location);
    POINTER_CAST<T> castObj(void* location);

    std::map<std::string, size_t> getDataTypeSizeMap();
    std::vector<std::string> getDataTypeOrder();

};




template<class T>
void* CSchematic<T>::iterate(int index, void* it){
    if(index == dataTypeOrder.size()-1){
        return it;
    }
    if(dataTypeOrder[index] == "double" || dataTypeOrder[index+1] == "double"){
        it = (void*)((int*)it+2);
    }
    else{
        it =(void*)((int*)it+1);
    }

    return it;
}

template<class T>
bool CSchematic<T>::isDataType(std::string dataType){
    std::regex objRegEx("( )*(obj)( )*[a-zA-Z0-9]+");
    if(mapOfDataTypes.find(dataType) == mapOfDataTypes.end()){
        if(std::regex_match(dataType, objRegEx)){
            return true;
        }
        return false;
    }
    return true;;
}
template<class T>
void CSchematic<T>::loadSchemeMan(){
    
    std::cout<<"You have opted to load the scheme manually, please enter in order, the data types\nof the variable stored in the class."
    <<"\nFor programmer made objects not apart of the STL please start the type with obj."
    <<"\ne.g."
    <<"\n\tint x ==> int"
    <<"\n\tvector<int> ==> vector<int>"
    <<"\n\tMyClass object0 ==> obj MyClass"
    <<"\nenter \"!f\" when finished:\n";

    std::string type = "";
    while(type!="!f"){
        std::cout<<"Please enter data type: ";
        getline(std::cin, type);
        if(type == "!f"){
            break;
        }
        if(!isDataType(type)){
            std::cout<<"The data type is not recognized, if its an obj, please put \"obj\" in front of of the class name."<<std::endl;
            continue;
        }
        dataTypeOrder.push_back(type);
    }

    std::cout<<std::endl<<"If you are loading manually due to loading scheme auto not working, please submit a request to the DBSL github\n"
    <<"Along with an example of your header class file so that I can work the regex expressions or logic to incorporate the style.\n"
    <<"If you would like, you may add to the parser function yourself and create a pull request\n";
}

template <class T>
void CSchematic<T>::loadScheme(std::string filepath){
    std::ifstream inputFile(filepath, std::ios::in);
    if(inputFile){
        //std::cout<<"Creating Scheme..."<<std::endl;
        std::string line;
        while(getline(inputFile, line)){
            trim(line);
            //std::cout<<line<<std::endl;
            if(isVariable(line)){
                std::string dataType = line.substr(0, line.find_first_of(" "));
                //std::cout<<dataType<<std::endl;;
                dataTypeOrder.push_back(dataType);
            }
        }
    }else{
        std::cout<<"Could not open file, please make sure the\nfile name or path to file was entered correctly"<<std::endl;
    }
    /*std::cout<<"Printing dataTypeOrder: "<<std::endl;
    for(int i = 0; i < dataTypeOrder.size(); i++){
        std::cout<<"["<<dataTypeOrder[i]<<"]";
    }std::cout<<std::endl;*/
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
    
    //Pointer Cast Table Initialization
    pointerCastTable[typeid(int)] = &CSchematic<T>::castInt; pointerCastTable[typeid(double)] = &CSchematic<T>::castDouble;
    pointerCastTable[typeid(float)] = &CSchematic<T>::castFloat; pointerCastTable[typeid(char)] = &CSchematic<T>::castChar;
    pointerCastTable[typeid(std::string)] = &CSchematic<T>::castString; pointerCastTable[typeid(T)] = &CSchematic<T>::castObj;

    //Data Type Map
    mapOfDataTypes["int"]=0; mapOfDataTypes["double"]=0; mapOfDataTypes["float"]=0; mapOfDataTypes["char"]=0; mapOfDataTypes["string"]=0;

    //P Cast Table Initialization to do, for deserializing
    //Data Size Map
    dataTypeSize["int"] = sizeof(int); dataTypeSize["double"] = sizeof(double); dataTypeSize["float"] = sizeof(float); dataTypeSize["char"] = sizeof(char);
    dataTypeSize["string"] = sizeof(std::string);

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
    std::regex r("( |\t)*[a-z]+(<[a-z]+>)*( |\t)+[a-zA-Z0-9]+[,a-zA-Z0-9]*;$");
    if(std::regex_match(line, r)){
        return true;
    }

    return false;
}

template <class T>
std::string CSchematic<T>::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

template<class T>
std::string CSchematic<T>::rtrim(std::string &s){
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

template<class T>
std::string CSchematic<T>::trim(std::string &s){
    ltrim(s);
    rtrim(s);
    return s;
}

template<class T>
std::map<std::string, size_t> CSchematic<T>::getDataTypeSizeMap(){
    return this->dataTypeSize;
}

template<class T>
std::vector<std::string> CSchematic<T>::getDataTypeOrder(){
    return this->dataTypeOrder;
}