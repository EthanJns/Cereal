#include<iostream>
#include<stdlib.h>
#include<regex>
#include"myclass.h"
#include"Serializer.h"
using namespace std;



int main(){
    Serializer<MyClass> serializer;
    serializer.init("myclass.h");
    MyClass myObj(23219,1.2e23,3.92,'-', "proof of concepts are fairly wild, dont you think?");
    myObj.print_addr();
    //cout<<"String location: "<<&myObj.s<<endl;
    serializer.serialize(myObj);

    return 0;
}