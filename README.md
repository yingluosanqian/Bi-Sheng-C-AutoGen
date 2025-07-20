

# Bi-Sheng-C Auto-Trans

Bi-Sheng-C Auto-Trans 是一个使用大模型自动将 C 代码翻译为 BiSheng-C 代码的工具。

## 环境配置

### 1. BiSheng-C 编译器配置

支持多种方式安装 BiSheng-C 编译器。

#### 1.1 从源码构建

```
git clone git@gitee.com:bisheng_c_language_dep/llvm-project.git
cd llvm-project
mkdir build && cd build
cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;libcbs" -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm && make clang && make
```

构建完成后，可以在 `build/bin` 的目录下找到 `clang`，可以编译 `.cbs` 文件。需要将 `clang` 写入环境变量。

``` sh
export LLVM_HOME={PATH_TO}/llvm-project/build/bin
export LLVM_SOURCE={PATH_TO}/llvm-project # 非常重要，在 validation.py 中依赖这个环境变量
export PATH=$LLVM_HOME:$PATH
```

使用如下命令验证安装 `clang` 成功：

``` txt
clang --version
```

应该看到和 bisheng-c 相关的输出，例如：

``` txt
clang version 15.0.4 (git@gitee.com:bisheng_c_language_dep/llvm-project.git 3fc8dc5f8f7946c53a0576f7bfbb2b5ebd7dbe75)
```

#### 1.2 下载构建完成的二进制文件（未尝试过）

[这里](https://mirrors.huaweicloud.com/kunpeng/archive/compiler/bisheng_compiler/)

同样需要如 1.1 描述配置环境。

### 2. Python 环境配置

### 3. API-KEY 配置

#### 3.1 DEEPSEEK_API_KEY

本工具使用 `deepseek-v3` 模型，需要用到 `DEEPSEEK_API_KEY`，将如下命令写入 shell 配置文件（永久生效）或shell（临时生效）。

``` sh
# DeepSeek
export DEEPSEEK_API_KEY={YOUR_DEEPSEEK_API_KEY}
```

#### 3.2 LANGSMITH_API_KEY

本工具使用 `LangChain` 工具库，需要用到 `LANGSMITH_API_KEY`（免费），将如下命令写入 shell 配置文件（永久生效）或shell（临时生效）。

``` sh
# LangChain
export LANGSMITH_TRACING="true"
export LANGSMITH_API_KEY={YOUR_LANGSMITH_API_KEY}
export LANGSMITH_PROJECT="default" # or any other project name
```

## 使用

支持两种翻译方式，翻译单个文件（Single Mode）或翻译某个目录下的所有文件（Batch Mode）。在进行翻译时，需要输入翻译的源文件（通过 `-i/--input` 输入），以及所涉及的 BiSheng-C 特性（通过 `-f/--feature` 输入，输入的内容必须是以下几种特性之一：`成员函数, 泛型, 常量计算, trait, 无栈协程, 内存安全, owned-struct-类型, 运算符重载, 非空指针, 标准库`）。

程序执行过程中的日志被存储于 `app.log` 中。

### 翻译单个文件（Single Mode）

如下给出一个翻译单个文件的例子：

``` sh
python translation.py -i test-data/0_成员函数/c_0.c -f 成员函数
```

执行该命令可能得到如下输出：

``` sh
Translating single file: test-data/0_成员函数/c_0.c with feature '成员函数'
Output saved to: results/default_output.cbs
[Success] Validation successful: C code and BiSheng-C code outputs match.
```

输出的文件位置默认是 `results/default_output.cbs`，也可以通过 `-o/--output` 指定输出文件位置。

### 翻译某个目录下所有文件（Batch Mode）

需要额外使用 `-m/--mode` 填写 batch 参数，如下给出一个例子：

``` sh
python translation.py -m batch -i test-data/0_成员函数 -f 成员函数
```

此时 `-i` 表示输入目录而非输入文件，而 `-o` 表示输出目录而非输出文件，输出文件与输入文件同名而后缀不同（`.c`, `.cbs`）。

执行该命令可能得到如下输出：

``` sh
Translating all 55 files in directory: test-data/0_成员函数 with feature '成员函数'
Translating C code to BiSheng-C: 100%|██████████████████████████████████████████████████████████████████████████| 55/55 [13:47<00:00, 15.04s/it, success=51/55 (92.7%)]
51 out of 55 C codes translated successfully. Rate: 92.73%
Output saved to: results/default_output_dir
```

输出的文件位置默认存储于 `results/default_output_dir` 目录下，也可以通过 `-o/--output` 指定输出文件目录。

## 测试

运行 `test.sh`， 将会对 `test-data` 目录下的预置测试集进行翻译测试，并逐一打印成功率。

``` sh
chmod +x test.sh # 第一次执行需要添加执行权限
./test.sh
```
