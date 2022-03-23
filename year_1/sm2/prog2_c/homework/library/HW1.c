/*                          NOTE FOR EXAMINER                       */
/* 
1) in the excercise, for saving file, we builted a format that seperates the book data with character ","
as shown in next example:
SERIAL,BOOK NAME, AUTHOR NAME,CATAGORY,NUMBER OF PAGES,YEAR OF RELEASE,
4871,book name,author name,4,1,2021,

no spaces between ",".
IN ADDITION, we send the program with one "example.txt"file , with some books inside, 
for your own convinience, so you can prepare yourself a file to check the program with , as Dr. Marcelo Shimam
asked us to do. 
2)the serial number is random number that given by the program.*/







#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Add_Bname book_DataBase.List[Next].B_name
#define Add_Aname book_DataBase.List[Next].A_name
#define Add_Catagory book_DataBase.List[Next].Catagory
#define List_Size (sizeof(book_DataBase.List)) //Amount of books

int Size = 4; //the size of the library (used by the malloc)

typedef struct book
{
    int Serial;
    char *B_name; //Book Name
    char *A_name; // Auther Name
    int Num_of_Pages;
    int Year_of_Release;
    int Catagory; // 1= History , 2= Drama , 3= Science Fiction, 4 = Horror

} book;

struct _book_DataBase
{
    int Next;   //points to the next empty spot in the library
    book *List; //an array of book (the library)
} book_DataBase;

void GetBName(int Next) //Gets the book name from the user
{
    char temp[999]; //and temporary array to save the size of the array
    printf("\nEnter The Book Name: ");
    getc(stdin);
    gets(temp);
    Add_Bname = (char *)malloc((strlen(temp) + 1) * sizeof(char));
    if (Add_Bname == NULL) //checking for errors
    {
        printf("Error in GetBName");
        return;
    }
    strcpy(Add_Bname, temp); //copy from temp to the database
}

void GetAName(int Next) //Gets the book Author name from the user
{
    char temp[999]; //and temporary array to save the size of the array
    printf("\nEnter The Author Name: ");
    gets(temp);
    Add_Aname = (char *)malloc((strlen(temp) + 1) * sizeof(char));
    if (Add_Aname == NULL)
    {
        printf("Error in GetAName");
        return;
    }
    strcpy(Add_Aname, temp); //copy the array to the database
}

void GetCatagory(int Next) //Gets the catagory of the book from the user
{

    printf("\nEnter the corrisponding number to the Catagory:\n 1= History , 2= Drama , 3= Science Fiction, 4 = Horror: ");
    scanf("%d", &book_DataBase.List[Next].Catagory);
}

void GetNumPages(int Next) //Gets the number of pages of the book from the user
{
    printf("\nEnter The Number Of Pages: ");
    scanf("%d", &book_DataBase.List[Next].Num_of_Pages);
}

void GetReleaseYear(int Next) //Gets the release year of the book from the user
{
    printf("\nEnter The Year Of Release: ");
    scanf("%d", &book_DataBase.List[Next].Year_of_Release);
}

void Add_Book() //the main function of adding a book
{
    int Next = book_DataBase.Next; //points the next empty spot in the library
    int Temp = (rand() % 10000);
    for (int i = 0; i < Next; i++) //testing the serial number is uniqe
    {
        if (Temp == book_DataBase.List[i].Serial)
        {
            Temp = (rand() % 10000);
            i = 0;
        }
    }

    if (Next >= Size) //check if the realloc is needed
    {
        Size *= 1.5;
        book_DataBase.List = (book *)realloc(book_DataBase.List, Size * sizeof(book));
    }

    GetBName(Next);
    GetAName(Next);
    GetNumPages(Next);
    GetReleaseYear(Next);
    GetCatagory(Next);
    book_DataBase.List[Next].Serial = Temp;
    printf("The book serial is : %d \n", book_DataBase.List[Next].Serial);
    book_DataBase.Next++;
}

void Remove_Book(int Serial) //remove a chosen book from the library
{
    double c = 2.0 / 3.0;
    int Next = book_DataBase.Next;
    for (int i = 0; i < Next; i++)
    {
        if (Serial == book_DataBase.List[i].Serial) //searches for the chosen book
        {
            for (int j = i + 1; j < Next; j++)
            {
                book_DataBase.List[i] = book_DataBase.List[j];
                book_DataBase.List[j].Catagory = -1;
                i = j;
            }
            book_DataBase.Next--;
        }
    }
    if (Next == book_DataBase.Next)
        printf("No books where found with that serial\n");

    if (Next < Size / 2) //checks if realloc is needed
    {
        Size = Size * c;
        book_DataBase.List = (book *)realloc(book_DataBase.List, Size * sizeof(book));
    }
}

