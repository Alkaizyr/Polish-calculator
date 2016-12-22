#include <stdio.h>
#include <stdlib.h>

#include "long_numbers.h"
#include "long_arithmetic.h"
#include "structs.h"

void BignumAdd(Bignum *f_head, Bignum *s_head)
{
  num_head=NULL;
  num_tail=NULL;
  int sum = 0, carry = 0;

  Bignum *f = f_head;
  Bignum *s = s_head;
  while(f != NULL || s != NULL) {
    sum = carry + (f? f->digit: 0) + (s? s->digit: 0);
    if(sum>=10) {
      sum = sum % 10;
      carry = 1;
    } else {
      carry = 0;
    }
    BignumPushBack(sum);
    if (f) {
      f=f->next;
    }
    if (s) {
      s=s->next;
    }
  }
  if(carry > 0) {
    BignumPushBack(carry);
  }
}

void Addition(char sign_f, char sign_s)
{
  if(sign_f == sign_s) {
    BignumAdd(stack_head->head, stack_head->next->head);
    StackPop();
    StackPop();
    StackPush(sign_f);
    return;
  } else {
    if(BignumCompare(stack_head->head, stack_head->next->head)) {
      BignumSubtract(stack_head->head, stack_head->next->head);
      StackPop();
      StackPop();
      StackPush(sign_s);
      return;
    } else {
      BignumSubtract(stack_head->next->head, stack_head->head);
      StackPop();
      StackPop();
      StackPush(sign_f);
      return;
    }
  }
}

void BignumSubtract(Bignum *f_head, Bignum *s_head)
{
  num_head=NULL;
  num_tail=NULL;
  int sum = 0, flag = 0;

  Bignum *f = f_head;
  Bignum *s = s_head;
  while(f != NULL && s != NULL) {
    sum = (f? f->digit: 0) -flag- (s? s->digit: 0);
    if(sum < 0) {
      sum =  10 + f->digit - flag - s->digit;
      flag=1;
    } else {
      flag=0;
    }
    BignumPushBack(sum);
    if (f) {
      f=f->next;
    }
    if (s) {
      s=s->next;
    }
  }
  while(f != NULL) {
    sum = f->digit - flag;
    if(sum < 0) {
      sum =  10 + f->digit - flag;
      flag=1;
      BignumPushBack(sum);
    } else {
      flag=0;
      BignumPushBack(sum);
    }
    f=f->next;
  }
}

void Subtraction(char sign_f, char sign_s)
{
  if(sign_f == sign_s) {
    if(BignumCompare(stack_head->next->head, stack_head->head)) {
      if(sign_f=='0') {
        BignumSubtract(stack_head->next->head, stack_head->head);
        StackPop();
        StackPop();
        StackPush('0');
        return;
      }
      if(sign_f=='1') {
        BignumSubtract(stack_head->next->head, stack_head->head);
        StackPop();
        StackPop();
        StackPush('1');
        return;
      }
    } else {
      if(sign_f=='0') {
        BignumSubtract(stack_head->head, stack_head->next->head);
        StackPop();
        StackPop();
        StackPush('1');
        return;
      }
      if(sign_f=='1') {
        BignumSubtract(stack_head->head, stack_head->next->head);
        StackPop();
        StackPop();
        StackPush('0');
        return;
      }

    }
  } else {
    if(sign_f == '1') {
      BignumAdd(stack_head->head, stack_head->next->head);
      StackPop();
      StackPop();
      StackPush('1');
      return;
    }
    if(sign_f == '0') {
      BignumAdd(stack_head->head, stack_head->next->head);
      StackPop();
      StackPop();
      StackPush('0');
      return;
    }
  }
}

void BignumMultiply(Bignum *f_head, Bignum *s_head)
{
  Bignum *temp =NULL;
  num_head=NULL;
  num_tail=NULL;
  Bignum *f = f_head;
  Bignum *s = s_head;

  BignumPush(0);
  Bignum *result_head = num_head;
  Bignum *result_tail = num_tail;

  int count_one = 0, count_two = 0;

  if(f->digit == 0 && f->next == NULL || s->digit == 0 && s->next == NULL) {
    BignumPush(0);
    return;
  }

  num_head = NULL;
  num_tail=NULL;

  while(f) {
    f=f->next;
    count_one++;
  }

  while(s) {
    s=s->next;
    count_two++;
  }

  if(count_one < count_two) {
    Bignum *tmp = s_head;
    s_head=f_head;
    f_head=tmp;
  }

  f = f_head;
  s = s_head;

  int counter = 0, sum = 0;
  while (s!=NULL ) {
    int remainder = 0;
    for (int i = counter; i>0; i--) {
      BignumPushBack(0);
    }
    while(f!=NULL) {
      sum = f->digit * s-> digit + remainder;
      remainder = 0;
      if(sum > 9) {
        remainder=(sum - (sum % 10)) / 10;
        sum = sum % 10;
      }
      BignumPushBack(sum);
      f = f->next;
    }
    if (remainder > 0) {
      BignumPushBack(remainder);
    }

    temp = num_head;

    num_head = NULL;
    num_tail=NULL;

    BignumAdd(temp, result_head);

    BignumFree(temp);
    BignumFree(result_head);

    result_head = num_head;
    result_tail = num_tail;

    counter++;

    s=s->next;
    f=f_head;
    num_head = NULL;
    num_tail = NULL;
  }

  num_head = result_head;
  num_tail = result_tail;
}

