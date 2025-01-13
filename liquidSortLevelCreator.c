#include<stdio.h>
#include<stdlib.h>

#include "colors.h"

char buffer[256];

int verifyLevel(char* file)
{

}

int getNumber(void)
{
  fgets(buffer, 256, stdin);
  char* end;
  long num = strtol(buffer, &end, 10);

  return (int)num; //strtol will return 0 if there is an error, for my use case, I want numbers grater than 0 

}

int getColor(void)
{
  fgets(buffer, 256, stdin);
  char c = buffer[0];

  switch(c)
  {
    
  }

}


int main(void)
{
  printf("hello world\n");
  printf("%d\n", getNumber());


}
