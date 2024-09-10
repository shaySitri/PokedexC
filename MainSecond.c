#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "Defs.h"
#include "Pokemon.h"

		////////////////////////////////////////////////////////////
		//////////////////////HELPER FUNCTIONS//////////////////////
		////////////////////////////////////////////////////////////


/* EqualPoke - compare between 2 Pokemons according their attack.
 * get - 2 Pokemon pointers
 * return: 0 - p1->attack = p2->attack, 1: p1->attack > p2->attack, other -1.
 */
int EqualPoke(Pokemon* p1, Pokemon* p2)
{

	if ((p1 == NULL) || (p2 == NULL)) return -1000;
	if (p1->pokemon_info->attack == p2->pokemon_info->attack)
		return 0;
	if (p1->pokemon_info->attack > p2->pokemon_info->attack)
		return 1;
	return -1;
}

/* CopyPokemon - deep copy Pokemon
 * get - 1 Pokemon pointe
 * return: Null if allocation failed. Other - new pointer to another Pokemon with same details like
 * pokemon sent by user.
 */
Pokemon* CopyPokemon(Pokemon* p)
{
	if (p == NULL) return NULL;
	Pokemon* newPok = (Pokemon*) malloc(sizeof(Pokemon));
	if (newPok == NULL) return NULL; // allocation failed
	newPok->p_name = (char*) malloc(sizeof(char)*(strlen(p->p_name) +1));
	if (newPok->p_name == NULL)
	{
		free(newPok);
		return NULL;
	}
	newPok->species = (char*) malloc(sizeof(char)*(strlen(p->species) +1));
	if (newPok->species == NULL)
	{
		free(newPok->p_name);
		free(newPok);
		return NULL;
	}
	strcpy(newPok->p_name, p->p_name);
	strcpy(newPok->species, p->species);

	BiologicalInfo* newBio = CopyBioInfo(p->pokemon_info);
	if (newBio == NULL)
	{
		free(newPok->species);
		free(newPok->p_name);
		free(newPok);
		return NULL;
	}

	newPok->pokemon_type = p->pokemon_type;
	newPok->pokemon_info = newBio;
	return newPok;
}

/* CopyBioInfo - deep copy Biological Information
 * get - 1 Pokemon bio inforamation
 * return: Null if allocation failed. Other - new pointer to another Bio Info with same details like
 * bio sent by user.
 */
BiologicalInfo* CopyBioInfo(BiologicalInfo* bi)
{
	if (bi == NULL) return NULL;
	BiologicalInfo* newBI = (BiologicalInfo*) malloc(sizeof(BiologicalInfo));
	newBI->attack = bi->attack;
	newBI->height = bi->height;
	newBI->weight = bi->weight;
	return newBI;
}

/* checkEffectiveAgainstMe - check if type2 is in "effective against me" list of type1.
 * get - 2 types pointers
 * return: 1 if t2 effective against t1, 1 otherwise.
 */
int checkEffectiveAgainstMe(Type* t1, Type* t2)
{
	// check if type 2 effective against type 1
	if ((t1 == NULL) || (t2 == NULL)) return -1;
	int i;
	for (i=0; i<t1->ea_me_count; i++)
	{
		if (t1->effective_against_me[i] == t2)
			return 1;
	}

	return 0;
}

/* getAttack - calculate p1 and p2 new attack for fight between them.
 * we need to supply this function for use BattleByCategory
 * get - 2 types pointers, a1, a2 - new attacks of pokemons.
 * return: a1-a2 - check who winner.
 */
int getAttack(Pokemon* p1, Pokemon* p2, int* a1, int* a2)
{
	if ((p1 == NULL) || (p2 == NULL)) return -1000;
	*a1 = p1->pokemon_info->attack;
	*a2 = p2->pokemon_info->attack;
	if (p1->pokemon_type == p2->pokemon_type)
		return (p1->pokemon_info->attack - p2->pokemon_info->attack);

	if (checkEffectiveAgainstMe(p1->pokemon_type, p2->pokemon_type) == 1)
		*a1 = *a1 - 10;


	if (checkEffectiveAgainstMe(p2->pokemon_type, p1->pokemon_type) == 1)
		*a2 = *a2 - 10;

	return (*a1 - *a2);

}

