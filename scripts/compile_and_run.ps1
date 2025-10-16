# Helper script to compile and run SMARTMARKET with raylib using MinGW

$raylib = "C:/Users/a35560/SmartMarket/raylib"
$gpp = "C:/Users/a35560/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.MCF.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin/g++.EXE"
$src = "src"
$build = "build"
$exe = "$build/smartmarket.exe"

# Create build dir
if (!(Test-Path $build)) { New-Item -ItemType Directory -Path $build | Out-Null }

# Collect sources
$sources = Get-ChildItem -Path $src -Filter *.cpp -Recurse | ForEach-Object { $_.FullName }

# Compile command
$include = "-I$($raylib)/include -Iinclude"
$libs = "-L$($raylib)/lib -lraylib -lopengl32 -lgdi32 -lwinmm"
$flags = "-std=c++17 -Wall -Wextra"

$cmd = "$gpp $flags $include $($sources -join ' ') -o $exe $libs"
Write-Host "Compiling with:" $cmd

Invoke-Expression $cmd

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build succeeded. Running executable..."
    $env:PATH = "$($raylib)/lib;" + $env:PATH
    & $exe
} else {
    Write-Host "Build failed with exit code $LASTEXITCODE"
}
