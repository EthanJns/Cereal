#include<iostream>
#include<fstream>

using namespace std;

int main(){
    int i;
    double d;
    float f;
    char c;
    string s;
    void* sp = &s;
    size_t st;
    ifstream inFile("MyClass_obj.dat", ios::in | ios::binary);

    inFile.read((char*)&st, sizeof(size_t));
    inFile.read((char*)&i, st);

    inFile.read((char*)&st, sizeof(size_t));
    inFile.read((char*)&d, st);

    inFile.read((char*)&st, sizeof(size_t));
    inFile.read((char*)&f, st);

    inFile.read((char*)&st, sizeof(size_t));
    inFile.read((char*)&c, st);

    inFile.read((char*)&st, sizeof(size_t));
    char* sc = new char[st];
    inFile.read((char*)sc, st);
    cout<<i<<" "<<d<<" "<<f<<" "<<" "<<c<<" "<<st<<endl;
    cout<<st<<endl;
    cout<<sc<<endl;
    
    *(string*)sp = sc;
    cout<<s<<endl;

}