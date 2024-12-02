#include <stdio.h>
#include <Windows.h>
#include "Elf2D.h"


void Elf2DInitScreen()
{
    //Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Ŀ���� ����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ȭ�� �ʱ�ȭ �Լ�
void Elf2DClearScreen(char* Buffer, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Buffer[i * (width + 1) + j] = ' ';  // ȭ�� �ʱ�ȭ
        }
        Buffer[i * (width + 1) + width] = '\n';  // ���� ����
    }
    Buffer[(width + 1) * height - 1] = '\0';  // ���� ����

}

// ��ũ�����۸� �̿��Ͽ� ȭ���� �׸��� �Լ�
void Elf2DDrawBuffer(char* Buffer)
{
    //0,0���� �̵�
    COORD coord = { 0, 0 };  // ��ǥ (0, 0)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // ��ũ�� ���� ���
    printf("%s", Buffer);  // ȭ�� ���
}

// �� ���� �����ϴ� ������ �׸��� �Լ� (�극���� �˰���)
void Elf2DDrawLineA(int x1, int y1, int x2, int y2, char* Buffer, int width, int height)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // ��ǥ�� ȭ�� ���� �ִ��� Ȯ��
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            int index = y1 * (width * 2 + 1) + x1 * 2; // 2���� ���� "AA"�� �����ϱ� ���� ��ġ ���
            Buffer[index] = 'A';                      // ù ��° ����
            Buffer[index + 1] = 'A';                  // �� ��° ����
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
        // ��ǥ�� ȭ�� ���� �ִ��� Ȯ��
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            int index = y1 * (width * 2 + 1) + x1 * 2; // 2���� ���� "AA"�� �����ϱ� ���� ��ġ ���
            Buffer[index] = 'B';                      // ù ��° ����
            Buffer[index + 1] = 'B';                  // �� ��° ����
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
        // ��ǥ�� ȭ�� ���� �ִ��� Ȯ��
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
            int index = y1 * (width * 2 + 1) + x1 * 2; // 2���� ���� ��ġ ���

            // ������ ������ FF�� �׸���
            if (x1 == x2 && y1 == y2) {
                Buffer[index] = 'F';       // ù ��° ����
                Buffer[index + 1] = 'F';   // �� ��° ����
            }
            else {
                Buffer[index] = 'C';       // ù ��° ����
                Buffer[index + 1] = 'C';   // �� ��° ����
            }
        }

        // ���� ������ �����ϸ� ����
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