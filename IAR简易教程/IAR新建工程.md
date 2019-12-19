[北京龙邱智能科技](http://shop36265907.taobao.com)

![北京龙邱智能科技](https://note.youdao.com/yws/api/personal/file/WEB8a51a3385904ba8d4505271e9e9be364?method=download&shareKey=c0de97cb64246fe4120904147dbaf057 "北京龙邱智能科技")

# IAR新建工程

>本教程适用于初次接触IAR的同学，通过介绍IAR如何新建工程，了解一些常用工程选项的作用。

## 创建工程文件夹

>这里以新建一个LPC54606工程为例

* 根据龙邱例程，创建工程文件夹（如果根据其他工程新建，可以打开对应工程，将使用到的文件复制到新建工程中）  
龙邱提供的LPC54606例程的文件结构如下

>├─CMSIS                          ARM的CMSIS库 包涵一些内核头文件等  
>├─Drivers                        芯片的驱动文件   
>│  ├─board                       从官方SDK中保留下来的东西  包括时钟初始化   Debug串口初始化等  
>│  ├─drivers                     底层驱动库   
>│  │  ├─FSL_LPC54606             官方FSL底层驱动文件  
>│  │  └─LQ_LPC54606              龙邱基于官方FSL库的上层驱动文件   
>│  │      ├─peripheral           基于龙邱的上层驱动文件 一些外设模块库   
>│  │      └─test                 基于外设模块库 做的测试文件  
>│  ├─startup                     启动汇编文件  
>│  │  ├─arm                      MDK使用的汇编文件  
>│  │  │        
>│  │  ├─gcc                      GCC使用的汇编文件  
>│  │  │         
>│  │  └─iar                      IAR使用的汇编文件  
>│  │            
>│  └─utilities                   从官方SDK中保留下来的东西  Debug控制台等内容  
>│            
>├─Example                        例子工程  龙邱的demo都是基于同一套底层文件  
>│  ├─example                     例子工程  用户可以直接基于这个工程做应用开发   

* 将使用到的文件复制到对应文件夹  
创建一个IAR_Project文件夹，将CMSIS和Drivers文件夹复制到IAR_Project文件夹中。

![图片](https://note.youdao.com/yws/api/personal/file/WEB65ec960b060687fc13b2b9e808e51959?method=download&shareKey=50a73dab776d5f17b3eadc7863463ebe)

## 新建工程  

>打开IAR，这里使用IAR8.2版本

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBf5821286f39d98d498ad23623dd7b5fa?method=download&shareKey=c737bd3b272dd85920df204225e8638e)

## 添加文件分组

上面新建了一个空的工程，我们需要将使用的文件添加到工程里面（注意CMSIS的.h头文件这里没有添加，因为.h文件可以不添加进工程分组里面）。
>├─board                          从官方SDK中保留下来的东西  包括时钟初始化  
>├─doc                            说明文档  
>├─drivers                        官方底层fsl库文件  
>├─lpc54606                       龙邱基于官方FSL库的上层驱动文件   
>├─peripheral                     基于龙邱的上层驱动文件 一些外设模块库   
>├─source                         主函数（不同例程，一般只有这里不一样）   
>├─startup                        启动文件  
>├─Test                           基于外设模块库 做的测试文件     
>├─uitlities                      从官方SDK中保留下来的东西  Debug控制台等内容   
>├─Output                         IAR生成的.map文件，包涵许多重要信息  

* 选中lpc54606工程 右键添加分组

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB0f43c1c68405a2919dab1a0123027224?method=download&shareKey=4060faa60f4b81909335c3d4b1a331db)

* 选中lpc54606分组文件夹 右键添加文件

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBfc9b0b96239f777f846bc189256d0df4?method=download&shareKey=5fff29d28911224c73f7aede5254fe81)

* 将龙邱工程中example文件夹下的mian.c 和include.h复制并添加到新工程

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB1310d361d7cd1f5c2c397ede89c13431?method=download&shareKey=14b3047439fa7347cb6353081d485938)

## 设置工程配置
* 选择芯片
>选择芯片后，如果芯片有硬件浮点单元会默认开启（注意需要单片机有硬件浮点单元，MK60DN就没有）

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB97bddd774277612433d89105465ac1b3?method=download&shareKey=b434f62cc6cb98eadc210d2e65b33030)

* printf 和 scanf 都选择支持全功能格式

>（支持浮点数）

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB1e6bfcf3155511f6d63fb19962fc77aa?method=download&shareKey=23bf7b420fb4d09ca2a17e803b53f8d7)

* 添加头文件路径  

