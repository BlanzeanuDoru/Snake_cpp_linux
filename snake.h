/*
 * snake.h
 *
 *  Created on: Nov 23, 2015
 *      Author: doru
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "point.h"
#include <vector>

//top left corner is (0,0)
//directions
// 1->right
// 0->left
// 2->up
// 3->down

class snake {
private:
    int diff; //difficulty (sets number of obstacles = 50*diff)
    int length;
	int direction;
	char *name;
    int speed,height,width;
    vector<point> v;  //the snake's points
    point food;   //the food
    vector<point> obs; //obstacles
public:
    ~snake();
    snake(const char*,const int&);
    snake(const point&,const char*);
    snake(const snake&);
    snake& operator=(const snake&);
    void makeMove();
    void modifyDirection(const int&);
    int getDirection() const;
    void start(); //for terminal initialisation
    void end(); //for terminal end
    void show();
    void eraseLast();
    bool legalNextMove(); //condition to not overlap
    void setFood();
    void setObstacles();
};




#endif /* SNAKE_H_ */
