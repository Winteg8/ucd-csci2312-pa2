//
//  Cluster.cpp
//  csci2312-pa2
//
//  Created by Maxim Anaya on 3/2/16.
//  Copyright © 2016 Maxim Anaya. All rights reserved.
//

#include <stdio.h>

#include "Point.h"
#include "Cluster.h"

using namespace Clustering;

LNode::LNode(const Point &p, LNodePtr n)
{
    point = p;
    next = n;
}

Cluster::Cluster()
{
    __size = 0;
    Point p;
    LNodePtr ptr;
    __points = new LNode(p, ptr);
}

Cluster & Cluster::operator=(const Cluster & equate)
{
    LNodePtr ptr1 = __points, ptr2 = equate.__points;
    do
    {
        ptr1->point = ptr2->point;
        
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    while(ptr1->next != nullptr);
        
    return *this;
}

Cluster::~Cluster()
{
    LNodePtr cursor = __points, previous = nullptr;
    while (cursor->next != nullptr)
    {
        delete previous->next;
        previous = cursor;
        cursor = cursor->next;
    }
    delete cursor;
    delete []__points;
    delete this;
}

int Cluster::getSize() const
{
    return __size;
}

void Cluster::add(const Point & p)
{
    LNodePtr cursor = __points;
    while (cursor->next != nullptr)
    {
        cursor = cursor->next;
    }
    
    cursor->next = new LNode(p, nullptr);
    __size++;
}


const Point & Cluster::remove(const Point & p)
{
    LNodePtr cursor = __points, previous = nullptr;
    while (cursor->next != nullptr)
    {
        if (p == cursor->point)
        {
            previous->next = cursor->next;
            __size--;
            return cursor->point;
        }
        else
        {
            previous = cursor;
            cursor = cursor->next;
        }
    }
    
    return p;
}


bool Cluster::contains(const Point & p)
{
    LNodePtr cursor = __points;
    while (cursor->next != nullptr)
    {
        if (p == cursor->point)
            return true;
        else
            cursor = cursor->next;
    }
    
    return false;
}

const Point & Cluster::operator[](unsigned int index) const
{
    LNodePtr cursor = __points;
    int i;
    while (cursor->next != nullptr && i < index)
    {
        cursor = cursor->next;
        i++;
    }
    
    return cursor->point;
}

Cluster & Cluster::operator+=(const Point & p)
{
    this->add(p);
    return *this;
}

Cluster & Cluster::operator-=(const Point & p)
{
    this->remove(p);
    return *this;
}

Cluster & Cluster::operator+=(const Cluster & c)
{
    LNodePtr cursor = c.__points;
    while (cursor->next != nullptr)
    {
        this->add(c.__points->point);
        __size++;
        cursor = cursor->next;
    }
    return *this;
}

Cluster & Cluster::operator-=(const Cluster & c)
{
    LNodePtr cursor = c.__points;
    while (cursor->next != nullptr)
    {
        this->remove(c.__points->point);
        
        // CHECK THIS LATER CUZ THIS WON'T WORK IN ALL SCENARIOS
        __size--;
        cursor = cursor->next;
    }
    return *this;
}


//Friends

std::ostream & Clustering::operator<<(std::ostream & stream, const Cluster & c)
{
    
    LNodePtr cursor = c.__points;
    while (cursor->next != nullptr)
    {
        stream << c.__points->point;
        cursor = cursor->next;
    }
    
    return stream;
}

std::istream & Clustering::operator>>(std::istream & stream, Cluster & c)
{
    LNodePtr cursor = c.__points;
    while (cursor->next != nullptr)
    {
        stream >> c.__points->point;
        cursor = cursor->next;
    }
    
    return stream;
}

bool Clustering::operator==(const Cluster & c1, const Cluster & c2)
{
    LNodePtr cursor1 = c1.__points, cursor2 = c2.__points;
    while (cursor1->next != nullptr)
    {
        if (cursor1->point != cursor2->point)
            return false;
        cursor1 = cursor1->next;
        cursor2 = cursor2->next;
        
    }
    return true;
}

bool Clustering::operator!=(const Cluster & c1, const Cluster & c2)
{
    if (c1 == c2)
        return false;
    else
        return true;
}

// Friends: Arithmetic (Cluster and Point)
const Cluster operator+(const Cluster & c, const Point & p)
{
    Cluster answer = c;
    answer += p;
    return answer;
}

const Cluster operator-(const Cluster & c, const Point & p)
{
    Cluster answer = c;
    answer -= p;
    return answer;
}

// Friends: Arithmetic (two Clusters)
const Cluster Clustering::operator+(const Cluster & c1, const Cluster & c2)
{
    Cluster answer = c1;
    answer += c2;
    return answer;
}

const Cluster Clustering::operator-(const Cluster & c1, const Cluster & c2)
{
    Cluster answer = c1;
    answer -= c2;
    return answer;
}






