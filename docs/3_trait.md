## trait

### 概述

trait 是一种定义行为的方式，它类似于其它语言中的接口或抽象类，目的是定义一个实现某些目的所必须的行为集合。trait 定义了一组方法签名，这些方法可以被多个结构体、枚举体或内置类型共享。主要作用是为了实现代码的复用和抽象，从而提高代码的可维护性和可扩展性。

### trait 语法规则

毕昇 C 引入关键字 `trait` 与 `impl`，通过关键字 `trait` 来定义，通过 `impl` 可以为一个类型实现一个或多个 trait。下面通过一些代码示例来了解 trait 的使用方法。

#### trait 的定义

**语法：**

```c
trait TraitName {
  // 定义 trait 中的方法签名
};
```

其中，`TraitName` 是 trait 的名称，后面跟着一对花括号，里面可以定义一些方法的签名。trait 中定义的方法不支持默认实现，必须由实现该 trait 的类型提供具体实现。下面我们来看一个简单的例子：

```c
trait T {
    void doSomeThing1(This* this);
    void doSomeThing2(This* this);
};
```

**规则：**

1. trait 定义只能出现在 top-level

```c
void test() {
    trait T {}; // error: 不能在函数体中定义 trait
}

struct MyStruct {
    trait T {}; // error: 不能在结构体中定义 trait
};
```

2. trait 内要求函数首个入参且只有首个入参类型为 `This` 指针，命名为 `this`; `This` 指代实现了 trait 的具体类型

```c
trait T {
    void doSomeThing1(This* this); // ok
    void doSomeThing2(This* a); // error: 第一个参数名必须为 this
    void doSomeThing3(int a, This* this); // error: 第一个参数类型必须为 This
};
```

3. trait 内只允许声明函数

```c
trait T {
    void doSomeThing1(This* this) { // error: trait 内的成员函数不支持默认实现
        ...
    }
};
```

4. trait 内可以没有方法签名

```c
trait T {}; // ok
```

5. 不允许给 trait 类型扩展成员函数

```c
void trait T::getArea(trait T* this) { // error: 不允许给 trait 类型扩展成员函数
	...
}
```



#### 实现 trait

**语法：**

```c
impl <trait> for <type>;
```

我们可以通过 `impl` 关键字来为一个类型实现一个 trait。直观的，我们来看一个简单的例子：

```c
trait T {
    void f(This* this);
};

struct S {};
void struct S::f(struct S* this);
void int::f(int* this);

impl trait T for int;
impl trait T for struct S;
```

**规则：**

1. 在 impl 语句之前，一定存在 `<trait>` 和 `<type>` 的定义
2. 在 impl 语句之前，`<type>` 必须已经声明了 `<trait>` 中所有成员函数

```c
trait T {
    int f1(This* this);
    int f2(This* this);
};

struct S{};

int struct S::f1(struct S* this);
impl trait T for struct S; // error: struct S 未扩展声明函数 f2
int struct S::f2(struct S* this);
impl trait T for struct S; // ok，struct S 已扩展声明了 trait 中所有成员函数
```

3. `<type>` 类型不允许是 trait

```c
impl trait T for struct S; // ok，支持通过 impl 对已有 struct/union/enum 或内置类型实现 trait
impl trait T for trait T; // error: 不允许给 trait 类型实现 trait
```

4. 支持对 `typedef` 类型实现 trait

```c
typedef struct S S1;
impl trait T for S1;
```



#### trait 类型的变量

我们可以定义 trait 指针类型的变量，并可以通过该指针变量进行函数调用等，具体使用方法如下：

