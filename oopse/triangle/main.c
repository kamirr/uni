#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUF(x, y) (buf[(x) + buf_x * (y)])

typedef struct {
  double a; //horizontal
  double b; //vertical
  double c;
} triangle_t;

triangle_t get_triangle() {
  double a = -1, b = -1;
  printf("side a (horizontal): ");
  do {
    scanf("%lf", &a);
    if(a <= 0.f) printf("must be positive!: ");
  } while(a <= 0.f);
  
  printf("side b (vertical): ");
  do {
    scanf("%lf", &b);
    if(b <= 0.f) printf("must be positive!: ");
  } while(b <= 0.f);

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
  return y < cutoff;
}

void render(const triangle_t *tr, int* buf, int buf_x, int buf_y) {
  for(int y = 0; y < buf_y; ++y) {
    for(int x = 0; x < buf_x; ++x) {
      double X = x;
      double Y = buf_y - (buf_y % 3) - 1 - y;

      BUF(x, y) = contains(tr, X, Y) ? 1 : 0;
    }
  }
}

void display(int *buf, int buf_x, int buf_y, bool noutf) {
  char br[] = "\xe2\xa0\0";

  for(int y = 0; y < buf_y - 2; y += 3) {
    for(int x = 0; x < buf_x - 1; x += 2) {
      if(!noutf) {
        const int code = BUF(x, y) | BUF(x, y+1) << 1 | BUF(x, y+2) << 2 | BUF(x+1, y) << 3 | BUF(x+1, y+1) << 4 | BUF(x+1, y+2) << 5;
        br[2] = '\x80' + code;
        printf("%s", br);
      } else {
        const int count = BUF(x, y) + BUF(x, y+1) + BUF(x, y+2) + BUF(x+1, y) + BUF(x+1, y+1) + BUF(x+1, y+2);
        if(count == 0)      printf(" ");
        else if(count < 3)  printf(",");
        else if(count < 5)  printf("\\");
        else                printf(rand() % 2 ? "#" : "@");
      }
    }

    printf("\n");
  }
}

int main(int argc, char **argv) {
  bool noutf_term = false;
  bool wrong_use = false;
  if(argc == 2) {
    if(strcmp(argv[1], "noutf") == 0) {
      noutf_term = true;
    } else {
      wrong_use = true;
    }
  } else if(argc != 1) {
    wrong_use = true;
  }

  if(wrong_use) {
    printf("%s [noutf]\n", argv[0]);
    printf("  pass the `noutf` option if your terminal doesn't support UTF braille characters\n");
    return 1;
  }

  triangle_t tr = get_triangle();
  printf("area: %lf\n", area(&tr));
  printf("circumference: %lf\n", circumference(&tr));

  int buf_x = tr.a + 2;
  int buf_y = tr.b + 3;
  int *buf = malloc(sizeof(int) * buf_x * buf_y);

  render(&tr, buf, buf_x, buf_y);
  display(buf, buf_x, buf_y, noutf_term);

  free(buf);

  return 0;
}
