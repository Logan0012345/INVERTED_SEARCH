/*Function to display datas stored in hash table*/

#include "invert.h"

int display_DB(Hash_t *arr)
{
    for(int i=0;i<28;i++)
    {
        if(arr[i].link != NULL)
        {
            Main_t *m_temp = arr[i].link;
            while(m_temp)
            {
                printf("INDEX : %d\tWORD : %s\tFILE COUNT : %d\n",i,m_temp->word,m_temp->file_count);//print word and file count
                Sub_t *s_temp = m_temp->sublink;
                while(s_temp)
                {
                    printf("\tFILE NAME : %s\tWORD COUNT : %d\n",s_temp->filename,s_temp->word_count);//print file name and word count
                    s_temp = s_temp->link;
                }
                m_temp = m_temp->mainlink;
            }
        }
    }
    return SUCCESS;
}