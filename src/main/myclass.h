#include<vector>
#ifndef MY_CLASS_H
#define MY_CLASS_H

using namespace std;
class MyClass{
    public:
        int     x;
        double  d;
        float   f;
        char    c;
        string  s;

        MyClass(){}
        MyClass(int x, double d, float f, char c, string s){
            this->x = x;
            this->d = d;
            this->f = f;
            this->c = c;
            this->s = s;
        }
        void print(){
            std::cout<<x<<" "<<d<<" "<<" "<<f<<" "<<c<<" "<<s<<std::endl;
            //std::cout<<xx<</*" "<<other<<*/std::endl;
        }
        void print_addr(){
            cout<<"x: "<<&x<<endl;
            cout<<"d: "<<&d<<endl;
            cout<<"f: "<<&f<<endl;
            cout<<"c: "<<&c<<endl;
            cout<<"s: "<<&s<<endl;
            //cout<<"xx: "<<&xx<<endl;
        }


};

#endif