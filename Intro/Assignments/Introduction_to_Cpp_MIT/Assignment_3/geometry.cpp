#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "geometry.h"
#include <iostream>
#include <math.h>
using namespace std;

int Point::getX() const {return x;}
int Point::getY() const {return y;}
void Point::setX(const int new_x) {x=new_x;}
void Point::setY(const int new_y) {y=new_y;}

//Constructors of PointArray
//Implement default constructor:It should create an array with size 0.
PointArray::PointArray()
{
    length=0;
    p=new Point[length];
}
/* Implement a constructor that takes a Point array called points and an int called size as its arguments.
   It should initialize a PointArray with the specified size, copying the values from points.
   You will need to dynamically allocate the PointArray’s internal array to the specified size.
*/
PointArray::PointArray(const Point points[], const int size)
    {
        length=size;
        p=new Point[length];
        for (int i=0;i<size;i++)
        {
            p[i]=points[i];
        }
    }
//Copy constructor
PointArray::PointArray(const PointArray& pv)
{
    length=pv.length;
    p=new Point[length];
        for (int i=0;i<length;i++)
        {
            p[i]=pv.p[i];
        }
    cout<<"Custom copy constructor has been called";
}

PointArray::~PointArray()
{
    delete [] p;
    cout<<"Freeing p...\n";
}

/*Since we will allow modifications to our array, you’ll find that the internal array grows and shrinks quite often.
A simple (though very inefficient) way to deal with this without repetitively writing similar code is to write a member function PointArray::resize(int n)
that allocates a new array of size n, copies the first min(previous array size,n) existing elements into it, and deallocates the old array.
If doing so has increased the size, it’s fine or resize to leave the new spaces uninitialized;
*/
void PointArray::resize(int n)
{
    int size=min(length,n);
    Point *new_arr=new Point[size];
    for (int i=0;i<size;i++)
    {
        new_arr[i]=p[i];
    }
    //Assignments
    length=size;
    delete [] p;
    p=new_arr;
}
void PointArray::push_back(const Point &new_point)
{
    //it is very important to call resize since we will put an extra element so our array should be increased otherwise
    //we will get an out of bounds error
    resize(length+1);
    p[length-1]=new_point;
}
void PointArray::insert(const int position, const Point &new_point)
{
    resize(length+1);
    for (int i=length-2;i>position;i--)
    {
        p[i+i]=p[i];
    }
    p[position]=new_point;
}

void PointArray::remove(const int pos)
{
    //Remove element from specific position and shift other elements to the right
    for (int i=pos;i<length-1;i++)
    {
        p[i]=p[i+i];
    }
    resize(length-1);
}

const int PointArray::getSize() const
{
    return length;
}

void PointArray::clear()
{
    resize(0);
}

Point *PointArray::get(const int position)
{
    Point *new_p=NULL;
    if (position>=length){return new_p;}
    else
    {
        new_p=(p+position);
        return new_p;
    }

}

const Point *PointArray::get(const int position) const
{
    return (p+position);
}

//class Polygon: implementation
Polygon::Polygon(const Point arr[],const int length):p_arr(arr,length)
{
    n++;
}
/*Implement a constructor that creates a polygon using the points in an existing PointArray that is passed as an argument.
(For the purposes of this problem, you may assume that the order of the points in the PointArray traces out a convex polygon.)
 You should make sure your constructor avoids the unnecessary work of copying the entire existing PointArray each time it is called.*/
Polygon::Polygon(const PointArray &p):p_arr(p)
{
    ++n;
}


int Polygon::getNumSides()
{
    return p_arr.getSize(); //We want the size of point array. Actually, represents the number of the sides of the polygon
}
const PointArray* Polygon:: getPoints ()const
{
    return &p_arr;
}
int Polygon::n;

/*
**********Implementation of Polygon*************************

Both of constructors should use member initializer syntax to call the base-class constructor,
and should have nothing else in their bodies. C++ unfortunately does not allow us to define arrays on the fly to pass
to base-class constructors. To allow using member initializer syntax, we can implement a little trick where we have a global array that
we update each time we want to make a new array of Points for constructing a Polygon. You may include the following code snippet in your
geometry.cpp file: */
Point constructorPoints[4];

Point *updateConstructorPoints( const Point &p1, const Point &p2, const Point &p3, const Point &p4 = Point(0,0)) {
constructorPoints[0] = p1;
constructorPoints[1] = p2;
constructorPoints[2] = p3;
constructorPoints[3] = p4;
return constructorPoints;
}
/*We want to create a rectangle using 4 points.That's could be implemented by creating 4 points using only the lower left
point and the upper right one. We will use the constructor of Point class for that purpose
*/
Rectangle::Rectangle(const Point &p1,const Point &p2):Polygon(updateConstructorPoints(p1,Point(p2.getX(),p1.getX()),
                                                                                      p2,Point(p1.getX(),p2.getY())),4){}

Rectangle::Rectangle(const int x1,const int x2, const int y1, const int y2):Polygon(updateConstructorPoints(Point(x1,y1),
                                                                                      Point(x2,y1),Point(x2,y2),Point(x1,y2)),4){}
double Rectangle::area()
{
    int length=p_arr.get(1)->getX()-p_arr.get(0)->getX();
    int width=p_arr.get(2)->getY()-p_arr.get(1)->getY();
    return abs((double)length*width);
}

/*Implementing Triangle class */
Triangle::Triangle(const Point &p1,const Point &p2,const Point &p3):Polygon(updateConstructorPoints(p1,p2,p3),3){}
double Triangle::area()
{
    //Calculate area using Heron's formula
    double a=sqrt(pow(p_arr.get(0)->getX()-p_arr.get(1)->getX(),2)+pow((p_arr.get(0)->getY()-p_arr.get(1)->getY()),2)); //base

    //It is well known from basic vector theory that distance between two arbitary points it is given by :d=sqrt(pow(x2-x1)+pow(y2-y1))
    double b=sqrt(pow(p_arr.get(2)->getX()-p_arr.get(1)->getX(),2)+pow((p_arr.get(2)->getY()-p_arr.get(1)->getY()),2));

    double c=sqrt(pow((p_arr.get(2)->getX()-p_arr.get(0)->getX()),2)+pow((p_arr.get(2)->getY()-p_arr.get(0)->getY()),2));

    double s=(a+b+c)/2;

    return ((double)sqrt(s*(s-a)*(s-b)*(s-c)));

}
void printAttributes(Polygon *poly)
{
    cout<<"The area of the polygon is : "<<poly->area()<<endl;
    cout<<"The points of the polygon are : \n";
    //Store in point array the points
    const PointArray *arr=poly->getPoints();
    for (int i=0;i<arr->getSize();i++)
    {
        cout<<"("<<arr->get(i)->getX()<< ", " << arr->get(i)->getY()<<")"<<endl;
    }

}

int main(int argc, char *argv[]) {
 cout << "Enter lower left and upper right coords of rectangle as four space separated integers: ";
int llx, lly, urx, ury;
cin >> llx >> lly >> urx >> ury;
Point ll(llx, lly), ur(urx, ury);
Rectangle r(ll, ur);
printAttributes(&r);
 cout << "Enter three coords of triangle as six space separated integers: ";
 int x1, y1, x2, y2, x3, y3;
 cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
Point a(x1, y1), b(x2, y2), c(x3, y3);
Triangle t(a, b, c);
printAttributes(&t);

return 0;
}

