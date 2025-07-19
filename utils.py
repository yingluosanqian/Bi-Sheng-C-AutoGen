
from pathlib import Path
from enum import Enum
from typing import Optional

lang_sub_ft = (
  "0_成员函数",
  "1_泛型",
  "2_常量计算",
  "3_trait",
  "4_无栈协程",
  # "5_源源变换",
  "6_内存安全",
  "7_owned-struct-类型",
  "8_运算符重载",
  "9_非空指针",
  "10_标准库",
)

#############################################################################
# Text Area
#############################################################################

BiShengCIntro = "Bisheng C adopts a different strategy. It incorporates many enhanced designs based on the C language, such as stronger memory safety features and built-in support for concurrency. Moreover, these features can be incrementally adopted in existing codebases without requiring a full rewrite of legacy code. It can be said that Bisheng C is a superset of the C language."

notes_base = f"""
- The outputs of both programs must be identical. Ensure there are no extra outputs (such as additional logs, debug info, or unintended formatting) in either program.
- You also need to use 'include<>' statements in the bisheng-C code, such as <stdio.h> and <stdlib.h>.
- In bisheng-c, member functions are implemented with an explicit 'this' parameter as the first argument (like void int::print(int* this)), but when calling these methods, the 'this' argument is automatically handled and shouldn't be passed explicitly. (e.g., queue.enqueue(10) not queue.enqueue(&queue,10)).
- There is no bool type in C, so you can use int instead. In Bisheng-C, you can use _Bool type.
- Do not use keyword or builtin-function as function name of variable name, such as 'abs'.
"""

notes_member_function = notes_base + f"""
"""

notes_generic = notes_base + """- Do not use "is_same_type", it's a c++ function rather than bisheng-c function.
- Do not write specialized versions of generic functions (e.g., void print_inorder<int>(...), it should be print_inorder<T>(...)). Template specialization like C++ is not supported in bisheng-c. 
- In bisheng-c, member functions must include the struct name (e.g., void struct tuple<T>::func(...)). Never write just void func<T>(struct Struct<T>* this)—always prefix with the struct type.
- In bisheng-c, when defining a templated struct member function, ensure non-type template parameters (like int N) are explicitly typed in both the struct and function declaration (e.g., void struct Array<T, int N>::init(struct Array<T, int N>* this, int size), not void struct Array<T,  N>::init(struct Array<T, N>* this, int size).
- Avoid using identical names for struct and typedef (e.g., typedef struct Node<T> {...} Node;). Rename either the struct or the typedef to prevent conflicts.
- Do not use 'template <typename K, typename V>', it's a c++ feature not bisheng-c feature.
- Do not use 'if (sizeof(T) == sizeof(int)) {...} else if (sizeof(T) == sizeof(float)) ...', it's not the right way. You should implement two function to deal with different types.
"""

notes_constant = notes_base + f"""- Do not use 'constexpr' to define float type, it's not supported in bisheng-c. 
- bisheng-c does not support constexpr for float types. Remove the constexpr keyword when defining float values (e.g., use float float_val = 0.5f; instead of constexpr float float_val = 0.5f;).
- Shoule include header file <bsc_type_traits.hbs> before use is_integral, is_floating_point, ... function.
- Must not use while-statement in constexpr function.
- Must not use for-statement in constexpr function (for (int i = 2; i <= n; i++), NO!)
- Must not use unconstexpr variable in constexpr expression, e.g. 'if constexpr (n <= 5)' will cause error if n is not constexpr.
"""

notes_trait = notes_base + f"""
"""

notes_no_stack_coroutine = notes_base + f"""- You need to include <stdlib.h> before using the 'async' keyword
- 'main' is not allowed to be declared async
"""

notes_memory_safety = notes_base + f"""- Cast to (void * owned) before passing a pointer to a function that takes an owned pointer, such as 'safe_malloc<Type>(...)', 'safe_free', etc. For example:
    - safe_free((void * owned)q);
  - Include "bishengc_safety.hbs" before use "safe_malloc", "safe_free", etc. in Bisheng-C code.
  - No need to set pointer to NULL after the ownership transfer, such as 'q = NULL;'. In Bisheng-C, the ownership transfer is implicit and does not require explicit nullification.
  - Use 'safe int main(void)' instead of 'safe int main()' when use sage to decorate main function in Bisheng-C.
  - 'printf' function should be placed in unsafe block, if you use safe to decorate main function in Bisheng-C.
  - A function without safe decorator is regarded as unsafe function in Bisheng-C, so you can not put them in safe block.
  - 'i++' operator is forbidden in the safe zone, use 'i=i+1' instead.
"""

