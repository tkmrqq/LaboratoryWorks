#include <cstdio>
#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

class Car {
    string mark;
    unsigned num;
    string color;
    unsigned current_speed;
public:
    Car(string mark_, unsigned num_, string color_, unsigned current_speed_) : mark(std::move(mark_)),
    num(num_), color(std::move(color_)), current_speed(current_speed_) {}

    void beep(){
        cout << "Beep!" << '\n';
    }

    void drive(){
        char answer;
        cout << "Do u rlly want to add speed?(Y/n)" << '\n';
        answer = getchar();
        if(answer == 'y' || answer == 'Y'){
            cout << "What speed do you want to add?" << '\n';
            cin >> current_speed;
        }
    }
};


int main() {
    Car cars[3];
    cars[0] = Car{"Porcshe", 4012, "black", 0};

}
