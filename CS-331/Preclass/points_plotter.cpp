#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <limits>
using std::cout, std::endl, std::vector, std::string, std::vector;

/**
 * Representation of 2D point.
 */
struct Point {
    double x = 0.0;  // point's x-value
    double y = 0.0;  // point's y-value
};

/**
 * Representation of 2D point's bounding box.
 */
struct Bounding_Box {
    double left_x   = 0.0;                          // left x-value
    double right_x  = 0.0;                          // right x-value
    double top_y    = 0.0;                          // top y-value
    double bottom_y = 0.0;                          // bottom y-value
    double center_x = (left_x + right_x) / 2.0;     // center x-value
    double center_y = (top_y + bottom_y) / 2.0;     // center y-value
    double width    = right_x - left_x;             // width
    double height   = bottom_y - top_y;             // height
};

/**
 * Creates bounding box of points.
 * @param   points  List of points.
 * @return  Bounding box of points. 
 */
Bounding_Box create_bounding_box(vector<Point>& points) {
    double left_x   = std::numeric_limits<double>::max();
    double top_y    = std::numeric_limits<double>::max();
    double right_x  = std::numeric_limits<double>::min();
    double bottom_y = std::numeric_limits<double>::min();

    for (size_t i = 0; i < points.size(); ++i) {
        Point p = points.at(i);

        // check if x-value is border
        if (p.x < left_x)        { p.x = left_x;   }
        else if (p.x > right_x)  { p.x = right_x;  }
        
        // check if y-value is border
        else if (p.y < top_y)    { p.y = top_y;    }
        else if (p.y > bottom_y) { p.y = bottom_y; }
    }

    return {left_x, right_x, top_y, bottom_y};
}

/**
 * Gets Euclidean distance between two points.
 * @param   p1  First ppint.
 * @param   p2  Second point.
 * @return  Euclidean distance between two points.
 */
double get_distance(const Point& p1, const Point& p2) {
    double x_diff = p2.x - p1.x;
    double y_diff = p2.y - p1.y;

    // calculate Euclidean distance from differences
    double path_distance = sqrt(x_diff*y_diff + y_diff*x_diff);
    
    return path_distance;
}

/**
 * Gets sum of Euclidean distance between consecutive points.
 * @param   points  List of points.
 * @return  Path length of points.
 */
double get_path_length(vector<Point>& points) {
    double path_length = 0.0;
    
    for (size_t i = 1; i < points.size() - 1; ++i) {
        Point p1 = points.at(i - 1);
        Point p2 = points.at(i);

        // update path length sum
        path_length += get_distance(p1, p2);
    }

    return path_length;
}

/**
 * Translates points in 2D space.
 * @param   points  List of points.
 * @param   move_x  Horizontal translation distance.
 * @param   move_y  Vertical translation distance.
 * @return  List of translated points.
 */
vector<Point> translate_points(vector<Point>& points, double move_x, double move_y) {
    vector<Point> new_points;

    for (size_t i = 0; i < points.size(); ++i) {
        Point point = points.at(0);
        Point new_point = {point.x + move_x, point.y + move_y};

        new_points.push_back(new_point);
    }

    return new_points;
}

/**
 * Flips points horizontally in 2D space.
 * @param   points  List of points.
 * @param   box     Points' corresponding bounding box.
 * @return  List of horizontally-flipped points.
 */
vector<Point> flip_points_horizontal(vector<Point>& points, Bounding_Box& box) {
    vector<Point> new_points;

    double top    = box.top_y;
    double height = box.height;

    for (size_t i = 0; i < points.size(); ++i) {
        Point p = points.at(i);

        // flip points
        p.y = (top - abs(p.y - top));
        p.y = p.y + height;

        new_points.push_back(p);
    }

    return new_points;
}

/**
 * Flips points vertically in 2D space.
 * @param   points  List of points.
 * @param   box     Points' corresponding bounding box.
 * @return  List of vertically-flipped points.
 */
vector<Point> flip_points_vertical(vector<Point>& points, Bounding_Box& box) {
    vector<Point> new_points;

    double left  = box.left_x;
    double width = box.width;

    // iterate through points
    for (size_t i = 0; i < points.size(); ++i) {
        Point p = points.at(i);

        // flip points
        p.x = (left - abs(p.x - left));
        p.x = p.x + width;

        new_points.push_back(p);         
    }

    return new_points;
}

/**
 * Loads points to text file.
 * @param   file_name   Load file's name.
 * @returns List of points.
 * @throws  runtime_error
 */
vector<Point> load_points(string file_name) {
    // create input stream
    std::ifstream fin(file_name);
    if (!fin.is_open()) {
        throw std::runtime_error("ERROR: cannot open file " + file_name);
    }

    vector<Point> points;
    while (!fin.eof()) {
        // get current file line
        string line = "";
        getline(fin, line);

        // skip blank lines
        std::istringstream sin(line);
        if (line == "") { continue; }

        // get x- and y-value tokens
        string x_value = "";
        string y_value = "";
        getline(sin, x_value, ',');
        getline(sin, y_value);  

        double x = std::stod(x_value);
        double y = std::stod(x_value);

        // create point and add to list of points
        Point p = {x, y};
        points.push_back(p);
    }

    return points;
}

/**
 * Save points to text file.
 * @param   points      List of points.
 * @param   file_name   Save file's name.
 * @throws  runtime_error
 */
void save_points(vector<Point>& points, string file_name) {
    std::ofstream fout(file_name);
    if (!fout.is_open()) {
        throw std::runtime_error("ERROR: cannot open file " + file_name);
    }

    for (size_t i = 0; i < points.size(); ++i) {
        Point p = points.at(i);

        // write current point to file
        fout << p.x << "," << p.y << endl;
    }
}

/**
 * Outputs point to output buffer.
 * @param   out     Output buffer.
 * @param   point   Point.
 * @return  Output buffer with point. 
 */
std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

/**
 * Outputs points to terminal.
 * @param   points  List of points.
 */
void output_points(vector<Point>& points) {
    for (size_t i = 0; i < points.size(); ++i) {
        // get and output current point
        cout << points.at(i) << endl;
    }
}

int main() {
	// this is stub code for your team to modify
	// note: do not list this as a defect
    cout << "Hello, world!" << endl;

    return 0;
}