notes_owned_struct = notes_base + f"""
"""

notes_operator_overloading = notes_base + f"""
"""

notes_non_null_pointer = notes_base + """- use safe int main(void) instead of int main()。{
- unsafe function call is forbidden in the safe zone
- function without safe decorator is regarded as unsafe function in Bisheng-C, so you can not put them in safe block.
- 'printf' function should be placed in unsafe block, if you use safe to decorate main function in Bisheng-C.
- 'i++' operator is forbidden in the safe zone, use 'i=i+1' instead.
- 'arr[i]' is forbidden in the safe zone,
- 安全区内不允许无初始化或初始化不完整的变量声明，例如
```
safe {
    int a; // error: 安全区内不允许无初始化的变量声明
    struct F tom = {10}; // error：安全区不允许部分初始化
    struct F tony = {10, "tony"};
}
```
- 安全区内不允许使用自增 （++）、自减（--）操作符，不允许裸指针通过“->”访问成员，允许owned指针和borrow指针通过“->”访问成员
- 安全区内不允许使用取地址符“&”（允许对函数取地址），只允许&const，&mut取借用
- 安全区内不允许解引用裸指针类型，但可以解引用owend指针类型和borrow指针类型
- 安全区内不允许指向类型不同的指针类型之间转换
- 安全区内不允许表达范围从大向小的类型转换（比如从 long 转换为 int，从 int 转换为 _Bool，从 int 转换为 enum）
- 在 BiShengC 语言中，使用`owned`关键字用来修饰一个指针类型，表明该指针拥有其指向的内存的所有权。 拥有所有权的指针必须确保其指向的内存在指针作用域结束前被显式释放，否则存在潜在的内存泄漏错误； 此外，一块堆内存只能同时被一个`owned`指针所拥有，`owned`指针为移动语义，这样避免了释放后使用等内存安全问题的发生。
- 在安全区，`owned`指针指向的内存一定为通过`safe_malloc`函数申请出的堆内存，`owned`指针不可能指向栈内存。
- About borrow:
  - 引入借用操作符 `&mut` 和 `&const`，其中，`&mut e`表示获取对表达式 e 的可变借用，`&const e`表示获取对表达式 e 的只读借用。此处要求表达式 e 是 lvalue，与标准 C 中的取地址操作符`&`类似, 借用操作符实际上获取的是表达式 e 的地址
  - 同一时刻一个变量只能拥有一个可变借用，任意多个不可变借用，对同一个数组任意两个元素的借用被视为对同一个变量的借用
  - 借用指针变量不支持算数运算
  - subscript of borrow pointer is not allowed (e.g. `&mut arr[i]` is not allowed)
  - 借用变量在定义的时候必须初始化
- subscript of borrow pointer is not allowed 
- safe_malloc仅能申请int大小的内存，其他大小的需要在非安全区内申请 
- uninitialized declarator is forbidden in the safe zone 
- 安全区内不可申请裸指针
"""

notes_standard_library = notes_base + """- Use safe data structures like `Vec`, `String`, `Rc<T>`, etc. instead of raw pointers or arrays.
- Use `safe_malloc` and `safe_free` for memory management.
- Use `safe int main(void)` instead of `int main()`.
- Never use `++`, `--`, or `arr[i]` style indexing on owned types
- Nerver use `++`, `--` on safe types, use `i = i + 1` instead.
- No need to free Vec or String types explicitly — BiSheng-C handles this automatically
- Never call unsafe functions in safe blocks (e.g., `printf`, `String::from`, `fopen`)
- In bisheng-c, member functions must include the struct name (e.g., void struct tuple<T>::func(...)). Never write just void func<T>(struct Struct<T>* this)—always prefix with the struct type.
- In bisheng-c, when defining a templated struct member function, ensure non-type template parameters (like int N) are explicitly typed in both the struct and function declaration (e.g., void struct Array<T, int N>::init(struct Array<T, int N>* this, int size), not void struct Array<T,  N>::init(struct Array<T, N>* this, int size).
- Avoid using identical names for struct and typedef (e.g., typedef struct Node<T> {...} Node;). Rename either the struct or the typedef to prevent conflicts.
- Can not use unsafe function in safe zone, such as `printf`, `String::from`, `fopen`, etc.
"""

