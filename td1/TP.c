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

void Date_ToString(Date d, char text[], int capacity){
    char c = d.cal_is_julian?'j':'g';
    snprintf(text, capacity, "%d/%d/%d:%c", d.day, d.month, d.year, c);
}

char * Date_ToStaticString (Date d) {
#define STATIC_TEXT_CAPACITY 100
static char static_text [ STATIC_TEXT_CAPACITY ];
Date_ToString (d , static_text , STATIC_TEXT_CAPACITY );
return static_text ; // evaluates to & static_text [0] , the address of static_text []
}

#define SIZEDATE 20

bool JulianYear_IsLeap(int year){
    return year%4==0;
}

bool GregorianYear_IsLeap(int year, bool cal_is_julian){
    if(year%100==0 && year%400==0){
        return true;
    }
    if(year%4==0){
        return true;
    }
    return false;
}

bool Year_IsLeap(int year, bool cal_is_julian){
    if(cal_is_julian){
        return year%4==0;
    }
    else{
        if (year%100 && year%400==0){
            return true;
        }
        if(year%4==0){
            return true;
        }
    }
}

int Year_Length(int year, bool cal_is_julian){
    if(Year_IsLeap(year, cal_is_julian)){
        return 366;
    }
    return 365;
}

bool Date_YearIsLeap(Date date){
    return Year_IsLeap(date.year, date.cal_is_julian);
}

int Date_YearLength(Date date){
    return Year_Length(date.year, date.cal_is_julian);
}

bool Month_Has31Days(int month){
    if(month<8 && month%2 != 0){
        return true;
    }
    if(month>7 && month%2 == 0){
        return true;
    }
    return false;
}

int Month_Length(int month, int year, bool cal_is_julian){
    if(month == 2){
        if(Year_IsLeap(year, cal_is_julian)){return 29;}
        else{return 28;}
    }
    if (Month_Has31Days){
        return 31;
    }
    else{
        return 30;
    }
}

int Date_MonthLength(Date d){
    return Month_Length(d.month, d.year, d.cal_is_julian);
}

bool Date_IsValid(Date d){
    if(d.cal_is_julian && Year_IsLeap(d.year, d.cal_is_julian) && Date_MonthLength(d)==29){
        return true;
    }
    else if(d.cal_is_julian==false && Year_IsLeap(d.year, d.cal_is_julian) && Date_MonthLength(d)==29){
        return true;
    }
    return false;
}

Date Date_Add1Day(Date d){
    if(d.day == Date_MonthLength(d)){
        if(d.month<12){
            return Date_Make(1, d.month+1,d.year,d.cal_is_julian);
        }
        else{
            return Date_Make(1,1,d.year+1,d.cal_is_julian);
        }
    }
    else{
        return Date_Make(d.day+1,d.month,d.year,d.cal_is_julian);
    }
}

Date Date_Sub1Day(Date d){
    if(d.day==1){
        if(d.month==1){
            return Date_Make(31,12,d.year-1,d.cal_is_julian);
        }
        else{
            return Date_Make(Month_Length(d.month-1), d.month-1, d.year, d.cal_is_julian);
        }
    }
    else{
        return Date_Make(d.day-1, d.month, d.year,d.cal_is_julian);
    }
}

int Date_YearElapsedDays(Date d){
    int DaysElapsed = d.day-1;
    for(i=0, i<d.month,i++){
        DaysElapsed+=Month_Length(i, d.year, d.cal_is_julian);
    }
    return DaysElapsed;
}

int Date_YearsRemainingDays(Date d){
    int DaysRemaining = Month_Length(d.month, d.year, d.cal_is_julian)_d.day+1;
    for(i=12, i>d.month,i++){
        DaysRemaining+=Month_Length(i,d.year,d.cal_is_julian);
    }
    return DaysRemaining;
}

void Date_ToString(Date date,char text[], int capacity){
    snprintf(text, capacity, "%02d/%02d/%04d:%c", date.day, date.month, date.year, date.cal_is_julian?'j':'g');
}
long Date_DaysBetweenForSameCal(Date older, Date newer){
    long Difference=0;
    for(i=older.year+1, i<newer.year,i++){
        Difference+=Year_Length(i,older.cal_is_julian);
    }
    return Difference+=Date_YearRemainingDays(older)+Date_YearElapsedDays(newer);
}

int main(void) { 
    Date d = Date_Make(25, 12, 2000, false);
    printf("%d/%d/%d\n", d.day, d.month, d.year);
    printf("%scalendar\n", d.cal_is_julian? "julian ":"gregorian ");
    

    Date c= Date_FromString("3/2/2018:g");
    printf("date is %d/%d/%d\n", c.day, c.month, c.year);
    printf("calendar is %s\n", d.cal_is_julian?"julian":"georgian");
    
    Date e =Date_Epoch(true);
    int const CAPACITY=100;
    char text [CAPACITY];
    Date_ToString(e, text, CAPACITY);
    printf("date is %s\n", text);

    Date d1 = Date_Epoch(true), d2 = Date_Epoch(false);
    printf ("d1 is %s \n", Date_ToStaticString (d1));
    printf ("d2 is %s \n", Date_ToStaticString (d2));
    return 0;
}

/*
int main(int argc, char * argv[]){
    printf("argc : %d\n", argc);
    for (int k=0; k<argc; k++){
        printf("argv[%d] : <%s\n", k, argv[k]);
    }
    printf(Date_ToStaticString(Date_Epoch(Date_FromString(argv).cal_is_julian)));
}
    */
  /* 
int main(int argc, char * argv[]){
    if(argc<2){
    printf("usage:%s", argv[0]);
    return 0;
    }
    Date d = Date_FromString(argv[1]);
    Date epoch = Date_Epoch(d.cal_is_julian);
    Date_Epoch(d.cal_is_julian);
    int comp = Date_CompareForSameCal(d, epoch);
    char StrEpoch[SIZEDATE];
    Date_ToString(epoch, StrEpoch, SIZEDATE);
    printf("%s %c %s", argv[1], (comp>0?'>':comp<0?'<':'='), StrEpoch);
}
*/


//clang -W -Wall -std=c99 -pedantic TP.c -o app1
