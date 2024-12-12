#include <stdlib.h>
#include <unistd.h>
#include <vingraph.h>
#include <iostream>
#include <math.h>

int main(){
  ConnectGraph();
  int c = RGB(255,0,0);
  Text(100,100, "lab2");
  Pixel(20,40,c);
  Line(70,50,130,90,c);
  Rect(210,40,60,60);
  tPoint p1 [] = { {340,100}, {400,40} , {400, 100}, {455,55} };
  Polyline(p1,4);
  tPoint p2 [] = { {500,100}, {600,40} , {600, 100}};
  Polygon (p2,3);
  Ellipse(100,200,100,200);
  //Arc(300,250,300,250,0,1800);
  Grid(300,150,200,150,5,5);
  int *im_buf = (int*) malloc (60*60*4);
  for (int i = 0, c = 10; i < 60;i++, c += 0x010304)
    for(int j = 0;j < 60;j++) im_buf [60*i + j] = c;
  Image32(250,350,60,60,im_buf);
  sleep(10);
  CloseGraph();
	return 0;
}
