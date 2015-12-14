
#include "snake.h"
#include <iostream>
#include <curses.h>
using namespace std;

int main()
{   
    snake player("Doru",5);
    char x;
    erase();
    player.start();
    erase();
    player.setObstacles();
    player.show();
    while(1)
    {
      x = getch();
      if (x == 'w') {
      	player.modifyDirection(2);
      }
      if (x == 's') {
      	player.modifyDirection(3);
      }
      if (x == 'd') {
      	player.modifyDirection(1);
      }	
      if (x == 'a') {
      	player.modifyDirection(0);
      }
      if(player.legalNextMove())
      {
      	player.eraseLast();
        player.makeMove();
      }
      else {
      	break;
      }
      			
      player.show();
    }
    player.end();
    
    return 0;
}
