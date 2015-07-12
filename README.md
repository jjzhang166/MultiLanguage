<center>MultiLanguage</center>
==============================

What it is ?
------------
MultiLanguage 是一个用 C++ 实现的多语言模块。它从多语言文件中读取词条，并在软件运行时进行翻译。  

###特性

 - **易于新增语言**  
   新增一门语言LANG，只需要复制一份 language\_xx.txt，并重命名为: language\_LANG.txt  
   然后，在程序里调用 `set_langauge("LANG")`，即可

 - **支持任意特殊字符**    
   在多语言文件中，可以用 \xNN 在代表任意字符。比如：\x0a --> 换行符，\x41 --> 'A'

 - **支持域**   
   词条同名表示不同的意思可以用域的方式进行区分  
   比如：对话框A中的"M"要翻译成"中等"，而对话框B的"M"则要翻译成"男性"。域可以很好地区分它们，避免冲突。

 - **域继承**   
   大多数词条都能在 DomainA 中被合理翻译，但是有个别需要特殊翻译。难道要建一个 DomainB ，将 DomainA 中所有词条复制到 DomainA？如果词条上万条，将来如何维护？
   当 DomainB 继承于 DomainA ，在翻译 DomainB 的词条时，先从 DomainB 域中寻到，如果没找到便会到 DomainA 去找。

 - **支持逆翻译**  
   当A --> aa，那么逆翻译则是：aa --> A。

 - **易于调试**   
   在研发阶段，该调试功能能在词条翻译不成功时添加异常提示，使我们更容易地发展并解决翻译问题。  
   如：如果词条 "Yes" 没有找到相应的翻译，那么它则会返回 "!Yes!"。如果词条 "Yes" 有翻译，但翻译结果为空值，那么返回 "?Yes?"。   
   在产品发布阶段，可以关闭调试功能。如果词条"OK"，说算是没有被正确地翻译，翻译工具也返回"OK"

###文件格式

 - K-V 格式
 - XML 格式（预留接口，尚未实现）

#### K-V 格式
如下：  

    [A]
    OK=好的
    ERROR=错误
    M=中端

    [B:A]
    M=男性 # 这里翻译不一样

(code-1)  
用方括号包括起来的表示以下都是该域的词条，比如：[A]  
每个词条的格式都是：K=V，以等号分隔   
**支持注释：用 # 号表示行后面的都是注释**  
[B:A]，表示定义一个域 "B"，它继承于域 "A"

#### XML 格式
（尚未定义）

###依赖

 - boost库
   假定 boost库 安装在 /usr/local/boost 目录下。  
   库依赖：libboost\_system.so, libboost\_filesystem.so

###编译安装

####准备工作
假设你已在本地安装了 boost 库，安装路径为： "/usr/local/boost"  
若没有安装到该路径下，请用：`ln -s your-boost-path /usr/local/boost` 创建符号链接。  

当然，GCC 与 make 工具这是必备的。

本人使用的GCC版本信息：
gcc version 4.4.7 20120313 (Red Hat 4.4.7-11) (GCC)

####下载编译
你可以下载zip包到本地进行解压，或 `git clone` 到本地。

    cd MultiLanguage
    make && sudo make install

####运行测试

    make test

测试中，我们会看到有些错误，不必惊慌，那是目前尚未完成的功能。  

原本打算支持XML与K-V两种格式，但目前只实现了K-V格式，而XML格式的已编写了测试用例，但尚未实现。  
只要实现一种就够用了。

###集成运用

####C++
(TODO)  

####C
(TODO)  

问题反馈
--------

如果大家在使用过程中发现问题，欢迎讨论并提出宝贵的意见！  

本人联系方式如下：  

 - 博客: <http://my.oschina.net/hevakelcj>
 - QQ: 527020730
 - E-Mail: hevake\_lcj@126.com
