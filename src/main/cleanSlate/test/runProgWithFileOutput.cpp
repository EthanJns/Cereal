#include <iostream>
#include <fstream>
#include <stdio.h>      
#include <stdlib.h> 
using namespace std;

int main(){
    string test = "itworks";
    //So what needs to happen is this needs to be hardcoded and uniform
    system("g++ runThis.cpp -o itworks");
    system("./itworks myOtherTest bootyHoleBoi");
    fstream myFile;
    string name = "myOtherTest";
    myFile.open(name.c_str(), ios::in);
    string testVar;
    getline(myFile, testVar);
    cout<<"TestVar: "<<testVar<<endl;

    return 0;
}