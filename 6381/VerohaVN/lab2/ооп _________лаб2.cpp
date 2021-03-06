#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#define PI            3.14159265358979323846
using namespace std;

class Point {
public:
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {}
};

class Shape {
protected:
	//double x;
	//double y;
	double angle;
	vector<Point> points;
	string color = "black";
	Point center;
public:
	Shape(double x, double y) : color("black"), center(x, y), angle(0) {}
	void setColor(string color) {// установка цвета
		this->color = color;
	}
	void reLocate(double x, double y) {// перемещение в другие координаты (по центру)
		for (auto& i : points) {
			i.x += x - center.x;
			i.y += y - center.y;
		}
		center.x = x;
		center.y = y;
	}
	virtual void zoom(double n) = 0;
	void prepare_for_zoom(double& n) {// масштабирование каждой точки
		for (auto& center : points) {
			center.x = center.x * n;
			center.y = center.y * n;
		}

	}
	void turn(int angl) {// поворот на угол
		angle += angl % 360;
		double radian = angl * PI / 180;
		for (auto& i : points) {
			double newX = (i.x-center.x)*cos(radian) - (i.y-center.y)*sin(radian);
			double newY = (i.x - center.x)*sin(radian) + (i.y - center.y)*cos(radian);
			i.x = center.x + newX;
			i.y= center.y - newY;
		}
	}
	virtual void printOUT(ostream& out) = 0; // печать информации о фигуре
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}
};

class Ellipse : public Shape {
	double radiusX, radiusY;

public:
	Ellipse(Point center, double radiusX, double radiusY) : Shape(center.x, center.y), radiusX(radiusX), radiusY(radiusY) {

		points.push_back(Point((center.x - radiusX), center.y));
		points.push_back(Point(center.x, (center.y + radiusY)));
		points.push_back(Point((center.x + radiusX), center.y));
		points.push_back(Point(center.x, (center.y - radiusY)));
	}

	void zoom(double n) {
		radiusX *= n;
		radiusY *= n;

		points.clear();
		points.push_back(Point((center.x - radiusX), center.y));
		points.push_back(Point(center.x, (center.y + radiusY)));
		points.push_back(Point((center.x + radiusX), center.y));
		points.push_back(Point(center.x, (center.y - radiusY)));
	}

	void printOUT(ostream& out) {
		out << "***Create an ellipse***" << endl;
		out << "Center: (" << center.x << ", " << center.y << ")" << endl;
		out << "Radius lengths: " << radiusX << " , " << radiusY << endl;
		out << "Main points:" << endl;
		for (const auto& i : points) {
			out << "(" << i.x << ", " << i.y << ")\n";
		}
		out << "Color: " << color << endl;
		out << "Angle: " << angle << endl;

	}
};

class IsoscelesTrapeze : public Shape {
	double height;
	double base1; //Lower
	double base2; //Upper
public:
	IsoscelesTrapeze( Point center, double _height, double _base1, double _base2) : Shape( center.x , center.y), height(_height), base1(_base1), base2(_base2)  {
		points.push_back(Point(center.x, center.y +_height / 2));	//Upper center
		points.push_back(Point(center.x - base2 / 2, center.y + _height / 2));	//Upper Left
		points.push_back(Point(center.x + base2 / 2, center.y + _height / 2));	//Upper Right
		points.push_back(Point(center.x, center.y - _height / 2));	//Lower center
		points.push_back(Point(center.x - base1 / 2, center.y - _height / 2));	//Lower Left
		points.push_back(Point(center.x + base1 / 2, center.y - _height / 2));	//Lower Right
	}
	void zoom(double n) {
		prepare_for_zoom(n);
		height *= n;
		base1 *= n;
		base2 *= n;
	}
	void printOUT(ostream& out) {
		out << "***Create a trapeze***" << endl;
		out << "Center: (" << center.x << ", " << center.y << ")" << endl;
		out << "Height: " << height << endl << "Upper base: " << base2 << endl << "Lower base: " << base1 << endl;
		out << "Main points:" << endl;
		for (const auto& i : points) {
			out << "(" << i.x << ", " << i.y << ")\n";
		}
		out << "Color: " << color << endl;
		out << "Angle: " << angle << endl;

	}
};

