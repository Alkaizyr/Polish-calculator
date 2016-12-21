#include <stdio.h>
#include <stdlib.h>

typedef struct Bignum {
    int value;
    struct Bignum *next;
    struct Bignum *prev;
} Bignum;

typedef struct Stack {
    struct Bignum *head;
    char sign;
    struct Bignum *tail;
    struct Stack *next;
} Stack;

typedef struct specstack {
    struct Bignum *head;
    struct Bignum *tail;
    struct specstack *next;
} specstack;

specstack *specstack_head = NULL;

Bignum *num_tail2 = NULL;
Bignum *num_head2 = NULL;

Bignum *num_tail = NULL;
Bignum *num_head = NULL;
Stack *stack_head = NULL;
/*
void specstack_push() {
    specstack *new_st_node = malloc(sizeof(specstack));
    new_st_node->head = num_head;
    new_st_node->tail = num_tail;
    new_st_node->next = specstack_head;
    specstack_head = new_st_node;
}

void specstack_pop() {
    specstack *new_st_node = malloc(sizeof(specstack));
    new_st_node = specstack_head;
    specstack_head = new_st_node->next;
    free(new_st_node);

}*/

void node_push(int data) {
    Bignum *tmp = malloc(sizeof(Bignum));
    tmp->value = data;
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

void node_push_reverse(int data) {
    Bignum *tmp = malloc(sizeof(Bignum));
    tmp->value = data;
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


void node_output(Bignum *point) {
    Bignum *p = point;
    while(p != NULL) {
        printf("%d", (p->value));
        p=p->prev;
    }
    printf("\n");
}
/*
void specstack_output() {
    specstack *p = specstack_head; //output spiska
    while(p != NULL) {
        printf("%p\t", (p->tail));

        num_tail=p->tail;
        node_output(num_tail);
        p=p->next;
    }
    printf("\n");
}
*/


void stack_output() {

    for (int i =0; i<40; i++) {
        printf("_");
    }
    printf("\n");
    if (stack_head == NULL) {
        printf("Stack is empty\n");
    }
    Stack *p = stack_head;
    while(p != NULL) {
        // printf("%p || ", (p->tail));

        num_tail=p->tail;
        if(p->sign == '1') {
            printf("-");
        }
        node_output(num_tail);
        p=p->next;
    }
    for (int i =0; i<40; i++) {
        printf("_");
    }
    printf("\n");
}

void free_list()  //LJOHUNI
{
    Bignum *tmp = NULL;
    while((tmp=num_head))
    {
        num_head = num_head -> next;
        free(tmp);
    }
}


void free_list2()  //LJOHUNI
{
    Bignum *tmp = NULL;
    while((tmp=num_head2))
    {
        num_head2 = num_head2 -> next;
        free(tmp);
    }
}

void free_stack()  //LJOHINI
{
    Stack *tmp = NULL;
    while((tmp = stack_head))
    {
        num_head = stack_head->head;
        num_tail = stack_head->tail;
        free_list();
        stack_head = stack_head -> next; 
        free(tmp);
    }
}
void stack_pop() {
    Stack *new_st_node = NULL;//malloc(sizeof(Stack));
     new_st_node = stack_head;
     num_head2 = new_st_node->head;
num_tail2 = new_st_node->tail;
free_list2();
    stack_head = new_st_node->next;
    free(new_st_node);

}

void stack_push(char sign) { //SDELAT' KRASIVO i osvobodit' pammjat' na node tail
    Bignum* temp = NULL;

while(num_tail->value == 0 && num_tail ->prev !=NULL) {
        if(num_tail->value == 0) {
temp = num_tail;
            num_tail = num_tail -> prev;
            num_tail -> next = NULL;
free(temp);
        }
    }

    if(num_head->next == NULL && num_head->value == 0) {
        sign = '0';

    }

    Stack *new_st_node = malloc(sizeof(Stack));
    new_st_node->head = num_head;
    new_st_node->tail = num_tail;
    new_st_node->next = stack_head;
    new_st_node->sign=sign;
    stack_head = new_st_node;
//new_st_node = stack_head;
//free(new_st_node);
//free_list();
    num_head = NULL;
    num_tail = NULL;
}


void input(char c, char sign) {
    //free_list(); //при ее использовании неправильно pushit v stack
    num_head = NULL;
    num_tail = NULL;
    node_push(c - '0');
    while ((c = getchar()) != '\n')
    {
        node_push(c - '0');
    }
    stack_push(sign);
}

int compare(Bignum *f_head, Bignum *s_head) { //nado s4itsat't ne ot hada a ot taila

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
            if(f->value > s->value ) {
                return 1;
            }
            if(f->value < s->value || f->value == s->value)  {
                return 0;
            }
            s=s->prev;
        } while(f=f->prev);
    }
    return 0;
}

