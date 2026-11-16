#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

//イベントを処理する関数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//main関数のようなもの
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    //設計図
    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    //ウィンドウを作成
    HWND hwnd = CreateWindowEx(
        0,                              // 拡張スタイル
        CLASS_NAME,                     // ウィンドウクラス名
        L"VS Code & MSVC Window",       // ウィンドウタイトル
        WS_OVERLAPPEDWINDOW,            // ウィンドウスタイル
        CW_USEDEFAULT, CW_USEDEFAULT,   // 表示位置 (X, Y)
        800, 600,                       // サイズ (幅, 高さ)
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    //メッセージループ
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
