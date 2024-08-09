#include "HP.h"

// Constructor của lớp HP, khởi tạo các giá trị ban đầu
HP::HP(int initialHP, const char* heartImagePath) {
    maxHP = initialHP;  // Gán giá trị ban đầu cho maxHP, đây là số máu tối đa
    currentHP = initialHP;  // Gán giá trị ban đầu cho currentHP, đây là số máu hiện tại
    heartTexture = LoadTexture(heartImagePath);  
    position = { 900, 24 };  // Đặt vị trí ban đầu của texture trái tim trên màn hình, ở đây là tọa độ (900, 24)
}

// Destructor của lớp HP, giải phóng tài nguyên được sử dụng bởi lớp
HP::~HP() {
    UnloadTexture(heartTexture);  // Giải phóng bộ nhớ 
}

// Phương thức để vẽ biểu tượng trái tim lên màn hình, đại diện cho lượng máu hiện tại
void HP::Draw() {
    for (int i = 0; i < currentHP / 50; i++) {  // Lặp qua mỗi đơn vị 50 HP (mỗi trái tim đại diện cho 50 HP)
        // Mỗi trái tim được vẽ cách nhau một khoảng cách là `heartTexture.width + 10` pixels.
        DrawTexture(heartTexture, position.x - i * (heartTexture.width + 10), position.y, WHITE);
    }
}

// Phương thức để giảm lượng máu hiện tại
void HP::Decrease(int amount) {
    currentHP -= amount;  // Giảm currentHP theo giá trị `amount` truyền vào
    if (currentHP < 0) currentHP = 0;  // Nếu currentHP nhỏ hơn 0, đặt nó về 0 để tránh giá trị âm
}

// Phương thức trả về lượng máu hiện tại
int HP::GetCurrentHP() const {
    return currentHP;  // Trả về giá trị của currentHP
}

// Phương thức kiểm tra xem lượng máu có cạn kiệt không
bool HP::IsEmpty() const {
    return currentHP <= 0;  // Trả về true nếu currentHP nhỏ hơn hoặc bằng 0, nghĩa là nhân vật đã chết
}
