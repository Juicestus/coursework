# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Name:         Justus Languell
# Section:      201
# Assignment:   Lab 10
# Date:         22 Oct 2024
#
import itertools

def is_collinear(p1, p2, p3):
    """Check if three points are collinear using the slope formula."""
    (x1, y1), (x2, y2), (x3, y3) = p1, p2, p3
    return (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)

def is_valid_placement(points, new_point):
    """Check if adding new_point keeps all points non-collinear."""
    for p1, p2 in itertools.combinations(points, 2):
        if is_collinear(p1, p2, new_point):
            return False
    return True

def no_three_in_line(n):
    """Place the maximum number of points on an n x n grid without three in a line."""
    points = []
    # Start with the main diagonal to maximize distance between points
    for x in range(n):
        for y in range(n):
            new_point = (x, y)
            if is_valid_placement(points, new_point):
                points.append(new_point)
    return points
            