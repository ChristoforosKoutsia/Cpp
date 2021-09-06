#include <stdio.h>
#include <stdlib.h>
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

int main()
{
Point *p=new Point[5];
Point u(7,3);

//Construct an array of Points
for (int i=0;i<5;i++)
{
    p[i].setX(i);
    p[i].setY(i+2);
}
PointArray p_arr(p,5);

}
