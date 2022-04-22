#include <string>
#include <iostream>
#include <chrono> 
#include <thread> 
using namespace std;

//This display class handles creating the grid where things will be drawn
class Display{
private:
    string screen;
    int width, height;
    //int speed;
public:
    //constructor takes a width and height, the optional s was going to be used for speed control
    Display(int w, int h, int s=100){
        width = w;
        height = h;
        //speed = s;
        //This loop initializes the screen with the grid of dots
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
    //This function is called everytime a shape wants to update the display
    void change(int x, int y, string c){
        // cout<<"x: "<<x<<endl;
        // cout<<"y: "<<y<<endl;
        // cout<<"w: "<<width<<endl;
        // cout<<"h: "<<height<<endl;
        
        //The following line replaces characters at a certain location with those held in c
        screen.replace(y*(2*width+1)+x*2,2,c);
    }
    //This function clears the display by creating a new one, similar to the constructor
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
    //This function is used before drawing a shape to confirm that it isn't out of bounds of the display
    bool check(int x, int y){
        if(x <= width && y <= height){
            return true;
        }
        else{
            return false;
        }
    }
};

//This shape class is the parent to all following specific shape classes
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
    //virtual void identify()=0;
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
        //Check if the rightmost character is out of bounds of the display
        if(!d->check(x+length,y)){
            cout << "Line is out of bounds of the display. "<<endl;
            return;
        }
        setX(x);
        setY(y);
        setLength(length);
        setD(d);
        //cout<<"here x is" <<getX()<<endl;
        //loops through and calls the change function to update characters
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
        //Creates a vertical line by using the change function and incrementing y
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
        //Creates a rectangle by drawing 2 horizontal lines and one vertical line
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
        //Draws a circle by calling the change function multiple times
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
    //This display size works well with the terminal integrated in vscode
    Display d = Display(45,8);
    //The following display is very large, better for a full screen terminal
    //Display d = Display(65,30);
    HorizontalLine(3,2,20,&d);
    HorizontalLine(10,5,10,&d);
    VerticalLine(25,1,5,&d);
    Rectangle(27,2,10,4,&d);
    Circle(2,5,&d);
    Circle(40,5,&d);

    //This circle is purposely out of bounds to display how the bounds check works
    Circle(46,5,&d);
    //The following line can be used to clear the display
    //d.clear();

    return 0;
}