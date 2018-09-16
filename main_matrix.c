#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int month_code(int month)
{
    const int c[]={11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return c[month-1];
}

int day_index(int date, int month, int year)
{
    if(month==1 || month==2)
        year--;

    int i = (date + ((13*month_code(month)-1)/5) + (year%100) + ((year%100)/4) + ((year/100)/4) - 2*(year/100));
    int f = i % 7;

    if(f<0)
        f+=7;
    return f;
}

bool is_leap(int year)
{
    if((year % 4 == 0 && year %100 !=0) || year % 400 == 0)
        return true;
    else
        return false;
}

int no_days_in_month(int month, int year)
{
    const int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(is_leap(year) && month==2)
        return (d[month-1]+1);
    else
        return d[month-1];
}

int main()
{
    int date, month, year;

    scanf("%d%d%d", &date, &month, &year);
    printf("%d", no_days_in_month(month, year));

    return 0;
}