>我们已经将文件添加到工程中了，但是编译的时候，报错找不到对应头文件。每个人的习惯不一样，头文件存放位置也不一样，因此需要将所有头文件位置告诉编译器，让编译器知道去那个文件夹找头文件（如果自己新写了头文件，记得将自己的头文件路径添加进来）。注意使用相对路径，如果使用绝对路径，当工程位置移动时，就会找不到头文件。
>>>$PROJ_DIR$\\..\\..\\..\CMSIS\Include  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\board  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\drivers\FSL_LPC54606  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\drivers\LQ_LPC54606  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\drivers\LQ_LPC54606\peripheral  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\drivers\LQ_LPC54606\test  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\startup\iar  
>>>$PROJ_DIR$\\..\\..\\..\Drivers\utilities  
>>>$PROJ_DIR$\\..\\..\\..\Drivers  
>>>$PROJ_DIR$\\..  

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBe7345948a6c7c5df0b84dba8963fac84?method=download&shareKey=ef6a540d8c27ee168c6535ce7b634f58)

* 添加全局宏定义

>将龙邱例程中的全局宏定义复制到新工程
>>>DEBUG  
>>>_DLIB_FILE_DESCRIPTOR  
>>>CPU_LPC54606  
>>>CPU_LPC54606J512BD100=1  
>>>PRINTF_FLOAT_ENABLE=1  
>>>SCANF_FLOAT_ENABLE=1  
>>>PRINTF_ADVANCED_ENABLE=1  
>>>SCANF_ADVANCED_ENABLE=1  

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB09110359855ef60de3caaa44ce41c1cb?method=download&shareKey=8113de22dc22922e3af397fee9b92b47)

* 生成debug调试信息

>仿真调试时需要使用

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB5021d6a32818ce476bb53a47e9186597?method=download&shareKey=6a3dc1bc94607cc428c50091530a89d2)

* 优化等级

>优化等级是一个比较重要的配置，优化等级越高，生成的bin文件就越小，一般情况下代码的运行速度也会提高，但是在Debug调试的时候，由于优化，代码可能不会顺序执行，调试的时候可以将代码优化等级调到最低。

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBfc6a50ad032917bcf6219980135d7235?method=download&shareKey=ca849b1dddeb18a942be5a2f28f1c839)

* 屏蔽警告

>官方fsl库在编译时存在一些警告信息，因此我们参考官方SDK将对应的警告号屏蔽即可。

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB72807484fc4b55d9bb3f0af370e8a2af?method=download&shareKey=0099e6f9cb99bc96ba78dae994131ecc)

* 分散加载文件

>不同单片机RAM和FLASH起始地址和大小不尽相同，而且还可能外扩DRAM和FLASH，因此IAR中使用一个脚本.icf文件来确定工程的分散加载信息。IAR有自带的分散加载文件，但是这里我们使用自己修改过的分散加载文件。注意使用相对路径，如果使用绝对路径，当工程位置移动时，就会找不到分散加载文件。  

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB77f5bfbe68347f2105d1f55dc752b698?method=download&shareKey=8c58f9ce91dc79ed0dff26d49ea72bd2)

* 电源管理lib库

>NXP为了让用户更方便的使用电源低功耗，将相应的电源管理封装起来，做成lib库文件。

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEB35c507cfa056e7ef9d17843b114f6d3f?method=download&shareKey=7795a2d61034301875e39050a2b39a70)

* debug下载器配置

>IAR并不知道你使用什么下载器，因此需要你告诉IAR你使用的什么下载器。

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBe354c55978cbbebf88f1f0916f550c8c?method=download&shareKey=da6e94d2144f747c1690635cc5e7d95f)

## 添加工程分组

>经过上面的配置后，程序以及可以通过jlink烧录进单片机，但是有时候我们的Debug时，使用最低的优化等级。Debug完成后使用较高的优化等级，每次都有修改配置。 可不可以生成两套配置？  
> IAR可以添加分组，使一个代码可以有多种不同的配置。  
* 删除一种配置分组

>默认新建的工程都有两种配置 debug和release，上面我们配置了debug的配置，但是release还没有配置，将release删掉。

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBc64dc0c11e1b982a4641f61aa6246a50?method=download&shareKey=1c4094e7bb5f888d37a020d0748203e9)

* 添加一种配置分组

>基于debug配置，生成新的release分组

![在这里插入图片描述](https://note.youdao.com/yws/api/personal/file/WEBd5054c783f154341d9082a468d2f7a65?method=download&shareKey=154babe1d0b14c4b014a8c9862bad094)

## 总结

其实用户没必要新建工程，一些新手感觉例程里面文件过多，可能会影响单片机效率，影响文件可读性。

* 关于效率问题，在编译链接环节，根据IAR优化等级会将不使用的函数、变量删除，并不会添加到最终的bin文件中，因此不会影响效率，也不会增大代码量。

* 可读性，基于龙邱的例子工程，用户可以自行删减未使用到的文件，减少文件数量，增加代码可读性。
