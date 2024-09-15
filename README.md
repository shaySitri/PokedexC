# Pokemon Battle System and Pokedex

## 📜 Overview

This project is a **Pokemon Battle System** and a **Pokedex** built using C. The Pokedex stores and manages information about various Pokemon species and their types, while the battle system allows for Pokemon battles based on type effectiveness and attack strength.

The project is divided into two parts:
1. **Pokedex Creation**: Manage Pokemon types and species using dynamic memory allocation.
2. **Battle System**: Simulate Pokemon battles using a generic Abstract Data Type (ADT).

## 📂 Project Structure

### Pokemon Types
Each type (e.g., Fire, Water) has:
- A name
- A list of types it's effective against
- A list of types that are effective against it

### Pokemon
Each Pokemon has:
- A species (e.g., Pikachu)
- Biological attributes (height, weight, attack)
- A type (e.g., Electric)

### Battle System
The battle system simulates fights based on:
- Type effectiveness (e.g., Water beats Fire)
- Attack strength of the Pokemon

## 🚀 How to Run

To execute the program, run the following command:

```bash
./PokemonsBattles <numberOfTypes> <capacityInType> <configurationFile>
```

### Parameters:
- `numberOfTypes`: Number of Pokemon types (e.g., 3)
- `capacityInType`: Maximum number of Pokemon per type (e.g., 20)
- `configurationFile`: Path to the configuration file containing the Pokemon and type data.

### Example Command:
```bash
./PokemonsBattles 3 20 config.txt
```

## 📝 Configuration File Format

The configuration file has two sections:

### Types Section:
```text
Types
Fire,Water,Electric
Fire effective-against-me: Water
Fire effective-against-other: Grass
Water effective-against-other: Fire
```

### Pokemon Section:
```text
Pokemons
Pikachu,MousePokemon,0.4,6,55,Electric
Charmander,LizardPokemon,0.6,8.5,52,Fire
Squirtle,TinyTurtlePokemon,0.5,9,48,Water
```

## 💻 Main Menu

Once the program is running, you will be prompted with the following options:

1. **Print all Pokemon by types**
2. **Print all Pokemon types**
3. **Insert Pokemon into battles**
4. **Remove strongest Pokemon by type**
5. **Fight**
6. **Exit**

### Example Output:
```bash
Please choose one of the following numbers:
1 : Print all Pokemon by types
2 : Print all Pokemon types
3 : Insert Pokemon into battles
4 : Remove strongest Pokemon by type
5 : Fight
6 : Exit
```

## 🛠️ Memory Management

- The system dynamically allocates memory for Pokemon and types.
- Proper cleanup is done to avoid memory leaks.

## 🔧 Compilation

To compile the project, use the provided `Makefile`:

```bash
make
```

This will generate the executable file `PokemonsBattles`.

## 📚 Dependencies

- **C Compiler**: Ensure you have a C compiler like GCC installed to compile and run the project.


