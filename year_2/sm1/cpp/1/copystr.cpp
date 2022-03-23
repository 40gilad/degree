#include "copystr.h"
using namespace std;

char *copystring(const char *c)
{
    char *new_str = new char[strlen(c) + 1];
    cout<<endl<<"try agian"<<strlen(c)<<endl;
    if (new_str == nullptr)
        return new_str;
    strcpy(new_str, c);
    return new_str;
}