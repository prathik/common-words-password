#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

char* getRandomWord(char* password, int length, int level) {
  char ch, word[40];
  FILE *fp;
  char fileToOpen[9] = "/words";
  char fullFileName[100]={0};
  int randomFile,m,n;
  int i=0,j=0,lineToBeSelected, currentLine = 0, numberOfWords=0;
  srand(time(NULL));
  while(numberOfWords != length) {
    randomFile = rand()%level;
    m = (randomFile)%26;
    n = ((randomFile - m)/26);
    fileToOpen[6] = 97+n;
    fileToOpen[7] = 97+m;
    fileToOpen[8] = '\0';
    strcpy(fullFileName, DATADIR);
    strcat(fullFileName, fileToOpen);
    fp = fopen(fullFileName, "r");
    if(fp == NULL) {
      perror("Error while opening the file.");
      exit(EXIT_FAILURE);
    }
    if(strcmp(fileToOpen, "/wordsmv") == 0){
      lineToBeSelected = rand() % 333;
    } else {
      lineToBeSelected = rand() % 1000;
    }

    lineToBeSelected++;
    currentLine = 0;
    while(currentLine != lineToBeSelected) {
      i = 0;
      while((ch = fgetc(fp)) != '\n' && ch != EOF) {
	word[i++] = ch;
      }
      word[i] = '\0';
      currentLine++;
    }
    i = 0;
    while(word[i] != '\0') {
      password[j++] = word[i++];
    }
    fclose(fp);
    numberOfWords++;
  }
  password[j] = '\0';
  return password;
}

int main(int argc, char **argv) {
  char c,word[200];
  int level = 0;

  while((c = getopt(argc, argv, "l:")) != -1) {
    switch(c) {
    case 'l':
      level = (int)strtol(optarg, NULL, 10);
      break;
    case '?':
      if(optopt == 'l') {
	fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      } else {
	fprintf(stderr, "Unknown option. Usage pwgen -l <1-334>");
      }
    }
  }
  if(level == 0 || level > 334) {
    fprintf(stderr, "Invalid level. Usage pwgen -l <1-334>");
    return 1;
  }
  printf("Password: %s\n", getRandomWord(word,4,level));
  return 0;
}