/* getTypeNameOfPok - return Type Name of Pokemon
 * we need to supply this function for use BattleByCategory (get category function)
 * get - pointer of pokemon
 * return: type name of pokemon
 */
char* getTypeNameOfPok(Pokemon* p)
{
	if (p == NULL)
		return NULL;
	else
		return p->pokemon_type->t_name;
}


/* searchType - search type by name in list of types
 * get - list of type, type name to search, and list of type length.
 * return: type itself if found, NULL if not found.
 */
Type* searchType(Type* type_lst[], char* typeName, int typeNum)
{
	if ((type_lst == NULL) || (typeName == NULL))
		return NULL;
	int i;
	for (i = 0; i < typeNum; i++)
	{
		if (strcmp(type_lst[i]->t_name, typeName) == 0)
			return type_lst[i];
	}
	return NULL;
}


/* closeProg - close program in most useful way.
 * get - list of type, battle and list of type length.
 * return: NONE. cleaning all memory used on program.
 */
void closeProg(Type* type_lst[], Battle b, int tNum)
{
	// clear types fron memory
	int i;
	for (i = 0; i < tNum; i ++)
	{
		if (type_lst[i] != NULL)
			Delete_Type(type_lst[i]);
		type_lst[i] = NULL;
	}
	if (b != NULL)
	{
		destroyBattleByCategory(b);
		b = NULL;
	}

}

/* createPokemonUser - this function get Pokemon details from user and create new Pokemon.
 * get - Pokemon details
 * return new Pokemon
 */
Pokemon* createPokemonUser(char* pN, char* sN, int attack, double we, double he, Type* type)
{
	printf("Please enter Pokemon name:\n");
	scanf("%s", pN);
	printf("Please enter Pokemon species:\n");
	scanf("%s", sN);
	printf("Please enter Pokemon height:\n");
	scanf("%lf", &he);
	printf("Please enter Pokemon weight:\n");
	scanf("%lf", &we);
	printf("Please enter Pokemon attack:\n");
	scanf("%d", &attack);
	BiologicalInfo* bioInfo = Create_BiologicalInfo(he, we, attack);
	if (bioInfo == NULL)
		return NULL;

	Pokemon* p = Create_Pokemon(pN, sN, bioInfo, type);

	if (p == NULL)
	{
		Delete_BilogicalInfo(bioInfo);
		return NULL;
	}
	return p;
}

