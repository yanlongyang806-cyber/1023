# VehPatchSmart - DLL Patch for WorldServer

## 项目简介

**VehPatchSmart** 是一个用于 **worldserver.exe** 的 DLL 补丁程序，旨在通过 **VEH (Vectored Exception Handler)** 异常处理机制捕获并跳过特定的崩溃指令，增强程序的稳定性。该补丁主要用于在程序崩溃时避免导致的崩溃，并尝试智能跳过崩溃地址。

此项目还包括了日志记录和自动化构建功能，支持持续集成（CI）和持续交付（CD）。

## 特性

- **VEH 异常处理**：捕获并跳过崩溃指令，避免程序因访问违规、非法指令等崩溃。
- **日志系统**：记录关键异常信息并管理日志文件。
- **动态崩溃地址处理**：通过历史崩溃数据动态调整崩溃地址处理策略。
- **自动化构建**：集成 GitHub Actions 实现自动化构建和测试。
- **支持 Windows**：目前只支持 Windows 平台的应用。

## 安装与使用

1. 克隆仓库到本地：
   ```bash
   git clone https://github.com/your-username/your-repo.git
