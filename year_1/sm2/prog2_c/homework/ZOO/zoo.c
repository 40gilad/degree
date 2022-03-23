#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************ZOO EXERCISE -LINKED LIST- BY GILAD MEIR, SHENKAR, YEAR A, SM B, SOFT.ENGE*********/

#define NAME_SIZE 20 /*max size of name*/

/******************************* STRUCTURES **************************/
typedef struct animal_item
{
    char animal_id[NAME_SIZE];
    char name[NAME_SIZE];
    int weight;
    int age;
    struct animal_item *next_animal;
} animal;

typedef struct animal_species_item
{
    char kind[NAME_SIZE];
    int free_space;
    struct animal_species_item *next_specie;
    animal *in_dep;
    animal *waiting;
} spice;

/******************************* FUNCTIONS ***************************/

int isNumber(char *num)//check that input include numbers only
{

    int zevel = 0, in = 1, numsize = 0;
    for (int i = 0; num[i] != '\0'; i++)
    {
        numsize = i;
    }
    numsize++;
    while (in)
    {
        for (int i = 0; i < numsize; i++)
        {
            if (num[i] < 58 && num[i] > 47) //asscii of num 0-9
            {
                zevel *= 10;
                zevel += num[i] - 48;
            }
            else
                return 0;
        }
        return zevel;
    }
}
animal *find_animal(char *an_2rem, spice *department)//find animal from stdin
{
    spice *dep = department;
    while (dep->in_dep->name)
    {
        if (stricmp(an_2rem, dep->in_dep->name) == 0)
        { //means that theyr equal

            return dep->in_dep;
        }
        else
            dep->in_dep = dep->in_dep->next_animal;
    }
    return NULL;
}
void stop_waiting(spice *dep)//transfer from weiting list to dep if needed
{ 

    animal *temp_an;
    if (dep->waiting != NULL) //transfer from waiting to department
    {
        temp_an = dep->waiting;
        dep->waiting = temp_an->next_animal;

        temp_an->next_animal = dep->in_dep;
        dep->in_dep = temp_an;
        dep->free_space--;
    }
}
void print_animals(animal *dep)//print all animals in wished dep
{
    char temp = 0;
    animal *cur_an = dep;
    // int an_am = animals_amount(dep);
    for (char i = 65; i <= 90; i++)
    {
        cur_an = dep;

        while (cur_an)
        {
            temp = *(cur_an->name + 0);

            if (temp == i || temp == i + 32)
            {

                printf("\n - %s", cur_an->name);
                printf("\n\tIDENTEFIRE:%s", cur_an->animal_id);
                printf("\n\tAGE:%d", cur_an->age);
                printf("\n\tWEIGHT:%d", cur_an->weight);
                cur_an = cur_an->next_animal;
            }
            else
                cur_an = cur_an->next_animal;
        }
    }
}
int animals_amount(animal *dep)//check num of animals in dep
{
    animal *cur = dep;
    int i = 0;
    for (; cur != NULL; i++)
    {
        cur = cur->next_animal;
    }
    return i;
}
int check_string(char str[])//check that input is only letters
{
    int x = 0, p;
    p = strlen(str);
    for (int i = 0; i < p; i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == ' '))
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
int check_duplicate_name(char name[], spice *dep)//check that animal name is uniqe
{
    spice *cur = dep;
    if (cur->free_space >= 0 && cur->in_dep->name != NULL) //check in dep
    {

        while (cur->in_dep)
        {

            if (stricmp(name, cur->in_dep->name) == 0) //means they equal
                return 0;
            cur->in_dep = cur->in_dep->next_animal;
        }
        return 1;
    }
    else
    {
        if (cur->waiting != NULL) //check in waiting dep
        {
            while (cur->waiting)
            {

                if (stricmp(cur->waiting->name, name) == 0) //means they equal
                    return 0;
                cur->waiting = cur->waiting->next_animal;
            }
        }
        return 1;
    }
}
int check_duplicate_spice(char dep_name[], spice *head) //check duplicate DEPARTMENT names