```c
#include <stdio.h>

struct S {
    float num;
};

typedef trait Print {
    void print(This* this);
}P;
void struct S::print(struct S* this) {
    printf("This is a struct instance, valued %f\n", this->num);
}
void int::print(int* this) {
    printf("This is an int instance, valued %d\n", *this);
}

impl P for struct S;
impl P for int;

void test() {
    struct S s = { 0.0 };
    int a = 1;
    float b = 1.0;

    trait Print* p;
    p = &s; // ok，隐式转换
    p->print(); // This is a struct instance, valued 0.000000
    p = &a;
    p->print(); // This is an int instance, valued 1
    p = &b; // error: float 类型未实现 trait Print，不能进行赋值
}
```

**规则：**

1. 支持对 trait 进行 `typedef`

```c
typedef trait Print {
    ...
}P;
```

2. 只允许声明 trait 指针类型的变量

```c
trait Print* p1; // ok
trait Print p2; // error: 不允许定义 trait 类型的变量
```

3. 如果 `<type>` 实现了 `<trait>`，那么指向这个 `<type>` 的指针可以被转换为 `<trait>` 类型的变量

```c
impl trait Print for struct S;

struct S s;
trait Print* t1 = &s; // 隐式转换
trait Print* t2 = (trait Print*)&s; // 显式转换
```

4. trait 指针类型的变量可以通过 `->` 方式调用该 trait 中的成员方法

```c
struct S s;
trait Print* t = &s;
t->print();
```

5. trait 指针类型的变量，允许用 `NULL` 赋值

```c
trait Print* p = NULL;
```

6. 允许指向 trait 的多级指针，但这种类型不能直接调用成员函数。不允许结构体的二级指针直接隐式转换成 trait 的二级指针

```c
trait Print* p;
p->print();
trait Print** q = &p; // ok
q->print(); // error: 多级指针不能直接调用成员函数
(*q)->print(); // ok
struct S s;
q = &&s; // error: 不允许结构体的二级指针直接隐式转换成 trait 的二级指针
```

7. trait 指针类型的变量，不可以解引用

```
trait Print *p;
*p; // error: trait 指针类型的变量，不可以解引用
```

8. trait 指针类型变量可以用 `const` / `volatile` 修饰

```c
const trait Print* p1;
volatile trait Print* p2;
```

9. 支持 trait 指针类型作为函数参数及返回值类型

```c
trait Print* get(trait Print* t) {
    return t;
}
```

10. 支持 trait 指针变量和 `NULL` 做比较（这里的比较仅包含 `==` 和`!=`，下同）

```c
trait Print* p = NULL;
if (p == NULL) {} // ok
if (p != NULL) {} // ok
```

11. 支持 trait 指针变量和非 trait 指针变量比较

```c
int a = 1;
int *p1 = &a;
struct S s;
struct S *p2 = &s;
trait Print* p = NULL;
// 假设struct S 类型实现 trait F<int>，但 int 类型没有
if (p == p1) {}; // warning
if (p == p2) {}; // ok
if (p == a) {};  // error: 与非指针类型比较报 error
```

12. 支持 trait 指针变量和 trait 指针变量比较

```c
trait Print* t1 = NULL;
trait Print* t2 = NULL;
trait G *g = NULL;
if (t1 == g) {} // warning: 如果 trait 类型不同会报 warning
if (t1 == t2) {} // ok
```



#### 类型转换

trati 类型转换只能在实现了对应 trait 的类型之间进行，将一个类型转换为另一个类型，同时保留原有类型的特性和方法。

**规则：**

1. trait 指针类型的变量，不允许强制转换为非指针类型

2. 支持 trait 指针类型强制转为非 trait 指针类型，但不支持隐式转换

```c
int a = 0;
trait T *p = &a; // 假设 int 类型实现了 trait T
int *q1 = p; // error: 不支持 trait 指针类型隐式转换为具体类型
int *q2 = (int*)p; // ok
struct S *q3 = (struct S*)p;
```

3.  trait 类型支持强制转换为 `void *`类型，但`void *` 指针无法转换为 trait 指针类型

