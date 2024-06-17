# Отчет по лабораторной работе номер 4.
## Постановка задачи.
### Нужно реализовать функцию для проверки алгебраического выражения на правильность, используя структуру данных стек.

Выражение должно быть построено на множестве
1. Символов 'a'  - 'z', 'A' - 'Z', '0' - '9'
2. Операций '+', '-', '*', '/', '(', ')'

Данная программа не должна вычислять выражение, а проверять его на правильность, то есть мы можем не учитывать приоритет операций.

Также данная программа не должна работать с многозначными числами.


# Описание стека.
Для начала нужно разобрать, что такое стек и определить основные функции для работы с этой структурой данных.

> [!IMPORTANT]
> Стек - это динамическая структура данных, представляющий собой список элементов, организованных по принципу LIFO (Last In First Out - первым вошел, последним вышел)

![file-1024x768](https://github.com/ilpetinov24/ParserMathExpression/assets/144148020/02e1043d-95f2-495e-b174-2989c9062b52)

### 1. Объявленные структуры
Для работы со стеком нужно описать две структуры
1. **node** - это элемент стека, который содержит блок данных (data) и указатель на следующий элемент (next).
```c
typedef struct node {
    char data;
    struct node *next;
} node;
```
2. **stack** - это структура описывает сам стек. Содержит указатель на вершину стека (top) и размер стека (size).
```c
typedef struct stack {
    struct node *top; // вершина стека
    int size; // размер стека
} stack;
```
> [!IMPORTANT]
> **typedef** - это ключевое слово языка **C**, которое используется для создания псевдонимов других типов данных.

### 2. Функции для работы со структурой данных стек
1. **Push** - функция, которая добавляет элемент в стек.

```c
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
```

Функция возвращает **true**, если элемент был успешно добавлен в стек, иначе **false**.

2. **Pop** - это функция, которая получает элемент из вершины стека с последующим удалением из стека.

```c
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
```
Функция возвращает который находился в вершине стека.

3. **ShowTop** - это функция позволяет получить значение из вершины стека, не удаляя сам элемент.
```c
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
```
4. **DeleteStack** - это функция очищает стек и освобождает выделенную память под стек.
```c
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
```
5. **IsEmpty**  - функция проверяет стек на пустоту.
```c
bool IsEmpty(stack st)
{
    if (st.top)
        return false;
    
    return true;
}
```

6. **PrintStack** -функция выводит элементы стека.
```c
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
```

# Предложенное решение
## Идея алгоритма
Предложенный алгоритм имитирует вычисление выражения, для проверки его на корректность. В данном случае мы не учитываем приоритет операций. Алгоритм имитирует вычисления следующим образом: вытаскивает тройку символов из выражения и если тройка вычислима, то заменяет её на результат (символ 'r'). Тройка вычислима в том случае, если на 1 и 3 позиции стоит операнд, а на 2 месте стоит сам оператор. Далее алгоритм берет следующий тройку и имитирует вычисление. Это продолжается до тех пор, пока тройку можно вычислить или пока в стеке не останется один элемент.

## Алгоритм:
1. 



