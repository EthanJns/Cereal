#include<iostream>
#include<stdlib.h>
#include "../main/CSchematic.h"

using namespace std;

struct test{
    int x;
};

int main(){
    
    CSchematic<test> scheme(1);
    
    scheme.testData();

    return 0;
}