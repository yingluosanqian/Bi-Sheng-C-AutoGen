

# Bi-Sheng-C AutoGen

Bi-Sheng-C AutoGen 是一个使用大模型自动生成包含 Bi-Sheng-C 语言特性的工具，它的功能包含：

* 生成一对功能相同的 `.c` 和 `.cbs` 代码；
* 将 `.c` 代码翻译到 `.cbs` 代码；（TODO）

## 环境配置

目前仅支持 Linux 环境（支持 WSL）。

1. Bi-Sheng-C 编译器配置（运行本项目目前不需要配置 clang，但后续版本需要）

``` shell
git clone git@gitee.com:bisheng_c_language_dep/bi-sheng-c-release.git
cd bi-sheng-c-release/X86
cat clang+llvm_15.0.4_X86_BSC.tar.gz.* > clang+llvm_15.0.4_X86_BSC.tar.gz
# 获取到安装包以后，参考 docs 下面的用户手册进行使用
# (即：bi-sheng-c-release/docs/BiShengCLanguageUserManual.md)
```

验证安装成功，在命令行输入 `clang --version` 可以看到类似如下输出：

``` txt
InstalledDir: /path/to/bi-sheng-c-release/X86/llvm_15.0.4_X86_BSC/bin
```

如遇到问题，可参考[官方文档](https://gitee.com/bisheng_c_language_dep/bi-sheng-c-release)


2. Deepseek-API-Key 配置

我目前使用了 DeepseekAPIKey，需要输入如下命令将 APIKey 写入系统环境变量：

``` shell
export DEEPSEEK_API_KEY=sk-2cef7ab97f1c4b619dd61bd2218da081
```

一个更方便的方式是把上面的配置信息写入脚本配置文件，如 `.bashrc`。

如果想使用其他模型，可以在 `dpsk_llm.py` 文件中修改相应代码：

``` py
client = OpenAI(api_key=os.environ["DEEPSEEK_API_KEY"],
                base_url="https://api.deepseek.com")

model = "deepseek-chat" if model_version == "v3" else "deepseek-chat"
```

## 使用前

先运行如下命令，将 Bi-Sheng-C 的官方文档拆分为若干个一级、二级子文档，存放于 `docs/` 目录下

``` py
python split_features.py 
```

## 使用

### 生成代码

* 一个简单的例子，它将生成两组功能及输出完全一致的 C 代码和 CBS 代码，后者包含了 Bi-Sheng-C 的语言特性。

``` py
python main.py generate --method example
```

* 还可以指定生成的程序功能：

``` py
python main.py generate --method example --input implement_a_quick_sort_algorithm
```

* 另一种方法，随机选择 Bi-Sheng-C 的一个特性，并生成对应的两组代码

```  py
python main.py generate --method random
```

* 还可以通过 `--c_output` 和 `--bsc_output` 指定输出文件的路径，例如：

```  py
python main.py generate --method example --c_output IamHere.c --Here/IamHere.cbs
```

### 翻译代码

TODO.

### 更多功能

* 批量生成程序（TODO）
