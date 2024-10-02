#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define JOKER "\x5f\x75\x43\x30\x6e\x5f\x00"
#define TRUE  1
#define FALSE 0
#define OK    0
#define ERRO -1

void howtouse (char *sw_name);
int __is_valid_dynamic_token (char *password);
void create_tag (char *id);

int main (int argc, char *argv[]) {
  if (argc != 2) {
    howtouse(argv[0]);
    return ERRO;
  }

  if ( __is_valid_dynamic_token(argv[1]) ) {
    create_tag(argv[0]);
    printf("\n +-+ 무,무슨 ! +-+ \n");
  } else {
    printf("\n You r noob. \n");
  }

  return OK;
}

int __is_valid_dynamic_token (char *password) {
  char *token = (char *) malloc(30*sizeof(char));
  time_t time1;
  memset((char *)token, '\0', 30);
  sprintf(token, "%s_%d", JOKER, (int) time(&time1));

  if (! strncmp(token, password, 18) ) {
    return TRUE;
  }

  return FALSE;
}

void howtouse (char *sw_name) {
  printf(" ----------- [%s] ----------- \n", sw_name);
  printf(" ::. Usage: %s <DarimKey>\n\n", sw_name);
}

void create_tag (char *id) {
  FILE *fd;
  char *tag_name = (char *)malloc(24 * sizeof(char));
  memset(tag_name, '\0', 24);
  snprintf(tag_name,24, "./%s.tag", id);
  fd = fopen(tag_name, "w");
  if (fd != NULL) {
    fprintf(fd, "당했다!\n");
    fclose(fd);
  } else {
    printf("[!] 파일 열다가 오류 발생\n");
  }
}
