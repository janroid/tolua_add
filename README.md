# tolua++参考手册 #

本文档主要向大家介绍下如何在Windows环境下编译tolua++，和在cocos2d-x中如何使用tolua++。
本文档主要针对lua5.1+SCons环境来编译tolua++，如果不是使用这个环境，请自查查阅。

## 一、准备工作 ##
1. 安装lua环境，我使用的是lua5.1版本，下载地址：http://www.lua.org/download.html;
2. tolua++，最新版本是1.0.93，目前官网下载地址已经关闭了，本仓库tolua文件夹即是解压后的文件。
3. Scons安装，我用的版本是2.0.1，安装文件放在本仓库tools文件夹下，如果想使用其他版本，请自行下载：https://sourceforge.net/projects/scons
4. python安装，请安装python2.7
5. gcc安装

## 二、软件安装 ##
1. lua和python软件安装，因为比较普遍，这里就不说了，大家可以网上自行搜索，不过要注意下安装完成后，要记得配置环境变量。
2. Scons安装：
	1. 解压tools下Scons压缩文件。
	2. 命令行进入解压后的文件夹，
	3. 键入python setup.py install进行安装。
	
3. gcc 安装
	1. 详情查看这位兄弟的教程：[www.jianshu.com/p/ff24a81f3637](http://www.jianshu.com/p/ff24a81f3637 "安装教程")
	2. 或者自己在www.mingw.org下载安装软件--

## 三、windows下使用SCons编译tolua++ ##
当上述步骤完成后，现在就可以编译tolua++了，按以下步骤完成：

1. 找到lua安装目录，比如我的安装目录：C:\Program Files (x86)\Lua\5.1，拷贝include文件夹下的头文件到仓库中tolua\include下。同时拷贝lib目录下lua5.1.dll和lua51.dll文件到仓库tolua\lib和tolua\bin下。
2. 修改仓库tolua目录下config_posix.py文件中LIBS=['lua','lualib','m']为LIBS=['lua51']。
3. 使用命令行进到tolua目录下，使用命令：scons all完成安装，此时，可以看到bin目录下多了2个exe程序，lib目录下多了一个包。

## 四、使用范例 ##
上面讲了tolua++的编译，下面使用实际例子讲解一下。首先，正常编写 c++ 代码，这里我们创建一个类，更多使用请移步：[https://github.com/dabing1022/Blog/blob/master/tolua/tolua%2B%2B%E4%B8%AD%E6%96%87%E5%8F%82%E8%80%83%E6%89%8B%E5%86%8C%5B%E5%AE%8C%E6%95%B4%E7%BF%BB%E8%AF%91%5D.md](https://github.com/dabing1022/Blog/blob/master/tolua/tolua%2B%2B%E4%B8%AD%E6%96%87%E5%8F%82%E8%80%83%E6%89%8B%E5%86%8C%5B%E5%AE%8C%E6%95%B4%E7%BF%BB%E8%AF%91%5D.md)
 
**mylib.h**
 
    //mylib.h
    class Test
    {
    	public:
    		Test(int a, int b);
   			~Test();
    		void sayHello();
    		int add();
    		int getA();
    
    	private:
    		int a;
    		int b;
    };

**mylib.cpp**

    //mylib.cpp
    #include "mylib.h"
    #include <iostream>
    
    Test::Test(int a, int b)
    {
    	this->a = a;
    	this->b = b;
    }
    
    Test::~Test()
    {
    }
    
    void Test::sayHello()
    {
    	std::cout << "hello world" << std::endl;
    }
    
    int Test::add()
    {
    	return this->a + this->b;
    }
    
    int Test::getA()
    {
    	return this->a;
    }

**mylib.pkg**

	$#include "mylib.h"
	class Test
	{
	    Test(int, int);
	    ~Test();
	    void sayHello();
	    int add();  
	    int getA();
	};

可以看到 package 文件和 c++ 头文件基本一致，要注意的是要在文件头引入头文件，然后把 public 关键字去掉。所有公有的函数或数据都可以导出，如果不想导出某个函数，则在 package 文件中不要定义就可以了。

然后使用命令行进入上诉步骤生成的exe文件的目录，输入：

	tolua++ -n mylib -o tolua.cpp mylib.pkg
    
导出的文件名可以任意命名，但因为我们已经有一个原始的源文件 mylib.cpp 了，所以这里不能将导出的源文件命名为 mylib.cpp，否则后面使用的时候就会有问题，这里我命名为 tolua.cpp。还有一个要注意的就是必须把 mylib.h 跟 mylib.pkg 放在一起，因为 package 文件需要用到头文件（最好所有文件都放入同一个文件夹下）
