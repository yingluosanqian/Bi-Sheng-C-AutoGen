<div>
    <div style='height:1000px;width:90%'>
        <div style='border-top:1px solid'> </div>
        <div style='margin-top:10%;font-size:28px;width:100%;heigth:80%;font-width:600;letter-spacing:2px;text-align:center'>
            <span style=''>毕昇 C 用户手册</span>
        </div>
    </div>
</div>
<div style=“package-break-after:always;“></div>

## 编译器安装和使用

### 安装毕昇 C 编译器

首先请前往毕昇 C 版本发布渠道下载安装包，当前我们为开发者提供 Linux 平台上的 rpm 格式安装包，支持  clang + llvm 后端和 clang + BiShengC 后端。

> 注：其中 clang + llvm 支持编译和运行环境都在 X86_64 环境；而 clang + BiShengC 支持 X86_64 环境编译，aarch64 环境运行，如果用户想要在 X86_64 环境运行，则需要使用 qemu 工具。

#### clang + llvm 版本安装

以 clang+llvm_15.04_BiShengCLanguage-x-y.rpm 为例，下载到本地后，安装步骤如下 ：

- 解压

  ```shell
  $ rpm2cpio clang+llvm_15.0.4_BiShengCLanguage-x-y.rpm | cpio -div
  # 解压后会在当前目录生成 /opt/buildtools/clang+llvm_15.0.4_BiShengCLanguage 目录
  ```

- 配置环境变量

  > 注：所配置的环境变量仅在运行下列命令的当前 `shell` 会话窗口有效，重启 `shell` 后需要重新配置环境变量。若想要这些环境变量在 shell 每次启动时重新生效，你可以在 `$HOME/.bashrc` 或 `$HOME/.ashrc` (根据 shell 的种类而定) 等 `shell` 初始化配置文件中加入如下命令：

  ```shell
  $ export LLVM_HOME=/path/to/clang+llvm_15.0.4_BiShengCLanguage/bin
  $ export PATH=$LLVM_HOME:$PATH
  ```

- 验证安装，执行以下命令：

  ```shell
  $ clang --version
  ```

若安装成功，可以看到当前的版本号和安装目录，其格式如下：

`clang version xx.xx.xx`

`InstalledDir: /path/to/clang+llvm_15.0.4_BiShengCLanguage/bin`

#### clang + BiShengC 版本安装

以 bsc_host_linux_x86_64_target_aarch64-x-y.rpm 为例，下载到本地后，安装步骤如下 ：

- 解压

  ```shell
  $ rpm2cpio bsc_host_linux_x86_64_target_aarch64-x-y.rpm | cpio -div
  # 解压后会在当前目录生成 /opt/buildtools/bsc_host_linux_x86_64_target_aarch64 目录
  ```

- 下载第三方工具包（由于 rpm 不包含 GCC 交叉编译工具链及 qemu 工具，可直接下载我们提供的第三方工具包）

  ```shell
  # 下载与解压
  $ git clone https://gitee.com/bisheng_c_language_dep/ThirdParty.git
  $ cd ./ThirdParty
  $ dpkg-deb -R qemu-user_2.11+dfsg-1ubuntu7.40_amd64.deb qemu
  ```

- 配置环境变量（也可加入 `$HOME/.bashrc` 或 `$HOME/.ashrc` 等配置文件）

  ```shell
  $ export Maple_Path=/path/to/bsc_host_linux_x86_64_target_aarch64
  $ export MTP=/path/to/ThirdParty
  $ export BiShengC_GCC_Path=$MTP/gcc-linaro-7.5.0-2019.12-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc
  $ export PATH=$PATH:$Maple_Path/bin:$MTP/qemu/usr/bin
  
  # 设置编译时和 qemu 运行时依赖的库
  $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MTP/gcc-linaro-7.5.0-2019.12-i686_aarch64-linux-gnu/aarch64-linux-gnu/libc/lib
  $ export QEMU_LD_PREFIX=$MTP/gcc-linaro-7.5.0-2019.12-i686_aarch64-linux-gnu/aarch64-linux-gnu/libc
  ```

### 卸载与更新

在 linux 平台，删除相应目录下的文件，移除环境变量即可完成卸载（最简单的，您可以重新开一个 shell 环境）。

如需要更新，用户需自行卸载后重新下载安装新的版本。

### 第一个毕昇 C 程序

如下示例中，我们创建一个名为 bsc_project 的目录，创建 demo.cbs 源程序文件，并键入以下内容。

注：毕昇 C 的源码文件以 .cbs 为后缀。

```shell
$ mkdir -p bsc_project && cd bsc_project
$ touch demo.cbs
# 向demo.cbs写入如下内容：
```

```c
#include <stdio.h>

struct Foo {
    int a;
};

int struct Foo::getA(struct Foo* this) {
    return this->a;
}

int main() {
    struct Foo foo = {.a = 1};
    printf("foo.getA() = %d\n", foo.getA());
    return 0;
}
```

使用编译命令编译该文件，得到可执行文件，如下：

```shell
# clang + llvm 编译运行
$ clang demo.cbs -o demo
$ ./demo
foo.getA() = 1

# clang + maple 编译运行
$ maple demo.cbs -o demo
$ qemu-aarch64 demo
foo.getA() = 1
```

输出如上结果，说明你已经成功应用了毕昇 C 的成员函数特性。



## 毕昇 C 简介
在系统编程领域，C/C++ 是应用最广泛的编程语言。在硬件资源十分受限的嵌入式场景下，C 语言使用的最多，但使用 C 语言编码存在很多痛点问题，比如 C 语言中指针使用带来的内存安全问题，C 语言缺乏原生的并发支持，以及一些基础的编程抽象(如泛型等)。近年来，在系统编程语言领域有不少探索的工作，比如 Rust，主打内存安全(所有权，生命周期，borrow checker 等)和并行并发(无栈协程)。Rust 是一门全新的编程语言，采用了和 C/C++ 完全不同的语言设计，学习曲线陡峭，也无法解决存量代码开发的问题。

在这个背景下，毕昇 C 采用了不同的策略，它基于 C 语言做了很多增强的设计，比如更强的内存安全特性，语言层面支持并发等，且可以在存量代码中渐进式的使用这些特性而不用完全重写已有代码。可以认为，毕昇 C 是 C 语言的一个超集。这本用户手册，将从以下三个方面介绍毕昇 C ：
- 基础编程抽象：成员函数，trait，泛型
- 内存安全：所有权，借用
- 并发：无栈协程

------

## 成员函数

### 概述
在 C 语言里，如果我们想表达某个类型的数据(data)有对应的某个方法(operation)，一般使用全局函数，让这个数据类型作为入参，如下：
```c
struct Data{
  int x;
};

void print_data(struct Data* data) {
    // 提供 print data 的实现逻辑
    printf("print data\n");
}

void test() {
    struct Data data = {.x = 1};
    print_data(&data);
}
```

类似的，针对 int 类型我们可能需要 `print_int` 的函数，针对 float 类型需要 `print_float` 的函数，这不是一件令人愉快的事情，我们希望有一种更简洁的方式去表达类型与方法关联这件事，这就是为C语言引入成员函数的部分动机。引入成员函数后，上面例子的代码可以这么写：
```c
struct Data{
  int x;
};

void struct Data::print(struct Data* this) {
    // 提供 print data 的实现逻辑
    printf("print data\n");
}

void int::print(int* this) {
    // 提供 print int 的实现逻辑
    printf("print int\n");
}

void float::print(float* this) {
    // 提供 print float 的实现逻辑
    printf("print float\n");
}

void test() {
    struct Data data = {.x = 1};
    int a = 1;
    float b = 1.0;
    data.print();
    a.print();
    b.print();
}

```

如果，我们想表达某些类型具有一组相似的行为，比如上面例子中的 `print` ，我们可以定义一个 `trait`，然后让 `struct Data` `int` `float` 等类型实现这个 `trait` 。成员函数和 `trait` 相结合，非常有表达力。关于 `trait` 的介绍，参考后续章节。

下面，我们简单介绍下毕昇 C 成员函数的一些具体规则：

### 基本语法

当我们想为某个类型增加一个成员函数时，我们只需要在普通函数定义的语法基础上，在函数名如 foo 前，增加 `typename::foo`，如下所示：
```c
void foo1() {
  // do nothing
};

void int::foo2(int* this) { // 实例成员函数，第一个入参是 This 指针，指向当前int类型的实例
  // do something
}

void int::foo3(int this) { // 实例成员函数，第一个入参是 This 实例，不是 This 指针
  // do something
}

void int::foo4() { // 静态成员函数
  // do something
}

```

其中，type-name 可以是基础类型如 `int`, `float` 等，也可以是用户自定义的结构体等，符合 C 语言对类型的定义规则，此外可以使用`This` 来简化表示当前类型。下面是更多的用法示例：

```c
// case 1
void int::print(int* this); // 声明

void int::print(int* this){ // 定义
    printf("int::print");
}

// case 2
struct S1{};
// 错误使用 S，在 C 语言里 struct S 才是一个类型
void S1::print(struct S1* this); // error: must use 'struct' tag to refer to type 'S'
void struct S1::print(struct S1* this); // Ok，修正后的声明

// case 3
typedef struct {
}S2;
void S2::print(S2* this); // Ok, S2 是 typedef 后的 struct S2

// case 4
void S2::print(This this); // Ok, This 表示当前类型 struct S2
void S2::print(This* this); // Ok, This* 表示指向当前类型 struct S2 的指针

```

采用这样的语法设计有一个好处，那就是我们很方便就可以给已有类型增加成员函数而不用侵入式修改源码。

### 关于 `this`

在上面的成员函数的例子中，参数列表中的第一个参数如果为 `this`(如果有 `this`，它也只能是第一个参数)，它表示该成员函数对应类型实例(This this)、或指向该实例的指针(This* this)，它是一个“实例成员函数”。如果成员函数参数列表中，没有 `this` 存在，则表示这是一个“静态成员函数”。
```c
typedef struct {/*...*/} M;
void M::f(M* this, int i) {} // 实例成员函数

typedef struct {/*...*/} N;
void N::f() {} // 静态成员函数

int main() {
    M x;
    x.f(1); // Ok
    M::f(&x, 1); // Ok
    M* x1 = &x;
    x1->f(1); // Ok

    N y;
    y.f(); // Err: y does not have instance member function, use N::f instead.
    N::f(); // Ok
    return 0;
}

```
对于实例成员函数(第一个入参为`this`)，其调用方式有两种：

(1) 和访问成员变量类似，实例类型调用用 `.` 符号，如 `x.f(1)`；指针类型调用，用 `->` 符号，如 `x1->f(1)`。

(2) 普通函数调用方式，如 `M::f(&x, 1)`。

对于静态成员函数，其调用方式和调用普通全局函数类似，区别只是函数名变成 `type-name::func-name`，如 `N::f()`。

### 其他规则

- 成员函数支持声明和定义分开，如下：
```c
// 声明
const char* int::to_string(const int* this) ;

// 定义
const char* int::to_string(const int* this){
    // to_string 的实现，略
}

```
- 新增成员函数不影响原类型的 layout 包括 size 和 alignment
- 成员函数不支持重载和重定义
- 成员函数的名字不允许与成员变量相同，适用于 struct, union, enum 等
- 成员函数允许赋值给函数指针。
- 禁止对 cv-qualified type (被类型修饰符修饰的类型，如 const int 等) 添加成员函数
- 禁止对 “函数类型” "数组类型" "指针类型" 添加成员函数
- `this`指针允许被const/volatile等修饰符修饰
- 不允许给 incomplete type 扩展成员函数，incomplete type 即为那些声明了但未完整定义的类型
- 不允许给`void`类型扩展成员函数
- 如果两个头文件中对同一个类型扩展了同名的成员函数，那么在一个编译单元中包含这两个头文件，会导致编译错误
- 当前暂时禁止通过整数字面量、浮点数字面量、复合类型字面量直接调用成员函数

------

## 泛型

### 泛型概述

泛型是一种编程技术，它可以让类型（如整数、字符串等基本类型，或者用户自定义的类型）作为参数传递给函数、类或接口，从而实现代码的复用和灵活性，并可以非常高效地实现一些方法。

毕昇 C 的泛型是一种编译时的泛型机制，它可以定义一个通用的函数或类，然后根据不同的类型参数生成不同的实例。

目前，毕昇 C 已支持**泛型函数**、**泛型结构体**和**泛型类型别名**。

#### 实现动机

泛型的目的是为了提高代码的**效率**和**重用性**而实现的，其优点在于：

- 避免了代码冗余
- 提高了代码的可读性和可维护性
- 实现了类型安全和编译时检查
- ...

泛型编程使程序员能够编写一个适用于所有数据类型的通用算法。它消除了如果数据类型是整数、字符串或字符，就需要创建不同算法的场景。

这就使得用户可以为类或函数声明一种通用模式，使得类中的某些数据成员或成员函数的参数、返回值取得任意类型。

#### 示例

以下方的代码为例：

```c
int sum_int(int a, int b) {
    int c = a + b;
    return c;
}

float sum_float(float a, float b) {
    float c = a + b;
    return c;
}

int main() {
    int sum1 = sum_int(1, 2);
    float sum2 = sum_float(1.2, 2.5);
}
```

可以看出，对于sum方法，如果要实现返回值分别为 **float** 和 **int** 两种情况，普通的 C 语言需要为同样实现的方法定义两次。

但是如果使用毕昇 C 的泛型语法，则只需定义一次，即可在实例化时重复使用，如下：

```c
T sum_t<T>(T a, T b) {
    T c = a + b;
    return c;
}

int main() {
    int sum1 = sum_t<int>(1, 2);
    float sum2 = sum_t<float>(1.2, 2.5);
}
```

可以看出，泛型功能的引入，对于用了相同算法的声明场景，其代码量有明显的减少。

### 语法规则

对于毕昇 C 泛型，我们设计了如下的语法规则：

- 在声明泛型函数、结构体或类型别名时，泛型参数列表要用尖括号 '<>' 包裹起来，尖括号内部的类型一般是 identifier ，如 'T1', 'T2' 之类 。


- 在实例化时，既可以在尖括号内部传入具体的类型，如 int, float, struct S 等，也可以省略尖括号的书写，编译器会根据实际传入的参数进行隐式的类型推导。此外，如果将现有类型 typedef 为其他别名后，同样可以在实例化时用作泛型实参。


- 同时，毕昇 C 的泛型函数、泛型结构体和泛型类型别名也支持使用**常量参数**作为泛型的形参。

下面我们将分为三个部分详细说明。

#### 泛型函数

对于泛型函数，我们对语法规则的设计，主要体现在两个方面：

1. 声明时，区别于普通函数声明，我们需要在**函数名**和**函数入参**之间，添加一对尖括号 '<>' ，并在尖括号中写明泛型函数的**泛型形参**，其中形参可以为任何合法的名字（此处的合法指的是不会导致语义冲突的情况）；

   同时，对于函数返回值的类型，可以是普通的 builtin 类型，可以是用户已经定义过的结构体，也可以是泛型形参中的一个（如 T）。

2. 实例化时，类型既可以在尖括号中显式指定，也可以省略尖括号以及其中的内容，由编译器进行隐式推导：

   1. 显式指定类型时，区别于普通的函数调用，同样需要在被调用的**函数名**与**函数入参**之间添加一对尖括号 '<>' ，且中间无空格；然后在尖括号中传入**泛型实参**，此处的实参可以是 builtin 类型，也可以是用户已经定义过的结构体。
   2. 隐式推导时，写法与普通的函数调用相同，毕昇 C 编译器会根据函数调用传入的参数类型，自动推导**泛型实参**的类型。不过为了代码可读性等，推荐使显式指定类型。

下面是一些用法示例：

```c
typedef long int LT;

// 泛型函数
T max<T>(T a, T b) {						// 开头的'T'为函数返回值类型，而'<>'中的'T'泛型函数'max'的泛型形参
    T Max = a > b ? a : b;
    return Max;
}

int main() {
    int a = 3;
    int b = 5;
    int c = 4;

    // 泛型函数 实例化
    int max1 = max<int>(a, b);				// 显示指定泛型实参类型
    int max3 = max(a, c);				    // 隐式推导，编译器自动推导'T'为 int 类型

	return 0;
}
```



#### 泛型结构体

对于泛型结构体，我们对语法规则的设计，同样体现在两个方面：

1. 声明时，区别于普通结构体声明，我们需要在**结构体名**的后面之间，添加一对尖括号 '<>' ，并在尖括号中写明泛型结构体的**泛型形参**。
2. 实例化时，泛型结构体仅支持显式指定类型，即：显示指定类型时，区别于普通的结构体的构造，同样需要在被构造的**结构体名**后面添加一对尖括号 '<>' ，且中间无空格；然后在尖括号中传入**泛型实参**，此处的实参可以是 builtin 类型，也可以是用户已经定义过的结构体。
3. 在使用泛型结构体类型时，如声明泛型结构体类型的变量、声明泛型结构体类型的成员、声明参数、声明返回值、扩展成员函数时，可以省略 struct。即在使用形如`struct S<T>`的类型时，可以简写为`S<T>`，但在声明该类型时不允许省略。

下面是一些用法示例：

```c
typedef long int LT;

// 泛型struct
struct S<T, B>{
    T a;
    B b;
};

// 泛型union
union MyUnion<T1, T2> {
    T1 u1;
    T2 u2;
};

// 返回类型为'泛型union'的泛型函数'foo_union'
union MyUnion<T1, T2> foo_union<T1, T2>(union MyUnion<T1, T2> *this) {
    return *this;
}

int main() {
    // 泛型struct 实例化
    struct S<int, LT> s1 = {.a = 42, .b = 5};		// 使用 typedef 后的类型作为泛型实参

    // 泛型union 实例化
    union MyUnion<int, float> p;
    foo_union(&p);		// 泛型函数 foo_union 的隐式类型推导

    return 0;
}
```

#### 泛型成员函数

在支持定义泛型 struct 和泛型 union 类型的基础上，还可以为它们扩展普通成员函数。

如下是一个用法示例，该示例包含了声明泛型成员函数、定义泛型成员函数及实例化调用泛型成员函数：

```c
struct MyStruct<T> {
    T res;
};

union MyUnion<T> {
    T res;
};

T struct MyStruct<T>::foo(struct MyStruct<T>* this, T a); // 声明泛型成员函数
T struct MyUnion<T>::foo(struct MyStruct<T>* this, T a);

T struct MyStruct<T>::foo(struct MyStruct<T>* this, T a) { // 定义泛型成员函数
    this->res = this->res + a;
    return this->res;
}

T struct MyUnion<T>::foo(struct MyStruct<T>* this, T a) {
    this->res = this->res + a;
    return this->res;
}

int main() {
    struct MyStruct<int> s = { .res = 1 };
    struct MyUnion<int> u = { .res = 5 };
    int res1 = s.foo(2); // 调用泛型成员函数
    int res2 = u.foo(6);
    return 0;
}
```

关于泛型成员函数，还有以下几点需要注意：

1. 泛型成员函数可以是静态函数，即第一个参数可以不为`this`；
2. 不允许泛型成员函数的重载，这与成员函数的规则相同；
3. 泛型成员函数的返回类型可以是泛型 struct 或泛型 union类型。


#### 常量泛型

除了基础泛型的实现，毕昇 C 还引入了常量泛型的功能。具体来说，常量泛型是一种允许程序项在常量值上泛型化的特性。也就是说，常量可以作为泛型参数传递到泛型变量中，代码会根据常量参数而进行特化，从而确保无开销，并可以直接在代码中作为常量来使用。

例如，在 毕昇 C  中，可以定义一个泛型结构体，其中一个泛型参数是一个**常量泛型参数**，该参数可以用于表示结构体内定义的数组的大小。

这样，通过在实例化时传入不同的常量值，便可以生成多个不同大小的数组对象，如：

```c
struct Array<T, int N> {
    T data[N];
};

int main() {
    struct Array<int, 5> arr1();
    struct Array<int, 10> arr2();
    return 0;
}
```

如上，这里的 '10' 和 '5' 就是常量泛型参数 'int N' 的实参，它们决定了数组的大小。

目前，泛型常量的规则如下：

- 常量泛型的形参只支持“可编译时计算的类型”，目前只支持整数类型
- 常量泛型的实参只能是“编译时可计算”的常量表达式
- 语法上，如果只是 int 字面量、constexpr 常量，那么可以不需要小括号，其它常量表达式一律需要用小括号

目前，毕昇 C 对于常量泛型的实现仅限于整形的“整数常量”：

- 对于声明时，形参列表仅接受 int 及其修饰符 long、short、unsigned、signed，以及上述关键字的各种组合。同时也支持将上述关键字 typedef 成其他别名再做为形参。
- 对于实例化时，目前泛型实参列表支持 IntegerLiteral （即常量1，2之类），同时也支持 constexpr修饰的变量与常量表达式。

下面是一些用法示例：

```c
#include <stdio.h>

typedef long long int LLInt;

// 使用了泛型常量的泛型函数
int print_dataSize<T, int B>()
{
    T data[B];
    printf("the size of data is %d\n", B);
  	return B;
}

// 使用了 typedef别名 作为泛型常量的泛型函数
void print_const<LLInt B>() {
    printf("the const is %d\n", B);
}

// 使用了泛型常量的泛型struct
struct Array_1<T, int N>
{
  	T data[N];
};

// 使用了 typedef别名 作为泛型常量的泛型struct
struct Array_2<LLInt B, int C, T>
{
  	LLInt data1[B];
  	int data2[C];
  	T a;
};

int main() {
  	int a1 = print_dataSize<int, 5>();
  	print_const<20>();

  	struct Array_1<int, 5> arr1;
  	struct Array_2<5, 6, int> arr2 = {.a = 1};

    return 0;
}
```

#### 泛型类型别名
标准 C 已有类型别名的功能，语法为：
```c
typedef OldType NewType;
```
为了使类型别名能够与泛型一起配合使用，BSC 引入与标准 C 语法不同的类型别名语法：
```c
typedef NewType = OldType ;
```
加上泛型参数就形成了泛型类型别名，例如：
```c
typedef MyPointerType<T> = T*;
```
泛型类型别名的使用可以简化类型的书写，还可以为类型赋予更具描述性的名称，使代码更易于阅读和理解，举例来说：

我们可以使用 HashMap 来记录某年级学生的各科成绩，Key 表示学生的学号，Value 表示学生的各科成绩，根据实际情况的不同，学生的学号可以用 int、string 等类型表示，成绩可以用 int、float 等类型表示，科目数量也可能发生变化，使用泛型类型别名有助于我们根据实际需求进行定制：

```C
//辅助类及成员方法
struct HashMap<K, V> {
   //省略实现
};
void struct HashMap<K, V>::insert(This* this, K key, V value) {
   //省略实现
}
struct Array<T, int N> {
    T a[N];
};
//使用泛型类型别名定义一个特殊的HashMap类型，它的key是T1类型，value是一个长度为N，元素类型为T2的数组类型：
typedef GenericGrade<T1, T2, int N> = struct HashMap<T1, struct Array<T2, N>>;
//继续使用类型别名，针对不同的年级进行定制：
typedef Grade1 = GenericGrade<int, int, 3>;  //一年级学生学号为int，成绩为int，科目数量为3
typedef Grade3 = GenericGrade<int, float, 4>;//三年级学生学号为int，成绩为float，科目数量为4
typedef Grade6 = GenericGrade<int, float, 5>;//六年级学生学号为int，成绩为float，科目数量为5

int main() {
    Grade1 grade1;
    grade1.insert(10, {80, 90, 95});
    grade1.insert(11, {80, 95, 90});
    Grade3 grade3;
    grade3.insert(12, {90.0, 95.5, 90.0, 85.0});
    grade3.insert(13, {80.0, 90.0, 95.5, 90.0});
    Grade6 grade6;
    grade6.insert(15, {80.0, 90.0, 95.5, 90.0, 85.0});
    grade6.insert(16, {80.0, 90.0, 95.5, 90.0, 85.0});
    return 0;
}
```

对于类型别名，有以下规则：
1. 不允许为泛型类型别名扩展成员函数。
```C
struct S<T> {};
typedef MyS<T> = struct S<T>;

void MyS<T>::foo(This* this) {} //error
```
2. 不允许在结构体类型内部定义类型别名。
```C
struct S<T> {
    typedef type = T;    //error
    typedef Int64 = int; //error
};
```
3. 不允许在函数体内定义泛型类型别名，但可以定义普通类型别名。
```C
void foo<T>() {
    typedef type = T;
    typedef Int64 = int;

    typedef MyType1<T> = T;   //error
    typedef MyType2<T1> = T1; //error
}
```

下面是一些用法示例：
```C
struct S<T> {};
struct V<T1, T2> {
    T1 a;
    T2 b;
};

// 普通类型别名
typedef Int64 = long int;   //等价于 typedef long int Int64;
typedef MyS = struct S<int>;//等价于 typedef struct S<int> MyS;

// 泛型类型别名
typedef MyPointerType<T> = T*;
typedef Array_3<T> = T[3];
typedef Array_N<T, int N> = T[N]; //支持带常量泛型参数

typedef MyS_T_T<T> = struct V<T, T>;
typedef MyS_T_int<T> = struct V<T, int>;

int main() {
    Int64 a = 5;  //等价于int a = 5;
    MyS s;        //等价于struct S<int> s;
    int b = 2;
    MyPointerType<int> c = &b;  //等价于int* c = &b;
    Array_3<int> d = {1,2,3};   //等价于int d[3] = {1,2,3};
    Array_N<int, 3> e= {1,2,3}; //等价于int e[3] = {1,2,3};
    MyS_T_T<int> s2;
    MyS_T_int<int> s3;
    return 0;
}
```

##### conditional 泛型类型别名
在 bsc_conditional.hbs 这一 BSC 标准库中提供了 conditional 泛型类型别名，可以实现类型层面的“分支逻辑”：
```c
// bsc_conditional.hbs
typedef conditional<int C, T, F> = __conditional(int C, T, F);
```
当 C 非 0 时，conditional 类型别名指代类型 T ，否则指代类型 F，条件表达式必须是可以编译期求值的常量表达式：
```c
#include<bsc_conditional.hbs>  //使用conditional需要导入头文件
int main() {
    conditional<1, int, double> a = 1;   //等价于int a = 1;
    conditional<0, int, double> b = 1.0; //等价于double b = 1.0;
    return 0;
}
```
使用conditional，不仅可以简化书写，可以在编译时根据条件选择不同的类型，避免了运行时的条件分支，提高代码的效率，以下是一个关于选择函数返回类型的使用案例：

