# lvgl-gui-guider-tina
全志t113-tina系统移植gui guider工程驱动RGB屏幕，快速开发lvgl。
...
目录结构：
(base) leon@ubuntu:~/Desktop/t113-linux/platform/apps/lvgl8-tina$ tree -L 2
.
├── build-lvgl.sh
├── build_out
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── cmake_install.cmake
│   ├── lib
│   ├── lv_drivers
│   ├── lvgl
│   └── Makefile
├── CMakeLists.txt
├── lv_2048
│   ├── bin
│   ├── res
│   └── src
├── lv_86_boxes
│   ├── res
│   └── src
├── lv_drivers
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── cmake_install.cmake
│   ├── CMakeLists.txt
│   ├── display
│   ├── docs
│   ├── gtkdrv
│   ├── indev
│   ├── library.json
│   ├── LICENSE
│   ├── lv_drivers.mk
│   ├── lv_drv_conf_template.h
│   ├── Makefile
│   ├── README.md
│   ├── sdl
│   ├── wayland
│   ├── win32drv
│   ├── win_drv.c
│   ├── win_drv.h
│   └── win_drv.o
├── lv_examples
│   └── src
├── lv_g2d_test
│   ├── res
│   └── src
├── lvgl
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── cmake_install.cmake
│   ├── CMakeLists.txt
│   ├── component.mk
│   ├── demos
│   ├── docs
│   ├── env_support
│   ├── examples
│   ├── idf_component.yml
│   ├── Kconfig
│   ├── lib
│   ├── library.json
│   ├── library.properties
│   ├── LICENCE.txt
│   ├── lv_conf_template.h
│   ├── lvgl.h
│   ├── lvgl.mk
│   ├── Makefile
│   ├── README.md
│   ├── README_pt_BR.md
│   ├── README_zh.md
│   ├── SConscript
│   ├── scripts
│   ├── src
│   └── tests
├── lv_monitor
│   └── src
└── ui
    ├── bin
    ├── README.md
    ├── res
    └── src

    这里的
    ─ ui
    ├── bin
    ├── README.md
    ├── res
    └── src
    就是自己的lvgl应用