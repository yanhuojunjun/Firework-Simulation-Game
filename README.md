# SYSU-2021级CG-11组大作业

## 项目结构

- build: 构建目录
- code: 源代码目录
    - include: 头文件
    - src: 源文件
- release: 可执行文件以及必需的资源文件
    - img: 纹理资源
    - Lib_Lib: 第三方库文件
    - lib: 项目静态库输出目录
    - Object: 模型资源
    - Shaders: 着色器源码
    - sound: 音频资源

## 项目编译方式

进入 build 文件夹运行 make_build.bat 脚本即可编译程序, 生成的可执行文件在 release 目录下.

```
cd build
./make_build.bat
```