

# Bi-Sheng-C Auto-Trans

Bi-Sheng-C Auto-Trans 是一个使用大模型自动将 C 代码翻译为 BiSheng-C 代码的工具。

## 环境配置

目前支持 Linux 环境（支持 WSL）。

### 1. Bi-Sheng-C 编译器配置（运行本项目目前不需要配置 clang，但后续版本需要）

从源码构建 Bi-Sheng-C 编译器：

``` shell
git clone git@gitee.com:bisheng_c_language_dep/llvm-project.git
cd llvm-project
mkdir build && cd build
cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;libcbs" -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm
make clang -j6
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

### 3. LangSmith-API-KEY 配置

TODO.

## 使用

TODO.
