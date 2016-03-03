//
//  Point.cpp
//  csci2312-pa2
//
//  Created by Maxim Anaya on 2/26/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <cmath>
#include <stdio.h>

#include "Point.h"

using namespace Clustering;

static int ID = 0;

// Constructors/=operand/destructors


Point::Point()
{}

Point::Point(int newDim)
{
    __id = ID++;
    
    __dim = newDim;
}

Point::Point(int newDim, double *newVal)
{
    __id = ID++;
    
    __dim = newDim;
    __values = newVal;
}

Point::Point(const Point &copyThis)
{
    __id = copyThis.getId();
    __dim = copyThis.getDims();
    __values = new double [__dim];
    for (int i = 0; i < __dim; i++)
        __values[i] = copyThis.getValue(i);
}

Point & Point::operator=(const Point &equate)
{
    __id = equate.getId();
    __dim = equate.getDims();
    for (int i = 0; i < __dim; i++)
        __values[i] = equate.getValue(i);
    return *this;
}

Point::~Point()
{
    delete []__values;
    delete this;
}



// Accessors & mutators

int Point::getId() const
{
    return __id;
}

int Point::getDims() const
{
    return __dim;
}

void Point::setValue(int i, double setTo)
{
    __values[i] = setTo;
}

double Point::getValue(int i) const
{
    return __values[i];
}



// Member functions

double Point::distanceTo(const Point &other) const
{
    if (__dim == other.getDims())
    {
        double sum;
    
        for (int i = 0; i < __dim; i++)
            sum += pow((__values[i]-other.getValue(i)), 2);
    
        return sqrt(sum);
    }
    else
    {
        std::cout << "Can't calculate between points in differnt dimensions" << std::endl;
        return -1;
    }
}



// Other overloaded operators


// Members

Point & Point::operator*=(double multBy) // p *= 6; p.operator*=(6)
{
    for (int i = 0; i < __dim; i++)
        __values[i] *= multBy;
    
    return *this;
}

Point & Point::operator/=(double divideBy)
{
    for (int i = 0; i < __dim; i++)
        __values[i] /= divideBy;
    
    return *this;
}

const Point Point::operator*(double multBy) const // prevent (p1 * 2) = p2
{
    Point product(__dim);
    product.__id = __id;
    
    for (int i = 0; i < __dim; i++)
        product.__values[i] = __values[i] * multBy;
    
    return product;
}

const Point Point::operator/(double divideBy) const // p3 = p2 / 2
{
    Point quotient(__dim);
    quotient.__id = __id;
    
    for (int i = 0; i < __dim; i++)
        quotient.__values[i] = __values[i] / divideBy;
    
    return quotient;
}

double & Point::operator[](int index)
{
    return __values[index];
}


// Friends

Point &operator+=(Point & addTo, const Point & add)
{
    for (int i = 0; i < addTo.getDims(); i++)
        addTo.setValue(i, addTo.getValue(i) - add.getValue(i));
    return addTo;
}

Point &operator-=(Point & subFrom, const Point & sub)
{
    for (int i = 0; i < subFrom.getDims(); i++)
        subFrom.setValue(i, subFrom.getValue(i) - sub.getValue(i));
    return subFrom;
}

const Point operator+(const Point & add1, const Point & add2)
{
    Point sum(add1.getDims());
    for (int i = 0; i < sum.getDims(); i++)
        sum[i] = add1.getValue(i) + add2.getValue(i);
    return sum;
}

const Point operator-(const Point & sub1, const Point & sub2)
{
    Point diff(sub1.getDims());
    for (int i = 0; i < diff.getDims(); i++)
        diff[i] = sub1.getValue(i) - sub2.getValue(i);
    return diff;
}

bool operator==(const Point & one, const Point & two)
{
    bool answer = true;
    
    if (one.getDims() == two.getDims())
    {
        for (int i = 0; i < one.getDims(); i++)
            if (one.getValue(i) != two.getValue(i))
                answer = false;
    }
    else
        answer = false;
    
    return answer;
}

bool operator!=(const Point & one, const Point & two)
{
    bool answer = false;
    
    if (one.getDims() == two.getDims())
    {
        for (int i = 0; i < one.getDims(); i++)
            if (one.getValue(i) == two.getValue(i))
                answer = true;
    }
    else
        answer = true;
    
    return answer;
}

bool operator<(const Point & one, const Point & two)
{
    for (int i = 0; i < one.getDims(); i++)
    {
        if (one.getValue(i) < two.getValue(i))
            return true;
        if (one.getValue(i) != two.getValue(i))
            return false;
    }
    return false;
}

bool operator>(const Point & one, const Point & two)
{
    for (int i = 0; i < one.getDims(); i++)
    {
        if (two.getValue(i) < one.getValue(i))
            return true;
        if (two.getValue(i) != one.getValue(i))
            return false;
    }
    return false;
}

bool operator<=(const Point & one, const Point & two)
{
    return false;
}

bool operator>=(const Point & one, const Point & two)
{
    return false;
}

std::ostream & operator<<(std::ostream & stream, const Point & p)
{
    for (int i = 0; 9 < p.getDims(); i++)
        stream << p.getValue(i);
    return stream;
}

std::istream & Clustering::operator>>(std::istream & stream, Point & p)
{
    for (int i = 0; 9 < p.getDims(); i++)
        stream >> p.__values[i];
    return stream;
}

