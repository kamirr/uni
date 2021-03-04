#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUF(x, y) (buf[(x) + buf_x * (y)])

typedef struct {
  double a; //horizontal
  double b; //vertical
  double c;
} triangle_t;

triangle_t get_triangle() {
  double a, b;
  scanf("%lf %lf", &a, &b);

  const triangle_t tr = { a, b, sqrt(a*a + b*b) };
  return tr;
}

double area(const triangle_t *tr) {
  return tr->a * tr->b / 2;
}

double circumference(const triangle_t *tr) {
  return tr->a + tr->b + tr->c;
}

bool contains(const triangle_t *tr, const double x, const double y) {
  if(x < 0.f || y < 0.f || x > tr->a) {
    return false;
  }

  const double cutoff = tr->b * (1.0 - x / tr->a);
  return y <= cutoff;
}

void render(const triangle_t *tr, int* buf, int buf_x, int buf_y) {
  for(int y = 0; y < buf_y; ++y) {
    for(int x = 0; x < buf_x; ++x) {
      double X = x;
      double Y = buf_y - y;

      BUF(x, y) = contains(tr, X, Y) ? 1 : 0;
    }
  }
}

void display(int *buf, int buf_x, int buf_y) {
  char br[] = {'\xe2', '\xa0', '\0', '\0'};

  for(int y = 0; y < buf_y - 3; y += 3) {
    for(int x = 0; x < buf_x - 2; x += 2) {
      const int code = BUF(x, y) | BUF(x, y+1) << 1 | BUF(x, y+2) << 2 | BUF(x+1, y) << 3 | BUF(x+1, y+1) << 4 | BUF(x+1, y+2) << 5;
      br[2] = '\x80' + code;
      printf("%s", br);
    }

    printf("\n");
  }
}

int main() {
  triangle_t tr = get_triangle();
  printf("area: %lf\n", area(&tr));
  printf("circumference: %lf\n", circumference(&tr));

  int buf_x = tr.a + 1;
  int buf_y = tr.b + 2;
  int *buf = malloc(sizeof(int) * buf_x * buf_y);

  render(&tr, buf, buf_x, buf_y);
  display(buf, buf_x, buf_y);

  free(buf);
}