定义一个泛型函数，它的返回值类型取决于泛型参数 T ，如果 T 是指针类型，则返回值类型仍然是 T ，否则，返回 T 的指针类型。

C++ 中需要借助泛型特化和 concept 来实现：
```cpp
// T 是指针类型时，std::is_pointer_v<T> == true，匹配该版本:
template<typename T> requires std::is_pointer_v<T>
T foo() { ... }

// T 不是指针类型时，匹配该版本:
template<typename T>
T* foo() { ... }
```

在 BSC 中，我们可以借助 conditional 很方便地实现这样的功能，相比C++更加方便易用：
```c
typedef PointerType<T> = conditional<is_pointer<T>(), T, T*>;

PointerType<T> foo<T>() { ... }
```

------
## 常量计算
### constexpr
#### 概述
constexpr 可以定义编译时常量和编译时计算返回值的函数。
在 C 语言中已经有了 const 关键字，而它的含义更多的是 readonly 的意思，不是“编译时常量”这么强的约束，所以我们需要引入 "constexpr" 这个关键字来表达编译时计算的能力。

定义“编译时计算”的类型：
bool,char(signed char, unsigned char), 整数类型（包括 int 以及被 short/signed/unsigned/long/long long 等修饰的 int 类型，不包括 enum 类型），以及这些类型的别名。

定义“常量计算”上下文，也就是 constexpr 修饰的变量和函数可以作为常量使用的场景：
- 可以用于 static_assert 中，第一个条件参数属于“常量计算”上下文
- 可以用于定义定长数组，数组长度属于“常量计算”上下文
- 可以用于初始化其它 constexpr 常量
- 可以用于常量泛型的实参

下面举例说明什么是“常量计算”上下文。
```c
void bar<int N>(){}

constexpr int foo() {
    return 5;
}

int main() {
    constexpr int a = 5;

    //可以用于常量泛型的实参
    bar<a>();
    bar<foo()>();

    //可以用于定义定长数组
    int arr1[a] = {0};
    int arr2[foo()] = {0};

    //可以用于初始化其它 constexpr 常量
    constexpr int b = a;
    constexpr int c = foo();

    //可以用于 static_assert 中
    _Static_assert(a == 5, "fail");
    _Static_assert(foo() == 5, "fail");

    return 0;
}
```
#### 使用规则
##### constexpr 修饰变量
1. constexpr 可以修饰一个常量定义，且必须在定义时被初始化，否则要报错
```c
constexpr int a = 5;
constexpr int b; //error,未初始化
```
2. constexpr 修饰的常量在定义之后，不可被修改
```c
constexpr int a = 5;
a = 10; //error
```
3. constexpr 修饰常量的类型只能是上述“编译时计算”的类型
```c
constexpr float a = 5.0;//error,“编译时计算”的类型不包括浮点类型
```
4. constexpr 修饰的常量的初始化表达式必须可以在编译时求值，否则要报错。可编译时求值的常量表达式可以是：
- 字面量
- constexpr 修饰的常量
- sizeof,_Alignof 表达式
- 以可编译时求值的常量表达式作为实参，调用 constexpr 函数
- 由以下运算符组合起来的常量表达式，也是常量表达式：+,-,*,/,%,>,<,==,!=,<=,>=,&,|,^,~,!,&&,||,<<,>>,?:

举例说明：
```c
//场景1
int a = 10;
constexpr int b = a;//error
//场景2
constexpr int a = 10;
constexpr int b = a;
//场景3
constexpr int a = sizeof(int);
constexpr int b = sizeof(int);
//场景4
constexpr int foo(int a) {
    return 5;
};
constexpr int a = 10;
constexpr int b = foo(a);
//场景5
constexpr int b = 1 == 1.0;
```

5. 函数指针可以使用 constexpr 修饰，且函数指针也可以指向 constexpr 函数
6. constexpr 可以修饰指针变量，但其只能指向全局变量或静态变量

##### constexpr 修饰函数
1. constexpr 可以修饰一个函数声明或者定义，但必须保证声明和定义中同时有 constexpr 修饰或都没有 constexpr 修饰，否则会导致编译错误
```c
constexpr int foo();
constexpr int foo() {
    return 5;
}
```
2. constexpr 修饰的函数，参数和返回类型，只能是上述“编译时计算”的类型
```c
constexpr void foo(); //error,返回值是空值，不属于“编译时计算”的类型
```
3. constexpr 可以修饰泛型函数
```c
constexpr int foo<T>();
```
4. constexpr 函数体内的所有语句，都是编译期可求值的
- constexpr 函数体内不允许定义 static 变量
- constexpr 函数体内不允许调用非 constexpr 函数
- constexpr 函数体内不允许访问外部的非 constexpr 变量
- constexpr 函数体内不允许内嵌汇编
- constexpr 函数体内允许定义不使用 constexpr 修饰的局部变量，这些变量也只能是“编译时计算”的类型

5. 在非“常量计算”的上下文中，constexpr 修饰的函数可以当作普通函数使用，实参不需要是常量，返回值也不需要是常量。在“常量计算”的上下文中，实参和返回值都要求是常量表达式，否则会报错
```c
constexpr int foo(int a) {
    return 5;
};

int a = 10;
constexpr int b = foo(a);//error，foo 函数处于“常量计算“上下文中
int c = foo(a);//ok，foo 函数处于非“常量计算“上下文中
```
6. constexpr 可以修饰成员函数，包括普通成员函数和静态成员函数
```c
//普通成员函数，参数 This* this 不属于编译时计算类型
constexpr int int::foo1(This* this) { //error
    return 5;
}

//静态成员函数
constexpr int int::foo2() {
    return 5;
}

int main() {
    constexpr int c = int::foo2();//ok，可编译期求值
    return 0;
}
```
6. constexpr 不允许修饰 async 函数
7. constexpr 不允许支持变长参数
8. 函数的形参不能用 constexpr 修饰
```c
int foo1(constexpr int a) { //error
    return 5;
}

constexpr int foo2(constexpr int a) { //error
    return 5;
}
```
------

### type trait

type trait 可以看作是一个编译期计算返回值的 constexpr 函数。
BSC标准库中提供了一系列 type trait 泛型函数，使用时需要导入头文件 bsc_type_traits.hbs

目前实现的 type trait 函数有：
```c
// 判断类型的分类
constexpr bool is_integral<T>();
constexpr bool is_floating_point<T>();
constexpr bool is_pointer<T>();
constexpr bool is_function<T>();
constexpr bool is_array<T>();
constexpr bool is_struct<T>();
constexpr bool is_union<T>();
constexpr bool is_enum<T>();
constexpr bool is_void<T>();
//判断类型的属性
constexpr bool is_signed<T>();
constexpr bool is_unsigned<T>();
constexpr bool is_const<T>();
constexpr bool is_volatile<T>();
constexpr bool is_move_semantic<T>();
constexpr bool is_owned_pointer<T>();
constexpr bool is_owned_struct<T>();
constexpr size_t rank<T>();
constexpr size_t extent<T, size_t N>();
//判断类型的关系
constexpr bool is_same<T1, T2>();
constexpr bool is_convertible<From, To>();
```
针对其中一些作出说明和举例：
```c
constexpr bool is_move_semantic<T>(); //判断类型 T 是否是 move 语义的类型
// 我们认为具有 move 语义的类型包括：
//   1. owned指针类型
//   2. owned struct类型
//   3. 含有 move 语义字段的结构体类型
is_move_semantic<int *owned>() == true;
owned struct S {};
is_move_semantic<S>() == true;
struct S1 { int a; };
struct S2 { int *owned p; };
is_move_semantic<struct S1>() == false;
is_move_semantic<struct S2>() == true;

constexpr size_t rank<T>(); //可用于计算数组的维数，如
rank<int>() == 0;
rank<int[5]>() == 1;
rank<int[5][5]>() == 2;

constexpr size_t extent<T, size_t N>();//可用于计算数组第 N 维元素的个数，如
extent<int[3],0>() == 3;
extent<int[3],1>() == 0;
extent<int[3][4],0>() == 3;
extent<int[3][4],1>() == 4;
extent<int[3][4],2>() == 0;

constexpr bool is_same<T1, T2>();//判断类型 T1，T2 是否一样，忽略类型别名

constexpr bool is_convertible<From, To>();//判断类型 From 是否可以隐式转换为类型 To，如
is_convertible<int, float>() == true;
is_convertible<int, const int>() == true;
is_convertible<int, volatile int>() == true;
is_convertible<int, signed>() == true;
is_convertible<int, void>() == false;
is_convertible<int, int*>() == false;
is_convertible<int, void*>() == false;
is_convertible<struct S, struct G>() == false;
```

使用时就像普通泛型函数一样
```c
#include<stdio.h>
#include<bsc_type_traits.hbs>

int main() {
    printf("%d\n",is_integral<int>()); //1
    printf("%d\n",is_integral<float>()); //0
    return 0;
}
```

type trait 函数可以在泛型函数和泛型结构体的成员函数中使用
```c
#include<stdio.h>
#include<bsc_type_traits.hbs>

struct S<T> {};
void struct S<T>::foo(struct S<T>* this) {
    if (is_integral<T>()) {
        printf("integral\n");
    } else {
        printf("not integral\n");
    }
}

void bar<T>() {
    if (is_integral<T>()) {
        printf("integral\n");
    } else {
        printf("not integral\n");
    }
}

int main() {
    struct S<int> s1;
    struct S<float> s2;
    s1.foo(); //print "integral"
    s2.foo(); //print "not integral"
    bar<int>();  //print "integral"
    bar<float>(); //print "not integral"
    return 0;
}
```

type trait 函数也可用于静态断言中
```c
#include<bsc_type_traits.hbs>

int main() {
    _Static_assert(is_integral<int>() == true, "fail");
    _Static_assert(is_integral<float>() == false, "fail");
    return 0;
}
```

### constexpr if
#### 概述
以 if constexpr 开头的语句被称为 constexpr if 语句，允许用户使用 constexpr 表达式作为 if 语句的条件，保证条件是编译时计算的常量，使得编译器在编译时就能够做分支判断，并对 false 分支进行死代码消除，减少运行时开销。

constexpr if 语句与普通 if 语句的区别在于，cond 条件表达式之前使用 constexpr 关键字进行修饰，即：
```c
if constexpr (<cond>) {
    <then-statement>
} else {
    <else-statement>
}
```

我们以计算阶乘为例来认识 constexpr if，先写出一个不使用 constexpr if 的版本来计算阶乘：
```c
int factorial(int n) {
    return (n == 1) ? 1 : n * factorial(n - 1);
}

int main() {
    printf("%d", factorial(5));
    return 0;
}
```
由于 BSC 不支持泛型特化的功能，故想要实现阶乘只能使用普通函数，在运行期进行求值。使用 constexpr if，我们可以实现类似于泛型特化的功能，实现编译期计算阶乘结果。
```c
constexpr int factorial<int N>() {
    if constexpr (N == 1) {
        return 1;
    } else {
        return N * factorial<N - 1>();
    }
}

int main() {
    _Static_assert(factorial<5>() == 120, "fail");
    return 0;
}
```

#### 用法
constexpr if 语句中的 cond 表达式在使用时需要满足以下约束：
1. cond 表达式必须是可编译时求值的常量表达式；
2. cond 表达式的类型必须是可以隐式转换为 bool 的类型，包括 bool、整型和 char。
例如：
```c
int foo1() {
    return 5;
}

constexpr int foo2(int a) {
    return a;
}

int main() {
    int a = 1;
    if constexpr(5.0) { //error,类型不支持浮点类型
        a = 6;
    }
    if constexpr(a) {  //error,不是编译期计算的常量表达式
        a = 6;
    }
    if constexpr(foo1()) {  //error,不是编译期计算的常量表达式
        a = 6;
    }
    if constexpr(foo2(a)) {  //error,不是编译期计算的常量表达式
        a = 6;
    }
    return 0;
}
```

constexpr if 语句中，因为条件表达式是编译时计算的常量表达式，求值为 false 的分支会被定义为 “discarded statement”，会在编译期作为死代码被消除。
例如：
```c
if constexpr (<cond>) {  //如果<cond>的值为true
    <true-statement>
} else {
    <false-statement>  //那么else分支内的语句成为discarded statement，会在编译期作为死代码被消除
}
```

对于 discarded statement，有如下规则：
1. 在非泛型上下文内，discarded statement 仍然需要做完整的语法语义检查。
2. 在泛型上下文内，discarded statement 不会被实例化，也就不会进行实例化之后的语义检查。
例如：
```c
#include <stdio.h>
#include <bsc_type_traits.hbs>

void foo<T>(T a) {
    if constexpr (is_pointer<T>()) {
    //如果T不是指针，实例化的时候，下面这个block会被当作死代码，不会被实例化，也就不会进行实例化之后的语义检查
        printf("T is pointer\n");
        void* p = (void*) a;
    } else {
        printf("T is a generic case\n");
    }
}

int main() {
    int b = 5;
    foo<int>(5);
    foo<int*>(&b);
    return 0;
}
```

------

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

## 无栈协程

### 无栈协程简介

无栈协程与有栈协程调用栈由程序员显示分配的不同，协程的调用栈由运行时系统隐式管理的，协程本身不持有自己的调用栈，在切换协程时不需要保存和恢复整个调用栈，只保存协程执行状态。它是通过 `async/await` 关键字进行定义和调用。`async` 用来修饰异步函数，`await` 实现异步函数调用。

毕昇 C 的无栈协程目标是支持异步、高并发场景，例如 Web 服务器实现高并发网络通信、异步处理请求、 Web 应用程序的数据库连接池等。

### Future/PollResult标准库定义

#### Future/PollResult定义

**Future** 用于描述某个计算（或任务）尚未结束，用一个对象来代理这个未知的结果，这个计算（或任务）可以暂停和恢复。

Future 的执行是通过调用 poll 函数实现的。

**PollResult** 即 poll 函数返回值，用于描述计算（或任务）执行状态以及结果。

```c
struct PollResult<T> {
    _Bool isPending; //isCompleted
    T res;
};

T struct PollResult<T>::is_pending(struct PollResult<T>* this) { ... }
struct PollResult<T> struct PollResult<T>::pending() { ... }
_Bool struct PollResult<T>::is_completed(struct PollResult<T> *this, T *out) { ... }
struct PollResult<T> struct PollResult<T>::completed(T result) { ... }

trait Future<T> {
    struct PollResult<T> poll(This* this);
    void free(This* this);
};
```

#### Future/PollResult使用

协程的实现使用到 Future/PollResult 定义，其导入方式有系统默认导入和用户显式导入两种。

用户显式导入时需要引用头文件 `future.hbs`。文件安装在系统 /usr/include 默认搜索路径下（或者安装在指定目录）在编译时使用 -I 编译选项指定路径。

```c
#include  "future.hbs"
```

### 语法规则

1. 无栈协程只允许在毕昇 C 编译单元使用

2. 如果函数中使用了 `await` 关键字，那么这个函数必须用 `async` 修饰。`async` 函数内可以有 0,1...n 个 `await` 表达式

```c
async int TimeOut(int t) {
    return t;
}

async int getData1() {
    int t = await TimeOut(1000);
    return t;
}

async int getData2() {
    await getData1();
    await TimeOut(1000);
    await TimeOut(2000);
    return 0;
}
```

3. `async` 函数声明和实现可以分开

```c
#include "string.h"

async int ReadBuffer(char *str);

async int GetBufferSize() {
    char* Content;
    char ContentCopy[12] = "hello,word!";
    Content = ContentCopy;
    int size = await ReadBuffer(Content);
    return size;
}

async int ReadBuffer(char *str) {
    char *cstr = "hello,word!";
    if (strcmp(str, cstr) == 0)
      return sizeof(str);
    else return 0;
}
```

4. `async` 函数支持递归调用

```c
async int f(int n) {
    if (n == 0 || n == 1)
        return 1;
    int tmp = await f(n-1);
    return n*tmp;
}
```

5. `async` 关键字可以修饰成员函数

```c
async void int::g(int* this);

async int int::f() {
    int i = 1;
    await int::g(&i);
    await i.g();
    return 0;
}

async void int::g(int* this) {
    trait Future<int>* a = read(1);
    await a;
}
```

6. `async` 函数中可以出现多个不同或相同 `await` 表达式

```c
async void client1() {
    // client1 send message...
}

async void client2() {
    // client2 send message...
}

async int Server(int start) {
    // server receive message
    await client1();
    if (start < 20)
        await client2();
    return start;
}
```

7. `async` 函数不支持变量数组，即数组中含有变量

```c
async int f() {
    int *VarArray1[n]; // expected-error {{async function does not support VariableArrayType}}
    int VarArray2[3][2][n]; // expected-error {{async function does not support VariableArrayType}}
    int *VarArrayPtr[n][2][n][5]; // expected-error {{async function does not support VariableArrayType}}
    int Array[3]; // support
    int MultiArray[2][3][4][5]; // support
    return 0;
}
```

8. `await` 表达式不能出现在 if/while/for/do-while 等判断条件中

```c
async int read(int n) {
    // read data...
    return n;
}

async int getData() {
    int res = 0;
    if (await read(1)) { // expected-error {{await expression is not allowed to appear in condition statement of if statement}}
        res = await read(1);
    }

    if (res == 2) { // support
        res = await read(1);
    }
    return res;
}
```

9. `await` 表达式不能和“有副作用”的表达式（例如函数）并存

```c
async int read(int n) {
    // read data...
    return n;
}

int test(int a, int b) {
    return 42;
}

async int f() {
    test(await read(2), await read(2)); // expected-error {{await expression is not allowed to appear in function parameters}}
    test(t(), await read(2)); // expected-error {{await expression is not allowed to appear in function parameters}}
    test(3, await read(2)); // support
    return 0;
}
```

10. `await` 表达式不能出现在复合表达式中，例如：表达式中含有 +、-、*、/、%、&、|、>>、<< 等

```c
async int read(int n) {
    // read data...
    return n;
}

async int f() {
    int x = await read(2) + 3; // expected-error {{await expression is not allowed to appear in binary operator expression}}
    int y = await read(2); // support
    return 0;
}
```

11. `await` 表达式支持 `await` 多层嵌套调用

```c
async int test0(int n) {
    // read data...
    return n;
}

async int test1(int n) {
    // ...
    return n;
}

async int test2(int n) {
    // ...
    return n;
}

async int test3(int n1, int n2) {
    // ...
    return 0;
}

async int f() {
    int start = 0;
    int result1 = await test1(await test1(start));
    int result2 = await test1(await test2(start));
    int result3 = await test3(2, await test1(await test2(start)));
    return result1 + result2 + result3;
}
```

12. `await` 表达式可以出现在 return 语句中

```c
async int read(int n) {
    // read data...
    return n;
}

async int f() {
    return await read(2);
}
```

### 代码样例

```c
# include "future.hbs"
const int MAX = 3;

async int read(int a) {
    return 0;
}

async int f() {
    int *nptr = NULL;
    int  var[] = {10, 100, 200};
    int  i, *ptr;

    ptr = &var[MAX-1];
    for ( i = MAX; i > 0; i--)
    {
    ptr--;
    }
    int result = await read(1);
    result += *ptr;
    return result;
}

async void g(int start) {
    int result = start;
    for (int i = 0; i< start; i++) {
        int a = await f();
    }
}

int main() {
    trait Future<int>* this1 = f();
    this1->poll();
    this1->free();
    // 当 async 函数的返回类型是 void 时，我们需要用 struct Void 类型（会自动创建）来对 trait Future 实例化
    trait Future<struct Void>* this2 = g(5);
    this2->poll();
    this2->free();
    return 0;
}
```



------

## 源源变换

### 概述

对于一个毕昇 C 源代码文件，通常情况下只需要使用毕昇 C 编译器直接将其编译为对应的二进制代码并运行。
毕昇 C 编译器也提供了将编写的毕昇 C 源代码转换为等价的标准 C 代码的能力，该能力由编译选项`-rewrite-bsc`提供。
在编译时加上该编译选项后，编译会生成包含等价 C 代码的文件，该文件可再使用 gcc、clang 等编译器编译为目标代码。
一般而言，源源变换适用于如下场景：

1. 希望查看毕昇 C 代码对应的等价的 C 代码；
2. 基于现有的使用 C 语言开发的项目，使用毕昇 C 进行增量开发，但又希望依然使用原先的编译工具链进行编译；
3. 运行程序的目标平台不是毕昇 C 编译器所支持的标准后端时，也需要先将毕昇 C 代码转换为 C 代码，再使用支持目标平台的编译器编译 C 代码。

### 使用方式

毕昇 C 编译器的`-rewrite-bsc`编译选项的使用方式和 clang 原生的`-rewrite-objc`编译选项的用法相似。在编译想要被转换的毕昇 C 源码时加上`-rewrite-bsc`即可使用源源变换模式进行编译。

例如：如果你想要对`test.cbs`进行源源变换，那么在编译的时候使用如下命令即可在当前目录下得到一个名为`test.c`的 C 文件，文件的内容即为变换后的 C 源码。

```shell
clang -rewrite-bsc test.cbs
```

如果要变换的文件需要引用某些头文件，那么在源源变换时同样需要使用`-I`选项指定头文件搜索路径。例如如果`test.cbs`依赖于毕昇 C 标准库（后面的章节会具体说明），那么相应的编译命令为：

```shell
clang -rewrite-bsc test.cbs -I/path/to/libcbs/include
```

对于一个名为`xx.cbs`的毕昇 C 文件，源源变换生成的 C 文件的默认文件名为`xx.c`。
源源变换也支持使用`-o`指定输出的 C 文件名，如下示例就将源源变换生成的目标文件命名为`a.c`：

```shell
clang -rewrite-bsc test.cbs -o a.c
```

毕昇 C 编译器也支持同时对多个文件进行变换，不过多个文件同时变换时不支持通过`-o`指定输出的目录或名称，示例如下：

```shell
clang -rewrite-bsc boo.cbs foo.cbs
```

对于源源变换，还有以下几点需要说明和注意：

1. 使用源源变换模式进行编译时，编译器同样会像普通编译模式下那样先对要变换的文件进行词法、语法、语义的检查，对文件中的错误会编译报错，并且不会进行源源变换生成 C 文件。只有能正确通过编译的文件才会在源源变换模式下生成对应的 C 文件。
2. 对于非 cbs 后缀文件使用 -rewrite-bsc 选项，该选项会被忽略（除非添加`-x bsc`将文件按照毕昇 C 进行处理），并报如下 warning 。
    ```shell
    warning: ignoring '-rewrite-bsc' option because rewriting input type 'c' is not supported [-Woption-ignored]
    ```
3. 只需要对毕昇 C 源文件（cbs 文件）进行源源变换，不需要对毕昇 C 头文件（hbs 文件）进行变换。源源变换生成的 C 文件在后续编译时不再依赖任何 hbs 文件，原先 cbs 文件中依赖的 hbs 文件中的内容已经包含在了生成的 C 文件中。因此，可以直接编译生成的 C 文件并生成二进制代码。
4. 源源变换严格区分标准 C 头文件和 hbs 文件，但为方便用户使用，并不要求所有的 hbs 文件后缀名都为 .hbs。具体的区分规则为：
   - 以 .hbs 为后缀的是 hbs 文件
   - 以 .h 为后缀的头文件，且文件的第一行为`#pragma bsc`，则该文件也被视为 hbs 文件
   - 以 .h 为后缀的头文件，且该文件直接或间接包含了 hbs 文件，则该文件也被视为 hbs 文件

### 目标文件结构

对于源源变换，还需要对生成的 C 文件的结构进行说明。C 文件中的内容按照如下顺序排列：

1. 头文件包含。这里包含了所有需要引用的标准 C 的头文件，包括直接被 cbs 文件引用的头文件以及被 hbs 文件间接引用的头文件。由于 hbs 文件不再被目标文件依赖，因此目标代码中不会再包含对毕昇 C 头文件的引用。
2. 宏定义。这里包含了所有的 cbs 文件中定义的宏以及 cbs 文件引用的 hbs 文件中定义的宏。
3. 类型别名和枚举定义。这里包含了所有的类型别名定义以及枚举类型定义。如果一个类型别名是对 trait 的类型别名，那么它不会出现在目标文件中。如果一个类型别名是对匿名类型的类型别名，那么在目标文件中会为匿名类型加上 typedef 的类型别名作为类型名。如：
    ```c
    // 毕昇 C 文件中：
    typedef struct {
        char *buf;
        int len;
    } MSG;
    
    // 生成的 C 文件中：
    typedef struct _TD_MSG MSG;
    
    struct _TD_MSG {
        char *buf;
        int len;
    };
    ```
4. 类型定义。这里包含了所有 cbs 文件中以及 cbs 文件引用的 hbs 文件中的类型定义。由于毕昇 C 中有泛型类型，因此需要考虑到目标文件中类型定义的顺序问题。毕昇 C 编译器的源源变换采取的是一种类型拓扑排序的方案，保证在定义一个类型时，已经在前面包含了所有它依赖的类型的完整定义。如下用例展示了一个使用毕昇 C标准库构造出的`LinkedList<Vec<int>>`类型以及对应的目标文件中的类型定义顺序：
    ```c
    // 毕昇 C 文件中：
    #include "list.hbs"
    #include "vec.hbs"
    int main() {
        Vec<int> v1 = Vec<int>::new();
        Vec<int> v2 = Vec<int>::new();
        Vec<int> v3 = Vec<int>::new();
        for (int i = 0; i < 10; i = i + 1) {
            v1.push(i);
        }
        for (int i = 0; i < 10; i = i + 1) {
            v2.push(i);
        }
        for (int i = 0; i < 10; i = i + 1) {
            v3.push(i);
        }
        LinkedList<Vec<int>> l = LinkedList<Vec<int>>::new();
        l.push_back(v1);
        l.push_back(v2);
        l.push_back(v3);
        Vec<int> ele = l.pop_back();
        return 0;
    }
    
    // 编译命令：clang -rewrite-bsc main.cbs -I/path/to/libcbs/include
    // 生成的 C 文件中的类型定义（省略其他代码）：
    struct RawVec_int {
        int *ptr;
        size_t cap;
    };
    struct LinkedList_struct_Vec_int {
        struct _BSC_ListNode_struct_Vec_int *head;
        struct _BSC_ListNode_struct_Vec_int *tail;
        size_t len;
    };
    struct Vec_int {
        struct RawVec_int buf;
        size_t len;
    };
    struct _BSC_ListNode_struct_Vec_int {
        struct _BSC_ListNode_struct_Vec_int *next;
        struct _BSC_ListNode_struct_Vec_int *prev;
        struct Vec_int element;
    };
    ```
