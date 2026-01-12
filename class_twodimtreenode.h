#ifndef CLASS_TWODIMTREENODE_H
#define  CLASS_TWODIMTREENODE_H
#include "class_linkedlist.h"


class TwoDimTreeNode {
public:
    explicit TwoDimTreeNode( Rectangle Extent);                             //constructor
    TwoDimTreeNode( const TwoDimTreeNode & rhs );                           //copy constructor
    ~TwoDimTreeNode();                                                      //destructor

    bool IsHorizontal(TwoDimTreeNode * root, Rectangle input_rectangle);    //method to check whether the given rectangle is coinciding with horizontal line
    bool IsVertical(TwoDimTreeNode * root, Rectangle input_rectangle);      //method to check whether the given rectangle is coinciding with vertical line

    TwoDimTreeNode* getTopLeftChild();                                      //method to return Top Left child
    TwoDimTreeNode* getTopRightChild();                                     //method to return Top Right child
    TwoDimTreeNode* getBottomLeftChild();                                   //method to return Bottom Left child
    TwoDimTreeNode* getBottomRightChild();                                  //method to return Bottom Right child
    Rectangle getExtent();                                                  //method to return extent of the tree
    const LinkedList<Rectangle>& getVertical() const;                       //method to return Vertical Linked List of the node
    const LinkedList<Rectangle>&  getHorizontal() const;                    //method to return Horizontal Linked List of the node
    int getVerticalCoordinate();                                            //method to return vertical coordinate of the node
    int getHorizontalCoordinate();                                          //method to return vertical coordinate of the node

    void addVertical(Rectangle rect);                                       //method to add given rectangle to the Vertical Linked List of the node
    void addHorizontal(Rectangle rect);                                     //method to add given rectangle to the Horizontal Linked List of the node


    friend class Rectangle;                                                 //declared Rectangle class as a friend class to access private members of TwoDimTreeNode class from Rectangle
private:
    Rectangle Extent;                                                       //Area that tree spans
    LinkedList<Rectangle> Vertical, Horizontal;                             //Linked Lists that hold rectangles coinciding with vertical/horizontal lines
    TwoDimTreeNode *TopLeft, *TopRight, *BottomLeft, *BottomRight;          //children of the node
    int vertical_coordinates, horizontal_coordinates;                       // origin is (horizontal_coordinates , vertical_coordinates)
};

#endif

