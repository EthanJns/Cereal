#include <iostream>
#include <fstream>

using namespace std;

int main(int arg, char* argv[]){
    fstream f;
    string fileName(argv[1]);
    string pushToFile(argv[2]);
    f.open(fileName.c_str(), ios::out);
    f<<pushToFile<<endl;
    for(int i = 0; i < 1000000000; i++){}
    f.close();

    return 0;
}