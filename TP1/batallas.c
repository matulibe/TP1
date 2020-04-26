#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.h"

#define PRIMERO 0
#define SEGUNDO 1
#define TERCERO 2



torneo_t* torneo_crear(char *ruta_archivo){
  FILE * archivo;
  int cant_leidos;

  archivo = fopen(ruta_archivo, LECTURA);
  if(archivo == NULL){
    printf("No se pudo abrir el archivo\n");
    return NULL;
  }

  torneo_t* torneo = malloc(sizeof(torneo));
  if(torneo == NULL){
    printf("No se pudo dar memoria a el torneo\n");
    return NULL;
  }

  torneo->cantidad_entrenadores = 0;

  int i = 0; //Declaro la variable por prolijidad, pero funcionaria como cantidad_entrenadores

  entrenador_t* entrenador = malloc(sizeof(entrenador_t));
  if(entrenador == NULL){
    printf("No se pudo dar memoria a entrenador auxiliar\n");
    return NULL;
  }

  entrenador[i].pokemones = malloc(MAX_POKEMON * sizeof(pokemon_t));
  if(entrenador[i].pokemones == NULL){
    printf("No se pudo dar memoria a los pokemones\n");
    return NULL;
  }

  cant_leidos = fscanf(archivo, FORMATO_LECTURA, entrenador[i].nombre, entrenador[i].pokemones[0].nombre, &(entrenador[i].pokemones[0].fuerza), &(entrenador[i].pokemones[0].agilidad), &(entrenador[i].pokemones[0].inteligencia), entrenador[i].pokemones[1].nombre, &(entrenador[i].pokemones[1].fuerza), &(entrenador[i].pokemones[1].agilidad), &(entrenador[i].pokemones[1].inteligencia), entrenador[i].pokemones[2].nombre, &(entrenador[i].pokemones[2].fuerza),
  &(entrenador[i].pokemones[2].agilidad), &(entrenador[i].pokemones[2].inteligencia));
  while(cant_leidos != EOF){
    if(torneo->cantidad_entrenadores == 0){
      torneo->entrenadores = entrenador;
      torneo->cantidad_entrenadores++;
    }else{
      entrenador_t* entrenador_aux = realloc(torneo->entrenadores, ((unsigned int)(torneo->cantidad_entrenadores+1)*(sizeof(entrenador_t))));
      if(entrenador != NULL){
        entrenador = entrenador_aux;
        torneo->entrenadores = entrenador;
        torneo->cantidad_entrenadores++;
      }
    }
    cant_leidos = fscanf(archivo, FORMATO_LECTURA, entrenador[i].nombre, entrenador[i].pokemones[0].nombre, &(entrenador[i].pokemones[0].fuerza), &(entrenador[i].pokemones[0].agilidad), &(entrenador[i].pokemones[0].inteligencia), entrenador[i].pokemones[1].nombre, &(entrenador[i].pokemones[1].fuerza), &(entrenador[i].pokemones[1].agilidad), &(entrenador[i].pokemones[1].inteligencia), entrenador[i].pokemones[2].nombre, &(entrenador[i].pokemones[2].fuerza),
    &(entrenador[i].pokemones[2].agilidad), &(entrenador[i].pokemones[2].inteligencia));
  }

  free(entrenador->pokemones);
  free(entrenador);
  fclose(archivo);

  return torneo;
}


void torneo_destruir(torneo_t* torneo){

  free(torneo->entrenadores->pokemones);
  free(torneo->entrenadores);
  free(torneo);

}