```c
int a = 1;
trait T *p = &a; // 假设 int 类型实现了 trait T
void * q = (void *)p; // ok: trait 类型支持强制转换为 `void *`类型
trait T *p1 = (trait T *)q; // error: `void *` 指针无法强制转换为 trait 指针类型
trait T *p2 = q; // error: `void *` 指针无法隐式转换为 trait 指针类型
```



### 泛型 trait 语法规则

泛型 trait 是指在 trait 中使用泛型类型参数，从而使 trait 的方法可以适用于不同类型，避免代码的重复编写。下面通过一些代码示例来了解泛型 trait 的使用方法。

#### 泛型 trait 的定义

**语法：**

```c
trait TraitName<T1,T2,...,Tn> {
  // 定义泛型 trait 中的方法签名，可以使用泛型类型 T1,T2,...,Tn
};
```

与 trait 定义类似，`TraitName` 是泛型 trait 的名称，后面跟着一对尖括号，里面可以包含一个或多个泛型参数，在花括号里面可以定义一些方法的签名。同样，泛型 trait 中定义的方法不支持默认实现，必须由实现该泛型 trait 的类型提供具体实现。下面我们来看一个简单的例子：

```c
trait F<T1, T2> {
    T1 doSomeThing1(This* this);
    T1 doSomeThing2(This* this, T2 param);
};
```



**规则：**

1. 泛型 trait 定义只能出现在 top-level

```c
void test<T>() {
    trait F<T> {}; // error: 不能在函数体中定义泛型 trait
}

struct MyStruct<T> {
    trait F<T> {}; // error: 不能在结构体中定义泛型 trait
};
```

2. 泛型 trait 内要求函数首个入参且只有首个入参类型为 `This` 指针，命名为 `this`; `This` 指代实现了 trait 的具体类型

```c
trait F<T> {
    T doSomeThing1(This* this); // ok
    T doSomeThing2(This* a); // error: 第一个参数名必须为 this
    void doSomeThing3(T a, This* this); // error: 第一个参数类型必须为 This
};
```

3. 泛型 trait 内只允许声明函数

```c
trait F<T> {
    void doSomeThing1(This* this) { // error: 泛型 trait 内的成员函数不支持默认实现
        ...
    }
};
```

4. 泛型 trait 内可以没有方法签名

```c
trait F<T> {}; // ok
```

5. 不允许给泛型 trait 类型扩展成员函数

```c
void trait F<T>::getArea(trait F<T>* this) { // error: 不允许给泛型 trait 类型扩展成员函数
	...
}

void trait F<int>::getArea(trait F<int>* this) { // error: 不允许给泛型 trait 类型扩展成员函数
	...
}
```



#### 实现泛型 trait

**语法：**

```c
impl <trait<SpecializationType>> for <type>;
```

我们可以通过 `impl` 关键字对已有 `struct`/`union`/`enum` 类型和内置类型实现 `trait<int>`/`trait<float>`等，需要注意的是，我们目前仅支持对实例化的 trait 类型进行 impl。直观的，我们来看一个简单的例子：

```c
trait F<T> {
    T f(This* this);
};

struct S {};
int struct S::f(struct S* this);
int int::f(int* this);

impl trait F<int> for int;
impl trait F<int> for struct S;
```

**规则：**

1. 在 impl 语句之前，一定存在泛型 `<trait>` 和 `<type>` 的定义
2. 仅支持 `impl` 实例化的 trait 类型

```c
impl trait F<T> for int; // error: 不允许对泛型 trait 类型进行 impl
```

3. 在 impl 语句之前，`<type>` 必须已经声明了 `<trait>` 中所有成员函数

```c
trait F<T> {
    T f1(This* this);
    T f2(This* this);
};

struct S{};

int struct S::f1(struct S* this);
impl trait F<int> for struct S; // error: struct S 未扩展声明函数 f2
int struct S::f2(struct S* this);
impl trait F<int> for struct S; // ok，struct S 已扩展声明了 trait 中所有成员函数
```