void Print() //prints to the user all the books in the library

{
    int Next = book_DataBase.Next;
    if (Next == 0) //checks if library is empty
    {
        printf("\nLibrary Empty\n");
        return;
    }

    for (int i = 0; i <= Next; i++) //prints according to the catagory
    {

        if (book_DataBase.List[i].Catagory == 1) // History
        {
            printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: History,\t Number of pages: %d,\t Year of Release: %d \n",
                   i + 1,
                   book_DataBase.List[i].Serial,
                   book_DataBase.List[i].B_name,
                   book_DataBase.List[i].A_name,
                   book_DataBase.List[i].Num_of_Pages,
                   book_DataBase.List[i].Year_of_Release);
        }
        if (book_DataBase.List[i].Catagory == 2) // Drama
        {
            printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: Drama,\t Number of pages: %d,\t Year of Release: %d \n",
                   i + 1,
                   book_DataBase.List[i].Serial,
                   book_DataBase.List[i].B_name,
                   book_DataBase.List[i].A_name,
                   book_DataBase.List[i].Num_of_Pages,
                   book_DataBase.List[i].Year_of_Release);
        }
        if (book_DataBase.List[i].Catagory == 3) //Science Fiction
        {
            printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: Science Fiction,\t Number of pages: %d,\t Year of Release: %d \n",
                   i + 1,
                   book_DataBase.List[i].Serial,
                   book_DataBase.List[i].B_name,
                   book_DataBase.List[i].A_name,
                   book_DataBase.List[i].Num_of_Pages,
                   book_DataBase.List[i].Year_of_Release);
        }
        if (book_DataBase.List[i].Catagory == 4) //Horror
        {
            printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: Horror,\t Number of pages: %d,\t Year of Release: %d \n",
                   i + 1,
                   book_DataBase.List[i].Serial,
                   book_DataBase.List[i].B_name,
                   book_DataBase.List[i].A_name,
                   book_DataBase.List[i].Num_of_Pages,
                   book_DataBase.List[i].Year_of_Release);
        }
    }
}

void Search(int Serial) //prints a chosen book by the serial
{

    int Next = book_DataBase.Next;
    int i = 0;
    for (; i < Next; i++)
    {
        
        if (Serial == book_DataBase.List[i].Serial)
            break;
    }
    if (i == Next)
    {
        printf("\nNo Book was found with this serial, try again.\n");
        return;
    }

    // for (i = 0; i < Next; i++)
    // {

    // if (Serial == book_DataBase.List[i].Serial)
    // {

    if (book_DataBase.List[i].Catagory == 1) // History
    {
        printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: History,\t Number of pages: %d,\t Year of Release: %d \n",
               i + 1,
               book_DataBase.List[i].Serial,
               book_DataBase.List[i].B_name,
               book_DataBase.List[i].A_name,
               book_DataBase.List[i].Num_of_Pages,
               book_DataBase.List[i].Year_of_Release);
    }
    if (book_DataBase.List[i].Catagory == 2) // Drama
    {
        printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: Drama,\t Number of pages: %d,\t Year of Release: %d \n",
               i + 1,
               book_DataBase.List[i].Serial,
               book_DataBase.List[i].B_name,
               book_DataBase.List[i].A_name,
               book_DataBase.List[i].Num_of_Pages,
               book_DataBase.List[i].Year_of_Release);
    }
    if (book_DataBase.List[i].Catagory == 3) //Science Fiction
    {
        printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: Science Fiction,\t Number of pages: %d,\t Year of Release: %d \n",
               i + 1,
               book_DataBase.List[i].Serial,
               book_DataBase.List[i].B_name,
               book_DataBase.List[i].A_name,
               book_DataBase.List[i].Num_of_Pages,
               book_DataBase.List[i].Year_of_Release);
    }
    if (book_DataBase.List[i].Catagory == 4) //Horror
    {
        printf("\n%d: Serial : %d,\t Book name : %s,\t Auther name: %s,\t Catagory: Horror,\t Number of pages: %d,\t Year of Release: %d \n",
               i + 1,
               book_DataBase.List[i].Serial,
               book_DataBase.List[i].B_name,
               book_DataBase.List[i].A_name,
               book_DataBase.List[i].Num_of_Pages,
               book_DataBase.List[i].Year_of_Release);
    }
    // break;
    // }
    // }
}

