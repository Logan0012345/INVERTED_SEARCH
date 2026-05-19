
/*
NAME : Loganathan S
DATE : 02-03-2026

Description : 

An inverted index is an index data structure storing a mapping from content, such as words or numbers, to its locations in a 
database file, or in a document or a set of documents. The purpose of an inverted index is to allow fast full text searches, 
at a cost of increased processing when a document is added to the database. The inverted file may be the database file itself, 
rather than its index. It is the most popular data structure used in document retrieval systems, used on a large scale for example 
in search engines. The purpose of this project is to implement the inverted search using Hash Algorithms.

Sample Input/Output:
 Menu Bar
                            1.Create_DB
                            2.Search_DB
                            3.Display_DB
                            4.Save_DB
                            5.Update_DB
                            6.Exit
                    Enter Choice : 5
                    Enter Name of your Backup file : savefile.txt
                    Menu Bar
                            1.Create_DB
                            2.Search_DB
                            3.Display_DB
                            4.Save_DB
                            5.Update_DB
                            6.Exit
                    Enter Choice : 3
                    INDEX : 6       WORD : GOAT     FILE COUNT : 1
                            FILE NAME : f2.txt      WORD COUNT : 1
                    INDEX : 7       WORD : Hello    FILE COUNT : 2
                            FILE NAME : f1.txt      WORD COUNT : 2
                            FILE NAME : f2.txt      WORD COUNT : 1
                    INDEX : 7       WORD : Hi       FILE COUNT : 2
                            FILE NAME : f1.txt      WORD COUNT : 1
                            FILE NAME : f2.txt      WORD COUNT : 2
                    INDEX : 17      WORD : Ronaldo  FILE COUNT : 1
                            FILE NAME : f1.txt      WORD COUNT : 1
                    INDEX : 18      WORD : Suiiiii  FILE COUNT : 1
                            FILE NAME : f1.txt      WORD COUNT : 1
                    INDEX : 18      WORD : Subin    FILE COUNT : 1
                            FILE NAME : f2.txt      WORD COUNT : 1
                    INDEX : 26      WORD : 123456   FILE COUNT : 1
                            FILE NAME : f1.txt      WORD COUNT : 1
                    INDEX : 27      WORD : !@#$%^&* FILE COUNT : 1
                            FILE NAME : f2.txt      WORD COUNT : 1
                    Menu Bar
                            1.Create_DB
                            2.Search_DB
                            3.Display_DB
                            4.Save_DB
                            5.Update_DB
                            6.Exit
                    Enter Choice : 5
                    Uasge: Update_DB alraedy done...!
                    Menu Bar
                            1.Create_DB
                            2.Search_DB
                            3.Display_DB
                            4.Save_DB
                            5.Update_DB
                            6.Exit
                    Enter Choice :

*/


#include "invert.h"

int c_flag;
int u_flag;

int validate(int argc,char *argv[], File_t **head)
{
    for(int i=1;i<argc;i++)
    {
        char *ch = strchr(argv[i],'.');
        if(ch == NULL)
            return FAILURE;
        if(strcmp(ch,".txt") == 0)
        {
            FILE *fptr = fopen(argv[i],"r");
            if(fptr == NULL)
            {
                printf("FILE OPEN FAILED\n");
                continue;
            }
            char ch;    
            if(fgetc(fptr) == EOF)
            {
                printf("%s is empty...!\n",argv[i]);
            }
            else
                insert_last(head,argv[i]);        
            fclose(fptr);
        }
        else
        {
            printf("%s is unsupported\nusage: %s <file name> <file name> ...\n",argv[i],argv[0]);
        }
    }

    if(remove_duplicate(head) == SUCCESS)
        return SUCCESS;
    else
        return FAILURE;
}


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        File_t *file_head = NULL;
        if(validate(argc,argv,&file_head) == SUCCESS)
        {
            Hash_t arr[28];
            for(int i=0;i<28;i++)
            {
                arr[i].index = i;
                arr[i].link = NULL;
            }
            int choice;
            while(1)
            {
                printf("Menu Bar\n\t1.Create_DB\n\t2.Search_DB\n\t3.Display_DB\n\t4.Save_DB\n\t5.Update_DB\n\t6.Exit\nEnter Choice : ");
                scanf("%d",&choice);
                getchar();
                switch(choice)
                {
                    case 1:
                        create_DB(arr,file_head);
                        break;
                    case 2:
                        search_DB(arr);   
                        break;
                    case 3:
                        display_DB(arr);
                        break;     
                    case 4:
                        save_DB(arr);
                        break;  
                    case 5:
                        update_DB(arr,&file_head);
                        break;
                    case 6:
                        exit(0);
                        break;
                    default : 
                        printf("INVALID CHOICE...!\n");              
                }
            }
        }
        else
        {
            printf("INVALID ARGUMENTS PASSED...!\nusage: %s <file name> <file name> ...\n",argv[0]);
        }
    }
    else
    {
        printf("NO ARGUMENTS PASSED...!\nusage: %s <file name> <file name> ...\n",argv[0]);
    }
}