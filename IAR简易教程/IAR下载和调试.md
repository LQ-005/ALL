[北京龙邱智能科技](http://shop36265907.taobao.com)

![北京龙邱智能科技](https://note.youdao.com/yws/api/personal/file/WEB8a51a3385904ba8d4505271e9e9be364?method=download&shareKey=c0de97cb64246fe4120904147dbaf057 "北京龙邱智能科技")

# IAR下载

>下载器与单片机之间的接线有两种JTAG和SWD，SWD只需要四根线（GND、TCK、TMS、RST（可选）），一般使用SWD接线即可。

1) 硬件连接


* 使用龙邱下载器的  
---

龙邱核心板的下载接口丝印层都有一个白色凸口，对应龙邱下载器排线的凸口。  

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB2b1ad5fb5efe4af5ec4b0d666a7c1566?method=download&shareKey=c7f2595bf7d66d96ad2df038ef03b427">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBc513f27a220d0099e4b95ea7d5a01bb9?method=download&shareKey=1d363eaa1f59e35f7596a40a7e6a7d40">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB78620a778f1182a0cadc69cf0e173650?method=download&shareKey=8f1665f86b89bae264a2af24780063d4">
</div>

* 使用其他下载器的  
---

如果没有使用龙邱下载器，打开核心板原理图，找到下载口部分，接线对应即可：
<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB3973a1d686a9e82352040f43c45382d8?method=download&shareKey=7fb27a8050e12645709af14d8737545c">
</div>

      单片机SWDIO(TMS)  -----  下载器SWDIO(TMS)
      单片机SWDIO(TMS)  -----  下载器SWCLK(TCK)
      单片机RST         -----  下载器RST

下载器哪个管脚是SWDIO、哪个是SWCLK，打开盒子看丝印或者问卖家。一般常用的20Pin接口图
<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBf3b52488139b137e932620ed3668b10f?method=download&shareKey=5446b3f3a325007974ee1e9f4ec52c0b">
</div>

---
---
---

2) 软件配置  

>>IAR并不知道你使用什么下载器，因此需要你告诉IAR你使用的什么下载器。

* 使用JLink-V9下载
---

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBcb332b1cca0ba3655aa8331e6bbc4931?method=download&shareKey=438ffe63d8e040f9d50e63f353e25cc1">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB567bb84238321e8ff417f75fb2f3ddfb?method=download&shareKey=88f34ac8ce4fc33499145d533b6a9b0c">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB3da1bb9ab9a3b23cd08cb1c402a2cb7d?method=download&shareKey=9c0bf7c3b3c0ad7b30c11f86b54dfb1d">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB194171059b8edc1e5d4ff52e1efba7fc?method=download&shareKey=947fdccc16c388f3d925f1334b1f9eae">
</div>

* 使用DAPLink下载
---

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBcb332b1cca0ba3655aa8331e6bbc4931?method=download&shareKey=438ffe63d8e040f9d50e63f353e25cc1">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB9f3ee75785d0fa5202d0fe451587fa72?method=download&shareKey=f94c4f27f763387eaef0721161d62462">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB3da1bb9ab9a3b23cd08cb1c402a2cb7d?method=download&shareKey=9c0bf7c3b3c0ad7b30c11f86b54dfb1d">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB5952f32a4fc9cf94f835a1f49ee7329c?method=download&shareKey=d4974fb31f97fa8e7d62cc5461fbe8ef">
</div>

---
---
---

# IAR调试

>下载器和核心板接好线并且在IAR中选择好下载器，就可以下载调试了，调试时最好把优化等级调低（参考IAR常用功能简介）。  

## 调试常用按键说明

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBe46879c73e6019d93583fc2a06c359b2?method=download&shareKey=cc4b17c487230595bd4ce9ae3d530a7d">
</div>

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB08f0da20f9b7c387b7c02b7f17d68c36?method=download&shareKey=9fb0665df9a4392fc4f49628c04f10f9">
</div>

* 第 1 个图标是重新编译例程并进入调试状态。

* 第 2 个图标是重新进入调试状态。

* 第 3 个图标是退出调试。

* 第 4 个图标是每次点击以函数为单位运行，不会进入函数内部。

