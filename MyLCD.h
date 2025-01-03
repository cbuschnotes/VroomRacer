/*
 * Code by Chris Busch (c) 2024
 * There are no warranties express or implied with this code.
 * No guarantees of being fit for purpose.
 */
 
#define SCROLLDELAY 700
#include <LiquidCrystal.h>
LiquidCrystal realLcd(7, 8, 9, 10, 11, 12);
class MyLCD {
  private:
  void clearLine(){
    ///////////////1234567890123456789012345678901234567890
    realLcd.print("                                       ");
  }
  
  public:
  
  
  int lefts;
  unsigned long scrolled;

  MyLCD():lefts(0),scrolled(millis()){}

  void begin(int a,int b){
    realLcd.begin(a,b);
  }

  void scrollLeft(){
    if( scrolled+SCROLLDELAY <millis()){
        realLcd.scrollDisplayLeft();
        scrolled=millis();
        lefts++;
        lefts %= 40;
    }  
  }
  void recenter(){
    while(lefts>0){
      delay(3);
      realLcd.scrollDisplayRight();
      lefts--;
    } 
  }
  

  void setCursor(int col,int row){
    realLcd.setCursor(col,row);
    recenter();
    clearLine();
    realLcd.setCursor(col,row);
  }
    
  // Templated member function
  template <typename T>
  void print(const T& value) {
     realLcd.print(value);
     scrolled=millis()+2000;
  }

  void print(char* label,unsigned long lt){
    realLcd.print(label);
    if(lt<10000) {
      realLcd.print(lt);
      realLcd.print("ms");
    }else if(lt>60000){
      lt/=100;
      realLcd.print(lt/10.0);
      realLcd.print("s");
    }else{
      realLcd.print(lt/1000.0);
      realLcd.print("s");
    }
  }
  
  

};
