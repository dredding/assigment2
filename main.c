#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct pair
{
  char op;
  float val;
};

struct organism
{
  struct pair genes[30];
  int size;
  double fitness;
};

void genetic_algorithm(int start, int final, float time, struct pair * nodes[], int num_nodes, struct timeval time1);
void create_population(struct organism * pop[], int pop_size, struct pair * nodes[], int num_nodes);
double fitness_function(struct organism * indiv, int start, int final);

int main(int argc, char * argv[])
{
  FILE *file;
  int start, final, ret, i = 0, j = 0;
  float time;
  char* search_type;
  struct pair * nodes[15];
  struct timeval time1;

  gettimeofday(&time1, NULL);

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

  // printf("%s\n%d\n%d\n%f\n", search_type, start, final, time);
  
  do
  {
    struct pair * hold = (struct pair*)malloc(sizeof(struct pair));
    ret = fscanf(file, " %c", &hold->op);
    ret += fscanf(file, "%f", &hold->val);

    if(ret != 2)
      break;
    
    nodes[i] = hold;
  
  // printf("ret: %d op: %c val: %f\n", ret, nodes[i]->op, nodes[i]->val);

    i++;
  } while(1);

  if(strncmp("genetic", search_type, 10) == 0)
  {
    genetic_algorithm(start, final, time, nodes, i, time1);
  }

  for(j = 0; j < i; j++)
  {
    free(nodes[j]);
  }
}

void genetic_algorithm(int start, int final, float time, struct pair * nodes[], int num_nodes, struct timeval time1)
{
  int i, j, org_size, population_size = 10;
  struct organism * population[population_size];
  struct timeval time2;
  
  create_population(population, population_size, nodes, num_nodes);

  /* check population was created correctly 
  for(i = 0; i < population_size; i++)
  {
    org_size = population[i]->size;
    printf("organism: %d, size: %d\n", i, org_size);
    for(j = 0; j < org_size; j++)
    {
      printf("gene: %d, op: %c, val: %f\n", j, population[i]->genes[j].op, population[i]->genes[j].val);
    }
  }
  */

  for(i = 0; i < population_size; i++)
  {
    fitness_function(population[i], start, final);
    printf("organism: %d fitness: %lf\n", i, population[i]->fitness);
  }
  
}

void create_population(struct organism * pop[], int pop_size, struct pair * nodes[], int num_nodes)
{
  int i, j, org_size, op_num;
  time_t t;

  srand((unsigned) time(&t));
  
  for(i = 0; i < pop_size; i++)
  {
    struct organism * indiv = (struct organism*)malloc(sizeof(struct organism));
    org_size =  1 + rand() % 30;
    indiv->size = org_size;
    
    for(j = 0; j < org_size; j++)
    {
      op_num = rand() % num_nodes;
      indiv->genes[j].op = nodes[op_num]->op;
      indiv->genes[j].val = nodes[op_num]->val;
    }
    pop[i] = indiv;
  }
}

double fitness_function(struct organism * indiv, int start, int final)
{
  int i, j, size = indiv->size;
  double total_val = start, fitness;

  for(i = 0; i < size; i++)
  {
    switch(indiv->genes[i].op)
    {
    case '+':
      total_val = total_val + indiv->genes[i].val;
      break;
    case '-':
      total_val = total_val - indiv->genes[i].val;
      break;
    case '/':
      total_val = total_val / indiv->genes[i].val;
      break;
    case '*':
      total_val = total_val * indiv->genes[i].val;
      break;
    case '^':
      pow(total_val, indiv->genes[i].val);
      break;
    default:
      printf("Invalid input in file");
    }
  }
  
  fitness = abs(final - total_val);

  indiv->fitness = fitness;

  return fitness;
}
