#pragma once

#include "structs.h"

void BignumAdd(Bignum *f_head, Bignum *s_head);
void Addition(char sign_f, char sign_s);
void BignumSubtract(Bignum *f_head, Bignum *s_head);
void Subtraction(char sign_f, char sign_s);
void BignumMultiply(Bignum *f_head, Bignum *s_head);
void Multiplication(char sign_f, char sign_s);
void BignumDivide(Bignum *Bignum_tail_f, Bignum *s_head);
void Division(char sign_f, char sign_s, Bignum *f, Bignum *s);
