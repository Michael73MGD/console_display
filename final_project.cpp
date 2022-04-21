#include <string>
#include <iostream>
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for
using namespace std;

class Display{
private:
    string screen;
    int width, height;
    //int speed;
public:
    Display(int w, int h, int s=100){
        width = w;
        height = h;
        //speed = s;
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
    void clear(){
        string newScreen;
        for(int j=0;j<height;j++){
            for(int i=0;i<width;i++){
                newScreen.append(". ");
            }
            newScreen.append("\n");
        }
        screen = newScreen;

        cout << "Display cleared. " <<endl;
        print();
    }
    /*int getSpeed(){
        return speed;
    }
    void setSpeed(int s){
        speed = s;
    }*/
    int getWidth(){
        return width;
    }
    bool check(int x, int y){
        if(x <= width && y <= height){
            return true;
        }
        else{
            return false;
        }
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
        if(!d->check(x+length,y)){
            cout << "Line is out of bounds of the display. "<<endl;
            return;
        }
        setX(x);
        setY(y);
        setLength(length);
        setD(d);
        //cout<<"here x is" <<getX()<<endl;
        for(int i=0;i<length;i++){
            d->change(getX(), getY(), "--");
            d->print();
            setX(++x);
            //double s = d->getSpeed();
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
        if(!d->check(x,y+length)){
            cout << "Line is out of bounds of the display. "<<endl;
            return;
        }
        setX(x);
        setY(y);
        setLength(length);
        setD(d);
        //cout<<"here x is" <<getX()<<endl;
        for(int i=0;i<length;i++){
            d->change(getX(), getY(), "| ");
            d->print();
            setY(++y);
            //double s = d->getSpeed();
            this_thread::sleep_for(200ms);
        }
        
    }
    int getLength(){
        return length;
    }
    void setLength(int length){
        this->length = length;
    }
};

class Rectangle:public Shape{
private:
    int height, width;
public:
    Rectangle(int x, int y, int width, int height, Display *d){
        if(!d->check(x+width,y+height)){
            cout << "Rectangle is out of bounds of the display. "<<endl;
            return;
        }
        HorizontalLine(x, y, width, d);
        d->change(x, y, "|-");
        VerticalLine(x, y+1, height+1-2, d);
        d->change(x, y+height, "|-");
        HorizontalLine(x+1, y+height, width-1, d);
        VerticalLine(x+width, y, height+1, d);
    }
};

class Circle:public Shape{
public:
    Circle(int x, int y, Display *d){
        if(!d->check(x+1,y)){
            cout << "Circle is out of bounds of the display. "<<endl;
            return;
        }
        setX(x);
        setY(y);
        setD(d);
        d->change(x, y-2, "__");
        d->print();
        this_thread::sleep_for(200ms);
        d->change(x, y-1, "  ");
        d->print();
        this_thread::sleep_for(200ms);
        d->change(x-1, y-1, " /");
        d->print();
        this_thread::sleep_for(200ms);
        d->change(x+1, y-1, "\\ ");
        d->print();
        this_thread::sleep_for(200ms);
        d->change(x-1, y, " \\");
        d->print();
        this_thread::sleep_for(200ms);
        d->change(x+1, y, "/ ");
        d->print();
        this_thread::sleep_for(200ms);
        d->change(x, y, "__");
        d->print();
        this_thread::sleep_for(200ms);
    }
};

int main(){
    //good for vscode
    Display d = Display(45,8);
    //Display d = Display(65,30);
    HorizontalLine(3,2,20,&d);
    HorizontalLine(10,5,10,&d);
    VerticalLine(25,1,5,&d);
    Rectangle(27,2,10,4,&d);
    Circle(2,5,&d);
    Circle(40,5,&d);

    Circle(46,5,&d);
    //d.clear();

    return 0;
}