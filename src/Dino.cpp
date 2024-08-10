#include "Dino.h"

// Constructor của lớp Dino, khởi tạo các giá trị ban đầu
Dino::Dino() : HP(100, "Graphics/heart.png") {
    // Tải các hình ảnh frame của Dino từ file ảnh và lưu vào vector frames
    frames.push_back(LoadTexture("Graphics/dino0.png"));
    frames.push_back(LoadTexture("Graphics/dino1.png"));
    frames.push_back(LoadTexture("Graphics/dino2.png"));

    position.x = 100;  // Đặt vị trí ban đầu của Dino trên trục x là 100
    position.y = 550;  // Đặt vị trí ban đầu của Dino trên trục y là 550

    speed = 10;  // Tốc độ di chuyển của Dino

    currentFrame = 0;  // Khung hình hiện tại của animation
    frameCounter = 0;  // Bộ đếm số frame đã qua
    frameSpeed = 8;  // Tốc độ thay đổi khung hình trong animation

    isJumping = false;  // Biến để kiểm tra Dino có đang nhảy không
    jumpVelocity = 0.0f;  // Tốc độ nhảy ban đầu
    gravity = 1.5f;  // Lực hấp dẫn ảnh hưởng tới tốc độ rơi của Dino
    initialY = position.y;  // Vị trí y ban đầu của Dino (dùng để xác định khi nào Dino chạm đất sau khi nhảy)

    isInvincible = false;  // Biến để kiểm tra Dino có đang trong trạng thái bất tử không
    invincibilityTime = 0.0f;  // Thời gian tồn tại của trạng thái bất tử
    invincibilityTimer = 0.0f;  // Bộ đếm thời gian cho trạng thái bất tử
}

// Destructor của lớp Dino, giải phóng tài nguyên
Dino::~Dino() {
    for (auto &frame : frames) {  
        UnloadTexture(frame);
    }
}

// Phương thức vẽ Dino lên màn hình
void Dino::Draw() {
    DrawTextureV(frames[currentFrame], position, WHITE);  // Vẽ frame hiện tại của Dino tại vị trí của nó
    DrawHP();  // Vẽ thanh máu của Dino
}

void Dino::Update() {
    // Xử lý việc nhấn phím nhảy (SPACE)
    if (IsKeyPressed(KEY_SPACE) && !isJumping) {
        isJumping = true;
        jumpVelocity = -25.0f;  // Thiết lập tốc độ nhảy ban đầu
    }

    // Xử lý hành động nhảy
    if (isJumping) {
        position.y += jumpVelocity;  // Cập nhật vị trí y của Dino theo tốc độ nhảy
        jumpVelocity += gravity;  // Tăng tốc độ rơi bằng lực hấp dẫn

        // Kiểm tra nếu Dino đã chạm đất (vị trí y >= vị trí ban đầu)
        if (position.y >= initialY) {
            position.y = initialY;  // Đặt vị trí y lại vị trí ban đầu
            isJumping = false;  // Kết thúc nhảy
            jumpVelocity = 0.0f;  // Đặt lại tốc độ nhảy
        }
    }

    frameCounter++;  // Tăng bộ đếm khung hình

    // Cập nhật animation của Dino
    if (frameCounter >= frameSpeed) {
        currentFrame++;  // Chuyển sang khung hình tiếp theo
        if (currentFrame >= frames.size()) {
            currentFrame = 0;  // Quay lại khung hình đầu tiên nếu đã hết các khung hình
        }
        frameCounter = 0;  // Đặt lại bộ đếm khung hình
    }

    // Cập nhật bộ đếm thời gian bất tử
    if (isInvincible) {
        invincibilityTimer += GetFrameTime();  // Tăng bộ đếm thời gian vô địch theo thời gian của mỗi frame
        if (invincibilityTimer >= invincibilityTime) {
            isInvincible = false;  // Kết thúc trạng thái bất tử nếu đã hết thời gian
            invincibilityTimer = 0.0f;  // Đặt lại bộ đếm thời gian bất tử
        }
    }
}

// Phương thức trả về hình chữ nhật bao quanh Dino, dùng để kiểm tra va chạm
Rectangle Dino::GetRect() {
    return Rectangle{position.x, position.y, (float)frames[currentFrame].width, (float)frames[currentFrame].height};
}

//vẽ hitbox dùng để debug hoặc kiểm tra va chạm
void Dino::DrawHitbox(bool isColliding) {
    Color outlineColor = isColliding ? RED : BLACK;  
    DrawRectangleLinesEx(GetRect(), 3, outlineColor); 
}

// Phương thức giảm máu của Dino khi bị tấn công
void Dino::TakeDamage(int damage) {
    if (!isInvincible) {  // Nếu Dino không trong trạng thái vô địch
        Decrease(damage);  // Giảm máu theo giá trị `damage`
        ActivateInvincibility(1.0f);  // Kích hoạt trạng thái vô địch trong 1 giây sau khi bị tấn công
    }
}

// Phương thức kiểm tra Dino có chết không (máu có cạn không)
bool Dino::isDead() {
    return IsEmpty();  // Trả về true nếu lượng máu bằng 0 hoặc ít hơn
}



// Phương thức kích hoạt trạng thái bất tử
void Dino::ActivateInvincibility(float duration) {
    isInvincible = true;  // Đặt trạng thái vô địch là true
    invincibilityTime = duration;  // Đặt thời gian vô địch theo giá trị `duration` truyền vào
    invincibilityTimer = 0.0f;  // Đặt lại bộ đếm thời gian vô địch
}

// Phương thức kiểm tra xem Dino có đang trong trạng thái bất tử không
bool Dino::IsInvincible() const {
    return isInvincible;  // Trả về true nếu Dino đang trong trạng thái bất tử
}
