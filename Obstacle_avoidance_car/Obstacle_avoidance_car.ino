#include <Servo.h>
//舵机引脚
#define PIN_CAR_IN1 5
#define PIN_CAR_IN2 6
#define PIN_CAR_IN3 9
#define PIN_CAR_IN4 10
//继电器
int pinRelay = 8; //管脚D3连接到继电器模块的信号脚
//超声波
int incomedate = 0; 
const int trigPin = 3;//发声引脚
const int echoPin = 11;//回声引脚
long duration;//持续时间
int distance;//距离
Servo myServo; // 创建一个名为myServo的舵机控制对象
//超声波测距
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // 读取echoPin收到的回声信号,测量脉冲宽度时间
  distance= duration*0.034/2;
  return distance;
}
//小车向前
void doForward(){
 digitalWrite(PIN_CAR_IN3,LOW);
 digitalWrite(PIN_CAR_IN4,HIGH);
 digitalWrite(PIN_CAR_IN1,LOW);
 digitalWrite(PIN_CAR_IN2,HIGH);
}
//小车向后
void doBackward() {
 digitalWrite(PIN_CAR_IN3,HIGH);
 digitalWrite(PIN_CAR_IN4,LOW);
 digitalWrite(PIN_CAR_IN1,HIGH);
 digitalWrite(PIN_CAR_IN2,LOW);
}
//小车停止
void doStop() {
 digitalWrite(PIN_CAR_IN3,LOW);
 digitalWrite(PIN_CAR_IN4,LOW);
 digitalWrite(PIN_CAR_IN1,LOW);
 digitalWrite(PIN_CAR_IN2,LOW); 
 digitalWrite(PIN_CAR_IN3,HIGH);
 digitalWrite(PIN_CAR_IN4,HIGH);
 digitalWrite(PIN_CAR_IN1,HIGH);
 digitalWrite(PIN_CAR_IN2,HIGH);
}
//小车左转向
void doLeft() {
 digitalWrite(PIN_CAR_IN3,LOW);
 digitalWrite(PIN_CAR_IN4,HIGH);
 digitalWrite(PIN_CAR_IN1,HIGH);
 digitalWrite(PIN_CAR_IN2,LOW);  

}
//小车右转向
void doRight() {
 digitalWrite(PIN_CAR_IN3,HIGH);
 digitalWrite(PIN_CAR_IN4,LOW);
 digitalWrite(PIN_CAR_IN1,LOW);
 digitalWrite(PIN_CAR_IN2,HIGH);
}
int lookRight()
{
    myServo.write(10); 
    delay(500);
    int distance = calculateDistance();
    delay(100);
    myServo.write(90); 
    return distance;
}
int lookLeft()
{
    myServo.write(170); 
    delay(500);
    int distance = calculateDistance();
    delay(100);
    myServo.write(90); 
    return distance;
    delay(100);
}
void setup() {
  pinMode(PIN_CAR_IN1,OUTPUT);
  pinMode(PIN_CAR_IN2,OUTPUT);
  pinMode(PIN_CAR_IN3,OUTPUT);
  pinMode(PIN_CAR_IN4,OUTPUT);
  digitalWrite(PIN_CAR_IN1, OUTPUT);
  digitalWrite(PIN_CAR_IN2, OUTPUT);
  digitalWrite(PIN_CAR_IN3, OUTPUT);
  digitalWrite(PIN_CAR_IN4, OUTPUT);
  pinMode(pinRelay,OUTPUT); //设置pinRelay脚为输出状态
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //超声波引脚初始化
  pinMode(echoPin, INPUT); 
  myServo.attach(4); //舵机引脚
  myServo.write(90);
}
void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  distance = calculateDistance();// 调用计算超声波距离的函数
  //doForward();
  //光敏控制车灯
  Serial.println(analogRead(A0));
  delay(100);
  if(analogRead(A0)> 75){
   digitalWrite(pinRelay,HIGH);
   delay(100);
  }else{
   digitalWrite(pinRelay,LOW) ;
   delay(100);
  }
  //控制舵机
  if(distance <= 45){//前方有障碍物
   doStop();//停车
   delay(100);
   doBackward(); 
   delay(300);  
   doStop();//停车
   delay(200); 
   distanceR = lookRight();
   delay(200);
   distanceL = lookLeft();
   delay(200);
     if(distanceR >= distanceL)
    {
      doRight();
      delay(1000);
      doStop();
    }else{
      doLeft();
      delay(1000);
      doStop();
    }                                                                                                                                     
  }else{
   doForward();
  }
  //distance = calculateDistance();
}
