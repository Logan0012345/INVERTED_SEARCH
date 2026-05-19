#include "invert.h"

extern int c_flag;
extern int u_flag;

int update_DB(Hash_t *arr, File_t **f_head)
{
    if(c_flag == 0 && u_flag == 0)
    {
        char file[30];
        printf("Enter Name of your Backup file : ");
        scanf("%s",file);
        FILE *fptr = fopen(file,"r");
        if(fptr == NULL)
        {
            printf("FILE OPEN FAILED\n");
            return FAILURE;
        }
        
        int index;
        char ch;
        while((ch = fgetc(fptr)) !=  EOF)
        {
            if(ch != '#')
                continue;
            Main_t *new_main = malloc(sizeof(Main_t));
            if(!new_main)
                return FAILURE;
            fscanf(fptr,"%d;%[^;];%d",&index,new_main->word,&new_main->file_count);//read word and file count
            new_main->mainlink = NULL;
            new_main->sublink = NULL;

            if(arr[index].link == NULL)
                arr[index].link = new_main;
            else
            {
                Main_t *m_temp = arr[index].link;
                while(m_temp->mainlink)
                    m_temp = m_temp->mainlink;
                m_temp->mainlink = new_main;   
            }    
            for(int i=0;i<new_main->file_count;i++)
            {
                Sub_t *new_sub = malloc(sizeof(Sub_t));
                if(!new_sub)
                    return FAILURE;
                fscanf(fptr,";%[^;];%d",new_sub->filename,&new_sub->word_count);//read file name and word count
                update_file_sll(new_sub->filename,f_head);
                new_sub->link = NULL;

                if(new_main->sublink == NULL)
                    new_main->sublink = new_sub;
                else
                {
                    Sub_t *s_temp = new_main->sublink;
                    while(s_temp->link)
                        s_temp = s_temp->link;
                    s_temp->link = new_sub;    
                }        
            }
            fgetc(fptr);//skip "#"
            fgetc(fptr);//skip '\n'
        }
        fclose(fptr);
        
        u_flag = 1;

    }
    else
    {
        printf("Uasge: Update_DB alraedy done...!\n");
    }
    return SUCCESS;
}