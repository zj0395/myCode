## 生成makefile
- 该脚本会在当前目录下生成 makefile，会覆盖掉现存的makefile。  
- 调用生成的 makefile 时执行步骤如下：
	- 检查当前目录下所有 .cpp 文件，通过 `g++ -MM file.cpp` 命令获得所有 .cpp 文件的依赖关系，并把依赖关系保存到 .d 文件中
	- 根据 .d 文件中的依赖关系，编译所有 .cpp 文件生成 .o 文件；如果依赖文件的修改时间晚于目标文件，就会重新编译，如果依赖文件的修改时间早于目标文件，就什么也不会做
	- 链接所有 .o 文件生成名为 test 的可执行文件


- 如果需要多目录的处理，可以在调用此脚本时加上参数 -r，这样就会自动处理当前目录和当前目录下的所有一级子目录下的所有 .cpp 文件。在 .cpp 文件的目录里生成 .o 和 .d 文件，之后将所有 .o 文件链接成可执行文件 test，可执行文件位于当前目录下。    
- 如需使用动态库或静态库，则需自行在生成的 makefile 中加入相关代码。
- 方便起见，可以将此文件放到 /bin/ 下，只需简单调用就可生成 makefile。

## 关于依赖关系
对于 makefile 中的以下代码: 

```
sinclude $(SRC:.cpp=.d)
%.o : %.cpp
	$(CC) $(CFLAGS) -c $<
```

- 如果 `.cpp` 文件 比 `.o` 新，那么会重新生成 `.o` 。判断是否重新生成 `.o` 文件的唯一标准是它们两个之间的时间顺序。  
- 而对于 c++ 文件，每一个 cpp 文件是否需要重新编译实际上是还要看它所包含的头文件，如果头文件修改了，这个 cpp 也是需要重新编译的。所以通过 `g++ -MM file.cpp` 生成的依赖关系，并将这些依赖文件与 `.o` 文件的时间进行对比来判断是否需要执行 `$(CC) $(CFLAGS) -c $<`。