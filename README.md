# SYSU-2021级CG-11组大作业

## 项目结构

- build: 构建目录
- include: 头文件目录
- run: 可执行文件以及库文件目录
    - Lib_Lib: 第三方库
    - bin: 可执行文件, 动态链接库, 资源文件(着色器, 图片, 模型等)
    - lib: 自定义库文件生成目录
- src: 项目源码
    - OpenGLTools: OpenGL必需的对象(包含教程中提供的与小组成员编写的)
    - test_demo: 测试样例
    - Object: 测试样例需要的杂项(后续用不到)

## 项目编译方式

进入 build 文件夹运行 make_build.bat 脚本即可编译程序, 生成的可执行文件在 run/bin目录下.

```
cd build
./make_build.bat
```
