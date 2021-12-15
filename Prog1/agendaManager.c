#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct EventObj{
    char *name;
    int time;
} EventObj;
typedef EventObj* EventPtr;


// provided for output header formatting
void print(ListPtr l, char *agenda_name) {
    printf("======== %s ========\n", agenda_name);
    // print the content of the list 
    printList(l); 
    printf("===== END OF %s =====\n", agenda_name);
}

bool dataEqual (void *obj1, void *obj2){
    bool checker = false;
    EventPtr myevnt1 = (EventObj*) obj1; 
    EventPtr myevnt2 = (EventObj*) obj2;
    if (strcmp(myevnt1->name, myevnt2->name)==0){
        checker = true; 
    }
    return checker; 
}

void dataPrinter (void *data){
    EventPtr myevnt = (EventObj*) data; 
    int evnttime = myevnt -> time; 
    if(evnttime < 10){
        printf("%s","0"); 
    }
    printf("%d",evnttime);
	printf("%s",":00 ");
    printf("%s", myevnt -> name);
}

void freeData (void *data){
    EventPtr myevnt = (EventObj*) data;
    free(myevnt); 
}

// helper functions created by me to help swap the elements of the list
void swap(ListPtr L, char *evtn1, char *evtn2){
    EventObj* tevt1 =  malloc(sizeof(EventObj));
    EventObj* tevt2 =  malloc(sizeof(EventObj));

    tevt1 -> name = evtn1; 
    tevt2 -> name = evtn2;
    int e1Index = findElement(L, tevt1); 
    int e2Index = findElement(L, tevt2); 

    tevt1 = getElement(L, e1Index); 
    tevt2 = getElement(L, e2Index); 
    //swapping the times of both the events
    int tempTime = tevt1 -> time; 
    tevt1 -> time = tevt2 -> time; 
    tevt2 -> time = tempTime; 
    insertElement(L, e1Index, tevt1);
    delElement(L, e1Index+1);
    insertElement(L, e2Index, tevt2);
    delElement(L, e2Index+1);  
}

void merge(ListPtr L1, ListPtr L2){
    int length2 = length(L2);
    //printf("%d", length2); 
    int counter =0; 
    /*while(counter < length2){
        if(getElement(L2, counter)!= NULL){
            appendList(L1, getElement(L2, counter));
        }
        else{
            printf("GetElement error"); 
        }  
        counter++; 
    }*/
}

