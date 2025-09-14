#include <iostream>
#include <cstring>

struct Point {
    int x, y;

    Point () : x(), y() {}
    Point (int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
    int vertices;
    Point** points;

public:
    Shape (int _vertices) {
        vertices = _vertices;
        points = new Point*[vertices+1];    // allocating the array of pointers...
        for (int i = 0; i <= vertices; i++)         
            points[i] = new Point();        //... but also need memory for each point object 
    }

    ~Shape () {
        // Must deallocated...
        for (int i = 0; i <= vertices; i++)
            delete points[i];           //... all the individual point memory locations
        delete[] points;        //... and the actual memory for the array of pointers
    }

    void addPoints(Point* pts) {    // accepting an array, assumes that the length is at least verticies
        for (int i = 0; i <= vertices; i++) {
            memcpy(points[i], &pts[i%vertices], sizeof(Point));
        }
    }

    double area () {        // changed return type b/c not returning a pointer anymore
        int temp = 0;
        for (int i = 0; i < vertices; i++) {
            // FIXME: there are two methods to access members of pointers
            //        use one to fix lhs and the other to fix rhs
            int lhs = points[i]->x * points[i+1]->y;                // uses arrow operator
            int rhs = (*points[i+1]).x * (*points[i]).y;            // and also deref + regular accessor (dot operator)
            temp += (lhs - rhs);
        }
        double area = abs(temp)/2.0;
        return area;                        // not returning the memory location of the area variable
                                            // because it is stored on the stack
    }
};

int main () {
    // FIXME: create the following points using the three different methods
    //        of defining structs:
    //          tri1 = (0, 0)
    //          tri2 = (1, 2)
    //          tri3 = (2, 0)
    Point tri1(0, 0);               // Calling the constructor
    Point tri2 = Point(1, 2);       // Using the copy/assignment constructor
    Point tri3;                     // Using the default constructor...
    tri3.x = 2;                     // ...and initializing the fields
    tri3.y = 0;                     // ...one by one

    // adding points to tri
    Point triPts[3] = {tri1, tri2, tri3};
    Shape* tri = new Shape(3);
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
    //          quad1 = (0, 0)
    //          quad2 = (0, 2)
    //          quad3 = (2, 2)
    //          quad4 = (2, 0)

    // adding points to quad
    Point quad1(0, 0);
    Point quad2 = Point(0, 2);
    Point quad3;
    quad3.x = 2;
    quad3.y = 2;
    Point quad4(2, 0);              // Reusing the basic compiler b/c of 4 points

    Point quadPts[4] = {quad1, quad2, quad3, quad4};
    Shape* quad = new Shape(4);
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    std::cout << "Area of triangle = " << tri->area() << "\n";
    std::cout << "Area of quadrilateral = " << quad->area() << "\n";

    delete tri;         // deallocate shape objects on the heap
    delete quad;

}
