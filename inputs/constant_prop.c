
int main(int argc, char *argv[]) {
  int a = 123 + 123;
  int b = a + a;
  int c = b * b;
  int d = a ^ a;

  if (a < 3) {
    d = a & a;
  } else {
    d = a | a;
  }


  int x;
  int y = x * 1;
  int z = y + 0;

  return 0;
}
