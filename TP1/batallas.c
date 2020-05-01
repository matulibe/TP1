#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "batallas.h"

#define CANT_LECTURA 13


torneo_t* torneo_crear(char *ruta_archivo){
  FILE * archivo;
  int cant_leidos;

  archivo = fopen(ruta_archivo, LECTURA);
  if(archivo == NULL){
    printf("No se pudo abrir el archivo\n");
    return NULL;
  }

  torneo_t* torneo = malloc(sizeof(torneo_t));
  if(torneo == NULL){
    printf("No se pudo dar memoria a el torneo\n");
    fclose(archivo);
    return NULL;
  }

  torneo->cantidad_entrenadores = 0;
  torneo->ronda = 0;

  entrenador_t* entrenador = malloc(sizeof(entrenador_t));
  if(entrenador == NULL){
    printf("No se pudo dar memoria a entrenador auxiliar\n");
    free(torneo);
    fclose(archivo);
    return NULL;
  }

  entrenador->pokemones = malloc(MAX_POKEMON * sizeof(pokemon_t));
  if(entrenador->pokemones == NULL){
    printf("No se pudo dar memoria a los pokemones\n");
    free(entrenador);
    free(torneo);
    fclose(archivo);
    return NULL;
  }

  cant_leidos = fscanf(archivo, FORMATO_LECTURA, entrenador[torneo->cantidad_entrenadores].nombre, entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].inteligencia), entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].inteligencia), entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].inteligencia));
  if(cant_leidos != CANT_LECTURA){
    free(entrenador->pokemones);
    free(entrenador);
    free(torneo);
    fclose(archivo);
    return NULL;
  }

  while(cant_leidos == CANT_LECTURA){
    torneo->entrenadores = entrenador;
    torneo->cantidad_entrenadores++;
    entrenador = realloc(torneo->entrenadores, (unsigned int)(torneo->cantidad_entrenadores+1)*(sizeof(entrenador_t)));
    if(entrenador == NULL){
      printf("No se pudo dar memoria al auxiliar\n");
      for(int j = 0; j < torneo->cantidad_entrenadores; j++){
        free(torneo->entrenadores[j].pokemones);
      }
      free(torneo->entrenadores);
      free(torneo);
      fclose(archivo);
      return NULL;
    }
    torneo->entrenadores = entrenador;
    entrenador[torneo->cantidad_entrenadores].pokemones =  malloc(MAX_POKEMON * sizeof(pokemon_t));
    if(entrenador[torneo->cantidad_entrenadores].pokemones == NULL){
      printf("No se pudo dar memoria al auxiliar\n");
      for(int j = 0; j < torneo->cantidad_entrenadores; j++){
        free(torneo->entrenadores[j].pokemones);
      }
      free(torneo->entrenadores);
      free(torneo);
      fclose(archivo);
      return NULL;
    }
    cant_leidos = fscanf(archivo, FORMATO_LECTURA, entrenador[torneo->cantidad_entrenadores].nombre, entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].inteligencia), entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].inteligencia), entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].inteligencia));
    if(cant_leidos != CANT_LECTURA && cant_leidos != EOF){
      free(entrenador->pokemones);
      free(entrenador);
      free(torneo);
      fclose(archivo);
      return NULL;
    }
  }
  free(entrenador[torneo->cantidad_entrenadores].pokemones);
  fclose(archivo);
  return torneo;
}




int torneo_jugar_ronda(torneo_t* torneo, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)){
  int pos_nueva = 0;
  int ganador;
  entrenador_t* auxiliar;

  for(int i = 0; i < torneo->cantidad_entrenadores; i+=2){
    if(torneo->cantidad_entrenadores%2 == 0){
      ganador = ganador_batalla(&(torneo->entrenadores[i]), &(torneo->entrenadores[i+1]));
      if(ganador == 0){
        free(torneo->entrenadores[i+1].pokemones);
        torneo->entrenadores[pos_nueva] = torneo->entrenadores[i];
      }else{
        free(torneo->entrenadores[i].pokemones);
        torneo->entrenadores[pos_nueva] = torneo->entrenadores[i+1];
      }
      pos_nueva++;
    }else{
      ganador = ganador_batalla(&(torneo->entrenadores[i]), &(torneo->entrenadores[i+1]));
      if(ganador == 0 ){
        free(torneo->entrenadores[i+1].pokemones);
        torneo->entrenadores[pos_nueva] = torneo->entrenadores[i];
      }else{
        free(torneo->entrenadores[i].pokemones);
        torneo->entrenadores[pos_nueva] = torneo->entrenadores[i+1];
      }
      pos_nueva++;
      if(i == torneo->cantidad_entrenadores-2){
        torneo->entrenadores[pos_nueva] = torneo->entrenadores[torneo->cantidad_entrenadores-1];
      }
    }
  }

  auxiliar = realloc(torneo->entrenadores, (unsigned int)(torneo->cantidad_entrenadores/2 + 1) * sizeof(entrenador_t));
  if(auxiliar == NULL){
    printf("No se puede dar memoria a auxiliar\n");
    for(int i = 0; i < torneo->cantidad_entrenadores; i++){
      free(torneo->entrenadores[i].pokemones);
      free(torneo->entrenadores);
    }
    return -1;
  }
  torneo->cantidad_entrenadores = (torneo->cantidad_entrenadores/2);
  torneo->entrenadores = auxiliar;
  return 0;
}





void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){
  printf("Torneo Pokemon: Ronda %i\n", torneo->ronda);
  for(int i = 0; i < torneo->cantidad_entrenadores; i++){
    formatear_entrenador(&(torneo->entrenadores[i]));
  }
  printf("----------------------------------------------------------------\n");
}





void torneo_destruir(torneo_t* torneo){
  for(int j = 0; j < torneo->cantidad_entrenadores; j++){
    printf("%i\n", j);
    free(torneo->entrenadores[j].pokemones);
  }
  free(torneo->entrenadores);
  free(torneo);
}
