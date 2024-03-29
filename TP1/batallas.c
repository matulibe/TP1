#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "batallas.h"

#define CANT_LECTURA 13
#define COMIENZO 0
#define PRIMERO 0
#define SEGUNDO 1
#define TERCERO 2
#define MAX_POKEMON 3
#define UNICO 1

#define FORMATO_LECTURA "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n"
#define LECTURA "r"


//pre:Se le enviara un archivo abierto, el torneo, el entrandor auxiliar y la cantidad de lo que tiene que leer.
//post: En el caso de que salga todo bien le asignara los valores correspondientes al vector de entrenadores en la posicion deseada.
void leer_entrenadores(FILE* ruta, torneo_t* torneo, entrenador_t* entrenador, int* cant_leidos){
  *cant_leidos = fscanf(ruta, FORMATO_LECTURA, entrenador[torneo->cantidad_entrenadores].nombre, entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[PRIMERO].inteligencia), entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[SEGUNDO].inteligencia), entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].nombre, &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].fuerza), &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].agilidad), &(entrenador[torneo->cantidad_entrenadores].pokemones[TERCERO].inteligencia));
}
//pre:Recibira el torneo cuando haya habido un error al hacer o al tener un problema con el archivo.
//post:Destruira el torneo por emergencia y le avisara al usuario.
void destruccion_seguridad(torneo_t* torneo){
  for(int j = 0; j < torneo->cantidad_entrenadores; j++){
    free(torneo->entrenadores[j].pokemones);
  }
  free(torneo->entrenadores);
  free(torneo);
  printf("Se destruyo el torneo por seguridad\n");
}



//pre:Se le pasara la ruta de un archivo el cual debe abrir.
//post:Devolvera el torneo cargado con los datos que se le pasaron mediante el archivo y cancelara el torneo en el caso que el archivo genere problemas.
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

  leer_entrenadores(archivo, torneo, entrenador, &cant_leidos);
  if(cant_leidos != CANT_LECTURA){
    torneo->entrenadores = entrenador;
    torneo->cantidad_entrenadores++;
    destruccion_seguridad(torneo);
    fclose(archivo);
    return NULL;
  }

  while(cant_leidos == CANT_LECTURA){
    torneo->entrenadores = entrenador;
    torneo->cantidad_entrenadores++;
    entrenador = realloc(torneo->entrenadores, (unsigned int)(torneo->cantidad_entrenadores+1)*(sizeof(entrenador_t)));
    if(entrenador == NULL){
      printf("No se pudo dar memoria al auxiliar\n");
      destruccion_seguridad(torneo);
      fclose(archivo);
      return NULL;
    }
    torneo->entrenadores = entrenador;
    entrenador[torneo->cantidad_entrenadores].pokemones =  malloc(MAX_POKEMON * sizeof(pokemon_t));
    if(entrenador[torneo->cantidad_entrenadores].pokemones == NULL){
      printf("No se pudo dar memoria al auxiliar\n");
      destruccion_seguridad(torneo);
      fclose(archivo);
      return NULL;
    }
    leer_entrenadores(archivo, torneo, entrenador, &cant_leidos);
    if(cant_leidos != CANT_LECTURA && cant_leidos != EOF){
      torneo->cantidad_entrenadores++;
      destruccion_seguridad(torneo);
      fclose(archivo);
      return NULL;
    }
  }
  if(torneo == NULL){
    printf("No se puede jugar un torneo NULL\n");
    destruccion_seguridad(torneo);
    fclose(archivo);
  }
  free(entrenador[torneo->cantidad_entrenadores].pokemones);
  fclose(archivo);
  return torneo;
}

//pre:Se le enviara el torneo y las posiciones del perdedor y del ganador, ademas de una nueva posicion.
//post:Eliminara las pokemones del entrenador que perdio y movera al entrenador ganador a la posicion nueva.
void acomodar_vector(torneo_t* torneo, int ganador, int perdedor, int pos_nueva){
  free(torneo->entrenadores[perdedor].pokemones);
  torneo->entrenadores[pos_nueva] = torneo->entrenadores[ganador];
}

