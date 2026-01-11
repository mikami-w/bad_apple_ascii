# 设置错误时停止执行
$ErrorActionPreference = "Stop"

$BuildDir = "build"
$DistDir = "deploy"
$PackageName = "BadApple_Windows_v1.0.zip"

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "   BadApple ASCII Player - Deployment     " -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# 清理环境
Write-Host "[1/5] Cleaning previous builds..." -ForegroundColor Yellow
if (Test-Path $BuildDir) { Remove-Item -Recurse -Force $BuildDir }
if (Test-Path $DistDir) { Remove-Item -Recurse -Force $DistDir }
if (Test-Path $PackageName) { Remove-Item -Force $PackageName }

# 配置项目
# 注意：如果使用的是 MinGW，CMake 会自动检测。如果是 VS，也会自动检测。
# 如果想强制指定生成器（例如 MinGW Makefiles），可以在下面加 -G "MinGW Makefiles"
Write-Host "[2/5] Configuring CMake..." -ForegroundColor Yellow
cmake -B $BuildDir

# 编译 (Release 模式)
Write-Host "[3/5] Building project..." -ForegroundColor Yellow
cmake --build $BuildDir --config Release

# 安装 (触发 CMake 的 install 逻辑)
Write-Host "[4/5] Installing artifacts..." -ForegroundColor Yellow
cmake --install $BuildDir --config Release --prefix $DistDir

# 打包
Write-Host "[5/5] Packaging to $PackageName..." -ForegroundColor Yellow
$SourcePath = Join-Path $DistDir "*"
Compress-Archive -Path $SourcePath -DestinationPath $PackageName

Write-Host "==========================================" -ForegroundColor Green
Write-Host "   SUCCESS! Package created: $PackageName" -ForegroundColor Green
Write-Host "==========================================" -ForegroundColor Green

Read-Host -Prompt "Press Enter to exit"