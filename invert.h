#ifndef INVERT
#define INVERT

#define SUCCESS 0
#define FAILURE -1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct sub_st
{
    char filename[40];
    int word_count;
    struct sub_st *link;
}Sub_t;

typedef struct main_st
{
    char word[30];
    int file_count;
    struct main_st *mainlink;
    struct sub_st *sublink;
}Main_t;

typedef struct file_st
{
    char filename[30];
    struct file_st *link;
}File_t; 

typedef struct hash_st
{
    int index;
    struct main_st *link;
}Hash_t;

int validate(int argc,char *argv[], File_t **head);
int create_DB(Hash_t *arr, File_t *head);
int insert_last(File_t **head,char *str);
int search_DB(Hash_t *arr);
int display_DB(Hash_t *arr);
int save_DB(Hash_t *arr);
int update_DB(Hash_t *arr, File_t **f_head);
int update_file_sll(char *filename, File_t **f_head);
int remove_duplicate(File_t **head);
#endif