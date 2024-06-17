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
### 1. Разделить выражение на два стека.
На данном этапе создается два стека. В первый мы помещаем скобки, а во второй мы помещаем само выражение без скобок. Если в выражении были пробелы, то они не учитываются.

### 2. Проверить скобки в выражении.
Здесь нам нужно проверить количество разных скобок, есть ли какое-нибудь выражение в скобках и есть ли оператор между разными скобками.

### 3. Проверить выражение без скобок.
На этом шаге алгоритм должен вытаскивать из выражения тройку и проверять её на вычислимость.

### 4. Результат
Если в стеке, где было наше выражение остался один элемент, то выражение корректно.

Для удобства я разделил алгоритм на две функции.

1. **CheckLexeme** - это функция для проверки тройки символов.
```c
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
```
Функция возвращает значение **true**, если тройка вычислима, иначе возвращает значение **false**

2. **ExpressionValid** - функция для проверки выражения.
```c
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
            char top;

            if (ShowTop(st, &top))
            {
                if (!IsOperator(top))
                    return false;
            }
            Push(&brackets, '(');
        }
        else if (expression[i] == ')')
        {
            char top;

            if (ShowTop(st, &top))
            {
                if (IsOperator(top))
                    return false;
            } 
            if (IsEmpty(brackets))
                return false;
            
            Pop(&brackets);
        }
        else if (expression[i] != ' ')
        {
            if (flag && (expression[i] == '-' || expression[i] == '+'))
                Push(&st, '0');

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
```
Возвращает значение **true**, если выражение корректно, иначе значение **false**

# Тестовые случаи.

