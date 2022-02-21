// NICKOLAS UKASINSKI - GRR20193940
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  short int h;
  short int m;
  short int s;
} t_time;

typedef struct
{
  t_time key;
  char *value;
  struct t_timetable *r;
  struct t_timetable *l;
} t_timetable;

t_time string_to_time(char *hora);
t_timetable *init();
void put(t_timetable **t, char *key, char *value);
const char *get(t_timetable **t, char *key);
void max(t_timetable **t);
void min(t_timetable **t);

t_timetable *init() // aloca memória para o nodo
{
  t_timetable *p;
  p = (t_timetable *)malloc(sizeof(t_timetable));
  if (!p)
  {
    printf("Problema de alocação");
    exit(0);
  }
  p->l = NULL;
  p->r = NULL;

  return p;
}

const char *get(t_timetable **t, char *key)
{
  t_timetable *aux;
  t_time search_key = string_to_time(key);

  aux = *t;
  int find = time_cmp(aux->key, search_key);
  while (find != 0)
  {
    if (find == 1)
      aux = aux->l;
    else
      aux = aux->r;
    if (aux == NULL)
      return ("NOT FOUND.");
    find = time_cmp(aux->key, search_key);
  }
  return (aux->value);
}

void put(t_timetable **t, char *key, char *value)
{
  t_timetable *branch, *aux, *ant;
  branch = init();

  branch->key = string_to_time(key);
  branch->value = value;
  if ((*t) == NULL)
  {
    *t = branch;
  }
  else
  {
    aux = *t;
    while (aux != NULL)
    {
      ant = aux;
      if (time_cmp(aux->key, branch->key) == 1)
        aux = aux->l;
      else
        aux = aux->r;
    }
    if (time_cmp(ant->key, branch->key) == 1)
      ant->l = branch;
    else
      ant->r = branch;
  }
}

void max(t_timetable **t)
{
  t_timetable *aux, *ant;

  aux = *t;
  while (aux != NULL)
  {
    ant = aux;
    aux = aux->r;
  }

  print_time(ant->key);
}

void min(t_timetable **t)
{
  t_timetable *aux, *ant;

  aux = *t;
  while (aux != NULL)
  {
    ant = aux;
    aux = aux->l;
  }

  print_time(ant->key);
}

t_time string_to_time(char *hora)
{
  t_time time;
  int i = 0;
  int time_s[3];
  char *h = strtok(hora, ":");

  while (h != NULL)
  {
    time_s[i] = atoi(h);
    h = strtok(NULL, ":");
    i++;
  }

  time.h = time_s[0];
  time.m = time_s[1];
  time.s = time_s[2];

  return time;
}

void print_time(t_time hora)
{
  char str[2];

  itoa(hora.h, str, 10);
  printf("%s:", str);
  itoa(hora.m, str, 10);
  printf("%s:", str);
  itoa(hora.s, str, 10);
  printf("%s", str); 
}

int time_cmp(t_time h1, t_time h2)
{
  if (h1.h == h2.h && h1.m == h2.m && h1.s == h2.s)
    return 0;
  if (h1.h > h2.h)
    return 1;
  if (h1.h == h2.h && h1.m > h2.m)
    return 1;
  if (h1.h == h2.h && h1.m == h2.m && h1.s > h2.s)
    return 1;

  return -1;
}

void init_tree(t_timetable **tree)
{
  *tree = NULL;
}

int main()
{
  t_timetable *tree;
  init_tree(&tree);

  char hora[] = "22:02:14";
  put(&tree, hora, "Venezuela");
  char hora2[] = "22:01:15";
  put(&tree, hora2, "Brasil");
  char hora3[] = "22:12:16";
  put(&tree, hora3, "USA");
  char hora4[] = "23:15:17";
  put(&tree, hora4, "São Paulo");
  char hora5[] = "14:30:19";
  put(&tree, hora5, "Mariana");
  char hora7[] = "20:30:19";
  put(&tree, hora7, "Louisianna");
  char hora8[] = "19:30:19";
  put(&tree, hora8, "London");
  char hora9[] = "19:45:19";
  put(&tree, hora9, "Rio");

  char hora6[] = "22:02:14";
  printf("%s", get(&tree, hora6));  
  min(&tree);
  max(&tree);
  // char hora2[8] = "22:12:15";
  // t_time time2 = string_to_time(hora2);
  // printf("%s", time_to_string(time2));
  // printf("%d", time_cmp(time, time2));
}