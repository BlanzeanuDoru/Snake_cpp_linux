/*
 * point.h
 *
 *  Created on: Nov 23, 2015
 *      Author: doru
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
using namespace std;

class point {
private:
	int x;
	int y;
public:
	point();
	point(const int&,const int&);
	int getX() const;
	int getY() const;
	void setX(const int&);
	void setY(const int&);
	void setXY(const int&,const int&);
	bool operator==(const point&);
	friend ostream& operator<<(ostream&,const point&);
	friend istream& operator>>(istream&,point&);
};



#endif /* POINT_H_ */
