#include <iostream>
#include <windows.h>

void insaneThing(HBRUSH brush, HDC wow, int a, int b, int c, int d){
    CreateSolidBrush(RGB(250,250,1));
    SelectObject(wow, brush);
    Ellipse(wow, a, b, c, d);
    return;
}

void psycho(HDC insane){
    POINT mish;
    GetCursorPos(&mish);
    DrawIcon(insane, mish.x, mish.y, LoadIcon(NULL, IDI_ERROR));
    return;
}

void isSky(int a, HDC ok){
    StretchBlt(ok, -80, -80, a+100, a+100, ok, 0, 0, a, a, SRCINVERT);
    return;
}

void trash(int a, int b, int c, HDC da){
    BitBlt(da, b, c, a, a, da, 0, 0, SRCCOPY);
}

int main(){
    insaneThing(0, GetDC(0), rand(), rand() % 15, rand() % 15, rand());
    psycho(GetDC(0));
    isSky(GetSystemMetrics(0), GetDC(0));
    trash(GetSystemMetrics(0), rand() % -4, rand() % 4, GetDC(0));
}