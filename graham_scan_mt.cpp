#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "gl/glut.h"
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

#pragma comment(lib, "glut32.lib")

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

double vector_product(Point p1, Point p2, Point p3) {
	std::cout << p1 << p2 << p3 << (p2.x - p1.x)*(p3.y - p2.y) - (p2.y - p1.y)*(p3.x - p2.x) << std::endl;
	return (p2.x - p1.x)*(p3.y - p2.y) - (p2.y - p1.y)*(p3.x - p2.x);
}

class Comparer {
public:
	Point p;
	Comparer(Point p0) : p(p0){}
	bool operator () (Point p1, Point p2) {
		if (p1 == p2) {
			return false;
		}
		double ang1 = asin((p1.y - p.y) / p.abs(p1));
		double ang2 = asin((p2.y - p.y) / p.abs(p2));
		std::cout << "Functor called  " << p1 << p2 << "  " << ang1 << " " << ang2 << std::endl;
		if (ang1 != ang2) {
			return ang1 < ang2;
		}
		else {
			return p.abs(p1) < p.abs(p2);
		}
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

int foo(float bar) {
	return 0;
}

std::vector<Point> points;
std::vector<Point> src_points;
std::vector<Point> sorted_points;
HANDLE hMutex;
std::vector<Point> scan;
Point p1, p2;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 10.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(10.0f, 0.0f);
	glEnd();

	glPointSize(10.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	WaitForSingleObject(hMutex, INFINITE);
	for each (auto point in src_points) {
		//std::cout << "X:" << point.x << " Y:" << point.y << std::endl;
		glVertex2f(point.x, point.y);
	}
	ReleaseMutex(hMutex);
	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	WaitForSingleObject(hMutex, INFINITE);
	for each (auto point in sorted_points) {
		//std::cout << "X:" << point.x << " Y:" << point.y << std::endl;
		glVertex2f(point.x, point.y);
	}
	ReleaseMutex(hMutex);
	glEnd();



	glPointSize(5.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for each (auto point in scan) {
		//std::cout << "X:" << point.x << " Y:" << point.y << std::endl;
		glVertex2f(point.x, point.y);
	}
	if (scan.size() > 0) {
		glVertex2f(scan[0].x, scan[0].y);
	}
	glEnd();

	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();

	glFlush();
}

void Initialize() {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 10.0, -1.0, 10.0, -5.0, 5.0);\
}

#define RANDOM(min,max) (rand()*(max-min)/RAND_MAX + min)

DWORD WINAPI myThread(LPVOID lpParam) {
	srand(time(NULL));
	for (int i = 0; i < 30; i++){
		WaitForSingleObject(hMutex, INFINITE);
		src_points.push_back(Point(RANDOM(0, 9), RANDOM(0, 9)));
		ReleaseMutex(hMutex);
		Sleep(100);
	}

	points = src_points;

	int start_length = points.size();
	Point p0 = get_left_bottom(points);
	scan.push_back(p0);

	for (std::vector<Point>::iterator i = points.begin(); i < points.end(); i++) {
		Sleep(100);
		if (*i == p0) {
			points.erase(i);
			break;
		}
	}

	Comparer c(scan[0]);
	std::sort(points.begin(), points.end(), c);

	for (auto point: points) {
		WaitForSingleObject(hMutex, INFINITE);
		sorted_points.push_back(point);
		ReleaseMutex(hMutex);
		Sleep(300);
	}

	scan.push_back(points[0]);
	points.erase(points.begin());

	for (; points.size();) {
		Sleep(200);
		while (vector_product(*(++scan.rbegin()), *(scan.rbegin()), points[0]) < 0) {
			scan.pop_back();
		}
		scan.push_back(points[0]);
		points.erase(points.begin());
	}

	for each (auto point in points) {
		std::cout << "X:" << point.x << " Y:" << point.y << std::endl;
	}

	double max_distance = 0;
	for (unsigned int i = 0; i < scan.size(); i++) {
		Sleep(500);
		for (unsigned int j = i + 1; j < scan.size(); j++) {
			if (scan[i].abs(scan[j]) > max_distance) {
				max_distance = scan[i].abs(scan[j]);
				p1 = scan[i];
				p2 = scan[j];
			}
		}
	}
	return 0;
}

void mytimerevent(int t) {
	glutPostRedisplay();
	glutTimerFunc(10, mytimerevent, 1);
}

int main(int argc, char** argv){
	srand(time(NULL));
	hMutex = CreateMutex(NULL, FALSE, NULL);
	char *array = new char[1024];
	strcpy(array, "Some string data!");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);
	Initialize();

	//myThread(0);
	CreateThread(NULL, 0, myThread, 0, 0, NULL);

	//Sleep(1000);
	glutTimerFunc(10, mytimerevent, 1);
	glutMainLoop();
	return 0;
}
