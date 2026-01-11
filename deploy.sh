#!/bin/bash

# 遇到错误立即停止
set -e

# 定义目录
BUILD_DIR="build"
DIST_DIR="deploy"
PACKAGE_NAME="BadApple_Linux_v1.0.tar.gz"

echo "=========================================="
echo "   BadApple ASCII Player - Deployment     "
echo "=========================================="

# 清理环境
echo "[1/5] Cleaning previous builds..."
rm -rf $BUILD_DIR
rm -rf $DIST_DIR
rm -f $PACKAGE_NAME

# 配置项目 (Release 模式)
echo "[2/5] Configuring CMake..."
cmake -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Release

# 编译
echo "[3/5] Building project..."
# -j$(nproc) 表示使用所有 CPU 核心并行编译
cmake --build $BUILD_DIR --config Release -j$(nproc)

# 安装 (触发 CMake 的 install 逻辑)
echo "[4/5] Installing artifacts..."
cmake --install $BUILD_DIR --prefix ./$DIST_DIR

# 打包
echo "[5/5] Packaging to $PACKAGE_NAME..."
cd $DIST_DIR
# 压缩当前目录下的所有内容 (./*) 输出到上一级目录 (../$PACKAGE_NAME)
tar -czvf ../$PACKAGE_NAME ./*

# 返回原目录
cd ..

echo "=========================================="
echo "   SUCCESS! Package created: $PACKAGE_NAME"
echo "=========================================="