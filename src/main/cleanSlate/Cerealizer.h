#include"includes.h"

using namespace std;

#ifndef CEREALIZER_H
#define CEREALIZER_H

//CSchematic Goes here
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
    void test(){cout<<2<<endl;}
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
void CSchematic<T>::loadScheme(string path){cout<<"Loading Scheme\n";}

//Serilizer Goes Here
template<class T>
class Serializer{
private:

    std::ofstream objFile;
    CSchematic<T>* schematic;
    std::stack<CSchematic<T>> schematicStack;

public:
    Serializer<T>();
    void serialize(T &obj);
    void init(CSchematic<T>* scheme);
    void test(){cout<<"1"<<endl;}
};

template<class T>
void Serializer<T>::init(CSchematic<T>* schematic){
    this->schematic = schematic;    
}

//Deserializer Goes Here
template<class T>
class Deserializer{
private:
    CSchematic<T>* schematic;

public:
    Deserializer<T>();
    T deserialize(std::string filePath);
    void init(CSchematic<T>* schematic);

};

template<class T>
void Deserializer<T>::init(CSchematic<T>* schematic){
    this->schematic = schematic;    
}

//Cerealizer Goes Here
template<class T>
class Cerealizer{
    private:
        void* serializer;
        void* deserializer;
        void* schematic;
        Serializer<T>* serial;
        Deserializer<T>* deserial;
        CSchematic<T>* scheme;

    public:
        void testIng();
        Cerealizer(string pathToFile);
        ~Cerealizer();

};


template<class T>
Cerealizer<T>::Cerealizer(string pathToFile){

    //Instanciate in memory the CSchematic | Serializer | Deserializer
    cout<<"Allocating Memory"<<endl;
    this->serializer = malloc(sizeof(Serializer<T>));
    this->deserializer = malloc(sizeof(Deserializer<T>));
    this->schematic = malloc(sizeof(CSchematic<T>));
    this->scheme = (CSchematic<T>*) schematic;
    this->serial = (Serializer<T>*) serializer;
    this->deserial = (Deserializer<T>*) deserializer;

    //Load the schematic
    this-> scheme -> loadScheme(pathToFile);
    
    //Initialize Serializer and Deserializer with Scheme
    this -> serial -> init(this->scheme);
    this -> deserial -> init(this->scheme);
    
 }

 template<class T>
 Cerealizer<T>::~Cerealizer(){
     free(this->serial);
     free(this->deserial);
     free(this->scheme);
 }

 template<class T>
 void Cerealizer<T>::testIng(){
     cout<<"Does this work?\n";
 }

#endif