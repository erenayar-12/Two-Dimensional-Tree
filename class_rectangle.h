#ifndef CLASS_RECTANGLE_H
#define CLASS_RECTANGLE_H

#include <ostream>

template <typename T>   //since we are going to use LinkeList methods we need to partially declare class here
class LinkedList;

using namespace std;


class Rectangle {
public:
    Rectangle(const int _top, const int _left, const int _bottom, const int _right);   //constructor

    //get methods to access coordinates from main
    int getTop() const;
    int getBottom() const;
    int getLeft() const;
    int getRight() const;

    //set methods to declare the coordinates from main
    void setTop(const int _top);
    void setBottom(const int _bottom);
    void setLeft(const int _left);
    void setRight(const int _right);

    //check the rectangle whether it covers the given point
    bool isInRectangle(const int x, const int y);

    //operator overloading for << operator
    friend ostream &operator<<( ostream &OS, const Rectangle &rect);

    //declaring TwoDimTreeNode as friend because we need to access private members of Rectangle class from TwoDimTreeNode class
    friend class TwoDimTreeNode;
private:
    int Top;    // y coordinate of the upper edge
    int Left;   // x coordinate of the leftmost edge
    int Bottom; // y coordinate of the bottom edge
    int Right;  // x coordinate of the rightmost edge
};

#endif

