#include <iostream>
#include <raylib.h>


using namespace std;
int ps = 0;
int cs = 0;
class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int r;
    void Draw() {
        DrawCircle(x, y, r, WHITE);

    }

    void update() {

        x += speed_x;
        y += speed_y;

        if (y+r>=GetScreenHeight()||y-r<=0)
        {
            speed_y *= -1;
        }
        if (x + r >= GetScreenWidth()     )
        {
            cs++;
            reset();
        }
        if (x - r <= 0)
        {
            ps++;
            reset();
        }
    }
    void reset() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int spd[2] = { -1,1 };
        speed_x *= spd[GetRandomValue(0, 1)];
        speed_y *= spd[GetRandomValue(0, 1)];
    }

};


class Pad {
protected:
    void limitmov() {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + h >= GetScreenHeight())
        {
            y = GetScreenHeight() - h;
        }
    }
public:
    float x, y;
    float w, h;
    int speed;
    
    void Draw() {

        DrawRectangle(x, y, w, h, GOLD);
    }

    void update() {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        limitmov();
       
    }


};
class cpuPad:public Pad {
public: void update(int ball_y) {


    if (y+h/2 > ball_y)
    {
        y -= speed;
    }
    if (y+h/2 <ball_y)
    {
        y += speed;
    }
    limitmov();
}

};
Ball ball;
Pad pad;
cpuPad cpu;

int main() {
    int sw =1280;
    int sl = 800;
    InitWindow(sw, sl, "PONG PONG!!");
    SetTargetFPS(60);
    
    ball.r = 20;
    ball.x = 800 / 2;
    ball.y = 1280 / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    pad.w = 25;
    pad.h = 120;
    pad.x = sw - pad.w - 10;
    pad.y = sl / 2 - pad.h / 2;
    pad.speed = 6;

    cpu.w = 25;
    cpu.h = 125;
    cpu.x = 10;
    cpu.y = sl / 2 - cpu.h / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        //Update
        ball.update();
        pad.update();
        cpu.update(ball.y);

        // collison
        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y,},ball.r,Rectangle{pad.x,pad.y,pad.w,pad.h}))
            ball.speed_x *= -1;
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y, }, ball.r, Rectangle{ cpu.x,cpu.y,cpu.w,cpu.h }))
            ball.speed_x *= -1;

        //drawing 
        ClearBackground(DARKPURPLE);
        DrawLine(sw / 2, 0, sw / 2, sl, WHITE);
        ball.Draw();
        cpu.Draw();
        pad.Draw();
        DrawText(TextFormat("%i", cs), sw / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", ps), 3*sw / 4 - 20, 20, 80, BLACK);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}