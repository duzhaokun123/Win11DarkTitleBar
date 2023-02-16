# Win11DarkTitleBar

[![GitHub license](https://img.shields.io/github/license/duzhaokun123/Win11DarkTitleBar?style=flat-square)](https://github.com/duzhaokun123/Win11DarkTitleBar/blob/main/LICENSE)
![Android SDK min 31](https://img.shields.io/badge/Windows-11-blue?style=flat-square&logo=windows11)

简体中文 | [English](README.md)

### 为什么暗色标题栏?

许多使用 Qt, gtk ... 的应用 (比如 OBS Studio, Krita, GIMP ...) 提供了暗色主题但没有暗色标题栏

丑死了! 对我的眼睛造成了极大的伤害

![so light](arts/light.png)

### 如何暗色标题栏?

从 Windows 11 Build 22000 开始, Windows 提供了一个新的 Win32 api 使得使用深色标题栏更容易

[为 Win32 应用程序启用深色模式标题栏](https://learn.microsoft.com/zh-cn/windows/apps/desktop/modernize/apply-windows-themes#enable-a-dark-mode-title-bar-for-win32-applications)

```c++
BOOL value = TRUE;
::DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
```

### 暗色标题栏看上去怎么样?

自己看吧

![so dark](arts/dark.png)

## Thanks

[Detours](https://github.com/microsoft/Detours)

[Locale_Remulator](https://github.com/InWILL/Locale_Remulator)