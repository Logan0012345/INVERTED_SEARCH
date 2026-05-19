/*Function to search datas in database which is stored in hash table*/

#include "invert.h"

int search_DB(Hash_t *arr)
{
    char input[30];
    printf("Enter the word to search : ");
    scanf("%s",input);
    //to find index in hash table
    int index;
    if(isupper(input[0]))
        index = input[0] - 'A';//when first character is upper case  
    else
        index = input[0] - 'a';//when fisrt character is lower case
    
    if(arr[index].link == NULL)
    {
        printf("DATA NOT FOUND\n");
        return FAILURE;
    }

    Main_t *m_temp = arr[index].link;
    while(m_temp)
    {
        if(strcasecmp(m_temp->word,input) == 0)
        {
            printf("WORD : %s\tFILE COUNT : %d\n",input,m_temp->file_count);//print word and file count
            Sub_t *s_temp = m_temp->sublink;
            while(s_temp)
            {
                printf("FILE NAME : %s\tWORD COUNT : %d\n",s_temp->filename,s_temp->word_count);//print file name and word count
                s_temp = s_temp->link;
            }
            return SUCCESS;
        }
        m_temp = m_temp->mainlink;
    }
    printf("DATA NOT FOUND\n");
    return FAILURE;
}