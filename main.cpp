#include <windows.h>

static void SetWindowsTheme(const DWORD lightMode) {
    HKEY hKey;

    if (auto path = R"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)"; RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, "AppsUseLightTheme", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&lightMode), sizeof(lightMode));
        RegSetValueExA(hKey, "SystemUsesLightTheme", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&lightMode), sizeof(lightMode));
        RegCloseKey(hKey);
    }
    SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, reinterpret_cast<LPARAM>(L"ImmersiveColorSet"), SMTO_ABORTIFHUNG, 5000, nullptr);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int) {
    HKEY hKey;
    DWORD currentMode = 1; // Default to light
    DWORD bufferSize = sizeof(currentMode);

    // Read the current system theme
    if (const char* path = R"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)"; RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
        RegQueryValueExA(hKey, "SystemUsesLightTheme", nullptr, nullptr, reinterpret_cast<LPBYTE>(&currentMode), &bufferSize);
        RegCloseKey(hKey);
    }

    // Toggle: If currently Light (1), switch to Dark (0). Otherwise, switch to Light (1).
    SetWindowsTheme(currentMode == 1 ? 0 : 1);

    return 0;
}