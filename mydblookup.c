
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mdb.h"
#include "mylist.h"
#define BUFFERSIZE 1000


int loadmdb(FILE *fp, struct List *dest){
    
    int counter = 0; 
    struct MdbRec *one = malloc(sizeof(struct MdbRec));
    struct Node *temp;
    temp = NULL;

     //need to read one item at a time
     while(fread(one, sizeof(struct MdbRec), 1, fp) == 1){
         temp = addAfter(dest, temp, one);
         one = malloc(sizeof(struct MdbRec));
         //should add temp after temp continuously
         //into the list. 
         counter++;

         if(one == NULL){
             perror("malloc is NULL");
             exit(1);
          }   
     }
    
    free(one); 
    //this returns only the orginal pointer
    return counter; 
    //return number of MdbRecs loaded onto the list
    //to use later for line number
 
}

void freemdb(struct List *list){
    
    struct Node *temp=list->head;
    //must free all the MdbRecs in the
    //nodes that were malloced
    while (temp!=NULL){
        free(temp->data);
        temp = temp->next;
    }
    //now remove all nodes
    removeAllNodes(list);
}


int main(int argc, char **argv){

    FILE *db = fopen(argv[1],"rb");
    char buffer[BUFFERSIZE];
    //created a buffersize for entry because wont 
    //exceed 1000 chars

    struct List list;
    initList(&list);
     
    //load the entries into the list
    loadmdb(db,&list); 
    char input[5];      
    struct MdbRec *two;

    //print lookup intially and this enters the main while loop
    printf("lookup: ");
    while((fgets(buffer,BUFFERSIZE,stdin) != NULL)){
     //while there is no Ctrl-D or EOF entered it runs
           memset(input, '\0', sizeof(input));
           //intialize all of input to be null
           //and then copy over 5 characters from
           //the buffer
           strncpy(input,buffer, 5); 
           input[5] = '\0';
           //make sure it nulls terminates

           struct Node *node = list.head;
           char *n,*m;
           int counter = 1;
           //database entries start at one

           //traverse the list
           while(node != NULL){
             two = node->data;
             //set the pointer to be the data for each node

             //if found in name of node then it prints
             if(((strstr(two->name,input))) != NULL){
                 n = strstr(two->name, input); 
                 printf("%i: {%s}",counter,n);
                 printf(" said {%s}\n", two->msg);
                 printf("\n"); 
                 
             }       
             //if found in msg of node then it also prints
             else if(((strstr(two->msg,input))) != NULL){
                 m = strstr(two->msg,input);
                 printf("%i: {%s} said {%s}\n",counter,two->name,m);
                 
             }    

             node = node->next;
             //keep travesing list and 
             //set the strings to null.
             n = "";
             m = "";
             counter++;
           } 
           printf("lookup: ");
      
      }

    freemdb(&list);
    fclose(db);
    return 0; 
}
