#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <process.h>
#include <math.h>
#include <time.h>
#include <string.h>

struct date_time
{
    int _sec, _min, _hour, _mday, _mon, _year,  _wday;
};

//  returns specific codes for each month: considering March as the start of the year
int month_code(int month)
{
    const int c[]={11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return c[month-1];
}

//  returns the day index number depending upon the date, month and year
//  read this: http://mathforum.org/dr.math/faq/faq.calendar.html
int day_index(int date, int month, int year)
{
    int y=year;
    if(month==1 || month==2)
        y--;    //  Jan and Feb treated as a part of the previous year

    //  the formula
    int f = (date + (((13*month_code(month))-1)/5) + (y%100) + ((y%100)/4) + ((y/100)/4) - 2*(y/100));
    int i = f % 7;

    if(i<0) //  if negative, adjust remainder
        i+=7;
    return i;
}

//  checks whether a year is leap or not
int is_leap(int year)
{
    //  leap condition
    if((year % 4 == 0 && year %100 !=0) || year % 400 == 0)
        return 1;
    else
        return 0;
}

//  calculated the number of days in each month
int no_days_in_month(int month, int year)
{
    //  no. of days in each month
    const int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(is_leap(year) && month==2)
        return (d[month-1]+1);  //  if leap year, then Feb has 29 days
    else
        return d[month-1];
}

//  create the month matrix
int month_matrix(int month_m[6][7], int month, int year)
{
    int i;
    //  initialising the total matrix as 0
    for(i=0; i<6; i++)
        for(int j=0; j<7; j++)
            month_m[i][j]=0;

    //  shift to the weekday of day1
    int k = day_index(1, month, year);

    //  get no. of days in the month
    int days = no_days_in_month(month, year);

    //  fill the whole matrix with days
    i=0;
    int d=1;
    while(1)
    {
        month_m[i][k]=d;

        if(k==6)    //  smoothen edges to next line
        {
            i++;
            k=0;
        }
        else
            k++;

        if(d==days) //  no. of days exhausted
            break;
        else
            d++;
    }

    //  returning no. of rows, i.e. no. of weeks
    if(k==0)
        return i;
    else
        return i+1;
}

//  get the name of the months
char* get_month_name(int month)
{
    char* m[] = {"January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"};

    return m[month-1];
}

//  print a specified month (old one: w/o borders)
/*
void print_month(int matrix[6][7], int month)
{
    //  print the month name in center alignment
    int space = (int)((27 - strlen(get_month_name(month)))/2);
    for(int i=0; i<space; i++)
        printf(" ");

    printf("%s\n", get_month_name(month));
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    //  print the month matrix
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(matrix[i][j]==0)
                printf("   ");  //  if 0, its no day :(
            else
                printf("%3d", matrix[i][j]);    //  setw with spaces
            printf(" ");
        }
        printf("\n");
    }
}
*/

//  print a specified month with borders
void print_month(int matrix[6][7], int month, int rows)
{
    printf("%c", 201);
    for(int i=0; i<27; i++)
        printf("%c", 205);
    printf("%c\n", 187);

    //  print the month name in center alignment
    int space = (int)((27 - strlen(get_month_name(month)))/2);
    printf("%c", 186);
    for(int i=0; i<space; i++)
        printf(" ");

    space=27-space-strlen(get_month_name(month));
    printf("%s", get_month_name(month));
    for(int i=0; i<space; i++)
        printf(" ");
    printf("%c\n", 186);

    printf("%c", 199);
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<3; j++)
            printf("%c", 196);
        printf("%c", 194);
    }
    printf("\b%c\n", 182);

    printf("%cSun%cMon%cTue%cWed%cThu%cFri%cSat%c\n", 186, 179, 179, 179, 179, 179, 179, 186);

    printf("%c", 199);
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<3; j++)
            printf("%c", 196);
        printf("%c", 197);
    }
    printf("\b%c", 182);

    //  print the month matrix
    for(int i=0; i<rows; i++)
    {
        printf("\n%c", 186);
        for(int j=0; j<7; j++)
        {
            if(matrix[i][j]==0)
                printf("   ");  //  if 0, its no day :(
            else
                printf("%3d", matrix[i][j]);    //  setw with spaces
            printf("%c", 179);
        }
        printf("\b%c", 186);

        printf("\n%c", 199);
        for(int i=0; i<7; i++)
        {
            for(int j=0; j<3; j++)
                printf("%c", 196);
            printf("%c", 197);
        }
        printf("\b%c", 182);

        //printf("\n");
    }

    printf("\r%c", 200);
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<3; j++)
            printf("%c", 205);
        printf("%c", 207);
    }
    printf("\b%c\n", 188);
}

//  print a total year
void print_year(int year)
{
    int month_m[6][7];

    //  print the year in center alignment
    int dig = floor(log10(year))+1;
    int space = (int)((27 - dig)/2);
    printf("\n");
    for(int i=0; i<space; i++)
        printf(" ");

    printf("%d\n\n", year);

    //  print each month iteratively
    for(int i=0; i<12; i++)
    {
        int rows=month_matrix(month_m, i+1, year);
        print_month(month_m, i+1, rows);
        printf("\n");
    }
}

//  print the year number on the head
void print_year_num(int year)
{
    //  print year number
    int dig = floor(log10(year))+1;
    int space = (int)((27 - dig)/2);
    printf("\n");
    for(int i=0; i<space; i++)
        printf(" ");

    printf("%d\n\n", year);
}

//  main function
int main()
{
    int month, year, month_m[6][7];

    struct date_time T;
    time_t t = time(0);   // get time now
    struct tm* now = localtime(&t);
    T._mon=now->tm_mon+1;
    T._year=now->tm_year + 1900;

    month=T._mon;   //  initially set month as the current month
    year=T._year;   //  initially set year as the current year

    int view=0;
    //  0 for month and 1 for year

    char key;
    do
    {
        system("cls");
        switch(view)    //  switch year/month view
        {
        case 0:
            print_year_num(year);
            //  print month matrix
            int rows = month_matrix(month_m, month, year);
            print_month(month_m, month, rows);

            break;

        case 1:
            print_year(year);
            break;
        }

        //  handle the keys
        key = getch();
        if(key == -32)
        {
            key = getch();
            if(view == 0)
            {
                switch(key)
                {
                    case 72:    year--;     break;  //  up arrow pressed
                    case 80:    year++;     break;  //  down arrow pressed
                    case 75:    month--;    break;  //  left arrow pressed
                    case 77:    month++;    break;  //  right arrow pressed
                }
            }

            else if(view == 1)
            {
                switch(key)
                {
                    case 72:    year--;     break;  //  up arrow pressed
                    case 80:    year++;     break;  //  down arrow pressed
                    case 75:    year--;    break;  //  left arrow pressed
                    case 77:    year++;    break;  //  right arrow pressed
                }
            }

            if(month==13)
            {
                year++;
                month=1;
            }

            else if(month==0)
            {
                year--;
                month=1;
            }
        }
        else if(key == 'Y' || key == 'y')   //  year view
            view = 1;
        else if(key == 'M' || key == 'm')   //  month view
            view = 0;
        else if(key == 'T' || key == 't')   //  current month
        {
            view = 0;
            month=T._mon;
            year=T._year;
        }
    }
    while(key != 27);   //  run till ECS key is not pressed

    return 0;
}
