#ifndef GENERICSORTEDDLINKEDLIST_H
#define GENERICSORTEDDLINKEDLIST_H
typedef void* elem;
typedef enum
{
    fail,
    success
} result;
typedef enum
{
    left, 
    right, 
    same
}comp_res;
// typedef struct list_t* list;//"list" is the pointer to first elem of the list
typedef struct database_t *database_ptr; //"list" means pointer to the struct
typedef struct list_t *list_ptr;
/********FUNCS THAT BUILT BY USER:    **********************/

typedef comp_res (*comp)(elem,elem); //compare elems SUCCESS=left one is higher priority or the same, FAIL= right one
typedef void (*free_func)(elem);//func addres to free elemnts-BUILD BY USER
typedef elem (*cpy_func)(elem); /*func that gets struct and element to sort. SORT=ADD NEW ELEM - BUILD BY USER*/ 
typedef elem (*memAllocate)(elem);// memory allocate made by user and returns to adt to insert
/******** FUNCS IN C FILE :   *************/
database_ptr create(comp,free_func,cpy_func,memAllocate);//creat new struct and returns add of struct
result new_elem(database_ptr, elem); //new elem=insert
void destroy(database_ptr); // "FCLOSE"- free database
result sort (database_ptr);
elem pop(database_ptr, elem);
database_ptr copyDATA(database_ptr);
#endif