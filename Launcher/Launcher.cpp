#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <detours.h>

#ifdef _M_AMD64
std::string cpu = "x86_64";
std::string dll = "64";
#elif _M_IX86
std::string cpu = "x86";
std::string dll = "32";
#endif


int main(int argc, char** argv) {
	printf("Win11DarkTitleBar %s build\n", cpu.c_str());

	if (argc < 2) {
		std::string exePath = argv[0];
		auto message = "Win11DarkTitleBar " + cpu + " build\n"
			+ "usage: " + exePath + " <app> [args...]\n"
			+ "app: apth to app\n"
			+ "args: args to app";
		MessageBoxA(nullptr, message.c_str(), "Win11DarkTitleBar", NULL);
		return 0;
	}

	auto dllPath = (std::filesystem::current_path() / ("Hook" + dll + ".dll")).string();
	
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFOA));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFOA);

	std::string cmdLine = argv[1];
	for (int i = 2; i < argc; i++) {
		cmdLine += " ";
		cmdLine += argv[i];
	}

	printf("launch cmdLine: %s\n", cmdLine.c_str());

	auto r = DetourCreateProcessWithDllExA(nullptr, (LPSTR)cmdLine.c_str(), nullptr, nullptr, false, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &si, &pi, dllPath.c_str(), nullptr);
	if (r) {
		printf("success");
		return 0;
	} else {
		auto message = "launch:\n" + cmdLine + "\nfailed with code " + std::to_string(GetLastError());
		printf("%s\n", message.c_str());
		MessageBoxA(nullptr, message.c_str(), "Win11DarkTitleBar", NULL);
		return r;
	}
}
