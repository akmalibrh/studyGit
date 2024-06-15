# TugasBesarEL2008 Kelompok 7

## Getting Started

1. Clone repository ini
   ```sh
   git clone https://github.com/frozel15/TugasBesarEL2008.git
   ```
2. Masuk ke folder
   ```sh
   cd TugasBesarEL2008
   ```
3. Pindah ke branch ini
   ```sh
   git checkout nogui
   ```

Untuk windows:
1. Install MSYS2
2. Install GCC dan Make di MSYS2 Shell
   ```sh
   pacman -S mingw-w64-x86_64-toolchain base-devel mingw-w64-x86_64-minizip mingw-w64-x86_64-gcc mingw-w64-x86_64-xlsxio
   ```
3. Build program di terminal MSYS2
   ```sh
   make
   ```
4. Atau, jika terinstall MinGW, build program di PowerShell/Command Prompt
   ```
   mingw32-make.exe
   ```
5. Jalankan program
   ```
   ./main.exe
   ```