void actualizar_entrenadores(torneo_t* torneo, entrenador_t* auxiliar){
  if(torneo->cantidad_entrenadores%2 == 0){
    torneo->cantidad_entrenadores = (torneo->cantidad_entrenadores/2);
  }else{
    torneo->cantidad_entrenadores = (torneo->cantidad_entrenadores/2 + 1);
  }
  torneo->entrenadores = auxiliar;
}

//pre:Recibira el torneo y un puntero a funion que definira la ronda que se va a jugar.
//post:Si todo sale bien devolvera el torneo con los entrenadores que ganaron y liberar la memoria de los entrenadores y pokemones que perdieron.
int torneo_jugar_ronda(torneo_t* torneo, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)){
  int pos_nueva = 0;
  int ganador;
  entrenador_t* auxiliar;

  if(ganador_batalla == NULL){
    printf("ERROR: la funcion es NULL\n");
    return ERROR;
  }

  if(torneo == NULL){
    printf("No se puede jugar un torneo NULL\n");
    return -1;
  }


  if(torneo->cantidad_entrenadores == UNICO && torneo->ronda == COMIENZO){
    //printf("No hay sufucientes jugadores para jugar el torneo\n");
    return ERROR;
  }

  torneo->ronda++;

  if(torneo->cantidad_entrenadores%2 == 0){
    for(int i = 0; i< torneo->cantidad_entrenadores; i+=2){
      ganador = ganador_batalla(&(torneo->entrenadores[i]), &(torneo->entrenadores[i+1]));
      if(ganador == 0){
        acomodar_vector(torneo, i, i+1, pos_nueva);
      }else{
        acomodar_vector(torneo, i+1, i, pos_nueva);
      }
      pos_nueva++;
    }
  }else{
    int i = 0;
    while(i+2 < torneo->cantidad_entrenadores){
      ganador = ganador_batalla(&(torneo->entrenadores[i]), &(torneo->entrenadores[i+1]));
      if(ganador == 0){
        acomodar_vector(torneo, i, i+1, pos_nueva);
      }else{
        acomodar_vector(torneo, i+1, i, pos_nueva);
      }
      pos_nueva++;
      i+=2;
    }
    torneo->entrenadores[pos_nueva] = torneo->entrenadores[torneo->cantidad_entrenadores-1];
  }

  auxiliar = realloc(torneo->entrenadores, (unsigned int)(torneo->cantidad_entrenadores/2 + 1) * sizeof(entrenador_t));
  if(auxiliar == NULL){
    printf("No se puede dar memoria a auxiliar\n");
    destruccion_seguridad(torneo);
    return ERROR;
  }
  actualizar_entrenadores(torneo, auxiliar);
  return EXITO;
}




//pre:Recicira un puntero a funcion que definira la forma de listado y el torneo.
//post:Imprimira por pantalla los participantes y sus pokemones como lo pida el puntero a funcion.
void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){
  if(torneo == NULL){
    printf("No se puede listar un torneo NULL\n");
    return;
  }

  if(formatear_entrenador == NULL){
    printf("ERROR: el listado pasado es NULL\n");
    return;
  }
  for(int i = 0; i < torneo->cantidad_entrenadores; i++){
    formatear_entrenador(&(torneo->entrenadores[i]));
  }
  printf("------------------------------------------------------------------------------\n");
}




//pre:Una vez finalizado el programa recibira el torneo para destruirlo.
//post:Liberara la memoria del torneo.
void torneo_destruir(torneo_t* torneo){
  if(torneo == NULL){
    printf("No se puede destruir un torneo NULL\n");
    return;
  }
  for(int i = 0; i < torneo->cantidad_entrenadores; i++){
    printf("%i\n", i);
    free(torneo->entrenadores[i].pokemones);
  }
  free(torneo->entrenadores);
  free(torneo);
}
