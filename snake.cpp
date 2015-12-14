/*
 * snake.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: doru
 */

#include "snake.h"
#include <cstring>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

snake::~snake() {
	delete [] this->name;
}

snake::snake(const char *name,const int &diff) {
   this->name = new char[strlen(name)+1];
   strcpy(this->name,name);
   v.push_back(point(1,6));
   v.push_back(point(1,5));
   v.push_back(point(1,4));
   v.push_back(point(1,3));
   v.push_back(point(1,2));
   this->length = v.size();
   speed = 300;
   this->direction = 1;
   this->diff = diff;
}
snake::snake(const point &start,const char *name) {
   this->name = new char[strlen(name)+1];
   strcpy(this->name,name);
   v.push_back(start);
   point x(start.getX(),start.getY()-1);
   v.push_back(x);
   x.setY(x.getY()-1);
   v.push_back(x);
   this->length = v.size();
   speed = 300;
   this->direction = 1;
}
snake::snake(const snake &other) {
	this->name = new char[strlen(other.name)+1];
	strcpy(this->name,other.name);
	this->v = other.v;
  this->length = other.length;
  obs = other.obs;
  food = other.food;
}

snake& snake::operator=(const snake &other) {
	this->name = new char[strlen(other.name)+1];
	strcpy(this->name,other.name);
	this->v = other.v;
  this->length = other.length;
  obs = other.obs;
  food = other.food;
	return *this;
}
void snake::modifyDirection(const int &direction) {
	this->direction = direction;
}
int snake::getDirection() const {
	return this->direction;
}
void snake::makeMove() {
    for(int i = this->length; i >=1; i--) {
       v[i] = v[i-1];
    }
    if (this->direction == 1) {
         v[0].setX(v[0].getX()+1); //right
       }
       if (this->direction == 0) {
         v[0].setX(v[0].getX()-1); //left
       }
       if (this->direction == 2) {
         v[0].setY(v[0].getY()-1); //up
       }
       if (this->direction == 3) {
         v[0].setY(v[0].getY()+1); //down
       }
}

void snake::setFood() {
  food = point(rand() % width, rand() % height);
}

void snake::start() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  curs_set(0);
  srand(time(NULL));
  timeout (speed);
  getmaxyx(stdscr ,height, width);
  setFood();
  if (has_colors() != false)
     {
      start_color();
      init_pair(1, COLOR_GREEN, COLOR_GREEN);
      init_pair(2, COLOR_RED, COLOR_RED);
      init_pair(3, COLOR_BLUE, COLOR_BLUE);
    }
    mvprintw(20,20,"Dificulty");
    mvprintw(21,20,"1.Easy");
    mvprintw(22,20,"2.Medium");
    mvprintw(23,20,"3.Hard");
    char x;
    while(x=getch())
    {
      if(x < '1' || x > '3')
      {
        continue;
      }
      else{
        break;
      }
    }
    this->diff = (int)(x-'0');
}

void snake::end() {
  mvprintw((height/3)+1, width/2, "Press any key to exit!" );
  timeout(-1);
  getch();
  keypad(stdscr,false);
  nodelay(stdscr ,false);
  nocbreak();
  echo();
  endwin();
  exit(0);
}
void snake::eraseLast() {
  mvaddch (v[length-1].getY(), v[length-1].getX(), ' ');
}

void snake::show() {
   attron(COLOR_PAIR(1));
   mvaddch (food.getY(), food.getX(), '+');
   attroff(COLOR_PAIR(1));
   for (int i = 0; i < length; i++) {
      mvaddch (v[i].getY(), v[i].getX(), '0' | A_STANDOUT | COLOR_PAIR(1));
   }  
}

void snake::setObstacles() {
   point x;
   //creating obstacles
   for(int i=0; i<50*diff;i++) {
      x = point(rand() % width, rand() % height);
      obs.push_back(x);
   }
  for (int i = 0; i < 50*diff; i++) {
    attron(COLOR_PAIR(2));
    mvaddch (obs[i].getY(), obs[i].getX(), 'x');
    attron(COLOR_PAIR(2));
  }
}

bool snake::legalNextMove() {
  point temp;
  if (direction == 1) {
     temp = point(v[0].getX()+1,v[0].getY());
  }
  if (direction == 0) {
     temp = point(v[0].getX()-1,v[0].getY());
  }
  if (direction == 2) {
     temp = point(v[0].getX(),v[0].getY()-1);
  }
  if (direction == 3) {
     temp = point(v[0].getX(),v[0].getY()+1);
  }
  if (temp.getX() < 0 || temp.getX() > width-1 || temp.getY() < 0 || temp.getY() > height-1) {
    return false;
  }
  if (temp == food) {
    point last = point(v[length-1]);
    v.push_back(last);
    length = v.size();
    setFood();
  }
  for(int i = 1; i < length; i++) {
    if (temp == v[i])
       return false;
  }
  for(int i = 0; i < 50*diff; i++) {
    if (temp == obs[i]) {
      return false;
    }
  }
  return true;
}
