#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

typedef int32_t int32_t;

int8_t* writeInteger(int32_t n) {
  printf("%d", n);
  return NULL;
}

int8_t* writeBoolean(bool b) {
  if (b == 0) {
    printf("false");
  }
  else {
    printf("true");
  }
  return NULL;
}

int8_t* writeChar(int8_t c) {
  printf("%c", c);
  return NULL;
}

int8_t* writeReal(double x) {
  printf("%f", x);
  return NULL;
}

int8_t* writeString(int8_t *s) {
  printf("%s", s);
  return NULL;
}

int32_t readInteger() {
  int32_t n;
  scanf("%d", &n);
  return n;
}

bool readBoolean() {
  int8_t n;
  scanf("%c", &n);
  return (bool)n;
}

int8_t readChar() {
  int8_t n;
  n = getchar();
  return n;
}

double readReal() {
  double n;
  scanf("%lf", &n);
  return n;
}

void readString(int32_t size, int8_t *s) {
    if (size <= 0) {
      return;
    }

    int8_t buf[size];

    memset(buf, 0, size);

    if (size == 1) {
      return;
    }

    size--;
    int32_t i = 0;
    int8_t c = getchar();

    for (i = 0; i < size; i++) {
      buf[i] = c;
      c = getchar();
      if (c == EOF || c == '\n') break;
    }

    strcpy((char *)s, (char *)buf);
}

// ln
double ln(double x) {
  return log(x);
}

// arctan
double arctan(double x) {
  return (double) atan(x);
}

double pi() {
  return (double) M_PI;
}

int32_t trunc2(double x) {
  return (int32_t) trunc(x);
}

int32_t round2(double x){
  return (int32_t) round(x);
}

int8_t chr(int32_t x){
  return (int8_t) x;
}

int32_t ord(int8_t x){
  return (int32_t) x;
}
