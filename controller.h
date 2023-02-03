#pragma once

struct snake {
	int x, y;
};

struct food {
	int x, y;
	bool exist = false;
};

//hướng dẫn di chuyển rắn
void noteGame();

//vẽ tường, tính điểm
void drawWall();

//khởi tạo vị trí rắn
void creatSnake();

//vẽ vị trí hiện tại của rắn
void drawSnake();

//tăng kích thước rắn
void increaseSnakcSize(snake nextStep);

//vẽ mồi
void addFood();

bool suicide();

//kiểm tra chướng ngại vật
int checkAddress(snake nextStep);

void check(snake nextStep);

//di chuyển
void moveUp();
void moveRight();
void moveDown();
void moveLeft();

//cập nhật màn hình sau mỗi bước rắn đi
void updateDisplay();

void gameOver();

//hàm thực thi game
void run();
void Start();
void gamePlay();