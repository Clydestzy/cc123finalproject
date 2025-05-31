#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct event {
    int mm;
    int dd;
    int yy;
    char eventName[100];
};

int dateExists(int dd, int mm, int yy) {
    FILE *file = fopen("EventScheduler.txt", "r");
    if (file == NULL) return 0;

    char line[256];
    int filedd, filemm, fileyy;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Date of Event:%d/%d/%d", &filemm, &filedd, &fileyy) == 3) {
            if (filedd == dd && filemm == mm && fileyy == yy) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

void eventsScheduler(struct event *eventptr) {
    int add;
    int j = 2;

    for (int i = 1; i < j; i++) {
        int valid = 1;
        int different = 0;

        FILE *pF = fopen("EventScheduler.txt", "a");
        printf("********************************\n");
        printf("What is the name of your event\n>> ");
        fgets(eventptr->eventName, sizeof(eventptr->eventName), stdin);
        eventptr->eventName[strcspn(eventptr->eventName, "\n")] = 0;
        printf("********************************\n");
        while (different == 0) {
            
            valid = 1;
            while (valid == 1) {
                printf("What is the year of your event?\n>> ");
                scanf(" %d", &eventptr->yy);
                printf("********************************\n");
                if (eventptr->yy < 2025) {
                    printf("We already passed the year %d.\n", eventptr -> yy);
                    printf("********************************\n");
                } else {
                    valid = 2;
                }
            }

            
            valid = 1;
            while (valid == 1) {
                printf("What is the month of your event (1 - 12)\n>> ");
                scanf(" %d", &eventptr->mm);
                printf("********************************\n");
                if (eventptr->mm < 1 || eventptr->mm > 12) {
                    printf("Invalid Month\n");
                    printf("********************************\n");
                } else {
                    valid = 2;
                }
            }

            
            valid = 1;
            while (valid == 1) {
                printf("What is the day of your event?\n>> ");
                scanf("%d", &eventptr->dd);
                printf("********************************\n");

                if ( (eventptr -> yy % 4 == 1 && eventptr -> mm == 2) && eventptr -> dd > 28 ||
    (eventptr -> yy % 4 == 0 && eventptr -> mm == 2) && eventptr -> dd > 29) {
        printf("Invalid Day\n");
        printf("********************************\n");
        
    } else if
       ( eventptr -> mm == 1 && eventptr -> dd > 31 || 
        eventptr -> mm == 3 && eventptr -> dd > 31 || 
        eventptr -> mm == 5 && eventptr -> dd > 31 ||
        eventptr -> mm == 7 && eventptr -> dd > 31 ||
        eventptr -> mm == 8 && eventptr -> dd > 31 ||
        eventptr -> mm == 10 && eventptr -> dd > 31 ||
        eventptr -> mm == 12 && eventptr -> dd > 31) {
        printf("Invalid Day\n");
        
    } else if ( eventptr -> mm == 4 && eventptr -> dd > 30 ||
        eventptr -> mm == 6 && eventptr -> dd > 30 || 
        eventptr -> mm == 9 && eventptr -> dd > 30 ||
        eventptr -> mm == 11 && eventptr -> dd > 30) {
        printf("Invalid Day\n");
        
    } else {
        valid = 2;
    }
            }

            if (dateExists(eventptr->dd, eventptr->mm, eventptr->yy)) {
                printf("The date has already been used!!\n");
            } else {
                different = 1;
            }
        }

        fprintf(pF, "*********************************************************\n");
        fprintf(pF, "Date of Event:%d/%d/%d\t Event Name: %s\n",
                eventptr->mm, eventptr->dd, eventptr->yy, eventptr->eventName);
        fclose(pF);

        
        printf("Would you like to add more?\n1. Add\n2. Exit\n>> ");
        scanf("%d", &add);
        getchar();
        if (add == 1) {
            j = j + 1;
        } else {
            printf("Exiting...\n");
        }
    }
}


int main () {

struct event eventlist;

int choice;
printf("********************************\n");
printf("Welcome to the Event Scheduler\n");
sleep(1);
printf("********************************\n");
printf("What would you like to do?\n1. Add Event\n2. View Events\n>> ");


scanf("%d",&choice);

getchar();
printf("********************************\n");
sleep(1);

if ( choice == 1 ) {
    eventsScheduler(&eventlist);
} else if ( choice == 2 ) {
    FILE *file = fopen("EventScheduler.txt", "r");
    if (file == NULL) {
        printf("No events found.\n");
        return 0;
    }

    char line[200];
    printf("Events:\n");
    

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }


    fclose(file);
}


return 0;
}