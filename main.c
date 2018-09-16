#include <stdio.h>
#include <stdlib.h>

// Declaration of variables:

int year, monthIndex, daysIndex, firstDayIndex, weekDayIndex, daysOfWeekIndex, monthInput;

char *month[]= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int daysOfMonth[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// Checking whether year is leap or not

int leapCheck(int year) {
    if((year % 4 == 0 && year %100 !=0) || year % 400 == 0) {
        return 29;
    }
    return 28;
}

// getting the index of the first day of the year:

int getFirstDayIndex(int year){
    
    int day = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
    return day;
}

// Method to call if user wants calendar in year format :

void yearView() {
    printf("Enter year: ");
    scanf("%d",&year);
    
    daysOfMonth[1] = leapCheck(year);
    
    firstDayIndex = getFirstDayIndex(year);
    
    for (monthIndex = 0; monthIndex < 12; monthIndex++) {
        
        printf("\n\n\t\t** %s **\n\n",month[monthIndex]);
        
        for (daysOfWeekIndex = 0; daysOfWeekIndex < 7; daysOfWeekIndex++) {
            
            //TODO: Need to check if the color works both in gcc and mingw compiler
            
            //            if (daysOfWeekIndex == 0) {
            //                printf("\033[1;31m");
            //            }
            printf("%s\t", daysOfWeek[daysOfWeekIndex]);
            //            printf("\033[0m");
        }
        
        printf("\n");
        
        for(weekDayIndex = 0; weekDayIndex <= firstDayIndex - 1; weekDayIndex++) {
            
            printf("\t ");
        }
        
        for (daysIndex = 1; daysIndex <= daysOfMonth[monthIndex]; daysIndex++) {
            
            //TODO: Need to check if the color works both in gcc and mingw compiler
            
            //            if (weekDayIndex == 0) {
            //                printf("\033[1;31m");
            //            }
            printf("%d\t ", daysIndex);
            //            printf("\033[0m");
            weekDayIndex++;
            
            if (weekDayIndex > 6) {
                
                printf("\n");
                weekDayIndex = 0;
            }
            
            firstDayIndex = weekDayIndex;
        }
    }
}

// Method to call if user wants calendar in month format :

void monthView() {
    printf("Enter year: ");
    scanf("%d",&year);
    printf("Enter month number: ");
    scanf("%d", &monthInput);
    
    daysOfMonth[1] = leapCheck(year);
    
    firstDayIndex = getFirstDayIndex(year);
    
    printf("\n\n\t** 2018 %s **\n\n",month[monthInput - 1]);
    
    for (monthIndex = 0; monthIndex < monthInput; monthIndex++) {
        
        if (monthIndex == monthInput - 1) {
            for (daysOfWeekIndex = 0; daysOfWeekIndex < 7; daysOfWeekIndex++) {
                
                //TODO: Need to check if the color works both in gcc and mingw compiler
                
                //                if (daysOfWeekIndex == 0) {
                //                    printf("\033[1;31m");
                //                }
                printf("%s\t", daysOfWeek[daysOfWeekIndex]);
                //                printf("\033[0m");
            }
            printf("\n");
        }
        
        for(weekDayIndex = 0; weekDayIndex <= firstDayIndex - 1; weekDayIndex++) {
            if (monthIndex == monthInput - 1) {
                printf("\t ");
            }
            
        }
        
        for (daysIndex = 1; daysIndex <= daysOfMonth[monthIndex]; daysIndex++) {
            if (monthIndex == monthInput - 1) {
                
                //TODO: Need to check if the color works both in gcc and mingw compiler
                
                //                if (weekDayIndex == 0) {
                //                    printf("\033[1;31m");
                //                }
                printf("%d\t ", daysIndex);
                //                printf("\033[0m");
            }
            
            weekDayIndex++;
            
            if (weekDayIndex > 6) {
                if (monthIndex == monthInput - 1) {
                    printf("\n");
                }
                
                weekDayIndex = 0;
            }
            
            firstDayIndex = weekDayIndex;
        }
    }
}

// Main function:

int main() {
    int choice;
    
    printf("Enter 1 - Year view || 2 - Month View: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            yearView();
            break;
        case 2:
            monthView();
            break;
            
        default:
            printf("Wrong choice");
            break;
    }
    printf("\n\n");
    return 0;
    
}
