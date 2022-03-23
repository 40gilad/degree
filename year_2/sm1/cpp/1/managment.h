#include "person.h"
#include <iostream>
#ifndef MANAGMENT_H
#define MANAGMENT_H
#define SIZE 10
using namespace std;
#endif


// ש להחזיק מערך של מצביעים למחלקת  Person  ולהגדיל אותו דינאמית ע"פ הצורך בהתאם   
// לכמות האנשים שנוספים לתוך המערך.  
// יש לממש מתודת הכנסה/ מחיקה של אדם מתוך המחלקה.  
// יש לממש  מתודה המחזירה את המקום הפנוי הראשון במ ערך האנשים.  
// יש לממש אופרטור השמה ו -  Copy C’tor . 
// יש לממש מתודת הדפסה אשר מדפיסה את כל האנשים שמנוהלים ע"י המחלקה.  


class managment{
    private:
    person** p_arr;
    int sizeOfArr;
    void initAll();
    void incSize();
    int vac ();//returns the first vac index in the arrey
    public:
    managment* operator=(const managment &m);
    managment();
    managment(int size);
    managment (const managment &man);
    ~managment();
    void setPerson (person *p);
    void remove (person *p);
    void printPersons();
    
};