#include <stdio.h>

int leapCheck(int year) {
    if((year % 4 == 0 && year %100 !=0) || year % 400 == 0) {
        return 29;
    }
    return 28;
}

int getFirstDayIndex(int year){
    
    int day = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
    return day;
}

int main() {
    int year, monthIndex, daysIndex, firstDayIndex, weekDayIndex, daysOfWeekIndex;
    
    char *month[]= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysOfMonth[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    
    printf("Enter year: ");
    scanf("%d",&year);
    
    daysOfMonth[1] = leapCheck(year);
    
    firstDayIndex = getFirstDayIndex(year);
    
    for (monthIndex = 0; monthIndex < 12; monthIndex++) {
        
        printf("\n\n\t\t** %s **\n\n",month[monthIndex]);
        
        for (daysOfWeekIndex = 0; daysOfWeekIndex < 7; daysOfWeekIndex++) {
            
            printf("%s\t", daysOfWeek[daysOfWeekIndex]);
        }
        
        printf("\n");
        
        for(weekDayIndex = 0; weekDayIndex <= firstDayIndex - 1; weekDayIndex++) {
            
            printf("\t ");
        }
        
        for (daysIndex = 1; daysIndex <= daysOfMonth[monthIndex]; daysIndex++) {
            
            printf("%d\t ", daysIndex);
            weekDayIndex++;
            
            if (weekDayIndex > 6) {
                
                printf("\n");
                weekDayIndex = 0;
            }
            
         firstDayIndex = weekDayIndex;
        }

    }
    
    printf("\n\n");
    
    return 0;
    
    
}
