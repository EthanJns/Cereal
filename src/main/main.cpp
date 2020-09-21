#include<iostream>
#include<stdlib.h>
#include"CSchematic.h"
#include<regex>
using namespace std;



int main(){
    CSchematic<long> schematic;
    schematic.testData();
    schematic.loadScheme("myclass.h");
    std::string str = "the is here";
    if(str.find(';') == string::npos){
        std::cout<<1234<<std::endl;
    }
    std::cout<<std::endl<<str.find(';')<<std::endl;

    regex r("( )*[a-z]+( )+[a-zA-Z0-9]+[,a-zA-Z0-9]*;$");
    std::string varI = " int x;";
    std::string nVar = "while(x ==1);";
    std::string func = "int func();";
    std::string vars = "int x,y,zdsfsd232,sassa;";
    if(std::regex_match(varI, r)){
        std::cout<<varI<<" Its a var?"<<std::endl;
    }
    if(std::regex_match(nVar, r)){
        std::cout<<nVar<<" Its a var?"<<std::endl;
    }
    if(std::regex_match(func, r)){
        std::cout<<func<<" Its a var?"<<std::endl;
    }
    if(std::regex_match(vars, r)){
        std::cout<<vars<<" Its a var?"<<std::endl;
    }

    return 0;
}