void Save() //save the current library to a file
{
    int Next = book_DataBase.Next;
    FILE *ptr;
    char str[100];
    printf("\nName of File? (without '.txt')\n");
    {
        getc(stdin); // add .txt to file name
        gets(str);
        int i = strlen(str);
        str[i++] = '.';
        str[i++] = 't';
        str[i++] = 'x';
        str[i++] = 't';
        str[i++] = '\0';
        ptr = fopen(str, "w");
    }
    if (ptr == NULL) // if Error
    {
        printf("error opening file\n");
        return;
    }

    for (int i = 0; i < Next; i++) //print each book to the file
    {
        if (i < Next - 1) //next always shows the next empty spot so here is only to next-1
        {
            if (book_DataBase.List[i].Catagory == 1) // History
            {
                fprintf(ptr, "%d,%s,%s,1,%d,%d,\n",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
            if (book_DataBase.List[i].Catagory == 2) // Drama
            {
                fprintf(ptr, "%d,%s,%s,2,%d,%d,\n",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
            if (book_DataBase.List[i].Catagory == 3) //Science Fiction
            {
                fprintf(ptr, "%d,%s,%s,3,%d,%d,\n",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
            if (book_DataBase.List[i].Catagory == 4) //Horror
            {
                fprintf(ptr, "%d,%s,%s,4,%d,%d,\n",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
        }
        if (i == Next - 1) //in the last book we dont use '\n' so we could read it again to database in upload function
        {
            if (book_DataBase.List[i].Catagory == 1) // History
            {
                fprintf(ptr, "%d,%s,%s,1,%d,%d,",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
            if (book_DataBase.List[i].Catagory == 2) // Drama
            {
                fprintf(ptr, "%d,%s,%s,2,%d,%d,",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
            if (book_DataBase.List[i].Catagory == 3) //Science Fiction
            {
                fprintf(ptr, "%d,%s,%s,3,%d,%d,",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
            if (book_DataBase.List[i].Catagory == 4) //Horror
            {
                fprintf(ptr, "%d,%s,%s,4,%d,%d,",
                        book_DataBase.List[i].Serial,
                        book_DataBase.List[i].B_name,
                        book_DataBase.List[i].A_name,
                        book_DataBase.List[i].Num_of_Pages,
                        book_DataBase.List[i].Year_of_Release);
            }
        }
    }

    fclose(ptr);
}

void Upload(char str[]) //upload to the library from a file according to the format we used in 'save' function
{
    //int Next = book_DataBase.Next;
    char temp[99] = {1};
    char kaki;
    int i = 0;
    int Next = book_DataBase.Next;
    FILE *ptr;
    ptr = fopen(str, "r"); //open file to read
    if (ptr == NULL)       //checking for error
    {
        printf("Error With File Opening");
        return;
    }

    while (temp[i] != EOF) //loop to move in the file
    {
        int zevel = 0;
        for (int k = 0; k < 99; k++)
        {
            temp[k] = '\0';
        }
        if (book_DataBase.Next >= Size) //check for realloc
        {
            Size *= 1.5;
            book_DataBase.List = (book *)realloc(book_DataBase.List, Size * sizeof(book));
        }
        //Serial:-------------------------------------------------------------------------------------
        while (temp[0] != ',')
        {
            temp[0] = fgetc(ptr);
            if (temp[0] != ',') //casting from char to int
            {
                zevel *= 10;
                zevel += temp[0] - 48;
            }
        }

        for (i = 0; i < Next; i++) //testing the serial number is uniqe
        {
            if (zevel == book_DataBase.List[i].Serial)
            {
                printf("Error in Upload: The Serial Number %d in the file already exists\n");
                printf("Please Check there is no duplicate Serials and try again.\n");
                return;
            }
        }

        book_DataBase.List[book_DataBase.Next].Serial = zevel;
        printf("\nserial: %d\n", book_DataBase.List[book_DataBase.Next].Serial);
        kaki = '\0';
        //Book Name:-------------------------------------------------------------------------------------
        temp[0] = 0;
        i = 0;
        while (kaki != ',')
        {
            kaki = getc(ptr);
            if (kaki != ',')
            {
                temp[i] = kaki;
            }
            i++;
            temp[i] = '\0';
        }

        book_DataBase.List[book_DataBase.Next].B_name = (char *)malloc((strlen(temp) + 1) * sizeof(char));
        if (book_DataBase.List[book_DataBase.Next].B_name == NULL)
        {
            printf("Error in Upload B_Name");
            return;
        }
        strcpy(book_DataBase.List[book_DataBase.Next].B_name, temp);
        printf("Book name test: %s\n", book_DataBase.List[book_DataBase.Next].B_name);
        //Auther name:-------------------------------------------------------------------------------------
        for (int y = 0; y < 99; y++) //reset temp
        {
            temp[y] = '\0';
        }

        kaki = 0;
        i = 0;
        while (kaki != ',')
        {

            kaki = getc(ptr);
            if (kaki != ',')
            {
                temp[i] = kaki;
            }
            i++;
            temp[i] = '\0';
        }
        book_DataBase.List[book_DataBase.Next].A_name = (char *)malloc((strlen(temp) + 1) * sizeof(char));
        if (book_DataBase.List[book_DataBase.Next].A_name == NULL)
        {
            printf("Error in GetAName");
            return;
        }
        strcpy(book_DataBase.List[book_DataBase.Next].A_name, temp);
        printf("athuer name test: %s\n", book_DataBase.List[book_DataBase.Next].A_name);

        //catagory:-------------------------------------------------------------------------------------
        zevel = 0;
        i = 0;
        zevel = getc(ptr);
        book_DataBase.List[book_DataBase.Next].Catagory = zevel - 48;
        getc(ptr);
        printf("catagory test: %d\n", book_DataBase.List[book_DataBase.Next].Catagory);

        zevel = 0;
        temp[0] = 0;
        //Number of pages:------------------------------------------------------------------------------
        while (temp[0] != ',')
        {
            temp[0] = fgetc(ptr);
            if (temp[0] != ',') //casting from char to int
            {
                zevel *= 10;
                zevel += temp[0] - 48;
            }
        }
        book_DataBase.List[book_DataBase.Next].Num_of_Pages = zevel;
        printf("Num of pages : %d\n", book_DataBase.List[book_DataBase.Next].Num_of_Pages);

        //year of release:-------------------------------------------------------------------------------------

        zevel = 0;
        temp[0] = 0;
        while (temp[0] != ',')
        {
            temp[0] = fgetc(ptr);
            if (temp[0] != ',') //casting from char to int
            {
                zevel *= 10;
                zevel += temp[0] - 48;
            }
        }
        book_DataBase.List[book_DataBase.Next].Year_of_Release = zevel;
        printf("year : %d\n", book_DataBase.List[book_DataBase.Next].Year_of_Release);

        temp[i] = getc(ptr);

        book_DataBase.Next++; //move to the next spot in the library
    }
    fclose(ptr); //colses the file
}

void Malloc_free()
{
    int Next = book_DataBase.Next;
    for (int i = 0; i < Next; i++)
    {
        free(book_DataBase.List[i].A_name);
        free(book_DataBase.List[i].B_name);
    }
    free(book_DataBase.List);
    printf("\n\n\n\t\tthe Application closed successfully");
}

int main(int argc, char **argv)
{
    int choice;
    int temp = 0;
    char zevel[50];
    srand(time(0));
    book_DataBase.List = (book *)malloc(4 * sizeof(book));
    do
    {
        printf("\n\t\t   Menu:\n");
        printf("1 -> Add a book          4 -> Print all books          \n");
        printf("2 -> Remove a book       5 -> Save All books to a file \n");
        printf("3 -> Search a book       6 -> Upload books from a file \n");
        printf("                 0 -> exit                             \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case (1):
            Add_Book();
            break;
        case (2):
            printf("Please Enter the Serial number of the book you wish to remove: ");
            scanf("%d", &temp);
            Remove_Book(temp);
            break;
        case (3):
            printf("Please Enter the Serial number of the book you wish to Find: ");
            scanf("%d", &temp);
            printf("\n");
            Search(temp);

            break;
        case (4):
            Print();
            break;
        case (5):
            Save();
            break;
        case (6):
            printf("Please Enter the name of the file you with to upload, include format (txt...)\n");
            scanf("%s", zevel);
            Upload(zevel);
            break;
        case (0):
        {
            Malloc_free();
        }
        break;
        default:
            printf("\n\n\tError in Selection\n\n");
            break;
        }
    } while (choice != 0);
    return 0;
}