int main(int argc, char **argv) {
	// declare 2 lists
    
    //------CREATING--VARIABLES--------------------------
    int num_lists = 0; 
    ListPtr mylist1 = newList(&dataEqual, &dataPrinter, &freeData); 
    ListPtr mylist2 = newList(&dataEqual, &dataPrinter, &freeData); 
    
    //testing the functions
    
    EventObj* e1 =  malloc(sizeof(EventObj)); 
    e1 -> name = "Coffee time"; 
    e1 -> time = 9;
    EventObj* e2 =  malloc(sizeof(EventObj)); 
    e2 -> name = "School"; 
    e2 -> time = 10; 
    EventObj* e3 =  malloc(sizeof(EventObj)); 
    e3 -> name = "Break time"; 
    e3 -> time = 13;
    EventObj* e4 =  malloc(sizeof(EventObj));
    e4 -> name = "Name time"; 
    e4 -> time = 18; 
    EventObj* e5 =  malloc(sizeof(EventObj));
    e5 -> name = "false event"; 
    e5 -> time = 22; 

    char action[30]; 
    char *agendaName1 = NULL;  
    char *mergename1[30]; 
    char *mergename2[30]; 
    char *agendaName2 = NULL; 
    char eventName1[100];
    char eventName2[30];  
    char *tempagenda[30]; 
    int startTime; 
    int agendacounter = 0; 

    char var_add[] = "ADD";
    char var_del[] = "DEL";
    char var_swap[] = "SWAP"; 
    char var_print[] = "PRINT"; 
    char var_merge[] = "MERGE";

    //------MANUAL---TESTING--------------------------
    //dataPrinter(e1); 
    //bool appendchecker = appendList(mylist2, e1); 
    //appendList(mylist2, e2); 
    //print(mylist2, "test2"); 
    //appendList(mylist2, e3);
    //appendList(mylist2, e4);
    //print(mylist2, "2");
    //printf("Length of List 2: %d\n", mylist2 -> length);
    //printf("lengthtesting1 : %d\n", length(mylist1)); 
    //if (getElement(mylist1, 3)== NULL){
    //    printf("True"); 
    //} 
    //printf("\n"); 
    //print(mylist1, "mylist1");
    //print(mylist2, "mylist2"); 
    //appendList(mylist1, e4); 
    //appendList(mylist1, e5); 
    //print(mylist1, "1");
    //printf("lengthtesting1 : %d\n", length(mylist1)); 
    //printf("length: %d", mylist1->length); 
    //merge(mylist2, mylist1);
    //print(mylist2, "merged");
    
    //print(mylist1, "test"); 
    //delElement(mylist1, 5);
    //dataPrinter(delElement(mylist1, 0)); 
    //printf("\n"); 
    //print(mylist1, "test");
    //printf("%s", "\n"); 
    //printf("%s", "\n");
    //print(mylist1, "Other");
    //printf("finding: %d\n", findElement(mylist1, e5)); 
    //printf("\n\n testing\n"); 
    //dataPrinter(getElement(mylist1, 3)); 
    //NOTES:
    // use array for the list management check length of array easily 

    
	// accept input from the user 
    //-----------------READING--FROM--FILE-----------   
    
    //print(mylist1, "testing"); 
    
    
    while(!feof(stdin)){
		scanf("%s", action);
        // if action ADD "<AGENDA_NAME>" "<EVENT_NAME>" <START_TIME>
        if (strcmp(action, var_add)==0){
            int findObj; 
            EventObj* tempEvt =  malloc(sizeof(EventObj));
            // source used stack overflow: https://stackoverflow.com/questions/17214026/ignoring-separating-character-using-scanf
            // \" ignores the space and the quote and gets everything in between
            scanf(" \"%[^\"]\" ", tempagenda);
            scanf(" \"%[^\"]\" ", eventName1);
            scanf("%d", &startTime);

            //printf("tempagenda: %s\n", tempagenda);
            //printf("event1: %s\n", eventName1);
            //printf("starttime: %d\n", startTime);

            tempEvt -> name = strdup(eventName1); 
            tempEvt -> time = startTime; 
            //dataPrinter(tempEvt); 
            //printf("\n"); 
            //print(mylist1, "testing"); 

            findObj = findElement(mylist1, tempEvt);
            //checking for same time event
            //int looper =0;
            //while(looper < ((mylist1-> length)-1)){
            //    if(getElement(mylist1, looper)!=NULL){
            //        if((getElement(mylist1, looper))->time == tempEvt-> time){
            //            printf("\nERROR: Already an event at that time\n"); 
            //        }
            //    }

            //} 
            if(findObj== -1){
                appendList(mylist1, tempEvt);
            }
            else{
                printf("\nERROR: Already an event with that name\n");
            }              
        }
        // if action DEL "<AGENDA_NAME>" "<EVENT_NAME>"
        else if (strcmp(action, var_del)==0){
            EventObj* tempEvt =  malloc(sizeof(EventObj));
            int find_obj; 
            scanf(" \"%[^\"]\" ", tempagenda);
            scanf(" \"%[^\"]\" ", eventName1);
            tempEvt -> name = eventName1; 
            tempEvt -> time = 0;
            // trying to find the object to delete 
            find_obj = findElement(mylist1, tempEvt);
            // deleting object at a given specific location 
            delElement(mylist1, find_obj);  
        }
        // if action SWAP "<AGENDA_NAME>" "<EVENT_NAME_1>" "<EVENT_NAME_2>"
        else if (strcmp(action, var_swap)==0){
            scanf(" \"%[^\"]\" ", agendaName1);
            scanf(" \"%[^\"]\" ", eventName1);
            scanf(" \"%[^\"]\" ", eventName2); 
            swap(mylist1, eventName1, eventName2);     
        }
        // if action PRINT "<AGENDA_NAME>"
        else if (strcmp(action, var_print)==0){
            scanf(" \"%[^\"]\" ", tempagenda); 
            //printf("\ntempagenda: %s\n", tempagenda); 
            print(mylist1, tempagenda);
        }
        // if action MERGE "<AGENDA_NAME_1>" "<AGENDA_NAME2>"
        else if (strcmp(action, var_merge)==0)
        {
            scanf(" \"%[^\"]\" ", mergename1);
            scanf(" \"%[^\"]\" ", mergename2);
            //printf("\agendanaem1: %s\n", mergename1);
            //printf("\aagendaname : %s\n", mergename2);
        }
        // if action None not an action from the list
        else{
            printf("ERROR: this command does not exist.\n%s", action); 
        }		 	
	} 
	//free(current_line); 
    // process input and modify appropriate list   

	// be sure to release memory
}