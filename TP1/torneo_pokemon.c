#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "batallas.h"

#define ULTIMO 1
#define ARGUMENTOS 2
#define RUTA 1


int batalla_torpeza(entrenador_t* entrenador_a, entrenador_t* entrenador_b){
  int a = entrenador_a->pokemones[PRIMERO].agilidad;
  int b = entrenador_b->pokemones[PRIMERO].agilidad;
  int victorioso;
    if(a < b){
      victorioso = 0;
    }else if(b < a){
      victorioso = 1;
    }else{
      if(entrenador_a->pokemones[SEGUNDO].inteligencia > entrenador_b->pokemones[SEGUNDO].inteligencia){
        victorioso = 0;
      }else{
        victorioso = 1;
      }
    }
    return victorioso;
}

int batalla_debilidad(entrenador_t* entrenador_a, entrenador_t* entrenador_b){
  int a = entrenador_a->pokemones[PRIMERO].fuerza;
  int b = entrenador_b->pokemones[PRIMERO].fuerza;
  int victorioso;
    if(a < b){
      victorioso = 0;
    }else if(b < a){
      victorioso = 1;
    }else{
      a = (entrenador_a->pokemones[SEGUNDO].agilidad + entrenador_a->pokemones[TERCERO].agilidad);
      b = (entrenador_b->pokemones[SEGUNDO].agilidad + entrenador_b->pokemones[TERCERO].agilidad);
      if(a > b){
        victorioso = 0;
      }else{
        victorioso = 1;
      }
    }
    return victorioso;
}

int batalla_superior(entrenador_t* entrenador_a, entrenador_t* entrenador_b){
  int a = 0;
  int b = 0;
  int victorioso;

  for(int i = 0; i < MAX_POKEMON; i++){
    a += (entrenador_a->pokemones[i].agilidad + entrenador_a->pokemones[i].inteligencia + entrenador_a->pokemones[i].fuerza);
  }

  for(int j = 0; j < MAX_POKEMON; j++){
    b += (entrenador_b->pokemones[j].agilidad + entrenador_b->pokemones[j].inteligencia + entrenador_b->pokemones[j].fuerza);
  }

  if(a < b){
    victorioso = 1;
  }else if(a > b){
    victorioso = 0;
  }else{
    if((entrenador_a->pokemones[PRIMERO].fuerza) < (entrenador_b->pokemones[PRIMERO].fuerza)){
      victorioso = 1;
    }else{
      victorioso = 0;
    }
  }
  return victorioso;
}

int batalla_inferior(entrenador_t* entrenador_a, entrenador_t* entrenador_b){
  int a = 0;
  int b = 0;
  int victorioso;

  for(int i = 0; i < MAX_POKEMON; i++){
    a += (entrenador_a->pokemones[i].agilidad + entrenador_a->pokemones[i].inteligencia + entrenador_a->pokemones[i].fuerza);
  }

  for(int j = 0; j < MAX_POKEMON; j++){
    b += (entrenador_b->pokemones[j].agilidad + entrenador_b->pokemones[j].inteligencia + entrenador_b->pokemones[j].fuerza);
  }

  if(a < b){
    victorioso = 0;
  }else if(a > b){
    victorioso = 1;
  }else{
    if((entrenador_a->pokemones[PRIMERO].fuerza) < (entrenador_b->pokemones[PRIMERO].fuerza)){
      victorioso = 0;
    }else{
      victorioso = 1;
    }
  }
  return victorioso;
}

int batalla_mejor_luchador(entrenador_t* entrenador_a, entrenador_t* entrenador_b){
  int a = (entrenador_a->pokemones[PRIMERO].agilidad + entrenador_a->pokemones[PRIMERO].fuerza);
  int b = (entrenador_b->pokemones[PRIMERO].agilidad + entrenador_b->pokemones[PRIMERO].fuerza);
  int victorioso;
    if(a < b){
      victorioso = 0;
    }else if(b < a){
      victorioso = 1;
    }else{
      int a = (entrenador_a->pokemones[TERCERO].agilidad + entrenador_a->pokemones[TERCERO].fuerza);
      int b = (entrenador_b->pokemones[TERCERO].agilidad + entrenador_b->pokemones[TERCERO].fuerza);
      if(a > b){
        victorioso = 0;
      }else{
        victorioso = 1;
      }
    }
    return victorioso;
}

void listar_todo(entrenador_t* entrenador){
  printf("\tEntrenador: %s\n", entrenador->nombre);
  for(int i = 0; i < MAX_POKEMON; i++){
    printf("\t\tNombre: %s, inteligencia: %i, Agilidad: %i, Fuerza: %i\n", entrenador->pokemones[i].nombre, entrenador->pokemones[i].inteligencia, entrenador->pokemones[i].agilidad, entrenador->pokemones[i].fuerza);
  }
}

void listar_inteligencia(entrenador_t* entrenador){
  printf("\tEntrenador: %s\n", entrenador->nombre);
  for(int i = 0; i < MAX_POKEMON; i++){
    printf("\t\t\tNombre: %s, inteligencia: %i\n", entrenador->pokemones[i].nombre, entrenador->pokemones[i].inteligencia);
  }
}

void listar_agilidad(entrenador_t* entrenador){
  printf("\tEntrenador: %s\n", entrenador->nombre);
  for(int i = 0; i < MAX_POKEMON; i++){
    printf("\t\tNombre: %s, Agildad: %i\n", entrenador->pokemones[i].nombre, entrenador->pokemones[i].agilidad);
  }
}

void listar_fuerza(entrenador_t* entrenador){
  printf("\tEntrenador: %s\n", entrenador->nombre);
  for(int i = 0; i < MAX_POKEMON; i++){
    printf("\t\tNombre: %s, fuerza: %i\n", entrenador->pokemones[i].nombre, entrenador->pokemones[i].fuerza);
  }
}


int main(int argc, char const *argv[]){
  char ruta[MAX_NOMBRE] = "ruta_archivo.txt";
  torneo_t* torneo = torneo_crear(ruta);
  if(torneo->cantidad_entrenadores <= 1 || torneo == NULL){
    printf("No se puede jugar el torneo\n");
    return 0;
  }
  torneo_listar(torneo, listar_todo);
  while(torneo->cantidad_entrenadores > ULTIMO){
    torneo->ronda++;
    if(torneo == NULL){
      printf("No se puede jugar el torneo\n");
      return 0;
    }
    torneo_jugar_ronda(torneo, batalla_superior);
    torneo_listar(torneo, listar_fuerza);
  }
  printf("Ganador:\n");
  torneo_listar(torneo, listar_inteligencia);
  torneo_destruir(torneo);
  return 0;
}
