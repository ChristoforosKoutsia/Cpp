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
#endif // GEOMETRY_H_INCLUDED
