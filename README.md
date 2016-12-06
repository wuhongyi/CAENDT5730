<!-- README.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 11月 26 16:41:07 2016 (+0800)
;; Last-Updated: 二 12月  6 14:20:12 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 11
;; URL: http://wuhongyi.cn -->

# README

本程序专为 CAEN 桌面版 Digitizer 开发。

将所有插件按照固件分为 Standard、PHA、PSD 三种类型（手中当前没有CI固件插件），封装成三个类。可扩展成支持该固件的任何插件。

当前拟支持：

- DT5730  Standard DPP-PSD (开发中，12月上旬完成)
- DT5724A Standard（开发中，12月中下旬完成）
- DT5742B Standard

方便括展支持更多插件。

----

## 运行方法

第一次运行本程序包时，需安装基本依赖软件。在 **CAEN** 文件夹下有自动安装脚本**setup.sh**，在 ROOT 权限下运行该脚本即可。

在该程序目录下新建名字为**build**文件夹，然后进入该文件夹编译程序，具体如下：

```shell
mkdir build
cd build
cmake ..
make
```

运行编译之后的可执行程序：

- 从 USB/Optical 中选择连接方式，然后按 **Connect**，如果连接成功，**Connect**按钮将变灰，出现**DeleteConnect**按钮。按钮右边将显示插件及其固件名称。
- 连接成功后，选择将要进行获取的channel，以及设置 Record Length 长度。之后按**ProgramDigitizer**按钮，成功之后再按**AllocateMemory**按钮。
- 接下来按**AdjustParFrame**按钮，将会弹出一个临时窗口（不同固件显示的界面不同），用来调节其基本参数。按钮**Load**从插件读取参数并显示到窗口，按钮**Apply**将当前参数写入插件，按钮**Cannel**用来关闭当前临时窗口。
  - **PostTrigger**为trigger点之后占总采集波形的百分比。
  - **Trigger**选择ACQ_ONLY为自触发，（x730，x725比较特殊，每两个channel为一组）
  - **Polarity**当输入信号为正信号，选择Positive时为上升沿触发，选择Negative时为下降沿触发，当输入信号为负信号时，情况相反。
  - **DC Offset** 范围为-50 - +50，-50表示动态范围为（-V，0），0表示动态范围为（-V/2，V/2），+50表示动态范围为（0，V）。
  - **Threshold** 表示阈值线在 ADC 上的位置，其量程为（0，2^NBits-1）。对标准固件，只要信号幅度超过该阈值即触发。
- 接下来按**Start/Stop**来启动/停止获取。
- 在线时时监测每路获取计数率，传输数据量。
- 在线监视某路单波形、累积波形。可用来快速确定合适阈值。
  - 选择要监视的 Channel，监视类型**Single/Mutli**，**Monitor**用来控制是否开启监视。**Clear**用来清屏。 
- （未完成）数据写入文本。
- （未完成）离线数据转化，离线数据分析，梯形算法计算能量，提取上升时间等。
- （未完成）在线计算能量等。


<!-- README.md ends here -->
