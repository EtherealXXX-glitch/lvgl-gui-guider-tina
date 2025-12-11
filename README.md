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
    ├── lv_86_boxes
    ├── lv_drivers
    ├── lv_examples
    ├── lv_g2d_test
    ├── lvgl
    ├── lv_monitor
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