#ifndef MY_CLASS_H
#define MY_CLASS_H

class MyClass{
    private:
        int x;
        double d;
        float f;
        char c;

    public:
        void print(){
            std::cout<<x<<" "<<d<<" "<<" "<<f<<" "<<c<<std::endl;
        }


};

#endif