void addTwoLists (Bignum *node_head_f, Bignum *node_head_s) {
//free_list();
    num_head=NULL;
    num_tail=NULL;
    int sum = 0, carry = 0;

    Bignum *f = node_head_f;
    Bignum *s = node_head_s;
    while(f != NULL || s != NULL) {
        sum = carry + (f? f->value: 0) + (s? s->value: 0);
        if(sum>=10) {
            sum = sum % 10;
            carry = 1;
        } else {
            carry = 0;
        }
        node_push_reverse(sum);
        if (f) {
            f=f->next;
        }
        if (s) {
            s=s->next;
        }
    }
    if(carry > 0) {
        node_push_reverse(carry);
    }
//Bignum *f = node_head_f;

 //  Bignum* tmp = NULL;
    //int val;
   // node_head_f = node_head_f-> next;
    //val = del->value;
   // tmp = node_head_f->next;
 //   free(tmp);
   // return val;

}

void minusTwoLists (Bignum *node_head_f, Bignum *node_head_s) {
    num_head=NULL;
    num_tail=NULL;
    int sum = 0, flag = 0;

    Bignum *f = node_head_f;
    Bignum *s = node_head_s;
    while(f != NULL && s != NULL) {
        sum = (f? f->value: 0) -flag- (s? s->value: 0);
        if(sum < 0) {
            sum =  10 + f->value - flag - s->value;
            flag=1;
        } else {
            flag=0;
        }
        node_push_reverse(sum);
        if (f) {
            f=f->next;
        }
        if (s) {
            s=s->next;
        }
    }
    while(f != NULL) {
        sum = f->value - flag;
        if(sum < 0) {
            sum =  10 + f->value - flag;
            flag=1;
            node_push_reverse(sum);
        }
        else {
            flag=0;
            node_push_reverse(sum);
        }
        f=f->next;
    }
}

void plusplus(char sign_f, char sign_s) {
    if(sign_f == sign_s) {
        addTwoLists(stack_head->head, stack_head->next->head);
        stack_pop();
        stack_pop();
        stack_push(sign_f);
    }
    else {
        if(compare(stack_head->head, stack_head->next->head)) {
            minusTwoLists(stack_head->head, stack_head->next->head);
            stack_pop();
            stack_pop();
            stack_push(sign_s);
        } else {
            minusTwoLists(stack_head->next->head, stack_head->head);
            stack_pop();
            stack_pop();
            stack_push(sign_f);
        }
    }
}

void multiplyTwoLists (Bignum *node_head_f, Bignum *node_head_s) {
num_head=NULL;
    num_tail=NULL;
    Bignum *f = node_head_f;
    Bignum *s = node_head_s;

    node_push(0);
Bignum *result_head = num_head;
Bignum *result_tail = num_tail;
/*
free_list(); // peremestil v proverku na nol'
num_head = NULL;
    num_tail=NULL;
*/
    int count_one = 0, count_two = 0;

    if(f->value == 0 && f->next == NULL || s->value == 0 && s->next == NULL) {
free_list(); // ETO FIX PRI UMNOZHENII NA NOL'. NE FAKT, 4TO MQ NE TERJAEM PAMJAT'
num_head = NULL;
    num_tail=NULL;
        node_push(0);
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
        Bignum *tmp = node_head_s;
        node_head_s=node_head_f;
        node_head_f=tmp;
    }

    f = node_head_f;
    s = node_head_s;

    int counter = 0, sum = 0;
    while (s!=NULL ) {
        int ostatok = 0;
        for (int i = counter; i>0; i--) {
            node_push_reverse(0);
        }
        while(f!=NULL) {
            sum = f->value * s-> value + ostatok;
            ostatok = 0;
            if(sum > 9) {
                ostatok=(sum - (sum % 10)) / 10;
                sum = sum % 10;
            }
            node_push_reverse(sum);
            f = f->next;
        }
        if (ostatok > 0) {
            node_push_reverse(ostatok);
        }
       // specstack_push();
////////////////////////////////////////
num_head2 = num_head;
num_tail2 = num_tail;

//free_list();
num_head = NULL;
num_tail=NULL;
////////////////
addTwoLists(num_head2, result_head);
////////////

free_list2();
num_head2 = NULL;
num_tail2 = NULL;
/////////////////////////////
//moi prikolq///////////////////// - odin leak!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11URAAAAAAA
num_head2 = result_head;
num_tail2 = result_tail;

result_head = NULL;
result_tail = NULL;

free_list2();

//////////////////////////////////
result_head = num_head;
result_tail = num_tail;

        counter++;

        s=s->next;
        f=node_head_f;
        num_head = NULL;
        num_tail = NULL;
    }
  /*  specstack *p = specstack_head;
    while(p != NULL) {
        num_tail=p->tail;
        p=p->next;
    }

    while(specstack_head->next != NULL) {
        addTwoLists(specstack_head->next->head, specstack_head->head);
        specstack_pop();
        specstack_pop();
        specstack_push();
    }*/

    num_head = result_head;
    num_tail = result_tail;
   // specstack_head = NULL;

}


