#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int month_code(int month)
{
    const int c[]={11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    return c[month-1];
}

int day_index(int date, int month, int year)
{
    int y=year;
    if(month==1 || month==2)
        y--;

    int i = (date + (((13*month_code(month))-1)/5) + (y%100) + ((y%100)/4) + ((y/100)/4) - 2*(y/100));
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

void month_matrix(int month_m[6][7], int month, int year)
{
    int i;
    for(i=0; i<6; i++)
        for(int j=0; j<7; j++)
            month_m[i][j]=0;

    int k = day_index(1, month, year);
    int days = no_days_in_month(month, year);

    i=0;
    int d=1;
    while(1)
    {
        month_m[i][k]=d;

        if(k==6)
        {
            i++;
            k=0;
        }
        else
            k++;

        if(d==days)
            break;
        else
            d++;
    }
}

char* get_month_name(int month)
{
    char* m[] = {"January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"};

    return m[month-1];
}

void print_month(int matrix[6][7], int month)
{
    int space = (int)((27 - strlen(get_month_name(month)))/2);
    for(int i=0; i<space; i++)
        printf(" ");

    printf("%s\n", get_month_name(month));
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(matrix[i][j]==0)
                printf("   ");
            else
                printf("%3d", matrix[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void print_year(int year)
{
    int month_m[6][7];

    int dig = floor(log10(year))+1;
    int space = (int)((27 - dig)/2);
    for(int i=0; i<space; i++)
        printf(" ");

    printf("%d\n\n", year);

    for(int i=0; i<12; i++)
    {
        month_matrix(month_m, i+1, year);
        print_month(month_m, i+1);
        printf("\n");
    }
}

int main()
{
    int choice, month, year, month_m[6][7];

    printf("Enter 1 - Year view || 2 - Month View: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Enter Year: ");
            scanf("%d", &year);

            print_year(year);

            break;
        case 2:
            printf("Enter Month and Year: ");
            scanf("%d%d", &month, &year);

            month_matrix(month_m, month, year);
            print_month(month_m, month);

            break;

        default:
            printf("Wrong choice");
            break;
    }
    printf("\n\n");
    return 0;

}
