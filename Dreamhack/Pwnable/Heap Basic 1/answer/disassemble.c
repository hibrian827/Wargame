#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct node {
  int id;
  int len;
  char* info;
  struct node* next;
};

struct node * root;

void make(void)
{
  struct node *ptr; // [rsp+8h] [rbp-8h]

  ptr = malloc(0x18);
  puts("note number");
  printf(">> ");
  scanf("%d", &ptr->id);
  puts("length of information");
  printf(">> ");
  scanf("%d", &ptr->len);
  if ( ptr->len >= 0 )
  {
    ptr->info = malloc(ptr->len);
    puts("info");
    printf(">> ");
    read(0, ptr->info, ptr->len);
    ptr->next = root;
    root = ptr;
  }
  else
  {
    puts("invalid information length");
    free(ptr);
  }
}

void copy(void)
{
  int v1; // [rsp+0h] [rbp-20h] BYREF
  int v2; // [rsp+4h] [rbp-1Ch] BYREF
  struct node* i; // [rsp+8h] [rbp-18h]
  struct node* j; // [rsp+10h] [rbp-10h]

  puts("src note number");
  printf(">> ");
  scanf("%d", &v1);
  puts("dist note number");
  printf(">> ");
  scanf("%d", &v2);
  for ( i = root; i && i->id != v1; i = i->next )
    ;
  for ( j = root; j && j->id != v2; j = j->next )
    ;
  if ( i && j )
  {
    if ( i->len <= j->len )
    {
      strcpy(j->info, i->info);
    }
    else
    {
      puts("size of src > size of dist, only copy partial");
      strncpy(j->info, i->info, j->len);
    }
    puts("copy successed");
  }
  else
  {
    puts("src or dist doesn't exist");
  }
  return;
}

void remove()
{
  int v1; // [rsp+4h] [rbp-1Ch] BYREF
  struct node *ptr; // [rsp+8h] [rbp-18h]
  struct node *v3; // [rsp+10h] [rbp-10h]

  v3 = 0;
  puts("note number");
  printf(">> ");
  scanf("%d", &v1);
  for ( ptr = root; ; ptr = ptr->next )
  {
    if ( !ptr )
    {
      puts("doesn't exist");
      return;
    }
    if ( ptr->id == v1 )
      break;
    v3 = ptr;
  }
  if ( ptr == root )
    root = root->next;
  else
    v3 = v3->next;
  free(ptr->info);
  free(ptr);
  puts("removed");
  return;
}

int main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+Ch] [rbp-34h] BYREF
  char buf[40]; // [rsp+10h] [rbp-30h] BYREF
  unsigned long v6; // [rsp+38h] [rbp-8h]

  setbuf(stdin, 0);
  setbuf(_bss_start, 0);
  puts("Welcome to my house");
  puts("what is your name?");
  read(0, buf, 0x20);
  printf("%s, what do you want to do?\n", buf);
  while ( 1 )
  {
    v4 = 0;
    puts("1. make note");
    puts("2. copy note");
    puts("3. delete");
    puts("4. change user name");
    puts("5. exit");
    printf(">> ");
    scanf("%d", &v4);
    switch ( v4 )
    {
      case 1:
        make();
        break;
      case 2:
        copy();
        break;
      case 3:
        remove();
        break;
      case 4:
        puts("new name");
        printf(">> ");
        read(0, buf, 0x20);
        printf("Hello %s\n", buf);
        break;
      case 5:
        return 0;
      default:
        puts("invalid input\n");
        break;
    }
  }
}