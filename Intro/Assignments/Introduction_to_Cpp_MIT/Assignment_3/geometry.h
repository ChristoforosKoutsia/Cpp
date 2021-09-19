#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
class Point{

private:
    int x,y;

public:
    Point(int u=0,int v=0):x(u),y(v){}
    int getX() const;
    int getY() const;
    void setX(const int new_x);
    void setY(const int new_y);
};

class PointArray{
private:
    Point *p;
    int length;
    void resize(int n);
public:
    //Implement default constructor:It should create an array with size 0.
    PointArray();
    PointArray(const Point points[], const int size);
    PointArray(const PointArray& pv);
    ~PointArray();
    void push_back(const Point &p);
    void insert(const int position, const Point &p);
    void remove(const int pos);
    const int getSize() const;
    void clear();
    Point* get(const int position);
    const Point* get(const int position) const;

};

class Polygon{
/* Protected access modifier is similar to that of private access modifiers, the difference is that the class member declared as
Protected are inaccessible outside the class but they can be accessed by any subclass(derived class) of that class.*/
protected:
    PointArray p_arr;
    /*the variables declared as static are initialized only once as they are allocated space in separate static storage so,
    the static variables in a class are shared by the objects. There can not be multiple copies of same static variables for
    different objects.Also because of this reason static variables can not be initialized using constructors.
    One instance of the variable across all instances of a class*/
    static int n;
public:
    Polygon(const Point arr[],const int length);
    Polygon(const PointArray p);
    ~Polygon();
    /*Sometimes implementation of all function cannot be provided in a base class because we don’t know the implementation.
Such a class is called abstract class.We cannot create objects of abstract classes.
A pure virtual function (or abstract function) in C++ is a virtual function for which we can have implementation,
But we must override that function in the derived class, otherwise the derived class will also
become abstract.A pure virtual function is declared by assigning 0 in declaration.*/
virtual double area() = 0;
static int getNumPolygons(){return n;}
int getNumSides();
const PointArray* getPoints() const;
};

class Rectangle: public Polygon{
public:
    Rectangle(const Point &x,const Point &y); //Pass by reference...we do not want to copy again objects
    Rectangle(const int a,const int b,const int c,const int d);
    virtual double area() const;

};
#endif // GEOMETRY_H_INCLUDED

