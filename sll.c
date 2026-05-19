#include "invert.h"

int insert_last(File_t **head,char *str)
{
    File_t *new = malloc(sizeof(File_t));
    if(!new)
        return FAILURE;
    strcpy(new->filename,str);
    new->link = NULL;
    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }    
    File_t *temp = *head;
    while(temp->link)
        temp = temp->link;
    temp->link = new;
    return SUCCESS;    
}

int remove_duplicate(File_t **head)
{
    if(*head == NULL)
        return FAILURE;
    File_t *temp = *head;
    File_t *cur = (*head)->link;
    File_t *prev = NULL;
    
    while(temp)
    {
        cur = temp->link;
        prev = temp;
        while(cur)
        {
            if(strcmp(temp->filename,cur->filename) == 0)
            {
                prev->link = cur->link;
                free(cur);
                cur = prev->link;
            }
            else
            {
                prev = cur;
                cur = cur->link;
            }
        }
        temp = temp->link;
    }
    return SUCCESS;
}

int update_file_sll(char *filename, File_t **f_head)
{
    if(*f_head == NULL)
        return FAILURE;
    File_t *f_temp = *f_head;
    File_t *prev = NULL;
    while(f_temp)
    {
        if(strcmp(f_temp->filename,filename) == 0)
        {
            if(f_temp == *f_head)
            {
                *f_head = f_temp->link;
                free(f_temp);
                f_temp = *f_head;
            }
            else
            {
                prev->link = f_temp->link;
                free(f_temp);
                f_temp = prev->link;
            }
        }
        else
        {
            prev = f_temp;
            f_temp = f_temp->link;
        }
    }

    return SUCCESS;
}