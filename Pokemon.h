/*
 * Pokemon.h - Pokemon module header file.
 * This module define pokemons and pokemons types.
 * This moudule implemts some helpful functions of maintain Pokedex.
 *  Created on: Nov 19, 2021
 *      Author: ise
 */

#ifndef POKEMON_H_
#define POKEMON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"

// Declaring about structures:

typedef struct BiologicalInfo_t
/*
 * This will store biological information of a pockemon.
 */
{
	float height;
	float weight;
	int attack;
}BiologicalInfo;

typedef struct Type_t
/*
 * This will store type of a pokemon.
 */
{
	char *t_name; // pointer to type name?,
	int pokemon_count; // how many pokemons exist from this type?
	struct Type_t **effective_against_me;
	int ea_me_count;
	struct Type_t **effective_against_others;
	int ea_other_count;
}Type;

typedef struct Pokemon_t
/*
 * This will store the pokemon itself.
 *
 */
{
	char *p_name;
	char *species;
	struct BiologicalInfo_t *pokemon_info;
	struct Type_t *pokemon_type;

}Pokemon;

// Declaring about functions:

// This function get "all information needed" to create pokemon.
Pokemon* Create_Pokemon(char*, char*, BiologicalInfo*, Type*);

// This function create type of pokemon. Gets: name;
Type* Create_Type(char*);

// This function create biological information of specific pokemon.
// who use this function? perhaps create_pokemon calls its.
BiologicalInfo* Create_BiologicalInfo(float, float, int); // could be changes during work

// This function add type of pokemon to list effective against others/me.
// Gets: source pokemon(A), and destination pokemon(B), adds B to effective against others/me of A.
status Add_Me(Type*, Type*);
status Add_Others(Type*, Type*);

// This function delete type of pokemon from list effective against others/me.
// Gets: source pokemon(A), and destination pokemon(B), delete B from effective against others/me of A.
status Delete_Me(Type*, char*);
status Delete_Others(Type*, char*);

// Prints pokemon information. Gets pointer to pokemon.
status Print_Pokemon(Pokemon*);

// Prints type pokemon information. Gets pointer to type
status Print_Type(Type*);

// All of those taking care of delte all.
status Delete_Pokemon(Pokemon*);
void Delete_Type(Type*);
void Delete_BilogicalInfo(BiologicalInfo*);

/* copy functions of pokemon and biological informatio.
 * all of those been added to support unsing pokemon on some adt's...
 * get - pointer to pokemon struct
 * return - deep copy of pokemon
 */
Pokemon* CopyPokemon(Pokemon*);
BiologicalInfo* CopyBioInfo(BiologicalInfo*);
char* getTypeNameOfPok(Pokemon*);


int EqualPoke(Pokemon*, Pokemon*);

int getAttack(Pokemon*, Pokemon*, int*, int*);

/* searchTypeByName - This function get pointer to type, type name
 * search for specific type by name in type effectives list.
 * returns value - 0 NONE, 1 only effective against me, 2 only effective against other, 3 both.
 */
int searchTypeByName(Type*, Type*);

#endif /* POKEMON_H_ */
