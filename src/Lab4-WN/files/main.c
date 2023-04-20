#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "treeLib.h"

int check(int key){
    while(!scanf_s("%d", &key) || key < 1 || key > 5) {
        printf("Invalid option!\n");
        rewind(stdin);
    }
    return key;
}

int menu() {
    system("chcp 65001");
    Node* tree = NULL;
    Node** answers = malloc(sizeof(Node*));
    int answersSize = 0;
//    while(1) {
        int key = 0;
        char path[100];
        printf("\nMenu:\n1) Start\n2) Load DB\n3) Save DB\n4) Exit\n");
        key = check(key);
        switch (key) {
            case 1:
                if(tree != NULL)
                {
                    play(tree, &answers, &answersSize);
                }
                else
                    fprintf(stderr,"Error! Database not loaded\n");
                break;
            case 2:
                printf("Input database: ");
                scanf_s("%99s", path);
                tree = load(path);
                break;
            case 3:
                printf("Output database: ");
                scanf_s("%99s", path);
                save(tree, path);
                break;
            default:
                if(tree != NULL) {
                    clearMemory(tree);
                }
                free(answers);
                exit(EXIT_SUCCESS);
//        }
    }
}



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
                    menu();
                    break;
                case 2:
                    DestroyWindow(hwnd);
                    exit(EXIT_SUCCESS);
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
    HWND btn = CreateWindow("BUTTON", "Load",
                            WS_VISIBLE | WS_CHILD,
                            10, 10, 100, 30,
                            hwnd, (HMENU)1, hInstance, NULL);

    HWND btn2 = CreateWindow("BUTTON", "Exit",
                            WS_VISIBLE | WS_CHILD,
                            300, 10, 100, 30,
                            hwnd, (HMENU)2, hInstance, NULL);

    HWND edit = CreateWindow("EDIT", "This is edit",
                             WS_VISIBLE | WS_CHILD,
                             10, 50, 100, 30,
                             hwnd, (HMENU)2, hInstance, NULL);
    // Обработка сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
