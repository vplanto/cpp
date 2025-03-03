/* Implementation for Moving 3D Points with int coords (MovablePoint.cpp) */
#include "MovablePoint.h"  // Include header containing the class declaration

#include <iostream>
using namespace std;

MovablePoint::MovablePoint(int x, int y, int xSpeed, int ySpeed)
    : Point(x, y), xSpeed(xSpeed), ySpeed(ySpeed) {}

// Getters
int MovablePoint::getXSpeed() const { return xSpeed; }
int MovablePoint::getYSpeed() const { return ySpeed; }

// Setters
void MovablePoint::setXSpeed(int xs) { xSpeed = xs; }
void MovablePoint::setYSpeed(int ys) { ySpeed = ys; }

// Functions
void MovablePoint::print() const {
  cout << "Movable";
  Point::print();  // Invoke base class function via scope resolution operator
  cout << " Speed="
       << "(" << xSpeed << "," << ySpeed << ")";
}

void MovablePoint::move() {
  // Subclass cannot access private member of the superclass directly
  // Need to go thru the public interface
  Point::setX(Point::getX() + xSpeed);
  Point::setY(Point::getY() + ySpeed);
}
