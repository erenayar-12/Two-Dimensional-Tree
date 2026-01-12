#include "class_rectangle.h"

Rectangle::Rectangle(const int _top, const int _left, const int _bottom, const int _right)
    : Top(_top), Left(_left), Bottom(_bottom), Right(_right) {} //initializing variables

ostream &operator<<( ostream &OS, const Rectangle& rect) {
    OS <<rect.Top << " " <<rect.Left << " " <<rect.Bottom << " " <<rect.Right << endl;
    return OS;
}

int Rectangle::getTop() const {
    return Top;
}
int Rectangle::getBottom() const{
    return Bottom;
}
int Rectangle::getLeft() const{
    return Left;
}
int Rectangle::getRight() const{
    return Right;
}

void Rectangle::setTop(const int _top) {
    Top = _top;
}
void Rectangle::setBottom(const int _bottom) {
    Bottom = _bottom;
}
void Rectangle::setLeft(const int _left) {
    Left = _left;
}
void Rectangle::setRight(const int _right) {
    Right = _right;
}

bool Rectangle::isInRectangle(const int x, const int y) {
    if ((x >= Left) && (x < Right) && (y >= Top) && (y < Bottom)) {
        return true;
    }
    return false;
}