class Trapeze : public Shape {
	double height;
	double base1; //Lower
	double base2; //Upper
	double upperOffset;
public:
	Trapeze(Point center, double _height, double _base1, double _base2, double _offset) : Shape(center.x, center.y), height(_height), base1(_base1), base2(_base2), upperOffset(_offset) {
		points.push_back(Point(center.x + _offset, center.y + _height / 2));	//Upper center
		points.push_back(Point(center.x - _base2 / 2 + _offset, center.y + _height / 2));	//Upper Left
		points.push_back(Point(center.x + _base2 / 2 + _offset, center.y + _height / 2));	//Upper Right
		points.push_back(Point(center.x, center.y - _height / 2));	//Lower center
		points.push_back(Point(center.x - _base1 / 2, center.y - _height / 2));	//Lower Left
		points.push_back(Point(center.x + _base1 / 2, center.y - _height / 2));	//Lower Right
	}
	void zoom(double n) {
		prepare_for_zoom(n);
		height *= n;
		base1 *= n;
		base2 *= n;
		upperOffset *= n;
	}
	void printOUT(ostream& out) {
		out << "***Create a trapeze***" << endl;
		out << "Center: (" << center.x << ", " << center.y << ")" << endl;
		out << "Height: " << height << endl << "Upper base: " << base2 << endl << "Lower base: " << base1 << endl << "Offset: " << upperOffset << endl;
		out << "Main points:" << endl;
		for (const auto& i : points) {
			out << "(" << i.x << ", " << i.y << ")\n";
		}
		out << "Color: " << color << endl;
		out << "Angle: " << angle << endl;
	}
};

int main() {
	while (true) {
		system("cls");
		int choice = 0;
		cout << "Tests:" << endl << "1. Ellipse" << endl << "2. Trapeze" << endl
			<< "3. Isosceles trapeze" << endl << "4. Ending the preview" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			//Ellipse shape1({ 1, 2 }, 5, 2);
			Ellipse shape1({ 2, 3 }, 4, 2);
			cout << shape1 << endl;
			cout << endl << "Turn it 90 degrees." << endl;
			shape1.turn(90);
			cout << shape1 << endl;
			cout << endl << "Let's color it in red and zoom it 2 times. Results:" << endl;
			shape1.zoom(2);
			shape1.setColor("red");
			cout << shape1 << endl;
			cout << endl << "Move it:" << endl;
			shape1.reLocate(1, 2);
			cout << shape1 << endl;
			system("pause");
			break;
		}
		case 2: {
			Trapeze shape2({ 0, 0 }, 6, 10, 8, 1);
			cout << shape2 << endl;
			cout << endl << "Turn it 180 degrees." << endl;
			shape2.turn(180);
			cout << shape2 << endl;
			cout << endl << "Let's color it in white and zoom it 2 times. Results:" << endl;
			shape2.zoom(2);
			shape2.setColor("white");
			cout << shape2 << endl;
			cout << endl << "Move it:" << endl;
			shape2.reLocate(1, 2);
			cout << shape2 << endl;
			system("pause");
			break;
		}
		case 3: {
			IsoscelesTrapeze shape3({ 1, 2 }, 3, 5, 4);
			cout << shape3 << endl;
			cout << endl << "Turn it 90 degrees." << endl;
			shape3.turn(90);
			cout << shape3 << endl;
			cout << endl << "Let's color it in blue and zoom it 2 times. Results:" << endl;
			shape3.zoom(2);
			shape3.setColor("blue");
			cout << shape3 << endl;
			cout << endl << "Move it:" << endl;
			shape3.reLocate(0, 0);
			cout << shape3 << endl;
			system("pause");
			break;
		}
		case 4: exit(0);
		default:break;
		}
	}
	return 0;
}