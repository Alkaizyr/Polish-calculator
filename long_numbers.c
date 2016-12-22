#include <stdio.h>
#include <stdlib.h>

#include "long_numbers.h"
#include "structs.h"

void BignumInput(char c, char sign)
{
  num_head = NULL;
  num_tail = NULL;
  BignumPush(c - '0');
  while ((c = getchar()) != '\n') {
    BignumPush(c - '0');
  }
  StackPush(sign);
}

void BignumPush(int data)
{
  Bignum *tmp = malloc(sizeof(Bignum));
  tmp->digit = data;
  tmp->next = num_head;
  tmp->prev = NULL;
  if ( num_head) {
    num_head->prev = tmp;
  }
  num_head = tmp;

  if (num_tail == NULL) {
    num_tail = tmp;
  }
}

void BignumPushBack(int data)
{
  Bignum *tmp = malloc(sizeof(Bignum));
  tmp->digit = data;
  tmp->next = NULL;
  tmp->prev = num_tail;
  if ( num_tail) {
    num_tail->next = tmp;
  }
  num_tail = tmp;

  if (num_head == NULL) {
    num_head = tmp;
  }
}

void BignumOutput(Bignum *point)
{
  Bignum *p = point;
  while(p != NULL) {
    printf("%d", (p->digit));
    p=p->prev;
  }
  printf("\n");
}

void BignumFree(Bignum *num)
{
  Bignum *tmp = NULL;
  while((tmp=num)) {
    num = num -> next;
    free(tmp);
  }
}

int BignumCompare(Bignum *f_head, Bignum *s_head)
{

  int count_one = 0, count_two = 0;
  Bignum *f = f_head;
  Bignum *s = s_head;
  while(f) {
    f=f->next;
    count_one++;
  }

  while(s) {
    s=s->next;
    count_two++;
  }

  if(count_one < count_two) {
    return 0;
  }
  if(count_one > count_two) {
    return 1;
  }
  if(count_one == count_two) {
    f = f_head;
    s = s_head;
    while(count_two>1) {
      s=s->next;
      f=f->next;
      count_two--;
    }
    do {
      if(f->digit > s->digit) {
        return 1;
      }
      if(f->digit < s->digit) {
        return 0;
      }
      s=s->prev;
    } while(f=f->prev);
  }
  return 2;
}

int BignumIsZero(Bignum *f)
{
  while(f) {
    if(f->digit == 0 ) {

      f=f->next;
    } else {
      return 0;
    }

  }
  return 1;
}

void StackPush(char sign)
{
  Bignum* tmp = NULL;

  while(num_tail->digit == 0 && num_tail ->prev !=NULL) {
    if(num_tail->digit == 0) {
      tmp = num_tail;
      num_tail = num_tail -> prev;
      num_tail -> next = NULL;
      free(tmp);
    }
  }

  if(num_head->next == NULL && num_head->digit == 0) {
    sign = '0';

  }

  Stack *temp = malloc(sizeof(Stack));
  temp->head = num_head;
  temp->tail = num_tail;
  temp->next = stack_head;
  temp->sign=sign;
  stack_head = temp;
  num_head = NULL;
  num_tail = NULL;
}

void StackPop()
{
  Stack *temp = NULL;
  temp = stack_head;
  BignumFree(temp->head);
  stack_head = temp -> next;
  free(temp);
}

void StackOutput()
{

  for (int i =0; i<40; i++) {
    printf("_");
  }
  printf("\n");
  if (stack_head == NULL) {
    printf("Stack is empty\n");
  }
  Stack *p = stack_head;
  while(p != NULL) {

    num_tail=p->tail;
    if(p->sign == '1') {
      printf("-");
    }
    BignumOutput(num_tail);
    p=p->next;
  }
  for (int i =0; i<40; i++) {
    printf("_");
  }
  printf("\n");
}

void StackFree()
{
  Stack *tmp = NULL;
  while((tmp = stack_head)) {
    num_head = stack_head->head;
    num_tail = stack_head->tail;
    BignumFree(num_head);
    stack_head = stack_head -> next;
    free(tmp);
  }
}
