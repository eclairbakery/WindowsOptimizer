#include <filesystem>
#include <ids.hpp>
#include <windows.h>

HWND hCheckUpdate;
HWND hCheckTemp;
HWND hCheckSystem;

void clear_directory(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) return;
    for (auto& entry : std::filesystem::directory_iterator(path)) {
        std::error_code ec;
        std::filesystem::remove_all(entry.path(), ec);
    }
}

void optimize() {
    if (SendMessageA(hCheckUpdate, BM_GETCHECK, 0, 0) == BST_CHECKED) {
        clear_directory("C:\\Windows\\SoftwareDistribution\\Download");
    }

    if (SendMessageA(hCheckTemp, BM_GETCHECK, 0, 0) == BST_CHECKED) {
        char tempPath[MAX_PATH];
        GetTempPathA(MAX_PATH, tempPath);
        clear_directory(tempPath);
    }

    if (SendMessageA(hCheckSystem, BM_GETCHECK, 0, 0) == BST_CHECKED) {
        clear_directory("C:\\Windows\\Temp");
    }

    MessageBoxA(NULL, "Optimization complete", "Done", MB_OK | MB_ICONINFORMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_OPTIMIZE) {
                optimize();
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    WNDCLASSA wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OptimizerApp";

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        "OptimizerApp",
        "Windows Optimizer",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 360, 240,
        NULL, NULL, hInstance, NULL
    );

    hCheckUpdate = CreateWindowA(
        "BUTTON",
        "Clear Windows Update cache",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        20, 20, 300, 25,
        hwnd, (HMENU)ID_CHECK_UPDATE, hInstance, NULL
    );

    hCheckTemp = CreateWindowA(
        "BUTTON",
        "Clear user TEMP",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        20, 50, 300, 25,
        hwnd, (HMENU)ID_CHECK_TEMP, hInstance, NULL
    );

    hCheckSystem = CreateWindowA(
        "BUTTON",
        "Clear system TEMP",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        20, 80, 300, 25,
        hwnd, (HMENU)ID_CHECK_SYSTEM, hInstance, NULL
    );

    CreateWindowA(
        "BUTTON",
        "OPTIMIZE",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 130, 300, 40,
        hwnd, (HMENU)ID_OPTIMIZE, hInstance, NULL
    );

    ShowWindow(hwnd, nShowCmd);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
