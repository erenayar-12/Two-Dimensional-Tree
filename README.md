# Two-Dimensional-Tree

## Overview
#### This project implements a hierarchical spatial data structure to solve the Point Enclosure Problem. It takes a set of rectangular regions and organizes them into a tree structure to allow for efficient querying. Given a query point $(x, y)$, the system identifies every rectangle in the database that contains that point.The core data structure is a Two-Dimensional Tree (similar to a Region Quadtree), which recursively divides the 2D plane into four quadrants (Top-Left, Top-Right, Bottom-Left, Bottom-Right).

## Key Features
#### Hierarchical Space Decomposition: Recursively splits the 2D space based on the center coordinates of the current region.Boundary Handling: Uniquely handles rectangles that straddle the division lines by storing them in specialized Vertical and Horizontal linked lists at the intersecting node, rather than pushing them down to children.Recursive Querying: Efficiently traverses the tree to find all rectangles overlapping a specific coordinate $(x, y)$.Custom Linked List: Implements a custom templated LinkedList class for memory-efficient storage of rectangle objects.File-Based I/O: automated input parsing from a text file for tree construction and batched querying.

## How It Works
#### Tree Construction: The system reads the "extent" (total bounds) of the world and initializes the root.Rectangle Insertion (RectangleClassifier):Rectangles are read from the input.If a rectangle intersects the node's vertical center line, it is stored in the node's Vertical List.If it intersects the horizontal center line, it is stored in the Horizontal List.If it fits entirely within a quadrant, it is passed down recursively to the TopLeft, TopRight, BottomLeft, or BottomRight child.Querying (RectangleInserter):For a query point $(x, y)$, the search starts at the root.It checks the current node's Vertical and Horizontal lists for matches.It then determines which quadrant the point lies in and recurses only into that child node, pruning the search space significantly.

## Input Format (recdb.txt)

#### The program expects an input file named recdb.txt structured in three sections separated by -1:World Extent: Top Left Bottom Right (Defines the root bounds).Rectangles: List of rectangles to insert (Top Left Bottom Right).Separator: -1Queries: List of points to query (x y).Terminator: -1