5. 泛型函数、泛型结构体的扩展成员函数的声明。
6. 非泛型函数的定义。
7. 泛型函数、泛型结构体扩展的成员函数的定义。

------

## 内存安全

毕昇 C 内存管理的目标是将常见的时间类内存安全问题，如悬挂引用/内存泄漏/重复释放堆内存/解引用空指针等常见的内存安全问题在编译阶段暴露出来。

为此，毕昇 C 引入了所有权和借用两个新的概念。

### 所有权

#### 0. 前言

C 语言作为一种系统级编程语言，
提供了对指针的高度灵活的直接操作以及利用内存管理函数使开发者手动精细控制和管理内存的能力，
因而被广泛地应用于各种需要直接与硬件或内存等系统资源交互的领域和场景。
然而，这种内存管理模式存在容易导致内存泄漏、释放后使用、空指针解引用、缓冲区溢出和越界读写等内存安全问题。
内存安全问题不仅会造成资源的浪费，也可能导致程序行为错误，甚至导致程序崩溃，对程序的稳定性造成威胁。
内存安全问题可以划分为时间内存安全和空间内存安全两大类，其中时间内存安全包含内存泄漏、释放后使用、空指针解引用等，空间内存安全包括缓冲区溢出、越界读写等。
BiShengC 语言的内存管理为解决程序的时间内存安全问题，利用了**所有权特性**在编译期对潜在的内存安全问题进行检查，识别潜在的时间内存安全错误。


#### 1. 特性简介

BiShengC 语言的所有权特性被用于确保程序中的指针及其指向内存空间能被正确地管理。
在 BiShengC 语言中，使用`owned`关键字用来修饰一个指针类型，表明该指针拥有其指向的内存的所有权。
拥有所有权的指针必须确保其指向的内存在指针作用域结束前被显式释放，否则存在潜在的内存泄漏错误；
此外，一块堆内存只能同时被一个`owned`指针所拥有，`owned`指针为移动语义，这样避免了释放后使用等内存安全问题的发生。
以下是一段使用了所有权特性的 BiShengC 语言代码，用于了解所有权特性：

```c
#include "bishengc_safety.hbs" // BiShengC 语言提供的头文件，用于安全地进行内存分配及释放

int * owned takes_and_gives_back(int * owned p) {
    return p;
}

safe void test(void) {
    int * owned p = safe_malloc(2); // 通过提供的 safe_malloc 申请一块大小为 sizeof(int) 的堆内存，并将值设置为2
    int * owned q = p; // 将 p 指向的堆内存转移给 q，后续不可再使用 p 访问这块内存，否则编译报错
    unsafe {
    q = takes_and_gives_back(q); // 通过函数参数转移走 q 的所有权，但通过函数返回值归还所有权
        safe_free((void * owned)q); // 在 q 的作用域结束前调用 safe_free 安全释放堆内存，此处不释放则会报内存泄漏错误
    }
    return;
}
```

注：在安全区，`owned`指针指向的内存一定为通过`safe_malloc`函数申请出的堆内存，`owned`指针不可能指向栈内存。


#### 2. 语法及语义规则

为实现所有权特性，BiShengC 语言引入了`owned`关键字用于修饰指针类型的变量。
该关键字与`const`、`restrict`以及`volatile`均属于类型修饰符，其语法如下：

```
type-qualifier:
  const | restrict | volatile | ownership-qualifier

ownership-qualifier:
  owned
```

具体而言，所有权特性的语法及部分语义规则有以下几点：

1. `owned`关键字仅允许在 BiShengC 语言编译单元内使用；

2. `owned`关键字仅被允许用于修饰指针类型，不允许修饰非指针类型，修饰多级指针时，每级指针的类型修饰可以不一样，规则与`const`类似；

    ```c
    safe void test(void) {
        int * owned p = safe_malloc(2); // 允许
        // int owned a = 2; // 不允许
        double * owned q = safe_malloc(1.1); // 允许
        // double owned b = 1.1; // 不允许
        int * owned * owned pp = safe_malloc(p); // 允许
        unsafe {
            double * d = (double *)malloc(sizeof(double));
            double * * owned qq = safe_malloc(d); // 允许
            safe_free((void* owned* owned)pp);
            safe_free((void* owned)p);
            safe_free((void** owned)qq);
        }
    }
    ```

3. 允许使用`owned`关键字修饰结构体指针及结构体的指针成员；

    ```c
    struct S {
        int m;
        int n;
    };

    struct R {
        int * owned p; // 允许
        double * owned q; // 允许
    }

    safe void test(void) {
        struct S s = { .m = 1, .n = 2 };
        struct S * owned sp = safe_malloc(s); // 允许
        // struct S owned so = { .m = 1, .n = 2 }; // 不允许
        struct R r = { .p = safe_malloc(1), .q = safe_malloc(2.5) }; // 允许
        struct R * owned rp = safe_malloc(r); // 允许
        // struct R owned ro = { .p = safe_malloc(2), .q = safe_malloc(1.5) }; // 不允许
    }
    ```

4. `owned`不允许修饰`union`类型和`union`的成员，且`union`的每个成员均不能拥有`owned`修饰的成员；

    ```c
    struct S {
        int a;
        int b;
    };

    struct T {
        int * owned p;
        struct S S;
    };

    union A {
        int a;
        // int * owned p; // 不允许
        struct S s;
        // struct S * owned sp; // 不允许
        // struct T t; // 不允许
        // struct T * owned tp; // 不允许
        struct T * trp; // 允许，不跟踪裸指针指向的变量的 owned 成员
    };
    ```

5. `owned`修饰的类型或拥有`owned`修饰的成员的类型不可以作为数组的成员；

    ```c
    struct A {
        int * owned p;
    };

    safe void test(void) {
        // int * owned arr_i[2] = ...; // 不允许
        // struct A arr_a[2] = ...; // 不允许，struct A 拥有 owned 修饰的成员
    }
    ```

6. `owned`修饰的指针不支持算术运算符（指针偏移操作），但支持比较运算符；

    ```c
    safe void test(void) {
        int * owned p = safe_malloc(2);
        int * owned q = safe_malloc(3);
        // p++; // 不允许
        // p[3] = ...; // 不允许
        if (p == q) { // 允许
            // ...
        }
        unsafe {
            safe_free((void* owned)p);
            safe_free((void* owned)q);
        }
    }
    ```

7. `owned`修饰的类型与非`owned`修饰的类型之间不允许隐式类型转换；

    ```c
    safe void test(void) {
        unsafe {
            int *b = (int*)malloc(sizeof(int));
            // int * owned p = b; // 不允许
        }
        int * owned q = safe_malloc(3);
        // int *c = q; // 不允许
    }
    ```

8. 基本类型一致时，允许`owned`指针类型与非`owned`指针类型之间的显式强制类型转换，且这种转换只能在非安全区进行；
基本类型不一致时，只允许`void * owned`类型与`T * owned`类型之间的相互强制转换；

    ```c
    void test() {
        int *b = (int *)malloc(sizeof(int));
        int * owned p = (int * owned) b; // 允许，b 和 p 的基本类型均为 int
        double * d = (double *)malloc(sizeof(double));
        // int * owned q = (int * owned)d; // 不允许，基本类型不一致
        double * owned dd = safe_malloc(1.5);
        void * owned v = (void * owned)dd; // 允许
        safe_free((void* owned)p);
        safe_free((void* owned)d);
        safe_free((void* owned)v);
    }
    ```

9. `owned`允许修饰指向`trait`的指针，假设有一个具体类型`S`，它实现了`trait T`，则：

    - `S * owned`类型可以隐式转换为`trait T * owned`类型；
    - `trait T * owned`类型允许被显式转换为`void * owned`类型。

10. 通过函数指针调用函数的时候，规则与一般的函数调用一样，会在函数调用时检查形参类型与实参类型是否匹配及返回类型与返回值类型是否匹配；

    ```c
    int add(int *a, int *b);
    typedef int (*FTP)(int *, int *);
    typedef int (*FTOP)(int * owned, int *);

    void test() {
        FTP ftp = add;
        int * owned ap = safe_malloc(1);
        int * owned bp = safe_malloc(2);
        // ftp(ap, bp); // 不允许，类型不匹配
        // FTOP ftop = add; // 不允许，类型不匹配
        safe_free((void* owned)ap);
        safe_free((void* owned)bp);
    }
    ```

11. `owned`可以修饰 trait 类型，即`trait T* owned`，也表示该变量拥有其内部存储的数据的所有权。
    该类型可以作为类型声明、函数的入参类型及函数的返回值类型。但当前不支持`trait T* owned`与`trait T*`之间的类型转换。

    ```c
    trait T {
        safe void release(This* owned this);
    };
    
    struct IPv4 {
        char* buf1;
    };
    
    struct IPv6 {
        char* buf1;
        char* buf2;
    };
    
    safe void struct IPv4::release(struct IPv4* owned this) {
        free(this->buf1);
        safe_free((void* owned)this);
    }
    
    safe void struct IPv6::release(struct IPv6* owned this) {
        free(this->buf1);
        free(this->buf2);
        safe_free((void* owned)this);
    }
    
    impl trait T for IPv4;
    impl trait T for IPv6;
    
    void cleanup(trait T* owned t) {
        t->release();
    }
    ```

#### 3. 所有权状态转移规则

在对所有权特性的语法和部分语义有了解后，本节将对所有权的状态转移规则进行详细阐述。
为更好地理解所有权特性对内存安全带来的保障，首先需要明白程序执行时的堆栈内存模型。

总体而言，程序执行时内存可分为栈区和堆区两个部分，这两部分内存一起为程序在运行时提供内存空间。
栈区即为调用栈，保存的是程序执行所需要维护的所有信息。
每当一次函数调用发生时，就会创建一个对应的栈帧，函数调用的上下文、函数的入参以及函数体内的局部变量就存在这个栈帧中。
栈帧的基址一般由 rbp 寄存器指向，而栈顶由 rsp 寄存器指向，两个寄存器共同标识了一个函数的栈帧。
当一次函数调用结束时，相应的栈帧就会在函数返回前被销毁，相应的内存空间也就得到释放。
这个过程是通过调整 rbp 寄存器的值为调用者的栈帧基址、rsp 的值为调用者的栈顶地址完成的，这也是为什么栈区的变量不需要显式释放。
对于堆区，则存放的是那些在运行时动态分配内存的数据。
一个典型的例子是对于`int *p = malloc(sizeof(int))`这种操作，需要由操作系统在堆区找到一块适合大小的内存空间用于分配，然后将这块内存的地址存在 p 中，指针 p 是程序的一个栈上变量。
虽然堆区的内存分配更为灵活，但却缺乏组织，不正确的内存管理很容易导致堆区的内存泄漏。
例如，当一次函数调用完成后，其局部变量 p 被销毁，而其指向的堆内存未被显式地调用`free(p)`进行回收，则这块堆内存将永远无法被回收，产生了内存安全错误。

<div align="center">
    <img src=./BiShengCLanguageUserManualImages/memory-leak-example.png width=60% />
</div>

利用 BiShengC 语言提供的所有权特性，可以用`owned`关键字对那些需要管理的指针进行标识，这样就可以在程序编译时检查出潜在的错误，避免在运行时出现错误。
以下是 BiShengC 语言所有权的核心规则：

1. 在 BiShengC 语言中每一个值都被一个`owned`指针变量所拥有，该`owned`指针变量即为值的所有者；
2. 一个值同时只能被一个`owned`指针变量所拥有，即一个值只能拥有一个所有者；
3. 当`owned`指针变量离开作用域范围时，需要释放其拥有的值所在的堆内存。

基于以上核心规则，接下来结合详细的代码示例进行具体介绍。

##### 3.1 转移所有权

**1. 一个拥有所有权的变量`s1`被赋值给另一个变量`s2`是一个移动语义，该操作后变量`s1`失去了对值的所有权，原先的变量`s1`无法再使用。**
以下是一段代码示例及说明：

```c
safe void test(void) {
    int * owned p = safe_malloc(10);
    int * owned q = p;
    int * owned m = p; // error
    unsafe {
        safe_free((void* owned)q);
        safe_free((void* owned)m);
    }
}
```

在这个例子中，`p`拥有一块堆内存的所有权，这块内存大小为`sizeof(int)`，存储的值为10。
在声明`q`时，将`p`的所有权转移给了`q`，`p`不再拥有对这块堆内存的所有权。
则在声明`m`时，便不可再将`p`的所有权转移给`m`，编译器会在此处报错。
因此，利用所有权特性，可以保证一个值只能拥有一个所有者。
（那么如果没有这条规则会出现什么后果呢？三个指针会同时指向一块内存，在作用域结束时对这块内存释放三次，出现重复释放的错误）

**2. 一个拥有所有权的变量`s1`作为整体被赋值给另一个变量`s2`时，如果`s1`内部还有其他拥有所有权的指针，则会全部都转移给`s2`。**
以下是一段代码示例及说明：

```c
struct S {
    int *p;
    int * owned q;
};

void test(void) {
    struct S s = {
            .p = (int *)malloc(sizeof(int)),
            .q = safe_malloc(1)
        };
    struct S * owned s1 = safe_malloc(s);
    struct S * owned s2 = s1;
    int * owned p = s1->q; // error
    safe_free((void* owned)s2->q);
    safe_free((void* owned)s2);
    safe_free((void* owned)p);
}
```

在这个例子中，将`s1`指向堆内存的所有权转移给了`s2`，但同时`s1`内部还有一个拥有所有权的指针`s1->q`，因此也会一并将他的所有权转移给`s2->q`，后续再使用`s1->q`时便会报错。

**3. 一个拥有所有权的变量`s1`作为整体被赋值给另一个变量`s2`时，如果`s1`内部还有其他拥有所有权的指针，则必须保证内部其他`owned`指针均拥有所有权，才能将`s1`赋值给`s2`。**
以下是一段代码示例及说明：

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void test(void) {
    struct S s = {
            .p = safe_malloc(2),
            .q = safe_malloc(3)
        };
    struct S * owned s1 = safe_malloc(s);
    int * owned p = s1->p;
    struct S * owned s2 = s1; // error
}
```

在这个例子中，我们先将`s1->p`的所有权转移走，然后试图整体转移`s1`的所有权给`s2`，但此时`s1->p`已经不再持有对任何一块堆内存的所有权，因此这个操作是不合法的。

**4. 一个拥有所有权的变量`s1`在失去其所有权后，可以通过赋值的方式使其再次拥有指向某块堆内存的所有权，这样就可以再次使用`s1`。**
以下是一段代码示例及说明：

```c
safe void test(void) {
    int * owned p = safe_malloc(10);
    int * owned q = p;
    p = safe_malloc(4);
    int * owned m = p;
}
```

在这个例子中，`p`的所有权转移给`q`后，再次调用了`safe_malloc`函数为其重新赋予了一块堆内存的所有权，因此后续仍可将`p`的所有权转移给`m`。

**5. 不允许将所有权转移给一个已经拥有所有权的变量。**
以下是一段代码示例及说明：

```c
safe void test(void) {
    int * owned p = safe_malloc(12);
    int * owned q = safe_malloc(67);
    q = p; // error
}
```

在这个例子中，试图将`p`的所有权转移给`q`，但`q`此时已经拥有所有权，再试图转移的话会使`q`原先指向的堆内存泄漏，因此无法进行转移，会在编译时报错。

**6. 如果一个变量`s1`拥有所有权，而其内部的`owned`指针变量的所有权已被转移，如果想再次赋予内部变量所有权，需要保证内部变量的所有父`owned`指针变量均拥有所有权。**
以下是一段代码示例及说明：

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void test(void) {
    struct S s = {
            .p = safe_malloc(2),
            .q = safe_malloc(3)
        };
    struct S * owned s1 = safe_malloc(s);
    struct S * owned s2 = s1;
    s1->p = safe_malloc(5); // error
}
```

在这个例子中，`s1`、`s1->p`以及`s1->q`的所有权均被转移给了`s2`，后续再试图赋予`s1->p`所有权时，其父`owned`变量指针`s1`尚未拥有所有权，因此此次操作是非法的，会在编译时报错。

##### 3.2 作用域结束时的内存释放

**1. 对于所有的`owned`指针变量，会在其词法作用域结束时检查其是否依然拥有堆内存的所有权，如果依然拥有，则存在内存泄漏错误。**
以下是一段代码示例及说明：

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void test(void) {
    int * owned p = safe_malloc(2);
    struct S s = {
            .p = safe_malloc(2),
            .q = safe_malloc(3)
        };
    struct S * owned s1 = safe_malloc(s);
    struct S * owned s2 = s1;
} // error
```

在这个例子中，当作用域结束时，编译器会发现`p`、`s2`、`s2->p`以及`s2->q`依然拥有其指向的堆内存的所有权，即这些堆内存都没有被释放，因此会编译失败并报告内存泄漏。

##### 3.3 强制类型转换

**1. 允许将`T * owned`类型的变量通过强制类型转换转为`void * owned`类型，但转换成功的条件为变量依然拥有所有权且其内部的`owned`指针变量均已不拥有所有权。**
以下是一段代码示例及说明：

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void test(void) {
    struct S s = {
            .p = safe_malloc(2),
            .q = safe_malloc(3)
        };
    struct S * owned s1 = safe_malloc(s);
    int * owned p = s1->p;
    unsafe {
        safe_free((void * owned)s1); // error
    }
}
```

在这个例子中，试图将`s1`强制类型转换为`void * owned`类型，但`s1->q`依然拥有所有权，因此转换失败。

**2. BiShengC 语言提供了`safe_free`函数用于释放`owned`指针变量指向的堆内存，该函数的入参要求为`void * owned`类型。**
以下是一段代码示例及说明：

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void test(void) {
    struct S s = {
            .p = safe_malloc(2),
            .q = safe_malloc(3)
        };
    struct S * owned s1 = safe_malloc(s);
    int * owned p = s1->p;
    unsafe {
        safe_free((void * owned)p);
        safe_free((void * owned)s1->q);
        safe_free((void * owned)s1);
    }
}
```

在这个例子中，分别释放了`p`、`s1->q`以及`s1`指向的堆内存，不存在任何内存泄漏问题，使用`safe_free`完成了正确的堆内存释放。

##### 3.4 函数调用与返回

**1. 函数调用和返回时，如果函数的形参或函数的返回值为`owned`指针类型，则要求传入的实参以及返回值必须拥有堆内存的所有权。**
以下是一段代码示例及说明：

```c
struct S {
    int * owned p;
    int * owned q;
};

struct S * owned foo(struct S s) {
    struct S * owned ret = safe_malloc(s);
    return ret;
}

safe void test(void) {
    struct S s = {
            .p = safe_malloc(2),
            .q = safe_malloc(3)
        };
    int * owned p = s.p;
    struct S * owned s1 = foo(s); // error
}
```

在这个例子中，传入`foo`函数的结构体变量`s`内部有两个`owned`指针变量，而`s.p`已经被转移走，因此这次函数调用是非法的，会编译报错。

#### 4. 源源变换

BiShengC 语言的 clang 编译器支持源源变换功能，即将`.cbs`文件转换为等价的`.c`文件。
所有权特性仅引入了`owned`关键字表示所有权，在源源变换时只会去掉所有的`owned`关键字，然后生成相应的`.c`代码。
关于源源变换的详细细节，请参考手册的源源变换章节。


### 借用
借用作为毕昇C内存安全特性的重要组成部分，是对所有权的一个补充。前面小节描述了所有权特性(ownership)，对某个资源拥有所有权的主体，有责任释放这个资源。这个小节，将介绍对资源的借用(borrow)。

#### 1. 特性简介
如果我们只有 ownership 类型，由于函数调用、赋值等操作都会转移所有权，那么代码能力会非常受限。在编程时，我们常常需要表达“对某个资源进行借用”的概念，区别于“拥有某个资源”。正如现实生活中，如果一个人拥有某样东西，你可以从他那里借来，当使用完毕后，也必须要物归原主。

#### 1.1 借用的定义及借用操作符
毕昇 C 的**借用是一个指针类型，指向了被借用对象存储的内存地址**。为表达借用的概念：
1. 引入新关键字`borrow`，用`borrow`来修饰指针类型 T*，表示 T 的借用类型
2. 引入借用操作符 `&mut` 和 `&const`，其中，`&mut e`表示获取对表达式 e 的可变借用，`&const e`表示获取对表达式 e 的只读借用。此处要求表达式 e 是 lvalue，与标准 C 中的取地址操作符`&`类似, 借用操作符实际上获取的是表达式 e 的地址

例如，我们可以创建指向局部变量 local 的可变借用 p1 和不可变借用 p2，并使用它们：
```C
void use_immut(const int *borrow p);
void use_mut(int *borrow p);

void test() {
    int local = 5;
    int *borrow p1 = &mut local;         //p1是可变借用指针，借用了local
    use_mut(p1);
    const int *borrow p2 = &const local; //p2是不可变借用指针，借用了local
    use_immut(p2);
}
```
另外，表达式 e 如果是指针的解引用表达式，`&mut *p`和`&const *p`分别可以看作对地址 p 中存放的值，也就是`*p`，取可变借用和不可变借用，这一操作不为`*p`产生临时变量。其中，p可以是裸指针、owned指针和其它借用指针。例如：
```C
void test() {
    int *x1 = malloc(sizeof(int));
    *x1 = 42;
    int *borrow p1 = &mut *x1;    //p1借用了*x1

    int* owned x2 = safe_malloc<int>();
    int *borrow p2 = &mut *x2;    //p2借用了*x2

    int local = 5;
    int *borrow x3 = &mut local;
    int *borrow p3 = &mut *x3;    //p3借用了*x3
}
```
#### 1.2 借用的作用
假设我们有这样的一个需求：创建一个文件，并且调用一些操作函数对文件进行读写操作。如果没有借用的概念，调用文件操作函数会导致文件指针所有权的转移，为了使文件指针在函数调用之后仍然可以被使用，我们需要再将所有权返回给调用方：
```C
MyFile* owned create_file();
void safe_free(MyFile* owned p);

MyFile* owned insert_str(MyFile* owned p, char *str) {  //字符串插入函数
    // some operation to insert a string to file
    return p;  //通过返回值，将所有权转移给调用方
}

MyFile* owned other_operation(MyFile* owned p) {  //对文件的其他操作函数
    // some operation
    return p;  //通过返回值，将所有权转移给调用方
}

int main(void) {
    MyFile* owned p = create_file();
    p = insert_str(p, str); // p的所有权先被移动到insert_str中，再通过返回值转移到调用方
    p = other_operation(p);
    safe_free(p);
    return 0;
}
```
这种写法会造成文件指针所有权的频繁转移，在代码逻辑较为复杂的时候很容易出错，而且如果所有权被转移走了但是没有归还，后续将无法再使用该文件指针。有了借用，将对文件指针的借用作为参数传递给操作函数，函数返回之后文件指针仍可以用于后续其他操作，不再需要像上面那个例子一样，先通过函数参数传入所有权，然后再通过函数返回来传出所有权，代码更加简洁：
```C
MyFile* owned create_file();
void safe_free(MyFile* owned p);

void insert_str(MyFile* borrow p, char *str) {  //字符串插入函数，对文件指针的借用作为入参
    // some operation to insert a string to file
}

void other_operation(MyFile* borrow p) {  //其他文件操作函数，对文件指针的借用作为入参
    // some operation
}

int main(void) {
    MyFile* owned p = create_file();
    insert_str(&mut *p, str); //不取得文件指针p的所有权，而是借用*p，后续p可以继续被使用
    other_operation(&mut *p);
    safe_free(p);
    return 0;
}
```

#### 2.借用变量和被借用对象的生命周期
##### 2.1 生命周期及其作用
我们可以对不同种类的对象取借用：owned变量、非owned类型的局部变量、全局变量、临时匿名变量、参数等，甚至是某个复合变量的一部分。为正确表示借用变量和不同种类被借用对象的有效作用域，我们引入生命周期的概念。

生命周期检查的主要作用是避免悬垂指针，它会导致程序使用本不该使用的数据，以下 C 代码就是一个使用了悬垂指针的典型例子：

```C
void test() {
    int *p;
    {
        int local = 5;
        p = &local;
    }
    use(p);
}