int main(int argc, char* argv[])
{
	// pre proccessing configration file
	// reading args

	if (argc < 1)
		return 0;
	char *endptr;
	long capicity;
	capicity =  strtol(argv[2],&endptr, 10);
	long numOfTypes = strtol(argv[1],&endptr, 10);
	FILE *fp;
	fp = fopen(argv[3],"r");
	if (fp == NULL)
		return 0;
	Type* type_lst[numOfTypes];
	int tnn = 0;
	char prev[300] = "none";
	char str[300];
	char categories[300];
	Battle b = NULL;
	while((fscanf(fp, "%s" , str)!= EOF ))
	{
		////////////////////////////////////////////////////////////
		////////////////////////INSERT TYPES////////////////////////
		////////////////////////////////////////////////////////////
		if ((strcmp(str, "Types")) == 0)
		{
			strcpy(prev, str);
			continue;
		}

		else
		{
			if ((strcmp(prev, "Types")) == 0)
			{
				// second line- type names, "," seperate between.
				// each name - insert to type;
				char* name;
				strcpy(categories, str);
				name = strtok(str, ","); // strtok return pointer
				// first all types are initiate with its names.
				while ((name != NULL)&&(tnn < numOfTypes))
				{
					type_lst[tnn] = Create_Type(name);
					if (type_lst[tnn] == NULL)
					{
						printf("No memory available.\n");
						closeProg(type_lst,b, tnn);
						return 0;
					}
					name = strtok(NULL, ",");
					tnn++;
				}
				// move step- Add to list of TypeA;
				strcpy(prev, "TypeA");
				continue;
			}
			Type* Add_typeA; // assumption - VALID INPUT!
			if ((strcmp(prev, "TypeA")) == 0)
			{
				// next step - initiate list "effective against"
				char typeAName[300];
				sscanf(str, "%s", typeAName);
				// assumption - configration file has valid input only.
				// even if there is NULL in add-TypeA, case is handles in ADD function
				Add_typeA = searchType(type_lst, typeAName, numOfTypes);
				strcpy(prev, "TypeB");
			}
			else
			{
				if ((strcmp(prev, "TypeB")) == 0) // looks for types B, and add them.
				{
					char* typeBName;
					status mem_stat;
					if (strstr(str,"me")) // against me
					{
						typeBName = strtok(str, ":");
						typeBName = strtok(NULL, ",");
						while(typeBName != NULL)
						{
							Type* Add_typeB = NULL;
							Add_typeB = searchType(type_lst, typeBName, numOfTypes);
							mem_stat = Add_Me(Add_typeA, Add_typeB);
							if (mem_stat == memofail)
							{
								// the only thing should be lost in memeory is "effective against me" list of typeA.
								printf("No memory available.\n");
								closeProg(type_lst,b, tnn);
								return 0;
							}
							typeBName = strtok(NULL, ",");
						}
					}

					if (strstr(str,"other")) // against me
					{
						typeBName = strtok(str, ":");
						typeBName = strtok(NULL, ",");
						while(typeBName != NULL)
						{
							Type* Add_typeB = NULL;
							Add_typeB = searchType(type_lst, typeBName, numOfTypes);
							mem_stat = Add_Others(Add_typeA, Add_typeB);
							if (mem_stat == memofail)
							{
								// the only thing should be lost in memeory is
								// "effective against others" list of typeA.
								printf("No memory available.\n");
								closeProg(type_lst,b, tnn);
								return 0;
							}
							typeBName = strtok(NULL, ",");
						}
					}
					strcpy(prev, "TypeA");
					continue;
				}
			}
		}

		////////////////////////////////////////////////////////////
		////////////////////////INSERT POKEMONS/////////////////////
		////////////////////////////////////////////////////////////
		if ((strcmp(str, "Pokemons")) == 0)

			strcpy(prev, str);

		else
		{

			if ((strcmp(prev, "Pokemons")) == 0)
			{
				char cur_poke_name[300];
				char speices[300];
				char cur_type_name[300];
				double height, weight;
				int attack;
				sscanf(str, "%[^,],%[^,],%lf,%lf,%d,%[^,]",
						cur_poke_name, speices, &height, &weight, &attack, cur_type_name);

				BiologicalInfo* bioInfo = Create_BiologicalInfo(height, weight, attack);
				if (bioInfo == NULL) // failed to allocate memory.
				{
					printf("No memory available.\n");
					closeProg(type_lst,b, tnn);
					return 0;
				}
				// find type:
				Type* poke_type = searchType(type_lst, cur_type_name, numOfTypes);
				poke_type->pokemon_count++;
				Pokemon* p = Create_Pokemon(cur_poke_name, speices, bioInfo, poke_type);

				if (p == NULL)
				{
					Delete_BilogicalInfo(bioInfo);
					printf("No memory available.\n");
					closeProg(type_lst,b, tnn);
					return 0;
				}

				insertObject(b,p);
				Delete_Pokemon(p);

			}
		}
		if (b == NULL)
		{
			b = createBattleByCategory(capicity, numOfTypes, categories,
								(equalFunction)EqualPoke,
								(copyFunction)CopyPokemon,
								(freeFunction)Delete_Pokemon,
								(getCategoryFunction)getTypeNameOfPok,
								(getAttackFunction)getAttack,
								(printFunction)Print_Pokemon);
			if (b == NULL)
			{
				printf("No memory available.\n");
				closeProg(type_lst,b, tnn);
				return 0;
			}
		}


	}
	fclose(fp);
	fp = NULL;// pre proccessong file done.

	////////////////////////////////////////////////////////////
	////////////////////////MENU////////////////////////////////
	////////////////////////////////////////////////////////////
	char ch;
	char pokeType[300]; // initial value
	char pokeName[300];
	char pokeSpec[300];
	double pokHeight = 0;
	double pokWeight = 0;
	int pokAttack = 0;
	Type *pokeT=NULL;
	status stat;

	//ch = "1";
	int x;
	ch = '1';
	while (ch != 6)
	{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");
		scanf(" %c", &ch);
		//ch = strtok(ch, "\n");
		switch(ch)
		{

			//case1: Print all Pokemons
			case '1':	displayObjectsByCategories(b);
						break;
			//case2: Print all Pokemons types
			case '2':	for (x=0; x<tnn; x++) Print_Type(type_lst[x]);
						break;
			//case3: Insert Pokemon to battles training camp
			case '3':	printf("Please enter Pokemon type name:\n");
						scanf("%s", pokeType);
						pokeT = searchType(type_lst, pokeType, tnn);
						if (pokeT == NULL)
						{
							printf("Type name doesn't exist.\n");
							break;
						}
						else
						{
							if (getNumberOfObjectsInCategory(b, pokeT->t_name) == capicity)
							{
								printf("Type at full capacity.\n");
								break;
							}
							Pokemon* p = createPokemonUser(pokeName, pokeSpec, pokHeight, pokWeight, pokAttack, pokeT);
							if (p == NULL)
							{
								printf("No memory available.\n");
								closeProg(type_lst,b, tnn);
								return 0;
							}

							pokeT->pokemon_count++;
							stat = 	insertObject(b,p);
							if (stat == success)
							{
								printf("The Pokemon was successfully added.\n");
								Print_Pokemon(p);
							}
							else
							{
								printf("No memory available.\n");
								closeProg(type_lst,b, tnn);
								return 0;

							}
							Delete_Pokemon(p);
							pokeT = NULL;
							break;
						}
			//case4: Remove strongest Pokemon by type
			case '4':	printf("Please enter type name:\n");
						scanf("%s", pokeType);
						pokeT = searchType(type_lst, pokeType, tnn);
						if (pokeT == NULL)
						{
							printf("Type name doesn't exist.\n");
							break;
						}
						Pokemon* p = removeMaxByCategory(b, pokeType);
						if (p == NULL)
							printf("There is no Pokemon to remove.\n");
						else
						{
							pokeT->pokemon_count--;
							printf("The strongest Pokemon was removed:\n");
							Print_Pokemon(p);
							Delete_Pokemon(p);
						}
						pokeT = NULL;
						break;
			//case5: Fight
			case '5':	printf("Please enter Pokemon type name:\n");
						scanf("%s", pokeType);
						pokeT = searchType(type_lst, pokeType, tnn);
						if (pokeT == NULL)
						{
							printf("Type name doesn't exist.\n");
							break;
						}
						else
						{
							Pokemon* p = createPokemonUser(pokeName, pokeSpec, pokHeight, pokWeight, pokAttack, pokeT);
							if (p == NULL)
							{
								printf("No memory available.\n");
								closeProg(type_lst,b, tnn);
								return 0;
							}
							printf("You choose to fight with:\n");
							Print_Pokemon(p);

							Pokemon* winner = fight(b,p);

							int pokAmount = 0;
							int i;
							for (i = 0; i<tnn; i++)
								pokAmount = pokAmount + getNumberOfObjectsInCategory(b,type_lst[i]->t_name);

							if (pokAmount == 0)
								// in this case, no pokemon to fight with,
							{
								printf("There are no Pokemons to fight against you.\n");
								Delete_Pokemon(p);
								break;
							}

							if (winner == NULL)
								// in this case, if not exist pokemon to fight with,
							{
								Delete_Pokemon(p);
								printf("No memory available.\n");
								closeProg(type_lst,b, tnn);
								return 0;

							}
							else
							{
								if (p != winner)
								Delete_Pokemon(winner);
							}

							Delete_Pokemon(p);
							break;
						}
						pokeT = NULL;
						break;
			case '6':	closeProg(type_lst,b, tnn);
						printf("All the memory cleaned and the program is safely closed.\n");
						return 0;


			default:	printf("Please choose a valid number.\n");
						break;


		}
	}
}

