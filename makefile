PokemonsBattles:BattleByCategory.o LinkedList.o Pokemon.o MaxHeap.o MainSecond.o
	gcc LinkedList.o MaxHeap.o BattleByCategory.o Pokemon.o MainSecond.o -o PokemonsBattles
BattleByCategory.o: BattleByCategory.c BattleByCategory.h Defs.h LinkedList.h MaxHeap.h
	gcc -g -c BattleByCategory.c
LinkedList.o:LinkedList.c LinkedList.h Defs.h
	gcc -g -c LinkedList.c
Pokemon.o:Pokemon.c Pokemon.h Defs.h
	gcc -g -c Pokemon.c
MainSecond.o:MainSecond.c BattleByCategory.h Defs.h LinkedList.h MaxHeap.h Pokemon.h
	gcc -g -c MainSecond.c
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -g -c MaxHeap.c
clean:
	rm -f *.o PokemonBattles
