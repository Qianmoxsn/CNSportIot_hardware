# CNSportIot_hardware

本项目为 CNSportIot 的硬件子项目，项目其他仓库链接：  

[项目总看板]()


---

## 工程描述

项目基于 PlatformIO 开发构建，其主要包含`data`、`include`、`lib`、`src`、`test`、`platformio.ini`六个部分，其中：

- `data` 包含一些配置文件，通过工具存储到 SPIFFS 中
- `lib` 为工程依赖的库（本地，通过 platefromio.ini 中的 lib_deps 配置的库位于 `~/.pio/libdeps/<env>/`）
- `src` 为项目工程源码
- `platformio.ini` 为 PlatformIO 的配置文件
- `test`、`include` 尚未涉及，详见[PlatformIO 文档](https://docs.platformio.org/en/latest/projectconf.html)

## 项目构建及烧录运行

### 驱动准备

使用沁恒`CH340`系列芯片需要安装驱动，驱动下载地址：[CH340 驱动下载](http://www.wch.cn/download/CH341SER_EXE.html)。

> 注：`2023/03/16(3.8)` 版驱动在 `win11` 系统构建时出现权限错误，使用 `2019/03/18(3.5)` 版尚未出现问题  
> [v3.5 版驱动下载](https://web.archive.org/web/20191222125650/https://www.wch.cn/download/CH341SER_EXE.html)

### 环境准备

#### 安装`VSCode`，并安装`PlatformIO`插件(略)

知乎上面有很多教程

#### build & upload

1. 打开 `VSCode` ，打开本项目
2. 修改 `data/config.json` 中的配置信息
3. 进入 PIO 主页 `PROJECT TASKS`，选择 `env` ，在 `Platform` 选项组中点击`Build Filesystem Image` 和 `Upload Filesystem Image`，等待配置文件烧写完成
4. 在 `General` 选项组中点击 `Build` 和 `Upload`，等待程序烧写完成（完全等效于底部快捷按钮）
