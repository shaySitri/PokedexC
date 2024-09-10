#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEFS_H_
#define DEFS_H_

typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure, memofail } status;

typedef void* Element;
typedef void* element;
typedef element (*compareFunction) (element, element);
typedef element(*copyFunction) (element);
typedef status(*freeFunction) (element);
typedef status (*printFunction) (element);
typedef int(*equalFunction) (element, element);
typedef char*(*getCategoryFunction) (element);
typedef int(*getAttackFunction)(element, element, int*, int*);


#endif /* DEFS_H_ */
