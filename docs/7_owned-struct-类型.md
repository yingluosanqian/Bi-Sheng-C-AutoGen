## owned struct 类型

`owned struct` 是一种自定义类型，与 `struct` 不同，主要体现在非拷贝语义上，一律是 `move` 语义整体跟踪。这意味着原变量中的资源所有权会转移到新变量或参数中。本节依次介绍如何定义 `owned struct` 类型，如何创建 `owned struct` 实例。

### 定义 `owned struct` 类型
`owned struct` 类型的定义由关键字 `owned struct` 和自定义的名字组成，紧跟着是定义在一对花括号中 `owned struct` 定义体，在定义体中可以定义成员变量、析构函数、成员函数和访问修饰符。允许定义泛型 `owned struct`。
示例：
```c
owned struct Person{
public:
    char name[50];
    int age;
    char* getName(Person *this) {
        return this->name;
    }
    int getAge(Person *this) {
        return this->age;
    }
    ~Person(Person this) {
        printf("Name = %s\n", this.getName());
        printf("Age = %d\n", this.getAge());
    }
};
```
上例定义了名为 `Person` 的 `owned struct` 类型，它有两个成员变量 `name` 和 `age`、成员函数`getName` 和 `getAge`、以及析构函数 `~Person`。

注：`owned struct` 与 `C struct`类似，允许结构体嵌套。
#### 成员变量

`owned struct` 的成员变量分为实例成员变量和静态成员变量(`static` 修饰)，和 `struct` 一样，成员变量定义的时候不允许写初始化。

```c
owned struct Person{
public:
    char name[50];
    static int age;
};
int Person::age = 20;
```

#### 析构函数
在一个对象生命周期结束时，会自动调用析构函数。析构函数与 `owned struct` 类型同名，前面带有 `~`, 但是不允许写泛型参数。当用户未定义析构函数时，编译器会自动提供默认的析构函数。
```c
owned struct S {
   ~S(S this) {
    printf("S destructor\n");
   }
};
```
当`owned struct`内有owned 修饰的指针的时候，该指针需要在析构函数内手动释放
```c
owned struct Person{
public:
    int * owned age;
    ~Person(Person this){
        safe_free((void * owned) this.p);
    }
};
Person p = {.p = safe_malloc(42)};
```


析构函数的使用有以下限制：

+ 一个 `owned struct` 最多只能有一个析构函数。
+ 不允许作为扩展定义，不允许写返回类型，参数只有一个 `owned struct` 类型的 `this`, 不允许用户主动调用。
+ 析构函数内部需要将 `this` 的所有 `owned` 成员释放，规则同 `ownership` 的检查规则。需要注意的是如果 `this` 的成员是 `owned struct`类型，那么成员的释放是由编译器自动添加的。
+ 全局变量的析构函数不会被调用，包括函数内定义的 `static` 变量。
+ 局部变量的析构函数, 如果在本函数内没有被 `move` 走，析构的顺序为先定义的变量后析构。
+ 临时变量是不支持析构的，会报内存泄漏。
+ 自定义类型内部的成员带有析构函数的时候，析构函数调用顺序：
  + 先调用外层类型的析构函数，再调用成员变量的析构函数
  + 不保证各个成员的析构函数的调用顺序
+ `owned struct` 及其内部的成员变量，在作用域结束时，必须处于以下两种状态之一
  + owned 状态：`owned struct` 及其内部所有owned修饰的成员（1.owned struct 也属于owned 修饰的成员 2.递归包含）均未被移动
  + moved 状态：`owned struct` 作为一个整体已被显式移动
+ `owned struct` 及其内部的成员变量，在作用域结束时，如若处于如下状态，则报错。 报错信息模板为 partially moved `owned struct`:`%0` at scope end, `%1` moved"（%0 为`owned struct` 变量名，%1 为被移动的成员变量名）
  + 有成员变量被转移所有权的状态： `owned struct`（递归包含嵌套成员）至少有一个owned 修饰的成员被移动。结构体本身未被整体移动。
+ `owned struct`内owned 修饰的指针需要在析构函数内被手动释放。如未被手动释放，则报错。 报错模板信息为 destructor for`%0` incorrect, %1 of owned type and needs to be handled manually（ %0 为owned struct 变量名）
#### 成员函数
`owned struct` 的成员函数分为实例成员函数和静态成员函数(不允许 `static` 修饰)。实例成员函数需要显式参数 `this`, 假设当前 `owned struct` 类型是 `C`, `this` 的类型可以是 `C*`、`const C*`、`C* borrow`、`const C * borrow`、`C * owned`。静态成员函数是没有 `this`。成员函数的访问与 `struct` 扩展成员函数访问一样(详见成员函数章节)。

注：当前不支持 owned struct 内部定义泛型函数。

```c
owned struct Person{
public:
    char name[50];
    int age;
    char* getName(Person *this) {
        return this->name;
    }
    char* getTypeName(){
        return "Preson";
    }
};
```

上例是 `owned struct` 定义体内部实例成员函数 `getName` 和静态成员函数 `getTypeName`。

`owned struct` 定义体内部可以只有函数声明，把函数体外置。等同于 `owned struct` 定义体内部的成员函数。
示例：

```c
owned struct Person{
public:
    char name[50];
    int age;
    char* getName(Person *this);
    char* getTypeName();

};
char* Person::getName(Person *this) {
    return this->name;
}
char* Person::getTypeName(){
    return "Preson";
}
```
`owned struct` 与 `struct` 类似，允许扩展成员函数（详见成员函数章节）。

#### 访问控制控制权限
`owned struct` 定义体内，允许成员指定可见性分为 `public` 和 `private`, 默认为 `private`。只有 `owned struct` 定义体内部的成员函数有权访问 `private` 和 `public`成员，在`owned struct` 外部（包括扩展成员函数）, 只能访问 `public` 成员。示例：

```c
owned struct A{
    private:
    int a;
    public:
    int b;
};
int A::f(A* this) {
    this->a; // error
    this->b; // ok
    return 0;
}
```

### 创建 `owned struct`实例
`owned struct` 允许使用 `struct initializer` 语法创建实例，也允许单独对每个成员变量初始化（如果成员变量是 `public`, 此时与 `struct` 一样单独跟踪每个成员的初始化状态，但是需要在安全区状态下保证在发生 `move`、传参、析构和返回等场景下该变量一定已经完整初始化, 非安全区不做保证。同时为了方便 `owned struct` 类型在使用的时候不携带 `owned struct` 关键字。
