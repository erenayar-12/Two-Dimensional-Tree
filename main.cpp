#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "class_twodimtreenode.h"

using namespace std;

//function to insert rectangles that covers a given point(x,y) to a given list(list)
void RectangleInserter(int x, int y, TwoDimTreeNode* tree, LinkedList<Rectangle>*& list) {
    if(tree == nullptr) {
        return;
    }
    //Checks the horizontal list's objects (Rectangles) of the given node (tree) for a match
    LinkedList<Rectangle> templist = tree->getHorizontal();
    Node<Rectangle>* temp = templist.getHeader();
    while(temp != nullptr) {
        //IsInRectangle method from class_rectangle is used to check
        if(temp->data.isInRectangle(x, y)) {
            list->insert(temp->data);
        }
        temp = temp->next;
    }
    //Works as same with horizontal, but checks vertical list in the given node (tree)
    templist = tree->getVertical();
    temp = templist.getHeader();
    while(temp != nullptr) {
        if(temp->data.isInRectangle(x, y)) {
            list->insert(temp->data);
        }
        temp = temp->next;
    }
    //Checks if the point is on the vertical or horizontal lines. If so, doesn't check the children nodes
    if(x == tree->getHorizontalCoordinate() || y == tree->getVerticalCoordinate()) {
        return;
    }
    //After scanning the lists' of main node (tree), checks which quadrant covers the given point(x,y)
    if(x < tree->getHorizontalCoordinate() && y < tree->getVerticalCoordinate()) {
        //Recursive call for Top Left Child
        RectangleInserter(x, y, tree->getTopLeftChild(), list);
    }
    else if(x > tree->getHorizontalCoordinate() && y < tree->getVerticalCoordinate()) {
        //Recursive call for Top Right Child
        RectangleInserter(x, y, tree->getTopRightChild(), list);
    }
    else if(x < tree->getHorizontalCoordinate() && y > tree->getVerticalCoordinate()) {
        //Recursive call for Bottom Left Child
        RectangleInserter(x, y, tree->getBottomLeftChild(), list);
    }
    else if(x > tree->getHorizontalCoordinate() && y > tree->getVerticalCoordinate()) {
        //Recursive call for Bottom Right Child
        RectangleInserter(x, y, tree->getBottomRightChild(), list);
    }
}

//function to add Rectangles to the correct list
void RectangleClassifier(TwoDimTreeNode* treeptr, Rectangle input_rect) {
    if(treeptr == nullptr) {
        return;
    }
    //basically adds the rectangle to horizontal list if IsHorizontal method from TwoDimTreeNode class returns true
    if(treeptr->IsHorizontal(treeptr, input_rect)) {
        treeptr->addHorizontal(input_rect);
        return;  //If we put rectangle to a list, we exit from the function in order not to add same rectangle to a different list
    }
    //Does same for vertical list
    if(treeptr->IsVertical(treeptr, input_rect)) {
        treeptr->addVertical(input_rect);
        return;
    }
    //If function did not return so far, that means we couldn't put rectangle in a suitable list.
    //According to coordinates of rectangle, we recursively do same for suitable child node.
    if(input_rect.getBottom() < treeptr->getVerticalCoordinate() && input_rect.getRight() < treeptr->getHorizontalCoordinate()){
        RectangleClassifier(treeptr->getTopLeftChild(), input_rect);
    }
    else if(input_rect.getBottom() < treeptr->getVerticalCoordinate() && input_rect.getLeft() >= treeptr->getHorizontalCoordinate()){
        RectangleClassifier(treeptr->getTopRightChild(), input_rect);
    }
    else if(input_rect.getTop() >= treeptr->getVerticalCoordinate() && input_rect.getRight() < treeptr->getHorizontalCoordinate()){
        RectangleClassifier(treeptr->getBottomLeftChild(), input_rect);
    }
    else if(input_rect.getTop() >= treeptr->getVerticalCoordinate() && input_rect.getLeft() >= treeptr->getHorizontalCoordinate()){
        RectangleClassifier(treeptr->getBottomRightChild(), input_rect);
    }
}


int main() {
    ifstream input;
    input.open("recdb.txt");
    if(!input.is_open()) {
        cout << "Error opening file" << endl;
    }
    string line;
    int checker = 0;
    /*
        Checker is used for checking input parts.
        0-> extent input, 1->rectangles input, 3->query input
        When we see a '-1' in input, we increment te checker (after taking extent we increment it without needing '-1')
    */
    TwoDimTreeNode* treeptr = nullptr;                                                   //initalizing the root of our tree
    while(getline(input, line)) {                                                        //For every line in input, we start a new loop
        if(checker == 0 && line.substr(0,2) != "-1") {                                   //unless we see a -1, this if block will work
            stringstream ss(line);                                                       //Since inputs will be ordered (top-bottom-left-right) we directly take the input with stringstream
            int extent_top, extent_left, extent_bottom, extent_right;
            ss >> extent_top >> extent_left >> extent_bottom >> extent_right;
            Rectangle extent(extent_top, extent_left, extent_bottom, extent_right);
            treeptr = new TwoDimTreeNode(extent);                                        //We created our tree
            checker = 1;                                                                 //since we took the extent, we can move to taking rectangle input
            continue;
        }
        if (checker == 1 && line.substr(0,2) != "-1") {                                  //unless we see a -1, this if block will work
            stringstream ss(line);                                                       //getting rectangles input with the same method
            int top_coord, left_coord, bottom_coord, right_coord;
            ss >> top_coord >> left_coord >> bottom_coord >> right_coord;
            Rectangle input_rectangle(top_coord, left_coord, bottom_coord, right_coord); //we created our rectangle object. It will be created for every rectangle input
            RectangleClassifier(treeptr, input_rectangle);                               //We call RectangleClassifier function in order to put every rectangle to suitable list
        }
        else if(checker == 1 && line.substr(0,2) == "-1") {
            checker = 2;                                                                 //while taking rectangle input, if we see '-1', we increment the checker to take query input.
        }
        else if(checker == 2 && line.substr(0,2) != "-1") {
            stringstream ss(line);                                                       //getting query input with same method
            int x_coord, y_coord;
            ss >> x_coord >> y_coord;
            LinkedList<Rectangle>* intersecting_rectangles = new LinkedList<Rectangle>;  //A list to store rectangles that covers the current query point(input)
            RectangleInserter(x_coord, y_coord, treeptr, intersecting_rectangles);       //We are calling our RectangleInserter function to insert suitable rectangles to the list we created
            cout<< x_coord << " " << y_coord << endl;                                    //printing coordinate of the query
            cout<< intersecting_rectangles->getSize() << endl;                           //printing the number of rectangles in the list
            if(intersecting_rectangles->getSize() != 0) {                                //if list is not empty, we print the rectangles in the list
                intersecting_rectangles->printList();
            }
            delete intersecting_rectangles;                                              //deleting the list we create to avoid issues
        }
        else if (checker == 2 && line.substr(0,2) == "-1") {                             //if we encounter -1 after query inputs, we exit from the loop
            break;
        }
    }
    delete treeptr;                                                                      //finally we delete our Two Dimensional Tree and exit the program.
}
