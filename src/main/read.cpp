#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;


int main(){


    ifstream ifile("MyClass_obj.dat", ios::in | ios::binary);

    int x;
    double d;
    float f;
    char c;
    size_t size;
    ifile.read((char*)&size, sizeof(size));
    ifile.read((char*)&x, sizeof(x));
    ifile.read((char*)&size, sizeof(size));
    ifile.read((char*)&d, sizeof(d));
    ifile.read((char*)&size, sizeof(size));
    ifile.read((char*)&f, sizeof(f));
    ifile.read((char*)&size, sizeof(size));
    ifile.read((char*)&c, sizeof(c));
    ifile.close();

    cout<<size<<endl;
    cout<<x<<endl;
    cout<<d<<endl;
    cout<<f<<endl;
    cout<<c<<endl;
    return 0;
}
