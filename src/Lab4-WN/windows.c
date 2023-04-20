#include <windows.h>
#include <stdio.h>

// Оконная процедура
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // Обработка нажатия на кнопку
        case WM_COMMAND:
            switch (wParam)
            {
                case 1:
                    // Вызов функции, написанной для консоли
                    printf("Hello, world!\n");
                    break;
            }
            break;

        // Обработка закрытия окна
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        // Обработка уничтожения окна
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

// Точка входа в программу
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    // Регистрация класса окна
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = "MyAppClass";
    RegisterClass(&wc);

    // Создание окна
    HWND hwnd = CreateWindow("MyAppClass", "My Window",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             500, 300, NULL, NULL, hInstance, NULL);

    // Создание кнопки
    HWND btn = CreateWindow("BUTTON", "Click me!",
                            WS_VISIBLE | WS_CHILD,
                            10, 10, 100, 30,
                            hwnd, (HMENU)1, hInstance, NULL);

    HWND btn2 = CreateWindow("BUTTON", "Exit",
                            WS_VISIBLE | WS_CHILD,
                            10, 10, 100, 30,
                            hwnd, (HMENU)1, hInstance, NULL);

    // Обработка сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
