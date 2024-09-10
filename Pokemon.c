/*
 * Pokemon.c - implemenation of functions of Pokemon.h
 */
#include "Pokemon.h"



BiologicalInfo* Create_BiologicalInfo(float height, float weight, int attack)
/*
 * This function return pointer to struct from bilogicalinfo.
 * biological info contatn weight, weight and attack of specific pokemon,
 */
{
	BiologicalInfo* bio_info;
	bio_info = (BiologicalInfo*) malloc(sizeof(BiologicalInfo));// pointer
	if (bio_info==NULL) // no memory allocated
	{
		printf("Memory Problem\n");
		return NULL;
	}
	else
	{
		bio_info->attack = attack;
		bio_info->height = height;
		bio_info->weight = weight;
		return bio_info;
	}
}


/*
 * Both create type and create pokemon gets from main fully length strings,
 * (300 chars as defined).
 * while create pokemons\type we use buffer to reduce memory amount
 * of using.
 */


Type* Create_Type(char *t_name)
/*
 * Thif function get a pointer to type name.
 * We used buffer on the originial string, and this name allocated just in its size.
 */
{
	if (t_name == NULL)
		return NULL;
	Type* type;
	type = (Type*) malloc(sizeof(Type));
	if (type == NULL)
		printf("Memory Problem\n");

	else
	{

		type->t_name = (char*) calloc((strlen(t_name))+1, (sizeof(char)));
		if (type->t_name)
		{
			strcpy(type->t_name, t_name);
			type->pokemon_count = 0;
			type->ea_me_count = 0;
			type->ea_other_count = 0;
			type->effective_against_me = (Type**) calloc(0,sizeof(Type*));
			type->effective_against_others = (Type**) calloc(0,sizeof(Type*));
			return type;
		}
		else
		{
			printf("Memory Problem\n");
			free(type);
		}
	}
	return NULL;
}


Pokemon* Create_Pokemon(char *p_name, char *species, BiologicalInfo *bio_inf, Type *p_type)
/*
 * This function gets a pointer to bilogical information of pokemon,
 * name of pokemon, and species of pokemon.
 * p_name, and species moved to function after buffer in main.
 */
{
	if ((p_name == NULL) || (bio_inf == NULL) || (species == NULL) || (p_type == NULL))
		return NULL;
	Pokemon* pokemon;
	pokemon = (Pokemon*) calloc(1, sizeof(Pokemon));
	if (pokemon == NULL)
	{
		printf("Memory Problem\n");
	}
	else
	{
		pokemon->p_name = (char*) calloc(strlen(p_name)+1, sizeof(char));
		if (pokemon->p_name == NULL)
		{
			printf("Memory Problem\n");
			free(pokemon);
			return NULL;
		}
		pokemon->species = (char*) calloc(strlen(species)+1, sizeof(char));
		if(pokemon->species == NULL)
		{
			printf("Memory Problem\n");
			free(pokemon->p_name);
			free(pokemon);
			return NULL;
		}

		strcpy(pokemon->p_name, p_name);
		strcpy(pokemon->species, species);
		pokemon->pokemon_info = bio_inf;
		pokemon->pokemon_type = p_type;
		return pokemon;

	}
	return NULL;
}

status Print_Pokemon(Pokemon *pokemon)
/**
 * This function pronts pokemon details
 */
{	if ((pokemon == NULL) || (pokemon->p_name == NULL) || (pokemon->species == NULL))
		return failure;
	// name
	printf("%s :\n", pokemon->p_name);
	// species and type
	printf("%s, %s Type.\n", pokemon->species, pokemon->pokemon_type->t_name);
	// bio info
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n",
			pokemon->pokemon_info->height,
			pokemon->pokemon_info->weight,
			pokemon->pokemon_info->attack);
	return success;

}