```
这段 C 代码有两点值得注意：
1. int *p 的声明方式存在使用 NULL 的风险；
2. `p`指向了内部 block 中的`local` 变量，但是`local`会在 block 结束的时候被释放，因此回到外部 block 后，`p`会指向一个无效的地址，是一个悬垂指针，它指向了提前被释放的变量`local`，可以预料到，`use(p)` 会导致该段程序运行时出现未定义行为（undefined behavior）。当代码逻辑较为复杂时，这类异常行为很难被发现。

对于第一点，毕昇 C 规定：和裸指针不同，表示借用的 borrow 指针必须被初始化，表示对某一个具体对象的借用；

对于第二点，毕昇 C 规定：**任何一个对资源的借用，都不能比资源的所有者的生命周期长**。也就是说：借用变量的生命周期，不能比被借用对象的生命周期长。

接下来我们使用毕昇 C 的借用特性改写上面的 C 代码，通过检查借用变量和被借用对象的生命周期，在编译期就可以识别出潜在的内存安全风险：
```C
void test() {
    int local = 5;
    int *borrow p = &mut local; //借用指针变量 p 必须被初始化，否则会报错
    {
        int local1 = 5;
        p = &mut local1; //对 p 进行再赋值之后，p 不再借用 local，而是借用 local1
    }
    use(p); // error，local1 的生命周期不够长
}
```

##### 2.2 借用变量和被借用对象
每个借用变量（也就是 borrow 指针变量）都会有一个或多个被借用对象，例如：
```C
int g = 5;
void test(int a, int *owned b, int *c, struct S d) {
    // 被借用对象是普通局部变量
    int local = 5;
    int *borrow p1 = &mut local;  //p1的被借用对象是local
    int *borrow p2 = &mut *p1;    //p2的被借用对象是*p1
    int *borrow p3 = p1;          //p3的被借用对象是*p1

    // 被借用对象是owned变量
    int *owned x1 = safe_malloc<int>(2);
    int *borrow p4 = &mut *x1;    //p4的被借用对象是*x1

    // 被借用对象是裸指针变量
    int *x2 = malloc(sizeof(int));
    int *borrow p5 = &mut *x2;    //p5的被借用对象是*x2

    // 被借用对象是结构体的某个字段
    struct S s = { .a = 5 };
    int *borrow p6 = &mut s.a;    //p6的被借用对象是s.a

    // 被借用对象是函数的返回值，与被调用函数的借用类型入参的 “被借用对象” 一样
    int local1 = 10, local2 = 20;
    int *borrow p7 = call(&mut local1, &mut local2); //被调用函数call有两个借用类型入参，因此p7的被借用对象是local1和local2

    // 被借用对象是全局变量
    int *borrow p8 = &const g;    //p8的被借用对象是g

    // 被借用对象是函数入参
    int *borrow p9 = &mut a;      //p9的被借用对象是a
    int *borrow p10 = &mut *b;    //p10的被借用对象是*b
    int *borrow p11 = &mut *c;    //p11的被借用对象是*c
    int *borrow p12 = &mut d.a;   //p12的被借用对象是d.a
}
```

##### 2.3 借用变量的 Non-Lexical Lifetime
一个变量的生命周期从它的声明开始，到当前整个语句块结束，这个设计被称为Lexical Lifetime，因为变量的生命周期是严格和词法中的作用域范围绑定的。这个策略实现起来非常简单，但它可能过于保守了，某些情况下借用变量的作用范围被过度拉长了，以至于某些实质上是安全的代码也被阻止了，这在一定程度上限制了程序员能编写出的代码。因此，毕昇 C 为借用变量引入 Non-Lexical Lifetime（简写为NLL），用更精细的手段计算借用变量真正起作用的范围，**借用变量的 NLL 范围为：从借用处开始，一直持续到最后一次使用的地方**。具体的，它是**从借用变量定义或被再赋值开始，到被再赋值之前最后一次被使用结束**。

其中，以下场景属于对借用变量p的使用：
1. 函数调用use(p)或use(&mut*p)
2. 函数返回return p或return &mut*p
3. 解引用*p
4. 成员访问p->field

举例来说：
```C
//本例中p的NLL是分段的，每段NLL都有一个被借用对象
void test() {
    int local = 5;              //#1
    int *borrow p = &mut local1;//#2，p的第一段NLL开始，被借用对象为local1
    other_op();                 //#3
    use(p);                     //#4，p的第一段NLL结束
    other_op();                 //#5
    p = &mut local2;            //#6，p的第二段NLL开始，被借用对象为local2，由于后面没有再对p的使用，p的NLL结束
    other_op();                 //#7
}
//p的NLL是：[2,4]->local1, [6,6]->local2
```
##### 2.4 被借用对象的 Lexical Lifetime
与借用变量不同，被借用对象的生命周期是 Lexical Lifetime，对于不同种类被借用对象的生命周期，我们给出具体的定义：
| 被借用对象种类 | | 生命周期定义 |
| ---- | ---- | ---- |
| 全局变量 | | 全局变量的生命周期是整个程序，从程序开始到退出，一直存在 |
| 局部变量 | owned变量 | 从变量定义开始，到它被 move 走结束（owned struct类型如果没有被move，生命周期会在当前block结束的时候结束）
| | 非owned非borrow变量 | 从变量定义开始，到当前 block 结束 |
| 局部字面量 | "string literal" | 从使用处开始，到当前 block 结束的时候结束 |
| | (struct S) { ... } | 从使用处开始，到当前 block 结束的时候结束
| e->field | | e 的生命周期 |
| e.field | | e 的生命周期 |
| e[index] | | e 的生命周期 |
| *e | | e 的生命周期 |

#### 2.5 借用的生命周期约束
在2.1中我们提到过，对于借用，我们有这样的生命周期约束：**借用变量的生命周期，不能比被借用对象的生命周期长**。
举例来说：
```C
//本例中，p的生命周期为[2,4]，被借用对象local的生命周期为[1,4]，满足生命周期约束
void test1() {
    int local = 5;               //#1
    int *borrow p = &mut local;  //#2
    use(p);                      //#3
}                                //#4

//本例中，p的生命周期有两段“
//第一段为[2,2]，被借用对象local的生命周期为[1,8]，满足生命周期约束
//第二段为[5,7]，被借用对象local1的生命周期为[4,6]，不满足生命周期约束，error
void test2() {
    int local = 5;              //#1
    int *borrow p = &mut local; //#2
    {                           //#3
        int local1 = 5;         //#4
        p = &mut local1;        //#5
    }                           //#6
    use(p);                     //#7
}                               //#8

//本例中p的生命周期有两段：
//第一段为[2,2]，被借用对象local的生命周期为[1, 8]，满足生命周期约束
//第二段为[5,7]，被借用对象有两个，分别是local和local1，其中local1的生命周期为[4, 6]，不满足生命周期约束，error
void test3() {
    int local = 5;                         //#1
    int *borrow p = &mut local;            //#2
    {                                      //#3
        int local1 = 5;                    //#4
        p = call(&mut local, &mut local1); //#5
    }                                      //#6
    use(p);                                //#7
}                                          //#8

//本例中，if分支对p进行了重新赋值，在#10 use(p)时，p的被借用对象local2的生命周期已经结束，不满足生命周期约束，error
//else分支满足生命周期约束
void test4() {
    local = 5;                  //#1
    int* borrow p = &mut local; //#2
    int local1 = 5;             //#3
    if (rand()){                //#4
        int local2 = 5;         //#5
        p = &mut local2;        //#6
    } else {                    //#7
        p = &mut local1;        //#8
    }                           //#9
    use(p);                     //#10
}

//本例中，p的生命周期为[2,4]，被借用对象*x的生命周期为[1,3]，不满足生命周期约束，error
void test5() {
    int *owned x = safe_malloc<int>(5); //#1
    int *borrow p = &mut *x;           //#2
    safe_free(x);                      //#3
    use(p);                            //#4
}                                      //#5
```

#### 3.可变借用和不可变借用
毕昇 C 将借用指针的权限进行了分级，分为可变（mut）借用和不可变（immut）借用，我们可以通过操纵可变借用指针来读写被借用对象的内容，通过不可变借用指针，我们只能读取被借用对象的内容，但是不能修改它。例如：
```C
void use_mut(int *borrow p) {
    *p = 5;      //通过可变借用指针，可以修改被借用对象的值
    int a = *p;  //通过可变借用指针，可以读取被借用对象的值
}

void use_immut(const int *borrow p) {
    *p = 5;  //error，无法通过不可变借用指针，来修改被借用对象的值
    int a = *p;  //通过不可变借用指针，可以读取被借用对象的值
}
```
##### 3.1 `&mut e`要求 e 是可修改的
我们在 1.1 中提到过，`&mut e`和`&const e`要求表达式 e 是 lvalue，即 e 是可以被取地址的，对于可变借用表达式`&mut e`，我们还要求 e 是可变的，具体的：
| lvalue表达式 | 是否可修改 |
| ---- | ---- |
| ident | 变量 ident 没有被 const 修饰，且ident 不能是函数名 |
| "string literal" | 不允许，因为字符串常量保存在常量区，不能写 |
| (struct S) { ... } | 允许 |
| e->field | 要求 e 是可变借用指针，或者是指向可修改类型的 owned 指针，或者是指向可修改类型的裸指针，且field没有被const修饰，多级 field 的情况应该要求每一级的 field 都没有 const 修饰 |
| e.field | 要求 e 是可变的，且field没有被const修饰，多级 field 的情况应该要求每一级的 field 都没有 const 修饰 |
| e[index] | 要求 e 是可变的 |
| *e | 要求 e 是可变借用，或者是指向可修改变量的裸指针 |

##### 3.2 可变借用同时只能存在一个
如果有两个或更多的指针同时访问同一数据，并且至少有一个指针被用来写入数据，可能会导致未定义行为，例如：
```C
void test() {
    int *a = malloc(sizeof(int));
    *a = 42;
    int *p1 = a;
    int *p2 = a;
    free_a(p1);    //该函数会释放 a 所指向的内存
    read_a(p2);    //该函数会读取 a 所指向的内存
}
```
由于借用本质上也是指针，所以为了避免上述问题，毕昇 C 规定，**同一时刻，对于同一个对象，要么只能拥有一个可变借用, 要么任意多个不可变借用**。
```C
void test1() {
    int local = 5;
    int *borrow p1 = &mut local;
    int *borrow p2 = &mut local;  //error，同一时刻最多只能有一个指向local的可变借用变量
    modify(p1);
    modify(p2);
}

void test2() {
    int local = 1;
    int *borrow p1 = &mut local;
    int *borrow p2 = &mut local;  //error，同一时刻最多只能有一个指向local的可变借用变量
    use(p2);
    use(p1);
}

void test3() {
    int local = 1;
    int * borrow p1 = &mut local;
    const int * borrow p2 = &const local; //error，指向local的可变和不可变借用不能同时存在
    use(p1);
    use(p2);
}

void test4() {
    int local = 1;
    const int * borrow p1 = &const local;
    int * borrow p2 = &mut local; // error，指向local的可变和不可变借用不能同时存在
    use(p1);
    use(p2);
}
```

如果同时存在对一个变量的可变借用和不可变借用，可能会出现通过可变借用修改被借用对象的内存状态，然后再使用不可借用访问被修改的内存，从而导致未定义行为的情况。
例如：

```C
struct A {
    int *p;
};

const int * borrow struct A::get_p(This * borrow this) {
    return &const *(this->p);
}

void struct A::free_p(This * borrow this) {
    free(this->p);
}

int main() {
    struct A a = { .p = malloc(sizeof(int)) };
    const int * borrow q = a.get_p();    // q借用了a.p
    a.free_p();                          // a.p指向的内存被释放
    printf("%d", *q);                    // *q的操作可能会导致未定义行为
    return 0;
}
```

上述代码中，`a.free_p()`实际上使用了一个指向 a 的可变借用，该可变借用会使在它之前被定义的借用 q 失效，由于`printf("%d", *q)`使用了失效的 q，毕昇 C 编译器会报错，也就阻止了不安全行为的发生。

由于不可变借用不会导致被借用对象被修改，因此同一时刻可以拥有任意多个不可变借用，例如：
```C
void test() {
    int local = 5;
    const int *borrow p1 = &const local;
    const int *borrow p2 = &const local;
    read(p1);  //ok，同一时刻可以拥有任意多个不可变借用
    read(p2);
}
```

#### 4.借用对被借用对象的影响
##### 4.1 不可变借用对被借用对象的影响
对表达式 e 做不可变借用， 即`&const e`，在这个不可变借用的生命周期结束之前，e 只能读不能修改，也不能对 e 创建可变借用。
| 不可变借用表达式 | 被借用对象的状态 |
| ---- | ---- |
| &const ident` | 变量 ident 只能被读不能被修改，也不能再对变量 ident 创建可变借用，允许对变量ident创建不可变借用 |
| &const "string literal" | 临时变量永远是 “只读” 状态 |
| &const (struct S) { ... } | 临时变量永远是 “只读” 状态 |
| &const e->field | e->field 进入 “只读” 状态，也不允许整体修改 *e。但允许修改 e 指向的其它成员，或者对其它成员做可变借用 |
| &const e.field | e.field 进入 “只读” 状态，也不允许整体修改 e。但允许修改 e 的其它成员，或者对其它成员做可变借用 |
| &const e[index] | e 进入 “只读” 状态，不允许修改 e 及其直接或间接成员，或者对其它成员做可变借用 |
| &const *e | *e 进入 “只读” 状态，不允许修改 *e 及其直接或间接成员，或者对其它成员做可变借用，如果 e 是 owned 指针类型，则 e 也进入只读状态 |

##### 4.2 可变借用对被借用对象的影响
对表达式 e 做可变借用， 即`&mut e`，表达式 e 进入 “冻结” 状态。在这个可变借用的生命周期结束之前，e 不能读，不能修改（包含被move），也不能被借用。
| 可变借用表达式 | 被借用对象的状态 |
| ---- | ---- |
| &mut ident` | 变量 ident 被冻结 |
| &mut "string literal" | 编译错误 |
| &mut (struct S) { ... } | 临时变量被冻结 |
| &mut e->field | e->field 被冻结，不允许读写 e->field，不允许整体修改 *e，但允许修改 e 指向的其它成员，或者对其它成员做可变借用 |
| &mut e.field | e.field 被冻结，不允许读写 e.field，不允许整体修改 e，但允许修改 e 的其它成员，或者对其它成员做可变借用 |
| &mut e[index] | e 被冻结，不允许读写 e 以及它的成员 |
| &mut *e | *e 被冻结，不允许读写 *e 以及它的成员，如果 e 是 owned 指针类型，则也不允许读写 e |

#### 5. 函数定义中包含借用类型
1. 不允许函数参数中没有借用类型的参数，但是函数返回是借用类型。

2. 如果函数参数中有一个借用类型的参数，函数返回是借用类型，那么我们直接认为这个返回值的借用，是来自于这个借用类型参数，返回的借用的 “被借用对象” 与这个借用类型参数的 “被借用对象” 一样，这个返回的借用也应该满足前面提到的那些借用规则。

3. 如果函数参数中有多个借用类型的参数，函数返回是借用类型，那么我们直接认为这个返回值的借用，同时包含了从多个借用类型参数传递过来的 “被借用变量”，这个返回的借用也应该满足前面提到的那些借用规则。

```C
int* borrow f1(int* borrow p);
int* borrow f2(int* borrow p1, int* borrow p2);

void test() {
    int local = 5;
    int* borrow p1 = f1(&mut local);
    /* 函数 f1 的参数创建了一个对 local 的可变借用，这个借用被传递给了返回值 p1，
       导致 p1 相当于是对 local 的一个可变借用, 所以返回值 p1 的被借用对象是 local,
       在 p1 的生命周期结束之前，local 会一直被冻结。*/

    int local1, local2;
    int* borrow p2 = f2(&mut local1, &mut local2);
    /* 函数 f2 的参数创建了一个对 local1 和 local2 的可变借用，这两个借用被传递给了返回值 p2，
       导致 p2 相当于是对 local1 和 local2 的一个可变借用, 所以返回值 p2 的被借用对象是 local1 和 local2,
       在 p2 的生命周期结束之前，local1 和 local2 一直被冻结。*/
}
```

#### 6. struct定义中包含借用类型
1. 结构体的成员可以是借用类型，带有借用类型成员的结构体变量在定义的时候必须初始化。
2. 结构体内如果包含多个借用成员，那么这个结构体同时存在多个 “被借用对象”，这些借用成员也应该满足前面提到的那些借用规则。

```C
struct R {
    int* borrow m1;
    int* borrow m2;
};

void test() {
    int local1, local2;
    struct R r = { .m1 = &mut local1, .m2 = &mut local2 };
    // 在 r 的生命周期结束之前，local1 和 local2 一直被冻结。
    // 因为变量 r 在初始化的时候创建了一个对 local1 和 local2 的可变借用，
    // 导致 r 同时包含对 local1 的一个可变借用，也包含对 local2 的可变借用。
}
```

#### 7. 借用变量的解引用操作
允许对借用指针变量解引用，与标准 C 的解引用操作一致：对借用指针变量 p 解引用的语法为 `*p`。
对 const T * borrow 类型的借用变量 e 解引用 `*e`，结果为 T 类型
对 T * borrow 类型的借用变量 e 解引用 `*e`，结果为 T 类型
如果 p 是指向 T 类型的借用，o 是 T 类型的 lvalue，对于 `*p` 表达式，有如下限制：
| | T是Copy语义 | T是Move语义 |
| ---- | ---- | ---- |
| p是immut借用 | *p = expr; 不允许 | *p = expr; 不允许 |
| | o = *p; 允许 | o = *p; 不允许|
| p是mut借用 | *p = expr; 允许 | *p = expr; 允许 |
| | o = *p; 允许 | o = *p; 不允许|

上表中 move / copy 语义分别指： T 是 owned 修饰的类型和 T 是其它类型。

注：上表中的赋值操作的权限，可同样应用于函数的传参和返回场景。

#### 8. 借用变量的成员访问
允许借用指针变量访问成员变量或调用成员函数，与标准 C 的箭头运算符一致：访问指针变量 p 的成员变量 field 的语法为 `p->field`，调用指针变量 p 的成员方法 method() 的语法为 `p->method()`。

##### 8.1 访问成员变量
通过借用访问成员变量，表达式的类型取决于成员变量本身的类型。`p->field` 表达式的类型与 field 成员定义的类型相同。
如果 `p->field` 的类型是 T，o 是 T 类型的 lvalue，对于 `p->field` 表达式，有如下限制：
| | T是Copy语义 | T是Move语义 |
| ---- | ---- | ---- |
| p是immut借用 | p->field = expr; 不允许 | p->field = expr; 不允许 |
| | o = p->field; 允许 | o = p->field; 不允许|
| p是mut借用 | p->field = expr; 允许 | p->field = expr; 允许 |
| | o = p->field; 允许 | o = p->field; 不允许|

上表中 move / copy 语义分别指： T 是 owned 修饰的类型和 T 是其它类型。

注：上表中的赋值操作的权限，可同样应用于函数的传参和返回场景。

##### 8.2 调用成员函数
通过借用调用成员函数，即 `p->method()` 的场景，实参和形参之间的规则如下：

| | void method(const This * borrow this) | void method(This * borrow this) |
| ---- | ---- | --- |
| p是immut借用 | 允许 | 不允许，immut借用不能创建出mut借用 |
| p是mut借用 | 允许，允许从mut借用创建immut借用 | 允许 |

举例来说：
```C
void int::method1(const This * borrow this) {}
void int::method2(This * borrow this) {}

void test() {
    int local = 5;
    const int *borrow p1 = &const local;
    int *borrow p2 = &mut local;
    p1->method1(); //ok, 形参类型和实参类型一致，都是不可变借用
    p1->method2(); //error, 形参是可变借用类型，实参是不可变借用类型，不可变借用不能创建出可变借用
    p2->method1(); //ok, 形参是不可变借用类型，实参是可变借用类型，允许从可变借用创建出不可变借用
    p2->method2(); //ok, 形参类型和实参类型一致，都是可变借用
}
```

#### 9. 借用的类型转换
1. 对于任意类型 T，如果 T 实现了 trait TR，则允许指向类型 T 的借用向上转型为指向类型 TR 的借用；反过来，从类型 TR 的借用往类型 T 借用的转换，是不允许的。
```C
trait T {
    void print(This* borrow this);
};
void int::print(int* this) { }

impl trait T for int;

void test() {
    int x = 10;
    int * borrow r = &mut x;
    trait T * borrow p = r; //支持 int* 类型的借用向上转型为 trait TR* 类型的借用
    p->print();
}
```
2. 允许指向类型 T 的借用转换为指向 void 类型的借用，反过来从类型 void 的借用往类型 T 借用的转换，是不允许的。
```C
void test() {
    int x = 10;
    int * borrow r = &mut x;
    void * borrow p = r; //支持 int * 类型的借用转为 void * 类型的借用
}
```
3. 只允许在非安全区进行 T * borrow 和 T * 之间的转换。
```C
unsafe { int * borrow p = (int* borrow) NULL };
```

#### 10. 借用的其它规则

除了上面的那些规则，对于借用，我们还有如下规则：
1. 对于全局变量，我们无法在函数签名中跟踪哪个函数读取了全局变量，哪个函数修改了全局变量。为了保证安全性，毕昇 C 规定：在安全区内，只允许对全局变量取只读借用，不允许取可变借用。如果是对函数名做借用，从生命周期的角度，可以当做是对全局变量做借用。

2. 借用变量在定义的时候必须初始化。
```C
void test() {
    int *borrow p; //error
}
```

3. 用一个借用类型的表达式给另外一个借用类型的 lvalue作初始化或再赋值，即 p = e，p 和 e 必须是同类型的借用类型，而且要求 e 的生命周期必须大于 p 的生命周期。
```C
void test() {
    const int *borrow p = &mut local; //error
}
```
基于此规则，一个 struct 内部的 borrow 指针成员，是不可以对这个 struct 或者它的其它成员做借用的。
```C
struct S {
    int m;
    const int * borrow p;
};

void test() {
    struct S s = { .m = 0, .p = &const s.m }; // error，因为s.p的生命周期与s.m的生命周期相同
}
```

4. 借用变量不允许是全局变量，只能是局部变量。
```C
int g = 5;
int *borrow p = &mut g; //error
void test() {
    int *borrow p = &mut g; //ok
}
```

5. 不允许对包含借用的表达式，再取借用。同理，借用类型 T* borrow 中，T 本身及其成员不能是借用类型。
```C
struct R {
    int *borrow p;
};

void test() {
    int local = 5;
    int *borrow *borrow p = &mut (&mut local); //error

    struct R r1 = { .p = &mut local };
    struct R * borrow r2 = &mut r1;    //error，r中已经包含了借用
}
```

6. 不允许为借用类型实现 trait。
```C
impl trait TR for int *borrow;//error
```

7. 不允许为借用类型添加成员函数。
```C
void int *borrow::f() {} //error
```

8. union 的成员不允许是借用类型。
```C
union MyUnion {
    int *borrow p;//error，借用指针不允许作为union成员
};
```

9. 借用指针类型不能是泛型实参。

10. 借用指针变量不支持索引运算。

11. 借用指针变量不支持算术运算。

12. 允许同类型的借用变量之间，使用 `==`、`!=`、`>`、`<`、`<=`、`>=` 等比较运算符操作。

13. 允许对借用类型使用 `sizeof`、`alignof`操作符，并且有：
sizeof(T* borrow) == sizeof(T*)
_Alignof(T* borrow) == _Alignof(T*)

14. 允许对借用类型使用一元的`&`、`!`及二元的`&&`、`||`运算符。

15. 不允许对借用类型使用一元的`-`、`~`、`&const`、`&mut`、`[]`、`++`、`--`运算符，也不允许对借用类型使用二元的`*`、`/`、`%`、`&`、`|`、`<<`、`>>`、`+`、`-`运算符。

16. 如果一个借用指针变量指向的是函数，那么可以通过这个借用指针变量来调用函数。
```C
int f() {}
void test() {
    int (* borrow p)() = &mut f;
    p();
}
```

17. 不允许对函数做可变借用，只能做只读借用。


### 安全区

#### 概述：

c 语言有很多规则过于灵活，不方便编译器做静态检查。因此我们引入一个新语法，使得在一定范围内的毕昇 c 代码必须遵循更严格的约束，保证在这个范围内的代码肯定不会出现“内存安全”问题。

允许用 safe/unsafe 关键字修饰函数、语句、括号表达式。

- ​    unsafe 表示这段代码在非安全区，这部分代码遵循标准 c 的规定，同时这部分代码的安全性由用户保证。


- ​    safe 表示这段代码在安全区，这部分代码必须遵循更严格的约束，同时编译器可以保证内存安全。


- ​    没有 safe/unsafe 关键字修饰的全局函数默认是非安全的。


#### 代码示例：

```c
#include <stdlib.h>

typedef struct File{
} FileID;

FileID* owned create(void) {
  FileID *p = malloc(sizeof(FileID));
  return (FileID* owned)p;
}

FileID* owned consume_and_return(FileID* owned p) {
  return p;
}
// 使用 safe 修饰函数，表示该函数为安全函数，函数内为安全区
safe void safe_free(FileID* owned p) {
    // 使用 unsafe 修饰代码块，表示这段代码在非安全区。这段代码是在安全区内的非安全区，也属于非安全区
    unsafe {free((FileID*)p);}
}

