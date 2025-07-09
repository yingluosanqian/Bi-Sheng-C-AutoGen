

# Bi-Sheng-C AutoGen

Bi-Sheng-C AutoGen 是一个使用大模型自动生成包含 Bi-Sheng-C 语言特性的工具，它的功能包含：

* 生成一对功能相同的 `.c` 和 `.cbs` 代码；
* 将 `.c` 代码翻译到 `.cbs` 代码；（TODO）

## 环境配置

目前支持 Linux 环境（支持 WSL）。

### 1. Bi-Sheng-C 编译器配置（运行本项目目前不需要配置 clang，但后续版本需要）

从源码构建 Bi-Sheng-C 编译器：

``` shell
git clone git@gitee.com:bisheng_c_language_dep/llvm-project.git
cd llvm-project
mkdir build && cd build
cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;libcbs" -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm
make -j6
```

在环境变量中配置 Clang 路径：

``` shell
export LLVM_HOME=/opt/compiler/llvm-project/build/bin
export PATH=$LLVM_HOME:$PATH
```

验证安装成功，在命令行输入 `clang --version` 可以看到类似如下输出：

``` txt
InstalledDir: /path/to/bi-sheng-c-release/X86/llvm_15.0.4_X86_BSC/bin
```

如遇到问题，可参考[这里](https://gitee.com/bisheng_c_language_dep/llvm-project/issues/ICKQM9?from=project-issue)


### 2. Deepseek-API-Key 配置

我目前使用了 DeepseekAPIKey，需要输入如下命令将 APIKey 写入系统环境变量：

``` shell
export DEEPSEEK_API_KEY=${YOUR_API_KEY}$
```

一个更方便的方式是把上面的配置信息写入脚本配置文件，如 `.bashrc`。

如果想使用其他模型，可以在 `dpsk_llm.py` 文件中修改相应代码：

``` py
client = OpenAI(api_key=os.environ["DEEPSEEK_API_KEY"],
                base_url="https://api.deepseek.com")

model = "deepseek-chat" if model_version == "v3" else "deepseek-chat"
```

## 使用前

先运行如下命令，功能是：

* Bi-Sheng-C 的官方文档拆分为若干个一级子文档，存放于 `docs/` 目录下

* 生成若干个程序功能描述，存放于 `program_desc` 目录下

``` py
python preprocess.py 
```

## 使用

### 批量生成代码

一个简单的例子，它将生成 $50$ 对功能及输出完全一致的 C 代码和 CBS 代码，后者包含了 Bi-Sheng-C 的 `成员函数` 语言特性。

可以将 `--dir` 后面的参数替换为 `const.py` 中的其他元素

``` py
python main.py generate --amount many --dir 0_成员函数
```
 
还可以使用 `all` 参数一次性生成每个语言特性的程序。

``` py
python main.py generate --amount all
```

### 验证代码

使用以下命令可以验证所有 `programs/xxx/` 目录下的代码对是否都能够通过编译且输出结果一致，通过测试的程序将被保存到 `passed_programs/xxx/` 目录下。 

``` py
python validate.py
```

### 翻译代码

TODO.

