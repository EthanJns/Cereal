#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

int main(){
    string s;
    size_t size;
    char* str;
    void* vpt = &s;
    void* dp;
    ifstream inFile("../main/MyClass_Obj.dat", ios::in | ios::binary);
    inFile.read((char*)&size, sizeof(size_t));
    inFile.read((char*)dp, size);
    inFile.read((char*)&size, sizeof(size_t));
    inFile.read((char*)dp, size);
    inFile.read((char*)&size, sizeof(size_t));
    inFile.read((char*)dp, size);
    inFile.read((char*)&size, sizeof(size_t));
    inFile.read((char*)dp, size);
    inFile.read((char*)&size, sizeof(size_t));
    str = new char[size+1];
    inFile.read((char*)str, size);
    cout<<*str<<endl;

    cout<<vpt<<endl;
    
}