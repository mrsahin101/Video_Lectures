# Syntax and Structure of C - Simply C
- For embedded systems initializing the code(initializing variables) done in assembly file.
- Typedef creates alias.
- Local variables always takes precedence over global variables.
- #define commands handled by pre-processor. 
``` C
#define x 5
#define x 10
/* x defined as 10. Its overwritten previous define*/
```
- There are 4 variable classes.
    1. **static**
    2. **Automatic** 
    3. **external**
    4. **register** : No need for embedded field.

- Difference between static and global variable is, static variable is only valid for created function. But it has fixed memory location like global variable.

- Any variable created inside function are **automatic**. But if we specify its either external or static then it changes. But by default its automatic. and destroyed when function finish execution.
- Static functions are **only** accessible where they are defined.
- When we use **.h** files, we can use for function prototypes and extern variables to include from other files.
- To create pointer type :
``` C
typedef int *intPtr; // Create Type
intPtr p; // Declare int pointer
```

## Structures :
``` C
/* Syntax of structure */
struct structName
{
    type1 memberName1;
    typen memberNamen;
}varName1, varNamen;
/* or like this */
struct structName varName1, ... , varNamen;
```
- With structure we can use varName1 = varNamen;. This copies varNamen structure all fields to varName1 structure.

``` C
/* Typedef example : */
typedef struct structTagoptional
{
    type1 memberName1;
    type2 memberName2;
}typeName;
/* Real example */
typedef struct
{
    float re;
    float im;
}complex;
```

- Bit fields are members of structures that occupy a specified number of adjacent bits. Compilers will typically determine the size of the variable that holds the bit field. They have specified bit-width. They are used conjunction with structures to provide bit access to a variable without masking operations

``` C
typedef struct
{
    unsigned int bit0:      1;
    unsigned int bit1to3:   3;
    unsigned int bit4:      1;
    unsigned int bit5:      1;
    unsigned int bit6to7:   2;
}byteBits;
```
``` C
union
{
    unsigned int u16ADRead;
    struct
    {
        unsigned char u8ADReadLow;
        unsigned char u8ADReadHigh;
    }STRUCT_ADReadMembers;
}UNION_ADRead;
```
- Size of pointers dictated by architecture working with.
- **->** notation is used with structure pointers.
- Structures are accesed by dot notation.

- Function pointers provides flexible way to call a function.
- Double pointers can be usefull sometimes.

### Simple Linked-List
``` C
struct Node
{
    int data;
    struct Node* next;
};
```

## CALLBACKS
- Callbacks are very usefull when dealing with hardware.
- Callback functions doesnt have return type and parameters
