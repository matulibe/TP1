#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.h"


int main(){
  torneo_t* torneo = torneo_crear(RUTA);
  torneo_destruir(torneo);
  return 0;
}
