# ASCII Video Player (基于控制台的字符画播放器)

这是一个基于 C++17 开发的高性能控制台视频播放器. 它能够读取常见的视频文件, 将其实时转换为 ASCII 字符画并在终端中播放, 同时保持高精度的音画同步. 

虽然本项目的默认演示视频是 "Bad Apple!!", 但它**完全支持播放任何你喜欢的视频文件**. 

## ✨ 特性 (Features)

- **跨平台支持**：完美运行于 **Windows** (CMD/PowerShell) 和 **Linux** (Terminal/WSL). 
- **音画同步**：基于音频主时钟的同步机制, 解决字符渲染延迟导致的音画脱节问题. 
- **高性能渲染**：使用底层控制台 API (Windows) 和 ANSI 转义序列 (Linux) 进行无闪烁渲染. 
- **极简依赖**：音频库采用 `miniaudio` (子模块集成), 视频库依赖 OpenCV. 
- **自动部署**：提供一键构建与打包脚本, 自动处理依赖复制. 

---

## 📥 下载与运行 (For Users)

如果您只是想运行程序, 不需要安装任何开发环境, 请按照以下步骤操作：

### 1. 下载

前往本项目的 **[Releases](https://github.com/mikami-w/bad_apple_ascii/releases)** 页面, 根据您的操作系统下载最新的压缩包：

- **Windows**: `BadApple_Windows_v1.0.zip`
- **Linux**: `BadApple_Linux_v1.0.tar.gz`

### 2. 解压

解压缩下载的文件. 请确保解压后的文件夹结构完整 (一定要包含 `resources` 文件夹和 `.dll` 文件). 

### 3. 运行方式

#### 方式 A：直接运行

这是最简单的运行方式, 将播放默认配置的视频. 

- **Windows**: 直接双击文件夹中的 `bad_apple_ascii.exe`. 
- **Linux**: 在终端中运行 `./bad_apple_ascii`. 

#### 方式 B：带参数运行

程序支持通过命令行参数传入一个整数配置项以指定播放画面宽度, 单位为字符. 

**Windows (PowerShell/CMD):**

```powershell
# 进入程序目录
cd path/to/extracted/folder
# 运行并传入参数 (例如 120)
.\bad_apple_ascii.exe 120
```

**Linux:**

```bash
# 进入程序目录
cd path/to/extracted/folder
# 运行并传入参数
./bad_apple_ascii 1
```

---

## 🛠️ 从源码构建 (For Developers)

如果您想要修改代码或自己编译项目, 请按照以下步骤操作. 

### 1. 环境依赖 (Prerequisites)

- **CMake**: 3.28 或更高版本
- **C++ 编译器**: 支持 C++17 (GCC, Clang, 或 MSVC)
- **Git**: 用于拉取代码
- **OpenCV**:
- **Linux**: `sudo apt install libopencv-dev`
- **Windows**: 下载预编译库, 并确保构建脚本能找到它. 



### 2. 克隆仓库

由于项目使用了 git 子模块 (`miniaudio`), 请务必使用 `--recursive` 参数：

```bash
git clone --recursive https://github.com/mikami-w/bad_apple_ascii.git
cd bad-apple-ascii
```

### 3. 一键构建与打包

项目提供了自动化脚本, 会自动完成编译、资源复制和依赖打包. 

**Windows (PowerShell):**

```powershell
./deploy.ps1
```

*构建完成后, 可执行文件位于 `deploy/` 目录下.*

**Linux (Bash):**

```bash
chmod +x deploy.sh
./deploy.sh
```

*构建完成后, 可执行文件位于 `deploy/` 目录下.*

---

## 🎬 如何播放任意视频 (自定义教程)

本项目不仅仅是 Bad Apple 播放器, 你可以用它播放任何视频 (如《Rick Roll》、《MARENOL》等). 这适用于**所有用户** (无论你是下载的还是自己编译的). 

由于程序默认读取 `resources/` 目录下的特定文件名, 替换视频的方法如下：

### 步骤 1：准备素材

准备好你的视频文件 (建议 `.mp4`) 和对应的音频文件. 

- **推荐**：为了最佳的兼容性, 建议将音频单独提取为 `.mp3` 或 `.wav` 格式. 
- **工具提示**: 你可以使用 ffmpeg 提取或转码视频与音频.

### 步骤 2：替换资源

打开程序目录下的 **`resources/`** 文件夹. 

1. 删除原有的 `ba_video.mp4` 和 `ba_audio.wav`. 
2. 将你的视频文件重命名为 **`ba_video.mp4`**. 
3. 将你的音频文件重命名为 **`ba_audio.wav`** (若要使用格式 wav 以外的格式, 请对应修改代码中硬编码的路径, 在`main.cpp`中). 
4. 将它们放入 `resources/` 文件夹. 

### 步骤 3：享受 ASCII ART

重新运行程序, 即可看到你的自定义视频转字符画的效果. 

---

## ❓ 常见问题 (FAQ)

**Q: Windows 上提示找不到 DLL？**
A: 请确保您解压了压缩包中的**所有文件**, 并且 `bad_apple_ascii.exe` 旁边有相关的 `.dll` 文件 (如 `opencv_videoio_ffmpeg...`). 

**Q: Linux 上运行报错？**
A: 确保你已经安装了 `libopencv-dev`. 本项目在 Linux 上采用动态链接系统库的方式, 不打包 `.so` 文件. 

**Q: 画面比声音快/慢？**
A: 这是由于音频延迟造成的. 请不要使用 WSL 或其他靠网络传输的远程终端, 这会由网络传输延迟造成几乎无法避免的音频延迟. 

---

## 📜 License

License & Copyright Note: The code in this repository is licensed under the MIT License. However, the media assets ("Bad Apple!!" video and audio) are the intellectual property of their respective creators (Team Shanghai Alice, Alstroemeria Records, etc.). This project is a derivative fan work and is not affiliated with the copyright holders.