* 第 5 个图标是单步调试，每次点击运行一行代码，所以只要有子函数就会进入。

* 第 6 个图标是退出当前执行函数，点击后退出当前运行的函数，执行下一个函数。

* 第 7 个图标是进入下一个状态，跟第 4 个图标
功能差不多。

* 第 8 个图标是直接运行到光标处，用户用鼠标左键点击一下，可以看到前面有光标即可。

* 第 9 个图标是全速运行（经常和断点配合使用）。

* 第 10 个图标是用于暂停全速运行。

* 第 11 个图标是复位调试，重新回到 main 函数开始执行。

## 断点

>>在Debug过程中，通常只需要重点关注某一部分代码，让程序运行到指定位置后，再单步调试，进行分析。  

经过上面debug按键介绍，可以使用第8个图标让程序运行到指定位置，当然也可以使用断点+全速运行的方法让程序运行到指定位置。

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBae2cab0d8627b93c5309aaf87530aacb?method=download&shareKey=15f09ee0d6816e6592e4954441a17f67">
</div>

## 寄存器查看说明

>>进行底层开发时，需要查看寄存器的值

打开寄存器窗口

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBc8f5cd676bf52565ae2187a5760a7e94?method=download&shareKey=afe18653eafa4dcf4c07df8353a3bd65">
</div>

右键选择对应寄存器窗口

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB45f4fec1f472eadc13248984bfe432a9?method=download&shareKey=e0c994c42231c54c990347609fa5b4dc">
</div>

## 全局变量查看

>>全局变量占用的内存空间是固定的，程序访问该全局变量时直接访问该地址空间即可，因此全局变量可以在live watch中实时显示。但是局部变量是存储在栈空间中的，当退出局部变量作用域时，该局部变量占用的内存空间就会被系统回收，相当于这个变量就没了，因此watch窗口中查看局部变量时，确保程序在局部变量的作用域内，否则会显示ERROR。

* watch窗口

>>>watch窗口可以查看全局变量和局部变量（查看局部变量时，确保程序在局部变量的作用域内，否则会显示ERROR）。不过watch窗口在全速运行时，里面的变量不能刷新。

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEBc70b1be6ed3e3dc680cfc748e9f4922e?method=download&shareKey=f5501a399bfed948fae7810237a50aa6">
</div>

* live watch窗口

>>>live watch窗口可以查看全局变量。不过live watch窗口不可以查看局部变量，在全速运行时，live watch里面的变量会实时刷新。

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB0cd99a59928a901dcbde7a4d73e41e0b?method=download&shareKey=91b79e9861f836620a175ab279b21580">
</div>

* 局部变量窗口

>>>可以显示当前栈空间下的局部变量

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB69f5cd027713a0de2ab99eb767cc7d2b?method=download&shareKey=f1f58028a3e34ace5f983a6754fbecb5">
</div>

## 其他窗口

<div align="center">
<img src="https://note.youdao.com/yws/api/personal/file/WEB38773294883796ac12175194f8745d70?method=download&shareKey=eb8b81a53da2b1215be5ff4a230823e5">
</div>



## 调试基本思想

>>好多同学拿到调试器后，就只是当作下载器用。不知道怎么去仿真，遇到问题之后，就直接跑过来，啥情况啊？咋回事啊？我......

 遇到问题后，首先分析问题，举个例子：

 我的程序里设置是小车在拐弯时减速，但是实际发现并没有减速？

 思考为啥没有减少？  

 可能没检测到拐弯！  

 进行Debug，设置一个入弯标志位，拐弯时检查入弯标志位，看是否检测到入弯。  

 这里假设检测到了入弯，那么再次思考，为啥没有减速？速度是哪里来的？  

 这里假设速度和PWM控制信号占空比正相关，没有减速，那就是证明，PWM信号占空比没有降低。思考为啥PWM信号占空比没有降低？ PWM信号哪里来的？  

这里假设PWM占空比是由PID控制的，进行Debug，查看PID控制器的输入信号和各个分量的输出。  

......

总结：整个Debug的思路就是找到异常，分析异常，追踪异常，找到异常根源，解决问题。
