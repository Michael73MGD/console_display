#include <string>
#include <iostream>
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for


using namespace std;

class Display{
private:
    string screen;
    int width, height;
    int speed;
public:
    Display(int w, int h, int s=100){
        width = w;
        height = h;
        speed = s;
        for(int j=0;j<h;j++){
            for(int i=0;i<w;i++){
                screen.append(". ");
            }
            screen.append("\n");
        }

        cout << "Display created. " <<endl;
        print();
    }
    //void add(Shape shape){
    //    shape.create(this);
    //}
    void print(){
        cout << screen<<endl;
    }
    void change(int x, int y, string c){
        // cout<<"x: "<<x<<endl;
        // cout<<"y: "<<y<<endl;
        // cout<<"w: "<<width<<endl;
        // cout<<"h: "<<height<<endl;
        screen.replace(y*(2*width+1)+x*2,2,c);
    }
    int getSpeed(){
        return speed;
    }
    void setSpeed(int s){
        speed = s;
    }
    int getWidth(){
        return width;
    }
};

class Shape{
private: 
    Display* d;
    string type;
    int x, y;
public:
    Shape(){
        x=0;
        y=0;
        d=nullptr;
        type = "";
    }
    //virtual void create(Display *display)=0;
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void setX(int x){
        this->x = x;
    }
    void setY(int y){
        this->y = y;
    }
    void setD(Display *d){
        d = d;
    }
};





class HorizontalLine:public Shape{
private:
    int length;
public:
    HorizontalLine(int x, int y, int length, Display *d){
        setX(x);
        setY(y);
        setLength(length);
        setD(d);
        //cout<<"here x is" <<getX()<<endl;
        for(int i=0;i<length;i++){
            d->change(getX(), getY(), "--");
            d->print();
            setX(++x);
            double s = d->getSpeed();
            this_thread::sleep_for(100ms);
        }
        
    }
    int getLength(){
        return length;
    }
    void setLength(int length){
        this->length = length;
    }
};

class VerticalLine:public Shape{
private:
    int length;
public:
    VerticalLine(int x, int y, int length, Display *d){
        setX(x);
        setY(y);
        setLength(length);
        setD(d);
        //cout<<"here x is" <<getX()<<endl;
        for(int i=0;i<length;i++){
            d->change(getX(), getY(), "| ");
            d->print();
            setY(++y);
            double s = d->getSpeed();
            this_thread::sleep_for(300ms);
        }
        
    }
    int getLength(){
        return length;
    }
    void setLength(int length){
        this->length = length;
    }
};

int main(){
    Display d = Display(45,8);
    HorizontalLine(3,2,20,&d);
    HorizontalLine(10,5,10,&d);
    VerticalLine(25,1,5,&d);
    return 0;
}