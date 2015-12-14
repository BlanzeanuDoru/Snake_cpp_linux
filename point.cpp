/*
 * point.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: doru
 */
#include "point.h"

point::point() {
	x=0;
	y=0;
}
point::point(const int &x,const int &y) {
    this->x = x;
    this->y = y;
}
int point::getX() const {
	return this->x;
}
int point::getY() const {
	return this->y;
}
void point::setX(const int &x) {
    this->x = x;
}
void point::setY(const int &y) {
    this->y = y;
}
void point::setXY(const int &x,const int &y) {
    this->x = x;
    this->y = y;
}
ostream& operator<<(ostream &os,const point &other) {
   os<<"\nX="<<other.x<<"\nY="<<other.y;
   return os;
}
istream& operator>>(istream &is,point &other) {
   std::cout<<"\nX="; is>>other.x;
   std::cout<<"\nY="; is>>other.y;
   return is;
}
bool point::operator==(const point &other) {
   return (this->x == other.x) && (this->y == other.y);
}