int main(void) {
  FileID* owned p1 = create();
  FileID* owned p2 = consume_and_return(p1);
  // 使用 safe 修饰语句，表示这段代码在安全区
  safe safe_free(p2);
  return 0;
}
```

#### 语法规则：

1. 允许使用 safe/unsafe 修饰函数声明、函数签名、函数定义、函数指针、语句、括号表达式。

   ```c
   // 修饰函数签名
   safe int test(int, int);
   // 修饰函数定义
   safe int test(int a, int b);
   // 修饰函数声明
   safe int test(int a, int b) {
   	return a + b;
   }
   // 修饰函数指针
   safe int (*p)(int, int);
   
   safe int main(void) {
       safe {  // 修饰代码块
           int a = 1;
       }
       unsafe {
           int b = 1;
       }
       // 修饰语句
       safe int c = 1;
       unsafe c++;
       // 修饰括号表达式
       char d = unsafe((char)c);
       return 0;
   }
   ```

2. 不允许使用 safe/unsafe 修饰全局变量、函数外类型声明、typedef 声明（允许修饰函数指针)。

   ```c
   #include <assert.h>
   
   safe int g_a; // error: 不允许修饰全局变量
   safe struct b {   // error: 不允许修饰函数外类型声明
       int a;
   };
   safe typedef int mm; // error: 不允许修饰 typedef
   safe typedef int (*p)(int a); // ok: 允许修饰函数指针
   int main() {
       return 0;
   }
   ```
   
3. safe 修饰的函数，参数类型和返回类型必须是 safe 类型。

   非 safe 类型包括：裸指针类型、union 类型、成员中包含不安全类型的 struct 类型、成员中包含不安全类型的数组类型。

   ```c
   safe int* test1(int a);  // error: 返回值为非安全类型的裸指针类型
   safe int test2(int *a);  // error: 参数类型为非安全类型的裸指针类型

   typedef struct F {
       int* a;
   } SF;
   safe SF test3(int a); // error: 返回值为成员中包含不安全裸指针类型的 struct 类型
   safe int test4(SF b); // error: 参数类型为成员中包含不安全裸指针类型的 struct 类型
   ```

4. safe 修饰的函数，函数参数列表不可以省略。`safe void test(); `是不允许的， `safe void test(void); `是允许的。

5. safe 修饰的函数，函数参数列表不可以包含变长参数。`safe int test(int a,  ...); `是不允许的。

6. 如果 trait 中的函数被声明为 safe，那么要求实现 trait 的类型的对应成员函数也必须是 safe 修饰的函数。若 trait 中的函数未声明为 safe，也允许实现 trait 中的类型的成员函数为 safe。

   ```c
   trait G {
       safe int* owned test1(This* owned this);
       int* owned test2(This* owned this);
   };
   safe int* owned int::test1(int* owned this) {
       return this;
   }
   safe int* owned int::test2(int* owned this) {
       return this;
   }
   impl trait G for int;
   ```

7. 多个同名函数声明必须有同样的 safe/unsafe 修饰。

   ```c
   safe int test(int a);
   unsafe int test(int a); // error: 多个函数声明中 safe/unsafe 不一致
   ```

8. 多个同名函数声明排除 safe/unsafe 修饰后，是完全一致的。

   ```c
   safe int test(int a);
   safe int test(int a, int b); // error: 函数声明不完全一致
   ```

9. safe 修饰泛型函数时，会对泛型每个实例化版本也做 safe 检查。

   ```c
   safe T test<T>(T a) {
       return a;
   }

   void test2() {
       int a = 1;
       int b = test<int>(a);
       int* owned c = (int* owned)&a;
       int* owned d = test<int* owned>(c);
       int* e = test<void*>((void*)0);  // error: 实列化函数入参和返回值为非安全的裸指针类型
   }
   ```

10. 成员函数也可以被 safe/unsafe 修饰，其规则和全局函数一样。

    ```c
    struct MyStruct<T> {
        T res;
    };
    safe T struct MyStruct<T>::foo_a(T a) {
        return a;
    }
    ```

11. 对于 safe 修饰的函数指针类型，与赋值的函数参数和返回值类型必须是一致的。

    ```c
    safe void test1(int a) {}
    safe void test2(void) {}
    safe void (*p)(int a);
    int main() {
    	p = test1; // ok
    	p = test2; // error: 参数类型不一致，不允许赋值
    }
    ```

12. 安全区内被调用的函数或函数指针必须是 safe 的函数签名，不允许调用非安全函数或函数指针。

    ```c
    safe void test1(void) {}
    unsafe void test2(void) {}
    safe void (*test3)(void);
    unsafe void (*test4)(void);
    int main() {
        safe {
            test1();
            test2(); // error: 安全区内不允许调用非安全函数
            test3();
            test4(); // error: 安全区内不允许调用非安全函数指针
        }
        unsafe {
            test1();
            test2();
            test3();
            test4();
        }
    }
    ```

13. 安全区内允许再包含 unsafe 修饰的语句、函数指针、括号表达式，非安全区内也允许再包含 safe 修饰的语句、函数指针、括号表达式。

    ```c
    int test1(int a, int b) {
        return a + b;
    }
    safe int test2(int a, int b) {
        return a > b ? a : b;
    }
    int main() {
        safe {
            int a = 0;
            unsafe a++;
            unsafe {
                a = test1(1, 3);
                safe a = test2(3, 5);
            }
        }
    }
    ```

15. 安全区内不允许无初始化或初始化不完整的变量声明。

    ```c
    struct F {
    	int age;
    	char name[20];
    };
    void test() {
    	safe {
    		int a; // error: 安全区内不允许无初始化的变量声明
    		struct F tom = {10}; // error：安全区不允许部分初始化
    		struct F tony = {10, "tony"};
    	}
    }
    ```

16. 安全区内 switch 语句中的 case/default 只能存在于 switch 后面的第一层代码块中，且第一层代码块不允许有变量定义。

    ```c
    safe void test(int a) {
        switch (a) {
        	int b = 10;  // error: 第一层代码块不允许有变量定义
            case 0: {
                int c = 1;  // ok
                break;
            }
            {
                case 1: {    // error: case 只能存在于 switch 后面的第一层代码块中
                    break;
                }
            }
            {
                default:{   // error: default 只能存在于 switch 后面的第一层代码块中
                    break;
                }
            }
        }
    }
    ```

17. 安全区内不允许使用自增 （++）、自减（--）操作符，不允许 union 类型通过“.”访问成员，不允许裸指针通过“->”访问成员，

    允许owned指针和borrow指针通过“->”访问成员。

    ```c
    union un {
        int age;
        char name[16];
    };
    struct F {
        int age;
    };

    void test(void) {
        struct F d = {10};
        struct F *e = &d;
        struct F* owned f = (struct F* owned)&d;
        struct F* borrow i = &mut d;
        safe {
            int a = 1;
            a++;    // error: 安全区不允许自增
            a--;    // error: 安全区不允许自减
            union un b = {10};
            int c = b.age;   // error: 安全区不允许 union 通过“.”访问成员
            int g = e->age;  // error: 安全区不允许裸指针通过“->”访问成员
            int h = f->age;  // ok ：允许owned指针“->”通过访问成员
            int j = i->age;  // ok ：允许borrow指针“->”通过访问成员
        }
    }
    ```

18. 安全区内不允许使用取地址符“&”（允许对函数取地址），只允许&const，&mut取借用。

    安全区内不允许解引用裸指针类型，但可以解引用owend指针类型和borrow指针类型。

    ```c
    #include "bishengc_safety.hbs" // BiShengC 语言提供的头文件，用于安全地进行内存分配及释放

    void test() {
    	safe {
    		int a = 10;
    		int *b = &a;  // error: 安全区不允许取地址符号
    		int c = *b;	  // error: 安全区不允许解引用裸指针
            int * owned d = safe_malloc(2);
            int e = *d;   // ok: 解引用owned指针
            safe_free(d);
            int * borrow f = &mut a;
            int g = *f;   // ok: 解引用borrow指针
    	}
    }
    ```

19. 安全区内不允许指向类型不同的指针类型之间转换，不允许指针和非指针类型之间的转换，不允许 owned/borrow/raw 指针之间的转换。

    ```c
    void test() {
    	int *a;
    	double *b;
    	safe {
    		b = a;  // error：不允许指向类型不同的指针类型之间转换
    		a = b;  // error：不允许指向类型不同的指针类型之间转换
    		b = (double *)a;  // error：不允许指向类型不同的指针类型之间转换
    	}
    	int c;
    	safe {
    		a = c;  // error：不允许指针和非指针类型之间的转换
    		c = a;  // error：不允许指针和非指针类型之间的转换
    	}
    	int* owned d = (int* owned)&c;
    	safe {
    		a = d;  // error：不允许 owned/raw 指针之间的转换
    		d = a;  // error：不允许 owned/raw 指针之间的转换
    	}
    }
    ```

20. 安全区内不允许表达范围从大向小的类型转换（比如从 long 转换为 int，从 int 转换为 _Bool，从 int 转换为 enum）。不允许表达精度从高向低的类型转换（比如从 double 转换为 float）。对于基础类型的常量发生类型转换，如果目标类型可以描述这个值，那么该类型转换是允许的。

    ```c
    void test() {
        long a;
        int b;
        _Bool c;
        double e;
        float f;
        safe {
            a = b;    // ok
            b = a;    // error: 不允许表达范围从大向小的类型转换
            a = 1;    // ok
            c = 1;    // ok
            c = 2;    // error: 目标类型不可以描述这个值，不允许转换
            e = f;    // ok
            f = e;    // error：不允许表达精度从高向低的类型转换
            f = 1.0;  // ok
            f = 1.2f; // ok
        }
    }
    ```

21. 安全区内不允许内嵌汇编语句。

    ```c
    void test() {
        safe {
            int ret = 0;
            int src = 1;
            asm("move %0, %1\n\t" :"=r"(ret) :"r"(src)); // error: 安全区不允许内嵌汇编
        }
    }
    ```

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

## 运算符重载

### 概述

通过给函数增加 operator 属性来定义一个函数，并告诉编译器，对于符合函数入参规则的该运算符需调用此函数来行使运算符功能。这个函数也叫做运算符的重载函数。

### 代码示例

```c++
#include <assert.h>
struct square
{
    int width;
    int height;
};

// 运算符‘+’号重载函数
__attribute__((operator +))
struct square squareAdd(struct square s1, struct square s2){
    struct square s = {s1.width + s2.width, s1.height + s2.height};
    return s;
}

int main(){
    struct square s1 = {100, 50};
    struct square s2 = {60, 110};
    // 在之前我们必须主动调用函数来完成结构体运算操作。
    struct square s3 = squareAdd(s1, s2);
    assert(s3.width == 160);
    assert(s3.height == 160);
	// 将函数加上重载标记后，现在我们可以直接对该结构体进行运算操作。
    struct square s4 = s1 + s2;
    assert(s4.width == 160);
    assert(s4.height == 160);
    return 0;
}
```

### 语法规则

1、在普通函数基础上，通过 `__attribute__((operator Op))` 属性标记该函数为运算符重载函数。

```c
__attribute__((operator OP)) function-declaration
```

代码示例：

```c
// 定义了一个“+”号运算符重载函数 
__attribute__((operator +))
struct square squareAdd(struct square s1, struct square s2){
    struct square s = {s1.width + s2.width, s1.height + s2.height};
    return s;
}
```
2、运算符重载函数只能是全局函数，不允许标记成员函数、`trait`声明的函数为重载函数。

3、支持重载的运算符列表。

| 类别           | 运算符                                                       |
| -------------- | ------------------------------------------------------------ |
| 双目算术运算符 | + (加)，- (减)，* (乘)，/ (除)，% (取模)                     |
| 关系运算符     | == (等于)，!= (不等于)，< (小于)，> (大于)，<= (小于等于)，>= (大于等于) |
| 位运算符       | \| (按位或)，& (按位与)，~ (按位取反)，^ (按位异或),，<< (左移)，>> (右移) |
| 单目运算符     | \+ (正)，- (负)，* (解引用)                                  |
| 成员访问运算符 | ->                                                           |
| 索引运算符     | []                                                           |

4、运算符重载函数入参和返回值要求。

| 运算符           | 入参要求     | 返回值要求                                                |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 关系运算符 | 只允许有两个入参, 且至少有一个参数是用户自定义类型，如结构体、枚举。 | 返回值类型必须是_Bool类型         |
| *(解引用), <br />-> (成员访问运算符) | 只允许有一个入参,且第一个参数为用户自定义类型的指针类型，包括裸指针、可变借用指针、不可变借用指针。 | 返回值类型必须是指针类型，包括裸指针、可变借用指针、不可变借用指针、Rc指针。 |
| [] (索引运算符) | 只允许有两个入参,且第一个参数为用户自定义类型的指针类型，包括裸指针、可变借用指针、不可变借用指针。 | 返回值类型必须是指针类型，包括裸指针、可变借用指针、不可变借用指针、Rc指针。 |
| 其他     | 单目运算符只允许有一个入参, 双目运算符值只允许有两个入参。函数至少有一个入参是用户自定义类型。 | 无                              |

- 关系运算符重载代码示例

    ```c
    #include <assert.h>
    struct Foo {
        int x;
        int y;
    };

    __attribute__((operator >))
    _Bool FooCompare(struct Foo A, struct Foo B) {  // 参数至少有一个是用户自定义类型
        return A.y > B.y;
    };

    int main() {
        struct Foo f1 = {180, 18};
        struct Foo f2 = {166, 22};
        assert(f2 > f1 && "compare error");
        return 0;
    }
    ```

- 解引用运算符重载代码示例

    ```c
    #include <assert.h>
    struct MyPoint<T> {
        T * data;
    };
    
    __attribute__((operator *))
    T * derefMyPoint<T>(struct MyPoint<T> * borrow p) {  // 入参和返回值必须是指针类型。
        return p->data;
    }
    
    int main() {
        int data = 100;
        struct MyPoint<int> p = {&data};
        // 编译器匹配到重载函数后，自动对p取地址并传入重载函数，并对函数返回值做解引用。此处等效为(*derefMypoint(&mut p)) == 100。
        assert(*p == 100);
        *p = 10;
        assert(*p == 10);
        return 0;
    }
    ```

- 成员访问运算符重载代码示例

    ```c
    #include <assert.h>
    struct MyData<T> {
        T a;
    };
    struct MyPoint<T> {
        MyData<T>* data;
    };
    
    __attribute__((operator ->))
    MyData<T> * mDerefMyPoint<T>(struct MyPoint<T> * borrow p) {   // 入参和返回值必须是指针类型。
        return p->data;
    }
    
    int main() {
        struct MyData<int> d = {100};
        struct MyPoint<int> p = {&d};
        assert(p->a == 100);   // 编译器匹配到重载函数后，自动对p取地址并传入重载函数。此处等效为mDerefMyPoint(&mut p)->a == 100。
        p->a = 10;
        assert(p->a == 10);
        return 0;
    }
    ```

-  索引运算符重载代码示例

    ```c
    #include <assert.h>
    #define ARRLEN 10
    struct MyArray<T> {
        T data[ARRLEN];
    };
    
    __attribute__((operator []))
    T * GetMyArrayData<T>(struct MyArray<T> * p, int index) {
        return &p->data[index];
    }
    
    int main() {
        struct MyArray<int> array;
        for (int i = 0; i < ARRLEN; i++) {
            // 编译器匹配到重载函数后，自动对p取地址并传入重载函数,并对函数返回值做解引用。此处等效为*GetMyArrayData(&mut p, i) = i。
    		array[i] = i;
        }
        assert(array[5] == 5);
        return 0;
    }
    ```
    
-  运算符重载错误代码示例

    ```c
    // error: 不允许定义无用户自定义入参类型的运算符重载函数。
    __attribute__((operator +))
    int squareAdd(int a, int b){
        return a + b;
    }
    ```

5、运算符重载函数名不能与普通函数名冲突。对同一个运算符定义多个重载函数时，如果函数名不同并且参数类型不完全一致，允许同时存在。

```c
__attribute__((operator +))
struct square squareAdd(struct square s1, struct square s2){
    /* code */
}
// 支持对同一个运算符多次重载
__attribute__((operator +))
struct oblong oblongAdd(struct oblong s1, struct oblong s2){
    /* code */
}
```

7、运算符重载函数可以是泛型函数。

```c
#include <stdio.h>

struct Point<T>
{
    T x;
    T y;
};

__attribute__((operator +))
struct Point<T> Add<T>(struct Point<T> lhs, struct Point<T> rhs){
  T x1 = lhs.x + rhs.x;
  T y1 = lhs.y + rhs.y; 
  struct Point<T> p = {.x = x1, .y = y1};
  return p;
}

__attribute__((operator *))
struct Point<T> Mul<T>(struct Point<T> lhs, struct Point<T> rhs){
  T x1 = lhs.x * rhs.x; 
  T y1 = lhs.y * rhs.y; 
  struct Point<T> p = {.x = x1, .y = y1};
  return p;
}

void test1() {
  struct Point<int> p1 = {.x = 1, .y = 2};
  struct Point<int> p2 = {.x = 3, .y = 4};
  struct Point<int> p3 = p1 + p2; // {.x = 4, .y = 6}
  printf("p3.x: %d, p3.y :%d\n", p3.x, p3.y);  
}

void test2() {
  struct Point<int> p1 = {.x = 1, .y = 2};
  struct Point<int> p2 = {.x = 3, .y = 4};
  struct Point<int> p3 = p1 * p2; // {.x = 3, .y = 8}
  printf("p3.x: %d, p3.y :%d\n", p3.x, p3.y);  
}

int main() {
  test1();
  test2();
}
```

## 非空指针
为了提高指针使用的安全性，BSC 为指针引入了可空（Nullable）和非空（Nonnull）属性：
1. 使用`_Nullable`关键字修饰任意指针类型（包括裸指针、owned和borrow指针），表明该指针是可空指针。
2. 使用`_Nonnull`关键字修饰任意指针类型，表明该指针是非空指针。
在使用指针时，BSC 编译器会（在编译期）对指针的 nullability 进行检查，避免出现解引用空指针、通过空指针访问成员等不安全行为。

BSC 不允许在安全区内使用`NULL`，但是在日常开发中，空指针的使用是不可避免的，例如：
1. 一个指针的指向需要在运行时才能确定，那么我们可以将指针初始化为空指针，在后续再根据运行状态来修改指向
2. 对于可空指针，在使用前需要判断该指针是否为空指针
为此 BSC 引入了`nullptr`关键字来替代`NULL`，用户可以定义 Nullable 指针，并将其初始化为`nullptr`，在解引用 Nullable 指针前，也可以使用`nullptr`对指针判空。

我们用一个简单的例子来学习如何定义指针的 nullabiliy 并使用它：
```C
#include "bishengc_safety.hbs"

safe int get_current_status(void);  // 获取当前运行状态的函数

struct Data {
    int value;
};

// 如果 init 成功，返回具体的地址，否则返回 nullptr
safe struct Data *owned _Nullable init_data(void) {
    if (get_current_status() == 1) {
        struct Data data = { 10 };
        struct Data *owned p = safe_malloc<struct Data>(data);
        return p;
    }
    return nullptr;
}

safe void read_data(struct Data *borrow p);

safe int main(void) {
    // 使用 _Nullable 修饰指针类型：
    struct Data *owned _Nullable p = init_data();
    // init 后 p 可能为空指针，因此需要先判空再使用：
    if (p != nullptr) {
        read_data(&mut *p);  // 如果没有对 p 做判空，编译器会报 error!
        safe_free((void *owned)p);
    }
    return 0;
}
```

### 指针变量的 Nullability
指针变量的默认 Nullability 跟 qualifier 和指针类型有关：
1. 如果有 qualifier(`_Nonnull`或`_Nullable`)修饰，以这个为准
2. 如果没有 qualifier 修饰，裸指针默认是 Nullable 的，owned 和 borrow 指针默认是 Nonnull 的
```C
// Nullable 指针：
int *_Nullable p1 = nullptr;       
int *borrow _Nullable p2 = nullptr;
int *owned _Nullable p3 = nullptr;
int * p4 = nullptr;
// Nonnull 指针：
int *_Nonnull p5 = &a;
int *borrow _Nonnull p6 = &mut a;
int *owned _Nonnull p7 = safe_malloc<int>(5);
int *borrow p8 = &mut a;
int *owned p9 = safe_malloc<int>(5);
```

对于 Nonnull 指针，它的 Nullability 一定是 Nonnull 的。
对于 Nullable 指针，它的 Nullability 可能会发生变化：
1. 如果用非空表达式对其进行了赋值，那么在这条赋值语句后面可以把它当做 Nonnull 指针使用
2. 如果在控制流语句中对其做了判空，那么在非空的分支中，可以把它当做 Nonnull 指针使用

```C
safe int *borrow _Nullable nullable(int* borrow p);  //返回值类型为 Nullable 的
safe int *borrow nonnull(int* borrow p);             //返回值类型为 Nonnull 的

safe void test(void) {
    int local = 10;
    int *borrow _Nullable p1 = nullptr; // p1 初始化后 Nullability 为 Nullable
    *p1 = 10;                           // error
    p1 = &mut local;                    // p1 被再赋值后 Nullability 变为 Nonnull
    *p1 = 20;                           // ok
    p1 = nullable(&mut local);          // p1 被再赋值后 Nullability 变为 Nullable
    *p1 = 20;                           // error
    p1 = nonnull(&mut local);           // p1 被再赋值后 Nullability 变为 Nonnull
    *p1 = 20;                           // ok

    int *borrow _Nullable p2 = nullable(&mut local); // Nullable
    if (p2 != nullptr)     // if 分支中 p2 的 Nullability 为 Nonnull
        *p2 = 10;          // ok
    else                   // else 分支中 p2 的 Nullability 为 Nullable
        *p2 = 20;          // error
}
```

### 指针的赋值、传参和返回
1. 不允许用可空表达式给 Nonnull 指针赋值：
```C
safe int *borrow _Nullable nullable(int* borrow p);  //返回值类型为 Nullable
safe int *borrow nonnull(int* borrow p);             //返回值类型为 Nonnull

safe void test(void) {
    int local = 10;
    int *borrow p1 = nullptr;               // error
    int *borrow p2 = nullable(&mut local);  // error
    int *borrow p3 = nonnull(&mut local);   // ok

    int *borrow _Nullable p4 = nullable(&mut local); // p4 的 Nullability 是 Nullable
    int *borrow p5 = p4;                    // error

    int *borrow _Nullable p6 = nonnull(&mut local);  // p6 的 Nullability 是 Nonnull
    int *borrow p7 = p6;                    // ok
}
```

2. 函数调用时，如果形参为 Nonnull 类型，那么不能使用用可空表达式作为实参：
```C
safe void take_nonnull(int *borrow p);  // 接收 Nonnull 类型的指针作为参数
safe int *borrow _Nullable nullable(int* borrow p);  // 返回值类型为 Nullable

safe void test(void) {
    int local = 10;
    int *borrow _Nullable p = nullable(&mut local);
    take_nonnull(p);       // error
}
```

3. 函数返回值类型如果是 Nonnull 类型，也不能使用可空表达式作为返回值：
```C
safe int *borrow return_nonnull(int *borrow p) {
    int *borrow _Nullable q = nullptr;
    return q;              // error
}
```

### 指针的解引用、成员访问
被定义为 Nullable 的指针的 Nullability 会随赋值和控制流发生变化，BSC 编译器会跟踪这些变换，保证指针解引用、成员访问等操作的安全性。
```C
struct Data {
    int value;
};
safe struct Data *borrow _Nullable nullable(struct Data *borrow);

safe void test(void) {
    struct Data data = { .value = 10 };
    struct Data *borrow _Nullable p = nullable(&mut data);
    if (p != nullptr) {
        p->value = 10;         // ok，如果没有判空操作，编译器会报 error
    }
}
```

### 结构体成员是 Nullable 指针
初始化有 Nullable 指针成员的结构体变量时：
1. 如果是通过初始化列表进行初始化，BSC 编译器会根据初始化表达式来初始化 Nullable 指针成员的 Nullability
2. 对于其它初始化方式，直接认为 Nullable 指针成员的 Nullability 为 Nullable 的，这可能会导致本身没有问题的代码无法通过编译，此时需要对 Nullable 指针成员作再赋值，或使用判空语句，即可改变 Nullability。
```C
struct Data { int *borrow _Nullable value; };

safe struct Data init_data(int* borrow p);
safe int *borrow nonnull(int* borrow p);

safe void test(void) {
    int local = 10;
    // 使用初始化列表做初始化：
    struct Data data1 = { .value = nonnull(&mut local) };// data1.value 的 Nullability 是 Nonnull
    *data1.value = 10;              // ok
    // 使用函数返回值做初始化：
    struct Data data2 = init_data(&mut local);           // data2.value 的 Nullability 是 Nullable
    *data2.value = 10;              // error
    // 使用变量赋值做初始化：
    struct Data data3 = data1;      // data3.value 的 Nullability 是 Nullable
    *data3.value = 10;              // error

    // 对 Nullable 指针成员作再赋值，可以改变 Nullability：
    data2.value = nonnull(&mut local);
    *data2.value = 10;              // ok
    // 通过指针判空语句，也可以改变 Nullability：
    if (data3.value != nullptr)
        *data2.value = 10;          // ok
}
```
### 非空指针检查的范围和控制选项

非空指针检查是一项强大的功能，能帮助开发者在编译期识别出潜在的危险行为。同时，这会带来一定的编译性能开销和编码行为限制。默认情况下，对非空指针的检查仅在安全区生效，安全区的定义详见[内存安全-安全区](#安全区)章节。

在非安全区，我们将是否开启非空指针检查的选择权交给开发者，即通过编译选项`-nullability-check=value`来控制该项检查的作用域。其中`value`是一个枚举值，有3种选项`none`, `onlysafe`, `all`：

1. `value`的默认值为`safeonly`，控制着检查只在安全区生效；无该编译选项时，等同`-nullability-check=safeonly`。
2. `value`值为`none`时，将整体禁用非空指针检查，安全区与非安全区均不做检查。
3. `value`值为`all`时，将整体使能非空指针检查，安全区与非安全区均开启检查。

提供一个示例说明：

```C
safe void nullptrTest(void) {
  int *borrow _Nullable p = nullptr;
  {
    unsafe {
      *p = 10; // error1: nullable pointer cannot be dereferenced
    }
  }
  *p = 5; // error2: nullable pointer cannot be dereferenced
}
```
对于上面这个示例，当编译选项`-nullability-check`不存在或者`-nullability-check=safeonly`时，只有在`safe`区的`error2`会被报告；当`-nullability-check=none`时，`error1`和`error2`均不会被报告；当`-nullability-check=all`时，非安全区的`error1`和安全区`error2`均会被报告。

## 标准库

### 安全 API

#### `safe_malloc`

`safe_malloc`是 BiShengC 语言提供的一个安全的内存分配函数。
该函数接收一个泛型类型`T`的变量，表示要分配的内存的大小以及分配后对内存的初始化。
该函数的返回值为`T * owned`类型，即指向分配好的堆内存的`owned`指针。
一些具体的使用例子如下。

在 C 语言中，如果我们需要申请一段堆内存，我们可以使用`malloc`函数进行分配，然后给该内存赋值，如：

```c
void example() {
    int *p = (int *)malloc(sizeof(int));
    *p = 2;
}
```

然而，这样分配的内存不会在`p`的作用域结束时检查是否调用了`free`进行释放，会造成内存泄漏。
此外，如果再使用一个指针也指向该内存，并在作用域结束时释放，则会出现重复释放的问题，如：

```c
void example() {
    int *p = (int *)malloc(sizeof(int));
    *p = 2;
    int *q = p;
    free(p);
    free(q); // error: double free!
}
```

使用 BiShengC 语言即可解决这种问题，相应的代码如下：

```c
safe void example(void) {
    int * owned p = safe_malloc(2);
    int * owned q = p;
    unsafe {
        safe_free((void * owned)q);
    }
}
```

在使用 BiShengC 语言改写后的代码中，如果我们在函数退出前什么都不做，则会出现编译错误`"memory leak of value: `q`"`，避免了内存泄漏问题的发生；
如果我们在函数退出前同时调用`safe_free((void * owned)p)`和`safe_free((void * owned)q)`，则会出现编译错误`"use of moved value: `p`"`，避免了重复释放问题的发生。

那么对于更为复杂的结构体类型，该如何正确使用`safe_malloc`进行内存分配呢？
对于结构体类型，需要首先在栈上构造出相应的变量，然后传给`safe_malloc`在堆上完成相应内存的分配，以下代码为具体示例：

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void example(void) {
    struct S s = { .p = safe_malloc(1), .q = safe_malloc(2) };
    struct S * owned sp = safe_malloc(s);
    ...
}
```

#### `safe_free`