status Add_Me(Type* poke_A, Type* poke_B)
/*
 * This function add poke_B to effective agains me list of poke_A.
 */
{
	// if pokeA and pokeB are the same (same pointer, do nothing
	// else -> we check if pointer exist in list according its pointer
	// if exist, do nothing
	// else -> reallcoate memory
	status stat;
	stat = failure;

	if ((poke_A == NULL) || (poke_B==NULL)) // check validity of pointers
		return stat;
	// list is empty. we add the pirst pokemon type
	if (poke_A->ea_me_count == 0)
	{
		poke_A->effective_against_me =
				(Type**) realloc(poke_A->effective_against_me, sizeof(Type*));
		if (poke_A->effective_against_me == NULL)
		{
			stat = memofail;
			return stat;
		}

		else
		{
			poke_A->ea_me_count++;
			poke_A->effective_against_me[0] = poke_B;
			stat = success;
		}
	}
	else
	{
		// list is not empty. need to check if pokimon already exist
		int i;

		for (i = 0; i<poke_A->ea_me_count; i++)
			if (poke_A->effective_against_me[i] == poke_B) return stat;

		if (stat == failure)
		{
			poke_A->ea_me_count++;
			poke_A->effective_against_me =
				(Type**) realloc(poke_A->effective_against_me,
						poke_A->ea_me_count*sizeof(Type*));
			if ((poke_A->effective_against_me) == NULL)
			{
				stat = memofail;
				return stat;
			}
			else
			{
				poke_A->effective_against_me[poke_A->ea_me_count-1] = poke_B;
				stat = success;
			}
		}
	}

	return stat;
}

status Add_Others(Type* poke_A, Type* poke_B)
/*
 * This function add poke_B to effective agains others list of poke_A.
 */
{
	// if pokeA and pokeB are the same (same pointer, do nothing_)
	// else -> we check if pointer exist in list according its pointer
	// if exist, do nothing
	// else -> reallcoate memory
	status stat;
	stat = failure;

	if ((poke_A == NULL) || (poke_B==NULL)) // check vlidity of pointers
		return stat;


	// list is empty
	if (poke_A->effective_against_others == 0)
	{
		poke_A->effective_against_others =
				(Type**) realloc(poke_A->effective_against_others, sizeof(Type*));
		if (poke_A->effective_against_others == NULL)
		{
			printf("Memory Problem\n");
			stat = memofail;
			return stat;
		}
		else
		{
			poke_A->ea_other_count++;
			poke_A->effective_against_others[0] = poke_B;
			stat = success;
		}
	}
	else
	{
		// list is not empty. need to check if pokimon already exist
		int i;
		for (i = 0; i<poke_A->ea_other_count; i++)
			if (poke_A->effective_against_others[i] == poke_B) return stat;

		if (stat == failure)
		{
			poke_A->ea_other_count++;
			poke_A->effective_against_others =
				(Type**) realloc(poke_A->effective_against_others,
						poke_A->ea_other_count*sizeof(Type*));
			if ((poke_A->effective_against_others) == NULL)
			{
				printf("Memory Problem\n");
				stat = memofail;
				return stat;
			}
			else
			{
				poke_A->effective_against_others[poke_A->ea_other_count-1] = poke_B;
				stat = success;
			}
		}
	}
	return stat;
}


status Print_Type(Type* type)
/*
 * This function print information about pokemon type.
 */
{
	status stat;
	stat = failure;
	if(!(type->t_name==NULL)) //TYPE DELETED
	{
		if ((type->ea_me_count == 0)&&(type->ea_other_count == 0))
		{
			printf("Type %s -- %d pokemons\n\n", type->t_name, type->pokemon_count);
		}
		else
		{
			printf("Type %s -- %d pokemons\n", type->t_name, type->pokemon_count);
			if (type->ea_me_count > 0)
			{
				printf("\tThese types are super-effective against %s:", type->t_name);
				int i;
				for (i=0; i < type->ea_me_count; i++)
				{
					if (i == 0)
					{
						if (type->ea_me_count == 1)// only one type
						{
							if (type->ea_other_count == 0)
								printf("%s\n\n", type->effective_against_me[i]->t_name);
							else
								printf("%s\n", type->effective_against_me[i]->t_name);
						}

						else // first type
							printf("%s", type->effective_against_me[i]->t_name);

					}
					else
					{
						if (i == type->ea_me_count - 1)
						{
							if (type->ea_other_count == 0)
								printf(" ,%s\n\n", type->effective_against_me[i]->t_name);
							else
								printf(" ,%s\n", type->effective_against_me[i]->t_name);
						}

						else
							printf(" ,%s", type->effective_against_me[i]->t_name);
					}

				}
			}
			if (type->ea_other_count > 0)
			{
				int i;
				printf("\t%s moves are super-effective against:", type->t_name);
				for (i=0; i < type->ea_other_count; i++)
				{
					if (i == 0)
					{
						if (type->ea_other_count == 1)
							printf("%s\n\n", type->effective_against_others[i]->t_name);
						else
							printf("%s", type->effective_against_others[i]->t_name);
					}

					else
					{
						if (i + 1 == type->ea_other_count)
							printf(" ,%s\n\n", type->effective_against_others[i]->t_name);
						else
							printf(" ,%s", type->effective_against_others[i]->t_name);
					}
				}
			}
		}
		stat = success;

	}
	return stat;
}




