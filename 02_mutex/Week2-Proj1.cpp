#include <iostream>
#include <string>
#include <limits>

class MotorController {
private:
    bool motor_on;           // 电机状态：开或关
    int speed;               // 电机速度：0-100
    std::string direction;   // 电机方向：前进、后退
    std::string mode;        // 当前模式：手动或自动

public:
    MotorController() : motor_on(false), speed(0), direction("停止"), mode("手动") {}

    // 启动电机
    void startMotor() {
        if (!motor_on) {
            motor_on = true;
            std::cout << "电机已启动。\n";
        }
        else {
            std::cout << "电机已经在运行中。\n";
        }
    }

    // 关闭电机
    void stopMotor() {
        if (motor_on) {
            motor_on = false;
            speed = 0;
            direction = "停止";
            std::cout << "电机已停止。\n";
        }
        else {
            std::cout << "电机已经关闭。\n";
        }
    }

    // 设置电机速度
    void setSpeed(int s) {
        if (!motor_on) {
            std::cout << "电机未启动，请先启动电机。\n";
            return;
        }
        if (s < 0 || s > 100) {
            std::cout << "速度必须在0到100之间。\n";
            return;
        }
        speed = s;
        std::cout << "电机速度已设置为 " << speed << "%。\n";
    }

    // 设置电机方向
    void setDirection(const std::string& dir) {
        if (!motor_on) {
            std::cout << "电机未启动，请先启动电机。\n";
            return;
        }
        if (dir != "顺时针" && dir != "逆时针") {
            std::cout << "方向应为“顺时针”或“逆时针”。\n";
            return;
        }
        direction = dir;
        std::cout << "电机方向已设置为 " << direction << "。\n";
    }

    // 设置工作模式（手动/自动）
    void setMode(const std::string& new_mode) {
        if (!motor_on) {
            std::cout << "电机未启动，请先启动电机。\n";
            return;
        }
        if (new_mode != "手动" && new_mode != "自动") {
            std::cout << "模式应为“手动”或“自动”。\n";
            return;
        }
        mode = new_mode;
        std::cout << "工作模式已切换为 " << mode << " 模式。\n";
    }

    // 显示当前状态
    void displayStatus() {
        std::cout << "\n电机控制面板\n";
        std::cout << "-------------------------\n";
        std::cout << "电机状态: " << (motor_on ? "开启" : "关闭") << "\n";
        std::cout << "当前速度: " << (motor_on ? std::to_string(speed) + "%" : "N/A") << "\n";
        std::cout << "当前方向: " << (motor_on ? direction : "N/A") << "\n";
        std::cout << "工作模式: " << (motor_on ? mode : "N/A") << "\n";
        std::cout << "-------------------------\n";
    }

    // 主菜单
    void showMenu() {
        int choice;
        do {
            std::cout << "\n电机控制面板菜单\n";
            std::cout << "-------------------\n";
            std::cout << "1. 启动电机\n";
            std::cout << "2. 停止电机\n";
            std::cout << "3. 设置速度\n";
            std::cout << "4. 设置方向\n";
            std::cout << "5. 设置模式\n";
            std::cout << "6. 显示状态\n";
            std::cout << "7. 退出程序\n";
            std::cout << "请选择操作（1-7）：";
            std::cin >> choice;

            // 清空输入缓冲区，以防止输入问题
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switch (choice) {
            case 1:
                startMotor();
                break;
            case 2:
                stopMotor();
                break;
            case 3: {
                int speed;
                std::cout << "请输入速度（0-100）：";
                std::cin >> speed;
                setSpeed(speed);
                break;
            }
            case 4: {
                std::string direction;
                std::cout << "请输入方向（顺时针/逆时针）：";
                std::cin >> direction;
                setDirection(direction);
                break;
            }
            case 5: {
                std::string mode;
                std::cout << "请输入模式（手动/自动）：";
                std::cin >> mode;
                setMode(mode);
                break;
            }
            case 6:
                displayStatus();
                break;
            case 7:
                std::cout << "退出程序...\n";
                break;
            default:
                std::cout << "无效选择，请重新选择。\n";
            }
        } while (choice != 7);
    }
};

int main() {
    MotorController motor;
    motor.showMenu();
    return 0;
}
