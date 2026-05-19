/*Function to save database*/

#include "invert.h"

int save_DB(Hash_t *arr)
{
    char file[30];
    printf("Enter Name of your Backup file : ");
    scanf("%s",file);
    FILE *fptr = fopen(file,"w");
    if(fptr == NULL)
    {
        printf("FILE OPEN FAILED\n");
        return FAILURE;
    }
    for(int i=0;i<28;i++)
    {
        if(arr[i].link != NULL)
        { 
            
            Main_t *m_temp = arr[i].link;
            while(m_temp)
            {
                fprintf(fptr,"#");
                fprintf(fptr,"%d;%s;%d",i,m_temp->word,m_temp->file_count);
                Sub_t *s_temp = m_temp->sublink;
                while(s_temp)
                {
                    fprintf(fptr,";%s;%d",s_temp->filename,s_temp->word_count);
                    s_temp = s_temp->link;
                }
                m_temp = m_temp->mainlink;
                fprintf(fptr,"#");
                fprintf(fptr,"\n");
            }
            //fprintf(fptr,"\n");
        }
    }
    fclose(fptr);
    return SUCCESS;
}