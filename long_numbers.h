#pragma once

#include "structs.h"

void BignumInput(char c, char sign);
void BignumPush(int data);
void BignumPushBack(int data);
void BignumOutput(Bignum *point);
void BignumFree(Bignum *num);
int BignumCompare(Bignum *f_head, Bignum *s_head);
int BignumIsZero(Bignum *f);
void StackPush(char sign);
void StackPop();
void StackOutput();
void StackFree();

