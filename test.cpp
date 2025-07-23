#include <algorithm>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// 获取程序当前所在显示器的分辨率大小，可以动态的获取程序所在显示器的分辨率
SIZE GetScreenResolution(HWND hWnd) {
    SIZE size;
    if (!hWnd)
        return size;

    // MONITOR_DEFAULTTONEAREST 返回值是最接近该点的屏幕句柄
    // MONITOR_DEFAULTTOPRIMARY 返回值是主屏幕的句柄
    // 如果其中一个屏幕包含该点，则返回值是该屏幕的HMONITOR句柄。如果没有一个屏幕包含该点，则返回值取决于dwFlags的值
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX miex;
    miex.cbSize = sizeof(miex);
    if (!GetMonitorInfo(hMonitor, &miex))
        return size;

    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;

    // ENUM_CURRENT_SETTINGS 检索显示设备的当前设置
    // ENUM_REGISTRY_SETTINGS 检索当前存储在注册表中的显示设备的设置
    if (!EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm))
        return size;

    size.cx = dm.dmPelsWidth;
    size.cy = dm.dmPelsHeight;
    return size;
}

int main() {

    return 0;
}
