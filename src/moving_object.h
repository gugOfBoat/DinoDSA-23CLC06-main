#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <Dino.h>
#include <HP.h>
#include "C:\\raylib\\raylib\\src\\raylib.h" 

//Class cơ sở MovingObject
class MovingObject {
    private:
        Vector2 position;
        Texture2D frame;
        const int speed;

    public:
        MovingObject(Vector2 pos, Texture2D tex, int spd);
        virtual ~MovingObject();
        
        virtual void Update(); // Cập nhật vị trí của đối tượng
        Rectangle GetRect() const; // Trả về hình chữ nhật bao quanh đối tượng
        virtual bool IsCollision(Dino* dino) const; // Kiểm tra va chạm với Dino
};

// Lớp Item kế thừa từ MovingObject
class Item : public MovingObject {
    public:
        Item(Vector2 pos, Texture2D tex, int spd);
        virtual ~Item() {}  

        virtual bool Collected() = 0;
};

// Lớp Shield kế thừa từ Item
class Shield : public Iteam {
    public:
        Shield(Vector2 pos, Texture2D tex, int spd);
        virtual ~Shield() {}

        virtual bool Collected() override;
};

// Lớp Apple kế thừa từ Item
class Apple : public Item {
    public:
        Apple(Vector2 pos, Texture2D tex, int spd);
        virtual ~Apple() {}

        virtual bool Collected() override;
};

// Lớp Trap kế thừa từ MovingObject
class Trap : public MovingObject {
    public:
        Trap(Vector2 pos, Texture2D tex, int spd);
        virtual ~Trap() {};

        virtual bool Collected() override;
};

#endif