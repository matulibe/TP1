#include <stdio.h>


char* devolvera_string(){

  return "MIRA LORO, DEVOLVI UN STRING";
}

int main(int argc, char const *argv[]) {
  char* palabra = devolvera_string();
  printf("%s\n", palabra);

  int a = 5;
  int b = 2;

  int r =(a/b + a%b);
  printf("%i\n", r);

  return 0;
}
