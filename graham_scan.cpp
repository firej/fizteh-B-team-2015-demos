#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#define SIGN(x) (((x) >= 0) ? (1) : (-1))
#define MSQR(x) ((x)*(x))

class Point {
public:
	double x, y;
	Point(){}
	Point(double px, double py) : x(px), y(py) {}
	double operator* (Point p2) {
		return this->x * p2.y - this->y * p2.x;
	}
	double abs() {
		return sqrt(MSQR(this->x) + MSQR(this->y));
	}
	double abs(Point p2) {
		return sqrt(MSQR(p2.x - this->x) + MSQR(p2.y - this->y));
	}
	bool operator == (Point p2) {
		return this->x == p2.x && this->y == p2.y;
	}

	double operator ^ (Point p2) {
		return this->x*p2.x + this->y*p2.y;
	}
};

std::ostream& operator << (std::ostream& c, Point p) {
	return c << "[" << p.x << "," << p.y << "]";
}

class Comparer {
public:
	Point p;
	Comparer(Point p0): p(p0){}
	bool operator () (Point p1, Point p2) {
		if (p1 == p2) {
			return false;
		}
		std::cout << "Functor called  " << p1 << p2 << "  " << (p1^p) << (p1.abs()*p.abs()) << (p2^p) << (p2.abs()*p.abs()) << std::endl;
		return ((p1^p)/(p1.abs()*p.abs()) - (p2^p)/(p2.abs()*p.abs())) > 0;
	}
};


Point get_left_bottom(std::vector<Point> points) {
	Point min_point = points[0];
	for each(auto point in points) {
		if (point.y < min_point.y) {
			min_point = point;
		}
		else if (point.y == min_point.y) {
			if (point.x < min_point.x) {
				min_point = point;
			}
		}
	}
	return min_point;
}


int main() {
	std::vector<Point> points;
	std::vector<Point> scan;

	points.push_back(Point(5, 5));
	points.push_back(Point(4, 4));
	points.push_back(Point(4, 6));
	points.push_back(Point(0, 0));
	points.push_back(Point(0, 4));
	points.push_back(Point(2, 4));

	scan.push_back(get_left_bottom(points));
	Comparer c(scan[0]);

	std::cout << "P0:" << scan[0] << std::endl;

	std::sort(points.begin(), points.end(), c);

	for each (auto point in points) {
		std::cout << "X:" << point.x << " Y:" << point.y << std::endl;
	}

	return 0;
}
