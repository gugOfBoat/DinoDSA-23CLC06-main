#include "C:\\raylib\\raylib\\src\\raylib.h"
#include "Dino.h"

const int windowWidth = 1000;
const int windowHeight = 600;

int main()
{
    InitWindow(windowWidth, windowHeight, "Dino Run");
    SetTargetFPS(60); // Đặt tốc độ khung hình là 60 FPS (Frames Per Second)

    Texture2D startScreen(LoadTexture("Graphics/started.png"));

    while (!WindowShouldClose())
    {
        BeginDrawing(); // Bắt đầu vẽ lên màn hình
        ClearBackground(RAYWHITE);

        // Vẽ hình ảnh màn hình bắt đầu
        DrawTexture(startScreen, 112, 84, WHITE);

        EndDrawing(); // Kết thúc quá trình vẽ

        // Kiểm tra nếu phím Space, Enter hoặc Escape được nhấn thì thoát vòng lặp
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
        {
            break; // Thoát vòng lặp khi một trong các phím được nhấn
        }
    }

    // Giải phóng bộ nhớ của hình ảnh màn hình bắt đầu
    UnloadTexture(startScreen);

    Texture2D groundTexture(LoadTexture("Graphics/ground.png"));  // Tải hình ảnh nền
    Texture2D stopButton(LoadTexture("Graphics/stopButton.png")); // Tải hình ảnh nút dừng

    Dino *dino = new Dino;                          // Khởi tạo đối tượng Dino
    Rectangle obtacle(Rectangle{950, 550, 30, 30}); // Đặt chướng ngại vật
    const float obstacleSpeed = 5.0f;               // Tốc độ di chuyển của chướng ngại vật

    float groundX1 = 0.0f;          // Vị trí ngang ban đầu của nền đầu tiên
    float groundX2 = windowWidth;   // Vị trí ngang ban đầu của nền thứ hai
    const float groundSpeed = 5.0f; // Tốc độ di chuyển của nền

    bool isPaused = false; // Biến để kiểm tra trò chơi có đang bị tạm dừng hay không

    while (!WindowShouldClose()) // Vòng lặp chính của trò chơi
    {
        if (!isPaused)
        {                            // Nếu trò chơi không bị tạm dừng
            dino->Update();          // Cập nhật trạng thái của Dino
            groundX1 -= groundSpeed; // Di chuyển nền đầu tiên sang trái
            groundX2 -= groundSpeed; // Di chuyển nền thứ hai sang trái

            // Kiểm tra và lặp lại nền khi nó đã ra khỏi màn hình
            if (groundX1 <= -windowWidth)
                groundX1 = windowWidth;
            if (groundX2 <= -windowWidth)
                groundX2 = windowWidth;

            obtacle.x -= obstacleSpeed; // Di chuyển chướng ngại vật sang trái

            // Kiểm tra và đưa chướng ngại vật trở lại màn hình nếu nó đã ra khỏi màn hình
            if (obtacle.x <= -obtacle.width)
            {
                obtacle.x = windowWidth;
            }

            // Kiểm tra va chạm giữa Dino và chướng ngại vật
            bool isColliding = CheckCollisionRecs(dino->GetRect(), obtacle);
            if (isColliding)
            {
                dino->TakeDamage(50); // Dino nhận 50sát thương nếu có va chạm
            }
        }

        BeginDrawing(); // Bắt đầu vẽ lên màn hình
        ClearBackground(WHITE);

        DrawTextureEx(groundTexture, {groundX1, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE); // Vẽ nền đầu tiên
        DrawTextureEx(groundTexture, {groundX2, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE); // Vẽ nền thứ hai
        DrawRectangleRec(obtacle, BLACK);                                                                 // Vẽ chướng ngại vật
        dino->Draw();                                                                                     // Vẽ Dino
        dino->DrawHitbox(CheckCollisionRecs(dino->GetRect(), obtacle));                                   // Vẽ hitbox  của Dino (nếu có va chạm)

        // Vẽ nút dừng ở góc trên bên phải
        DrawTexture(stopButton, 950, 0, WHITE);

        // Nếu Dino chết, hiển thị thông báo "Game Over"
        if (dino->isDead())
        {
            DrawText("Game Over", windowWidth / 2 - 100, windowHeight / 2, 40, RED);
            break; // Thoát khỏi vòng lặp trò chơi
        }

        // Kiểm tra nếu nút dừng được nhấn
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition(); // Lấy vị trí chuột
            if (mousePos.x >= 950 && mousePos.x <= 950 + stopButton.width &&
                mousePos.y >= 0 && mousePos.y <= stopButton.height)
            {
                isPaused = true; // Tạm dừng trò chơi nếu nút dừng được nhấn
            }
        }

        // Nếu trò chơi bị tạm dừng, hiển thị menu tạm dừng (chưa được cài đặt)
        if (isPaused)
        {
            // Menu tạm dừng sẽ được thêm vào đây
        }

        EndDrawing(); // Kết thúc quá trình vẽ
    }

    // Giải phóng bộ nhớ của các texture và đóng cửa sổ
    delete dino;
    UnloadTexture(groundTexture);
    UnloadTexture(stopButton);
    CloseWindow();

    return 0;
}
