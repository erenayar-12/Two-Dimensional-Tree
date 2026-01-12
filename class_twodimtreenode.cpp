#include "class_twodimtreenode.h"

TwoDimTreeNode::TwoDimTreeNode(const Rectangle Extent)
    : Extent(Extent), Vertical(), Horizontal(), TopLeft(nullptr), TopRight(nullptr), BottomLeft(nullptr), BottomRight(nullptr){

    //Setting main coordinates
    vertical_coordinates = (Extent.Bottom + Extent.Top) / 2;
    horizontal_coordinates = (Extent.Right + Extent.Left) / 2;

    //Creating extents of children nodes
    Rectangle tlExtent(Extent.Top, Extent.Left, vertical_coordinates,  horizontal_coordinates);
    Rectangle trExtent(Extent.Top, horizontal_coordinates, vertical_coordinates,  Extent.Right );
    Rectangle blExtent(vertical_coordinates , Extent.Left, Extent.Bottom,  horizontal_coordinates);
    Rectangle brExtent(vertical_coordinates, horizontal_coordinates, Extent.Bottom,  Extent.Right );

    //Creating children nodes if they are large enough (if a length of any side of rectangle is 1 or smaller, that can't be a child node)
    if(tlExtent.Bottom - tlExtent.Top > 1 && tlExtent.Right - tlExtent.Left > 1) {
        TopLeft = new TwoDimTreeNode(tlExtent);
    }
    if(trExtent.Bottom - trExtent.Top > 1 && trExtent.Right - trExtent.Left > 1) {
        TopRight = new TwoDimTreeNode(trExtent);
    }
    if(blExtent.Bottom - blExtent.Top > 1 && blExtent.Right - blExtent.Left > 1) {
        BottomLeft = new TwoDimTreeNode(blExtent);
    }
    if(brExtent.Bottom - brExtent.Top > 1 && brExtent.Right - brExtent.Left > 1) {
        BottomRight = new TwoDimTreeNode(brExtent);
    }
}

TwoDimTreeNode::TwoDimTreeNode( const TwoDimTreeNode & rhs )
    //calling rectangle constructor (Extent), LinkedList copy constructors (Vertical, Horizontal), copying integer values(vertical_coordinates, horizontal_coordinates)
    //initializing pointers to chidren with nullptr
    : Extent(rhs.Extent), Vertical(rhs.Vertical), Horizontal(rhs.Horizontal), vertical_coordinates(rhs.vertical_coordinates), horizontal_coordinates(rhs.horizontal_coordinates),
    TopLeft(nullptr), TopRight(nullptr), BottomLeft(nullptr), BottomRight(nullptr){

    //Recursively calling copy constructors of children nodes
    if (rhs.TopLeft != nullptr) {
        TopLeft = new TwoDimTreeNode(* rhs.TopLeft);
    }
    else {
        TopLeft = nullptr;
    }
    if (rhs.TopRight != nullptr) {
        TopRight = new TwoDimTreeNode(*rhs.TopRight);
    }
    else {
        TopRight = nullptr;
    }
    if (rhs.BottomLeft != nullptr) {
        BottomLeft = new TwoDimTreeNode(*rhs.BottomLeft);
    }
    else {
        BottomLeft = nullptr;
    }
    if (rhs.BottomRight != nullptr) {
        BottomRight = new TwoDimTreeNode(*rhs.BottomRight);
    }
    else {
        BottomRight = nullptr;
    }
}

TwoDimTreeNode::~TwoDimTreeNode() {
    //by deleting children nodes, we recursively call their destructors
    delete TopLeft;
    delete TopRight;
    delete BottomLeft;
    delete BottomRight;
}

bool TwoDimTreeNode::IsHorizontal(TwoDimTreeNode * root, Rectangle input_rectangle) {
    if(root->vertical_coordinates > input_rectangle.Top && root->vertical_coordinates < input_rectangle.Bottom) {
        return true;
    }
    return false;
}
bool TwoDimTreeNode::IsVertical(TwoDimTreeNode * root, Rectangle input_rectangle) {
    if(root->horizontal_coordinates > input_rectangle.Left && root->horizontal_coordinates < input_rectangle.Right) {
        return true;
    }
    return false;
}

TwoDimTreeNode* TwoDimTreeNode::getTopLeftChild() {
    return TopLeft ;
}
TwoDimTreeNode* TwoDimTreeNode::getTopRightChild() {
    return TopRight ;
}
TwoDimTreeNode* TwoDimTreeNode::getBottomLeftChild() {
    return BottomLeft ;
}
TwoDimTreeNode* TwoDimTreeNode::getBottomRightChild() {
    return BottomRight ;
}
Rectangle TwoDimTreeNode::getExtent() {
    return Extent ;
}
const LinkedList<Rectangle>& TwoDimTreeNode::getVertical() const {
    return Vertical;
}
const LinkedList<Rectangle>& TwoDimTreeNode::getHorizontal() const{
    return Horizontal;
}
int TwoDimTreeNode::getHorizontalCoordinate() {
    return horizontal_coordinates;
}

int TwoDimTreeNode::getVerticalCoordinate() {
    return vertical_coordinates;
}

void TwoDimTreeNode::addVertical(Rectangle rect) {
    //using insert method of LinkedList class to insert Rectangle object to a list.
    Vertical.insert(rect);
}
void TwoDimTreeNode::addHorizontal(Rectangle rect) {
    //inserting to horizontal LinkedList with same method
    Horizontal.insert(rect);
}
