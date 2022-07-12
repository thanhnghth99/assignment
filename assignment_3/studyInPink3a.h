/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x=0, int y=0);
    string toString() const;

    int distanceTo(const Point & otherPoint) const;
};

Point :: Point(int x, int y) : x(x), y(y){}

string Point :: toString() const{
    string result;
    result = "<Point[" + to_string(x) + "," + to_string(y) + "]>";
    return result;
}

int Point :: distanceTo(const Point & otherPoint) const{
    int d = 0;
    int xDiff = x - otherPoint.x;
    int yDiff = y - otherPoint.y;

    d = ceil(sqrt(pow(xDiff, 2) + pow(yDiff, 2)));

    return d;
}

class Node {
private:
    Point point;
    Node * next;

    friend class Path;

public:
    Node(const Point & point=Point(), Node * next=NULL);
    string toString() const;
};

Node :: Node(const Point & point, Node * next){
    this -> point = point;
    this -> next = next;
}

string Node :: toString() const{
    string result;
    result = "<Node[" + point.toString() + "]>";
    return result;
}

class Path {
private:
    Node * head;
    Node * tail;
    int count = 0;
    int length = -1;

public:
    // Path();
    // ~Path();

    void addPoint(int x, int y);
    string toString() const;
    Point getLastPoint() const;
    int len() const;
};

void Path :: addPoint(int x, int y){
    if (count == 0){
        Node *ptr = new Node(Point(x,y));
        head = ptr;
        tail = ptr;
        count++;
        length = 0;
    }
    else{
        Node *ptr = new Node(Point(x,y));
        Point ptr_m =  tail -> point;
        Point ptr_n = ptr -> point;
        length += ptr_m.distanceTo(ptr_n);
        tail -> next = ptr;
        tail = ptr;
        count++;
    }
}

string Path :: toString() const{
    string result;
    result = "<Path[count:" + to_string(count) + ",length:" + to_string(length) + ",[" ;
    Node *temp = new Node;
    temp = head;
    for (int i = 0; i < count; i++){
        result += temp -> toString();
        temp = temp -> next;
        if(count >= 2 && i <= count - 2)
            result += ",";
    }
    result += "]]>";
    return result;
}

Point Path :: getLastPoint() const{
    Point ptr = Point();
    ptr = tail -> point;
    return ptr;
}

int Path :: len() const{
    return length;
}

class Character {
private:
    string name;

public:
    Path path;
    Character(const string & name="");
    // ~Character();

    string getName() const;
    void setName(const string & name);

    void moveToPoint(int x, int y);
    string toString() const;

    int len() const;
};

Character :: Character(const string & name){
    this -> name = name;
}

string Character :: getName() const{
    return name;
}

void Character :: setName(const string & name){
    this -> name = name;
}

void Character :: moveToPoint(int x, int y){
    path.addPoint(x,y);
}

string Character :: toString() const{
    string result;
    result = "<Character[name:" + name + ",path:" + path.toString() + "]>";
    return result;
}

int Character :: len() const{
    return path.len();
}

bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ) {
            int l1 = chWatson.len();
            int l2 = chMurderer.len();
            if (l1 - l2 <= maxLength){
                outDistance = (chWatson.path.getLastPoint()).distanceTo(chMurderer.path.getLastPoint());
                if (outDistance > maxDistance)
                    return false;
            }
            else{
                outDistance = -1;
                return false;
            }

    return true;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */