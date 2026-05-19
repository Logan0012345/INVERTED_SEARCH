/*Function to create data base*/

#include "invert.h"

extern int c_flag;
extern int u_flag;

int create_DB(Hash_t *arr, File_t *head)
{
    if((c_flag == 0 && u_flag == 1) || (c_flag == 0 && u_flag == 0))//checks create_DB calls only once and if update_DB calls it should be before create_DB
    {
        if(head == NULL)
            return FAILURE;
        File_t *temp_f = head;
        while(temp_f)
        {
            c_flag = 1;
            FILE *fptr = fopen(temp_f->filename,"r");
            if(fptr == NULL)
                return FAILURE;
            char str[30];    
            while(fscanf(fptr,"%s",str) == 1)
            {
                int index;
                if(isupper(str[0]))
                    index = str[0] - 'A';
                else if(islower(str[0]))
                    index = str[0] - 'a';
                else if(isdigit(str[0]))
                    index = 26;
                else
                    index = 27;//index for special characters
                if(arr[index].link == NULL)
                {
                    //create and update main node
                    Main_t *new_main = malloc(sizeof(Main_t));
                    if(!new_main)
                        return FAILURE;
                    strcpy(new_main->word,str);
                    new_main->file_count = 1;
                    new_main->mainlink = NULL;

                    //create and update sub node
                    Sub_t *new_sub = malloc(sizeof(Sub_t));
                    if(!new_sub)
                        return FAILURE;
                    strcpy(new_sub->filename,temp_f->filename);
                    new_sub->word_count = 1;     
                    new_sub->link = NULL;
                    new_main->sublink = new_sub;
                    //update hash teble index with main node
                    arr[index].link = new_main;
                }        
                else
                {
                    Main_t *temp_m = arr[index].link;
                    Main_t *prev_m = NULL;
                    int m_flag = 0;
                    while(temp_m)
                    {
                        prev_m = temp_m;
                        if(strcasecmp(temp_m->word,str) == 0)//check word is present in any main node or not
                        {
                            //check if the subnode for the filename and word is already created or not
                            Sub_t *temp_s = temp_m->sublink;
                            Sub_t *prev_s = NULL;
                            int s_flag = 0;
                            while(temp_s)
                            {
                                prev_s = temp_s;
                                if(strcmp(temp_s->filename,temp_f->filename) == 0)
                                {   
                                    s_flag = 1;
                                    m_flag = 1;
                                    temp_s->word_count++;//increment word count if the word is of the same file
                                }
                                temp_s = temp_s->link;
                            }
                            if(s_flag == 0)
                            {
                                //word is present but filename name not found in sub nodes
                                Sub_t *new_sub = malloc(sizeof(Sub_t));//create new sub node if the subnode for the filename is not found 
                                if(!new_sub)
                                    return FAILURE;
                                strcpy(new_sub->filename,temp_f->filename);
                                new_sub->word_count = 1;     
                                new_sub->link = NULL;
                                temp_m->file_count++;
                                prev_s->link = new_sub;

                                m_flag = 1;
                            }
                        }
                        temp_m = temp_m->mainlink;
                    }
                    if(m_flag == 0)//if word is not present in the hash table
                    {
                        //if word is not present
                        Main_t *new_main = malloc(sizeof(Main_t));
                        if(!new_main)
                            return FAILURE;
                        strcpy(new_main->word,str);
                        new_main->file_count = 1;
                        //new_main->mainlink = NULL;
                        
                        Sub_t *new_sub = malloc(sizeof(Sub_t));
                        if(!new_sub)
                            return FAILURE;
                        strcpy(new_sub->filename,temp_f->filename);
                        new_sub->word_count = 1;     
                        new_sub->link = NULL;
                        new_main->sublink = new_sub;
                        prev_m->mainlink = new_main;
                    }
                }
            }   
            temp_f = temp_f->link; 
        }
    }
    else{
        printf("Usage: Create_DB only after Update_DB\n");
        if(c_flag == 1)
            printf("Create_DB already Done...!");
    }

    return SUCCESS;
}