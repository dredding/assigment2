#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct pair
{
  char op;
  float val;
};

void genetic_algorithm(int start, int final, float time, struct pair * nodes[], int num_nodes);

int main(int argc, char * argv[])
{
  FILE *file;
  int start, final, ret, i = 0, j = 0;
  float time;
  char* search_type;
  struct pair * nodes[15];

  if(2 != argc)
  {
    printf("invalid arguments\n");
    exit(0);
  }

  if((file = fopen(argv[1], "r")) == NULL)
  {
    printf("failed to open file\n");
    exit(0);
  }
    
  search_type = (char*)malloc(15);

  if((ret = fscanf(file, "%s %d %d %f", search_type, &start, &final, &time)) != 4)
  {
     printf("%d\n", ret);
     exit(0);
  }

  printf("%s\n%d\n%d\n%f\n", search_type, start, final, time);
  
  do
  {
    struct pair * hold = (struct pair*)malloc(sizeof(struct pair));
    ret = fscanf(file, " %c", &hold->op);
    ret += fscanf(file, "%f", &hold->val);

    if(ret != 2)
      break;
    
    nodes[i] = hold;
  
    printf("ret: %d op: %c val: %f\n", ret, nodes[i]->op, nodes[i]->val);

    i++;
  } while(1);

  if(strncmp("genetic", search_type, 10) == 0)
  {
    //genetic_algorithm(start, final, time, nodes, i);
  }

  for(j = 0; j < i; j++)
  {
    free(nodes[j]);
  }
}

void genetic_algorithm(int start, int final, float time, struct pair * nodes[], int num_nodes)
{

}
