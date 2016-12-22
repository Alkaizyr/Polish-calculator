#pragma once

typedef struct Bignum {
  int digit;
  struct Bignum *next;
  struct Bignum *prev;
} Bignum;

typedef struct Stack {
  struct Bignum *head;
  char sign;
  struct Bignum *tail;
  struct Stack *next;
} Stack;

Bignum *num_tail;
Bignum *num_head;
Stack *stack_head;