#############################################################################
# Method Area
#############################################################################


def load_txt(file_path: Path) -> str:
  with file_path.open(encoding="utf-8") as f:
    return f.read()


def save_txt(file_path: Path, content: str):
  with file_path.open("w", encoding="utf-8") as f:
    f.write(content)


class CodeSuffix(Enum):
  C: str = ".c"
  BSC: str = ".bsc"


def get_codes_fp(file_path: Path, suffix: list[CodeSuffix]) -> list[Path]:
  """Get all code files in the given directory."""
  if not file_path.exists():
    raise FileNotFoundError(f"Directory {file_path} does not exist.")
  return [p for s in suffix for p in file_path.glob(f"**/*{s.value}")]


#############################################################################
# Data Area
#############################################################################

class ClassLSFMeta(type):
  def __str__(cls):
    return getattr(cls, 'name')

  def __repr__(cls):
    return str(cls)

  @property
  def description(cls):
    if not hasattr(cls, '_description'):
      with open(cls.filepath, 'r', encoding='utf-8') as f:
        cls._description = f.read().strip()
    return cls._description

  @property
  def test_programs_dir(cls):
    return Path(f"test_programs/{cls.index}_{cls.name}")

  @property
  def filepath(cls):
    return Path(f"docs/{cls.index}_{cls.name}.md")

  def test_programs_fp(cls, suffix: list[CodeSuffix]) -> list[Path]:
    return get_codes_fp(cls.test_programs_dir, suffix)

  @property
  def examples_dir(cls):
    return Path(f"examples/{cls.index}_{cls.name}")

  @property
  def examples_code(cls) -> Optional[list[str]]:
    if not cls.examples_dir:
      return None
    return [load_txt(fp) for fp in cls.examples_dir.glob("*.cbs")]


class LangSubFeature(metaclass=ClassLSFMeta):
  name: str
  notes: str = notes_base


class LSFMemberFunction(LangSubFeature):
  index = 0
  name = "成员函数"
  notes: str = notes_member_function


class LSFGeneric(LangSubFeature):
  index = 1
  name = "泛型"
  notes: str = notes_generic


class LSFConstant(LangSubFeature):
  index = 2
  name = "常量计算"
  notes: str = notes_constant


class LSFTrait(LangSubFeature):
  index = 3
  name = "trait"
  notes: str = notes_trait


class LSFNoStackCoroutine(LangSubFeature):
  index = 4
  name = "无栈协程"
  notes: str = notes_no_stack_coroutine


# class LSFSourceTransform(LangSubFeature):
#   index = 5
#   name = "源源变换"


class LSFMemorySafety(LangSubFeature):
  index = 6
  name = "内存安全"
  notes: str = notes_memory_safety


class LSFOwnedStruct(LangSubFeature):
  index = 7
  name = "owned-struct-类型"
  notes: str = notes_owned_struct


class LSFOperatorOverloading(LangSubFeature):
  index = 8
  name = "运算符重载"
  notes: str = notes_operator_overloading


class LSFNonNullPointer(LangSubFeature):
  index = 9
  name = "非空指针"
  notes: str = notes_non_null_pointer


class LSFStandardLibrary(LangSubFeature):
  index = 10
  name = "标准库"
  notes: str = notes_standard_library


LSF_list = [
  LSFMemberFunction,
  LSFGeneric,
  LSFConstant,
  LSFTrait,
  LSFNoStackCoroutine,
  # LSFSourceTransform,
  LSFMemorySafety,
  LSFOwnedStruct,
  LSFOperatorOverloading,
  LSFNonNullPointer,
  LSFStandardLibrary,
]
