#include <stdio.h>
#include <stdlib.h>

#include "long_numbers.h"
#include "long_arithmetic.h"
#include "structs.h"

int main()
{

  printf("Reverse Polish notation calculator with long arithmetic.\nBig numbers will be saved in Stack.\n'+' '-' '*' '/' -- standard operations.\n'=' -- output Stack head.\n's' -- output entire Stack.\n'q' -- quit.\n");
  while (1) {
    char c = getchar();
    switch (c) {
    case '+':
      if(stack_head && stack_head->next) {
        Addition( stack_head->next->sign, stack_head->sign);

        break;
      } else {
        printf("Not enough operands! -- empty stack.\n");
        break;
      }
    case '*':
      if(stack_head && stack_head->next) {
        Multiplication(stack_head->next->sign, stack_head->sign);
        break;
      } else {
        printf("Not enough operands! -- empty stack.\n");
        break;
      }
    case '/':
      if(stack_head && stack_head->next) {
        Division(stack_head->next->sign, stack_head->sign, stack_head->next->head, stack_head->head);
        break;
      } else {
        printf("Not enough operands! -- empty stack.\n");
        break;
      }
    case '-':
      if ((c = getchar()) != '\n') {
        BignumInput(c, '1');
        break;
      }
      if(stack_head && stack_head->next) {
        Subtraction( stack_head->next->sign, stack_head->sign);
        break;
      } else {
        printf("Not enough operands! -- empty stack.\n");
        break;
      }
    case '=':
      if (stack_head->sign == '1') {
        printf("-");
      };
      BignumOutput(stack_head->tail);
      break;
    case 's':
      StackOutput();
      break;
    case 'q':
      StackFree();
      return 0;
    default:
      if (c != '\n') {
        BignumInput(c, '0');
        break;
      }
    }
  }
}
