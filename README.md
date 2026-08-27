<div align="center">

# 🏎️ ASC-Round2

**ASC 实验室 · 智能车竞赛 · STM32 嵌入式控制**

![STM32](https://img.shields.io/badge/MCU-STM32F103C8-blue)
![Keil](https://img.shields.io/badge/IDE-Keil%20MDK-green)
![Lang](https://img.shields.io/badge/Language-C-orange)

</div>

## 📋 项目简介

ASC 实验室智能车竞赛**第 2 轮**代码。

基于 **STM32F103C8**（ARM Cortex-M3）的智能车嵌入式控制系统，使用 Keil MDK 开发，采用 STM32F10x 标准外设库。

## ✨ 功能特性

| 功能 | 说明 |
|---|---|
| 🛞 编码器测速 | 硬件编码器实时测量车轮转速，供闭环控制使用 |
| 📟 OLED 显示 | SSD1306 驱动 OLED 屏，展示菜单 / 状态 / 数据 |
| 🔘 按键交互 | 独立按键输入，配合 OLED 菜单系统操作 |
| 💡 LED 指示 | 状态指示灯 |
| ⏱ 延时 / 定时 | System 层通用 Delay / Timer 模块 |

## 🛠 技术栈

| 项 | 说明 |
|---|---|
| 主控 | STM32F103C8（ARM Cortex-M3） |
| 外设库 | STM32F10x 标准外设库（SPL） |
| 开发环境 | Keil MDK |
| 语言 | C（含汇编启动文件） |

## 📁 工程结构



## 🔨 编译与烧录

1. 用 **Keil MDK** 打开工程
2. 选择 **STM32F103C8** 目标
3. **Build** 编译生成 
4. 通过 ST-Link / SWD 或串口 ISP 烧录到开发板

## 📄 License

[MIT](LICENSE)