`safe_free`是 BiShengC 语言提供的一个安全的内存释放函数。
该函数接收一个`void * owned`类型的指针，表示要释放的内存的地址。
该函数的返回值为`void`类型。
因此，在调用`safe_free`进行释放前需要将`owned`指针显式地强制转换为`void * owned`类型，具体的转换规则可参考 [3.3](#33-强制类型转换) 节。
一些具体的使用例子如下。

```c
struct S {
    int * owned p;
    int * owned q;
};

safe void example(void) {
    int * owned pa = safe_malloc(199);
    struct S s = { .p = safe_malloc(1), .q = safe_malloc(2) };
    struct S * owned sp = safe_malloc(s);
    unsafe {
        safe_free((void * owned)pa);
        safe_free((void * owned)sp->p);
        safe_free((void * owned)sp->q);
        safe_free((void * owned)sp); // 必须先释放 sp->p 和 sp->q，才能释放 sp
    }
}
```

#### `safe_swap`

`safe_swap`是 BiShengC 语言提供的一个安全交换两个变量的值的函数。
该函数是一个泛型函数,接收两个类型为`T* borrow`类型的参数,即需要交换的变量的值的借用。
该函数的返回值为`void`类型,该 API 的主要作用为在交换两个变量的值时,同时能交换两个变量所拥有的所有权.
一个具体的使用例子如下。

```c
owned struct S {
public:
    int* owned p;
    int* owned q;
    ~S(S this) {
        safe_free((void* owned)this.p);
        safe_free((void* owned)this.q);
    }
};

safe void example(void) {
    S s1 = { .p = safe_malloc(1), .q = safe_malloc(2) };
    S s2 = { .p = safe_malloc(3), .q = safe_malloc(4) };
    safe_swap(&mut s1, &mut s2); // 交换后,s1.p为3,s1.q为4
}
```

#### `forget`

`forget` 主要用于获取变量的所有权并且“忘记”它，该函数是一个泛型函数，接收一个类型为泛型类型`T`的变量，表示要“忘记”的值：
1. 如果该变量是 owned 指针，那么该指针指向的内存不会被释放；
2. 如果该变量是 owned struct 类型，那么不会调用其析构函数。

在一些特殊的场景，用户希望取得变量的所有权而不通过该变量来释放管理的底层资源（如堆内存或文件句柄，这些资源可能已经通过裸指针操作被转移或释放），例如：

```c
#include "bishengc_safety.hbs"
#include <string.h>
owned struct Resource {
public:
    char *owned s;
    ~Resource(This this) {
        safe_free((void *owned)this.s);
    }
};

void get_resource(char* val) {
    Resource r = { .s = safe_malloc<char>(100) };
    memcpy(val, (const void *)&r, sizeof(Resource)); // Resource中的资源被转移
    forget<Resource>(r); //此时 forget 函数会获取 r 的所有权，但是并不会调用 Resource 的析构函数来释放堆内存
}

int main() {
    char val[sizeof(Resource)];
    get_resource(val);
    return 0;
}
```

### 安全数据结构

#### `Vec`

`Vec`是 BiShengC 语言提供的安全动态数组类型,数组元素的数据存储在堆上，它是一个泛型数据结构，接受一个类型参数 T 表示其内部存储的数据的类型，其使用示例如下：

```c
#include "vec.hbs"

safe void example(void) {
    Vec<int> vec = Vec<int>::new(); // 分配一个空的动态数组
    vec.push(1); // 向数组中插入元素
    vec.push(2); // 向数组中插入元素

    size_t len = vec.length();
    int elem = *vec.get(0); // elem is 1

    vec.set(0, 7); // 将索引为0处的值置为7
    elem = *vec.get(0); // elem is 7

    vec.shrink_to_fit();
    // vec作用域结束时自动调用析构函数释放堆内存空间,无需手动释放
}
```

索引：
`Vec`目前不支持直接使用索引进行访问，但其提供了`set`和`get`等方法,可以传入想要访问的元素的索引，通过函数调用的方式进行访问。

容量及重新分配：
`Vec`的容量是为将来添加到`Vec`中的任何元素预先分配的内存空间大小，不要将其与`Vec`的长度向混淆，`Vec`的长度表示的是当前`Vec`内实际存储的元素的数量。
如果`Vec`的长度超过其容量，则容量会自动增长，且其元素也需要重新分配(这由Vec内部实现)。

注意：在使用`Vec<T>`时，需要保证 T 是 copy 语义的类型或 owned struct 类型，否则会编译期报错，因为对于其它类型，编译器无法知道应该如何清理内存。

`Vec`提供的对外接口及相应的使用用例如下：

|对外接口|接口功能|代码示例|
|---|---|---|
|`safe size_t Vec<T>::capacity(const Vec<T>* borrow this)`|返回数组的容量|size_t cap = vec.capacity();|
|`safe void Vec<T>::clear(Vec<T>* borrow this)`|清空数组的所有元素|vec.clear();|
|`safe const T* borrow Vec<T>::get(const Vec<T>* borrow this, size_t index)`|获取数组中下标为index的元素的不可变借用(**要做边界检查**)|const int* borrow elem = vec.get(2);|
|`safe T* borrow Vec<T>::get_mut(Vec<T>* borrow this, size_t index)`|获取数组中下标为index的元素的可变借用(**要做边界检查**)|int* borrow elem = vec.get_mut(2);|
|`safe _Bool Vec<T>::is_empty(const Vec<T>* borrow this)`|判断数组是否为空|_Bool flag = vec.is_empty();|
|`safe size_t Vec<T>::length(const Vec<T>* borrow this)`|返回数组的长度|size_t len = vec.length();|
|`safe Vec<T> Vec<T>::new(void)`|创建一个空的数组|Vec<int> vec = Vec<int>::new();|
|`safe T Vec<T>::pop(Vec<T>* borrow this)`|弹出数组中最后一个元素(**要做边界检查**)|int last = vec.pop();|
|`safe void Vec<T>::push(Vec<T>* borrow this, T value)`|向数组的尾部插入一个值为value的元素|vec.push(2);|
|`safe T Vec<T>::remove(Vec<T>* borrow this, size_t index)`|从数组中移除下标为index的元素(**要做边界检查**)|int m = vec.remove(3);|
|`safe void Vec<T>::set(Vec<T>* borrow this, size_t index, T value)`|将数组中下标为index的元素置为value(**要做边界检查**)|vec.set(3, 5);|
|`safe void Vec<T>::shrink_to_fit(Vec<T>* borrow this)`|调整数组占用的内存空间,将容量缩减到数组的长度|vec.shrink_to_fit();|
|`safe Vec<T> Vec<T>::with_capacity(size_t cap)`|创建一个容量为cap的空数组|Vec<int> vec = Vec<int>::with_capacity(120);|

注：`Vec`提供的安全 API 内部实现了严格的边界访问检查逻辑，确保在使用这些 API 时不会出现越界访问的问题。当发生越界访问时，程序打印当前的函数调用栈，并终止执行。

#### `String`

`String`是 BiShengC 语言提供的 C 风格的安全字符串类型，用于安全地管理分配在堆上的字符串。它拥有字符串内容的所有权，字符串的内容存储在堆分配的缓冲区中。其使用示例如下：

```c
String hello = String::from("Hello, world!");

hello.push('w');
hello.set(0, 'k');

String world = String::from("hello bishengc");
hello.equals(&const world);

String new_s = world.slice(1, 4);
```

内部表示：
`String`内部由三个部分组成：指向某些字节的指针、长度和容量。该指针指向`String`用于存储其数据的内部缓冲区，长度是当前存储在缓冲区中的字节数，容量是当前缓冲区的大小（以字节为单位）。因此，长度会始终小于或等于容量。存储字节的缓冲区始终分配在堆上。

`String`提供的对外接口及相应的使用用例如下：

|对外接口|接口功能|代码示例|
|---|---|---|
|`safe char* borrow String::as_mut_str(String* borrow this)`|返回对字符串的可变借用|char* borrow str = s.as_mut_str();|
|`safe const char* borrow String::as_str(const String* borrow this)`|返回对字符串的不可变借用|const char* borrow str = s.as_str();|
|`safe char String::at(const String* borrow this, size_t index)`|返回字符串的下标为index处的值（**要做边界检查**）|char c = s.at(2);|
|`safe size_t String::capacity(const String* borrow this)`|返回字符串的容量|size_t cap = s.capacity();|
|`safe _Bool String::equals(const String* borrow this, const String* borrow other);`|比较两个字符串是否相等|_Bool flag = str1.equals(str2);|
|`safe size_t String::find(const String* borrow this, char c)`|查找字符串中是否有字符c，返回第一次找到时的下标，如果没有找到，则返回bsc_string_no_pos|size_t pos = s.find('A');|
|`unsafe String String::from(const char* str)`|根据字符串字面量创建字符串|String s = String::from("hello");|
|`safe const T* borrow String::get(const String* borrow this, size_t index)`|获取字符串中下标为index的元素的不可变借用(**要做边界检查**)|const char* borrow elem = s.get(2);|
|`safe T* borrow String::get_mut(String* borrow this, size_t index)`|获取字符串中下标为index的元素的可变借用(**要做边界检查**)|char* borrow elem = s.get_mut(2);|
|`safe _Bool String::is_empty(const String* borrow this)`|判断字符串是否为空|_Bool flag = s.is_empty();|
|`safe size_t String::length(const String* borrow this)`|返回字符串的长度|size_t len = s.length();|
|`safe String String::new(void)`|创建一个空的字符串|String s = String::new();|
|`safe void String::push(String* borrow this, char value)`|向字符串的尾部插入一个值为value的元素|s.push('h');|
|`safe void String::set(String* borrow this, size_t index, char value)`|将字符串中下标为index的元素置为value(**要做边界检查**)|s.set(3, '5');|
|`safe void String::shrink_to_fit(String* borrow this)`|调整字符串占用的内存空间,将容量缩减到字符串的长度|s.shrink_to_fit();|
|`safe String String::slice(const String* borrow this, size_t start, size_t length);`|字符串切片，如果 start 大于字符串的长度，则会触发越界；对于 length，如果start + length 大于字符串的长度，则字符串切片只会取到字符串的结尾处|String new_string = s.slice(0, 5);|
|`safe String String::with_capacity(size_t cap)`|创建一个容量为cap的空字符串|String s = String::with_capacity(20);|

注：`bsc_string_no_pos`实际上是一个很大的 size_t 类型的值，即 SIZE_MAX。


#### LinkedList

##### 概述：

LinkedList是由双向链表来实现的，支持前后两种移动方向。

注意：在使用`LinkedList<T>`时，需要保证 T 是 copy 语义的类型或 owned struct 类型，否则会编译期报错，因为对于其它类型，编译器无法知道应该如何清理内存。

##### 头文件:

```c
#include "list.hbs"
```

##### API:

| 对外接口                                             | 接口功能                                                     | 代码示例                                                     |
| ---------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| LinkedList<T> LinkedList<T>::new()                   | 创建一个链表对象。                                           | #include "list.hbs"<br />// 新增int类型链表对象<br />LinkedList<int> list = LinkedList<int>::new(); |
| void LinkedList<T>::push_back(T el)                  | 向链表尾端插入一个数据。                                     | list.push_back(5); // 向链表尾插入数据5                      |
| void LinkedList<T>::push_front(T el)                 | 向链表表头插入一个数据。                                     | list.push_front(6); // 向链表头插入数据6                     |
| size_t LinkedList<T>::length()                       | 返回链表中已有数据个数。                                     | assert(2 == list.length());                                  |
| _Bool LinkedList<T>::is_empty()                      | 判断表是否为空表。                                           | list.push_back(4); <br />assert(0 == list.is_empty())        |
| T LinkedList<T>::pop_back()                          | 返回表尾数据，并将该数据从链表中删除。表不可以为空表。       | assert(5 == list.pop_back());                                |
| T LinkedList<T>::pop_front()                         | 返回表头数据，并将该数据从链表中删除。表不可以为空表。       | assert(6 == list.pop_front());                               |
| void LinkedList<T>::remove(T el)                     | 删除链表中所有指定数据。                                     | list.push_back(4);<br />list.remove(4); // 删除链表中所有值为4的元素 |
| void LinkedList<T>::clear()                          | 删除链表中所有数据。                                         | list.clear();                                                |
| T LinkedList<T>::front()                             | 返回表头数据，表不可以为空表。                               | list.push_front(3);<br />assert(3 == list.front())           |
| T LinkedList<T>::back()                              | 返回表尾数据，表不可以为空表。                               | list.push_back(3); <br />assert(3 == list.back())            |
| _Bool LinkedList<T>::contains(T el)                  | 检查表是否包含指定数据。                                     | list.push_back(6); <br />assert(1 == list.contains(6))       |
| LinkedList<T> LinkedList<T>::split_off(size_t index) | 在索引处将链表拆分为两个链表，<br />索引值不能大于链表中数据个数，<br />新链表包含索引值以及往后的数据。<br />若索引值为0，则旧链表将为空表，<br />若索引值等于表数据个数，则新链表将为空。 | LinkedList<int> l = LinkedList<int>::new();<br />l.push_back(5);<br />l.push_back(6);<br />l.push_front(4);<br />l.push_front(3);<br />LinkedList<int> j = l.split_off(2);<br />// 链表被拆为l和j两个表<br />assert(2 == l.length());      // 3 4<br />assert(2 == j.length());      // 5 6 |

#### `Option`

`Option`是 BiShengC 语言提供的用于处理可选值的一个安全数据结构，用来表示一个值可能存在或不存在这两种情况。
它是一个泛型数据结构，具有一个泛型参数`T`，用于表示其存储的可选值的类型。使用`Option`可以安全地处理一些函数的返回值，避免使用空指针等数据结构来表示一个值不存在的情况。
`Option`有两种状态，即`Some`和`None`，`Some`状态中会包含所需要的类型的值，而`None`状态中没有存储相应的值。
它的一个使用示例如下：

```c
#include "option.hbs" // Option类型声明在该头文件中，使用时需包含该头文件

Option<size_t> string_find(String str) {
    size_t pos = str.find('k');
    if (pos == bsc_string_no_pos) {
        return Option<size_t>::None(); // 如果没有找到k，则返回None
    } else {
        return Option<size_t>::Some(pos); // 如果找到了k，则返回Some，且Some中包含相应的值pos
    }
}

void use_option() {
    size_t pos = -1;
    String s = String::from("hello");
    Option<size_t> res = string_find(s);
    if (res.is_some()) { // 判断res是Some还是None
        pos = option_unwrap(res); // 对于Some，则调用option_unwrap获取其中的值
    } else {
        return; // 对于None，则不做处理
    }
}
```

这个例子中首先定义了一个函数`string_find`，对`String`的`find`方法进行了封装，用于处理找到字符k和没有找到字符k的情况。接下来在使用处，可以使用`is_some`方法处理返回的`Option<size_t>`类型的值，从而获取里面的数据或者不做处理。这种写法可以安全地处理一些函数的返回值，提高程序的安全性。

`Option`是一个owned struct类型的数据结构，因此其自带析构函数，可以安全地释放其所占用的内存空间，无需使用者进行手动内存释放。

注意：在使用`Option<T>`时，需要保证 T 是 copy 语义的类型或 owned struct 类型，否则会编译期报错，因为对于其它类型，编译器无法知道应该如何清理内存。

`Option`提供的对外接口及相应的使用用例如下：

|对外接口|接口功能|代码示例|
|---|---|---|
|`safe _Bool Option<T>::is_none(const Option<T>* borrow this)`|判断`Option`是否为`None`，若是则返回1，否则返回0|_Bool flag = option.is_none();|
|`safe _Bool Option<T>::is_some(const Option<T>* borrow this)`|判断`Option`是否为`Some`，若是则返回1，否则返回0|_Bool falg = option.is_some();|
|`safe Option<T> Option<T>::Some(T t)`|创建一个状态为`Some`的`Option`值，其中包含的`T`类型的结果的值为`t`|Option<size_t> option = Option<size_t>::Some(3);|
|`safe Option<T> Option<T>::None(void)`|创建一个状态为`None`的`Option`值，其中不包含`T`的类型的结果值|Option<size_t> option = Option<size_t>::None();|
|`safe T option_unwrap<T>(Option<T> option)`|展开option，从中取出存储的T类型的值，对于`Some`可以成功取出`T`类型的值，对于`None`则会导致运行时终止|size_t index = option_unwrap(option);|

注：`option_unwrap`函数并非`Option`类型的成员方法，且其再展开`None`时会运行时终止，因此建议在调用该函数前使用`is_some`或`is_none`对`Option`的状态先进行判断。

#### `HashMap`

`HashMap`是 BiShengC 语言提供的安全哈希表类型，哈希表的键和值都存储在堆上，它是一个泛型数据结构，具有三个泛型参数`K`、`V`和`S`。
其中`K`代表的是键的类型，`V`代表的是值的类型，而`S`代表的是该`HashMap`所使用的哈希函数。

我们可以用各种类型来作为键的类型，包含除float和double以外的各种基本类型，以及自定义的数据类型。
在将一个类型作为键的类型时，该类型必须实现了`hash`和`equals`这两个方法。BiShengC 已经为基本类型提供了这两个方法，无需使用者再次手动实现。

注意：在使用`HashMap<K, V>`时，需要保证 K 和 V 是 copy 语义的类型或 owned struct 类型，否则会编译期报错，因为对于其它类型，编译器无法知道应该如何清理内存。

对于哈希函数，BiShengC 提供了一个`SipHasher13`作为默认的哈希函数。该类型有两个方法用于创建其实例：

|对外接口|接口功能|代码示例|
|---|---|---|
|`SipHasher13 SipHasher13::new()`|创建默认的`SipHasher13`|SipHasher13 sh = SipHasher13::new();|
|`SipHasher13 SipHasher13::new_with_keys(uint64_t key0, uint64_t key1)`|使用`key0`和`key1`创建`SipHasher13`，BiShengC 还提供了`RandomState`类型，用于创建随机的`key0`和`key1`值|RandomState rs = RandomState::new();<br/>SipHasher13 sh = SipHasher13::new_with_keys(rs.k0, rs.k1);|

`HashMap`的一个使用实例如下：

```c
#include "hash_map.hbs" // HashMap类型声明在该头文件中，使用时需包含该头文件

// 使用HashMap来统计一个数组中各个值出现的次数
void hash_map_example(Vec<int> vec) {
    HashMap<int, int, SipHasher13> map = HashMap<int, int, SipHasher13>::with_hasher(SipHasher13::new()); // 创建HashMap

    for (size_t i = 0; i < vec.length(); i++) {
        const int* borrow cur = vec.get(i);
        if (map.contains_key(cur)) { // 判断map中是否已经有cur
            int* borrow v = map.get_mut(cur); // 获取键对应的值的可变借用
            *v = *v + 1; // 更新相应的值
        } else {
            int k = *cur;
            map.insert(k, 1); // 向map中插入键值对
        }
    }

    _Bool empty_flag = map.is_empty(); // 判断map是否为空
    int x = 3;
    _Bool key_flag = map.contains_key(&const x); // 判断map是否有键3
    Option<int> removed = map.remove(&const x);
    if (removed.is_some()) {
        int v = option_unwrap(removed);
    }
    map.clear(); // 清空map的所有元素
}
```

`HashMap`提供的对外接口及相应的使用用例如下：

|对外接口|接口功能|代码示例|
|---|---|---|
|`safe size_t HashMap<K, V, S>::capacity(const HashMap<K, V, S>* borrow this)`|返回哈希表的容量|size_t cap = map.capacity();|
|`safe void HashMap<K, V, S>::clear(HashMap<K, V, S>* borrow this)`|清空哈希表的所有键值对，但表的容量保持不变|map.clear();|
|`safe _Bool HashMap<K, V, S>::contains_key(const HashMap<K, V, S>* borrow this, const K* borrow k)`|判断哈希表是否存在值为\*k的键|int x = 1;<br/>_Bool flag = map.contains_key(&const x);|
|`safe Option<V* borrow> HashMap<K, V, S>::get_mut(HashMap<K, V, S>* borrow this, const K* borrow k)`|获取值为\*k的键对应的值的可变借用，若表中不存在键\*k，则返回None|int x = 1;<br/>int* borrow v = map.get_mut(&const x);|
|`safe void HashMap<K, V, S>::reserve(HashMap<K, V, S>* borrow this, size_t additional)`|调整哈希表的容量，使其调整后在不扩容的情况下能至少再存入additional个元素（一般来说，该方法无需手动调用，在调用insert时会被隐式调用一次）|map.reserve(1);|
|`safe Option<V> HashMap<K, V, S>::insert(HashMap<K, V, S>* borrow this, K k, V v)`|向哈希表中插入键为k、值为v的键值对|map.insert(1, 2);|
|`safe _Bool HashMap<K, V, S>::is_empty(const HashMap<K, V, S>* borrow this)`|判断哈希表是否为空|_Bool empty map.is_empty();|
|`safe size_t HashMap<K, V, S>::length(const HashMap<K, V, S>* borrow this)`|返回哈希表中存储的键值对的数量|size_t len = map.length();|
|`safe Option<V> HashMap<K, V, S>::remove(HashMap<K, V, S>* borrow this, const K* borrow k)`|从哈希表中移除键为\*k的键值对，并返回对应的值，如果哈希表不存在键\*k，则返回None|int x = 3;<br/>Option<int> removed = map.remove(&const x);<br/>if (removed.is_some()) { int y = option_unwrap(removed); }|
|`safe HashMap<K, V, S> HashMap<K, V, S>::with_capacity_and_hasher(size_t cap, S hash_builder)`|创建初始容量为cap、哈希函数为hash_builder的哈希表|HashMap<int, int, SipHasher13> map = HashMap<int, int, SipHasher13>::new_with_cap_and_hasher(3, SipHasher13::new());|
|`safe HashMap<K, V, S> HashMap<K, V, S>::with_hasher(S hash_builder)`|创建初始容量为0，哈希函数为hash_builder的哈希表|HashMap<int, int, SipHasher13> map = HashMap<int, int, SipHasher13>::new_with_hasher(SipHasher13::new());|

### Rc
#### 概述
BiShengC 的所有权机制要求一个值只能有一个所有者，然而，我们考虑以下场景：
1. 在图数据结构中，多个边可能指向相同的节点，这个节点为所有指向它的边所共有，该节点直到没有边指向它时，才能被释放清理
2. 当我们希望在堆上分配一些内存供程序的多个部分读取，而且无法在编译时确定程序的哪一部分会最后结束使用它的时候，这部分内存直到最后一个部分使用结束时，才能被释放清理

为解决此类问题，需要允许一个值在同一时刻拥有多个所有者，因此 BSC **在标准库中提供 `Rc<T>` 类型来实现所有权的共享，它是一种智能指针，指向被共享的数据**。为提高 Rc 的安全性，BSC 同时提供了 `Weak<T>` 来避免循环引用造成的内存泄漏问题，也提供了 `Cell<T>` 和 `RefCell<T>` 与 Rc 组合使用来实现 Rc 指向数据的可变性。

#### 使用 `Rc<T>` 共享数据
Rc 是引用计数（reference counting）的缩写，通过记录数据被引用的次数，来确定数据是否正在被使用，引用的数量就相当于所有者的数量。**如果引用计数变为 0，就意味着被引用数据可以被清理，此时 Rc 会自动调用数据的析构函数，避免内存泄漏。**

注意：在使用 `Rc<T>` 时，需要保证 T 是 copy 语义的类型或 owned struct 类型，否则会编译期报错，因为对于其它类型，编译器无法知道应该如何清理内存。

`Rc<T>` 的使用方法是：
1. 调用 new 方法来创建 Rc，该方法会分配堆内存，并将所要引用的数据存储在堆上
2. 调用 clone 方法可以从已有 Rc 得到另一个 Rc，该方法不执行深拷贝，仅仅创建另一个指向被引用数据的指针
3. 调用 deref 方法可以获取 Rc 所指向数据的不可变借用

我们通过以下的例子来学习 Rc 的使用：
假如一个班上有若干学生，他们共享一份成绩单，这份成绩记录文件就是需要被共享的数据资源，现在我们读取该文件来获取 1 号学生和 2 号学生的成绩：
```C
#include "rc.hbs"

owned struct ScoreRecord {  //学生成绩记录文件
    FILE *fp;
    ~ScoreRecord(This this) {
        fclose(this.fp);
    }
};

owned struct Student {
    unsigned student_id;    //学生id
    Rc<ScoreRecord> scores; //假设学生成绩记录文件为所有学生所共有
};

// 打开文件
ScoreRecord ScoreRecord::open(String filename);
// 读取文件第 id 行内容
String ScoreRecord::read(const This *borrow this, unsigned id);

// 获取 id 号学生的成绩
String Student::get_score(const This *borrow this) {
    const ScoreRecord *borrow scores = this->scores.deref(); 
    return scores->read(this->id);
}

int main() {
    ScoreRecord scores = ScoreRecord::open(String::from("scores.txt"));

    // student1 和 student2 共同拥有成绩文件的所有权
    Rc<ScoreRecord> rc1 = Rc<ScoreRecord>::new(scores);
    Rc<ScoreRecord> rc2 = rc1.clone()；
    Student student1 = { .id = 1, .scores = rc1 };
    Student student2 = { .id = 2, .scores = rc2 };
    // 此时共享文件的引用计数为 2，因为它有 2 个所有者

    print("学生1的成绩为：" + student1.get_score());
    print("学生2的成绩为：" + student2.get_score());

    return 0;
}   // 共享文件被使用完毕，引用计数变为 0，此时 Rc 会自动调用 ～ScoreRecord 来关闭文件
```

#### 引用计数
让我们通过以下案例来观察 `Rc<T>` 在创建、克隆和走出作用域时引用计数的变化。
```C
int main() {
    Rc<int> rc1 = Rc<int>::new(5);
    printf("ref count after creating rc1 = %d\n", rc1.strong_ref_count());
    Rc<int> rc2 = rc1.clone();
    printf("ref count after creating rc2 = %d\n", rc1.strong_ref_count());
    {
        Rc<int> rc3 = rc1.clone();
        printf("ref count after creating rc3 = %d\n", rc1.strong_ref_count());
    }
    printf("ref count after rc3 goes out of scope = %d\n", rc1.strong_ref_count());
    return 0;
}
```
这段代码会打印出：
```
ref count after creating rc1 = 1
ref count after creating rc2 = 2
ref count after creating rc3 = 3
ref count after rc3 goes out of scope = 2
```
我们能够看到 rc1 的初始引用计数为 1，随着每次调用 clone，计数会增加 1。当 rc3 离开作用域时，计数减 1。不必像调用 clone 增加引用计数那样调用一个函数来减少计数，因为 `Rc<T>` 析构函数的实现可以保证当一个 Rc 离开作用域时自动减少引用计数。

从这个例子我们所不能看到的是，在 ref_count 函数的结尾处，随着 rc1、rc2 离开作用域，计数会降为 0，其指向的数据也将被清理，这一清理操作也是通过 `Rc<T>` 的析构函数来自动实现的。

#### `Cell<T>`/`RefCell<T>` 与内部可变性

通过 deref 方法可以获取 Rc 所指向数据的不可变借用，这允许在程序的多个部分之间只读地共享数据。如果 `Rc<T>` 也允许多个可变借用，会违反 BSC 的借用规则：不能同时存在对同一数据的多个可变借用。但是在实际应用场景，修改数据是不可避免的。在这一部分，我们将讨论内部可变性模式和 Cell/RefCell 类型，它们**可以与 Rc 结合使用来修改 Rc 所指向的数据**。

BSC 编译器会在编译时对借用规则进行严格的检查，它可能会拒绝一个正确的程序，这往往会让用户痛苦不堪。因此在标准库中提供了 `Cell<T>` 和 `RefCell<T>` 来实现内部可变性：在拥有不可变借用的同时修改目标数据！对于正常的代码实现来说，这个是不可能做到的（要么一个可变借用，要么多个不可变借用）。

##### `Cell<T>`
`Cell<T>` 用于获取它内部包裹的值的拷贝或直接修改内部值，适用于 Copy 语义的类型，例如 int、float 等基本数据类型或 struct 类型。
```C
void cell_example() {
    Cell<int> c = Cell<int>::new(5);
    printf("Value in cell is: %d\n", c.get()); // get 方法可以获取 cell 内部包裹的值的拷贝
    c.set(10);   // set 方法可以直接修改 cell 内部包裹的值
    printf("Value in cell is: %d\n", c.get());
}
```
##### `RefCell<T>`
`RefCell<T>` 用于获取它内部包裹的值的可变或不可变借用，它实际上**并没有解决可变借用和不可变借用可以共存的问题，只是将报错从编译期推迟到运行时 abort**。

通过使用 `RefCell<T>` 的 borrow_mut 和 borrow_immut 方法，来尝试在运行时获取借用，如果借用成功，返回 `RefMut<T>` 或 `RefImmut<T>` 类型的值，否则会导致运行时 abort。规则是：
1. borrow_mut 方法用于获取 `RefMut<T>`，如果当前作用域内存在**任何其它借用**，则借用失败
2. borrow_immut 方法用于获取 `RefImmut<T>`，如果当前作用域存在**任何其它可变借用**，则借用失败

`RefMut<T>` 和 `RefImmut<T>` 是 `RefCell<T>` 的辅助数据结构，它们的 deref 方法可以分别获取 RefCell 内部值的可变和不可变借用。
```C
void refcell_example() {
    RefCell<int> c = RefCell<int>::new(5);

    // 通过 RefCell 的 borrow_mut 方法获得 RefMut：
    RefMut<int> ref_mut_c1 = c.borrow_mut();

    // 通过 RefMut 的 deref 方法获得 RefCell 内部值的可变借用：
    int* borrow mut_p1 = ref_mut_c.deref();

    // 通过可变借用修改内部值：
    *mut_p1 = 10;  

    // 再次尝试获取可变借用
    RefMut<int> ref_mut_c2 = c.borrow_mut(); //运行时abort，因为同时存在两个可变借用
}
```
#### Rc 和 RefCell 相结合来实现共享数据的修改
上面的读取学生成绩的案例我们只对数据进行了读操作，有了 RefCell，我们可以实现对共享数据的修改，以下例子实现了对成绩数据的读取和更新：
```C
#include "rc.hbs"
#include "cell.hbs"

owned struct ScoreRecord {  //学生成绩记录文件
    FILE *fp;
    ~ScoreRecord(This this) {
        fclose(this.fp);
    }
};

owned struct Student {
    unsigned student_id;
    Rc<RefCell<ScoreRecord>> scores; //将需要被修改的共享数据用 RefCell 进行包装
};

// 打开文件
ScoreRecord ScoreRecord::open(String filename);
// 读取文件第 id 行内容
String ScoreRecord::read(const This *borrow this, unsigned id);
// 更新文件第 id 行内容
void ScoreRecord::update(This *borrow this, unsigned id, String new);

// 获取 id 号学生的成绩
String Student::get_score(const This *borrow this) {
    // RefCell 的 borrow_immut 方法获取不可变借用
    RefImmut<ScoreRecord> ref_scores = this->scores.deref()->borrow_immut(); 
    const ScoreRecord *borrow scores = ref_scores.deref();
    return scores->read(this->id);
}

// 更新 id 号学生的成绩
String Student::update_score(const This *borrow this, String new_score) {
    // RefCell 的 borrow_mut 方法获取可变借用
    RefMut<ScoreRecord> ref_scores = this->scores.deref()->borrow_mut(); 
    ScoreRecord *borrow scores = ref_scores.deref();
    return scores->update(this->id, new_score);
}

int main() {
    ScoreRecord scores = ScoreRecord::open(String::from("scores.txt"));

    Rc<RefCell<ScoreRecord>> rc1 = Rc<RefCell<ScoreRecord>>::new(RefCell<ScoreRecord>::new(scores));
    Rc<RefCell<ScoreRecord>> rc2 = rc1.clone()；
    Student student1 = { .id = 1, .scores = rc1 };
    Student student2 = { .id = 2, .scores = rc2 };

    student1.update_score(String::from("100"));
    student2.update_score(String::from("99"));

    print("学生1的成绩为：" + student1.get_score());
    print("学生2的成绩为：" + student2.get_score());

    return 0;
}
```

#### `Weak<T>` 解决循环引用问题
尽管 BSC 有着完善的内存安全保障机制，但是不代表不会产生内存泄漏。一个典型的例子就是同时使用 `Rc<T>` 和  `RefCell<T>` 创建循环引用，由于引用计数无法被归零，因此 `Rc<T>` 指向的数据也就不会被释放清理。

##### 制造循环引用
```C
#include "rc.hbs"
#include "cell.hbs"

owned struct B;

owned struct A {
public:
    int value;
    RefCell<Rc<B>> c;
    ~A(A this) {
        printf("A is destructed, value = %d\n", this.value);
    }
};

owned struct B {
public:
    int value;
    RefCell<Rc<A>> d;
    ~B(B this) {
        printf("B is destructed, value = %d\n", this.value);
    }
};

int main() {
    A a = { .value = 5 };
    Rc<A> ap = Rc<A>::new(a);      //ap 拥有 a

    B b = { .value = 10 };
    RefMut<Rc<A>> rm_b = b.d.borrow_mut();
    *(rm_b.deref()) = ap.clone();  //通过 ap 的克隆，此处 b.d 拥有了 a
    Rc<B> bp = Rc<B>::new(b);      //bp 拥有 b

    RefMut<Rc<B>> rm_a = ap.deref()->c.borrow_mut();
    *(rm_a.deref()) = bp.clone();  //通过 bp 的克隆，此处 a.c 拥有了 b

    printf("ref count of a : %d\n", ap.strong_ref_count());
    printf("ref count of b : %d\n", bp.strong_ref_count());

    return 0;
}
```
这段代码会打印出：
```
ref count of a : 2
ref count of b : 2
```
在函数结束前，a 和 b 的引用计数都为 2，其中 a 为 ap 和 b.d 所共有，b 为 bp 和 a.c 所共有。

在函数结束处：
1. 对 a 来说，ap 走出作用域后 a 的引用计数由 2 变为 1，只有当 b.d 析构会使 a 的引用计数减为 0 从而触发 a 的析构
2. 对 b 来说，bp 走出作用域后 b 的引用计数由 2 变为 1，只有当 a.c 析构会使 b 的引用计数减为 0 从而触发 b 的析构

a 的析构需要 b 先被析构，而 b 的析构需要 a 先被析构，结果就是 a 和 b 都没有被析构，内存泄漏了！

##### 使用 `Weak<T>` 解决循环引用
为解决这一问题，BSC 引入 `Weak<T>` 类型，与 Rc 持有所有权不同，Weak 不持有所有权，它仅仅保存一份指向数据的弱引用，**建立弱引用不会增加引用计数，它也无法阻止所引用的数据被清理掉**。

`Weak<T>` 的使用方法是：
1. 调用 new 方法，通过一个已有的 `Rc<T>` 创建 `Weak<T>`
2. 无法通过 `Weak<T>` 直接访问被引用数据，如果想要访问数据，需要将 Weak 升级为 Rc，这通过 Weak 的 upgrade 方法实现，该方法返回一个类型为 `Option<Rc<T>>` 的值，如果被引用数据已经被清理释放，则 Option 的值是 None，也就是说，Weak 本身不对被引用数据的存在性做任何担保。

##### 循环引用场景 1
我们以上一小节中 a 和 b 循环引用导致内存泄漏的例子来学习`Weak<T>`的使用：
```C
#include "rc.hbs"
#include "cell.hbs"

owned struct B;

owned struct A {
public:
    int value;
    RefCell<Rc<B>> c;     //A 通过 Rc 引用 B
    ~A(A this) {
        printf("A is destructed, value = %d\n", this.value);
    }
};

owned struct B {
public:
    int value;
    RefCell<Weak<A>> d;  //B 通过 Weak 引用 A
    ~B(B this) {
        printf("B is destructed, value = %d\n", this.value);
    }
};

int main() {
    A a = { .value = 5 };
    Rc<A> ap = Rc<A>::new(a);           //ap 拥有 a

    B b = { .value = 10 };
    RefMut<Weak<A>> rm_b = b.d.borrow_mut();
    *(rm_b.deref()) = Weak<A>::new(ap); //通过 ap 创建弱引用，此处 b.d 弱引用 a
    Rc<B> bp = Rc<B>::new(b);           //bp 拥有 b

    RefMut<Rc<B>> rm_a = ap.deref()->c.borrow_mut();
    *(rm_a.deref()) = bp.clone();       //通过 bp 的克隆，此处 a.c 拥有了 b

    printf("ref count of a : %d\n", ap.strong_ref_count());
    printf("ref count of b : %d\n", bp.strong_ref_count());

    return 0;
}
```
这段代码会打印出：
```
ref count of a : 1
ref count of b : 2
B is destructed, value = 10
A is destructed, value = 5
```
通过打印结果，我们看到 a 和 b 都被析构了，分析这段代码：
1. 在函数结束前，a 为 ap 所拥有，引用计数为 1，b 为 bp 和 a.c 所共有，引用计数为 2；
2. 在函数结束处，ap 走出作用域后 a 的引用计数由 1 变为 0，从而触发 a 的析构，因为 a.c 拥有 b，随着 a 的析构，b 的引用计数由 2 减为 1；随后 bp 走出作用域后 b 的引用计数由 1 变为 0，从而触发 b 的析构。

##### 循环引用场景 2
Weak 常常被应用于父子循环引用关系中，做法是：让父节点通过 Rc 来引用子节点，然后让子节点通过 Weak 来引用父节点。接下来我们构造一个简单的 tree，它有 1 个 root 节点和 2 个 leaf 节点：
```C
owned struct Node {
public:
    int value;
    RefCell<Weak<Node>> parent;      //子结点通过 Weak 引用父节点
    RefCell<Vec<Rc<Node>>> children; //父结点通过 Rc 引用子节点
	
    ~Node(Node this) {
        printf("node %d is destructed\n", this.value);
    }
};

void tree() {
    // 构造叶子节点
    Node temp_leaf1 = { .value = 5, .children = RefCell<Vec<Rc<Node>>>::new(Vec<Rc<Node>>::new()) };
    Node temp_leaf2 = { .value = 6, .children = RefCell<Vec<Rc<Node>>>::new(Vec<Rc<Node>>::new()) };
    Rc<Node> leaf1 = Rc<Node>::new(temp_leaf1);
    Rc<Node> leaf2 = Rc<Node>::new(temp_leaf2);

    printf("ref count of leaf1 after init : %d\n", leaf1.strong_ref_count());
    printf("ref count of leaf2 after init : %d\n", leaf2.strong_ref_count());

    // 构造父节点，并让父结点通过 Rc 引用子节点
    Node temp_root = { .value = 10, .children = RefCell<Vec<Rc<Node>>>::new(Vec<Rc<Node>>::new()) };
    RefMut<Vec<Rc<Node>>> rm_root_children = temp_root.children.borrow_mut();
    rm_root_children.deref()->push(leaf1.clone());
    rm_root_children.deref()->push(leaf2.clone());
    Rc<Node> root = Rc<Node>::new(temp_root);

    printf("ref count of root after init : %d\n", root.strong_ref_count());
    printf("ref count of leaf1 after root points to it : %d\n", leaf1.strong_ref_count());
    printf("ref count of leaf2 after root points to it : %d\n", leaf2.strong_ref_count());

    // 子结点通过 Weak 引用父节点
    RefMut<Weak<Node>> rm_leaf1_parent = leaf1.deref()->parent.borrow_mut();
    *(rm_leaf1_parent.deref()) = Weak<Node>::new(&const root);
    RefMut<Weak<Node>> rm_leaf2_parent = leaf2.deref()->parent.borrow_mut();
    *(rm_leaf2_parent.deref()) = Weak<Node>::new(&const root);

    printf("ref count of root after leaf1 and leaf2 weakly points to it : %d\n", root.strong_ref_count());
}
```
这段代码会打印出：
```
ref count of leaf1 after init : 1
ref count of leaf2 after init : 1
ref count of root after init : 1
ref count of leaf1 after root points to it : 2
ref count of leaf2 after root points to it : 2
ref count of root after leaf1 and leaf2 weakly points to it : 1
node 5 is destructed
node 6 is destructed
node 10 is destructed
```
通过打印结果可以看到所有的节点数据都被清理释放。

#### 相关 API
##### `Rc<T>` 对外接口
|对外接口|接口功能|代码示例|
|---|---|---|
|`safe Rc<T> Rc<T>::new(T data)`|构造一个 Rc，开辟堆内存存储 data|`Rc<int> rc = Rc<int>::new(5);`|
|`safe Rc<T> Rc<T>::clone(const This * borrow this)`|通过一个已有 Rc，克隆出另一个 Rc，会使引用计数加 1|`Rc<int> rc2 = rc.clone();`|
|`safe unsigned Rc<T>::strong_ref_count(const This * borrow this)`|获取强引用计数|`unsigned count = rc.strong_ref_count();`|
|`safe unsigned Rc<T>::weak_ref_count(const This * borrow this)`|获取弱引用计数|`unsigned count = rc.weak_ref_count();`|
|`safe const T * borrow Rc<T>::deref(const This * borrow this)`|获取 Rc 指向数据的不可变借用|`const int * borrow data = rc.deref();`|

##### `Weak<T>` 对外接口
|对外接口|接口功能|代码示例|
|---|---|---|
|`safe Weak<T> Weak<T>::new(const Rc<T> * borrow rc)`|通过一个已有 Rc，构造出一个 Weak|`Weak<int> w = Weak<int>::new(&const rc);`|
|`safe Weak<T> Weak<T>::clone(const This * borrow this)`|通过一个已有 Weak，克隆出另一个 Weak|`Weak<int> w2 = w.clone();`|
|`safe unsigned Weak<T>::strong_ref_count(const This * borrow this)`|获取强引用计数|`unsigned count = w.strong_ref_count();`|
|`safe unsigned Weak<T>::weak_ref_count(const This * borrow this)`|获取弱引用计数|`unsigned count = w.weak_ref_count();`|
|`safe Option<Rc<T>> Weak<T>::upgrade(const This * borrow this)`|将 Weak 转化为对应的 Rc，转化失败时返回 None|`Option<Rc<T>> rc = w.upgrade();`|

##### `Cell<T>` 对外接口
|对外接口|接口功能|代码示例|
|---|---|---|
|`safe Cell<T> Cell<T>::new(T value)`|用所给 value 构造 Cell|`Cell<int> c = Cell<int>::new(5);`|
|`safe T Cell<T>::get(const This * borrow this)`|获得 Cell 内部值的拷贝|`int a = c.get();`|
|`safe void Cell<T>::set(const This * borrow this, T val)`|将 Cell 内部值替换为 val|`c.set(10);`|

##### `RefCell<T>` 对外接口
|对外接口|接口功能|代码示例|
|---|---|---|
|`safe RefCell<T> RefCell<T>::new(T value)`|用所给 value 构造 RefCell|`RefCell<int> c = RefCell<int>::new(5);`|
|`safe RefImmut<T> RefCell<T>::borrow_immut(const This * borrow this)`|获得 RefCell 内部值的RefImmut<T>，失败会导致 abort|`RefImmut<int> ref = c.borrow_immut();`|
|`safe Option<RefImmut<T>> RefCell<T>::try_borrow_immut(const This * borrow this)`|获得 RefCell 内部值的 RefImmut<T>，失败会返回 None|`Option<RefImmut<int>> ref = c.try_borrow_immut();`|
|`safe RefMut<T> RefCell<T>::borrow_mut(const This * borrow this)`|获得 RefCell 内部值的 RefMut<T>，失败会导致 abort|`RefMut<int> ref = c.borrow_mut();`|
|`safe Option<RefMut<T>> RefCell<T>::try_borrow_mut(const This * borrow this)`|获得 RefCell 内部值的 RefMut<T>，失败会返回 None|`Option<RefMut<int>> ref = c.try_borrow_mut();`|

##### `RefImmut<T>/RefMut<T>` 对外接口
|对外接口|接口功能|代码示例|
|---|---|---|
|`safe const T * borrow RefImmut<T>::deref(const This * borrow this)`|获取 RefCell 内部值的不可变借用|`const int * borrow p = immut_ref.deref();`|
|`safe T * borrow RefMut<T>::deref(This * borrow this)`|获取 RefCell 内部值的可变借用|`int * borrow p = mut_ref.deref();`|

### 协程调度器

#### Scheduler

##### 概述：

`Scheduler` 是 BiShengC 语言提供的负责协调和管理协程的数据结构，它使用了协程机制来支持高并发的异步编程，主要作用是将可执行的任务分配给可用线程来执行，以最大程度地利用计算机资源。其使用示例如下：

```c
#include <unistd.h>
#include "scheduler.hbs" // 引入头文件

atomic_int g_student_num = 10;

struct Student {
    char * name;
    int age;
    int score;
};

struct Student nameList[] =
{
    {"Mary", 12, 90},
    {"John", 13, 95},
    {"Michael", 12, 93},
    {"Emily", 11, 92},
    {"James", 12, 86},
    {"Emma", 12, 95},
    {"William", 11, 90},
    {"Jessica", 13, 80},
    {"Lily", 12, 92},
    {"Sarah", 12, 88}
};

async void readName(int i) {
    // 模拟 IO 操作，读取学生名单
    printf("name: %s, age: %d, score: %d\n", nameList[i].name, nameList[i].age, nameList[i].score);

    atomic_fetch_sub(&g_student_num, 1);
    // 任务完成，销毁调度器
    if (atomic_load(&g_student_num) == 0) {
        struct Scheduler::destroy();
    }
}

int main() {
    // 初始化，创建 4 个线程
    struct Scheduler::init(4);
    for (int i = 0; i < g_student_num; i++) {
        // 将任务放入执行队列中
        struct Scheduler::spawn(readName(i));
    }
    // 执行调度器
    struct Scheduler::run();
    return 0;
}
```

输出结果如下：

```
name: Mary, age: 12, score: 90
name: Michael, age: 12, score: 93
name: Emily, age: 11, score: 92
name: James, age: 12, score: 86
name: Emma, age: 12, score: 95
name: William, age: 11, score: 90
name: Jessica, age: 13, score: 80
name: Lily, age: 12, score: 92
name: Sarah, age: 12, score: 88
name: John, age: 13, score: 95
```

调度器是一个用于管理和调度任务的工具，`init`方法是在创建调度器对象时调用的，主要用于初始化调度器的一些属性。`spawn` 方法用于创建一个异步任务，并将任务添加到任务队列中**等待执行**。`run` 方法是调度器的核心方法，用于**执行异步任务**。需要注意的一点是，只有当我们调用 `run` 方法时，调度器才会真正的执行任务。`destroy` 方法是在我们不再需要使用调度器时调用的，主要用于清理调度器的一些资源和释放占用的系统资源。

另外，从这个输出结果来看，输出顺序并不是按照数组本身的顺序，并且多次执行输出顺序也可能不同，所以这比较适用于不需要严格要求执行顺序的任务。

##### 头文件:

```c
#include "scheduler.hbs"
```

##### API:

| 对外接口                                                     | 接口功能                                                     | 代码示例                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `void struct Scheduler::init(unsigned int threadCount)`      | 用于初始化调度器，不可多次重复初始化，参数为用户需要创建的线程数 | struct Scheduler::init(4);                                   |
| `struct Task * struct Scheduler::spawn(trait Future<struct Void> * future)` | 创建异步任务，并将任务放入执行队列中等待执行（目前仅接受返回类型是void的任务）。 | async void  taskFunc(int i) { <br/>    while(i < 10000) { <br/>        i = (i * 2) + 3 ; <br/>    }<br/>    printf("result: %d\n", i);<br/>}<br>struct Scheduler::spawn(taskFunc(0)); |
| `void struct Scheduler::run()`                               | 执行通过 spawn 函数创建的异步任务                            | struct Scheduler::run();                                     |
| `void struct Scheduler::destroy()`                           | 销毁调度器，释放资源                                         | struct Scheduler::destroy();                                 |

具体数据结构介绍如下：

`struct Scheduler`：表示调度器，包括任务队列和线程池。通过 `struct Scheduler::init`方法创建并初始，但由于一个进程只能有一个 Scheduler，所以不能重复初始化。当然，也不允许未初始化就直接使用，在调用 `struct Scheduler::spawn` 或  `struct Scheduler::run` 方法前，必须调 `struct Scheduler::init`。如果不再需要调度器了，可以通过 `struct Scheduler::destroy` 方法进行销毁（如果不销毁，进程无法终止）。

`strcut Task`: 表示异步任务，包括任务的状态和执行上下文。通过 `struct Scheduler::spawn` 方法进行创建，创建完成后会将其放入执行队列，但不会立马执行。只有调用了 `struct Scheduler::run` 方法才会真正的执行队列中的任务。

另外，我们注意到 `struct Scheduler::spawn` 方法的入参是 `trait Future<struct Void> *` 类型（`trait Future` 的定义可参考无栈协程章节），所以我们除了可以传入返回类型是 `void` 的 async 函数调用，也可以传显式返回 `trait Futrue<struct Void> *`  类型的函数调用，具体使用如下：

```c
#include "scheduler.hbs"

atomic_int g_task_num = 10;

struct _Futurework {
    int a;
    int __future_state;
};

// 必须实现 poll 和 free 两个函数
struct PollResult<struct Void> struct _Futurework::poll(struct _Futurework *this) {
    switch (this->__future_state) {
      case 0:
        goto __L0;
    }
  __L0:
    ;
    printf("The %d-th calculation begins\n", this->a);
    while (this->a < 100000000)
        {
            this->a++;
        }

    atomic_fetch_sub(&g_task_num, 1);
    if (atomic_load(&g_task_num) == 0) {
        struct Scheduler::destroy();
    }

    this->__future_state = -1;
    struct Void __RES_RETURN = (struct Void){};
    return struct PollResult<struct Void>::completed(__RES_RETURN);
}

void struct _Futurework::free(struct _Futurework *this) {
    if (this != 0) {
        free((void *)this);
        this = (struct _Futurework *)(void *)0;
    }
}

impl trait Future<struct Void> for struct _Futurework;

trait Future<struct Void>* work(int a)     {
  struct _Futurework* ptr = malloc(sizeof(struct _Futurework));
  ptr->a = a;
  ptr->__future_state = 0;
  return ptr;
}

int main() {
    struct Scheduler::init(4);
    for (int i = 0; i < 10; i++) {
        struct Scheduler::spawn(work(i));
    }
    struct Scheduler::run();
    return 0;
}
```




------

## 调试
支持毕昇c的基础调试功能；源源变换到标准c后，依旧支持对源文件的调试能力，方便程序调优与问题定位。

### 直接调试毕昇c源文件
这里的调试主要指gdb调试，能够设置断点，打印基础变量的值。标准c原有的类型，支持正确打印变量的值，毕昇c新增类型，如owned struct，泛型等，调试时也能正确打印。

下面是一个例子：
```c
owned struct Person<T>{
public:
    char name[50];
    T age;
    ~Person(This this) {
    }
};

char* Person<T>::getName(This *this) {
    return this->name;
}

int Person<T>::getAge(This *this) {
    T a = this->age;
    return a;
}

int main() {
    Person<int> per = {"davi", 21};
    char* name = per.getName();
    int age = per.getAge();
    return 0;
}
```
完整的调试过程如下：

- 生成带调试信息的可执行文件：
  ```shell
  clang -g debug_demo.cbs -o debug_demo_cbs
  ```
  **注意：** clang默认生成gdwarf-5格式的调试文件，安装的gdb版本需不低于10.1，否则存在兼容性问题。另外，也可以加上`-gdwarf-4`编译选项，生成兼容性更好的gdwarf-4格式的调试文件：
  ```shell
  clang -g -gdwarf-4 debug_demo.cbs -o debug_demo_cbs
  ```

- 运行`gdb debug_demo_cbs`，进入gdb调试界面。

- 下面是一些常用的调试命令：

  输入`b main`，设置断点，输入`run`，运行程序，程序运行到断点处，输入`info locals`，查看局部变量的值，输入`p var`，打印变量`var`的值，输入`s`或`n`，步进下一行。


在上面这个调试用例中，记录了一些调试过程信息，如下：
  ```shell
  (gdb) b main
  Breakpoint 1 at 0x1162: file debug_demo.cbs, line 19.
  (gdb) r
  Starting program: /path/to/debug_demo 

  Breakpoint 1, main () at debug_demo.cbs:19
  19	    Person<int> per = {"davi", 21};
  (gdb) n
  20	    char* name = per.getName();
  (gdb) p per
  $1 = {name = "davi", '\000' <repeats 45 times>, age = 21}
  (gdb) s
  _ZN_ZTS6PersonIiEgetName (this=0x7fffffffdce0) at debug_demo.cbs:10
  10	        return this->name;
  (gdb) s
  main () at debug_demo.cbs:21
  21	    int age = per.getAge();
  (gdb) s
  _ZN_ZTS6PersonIiEgetAge (this=0x7fffffffdce0) at debug_demo.cbs:14
  14	        T a = this->age;
  (gdb) s
  15	        return a;
  (gdb) p a
  $2 = 21
  (gdb) s
  _ZN_ZTS6PersonIiE~Person (this=...) at debug_demo.cbs:5
  5	    ~Person(This this) {

  ...

  ```
  在调试中，`owned struct`类型的`per` 以及泛型`a` 的值被正确打印出来了。

  **注意：** 函数名称显示为诸如`_ZN_ZTS6PersonIiEgetName`，这是经过编译器名称修饰(`Mangle`)之后的，与原始名称存在差异。


### 源源变换后调试毕昇c源文件
将毕昇c源源变换为标准c后，可以直接调试生成的c文件。由于标准c与毕昇c间的关联信息缺失，调试中无法建立其与原始毕昇c之间的映射关系，调试友好性欠佳。在此背景下，我们建立了源源变换后c文件与原cbs文件之间的行号映射关系，从而支持源源变换后对毕昇c源文件的调试能力。

**注意：** 直接的调试对象仍是变换后的c文件，但调试过程中显示的是变换前的cbs文件，本质是建立了一定程度的行号映射关系。

#### 单文件调试
仍以上一小节的cbs文件为例，尝试帮助开发者更好地理解这个调试特性。

完整的调试过程如下：
- 源源变换生成带行号映射关系的标准c文件：
  ```shell
  clang -rewrite-bsc -line debug_demo.cbs -o debug_demo.c
  ```

- 查看生成的c文件：
  ```c
  struct Person_int {
      char name[50];
      int age;
  };
  
  static char *struct_Person_int_getName( struct Person_int *this);
  
  static int struct_Person_int_getAge( struct Person_int *this);
  
  static void struct_Person_int_D( struct Person_int this);
  
  #line 18 "debug_demo.cbs"
  int main(void) {
      struct Person_int per = {"davi", 21};
      _Bool per_is_moved = 0;
      char *name = struct_Person_int_getName(&per);
      int age = struct_Person_int_getAge(&per);
      if (!per_is_moved)
          struct_Person_int_D(per);
      return 0;
  }
  
  #line 9 "debug_demo.cbs"
  static char *struct_Person_int_getName( struct Person_int *this) {
      return this->name;
  }
  
  #line 13 "debug_demo.cbs"
  static int struct_Person_int_getAge( struct Person_int *this) {
      int a = this->age;
      return a;
   }
  
  #line 5 "debug_demo.cbs"
  static void struct_Person_int_D( struct Person_int this) {
      _Bool this_is_moved = 0;
  }
  
  ```
  观察生成的c文件，可以发现，每段函数代码块前都插入了其在原始cbs文件中对应部分的开始行号，格式为
  ```c
  #line raw_number "debug_demo.cbs"
  ```
  其中 `raw_number`为起始行号，`"debug_demo.cbs"`为相对路径下原始cbs文件名。

- 生成带调试信息的可执行文件：
  ```shell
  clang -g debug_demo.c -o debug_demo_c
  ```

- 运行`gdb debug_demo_c`，进入gdb调试界面。

  此时，`gdb` 交互界面显示的是原始cbs文件中的内容和行号，而不是变换后的c文件中的行号。借助`gdb`的常用调试命令，可以在毕昇c原始代码中跳转，并打印一些变量值。
  
  **注意：** 源源变换时若采用相对路径，在调试时需要控制在同一相对路径下；若采用绝对路径，则无此问题。

- 记录了一些调试过程信息，如下：
  ```shell
  (gdb) b main
  Breakpoint 1 at 0x1152: file /path/to/debug_demo.cbs, line 19.
  (gdb) r
  Starting program: /path/to/debug_demo_c
  
  Breakpoint 1, main () at /path/to/debug_demo.cbs:19
  19	    Person<int> per = {"davi", 21};
  (gdb) s
  20	    char* name = per.getName();
  (gdb) s
  21	    int age = per.getAge();
  (gdb) s
  struct_Person_int_getName (this=0x7fffffffdcf0) at /path/to/debug_demo.cbs:10
  10	        return this->name;
  (gdb) s
  main () at /path/to/debug_demo.cbs:22
  22	    return 0;
  (gdb) s
  struct_Person_int_getAge (this=0x7fffffffdcf0) at /path/to/debug_demo.cbs:14
  14	        T a = this->age;
  (gdb) s
  15	        return a;
  (gdb) info locals
  a = 21
  (gdb) s
  main () at /path/to/debug_demo.cbs:23
  23	}
  (gdb) s
  24
  (gdb) info locals
  per = {name = "davi", '\000' <repeats 45 times>, age = 21}
  per_is_moved = false
  name = 0x7fffffffdcf0 "davi"
  age = 21
  (gdb) s
  struct_Person_int_D (this=...) at /path/to/debug_demo.cbs:6
  6	    }
  
  ...
  ```

#### 多文件调试
当存在多文件引用时，调试时也能在多文件间正确跳转。例如，存在一个包含基本数学运算函数的源文件`basic_math.cbs`及其头文件`basic_math.hbs`，在`cacl_demo.cbs`中调用`basic_math`中的函数。
- 源文件

  `basic_math.cbs`
  ```c
  #include "basic_math.hbs"
  
  int struct MyStruct::add(int a, int b){
      int res = a + b;
      return res;
  }
  
  int struct MyStruct::subtract(int a, int b) {
      int res = a - b;
      return res;
  }
  
  int struct MyStruct::multiply(int a, int b) {
      int res = a * b;
      return res;
  }
  
  int struct MyStruct::divide(int a, int b) {
      if (b != 0) {
          return a/b;
      } else {
          return 0;
      }
  }
  ```

  `basic_math.hbs`
  ```c
  #ifndef REWRITE_H
  #define REWRITE_H
  
  struct MyStruct {
      int a;
      int b;
  };
  
  int struct MyStruct::add(int a, int b);
  int struct MyStruct::subtract(int a, int b);
  int struct MyStruct::multiply(int a, int b);
  int struct MyStruct::divide(int a, int b);
  
  T min<T>(T a, T b) {
      return a > b ? b : a;
  }
  
  T max<T>(T a, T b) {
      return a > b ? a : b;
  }
  
  #endif
  ```

  `cacl_demo.cbs`
  ```c
  #include "basic_math.hbs"
  
  int main() {
      struct MyStruct s = {4, 2};
      int r1 = struct MyStruct::add(s.a, s.b);
      int r2 = struct MyStruct::subtract(s.a, s.b);
      int r3 = struct MyStruct::multiply(s.a, s.b);
      int r4 = struct MyStruct::divide(s.a, s.b);
      int c1 = max<int>(s.a, s.b);
      int c2 = min<int>(s.a, s.b);
      return 0;
  }
  ```
- 源源变换
  ```shell
  clang -rewrite-bsc -line basic_math.cbs basic_math.hbs calc_demo.cbs
  ```
  变换后，生成了`basic_math.c`、`basic_math.h`与`calc_demo.c`，分别如下：
  
  `basic_math.c`
  ```c
  #include "basic_math.h"
  
  #line 3 "basic_math.cbs"
  int struct_MyStruct_add(int a, int b) {
      int res = a + b;
      return res;
  }
  
  #line 8 "basic_math.cbs"
  int struct_MyStruct_subtract(int a, int b) {
      int res = a - b;
      return res;
  }
  
  #line 13 "basic_math.cbs"
  int struct_MyStruct_multiply(int a, int b) {
      int res = a * b;
      return res;
  }
  
  #line 18 "basic_math.cbs"
  int struct_MyStruct_divide(int a, int b) {
      if (b != 0) {
          return a / b;
      } else {
          return 0;
      }   
  }
  ```
  `basic_math.h`
  ```c
  #ifndef REWRITE_H
  #define REWRITE_H
  
  struct MyStruct {
      int a;
      int b;
  };
  
  #line 9 "basic_math.hbs"
  int struct_MyStruct_add(int a, int b);
  
  #line 10 "basic_math.hbs"
  int struct_MyStruct_subtract(int a, int b);
  
  #line 11 "basic_math.hbs"
  int struct_MyStruct_multiply(int a, int b);
  
  #line 12 "basic_math.hbs"
  int struct_MyStruct_divide(int a, int b);
  #endif
  ```

  `calc_demo.c`
  ```c
  #include "basic_math.h"
  
  static int min_int(int a, int b); 
  
  static int max_int(int a, int b); 
  
  #line 3 "calc_demo.cbs"
  int main(void) {
      struct MyStruct s = {4, 2}; 
      int r1 = struct_MyStruct_add(s.a, s.b);
      int r2 = struct_MyStruct_subtract(s.a, s.b);
      int r3 = struct_MyStruct_multiply(s.a, s.b);
      int r4 = struct_MyStruct_divide(s.a, s.b);
      int c1 = max_int(s.a, s.b);
      int c2 = min_int(s.a, s.b);
      return 0;
  }
  
  #line 14 "./basic_math.hbs"
  static int min_int(int a, int b) {
      return a > b ? b : a;
  }
  
  #line 18 "./basic_math.hbs"
  static int max_int(int a, int b) {
      return a > b ? a : b;
  }
  ```
- 生成调试信息
  ```shell
  clang -g calc_demo.c basic_math.c -o calc_demo_c
  ```
- gdb调试
  ```shell
  gdb calc_demo_c
  ```
  调试中，可以正常跳转到原始`cbs`和`hbs`文件，部分调试过程示例如下：
  ```shell
  Breakpoint 1, main () at /path/go/calc_demo.cbs:4
  4	  struct MyStruct s = {4, 2};
  (gdb) n
  5	  int r1 = struct MyStruct::add(s.a, s.b);
  (gdb) s
  struct_MyStruct_add (a=4, b=2) at /path/go/basic_math.cbs:4
  4	  int res = a + b;
  (gdb) s
  5	  return res;
  (gdb) p res
  $1 = 6
  (gdb) c
  Continuing.
  
  Breakpoint 2, max_int (a=4, b=2) at ./basic_math.hbs:19
  19	  return a > b ? a : b;
  
  ...
  ```
  该调试特性支持的功能与问题，汇总如下：
- 调试的对象是变换后的标准c，不改其运行逻辑、变量信息等。
- 调试中显示的代码位置指向原始cbs文件，支持多源文件的调试跳转。
- 当源源变换前后代码行数存在差异、无法逐行映射时，例如owned struct析构函数、trait等会生成新代码的特性，显示的调试位置可能不准确，需要开发者注意。

## 编译错误屏蔽

### 	概述

​	开发者可以针对性的让编译器在编译时不显示某些已知且暂时无需关注的错误，从而避免编译过程被这些错误打断，提高开发效率。当前只支持屏蔽 Nullability、Owned、Borrow 数据流安全分析过程中的报错，不支持屏蔽其他语法语义报错。在某些场景中，这些安全规则可能会过于严格，开发者可以针对这些过于严格的报错进行屏蔽。但需注意，屏蔽错误并不意味着错误不存在，只是在编译阶段不展示相关提示。过度使用错误屏蔽功能可能会导致一些严重问题被忽视。

### 	使用方式

- 使用编译选项屏蔽错误：毕昇 C 编译器新增了 `-Eno-xxx` 错误屏蔽编译选项。这里的`xxx`代表具体的**错误类型标识**。

  示例: 对于如下代码，使用毕昇编译器编译时会上报注释中所述错误，我们通过在编译命令中添加 `-Eno-repeated-borrow`可关闭此类错误提示。

  ```c++
  // file: test1.cbs
  // clang -Eno-repeated-borrow test1.cbs
  void use(int * borrow a){}
  int main() {
    int local = 1;
    int * borrow p1 = &mut local;
    int * borrow p2 = &mut local;	// error: cannot borrow `local` as mutable more than once at a time
    use(p2);
    use(p1);
    return 0;
  }
  ```

- 屏蔽代码片段中的错误：通过在代码片段中添加`#pragma` 预处理指令管理编译过程中的报错行为。

  `#pragma GCC diagnostic push`保存当前的诊断状态。

  `#pragma GCC diagnostic ignored "-Exxx"`告诉编译器忽略`xxx`错误类型的报错。这里的`xxx`代表具体的**错误类型标识**。

  `#pragma GCC diagnostic pop`恢复到之前保存的诊断状态。

  示例：对于如下代码，编译器会忽略`*p1 = 2;`触发的`assign-borrowed`错误类型的报错。

  ```c++
  int main() {
    int local = 42;
    int temp = 2;
    int *borrow p1 = &mut local;
    int *borrow p2 = &mut temp;
    p2 = p1;
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Eassign-borrowed"
    *p1 = 2; 					// error: cannot assign to `*p1` because it is borrowed
    #pragma GCC diagnostic pop
    temp = *p2;
    return 0;
  }
  ```
### 可被屏蔽的错误

  具体错误类型标识对应的错误日志详情见下表:

| **错误类型标识**     | 可屏蔽错误日志 (日志中%0、%1为您所写的代码中变量的属性。)    |
| -------------------- | ------------------------------------------------------------ |
| deref-nullable       | "nullable pointer cannot be dereferenced"                    |
| pass-nullable        | "cannot pass nullable pointer argument"                      |
| return-nullable      | "cannot return nullable pointer type"                        |
| cast-nullable        | "cannot cast nullable pointer to nonnull type"               |
| assign-nullable      | "cannot access member through nullable pointer"              |
| assign-nonnull       | "nonnull pointer cannot be assigned by nullable pointer"     |
| bsc-nullability      | 可屏蔽所有 Nullability 数据流分析过程的报错，<br />包括 deref-nullable、pass-nullable、return-nullable、cast-nullable、<br />assign-nullable、assign-nonnull 错误类型标识。 |
| use-moved-owned      | "use of moved value: \`%0\`“<br />"use of partially moved value: \`%0\`, %1 moved"<br />"use of all moved value: \`%0\`" |
| use-uninit-owned     | "use of uninitialized value: \`%0\`"<br />"use of possibly uninitialized value: \`%0\`" |
| init-nonnull    | "`%0` is a _Nonnull pointer and must be properly initialized." |
| use-owned            | 包括use-moved-owned、use-uninit-owned 错误类型标识可屏蔽的错误日志 |
| assign-moved-owned   | "assign to partially moved value: \`%0\`, %1 moved"<br />"assign to possibly partially moved value: \`%0\`, %1 possibly moved"<br />"assign to all moved value: \`%0\`"<br />"assign to part of moved value: \`%0\`" |
| assign-uninit-owned  | "assign to part of uninitialized value: \`%0\`"              |
| assign-owned         | "assign to owned value: \`%0\`"<br />"assign to part of owned value: \`%0\`"<br />"assign to subfield owned value: \`%0\`, %1 owned"<br />还包括assign-moved-owned、assign-uninit-owned 错误类型标识可屏蔽的错误日志 |
| cast-moved-owned     | "invalid cast to `void * owned` of moved value: \`%0\`"      |
| cast-owned           | "invalid cast to `void * owned` of owned value: \`%0\`"<br />"invalid cast to `void * owned` of uninit value: \`%0\`"<br />"invalid cast to `void * owned` of not all moved value: \`%0\`, %1 owned"<br />"invalid cast to `void * owned` of moved value:\`%0\`" |
| check-memory-leak    | "field memory leak of value: `%0`, %1 leak"<br />"memory leak of value: `%0` |
| destruct-owned-struct    | "destructor for`%0` incorrect, %1 of owned type and needs to be handled manually |
| partially-moved-struct    | "partially moved owned struct:`%0` at scope end, %1 moved |
| bsc-ownership        | 可屏蔽所有 owned 数据流分析过程的报错，<br />包括 use-owned、assign-owned、cast-owned、check-memory-leak 错误类型标识可屏蔽的错误日志。 |
| assign-borrowed      | "cannot assign to \`%0\` because it is borrowed"             |
| move-borrowed        | "cannot move out of \`%0\` because it is borrowed"           |
| use-mutably-borrowed | "cannot use \`%0\` because it was mutably borrowed"          |
| repeated-borrow      | "cannot borrow \`%0\` as mutable more than once at a time"<br />"cannot borrow \`%0\` as immutable because it is also borrowed as mutable"<br />"cannot borrow \`%0\` as mutable because it is also borrowed as immutable" |
| return-local-borrow  | "cannot return reference to local variable \`%0\`"           |
| short-life-borrow    | "\`%0\` does not live long enough"                           |
| bsc-borrow           | 可屏蔽所有 borrow 数据流分析过程的报错，<br />包括assign-borrowed、move-borrowed、use-mutably-borrowed、<br />repeated-borrow、return-local-borrow、short-life-borrow错误类型标识可屏蔽的错误日志。 |
| bsc-safety-check     | 可屏蔽所有 Nullability、owned、borrow 数据流分析过程的报错，<br />包括bsc-nullability、bsc-ownership、bsc-borrow错误类型标识可屏蔽的错误日志。 |




---


# 附录 A — Language syntax summary

本章对毕昇 C 语言的语法使用 EBNF（Extended Backus-Naur Form，扩展巴科斯范式）进行规范化描述。由于毕昇 C 语言扩展自 C 语言，本节不再列出 C 语言已有的语法的 EBNF 表示，**仅给出毕昇 C 语言扩展的语法的 EBNF 表示**，关于 C 语言已有语法的 EBNF 表示可查阅[ C11 标准规范](https://www.iso-9899.info/n1570.html#A.)。本章的组织结构与 C11 标准规范的附录 A 保持一致，用户可将两者对比阅读，能够清晰直观地了解到毕昇 C 扩展的 EBNF 表示的内容。

在本章中使用的语法符号中，采用与 C11 标准规范中类似的表示方式：

- 使用前下划线（_）表示语法类别（即非终结符，`_Nonnull`和`_Nullable`除外，他们是终结符），没有前下划线则表示字面量和字符集合（即终结符）；
- 在代码块的第一行，非终结符后接冒号（:）表示非终结符的具体定义（即产生式规则）；
- 除了以“one of”开头外，其他的可选定义都列在不同的行中，可选的非终结符使用后缀“_opt”表示；
- 对于向 C11 已有的语法类别中新增语法，使用“....”表示省略已有的语法规则。


## A.1 Lexical grammar

### A.1.1 Lexical elements

无新增或修改。

### A.1.2 Keywords

`_keyword`的产生式规则有如下变化：

1. 新增 17 个关键字，为`_keyword`新增 17 条产生式：

```text
_keyword : one of
    ....         impl         This
    async        nullptr      this
    await        owned        trait
    borrow       private      unsafe
    constexpr    public       _Nonnull
    fat          safe         _Nullable
```

### A.1.3 Identifiers

无新增或修改。

### A.1.4 Universal character names

无新增或修改。

### A.1.5 Constants

无新增或修改。

### A.1.6 String literals

无新增或修改。

### A.1.7 Punctuators

`_punctuator`的产生式规则有如下变化：

1. 新增 6 个运算符和分隔符，为`_punctuator`新增 6 条产生式。

```text
_punctuator : one of
    ....         &fat         ::
    &const       &mut
    &const *     &mut *
```

### A.1.8 Header names

无新增或修改。

### A.1.9 Preprocessing numbers

无新增或修改。

### A.1.10 Pointer literals

新增`_pointer-literal`，表示空指针字面量：

```text
_pointer-literal :
    nullptr
```


## A.2 Phrase structure grammar

### A.2.1 Expressions

`_primary-expression`的产生式规则有如下变化：

1. 支持泛型特性，修改了`_primary-expression`的第 1 条产生式；
2. `this`属于`_primary-expression`，为`_primary-expression`新增 1 条产生式。

```text
_primary-expression :
    ....
    _identifier _template-declaration_opt
    this
```

`_postfix-expression`的产生式规则有如下变化：

1. 支持泛型函数，修改了`_postfix-expression`的第 4 和第 5 条产生式；
2. 允许调用静态成员函数和实例成员函数，为`_postfix-expression`新增 2 条产生式。

```text
_postfix-expression :
    ....
    _postfix-expression . _identifier _template-declaration_opt
    _postfix-expression -> _identifier _template-declaration_opt
    _nested-name-specifier
    _postfix-expression _identifier _template-declaration_opt
```

`_unary-expression`的产生式规则有如下变化：

1. 允许使用`await`关键字修饰表达式，为`_unary-expression`新增 1 条产生式。

```text
_unary-expression :
    ....
    await _unary-expression
```

`_unary-operator`的产生式规则有如下变化：

1. 新增 5 种一元运算符，为`_unary-operator`新增 5 条产生式。

```text
_unary-operator : one of
    ....         &const *     &mut
    &const       &fat         &mut *
```

### A.2.2 Declarations

新增`_template-parameter`，表示泛型形参：

```text
_template-parameter :
    _identifier
    _parameter-declaration
```

新增`_template-parameter-list`，表示泛型形参列表：

```text
_template-parameter-list :
    _template-parameter
    _template-parameter-list , _template-parameter
```

新增`_template-argument`，表示泛型实参：

```text
_template-argument :
    _constant-expression
    _type-name
```

新增`_template-argument-list`，表示泛型实参列表：

```text
_template-argument-list :
    _template-argument
    _template-argument-list , _template-argument
```

新增`_template-declaration`，表示泛型形参声明或泛型实参声明：

```text
_template-declaration :
    < _template-parameter-list >
    < _template-argument-list >
```

新增`_constexpr-specifier`，表示常量表达式限定符：

```text
_constexpr-specifier :
    constexpr
```

`_declaration-specifiers`的产生式规则有如下变化：

1. `_constexpr-specifier`可修饰声明，为`_declaration-specifiers`新增 1 条产生式。

```text
_declaration-specifiers :
    ....
    _constexpr-specifier _declaration-specifiers_opt
```

`_initializer`的产生式规则有如下变化：

1. 支持通过`typedef`和等号定义类型别名的新语法，为`_initializer`新增 1 条产生式。

```text
_initializer :
    ....
    _type-name
```

`_type-specifier`的产生式规则有如下变化：

1. 新增 2 种类型限定符，为`_type-specifier`新增 2 条产生式。

```text
_type-specifier :
    ....
    This
    _trait-name
```

`_struct-or-union-specifier`的产生式规则有如下变化：

1. 允许定义泛型结构体和联合体，修改了`_struct-or-union-specifier`的第 1 和第 2 条产生式。

```text
_struct-or-union-specifier :
    _struct-or-union _identifier_opt _template-declaration_opt { _struct-declaration-list }
    _struct-or-union _identifier _template-declaration_opt
```

`_type-qualifier`的产生式规则有如下变化：

1. 新增 5 种类型说明符，为`_type-qualifier`新增 5 条产生式。

```text
_type-qualifier :
    ....
    borrow
    fat
    owned
    _Nonnull
    _Nullable
```

新增`_safe-specifier`，表示安全限定符：

```text
_safe-specifier :
    safe
    unsafe
```

新增`_access-specifier`，表示访问限定符：

```text
_access-specifier :
    public
    private
```

`_function-specifier`的产生式规则有如下变化：

1. 新增 3 种函数限定符，为`_function-specifier`新增 2 条产生式。

```text
_function-specifier :
    ....
    async
    _safe-specifier
```

新增`_nested-name-specifier`，表示嵌套限定符：

```text
_nested-name-specifier :
    _type-name ::
```

`_direct-declarator`的产生式规则有如下变化：

1. 支持泛型函数定义，修改了`_direct-declarator`的第 1 条产生式；
2. 支持为类型声明和定义扩展成员函数，为`_direct-declarator`新增 2 条产生式。

```text
_direct-declarator :
    ....
    _identifier _template-declaration_opt
    _nested-name-specifier
    _direct-declarator _identifier _template-declaration_opt ( _parameter-type-list )
```

`_typedef-name`的产生式规则有如下变化：

1. 支持对泛型类型定义别名，修改了`_typedef-name`的第 1 条产生式。

```text
_typedef-name :
    _identifier _template-declaration_opt
```

### A.2.3 Statements

`_compound-statement`的产生式规则有如下变化：

1. 安全限定符可修饰代码块，修改了`_compound-statement`的第 1 条产生式。

```text
_compound-statement :
    _safe-specifier_opt { _block-item-list_opt }
```

`_selection-statement`的产生式规则有如下变化：

1. 常量表达式限定符可修饰`if`语句的条件表达式，修改了`_selection-statement`的第 1 和 第 2 条产生式。

```text
_selection-statement :
    if _constexpr-specifier_opt ( _expression ) _statement
    if _constexpr-specifier_opt ( _expression ) _statement else _statement
```

### A.2.4 External definitions

新增`_function-declaration`，表示函数声明：

```text
_function-declaration :
    _declaration-specifiers _pointer_opt _identifier ( _parameter-type-list ) ;
```

新增`_function-declaration-list`，表示函数声明列表：

```text
_function-declaration-list :
    _function-declaration
    _function-declaration-list _function-declaration
```

新增`_trait-name`的定义，表示`trait`的名称：

```text
_trait-name :
    trait _identifier _template-declaration_opt
```

新增`_trait-definition`，表示`trait`的定义：

```text
_trait-definition :
    _trait-name { _function-declaration-list } ;
```

新增`_impl-declaration`，表示实现`trait`：

```text
_impl-declaration :
    impl _trait-name for _type-name ;
```

新增`_dtor-definition`，表示析构函数定义：

```text
_dtor-definition :
    ~ _identifier ( _declaration ) _compound-statement
```

新增`_member-declaration`，表示`owned struct`成员种类：

```text
_member-declaration :
    _declaration
    _dtor-definition
    _function-definition
```

新增`_member-specification`，表示`owned struct`成员变量或成员函数：

```text
_member-specification :
    _member-declaration _member-specification_opt
    _access-specifier : _member-specification_opt
```

新增`_owned-struct-declaration`，表示`owned struct`类型声明：

```text
_owned-struct-declaration :
    owned struct _identifier _template-declaration_opt { _member-specification_opt } ;
```

`_external-declaration`的产生式规则有如下变化：

1. `trait`定义、实现`trait`和`owned struct`类型声明都属于外部声明，为`_external-declaration`新增 3 条产生式。

```text
_external-declaration :
    ....
    _trait-definition
    _impl-declaration
    _owned-struct-declaration
```


## A.3 Preprocessing directives

无新增或修改。