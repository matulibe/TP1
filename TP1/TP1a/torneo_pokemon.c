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

void mostrar_campeon(entrenador_t* entrenador){
  printf(ANSI_COLOR_YELLOW"%s es el campeon!\n"ANSI_COLOR_RESET, entrenador->nombre);
  printf(ANSI_COLOR_YELLOW"\tSus Pokemones son:\n"ANSI_COLOR_RESET);
  for(int i = 0; i < MAX_POKEMON; i++){
    printf(ANSI_COLOR_YELLOW"\t\t%s, inteligencia: %i, Agilidad: %i, Fuerza: %i\n"ANSI_COLOR_RESET, entrenador->pokemones[i].nombre, entrenador->pokemones[i].inteligencia, entrenador->pokemones[i].agilidad, entrenador->pokemones[i].fuerza);
  }
}

void randomizar_pelea(int (**ganador_batalla)(entrenador_t* ,entrenador_t*)){
  int opcion = rand()%5;
  if(opcion == 0){
    (*ganador_batalla) = &batalla_torpeza;
  }else if(opcion == 1){
    (*ganador_batalla) = &batalla_inferior;
  }else if(opcion == 2){
    (*ganador_batalla) = &batalla_superior;
  }else if(opcion == 3){
    (*ganador_batalla) = &batalla_debilidad;
  }else{
    (*ganador_batalla) = &batalla_mejor_luchador;
  }
}

void randomizar_lista(void (**formatear_entrenador)(entrenador_t*)){
  int opcion = rand()%4;
  if(opcion == 0){
    (*formatear_entrenador) = &listar_todo;
  }else if(opcion == 1){
    (*formatear_entrenador) = &listar_fuerza;
  }else if(opcion == 2){
    (*formatear_entrenador) = &listar_agilidad;
  }else{
    (*formatear_entrenador) = &listar_inteligencia;
  }
}


int main(int argc, char const *argv[]){
  char ruta[MAX_NOMBRE];
  int (*ganador_batalla)(entrenador_t* ,entrenador_t*) = NULL;
  void (*formatear_entrenador)(entrenador_t*) = NULL;
  if(argc != ARGUMENTOS){
    printf("No se paso la cantidad correcta de argumentos\n");
    return -1;
  }
  strcpy(ruta, argv[RUTA]);
  torneo_t* torneo = torneo_crear(ruta);
  if(torneo->cantidad_entrenadores <= 1 || torneo == NULL){
    printf("No se puede jugar el torneo\n");
    return -1;
  }
  printf("Torneo Pokemon: Ronda %i\n", torneo->ronda);
  randomizar_lista(&formatear_entrenador);
  torneo_listar(torneo, formatear_entrenador);
  while(torneo->cantidad_entrenadores > ULTIMO){
    torneo->ronda++;
    printf("Torneo Pokemon: Ronda %i\n", torneo->ronda);
    randomizar_pelea(&ganador_batalla);
    torneo_jugar_ronda(torneo, ganador_batalla);
    randomizar_lista(&formatear_entrenador);
    torneo_listar(torneo, formatear_entrenador);
  }
  torneo_listar(torneo, mostrar_campeon);
  printf("Cantidad de rondas: %i\n", torneo->ronda);
  torneo_destruir(torneo);
  return 0;
}