4. 支持通过 `impl` 关键字对已有 `struct`/`union`/`enum` 类型和内置类型实现 `trait<int>`/`trait<float>`，但`struct`/`union` 类型类型不能是泛型的

```c
struct S {};
struct G<T> {};
trait F<T> {};
impl trait F<int> for int; // ok
impl trait F<int> for struct S; // ok
impl trait F<int> for struct G<int>; // error: 被 impl 的 struct/union 类型类型不能是泛型的
```

5. `<type>` 类型不允许是 trait/泛型 trait

```c
impl trait F<int>  for trait S; // error: 不允许给泛型 trait 类型实现 trait
impl trait F<int>  for trait F<int>; // error: 不允许给泛型 trait 类型实现泛型 trait
```

6. 支持对 `typedef` 类型实现泛型 trait

```c
typedef struct S S1;
impl trait F<int> for S1;
```



#### 泛型 trait 类型的变量

我们可以定义泛型 trait 实例化后的指针类型变量，并可以通过该指针变量进行函数调用等，具体使用方法如下：

```c
#include <stdio.h>

struct S {};

trait F<T> {
    T foo(This* this);
};
int struct S::foo(struct S* this) {
    return 1;
}
int int::foo(int* this) {
    return 0;
}

impl trait F<int> for struct S;
impl trait F<int> for int;

void test() {
    struct S s;
    int a = 1;
    float b = 1.0;

    trait F<int>* p;
    p = &s; // ok，隐式转换
    p->foo(); // return 1
    p = &a;
    p->foo(); // return 0
    p = &b; // error: float 类型未实现 trait F<int>，不能进行赋值
}
```

**规则：**

1. 只允许声明泛型 trait 实例化后的指针类型变量

```c
trait F<int>* p1; // ok
trait F<int> p2; // error: 不允许定义 trait<int> 类型的变量
```

2. 如果 `<type>` 实现了 `<trait>`，那么指向这个 `<type>` 的指针可以被转换为 `<trait>` 类型的变量

```c
impl trait F<int> for struct S;

struct S s;
trait F<int>* t1 = &s; // 隐式转换
trait F<int>* t2 = (trait F<int>*)&s; // 显式转换
```

3. 泛型 trait 实例化后的指针类型变量可以通过 `->` 方式调用该泛型 trait 中的成员函数

```c
struct S s;
trait F<int>* t = &s;
t->foo();
```

4. 泛型 trait 实例化后的指针类型变量，允许用 `NULL` 赋值

```c
trait F<int>* p = NULL;
```

5. 泛型 trait 实例化后的指针类型变量，不可以解引用

```c
trait F<int> *p;
*p; // error: 泛型 trait 实例化后的指针类型变量，不可以解引用
```

6. 允许指向泛型 trait 的多级指针，但这种类型不能直接调用成员函数。不允许结构体的二级指针直接隐式转换成泛型 trait 的二级指针

```c
trait F<int>* p;
p->foo();
trait F<int>** q = &p; // ok
q->foo(); // error: 多级指针不能直接调用成员函数
(*q)->foo(); // ok
struct S s;
q = &&s; // error: 不允许结构体的二级指针直接隐式转换成泛型 trait 的二级指针
```

7. 泛型 trait 实例化后的指针类型变量可以用 `const` / `volatile` 修饰

```c
const trait F<int>* p1;
volatile trait F<int>* p2;
```

8. 支持泛型 trait 实例化后的指针类型作为函数参数及返回值类型

```c
trait F<int>* get(trait F<int>* t) {
    return t;
}
```

9. 支持泛型 trait 实例化后的指针变量和 `NULL` 做比较（这里的比较仅包含 `==` 和`!=`，下同）

```c
trait F<int>* p = NULL;
p == NULL; // ok
p != NULL; // ok
```

