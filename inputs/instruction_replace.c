int foo(int a) { return a * 2; }

int bar(int a, int b) { return (a + foo(b) * 2); }

int fez(int a, int b, int c) { return (a + bar(a, b) * 2 + c * 3); }

int main(int argc, char *argv[]) {
  int a = 123;
  int ret = 0;
  a = ret + ret;
  ret = 0 + 0;

  int c = 30 + 30;

  ret += foo(a);
  ret += bar(a, ret);
  ret += fez(a, ret, 123);

  int x;
  int y = x * 1;
  int z = y + 0;

  return ret;
}
