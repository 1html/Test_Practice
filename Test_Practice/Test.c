#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  // _kbhit(), _getch() �Լ� ����� ���� ���

#include "ElfMath.h"
#include "Elf2D.h"

#define WIDTH 80
#define HEIGHT 24

typedef struct
{
    //Transform
    Vector2 Position;
    float Rotation;
    Vector2 Scale;

    //Geometry
    Vector2 Line[2]; // 0, 1 -> 0( x,y) 1(x,y) -> �극�������� ����

    char* Symbol; // ���� �̸� 

}GameObject_Line;

// 0: �Է¾���
// 99 : ���� ����
int Input()
{
    // ESC Ű�� �������� Ȯ��
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 27) {  // ESC Ű�� ������ ���� ����
            return 99;
        }
    }

    return 0;
}


void Update(GameObject_Line* obj, int objNum, int inputEvent)
{
    if (inputEvent == 3) { // Ư�� �Է¿� ����
        obj[0].Position.x += 5; // C ���� x��ǥ�� 5 ����
        printf("Updated Position.x: %f\n", obj[0].Position.x); // ����� ���
    }
}

//
void Render(GameObject_Line* obj, int objNum, char* Buf, int width, int height)
{
    Vector3 lineA, lineB;
    Matrix3x3 world = identity_matrix();    //������ķ� �ʱ�ȭ

    lineA.x = 0;
    lineA.y = 0;
    lineB.x = 0;
    lineB.y = 0;

    int i;
    for (i = 0; i < objNum; i++) {
        obj[i].Position.x = lineA.x;
        obj[i].Position.x = lineA.y;
        obj[i].Position.x = lineB.x;
        obj[i].Position.y = lineB.y;

        lineA.x = obj[i].Line[0].x;
        lineA.y = obj[i].Line[0].y;
        lineA.z = 1;
        lineB.x = obj[i].Line[1].x;
        lineB.y = obj[i].Line[1].y;
        lineB.z = 1;

        Matrix3x3 scale = scale_matrix(obj[i].Scale.x, obj[i].Scale.y); // ũ������ ��� ����
        Matrix3x3 rotation = rotation_matrix(obj[i].Rotation);// ȸ�� ��� ����
        Matrix3x3 translation = translation_matrix(obj[i].Position.x, obj[i].Position.y); // �̵� ��� ����

        world = multiply_matrices(scale, world);
        world = multiply_matrices(rotation, world);
        world = multiply_matrices(translation, world);
        lineA = multiply_matrix_vector(world, lineA);  // ���� ȸ�� ��� ���� (Matrix3x3 * Vector3)
        lineB = multiply_matrix_vector(world, lineB);  // ���� ȸ�� ��� ���� (Matrix3x3 * Vector3)

        if (i == 0) {
            Elf2DDrawLineA((int)lineA.x, (int)lineA.y, (int)lineB.x, (int)lineB.y, Buf, width, height);
        }
        else if (i == 1) {
            Elf2DDrawLineB((int)lineA.x, (int)lineA.y, (int)lineB.x, (int)lineB.y, Buf, width, height);
        }
        else if (i == 2) {
            Elf2DDrawLineC((int)lineA.x , (int)lineA.y, (int)lineB.x, (int)lineB.y, Buf, width, height);
        }
    }

}


// ���� ����
int main() {
    int fps = 60;
    double frameTime = 1000.0 / fps;

    // ���� ������ ��ũ�� ���� ����
    char screenBuffer[(WIDTH + 1) * HEIGHT];
    int screenWidth = WIDTH;
    int screenHeight = HEIGHT;

    GameObject_Line LineObj[3];

    // ���� �ʱ�ȭ
    Elf2DInitScreen();
    Elf2DClearScreen(screenBuffer, screenWidth, screenHeight);
    Elf2DDrawBuffer(screenBuffer);

    //��ü �ʱ�ȭ(���� 3��)
    
   
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        LineObj[i].Position.x = 5;
        LineObj[i].Position.y = 0;

        LineObj[i].Rotation = 0;


        //(0,0) ~ (2,0) �� �մ� ����
        LineObj[i].Line[0].x = 0;
        LineObj[i].Line[0].y = 0;

        LineObj[i].Line[1].x = 2;
        LineObj[i].Line[1].y = 0;
    }


   
   
    

   

    //1�� 2 �ݽð� ���� 30��
    LineObj[1].Rotation = 0;
    LineObj[2].Rotation = 0;

    //ȭ�� ��� �ɺ� �Է�
    LineObj[0].Symbol = "11";
    LineObj[1].Symbol = "22";
    LineObj[2].Symbol = "33";

    //ũ�� �Է�
    LineObj[0].Scale.x = 1;
    LineObj[0].Scale.y = 1;
    LineObj[1].Scale.x = 2;
    LineObj[1].Scale.y = 2;
    LineObj[2].Scale.x = 2;
    LineObj[2].Scale.y = 2;




    // ������ Ÿ�̸�
    clock_t lastTime = clock();

    while (1) {

        int event = Input();
        //�Է� ���
        if (event == 99)
        {
            break;
        }

        // ���� ������Ʈ
        Update(LineObj, 3, event);

        // ��ũ�����ۿ� ���� ������
        Render(LineObj, 3, screenBuffer, screenWidth, screenHeight);

        // ȭ�� �׸���
        Elf2DDrawBuffer(screenBuffer);

        // ���� �ð� ���
        clock_t now = clock();
        double deltaTime = (double)(now - lastTime) / CLOCKS_PER_SEC * 1000.0;
        Elf2DSleep(frameTime - deltaTime);
        lastTime = now;
    }

    return 0;
}