void Multiplication(char sign_f, char sign_s)
{
  if(sign_f == sign_s) {
    BignumMultiply(stack_head->next->head, stack_head->head);
//printf("multiplication\n");
    StackPop();
    StackPop();
    StackPush('0');
    return;
  } else {
    BignumMultiply(stack_head->next->head, stack_head->head);
    StackPop();
    StackPop();
    StackPush('1');
    return;
  }
}

void BignumDivide(Bignum *Bignum_tail_f, Bignum *s_head)
{
  Bignum* tmp = NULL;

  int t = 0;
  Bignum *y_head = NULL;
  Bignum *y_tail = NULL;

  num_head=NULL;
  num_tail=NULL;
  BignumPush(0);
  Bignum *res_head = num_head;
  Bignum *res_tail = num_tail;

  num_head=NULL;
  num_tail=NULL;
  BignumPush(1);
  Bignum *additor_head = num_head;
  Bignum *additor_tail = num_tail;

  num_head = NULL;
  num_tail = NULL;
  BignumPush(Bignum_tail_f->digit);
  Bignum *x_head = NULL;
  Bignum *x_tail = NULL;

LOOP:
  while(Bignum_tail_f	!= NULL) {
    if (num_head == NULL) {
      BignumPush(Bignum_tail_f->digit);

      x_head = num_head;
      x_tail = num_tail;
      if((BignumCompare(s_head, x_head) == 1) && t != 0) {

        x_head = num_head;
        x_tail = num_tail;

        num_head = y_head;
        num_tail = y_tail;

        BignumPush(0);
        y_head = num_head;
        y_tail = num_tail;

        num_head = x_head;
        num_tail = x_tail;
        Bignum_tail_f = Bignum_tail_f->prev;

        goto LOOP;

      }
    }
    if(BignumCompare(s_head, num_head) == 1) {
      if(t==0) {
        Bignum_tail_f = Bignum_tail_f->prev;
        BignumPush(Bignum_tail_f->digit);
      }
      if(t!=0) {
        if(num_tail->digit == 0) {
          num_head = y_head;
          num_tail = y_tail;
          BignumPush(Bignum_tail_f->digit);

          y_head=num_head;
          y_tail=num_tail;
          Bignum_tail_f = Bignum_tail_f->prev;
          num_head = NULL;
          num_tail = NULL;
          goto LOOP;
        } else {
          BignumPush(Bignum_tail_f->digit);
        }
      }
    }

    x_head=num_head;
    x_tail=num_tail;
    num_head = NULL;
    num_tail = NULL;

    while(BignumCompare(x_head, s_head)) {

      BignumSubtract(x_head, s_head);

      while(num_tail->digit == 0 && num_tail ->prev != NULL) {
        if(num_tail->digit == 0) {
          tmp = num_tail;
          num_tail = num_tail -> prev;
          num_tail -> next = NULL;
          free(tmp);
        }
      }

      BignumFree(x_head);

      x_head=num_head;
      x_tail=num_tail;

      num_head = NULL;
      num_tail = NULL;

      BignumAdd(res_head, additor_head);

      BignumFree(res_head);

      res_head=num_head;
      res_tail=num_tail;
      num_head = NULL;
      num_tail = NULL;
    }

    num_head = y_head;
    num_tail = y_tail;

    while(res_head != NULL) {
      BignumPush(res_head->digit);
      tmp = res_head;
      res_head = res_head->next;
      free(tmp);
    }

    y_head = num_head;
    y_tail = num_tail;

    num_head=NULL;
    num_tail=NULL;
    BignumPush(0);
    res_head = num_head;
    res_tail = num_tail;

    if(BignumIsZero(x_head)) {
      BignumFree(x_head);
    }

    num_head = x_head;
    num_tail = x_tail;
    Bignum_tail_f = Bignum_tail_f->prev;
    t=1;
  }
  num_head = y_head;
  num_tail = y_tail;

  BignumFree(x_head);

  BignumFree(res_head);

  BignumFree(additor_head);

}

void Division(char sign_f, char sign_s, Bignum *f, Bignum *s)
{

  if(BignumIsZero(s)) {
    printf("Division by zero! -- error.\n");
    return;

  }

  if(BignumCompare(s, f) == 1 || BignumIsZero(f)) {
    num_head = NULL;
    num_tail = NULL;
    BignumPush(0);
    StackPop();
    StackPop();
    StackPush('0');
    return;
  }

  if(BignumCompare(f, s) == 1) {
    if(sign_f == sign_s) {
      BignumDivide(stack_head->next->tail, stack_head->head);
      StackPop();
      StackPop();
      StackPush('0');
      return;
    } else {
      BignumDivide(stack_head->next->tail, stack_head->head);
      StackPop();
      StackPop();
      StackPush('1');
      return;
    }
  }

  if(BignumCompare(f, s) == 2) {
    num_head = NULL;
    num_tail = NULL;
    BignumPush(1);
    StackPop();
    StackPop();
    if(sign_f == sign_s) {
      StackPush('0');
      return;
    } else {
      StackPush('1');
      return;
    }
  }
}