void multymulty(char sign_f, char sign_s) {
    if(sign_f == sign_s) {
        multiplyTwoLists(stack_head->next->head, stack_head->head);
        stack_pop();
        stack_pop();
        stack_push('0');
    }
    else {
        multiplyTwoLists(stack_head->next->head, stack_head->head);
        stack_pop();
        stack_pop();
        stack_push('1');
    }
}

void minusminus(char sign_f, char sign_s) {
    if(sign_f == sign_s) {
        if(compare(stack_head->next->head, stack_head->head)) {
            if(sign_f=='0') {
                minusTwoLists(stack_head->next->head, stack_head->head);
                stack_pop();
                stack_pop();
                stack_push('0');
            }
            if(sign_f=='1') {
                minusTwoLists(stack_head->next->head, stack_head->head);
                stack_pop();
                stack_pop();
                stack_push('1');
            }
        }
        else {
            if(sign_f=='0') {
                minusTwoLists(stack_head->head, stack_head->next->head);
                stack_pop();
                stack_pop();
                stack_push('1');
            }
            if(sign_f=='1') {
                minusTwoLists(stack_head->head, stack_head->next->head);
                stack_pop();
                stack_pop();
                stack_push('0');
            }

        }
    }
    else {
        if(sign_f == '1') {
            addTwoLists(stack_head->head, stack_head->next->head);
            stack_pop();
            stack_pop();
            stack_push('1');
        }
        if(sign_f == '0') {
            addTwoLists(stack_head->head, stack_head->next->head);
            stack_pop();
            stack_pop();
            stack_push('0');
        }
    }
}





int chc_zero(Bignum *f) {
    while(f) {
        if(f->value == 0 ) {

            f=f->next;
        } else {
            return 1;
        }

    }
    return 0;
}


void devideTwoLists (Bignum *node_head_f, Bignum *node_head_s) {

    Bignum *f = node_head_f;
    Bignum *s= node_head_s;

    num_head = NULL;
    num_tail=NULL;

    node_push(1);

    Bignum *node_head_add=num_head;

    num_head = NULL;
    num_tail =NULL;

    node_push(0);

    Bignum *node_head_counter=num_head;
    num_head = NULL;
    num_tail=NULL;

    while(chc_zero(node_head_f)) {
        minusTwoLists(node_head_f, node_head_s);
        node_head_f=num_head;
        addTwoLists(node_head_counter, node_head_add);
        node_head_counter=num_head;
    }
}
/*
void devdev(Bignum *num_head_f, Bignum *num_tail_f, Bignum *num_head_s) {
    specstack_head =NULL;
    num_head = NULL;
    num_tail = NULL;
    node_push(1);

    Bignum *num_head_add=num_head;

    num_head = NULL;
    num_tail =NULL;

    node_push(0);

    Bignum *num_head_counter=num_head;
    num_head = NULL;
    num_tail=NULL;

    Bignum *f = num_tail_f;
    Bignum *s = num_head_s;
    Bignum *x = NULL;

    while((f->prev)) {
        while(compare(num_head_s, num_head)) {
            node_push_reverse(f->value);
        }
        x=num_head;

        while(compare(x, num_head_s)) {
            minusTwoLists(x, num_head_s);
            x=num_head;
            addTwoLists(num_head_counter, num_head_add);
            num_head_counter = num_head;
        }
        specstack_push();
        specstack_output();
        num_head=x;
    }
}*/
int main() {
    printf("Reverse Polish notation calculator with long arithmetic.\nBig numbers will be saved in Stack.\n'+' '-' '*' '/' -- standard operations.\n'=' -- output Stack head.\n's' -- output entire Stack.\n'q' -- quit.\n");
    while (1)
    {
        char c = getchar();
        switch (c)
        {
        case '+':
            if(stack_head && stack_head->next) {
                plusplus( stack_head->next->sign, stack_head->sign);

                break;
            }
            else {
                printf("Not enough operands - empty stack.\n");
                break;
            }
        case '*':
            if(stack_head && stack_head->next) {
                multymulty( stack_head->next->sign, stack_head->sign);
                break;
            }
            else {
                printf("Not enough operands - empty stack.\n");
                break;
            }
        case '/':
           // devdev( stack_head->next->head, stack_head->next->tail, stack_head->head);
            //stack_push('0');
            break;
        case '-':
            if ((c = getchar()) != '\n')
            {
                input(c, '1');
                break;
            }
            if(stack_head && stack_head->next) {
                minusminus( stack_head->next->sign, stack_head->sign);
                break;
            }
            else {
                printf("Not enough operands - empty stack.\n");
                break;
            }
        case '=':
if (stack_head->sign == '1') { 
printf("-");

};
            node_output(stack_head->tail);
            break;
        case 's':
            stack_output();
            break;
        case 'q':
            //free_list();  //nado li???
            free_stack();
            return 0;
        default:
            if (c != '\n')
            {
                input(c, '0');
                break;
            }
        }
    }
}

/*
1. dodelat' delenie
2. razbit' kod na chasti
3. napisat', kak rabotaet i pereimenovat' funkcii
*/
