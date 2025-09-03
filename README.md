# 🧬 Base64anlz
Base64anlz 是一个用纯 C 语言编写的轻量级工具，Base64steg的C语言版。支持从文本文件中批量提取 Base64 编码中的隐写信息，同时也提供命令行下的 Base64 编码与解码功能。该项目个人学习开发，环境为VSCode + GCC，代码中可能存在一些Bug。此README文档中的部分内容由AI生成。

# 🚀 功能特性
- 🔍 隐写分析：从 .txt 文件中提取一批 Base64 字符串中的隐藏内容，输出并保存到新文件。
- 🧪 命令行模式：直接在终端进行 Base64 编码与解码操作。
- ⚙️ 纯 C 实现：无依赖，可在类 Unix 系统或 Windows 上编译运行。

# 📦 使用方法
```bash
./base64anlz [String|FileName]
```
### 🍔字符串编解码
直接在程序名称后输入一个字符串作为参数以使用编解码功能。
Eg.
```bash
./base64anlz "HelloWorld"
输出: SGVsbG9Xb3JsZA==
```

### 🍟隐写提取模式
在程序名称后输入一个存储多行Base64字符串的文本文件以使用隐写提取。
Eg.
```bash
./base64anlz file.txt
# 从 file.txt 中提取隐写内容，保存到同一目录下的 file_stegres.txt
```

##### 📂 输入文件格式说明
file.txt 应包含一行一个 Base64 编码字符串，例如：
```
U29tZSBub3JtYWwgZGF0YQ==
U2VjcmV0IG1lc3NhZ2UgaGVyZQ==
...
```

# 📄 版权和许可证
本项目采用 [GNU GPL v3](https://www.gnu.org/licenses/gpl-3.0.html) 许可证。
你可以自由使用、修改和分发本项目的源代码，但在发布衍生版本时，**必须在文档或说明中明确标注原项目的 GitHub 仓库地址**：
> 原项目地址：https://github.com/LIBERTYEVIL/Base64Anlz/
