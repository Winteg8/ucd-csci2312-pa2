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

namespace Clustering
{
    // NODE STUFF
    LNode::LNode(const Point &p, LNodePtr n) : point(3)
    {
        point = p;
        next = n;
    }
    
    
    
    
    // CLUSTER STUFF
    Cluster::Cluster()
    {
        __size = 0;
        Point p(3);
        __points = nullptr;
    }
    
    Cluster::Cluster(const Cluster & copyThis)
    {
        __size = copyThis.__size;
        LNodePtr copyCursor = copyThis.__points;
        
        
        if (copyCursor != nullptr)
        {
            __points = new LNode(copyCursor->point, nullptr);
            copyCursor = copyCursor->next;
        }
            
        
        LNodePtr cursor = __points;
        while (copyCursor != nullptr)
        {
            cursor->next = new LNode(copyCursor->point, nullptr);
            
            cursor = cursor->next;
            copyCursor = copyCursor->next;
        }
        
        if (copyThis.__points == nullptr)
            __points = nullptr;
        
    }
    
    Cluster & Cluster::operator=(const Cluster & equate)
    {
        __size = equate.__size;
        
        LNodePtr ptr1 = __points, ptr2 = equate.__points;
        while (ptr1 != nullptr)
        {
            ptr1->point = ptr2->point;
            
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        
        return *this;
    }
    
    Cluster::~Cluster()
    {
        LNodePtr current = __points, following = nullptr;
        while (current != nullptr)
        {
            following = current->next;
            delete current->next;
            current = following;
        }
        delete current;
        delete __points;
    }
    
    int Cluster::getSize() const
    {
        return __size;
    }
    
    void Cluster::add(const Point & p)
    {
        __points = new LNode(p, __points);
        
        /*LNodePtr cursor = __points, previous = __points;
        
        while (cursor != nullptr)
        {
            previous = cursor;
            
            if (p >= cursor->point)
            {
                cursor->next = new LNode(p, cursor->next);
                break;
            }
            else if (p < __points->point)
            {
                __points = new LNode(p, __points->next);
                break;
            }
            else // iterate
                cursor = cursor->next;
                
        }
        
        if (__points == nullptr)
            __points = new LNode(p, nullptr);*/
        
        __size++;
    }
    
    
    const Point & Cluster::remove(const Point & p)
    {
        LNodePtr cursor = __points, previous = __points;
        while (cursor != nullptr)
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
        
        if (cursor->point == p)
            return true;
        
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
        LNodePtr cursor = __points, previous = __points;
        int i = 0;
        
        while ((cursor != nullptr) && (i < index))
        {
            previous = cursor;
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
        if (contains(p))
            remove(p);
        return *this;
    }
    
    Cluster & Cluster::operator+=(const Cluster & c)
    {
        LNodePtr cursor = c.__points;
        while (cursor != nullptr)
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
        while (cursor != nullptr)
        {
            if (contains(cursor->point))
                {
                    this->remove(c.__points->point);
                    __size--;
                }
            
            cursor = cursor->next;
        }
        return *this;
    }
    
    
    //Friends
    
    std::ostream & Clustering::operator<<(std::ostream & stream, const Cluster & c)
    {
        
        LNodePtr cursor = c.__points;
        while (cursor != nullptr)
        {
            stream << c.__points->point;
            cursor = cursor->next;
        }
        
        return stream;
    }
    
    std::istream & Clustering::operator>>(std::istream & stream, Cluster & c)
    {
        LNodePtr cursor = c.__points;
        while (cursor != nullptr)
        {
            stream >> c.__points->point;
            cursor = cursor->next;
        }
        
        return stream;
    }
    
    bool Clustering::operator==(const Cluster & c1, const Cluster & c2)
    {
        if (c1.__size == c2.__size)
        {
            LNodePtr ptr1 = c1.__points, ptr2 = c2.__points;
            
            while (ptr1 != nullptr && ptr2 != nullptr)
            {
                if (ptr1->point != ptr2->point)
                    return false;
                
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            
            return true;
        }
        return false;
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


}


