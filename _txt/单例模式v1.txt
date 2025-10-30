#include <iostream>

using namespace std;

class Point
{
public:
    static Point & getInstance(){
        static Point pt(1,2);
        return pt;
    }
    
    void print() const{
        cout << "(" << this->_ix
            << "," << this->_iy
            << ")" << endl;
    }
    
private:
     Point(int x,int y)
    : _ix(x)
    , _iy(y)
    {
        cout << "Point(int,int)" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test0(){
    Point & pt = Point::getInstance();
    pt.print();

    Point & pt2 = Point::getInstance();
    pt2.print();

    cout << &pt << endl;
    cout << &pt2 << endl;
}

int main(){
    test0();
    return 0;
}