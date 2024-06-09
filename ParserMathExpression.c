#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define IsDigit(c) ('0' <= c && c <= '9')
#define IsAlpha(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
#define str_size 200


typedef struct node {
    char data;
    struct node *next; 
} node;


typedef struct stack {
    struct node *top; // вершина стека
    int size; // размер стека
} stack;


bool Push(stack *st, char data)
{

    if (st == NULL)
        return false;
    
    node *newElem = (node *)malloc(sizeof(node));

    if (newElem == NULL)
        return false;
    else
    {
        newElem->data = data;
        newElem->next = NULL;
        if (st->top)
        {
            newElem->next = st->top;
            st->top = newElem;
        } 
        else
            st->top = newElem;

        st->size++;
    }

    return true;
}


char Pop(stack *st)
{
    if (st == NULL)
        return 0;

    // Если стек не пустой
    if (st->top)
    {
        node *tmp = st->top;
        st->top = st->top->next;

        int data = tmp->data;
        free(tmp);
        st->size--;
        return data;
    }

    return 0;
}


bool ShowTop(stack st, char *data)
{
    if (data == NULL)
        return false;
    
    if (st.top)
    {
        *data = st.top->data;
        return true;
    }

    return false;
}


void DeleteStack(stack *st)
{
    if (st == NULL)
        return;

    if (st->top)
    {
        node *current = st->top;
        
        while (current)
        {
            node *tmp = current;
            current = current->next;

            free(tmp);
            st->size--;
        }

        st->top = NULL;
    }
}


bool IsEmpty(stack st)
{
    if (st.top)
        return false;
    
    return true;
}


void PrintStack(stack st)
{
    if (st.top)
    {
        node *current = st.top;

        while (current)
        {
            printf("%c\n", current->data);
            current = current->next;
        }

    }
    else
        printf("Stack is empty!\n");
}


bool CheckLexeme(stack *st)
{ 
    if (st == NULL)
        return false;
    
    int i = 0;  
    while (!IsEmpty(*st))
    {
        char tmp = Pop(st);
        if (('a' <= tmp && tmp <= 'z') || ('A' <= tmp && tmp <= 'Z') || ('0' <= tmp && tmp <= '9'))
            if (i == 1)
                return false;
        
        if (tmp == '+' || tmp == '-' || tmp == '/' || tmp == '*')
            if (i == 0 || i == 2)
                return false;
        
        i++;
    }

    return true;
}


bool ExpressionValid(char *expression)
{
    if (expression == NULL)
        return false;
    
    stack brackets = {NULL, 0};
    stack st = {NULL, 0};

    bool flag = true;
    char tmp1;

    for (int i = 0; expression[i]; i++)
    {
        if (expression[i] == '(')
        {
            flag = true;
            Push(&brackets, '(');
        }
        else if (expression[i] == ')')
        {
            if (IsEmpty(brackets))
                return false;
            
            Pop(&brackets);
        }
        else if (expression[i] != ' ')
        {
            if (flag && expression[i] == '-')
            {
                Push(&st, '0');
                Push(&st, '-');
            }
            else
                Push(&st, expression[i]);

            flag = false;
        }
    }

    PrintStack(st);

    if (!IsEmpty(brackets))
        return false;

    flag = true;

    while (flag)
    {
        stack tmp = {NULL, 0};
        
        for (int i = 0; i < 3; i++)
            Push(&tmp, Pop(&st));

        if (CheckLexeme(&tmp))
            Push(&st, 'r');
        else
            return false;

        if (st.size == 1)
            flag = false;
    }

    return true;
}


int main()
{
    stack st = {NULL, 0};
    char *str = "-3";

    if (ExpressionValid(str))
        printf("YES!!!!\n");
    else
        printf("NO!!!!\n");

    return 0;
}