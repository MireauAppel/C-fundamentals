#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct Date {
    int day, month, year;
    bool cal_is_julian;
} Date;

Date Date_Make(int day, int month, int year, bool cal_is_julian){
    return (Date){
        .day=day,
        .month=month,
        .year=year,
        .cal_is_julian=cal_is_julian,
    };
}

Date Date_Epoch(bool cal_is_julian){
    return cal_is_julian?Date_Make(19,12,1969,true):Date_Make(01,01,1970,false);
}

bool Date_HasSameCal(Date d1, Date d2){
    return(d1.cal_is_julian==d2.cal_is_julian);
}

int Date_CompareForSameCal(Date d1, Date d2){
    assert(Date_HasSameCal(d1,d2));
    if(d1.year!=d2.year){return d1.year-d2.year;}
    if(d1.month!=d2.month){return d1.month-d2.month;}
    if(d1.day!=d2.day){return d1.day-d2.day;}
    return 0;
}

Date Date_Dummy(void){
    return Date_Make(0,0,0,false);
}

Date Date_FromString(char const description[]){
    int day, month, year;
    char c;
    int x = sscanf(description, "%d/%d/%d:%c", &day, &month, &year, &c);
    if((x!=4)||(c!='j' &&c!='g')){return Date_Dummy();}
    return Date_Make(day,month, year, c=='j');
}

int main(void) { 
    Date d = Date_Make(25, 12, 2000, false);
    printf("%d/%d/%d\n", d.day, d.month, d.year);
    printf("%scalendar\n", d.cal_is_julian? "julian ":"gregorian ");
    return 0;
}


//clang -W -Wall -std=c99 -pedantic TP.c -o app1
