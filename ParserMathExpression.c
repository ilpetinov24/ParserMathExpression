#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define IsDigit(c) (('0' <= c && c <= '9'))
#define IsAlpha(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
#define IsOperator(c) ((tmp == '+' || tmp == '-' || tmp == '/' || tmp == '*'))


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

    if (newElem)
    {
        newElem->data = data;
        newElem->next = NULL;
        
        if (st->top)
            newElem->next = st->top;
        
        st->top = newElem;
        st->size++;
    }
    else
        return false;

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
    
    // Если стек не пустой
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
        // Если на 2 позиции стоит операнд, то выражение неправильное
        if (IsDigit(tmp) || IsAlpha(tmp))
            if (i == 1)
                return false;
        // Если на 1 или 3 позиции стоит операция, то выражение неправильное
        if (IsOperator(tmp))
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
    
    stack brackets = {NULL, 0}; // Стек для скобок
    // Так как нам не важен приоритет, мы можем откинуть скобки
    stack st = {NULL, 0}; // Стек для выражения

    // Флаг нужен для проверки унарного минуса или плюса
    bool flag = true;

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
            if (flag && (expression[i] == '-' || expression[i] == '+'))
            {
                Push(&st, '0');
                Push(&st, expression[i]);
            }
            else
                Push(&st, expression[i]);

            flag = false;
        }
    }

    //PrintStack(st);

    // Если выражения нету
    if (IsEmpty(st))
        return false;
    if (!IsEmpty(brackets))
        return false;

    flag = true;

    while (flag)
    {
        stack lexeme = {NULL, 0};
        
        for (int i = 0; i < 3; i++)
        {
            char tmp = Pop(&st); 
            if (tmp)
                Push(&lexeme, tmp);
        }

        // Если тройка верная
        if (CheckLexeme(&lexeme))
            Push(&st, 'r');
        else
            return false;

        // Если в стеке остался один элемент, то завершаем цикл
        if (st.size == 1)
            flag = false;
    }

    return true;
}


int main()
{
    stack st = {NULL, 0};
    //char *str = "";
    //char *str = "(a+(b**h) - 8)";
    //char *str = "((a + 1) / Z) - 9";
    //char *str = "+1";
    //char *str = "()()";
    //char *str = "(+1 - (-2 - (-3 - (-4 - (-5 - 6)))))";
    char *str = "(-1 - (-2 - (-3 - (-4 - (-5 - 6)))))";
    //char *str = "(-1 - (-2 - (3 - 4) - 4) - 5)";
    //char *str = "1 - (-1) - (-3)";
    //char *str = "1 - (-1) - (-3)";
    //char *str = "1 - - - 3";
    //char *str = "-3";
    //char *str = "a + b * c / 1 - 9";

    if (ExpressionValid(str))
        printf("Expression is correct!!\n");
    else
        printf("The expression is not correct!!\n");


    return 0;
}