10. 支持泛型 trait 实例化后的指针变量和非 trait 指针变量比较

```c
int a = 1;
int *p1 = &a;
struct S s;
struct S *p2 = &s;
trait F<int> *t = NULL;
// 假设struct S 类型实现 trait F<int>，但 int 类型没有
if (t == p1) {}; // warning
if (t == p2) {}; // ok
if (t == a) {}; // error: 与非指针类型比较报 error
```

11. 支持指针变量和 trait 指针变量比较

```c
trait F<int> *t1 = NULL;
trait F<int> *t2 = NULL;
trait F<float> *t3 = NULL;
if (t1 == t2) {} // ok
if (t1 == t3) {} // warning: 如果trait类型不同会报warning
```



#### 类型转换

泛型 trait 类型转换只能在实现了对应泛型 trait 的类型之间进行，将一个类型转换为另一个类型，同时保留原有类型的特性和方法。

**规则：**

1. 泛型 trait 实例化后的指针变量，不允许强制转换为非指针类型

```c
struct S s;
trait F<int> *p = &s; // 假设 struct S 类型实现了 trait F<int>
(struct S)p; // error: 不允许强制转换为非指针类型
```

2. 支持泛型 trait 指针类型强制转为非 trait 指针类型，但不支持隐式转换

```c
struct S s;
trait F<int> *p = &s; // 假设 struct S 类型实现了 trait F<int>
struct S *q1 = p; // error: 不支持泛型 trait 指针类型隐式转换为具体类型
struct S *q2 = (struct S*)p; // ok
int *q3 = (int*)p; // ok
```

3. 泛型 trait 类型支持强制转换为 `void *`类型，但`void *` 指针无法转换为泛型 trait 指针类型

```c
struct S s;
trait F<int> *p = &s;
void * q = (void *)p; // ok: 泛型 trait 类型支持强制转换为 `void *`类型
trait F<int> *p1 = (trait F<int> *)q; // error: `void *` 指针无法强制转换为泛型 trait 指针类型
trait F<int> *p2 = q; // error: `void *` 指针无法隐式转换为泛型 trait 指针类型
```



### 应用

```c
#include <stdio.h>

// 定义 trait
trait Shape {
    int getArea(This* this);
    int getSideLen(This* this);
};

struct Square {
    int side;
};

struct Rectangle {
    int width;
    int hight;
};

int struct Square::getArea(struct Square* this) {
    int area = this->side * this->side;
    printf("the area of this square is %d.\n", area);
    return area;
}

int struct Square::getSideLen(struct Square* this) {
    int length = this->side * 4;
    printf("the side length of this square is %d.\n", length);
    return length;
}

int struct Rectangle::getArea(struct Rectangle* this) {
    int area = this->width * this->hight;
    printf("the area of this rectangle is %d.\n", area);
    return area;
}

int struct Rectangle::getSideLen(struct Rectangle* this) {
    int length = (this->width + this->hight) * 2;
    printf("the side length of this rectangle is %d.\n", length);
    return length;
}

// 为结构体类型实现 trait
impl trait Shape for struct Square;
impl trait Shape for struct Rectangle;

// trait 指针类型作为函数参数及返回值类型
trait Shape* get(trait Shape* s) {
    return s;
}

void test() {
    struct Square s = {.side = 5};
    struct Rectangle r = {.width = 2, .hight = 3};
    trait Shape* shape = &s;
    // trait 指针变量调用方法
    shape->getArea(); // the area of this square is 25.
    // 强制转换
    ((trait Shape*)&s)->getSideLen(); // the side length of this square is 20.
    // 将指针赋值给 trait 指针类型的变量
    shape = &r;
    shape->getArea(); // the area of this rectangle is 6.
    // 隐式转换，将 struct Rectangle* 转为 trait Shape*
    trait Shape* shape2 = get(&r);
    shape2->getSideLen(); // the side length of this rectangle is 10
}
```



------
