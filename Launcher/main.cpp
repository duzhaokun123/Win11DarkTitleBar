#include <windows.h>
#include <iostream>
#include <filesystem>
#include <detours.h>

#ifdef _WIN64
std::string cpu = "x86_64";
std::string dll = "64";
#elif _WIN32
std::string cpu = "x86";
std::string dll = "32";
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (__argc < 2) {
        std::string exePath = __argv[0];
        auto message = "Win11DarkTitleBar " + cpu + " build\n"
            + "usage: " + exePath + " <app> [args...]\n"
            + "app: apth to app\n"
            + "args: args to app";
        MessageBoxA(nullptr, message.c_str(), "Win11DarkTitleBar", MB_OK | MB_ICONINFORMATION);
        return 0;
    }

#ifdef _DEBUG
    MessageBoxA(nullptr, lpCmdLine, "lpCmdLine", NULL);
#endif

    auto exePath = (CHAR*)malloc(sizeof(CHAR) * MAX_PATH);
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    auto dllPath = (std::string)exePath + "/../Hook" + dll + ".dll";
    
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFOA);

    auto r = DetourCreateProcessWithDllExA(nullptr, lpCmdLine, nullptr, nullptr, false, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &si, &pi, dllPath.c_str(), nullptr);
    
    if (!r) {
        auto message = "launch:\n" + (std::string)lpCmdLine + "\nfailed with code " + std::to_string(GetLastError());
        MessageBoxA(nullptr, message.c_str(), "Win11DarkTitleBar", MB_OK | MB_ICONERROR);
    }

    return 0;
}
