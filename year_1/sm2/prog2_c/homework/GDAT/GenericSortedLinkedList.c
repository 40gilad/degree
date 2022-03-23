#include <stdio.h>
#include <stdlib.h>
#include "GenericSortedLinkedList.h"
struct list_t
{
    elem element;
    list_ptr next;
};
struct database_t
{
    list_ptr head;
    comp compare;
    free_func freedom;
    cpy_func copy;
    memAllocate mem;
};
database_ptr create(comp func, free_func fr, cpy_func copy, memAllocate mem_func) //creat new struct and returns add of struct
{
    database_ptr d;
    list_ptr l;
    l = (list_ptr)malloc(sizeof(struct list_t));
    d = (database_ptr)malloc(sizeof(struct database_t));
    d->head = l;
    d->head->next = NULL;
    d->head->element = NULL;
    d->compare = func;
    d->freedom = fr;
    d->copy = copy;
    d->mem = mem_func;
    return d;
}
result new_elem(database_ptr d, elem el) //new elem insert

{
    list_ptr new_el;
    if (d->mem(new_el) == NULL)
        return fail;
    new_el->element = d->copy(el);
    printf("\nafter copy");
    if (new_el == NULL)
    {
        printf("\nNEW ELEM fail");
        return fail;
    }
    if (d->head->element == NULL)
    { //first one in list is empty
        printf("\nnew_elem func,head.element=null");

        d->head->element = new_el;
        printf("\n\nHERE: s");
        return success;
    }
    printf("\nsdgbbdfg");
    if (d->head->element != NULL)
    {
        printf("\nNEW ELEM ELSE");
        new_el->next = d->head;
        d->head = new_el;
        // printf("\nnew_elem func,ELSE");
        // list_ptr temp_head = d->head;
        // int i = 1; //fur check only
        // while (1)
        // {
        //     printf("\nnew_elem func,ELSE->while, run num %d", i++);
        //     if(d->head->next==NULL){
        //         d->head->element = new_el;
        //         break;
        //     }
        //     d->head = d->head->next;
        // }
        // printf("\nout of loop");
        // d->head = temp_head;
        while (d->head)
        {
            printf("\nIN INITILIZE, add of head.next=%d", d->head->next);
            d->head = d->head->next;
        }
        // d->head = temp_head;
        return success;
    }
    return fail;
}
void destroy(database_ptr d)
{
    list_ptr curr = d->head->next;
    while (d->head->next)
    {
        curr = d->head->next;
        d->head->next = curr->next;
        d->freedom(curr->element);
        free(curr);
    }
    d->freedom(d->head->element);
    free(d->head);
}
elem pop(database_ptr d, elem el)
{
    int i = 1;
    elem temp; // temp is for return value
    list_ptr tempHead = d->head;
    if (el == NULL)
    {
        printf("\nPOP el=null");
        temp = d->head->element;
        return temp;
    }

    if (d->head->element == NULL)
    {
        printf("\n POP  ERROR");
        return NULL;
    }
    while (d->head->next)
    {
        i = d->compare(d->head->element, el);
        if (i == 2)
        {
            printf("\n%d", i);
            temp = d->copy(d->head->next->element);
            d->head = tempHead;
            return temp;
        }
        // d->head = d->head->next;
        // printf("\nPOP: ELEMENTS ARE SAME i= %d", i++);
        // if (d->head->next == NULL)
        //     return NULL;
    }
    temp = d->copy(d->head->next->element);
    d->head = tempHead;
    printf("\nPOP SUCCESS");
    return temp;
}
database_ptr copyDATA(database_ptr d)
{
    database_ptr temp = (database_ptr)malloc(sizeof(database_ptr));
    temp->mem = d->mem;
    temp->freedom = d->freedom;
    temp->copy = d->copy;
    temp->compare = d->compare;
    return temp;
}
result sort(database_ptr d) //if in compare_func a<b => a is higher priority
{
    database_ptr temp_dataB = NULL;
    temp_dataB = copyDATA(d);
    printf("\nSORT copied \n\ttemp add=%d \n\t d add= %d", temp_dataB->head, d->head);

    // list_ptr prior(database_ptr d)

    list_ptr temp, curr1 = d->head, curr2 = d->head->next, tempHead = d->head, winner, tempDBhead = temp_dataB->head;
    comp_res result;
    while (d->head)
    {
        printf("\n\tSORT: WHILE 1");
        d->head = tempHead;
        curr1 = d->head;
        curr2 = d->head->next;
        while (curr2 != NULL || curr1 != NULL)
        {
            printf("\n\tWHILE.WHILE2");
            printf("\n\tadd of cur1=%d add of curr2= %d", curr1, curr2);
            result = d->compare((elem)curr1, (elem)curr2);
            if (result == left || result == same)
            {
                printf("\nleft/same");
                winner = curr1;
                curr2 = curr2->next;
            }
            else
            {
                printf("\nright");
                winner = curr2;
                curr1 = curr1->next;
            }
        }
        temp_dataB->head = d->copy(winner);
        temp_dataB->head = temp_dataB->head->next;
        d->head = tempHead;
        while (d->head->next != winner)
        {
            printf("\nsomething");
            d->head = d->head->next;
        }
        temp = d->head->next->next;
        free(d->head->next);
        d->head->next = temp;
        return success;
    }
}
