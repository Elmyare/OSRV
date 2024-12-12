#include <stdlib.h>
#include <unistd.h>
#include <vingraph.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>

using namespace std;

int main() {
  ConnectGraph();
  pid_t proc;
  int c = RGB(255, 0, 0);
  int cc = RGB(0, 0, 255);
  int pic = Picture(100, 100);
  int ellipse1 = Ellipse(10, 50, 70, 70,cc, pic);
  int ellipse2 = Ellipse(7, 45, 90, 90, c, pic);
  int x, y, key=0;
  float phi = 0, rho = 0;
  float *a = static_cast<float*>(mmap(0, sizeof* a, PROT_READ + PROT_WRITE, MAP_SHARED + MAP_ANON, -1, 0));
  float *b = static_cast<float*>(mmap(0, sizeof* a, PROT_READ + PROT_WRITE, MAP_SHARED + MAP_ANON, -1, 0));
  *a = 100;
  *b = 100;
  if (proc = fork()) {
    while (key != 13) {
        key = InputChar();
        printf("%d\n", key);
        if (key == 'w')
            *a = *a + 10;
        if (key == 'a')
            *b = *b + 10;
        if (key == 's')
            *a = *a - 10;
        if (key == 'd')
            *b = *b - 10;
    }
    CloseGraph();
  }else{
  while(true){
    rho = *a * cos(phi) + *b;
    x = rho * cos(phi) + 20;
    y = rho * sin(phi) + 20;
    phi += 0.01;
    MoveTo(x,y,pic);
    delay(15);
    } 
  }
  CloseGraph();
  munmap(a, sizeof(float));
  munmap(b, sizeof(float));
  return 0;
}

