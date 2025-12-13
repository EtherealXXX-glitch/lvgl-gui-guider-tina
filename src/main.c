#include "lvgl/lvgl.h"               // 引入 LittlevGL 主头文件
#include "lv_drivers/display/sunxifb.h"  // 引入 Sunxi Framebuffer 显示驱动头文件
#include "lv_drivers/indev/evdev.h"      // 引入 Linux 输入设备驱动头文件（evdev）
#include <unistd.h>                   // 提供 usleep 等函数
#include <pthread.h>                  // 线程相关函数（目前代码没用到线程）
#include <time.h>                     // 时间相关函数
#include <sys/time.h>                 // gettimeofday 用于获取精确时间
#include <stdlib.h>                   // malloc/free 等标准函数
#include <stdio.h>                    // printf 函数

#include "gui_guider.h"                 // 包含GUI Guider生成的UI相关函数声明
#include "events_init.h"                // 包含事件初始化相关函数声明
#include "custom.h"                     // 包含自定义功能相关函数声明

lv_ui guider_ui;                        // 声明GUI Guider生成的UI结构体实例

static lv_style_t rect_style;         // 定义一个样式变量
static lv_obj_t *rect_obj;            // 定义一个指向对象的指针（矩形）
static lv_obj_t *canvas;              // 定义一个画布对象指针


// 打印触摸设备占用信息
void print_touch_pid(void) {
    printf("当前 /dev/input/event2 被以下进程占用:\n");
    system("lsof /dev/input/event2");
}

int main(int argc, char *argv[]) {
    lv_disp_drv_t disp_drv;           // 显示驱动结构体
    lv_disp_draw_buf_t disp_buf;      // 显示缓冲区结构体
    lv_indev_drv_t indev_drv;         // 输入设备驱动结构体
    uint32_t rotated = LV_DISP_ROT_NONE; // 显示旋转角度，0 表示不旋转

    lv_disp_drv_init(&disp_drv);      // 初始化显示驱动结构体

    /* 初始化 LittlevGL */
    lv_init();

    /* 初始化 Linux framebuffer 设备 */
    sunxifb_init(rotated);

    /* 获取屏幕尺寸，并申请绘图缓冲区 */
    static uint32_t width, height;
    sunxifb_get_sizes(&width, &height);  // 获取屏幕宽高

    static lv_color_t *buf;
    // 为 LittlevGL 分配绘图缓冲区
    buf = (lv_color_t*) sunxifb_alloc(width * height * sizeof(lv_color_t), "lv_2048");

    if (buf == NULL) {
        // 如果分配失败，释放 framebuffer 并退出程序
        sunxifb_exit();
        printf("malloc draw buffer fail\n");
        return 0;
    }

    /* 初始化显示缓冲区描述符 */
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, width * height);

    /* 初始化并注册显示驱动 */
    disp_drv.draw_buf = &disp_buf;      // 设置绘图缓冲区
    disp_drv.flush_cb = sunxifb_flush;  // 设置刷新回调函数
    disp_drv.hor_res = width;           // 设置水平分辨率
    disp_drv.ver_res = height;          // 设置垂直分辨率
    disp_drv.rotated = rotated;         // 设置旋转角度
    disp_drv.screen_transp = 0;         // 屏幕是否透明
    lv_disp_drv_register(&disp_drv);    // 注册显示驱动

    /* 初始化输入设备（鼠标、触摸板等） */
    evdev_init();                        // 初始化 evdev 输入
    lv_indev_drv_init(&indev_drv);       // 输入驱动基本初始化
    indev_drv.type = LV_INDEV_TYPE_POINTER; // 输入设备类型为指针（鼠标或触摸屏）
    indev_drv.read_cb = evdev_read;         // 输入读取回调函数
    // 注册输入设备并获取输入设备对象
    lv_indev_t *evdev_indev = lv_indev_drv_register(&indev_drv);

    print_touch_pid();

    /* 调用 GUI Guider 初始化界面 */
    setup_ui(&guider_ui);     // guider_ui 是 lv_ui 类型的结构体
    events_init(&guider_ui);  // 绑定事件
    custom_init(&guider_ui);  // 自定义功能初始化


    /* 主循环：处理 LittlevGL 任务（tickless 模式） */
    while (1) {
        lv_task_handler();  // LittlevGL 的任务处理函数
        usleep(1000);       // 延时 1 毫秒，防止 CPU 占用过高
    }

    return 0;
}

/* 
 * 自定义系统时间获取函数
 * 在 lv_conf.h 中设置 LV_TICK_CUSTOM_SYS_TIME_EXPR = custom_tick_get();
 * 返回系统启动以来的毫秒数
 */
uint32_t custom_tick_get(void) {
    static uint64_t start_ms = 0;      // 程序启动时间（毫秒）
    if (start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);  // 获取当前时间
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000; // 转换为毫秒
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);         // 获取当前时间
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000; // 转换为毫秒

    uint32_t time_ms = now_ms - start_ms; // 计算程序运行的毫秒数
    return time_ms;                       // 返回给 LVGL 使用
}
