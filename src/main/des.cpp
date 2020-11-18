#include<iostream>
#include<stdlib.h>
//#include"CSchematic.h"
#include<regex>
#include"myclass.h"
#include"Deserializer.h"
using namespace std;

int main(){
    Deserializer<MyClass> deserial;
    deserial.init("myclass.h");
    MyClass myObj = deserial.deserialize("MyClass_obj.dat");
    myObj.print();
    return 0;
}