status Delete_Me(Type* type_pA, char* name_pB)
/*
 * This function get name of Pokemon. If pokemonB is effective against pokemon A,
 * so pokemonB is deleted.
 */
{
	if ((type_pA == NULL) || (name_pB==NULL)) // check validity of pinters
		return failure;

	// runing all over effective against:
	int i;
	for (i = 0; i<type_pA->ea_me_count; i++)
	{
		if (strcmp(type_pA->effective_against_me[i]->t_name, name_pB) == 0)
		{
			type_pA->ea_me_count--;
			int j;
			for (j = i; j < type_pA->ea_me_count; j++) // shift other type in list
				type_pA->effective_against_me[j] = type_pA->effective_against_me[j+1];
			type_pA->effective_against_me[j] = NULL; // fake
			type_pA->effective_against_me = (Type**) realloc (type_pA->effective_against_me,
					type_pA->ea_me_count * sizeof(Type*));
			if (type_pA->ea_me_count != 0)
			{
				if (type_pA->effective_against_me == NULL) // memoey allocation failed
				{
					printf("Memory Problem\n");
					return memofail;
				}
			}

			return success;
		}
	}
	return failure;
}

status Delete_Others(Type* type_pA, char* name_pB)
/*
 * This function get name of Pokemon. If pokemonB is effective against pokemon A,
 * so pokemonB is deleted.
 */
{
	if ((type_pA == NULL) || (name_pB==NULL)) // check validity of pointers
		return failure;

	int i;
		for (i = 0; i<type_pA->ea_other_count; i++)
		{
			if (strcmp(type_pA->effective_against_others[i]->t_name, name_pB) == 0)
			{
				//Type *remove = type_pA->effective_against_me[i]; // what remove
				type_pA->ea_other_count--;
				int j;
				for (j = i; j < type_pA->ea_other_count; j++)
				{
					type_pA->effective_against_others[j] = type_pA->effective_against_others[j+1];
				}
				//type_pA->effective_against_others[j] = NULL; // fake
				type_pA->effective_against_others = (Type**) realloc (type_pA->effective_against_others,
						type_pA->ea_other_count * sizeof(Type*));
				if (type_pA->ea_other_count != 0)
				{
					if (type_pA->effective_against_others == NULL) // memoey allocation failed
					{
						printf("Memory Problem\n");
						return memofail;
					}
				}

				return success;
			}
		}
		return failure;
}

void Delete_BilogicalInfo(BiologicalInfo* bi)
/*
 * This function get pointer to biological info and delete.
 */
{
	free(bi);
	bi = NULL;
}

void Delete_Type(Type* t)
/*
 * This function delte type of pokemon
 */
{
	free(t->t_name);
	t->t_name = NULL;
	free(t->effective_against_me);
	t->effective_against_me = NULL;
	free(t->effective_against_others);
	t->effective_against_others = NULL;
	free(t);
	t = NULL;
}


status Delete_Pokemon(Pokemon* p)
/*
 * This function get pointer to pokemon, and delete him.
*/
{
	free(p->p_name);
	p->p_name=NULL;
	free(p->species);
	p->species=NULL;
	Delete_BilogicalInfo(p->pokemon_info);
	p->pokemon_type = NULL;
	free(p);
	p=NULL;
	return success;
}


