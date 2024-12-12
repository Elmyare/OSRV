#include <stdlib.h>
#include <unistd.h>
#include <vingraph.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;

int main() {
  ConnectGraph();
  int c = RGB(255, 0, 0);

  // Рисование элементов
  Text(2, 2, "lab2");
  int pixel = Pixel(20, 40, c);
  int rect = Rect(210, 40, 50, 50);
  tPoint p1[] = {{340, 100}, {400, 40}, {400, 100}, {455, 55}};
  int polyline = Polyline(p1, 4);
  tPoint p2[] = {{500, 100}, {600, 40}, {600, 100}};
  int polygon = Polygon(p2, 3);
  int ellipse = Ellipse(100, 200, 100, 200);

  pid_t pids[5];
  pids[0] = fork();
  
  if (pids[0] == 0) { 
    srand(time(0));
    while (true) {
      int c = RGB(rand() % 255, rand() % 255, rand() % 255);
      int x = (rand() % 3) - 1;
      int y = (rand() % 3) - 1;
      Move(pixel, x, y);
      SetColor(pixel, c);
      usleep(100000); 
    }
    exit(0); 
  } else if (pids[0] > 0) {
    pids[1] = fork();
    if (pids[1] == 0) { 
      srand(time(0));
      while (true) {
        int c = RGB(rand() % 255, rand() % 255, rand() % 255);
        int x = (rand() % 3) - 1;
        int y = (rand() % 3) - 1;
        Move(ellipse, x, y);
        SetColor(ellipse, c);
        usleep(200000);
      }
      exit(0);
    } else if (pids[1] > 0) {
      pids[2] = fork();
      if (pids[2] == 0) {
        srand(time(0));
        while (true) {
          int c = RGB(rand() % 255, rand() % 255, rand() % 255);
          int lr = (rand() % 20) - 10;
          int x = (rand() % 3) - 1;
          int y = (rand() % 3) - 1;
          Move(rect, x, y);
          SetColor(rect, c);
          Enlarge(rect, lr, lr);
          x = (rand() % 3) - 1;
          y = (rand() % 3) - 1;
          Move(polygon, x, y);
          SetColor(polygon, c);
          usleep(300000);
        }
        exit(0); 
      } else if (pids[2] > 0) {
        pids[3] = fork();
        if (pids[3] == 0) { 
          srand(time(0));
          while (true) {
            int x = (rand() % 3) - 1;
            int y = (rand() % 3) - 1;
            x = (rand() % 3) - 1;
            y = (rand() % 3) - 1;
            Move(polygon, x, y);
            usleep(400000); 
          }
          exit(0); 
        } else if (pids[3] > 0) { 
          srand(time(0));
          while (true) {
            int c = RGB(rand() % 255, rand() % 255, rand() % 255);
            int x = (rand() % 3) - 1;
            int y = (rand() % 3) - 1;
            Move(polyline, x, y);
            SetColor(polyline, c);
            usleep(500000);
          }
          exit(0); 
        }
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    wait(NULL);
  }

  CloseGraph();
  return 0;
}