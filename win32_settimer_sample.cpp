#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#define TIMER_ID 1

int box_x = 0;

//イベントを処理する関数
//CALLBACKはWindowsに呼び出してもらうということ
LRESULT CALLBACK WindowProc(
    HWND hwnd,//どのウィンドウか
    UINT uMsg,//種類
    WPARAM wParam,//情報
    LPARAM lParam//情報
) {
    switch (uMsg) {
        case WM_CREATE: {
            SetTimer(hwnd, TIMER_ID, 16, NULL);
            return 0;
        }

        case WM_TIMER: {
            if (wParam == TIMER_ID) {
                box_x += 10;
                if (box_x > 600) {
                    box_x = -10;
                }

                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            //文字
            SetTextColor(hdc, RGB(255, 0, 0));
            const wchar_t text[] = L"Hello, Win32 API!";
            TextOut(hdc, 50, 50, text, lstrlen(text));

            //図形
            Rectangle(hdc, 50, 100, 250, 200);
            
            MoveToEx(hdc, 50, 250, NULL);
            LineTo(hdc, 250, 500);

            //BeginPaintの後必ず実行
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_DESTROY: {
            KillTimer(hwnd, TIMER_ID);
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//main関数のようなもの
int WINAPI wWinMain(
    HINSTANCE hInstance,//実行中のプログラムそのものを識別するためのもの
    HINSTANCE hPrevInstance,//使わない
    PWSTR pCmdLine,//起動時に渡されるコマンドライン引数
    int nCmdShow//最初ウィンドウをどう表示するか
) {
    //const wchar_tのArray CLASS_NAMEという名前
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    //設計図
    WNDCLASS wc = {};
    //イベントを処理する関数
    wc.lpfnWndProc = WindowProc;
    //設計図の所有者はこの実行中のプログラム
    wc.hInstance = hInstance;
    //ポインタを渡す
    wc.lpszClassName = CLASS_NAME;
    //背景色
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //カーソル
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    //Windowsに登録
    if (!RegisterClass(&wc)) {
        return 0;
    }

    //ウィンドウを作成
    HWND hwnd = CreateWindowEx(
        0,                              // 拡張スタイル
        CLASS_NAME,                     // ウィンドウクラス名
        L"VS Code & MSVC Window",       // ウィンドウタイトル
        WS_OVERLAPPEDWINDOW,            // ウィンドウスタイル
        CW_USEDEFAULT, CW_USEDEFAULT,   // 表示位置 (X, Y)
        1200, 800,                       // サイズ (幅, 高さ)
        NULL, NULL, hInstance, NULL
    );

    //ウィンドウを作成できなかったら
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