{
    spice *cur = head;

    while (cur)
    {

        if (stricmp(dep_name, cur->kind) == 0) //means they equal
            return 0;
        cur = cur->next_specie;
    }
    return 1;
}
animal *alloc_new_animal()
{
    animal *new_animal = NULL;

    new_animal = (animal *)malloc(sizeof(animal));
    if (new_animal == NULL)
    {
        return NULL;
    }
    return new_animal;
}
spice *alloc_new_spice() //creating new specie item
{
    spice *new_spice = NULL;

    new_spice = (spice *)malloc(sizeof(spice));
    if (new_spice == NULL)
    {
        return NULL;
    }
    return new_spice;
}
spice *init_new_spice(spice *new_spice, char kind[], int space, spice *next, animal *in_dep, animal *waiting)
{ //creating new dep from user info or file

    strcpy(new_spice->kind, kind);
    new_spice->in_dep = in_dep;
    new_spice->waiting = waiting;
    new_spice->next_specie = next;
    new_spice->in_dep = NULL;
    new_spice->free_space = space;
    return new_spice;
}
spice *Add_Spice(spice *head)//main function to creat new specie department
{
    int space, in;
    char temp[NAME_SIZE];
    spice *new_spice;
    new_spice = alloc_new_spice();
    if (new_spice == NULL)
    {
        printf("error creating new struct");
        return NULL;
    }
    getc(stdin);
    do
    {
        printf("\nPlease type the animal specie for the new department:  ");

        gets(temp);
        if (check_string(temp))
        {
            if (check_duplicate_spice(temp, head) == 0)
            { //check if duplicate

                printf("\nError! a department with this name is already exist,try again\n");
            }
            else
                in = 0;
        }
        else
            printf("\nIllegal name, try again\n");
    } while (in);

    printf("\nPlease type the space in the department:  ");
    scanf("%d", &space);
    init_new_spice(new_spice, temp, space, head, NULL, NULL);
    return new_spice; //head points to the new spice
}
spice *find_spice(char dep_name[], spice *head)//fined specific specie in list and returns it
{
    spice *cur = head;
    while (cur != NULL)
    {

        if (stricmp(dep_name, cur->kind) == 0) //means they equal
            return cur;
        cur = cur->next_specie;
    }
    return NULL;
}
void init_new_animal(spice *dest_dep, char id[NAME_SIZE], char name[NAME_SIZE], int weight, int age)
{ //creating the animal from user info or file
    animal *new_animal;
    new_animal = alloc_new_animal();
    if (new_animal == NULL)
    {
        printf("\nError creating new animal- the new animal data has lost");
        return;
    }
    strcpy(new_animal->animal_id, id);
    strcpy(new_animal->name, name);
    new_animal->weight = weight;
    new_animal->age = age;

    //check if put in waiting or inside dep
    if (dest_dep->free_space != 0) //check if there is free space in department
    {
        new_animal->next_animal = dest_dep->in_dep;
        dest_dep->in_dep = new_animal;
        dest_dep->free_space--;
    }
    else
    { //no free space, animal in waiting for department
        new_animal->next_animal = dest_dep->waiting;
        dest_dep->waiting = new_animal;
    }
}
void Add_Animal(spice *head, animal *animal_head) //main function to creat new animal item
{
    spice *cur = head;
    animal *animal_cur = animal_head, *tmp = head->in_dep;
    char id[NAME_SIZE], name[NAME_SIZE], number[NAME_SIZE], number2[NAME_SIZE];
    int in = 1, kaki = 1, weight, age, zevel;
    spice *dest_department;

    char temp[NAME_SIZE];

    while (in)
    {
        printf("\nPlease type the department name you wish to add animal to:  ");
        getc(stdin);
        gets(temp);
        dest_department = find_spice(temp, cur);
        if (dest_department != NULL)
        {
            printf("\nPlease type animal's identifyer:  ");
            // getc(stdin);
            gets(id);

            while (kaki)
            {

                printf("\nPlease type animal's name:  ");
                // getc(stdin);
                gets(name);
                if (check_string(name) != 0)
                { //means that string is legle
                    if (dest_department->in_dep != NULL)
                    {
                        if (check_duplicate_name(name, dest_department) == 0)
                        {
                            printf("\nName already exist!");
                        } //func check if dup animal name
                        else
                            kaki = 0;
                    }
                    else
                        kaki = 0; //name leagle and uniqe
                }
                else
                    printf("\nIllegal name!");
            }
            kaki = 1;
            while (kaki)

            {
                printf("\nPlease type %s's weight:  ", name);
                gets(number);
                zevel = isNumber(number);
                if (zevel)
                    kaki = 0;
                else
                    printf("\nillegal number! please type again");
                if (zevel)
                {

                    kaki = 0;
                    weight = zevel;
                }

                else
                {
                    printf("\nillegal number! please type again");
                }
            }
            kaki = 1;
            while (kaki)
            {
                printf("\nHow old is %s?  ", name);
                gets(number2);
                zevel = isNumber(number2);
                if (zevel)
                {

                    kaki = 0;
                    age = zevel;
                }

                else
                {
                    printf("\nillegal number! please type again");
                }
            }
            cur->in_dep = tmp;
            dest_department = find_spice(temp, cur);
            init_new_animal(dest_department, id, name, weight, age);
            return;
        }
        else
        {
            printf("\nError!  the department %s has not found\n", temp);
            printf("\nWhat would you like to do?");
            printf("\nTo try again with other department name: press 1");
            printf("\nTo Cancel the \"Add animal\" process: press 0\n");
            scanf("%d", &in);
        }
    }
}
void dep_rep(spice *head)//main function to print dep report by alphabetic order
{
    int inWaiting;
    spice *cur = head;

    int i = 1;
    while (cur)
    {
        printf("\n\n\t\t%d. Department- %s:\n", i, cur->kind);
        printf("\nanimals in department:");
        print_animals(cur->in_dep);
        inWaiting = animals_amount(cur->waiting);
        printf("\n\nAmount of animals in waiting list: %d", inWaiting);
        if (inWaiting != 0)
        {
            printf("\n\nanimals in waiting list:");
            print_animals(cur->waiting);
        }

        cur = cur->next_specie;
        i++;
    }
}
int Remove_Animal(spice *department)//remvoe animal from specific department
{

    char an_2rem[NAME_SIZE];
    spice *dep = department;
    animal *req_animal = NULL, *first_an = department->in_dep;
    while (req_animal == NULL)
    {
        printf("\nPlease type the animal name you want to remove:  ");
        gets(an_2rem);
        req_animal = find_animal(an_2rem, dep);
        if (req_animal == NULL)
        {
            printf("\n\nERROR! The animal %s has not found!\n", an_2rem);
            break;
        }
    }
    dep->in_dep = first_an;
    if (dep->in_dep == req_animal) //the animal is first on list
    {
        printf("\n\nITS FIRST AGAIAN\n\n");
        department->in_dep = req_animal->next_animal;

        printf("\n%s HAS REMOVED SUCCESSFULLY", an_2rem);

        stop_waiting(dep);
        free(req_animal);
        return 1;
    }
    while (dep != NULL)
    {

        if (dep->in_dep->next_animal == req_animal) //if the animal is NOT the first in list
        {
            dep->in_dep->next_animal = req_animal->next_animal;

            printf("\n%s HAS REMOVED SUCCESSFULLY", an_2rem);
            stop_waiting(dep);
            free(req_animal);
            return 1;
        }
        else
            dep->in_dep = dep->in_dep->next_animal;
    }
    if (dep->free_space > 0 && dep->waiting != NULL)

        return 0;
}
int Remove_dep(spice *department)//remove specific dep. used for free all database as well
{
    char cur_animal[NAME_SIZE];
    spice *dep = department;
    animal *free_animal = NULL;

    while (dep->in_dep)
    {
        free_animal = dep->in_dep;

        free(dep->in_dep);
        dep->in_dep = free_animal->next_animal;
        stop_waiting(dep);
    }

    free(dep);
}
spice *loadSPFile(FILE *spicePtr, spice *DPhead)//loads argv departments files
{
    spice *new_spice, *head = DPhead;
    char zevel;
    int freeSpace, weight, age;
    while (1)
    {
        char spice_name[NAME_SIZE] = {'\0'}, animal_name[NAME_SIZE] = {'\0'}, animalID[NAME_SIZE] = {'\0'};
        for (int i = 0; i < NAME_SIZE; i++)
        {
            spice_name[i] = fgetc(spicePtr);
            if (spice_name[i] == '\r')
            {

                spice_name[i] = '\0';
                break;
            }
        }

        fscanf(spicePtr, "%d", &freeSpace);
        zevel = fgetc(spicePtr);
        new_spice = alloc_new_spice();
        head = init_new_spice(new_spice, spice_name, freeSpace, head, NULL, NULL);
        if (feof(spicePtr))

            return head;
    }
}
void loadANFile(FILE *spicePtr, FILE *anptr, spice *DPhead)//loads argv animals file
{
    animal *new_animal;
    spice *dest_spice, *head = DPhead;
    

    char zevel;

    int age, weight;

    while (1)
    {
        char id[NAME_SIZE] = {'\0'}, name[NAME_SIZE] = {'\0'}, dep[NAME_SIZE] = {'\0'};
     
        for (int i = 0; i < NAME_SIZE; i++)
        {
            id[i] = fgetc(anptr);
            if (id[i] == '\n')
            {

                id[i] = '\0';
                break;
            }
        }
        

        for (int i = 0; i < NAME_SIZE; i++)
        {
            name[i] = fgetc(anptr);
            if (name[i] == '\n')
            {

                name[i] = '\0';
                break;
            }
        }
        fscanf(anptr, "%d", &weight);
        fscanf(anptr, "%d", &age);
        zevel = fgetc(anptr);
       
        for (int i = 0; i < NAME_SIZE; i++)
        {
            if (feof(anptr))
            {
                dep[i - 1] = '\0';

                break;
            }

            dep[i] = fgetc(anptr);
            if (dep[i] == '\n')
            {

                dep[i] = '\0';
                break;
            }
        }
        dest_spice = find_spice(dep, head);
        if (dest_spice == NULL)
            break;
        init_new_animal(dest_spice, id, name, weight, age);
        if (feof(anptr))
            break;
    }
}
void vegan_func(spice *head) //FREE ALL ANIMALS AND DEPS
{
    spice *tmp;
    while (head)
    {
        tmp = head->next_specie;
        Remove_dep(head);
        head = tmp;
    }
}
int main(int argc, char *argv[])
{
    FILE *spice_ptr, *animal_ptr;
    spice *head = NULL, *dep_2rem, *temp_spice;
    animal *an_head = NULL;
    int selection, in = 1;
    char removal[NAME_SIZE], dep_removal[NAME_SIZE];

    do
    {

        printf("\n\n\t\tWelcome to Zoo Management Application, Please type your choice :\n\n");
        printf("\t\t\t1. Add a new Species Department to the Zoo \n"); //var
        printf("\t\t\t2. Remove Species Department from the Zoo \n");
        printf("\t\t\t3. Add animal to specific department  \n");
        printf("\t\t\t4. Remove animal from specific department  \n");
        printf("\t\t\t5. Sort Department by animal weight \n");
        printf("\t\t\t6. Show Department Report  \n");
        printf("\t\t\t7. Load File \n");
        printf("\t\t\t8. Exit  \n");
        printf("\n\t\t\tYour Selection:   ");
        scanf("%d", &selection);

        switch (selection)
        {
        case (1): //add dep
            head = Add_Spice(head);
            break;
        case (2):
            if (head == NULL)
            {
                printf("\n\n\t\tERROR! no departments in the zoo");
                break;
            }
            temp_spice = head;
            printf("\nPlease type the department you want to remvoe:  ");
            getc(stdin);
            gets(dep_removal);
            dep_2rem = find_spice(dep_removal, head);

            if (dep_2rem == NULL)
            {
                printf("\nERROR! department \"%s\" has not found!", dep_2rem);

                break;
            }
            if (head == dep_2rem) //means that dep_2rem is first dep
            {
                head = dep_2rem->next_specie;
                Remove_dep(dep_2rem);
                break;
            }
            while (head)
            {
                temp_spice = head;

                if (head->next_specie == dep_2rem) //means that its not first
                {

                    head->next_specie = dep_2rem->next_specie;
                    break;
                }
                head = head->next_specie;
            }

            Remove_dep(dep_2rem);
            head = temp_spice;
            break;
        case (3):
            if (head == NULL)
            {
                printf("\n\n\t\tERROR! no departments in the zoo");
                break;
            }
            Add_Animal(head, an_head); //varified

            break;
        case (4): //take from waiting to dep
            if (head == NULL)
            {
                printf("\n\n\t\tERROR! no departments in the zoo");
                break;
            }
            printf("\nPlease type the department you want to remvoe animals from:  ");
            getc(stdin);
            gets(removal);
            dep_2rem = find_spice(removal, head);
            if (dep_2rem != NULL)
            {
                if (Remove_Animal(dep_2rem) != 0)
                {
                    dep_2rem->free_space++;
                    break;
                }
                else
                {
                    printf("\n An error been accured. animal has not removed. please try again");
                    break;
                }
            }
            else
                printf("\ndepartment \"%s\" has not found!", removal);

            break;
        case (5):
            break;
        case (6):
            if (head == NULL)
            {
                printf("\n\n\t\tERROR! no departments in the zoo");
                break;
            }
            dep_rep(head);
            break;
        case (7):
            if (argc >= 1)
            {

                spice_ptr = fopen(argv[1], "r"); //open dep file
                // spice_ptr = fopen("dep.txt", "r"); //FOR DEBUG ONLY
                if (spice_ptr == NULL) //checking for error
                {
                    printf("Error With File Opening");
                    break;
                }
                animal_ptr = fopen(argv[2], "r"); //open animals file
                // animal_ptr = fopen("animals.txt", "r"); //FOR DEBUG ONLY

                if (animal_ptr == NULL) //checking for error
                {
                    printf("Error With File Opening");
                    // break;
                }
                head = loadSPFile(spice_ptr, head); //loads the departments file
                loadANFile(spice_ptr, animal_ptr, head);
            }

            else
            {
                printf("\n\t\tNOTE! NO FILE WAS LOADED");
                break;
            }
            printf("\n\nThe files: %s and %s were uploaded successfully!\n\n", argv[1], argv[2]);
            break;
        case (8):
            vegan_func(head);
            fclose(spice_ptr);
            fclose(animal_ptr);
            printf("\n\n\t\t\t\tBYE BYE KARAKO!\n\n");
            break;
        default:
            printf("\n\n\tError in Selection\n\n");
            break;
            // }
        }
    } while (selection != 8);

    return 0;
}
