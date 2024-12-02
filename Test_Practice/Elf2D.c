#include <stdio.h>
#include <Windows.h>
#include "Elf2D.h"


void Elf2DInitScreen()
{
    //커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // 커서를 숨김
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 화면 초기화 함수
void Elf2DClearScreen(char* Buffer, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Buffer[i * (width + 1) + j] = ' ';  // 화면 초기화
        }
        Buffer[i * (width + 1) + width] = '\n';  // 개행 문자
    }
    Buffer[(width + 1) * height - 1] = '\0';  // 개행 문자

}

// 스크린버퍼를 이용하여 화면을 그리는 함수
void Elf2DDrawBuffer(char* Buffer)
{
    //0,0으로 이동
    COORD coord = { 0, 0 };  // 좌표 (0, 0)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // 스크린 버퍼 출력
    printf("%s", Buffer);  // 화면 출력
}

// 두 점을 연결하는 직선을 그리는 함수 (브레젠햄 알고리즘)
void Elf2DDrawLineA(int x1, int y1, int x2, int y2, char* Buffer, int width, int height)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // 좌표가 화면 내에 있는지 확인
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            int index = y1 * (width * 2 + 1) + x1 * 2; // 2개의 문자 "AA"를 저장하기 위한 위치 계산
            Buffer[index] = 'A';                      // 첫 번째 문자
            Buffer[index + 1] = 'A';                  // 두 번째 문자
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void Elf2DDrawLineB(int x1, int y1, int x2, int y2, char* Buffer, int width, int height)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // 좌표가 화면 내에 있는지 확인
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            int index = y1 * (width * 2 + 1) + x1 * 2; // 2개의 문자 "AA"를 저장하기 위한 위치 계산
            Buffer[index] = 'B';                      // 첫 번째 문자
            Buffer[index + 1] = 'B';                  // 두 번째 문자
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Elf2DDrawLineC(int x1, int y1, int x2, int y2, char* Buffer, int width, int height)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // 좌표가 화면 내에 있는지 확인
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
            int index = y1 * (width * 2 + 1) + x1 * 2; // 2개의 문자 위치 계산

            // 마지막 점에는 FF를 그리기
            if (x1 == x2 && y1 == y2) {
                Buffer[index] = 'F';       // 첫 번째 문자
                Buffer[index + 1] = 'F';   // 두 번째 문자
            }
            else {
                Buffer[index] = 'C';       // 첫 번째 문자
                Buffer[index + 1] = 'C';   // 두 번째 문자
            }
        }

        // 선의 끝점에 도달하면 종료
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Elf2DSleep(int ms)
{
    Sleep(ms);
}