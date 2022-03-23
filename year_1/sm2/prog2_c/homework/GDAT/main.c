#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericSortedLinkedList.h"

typedef struct line_t
{
    int priority;
    int func_num;
    char str[50];
} line;
line *readLine(FILE *input);
/*          FUNCS 123                 */
void func1(char *s)
{
    printf("Func1:%s\n", s);
}
void func2(char *s)
{
    printf("Func2:%s\n", s);
}
void func3(char *s)
{
    printf("Func3:%s\n", s);
}
/*funs for check only:*/
result add_print_job(database_ptr data, FILE *input);
comp_res mashve(elem first1, elem second1);
void freedomFunc(elem num);
elem copy_elem(elem element);
elem mem_al();
/*struct*/

int main(int argc, char *argv[])
{
    database_ptr data = create(mashve, freedomFunc, copy_elem, mem_al);
    FILE *input = fopen(argv[1], "r");
    // FILE *input = fopen("input.txt", "r");
    while (1)
    {
        if (add_print_job(data, input) != fail)
            printf("\nprint job successed");

        else if (sort(data))
        {
            printf("\n\tprintjob done");
            line *temp1 = pop(data, NULL);
            printf("\nMAIN.SORT.pop line= %s", temp1->str);
            line *temp2 = pop(data, temp1);
            printf("\nMAIN.SORT.pop line= %s", temp2->str);
            temp1 = pop(data, temp2);
            printf("\nMAIN.SORT.pop line= %s", temp2->str);
        }
    }

    printf("\nMAIN FINISH");
}
comp_res mashve(elem first1, elem second1)
{
    printf("\n\tadd of first1=%d, add of sceond1= %d",first1,second1);
    printf("\nIN MASHVE");
    line *first = (line *)first1;
    line *second = (line *)second1;
    printf("\nfirst prio= %c sec prio= %c",first->priority,second->priority);
    if (first->priority < second->priority)
    {
        printf("\nMASHVE1 %d", first->priority);
        return left;
    }
    else if (first->priority > second->priority)
    {
        printf("\nMASHVE2 %d", second->priority);
        return right;
    }
    else
    {
        printf("\nMASHVE3 %d", first->priority);
        return same;
    }
    printf("\nsomething");
}
void freedomFunc(elem num)
{
    printf("fghdf");
}
elem copy_elem(elem element1)
{
    line *newElem;
    line *element = (line *)element1;
    newElem = (line *)malloc(sizeof(line));
    newElem->func_num = element->func_num;
    newElem->priority = element->priority;
    strcpy(newElem->str, element->str);
    printf("\nelement& = %s \nnewElem& = %s", element->str, newElem->str);
    return newElem;
}

elem mem_al()
{
    line *element = (line *)malloc(sizeof(line));
    return (elem)element;
}

line *readLine(FILE *input)
{
    line *newLine = (line *)mem_al();
    char temp[50] = {'\0'};
    int i = 0, num = 0;
    if (fscanf(input, "%[^\n]\n", temp) != '\n')
    {
        if (temp[0] != '<')
            return NULL;
        else
            newLine->func_num = temp[5] - 48;
        for (int j = 9; temp[j] != '>'; j++)
        {
            num = j;
            newLine->str[j - 9] = temp[j];
        }
        newLine->str[num + 1] = '\0';
        printf("\nREAD LINE= %s", newLine->str);
        newLine->priority = temp[num + 4] - 48;
        return newLine;
    }
}
result add_print_job(database_ptr data, FILE *input)
{
    line *newLine;
    newLine = readLine(input);
    if (newLine == NULL)
        return fail;
    printf("\nadd print= %s", newLine->str);

    if (new_elem(data, (elem)newLine))
    {
        printf("\nINSIDE %s prio %d func %d", newLine->str, newLine->priority, newLine->func_num);
        return success;
    }
}
