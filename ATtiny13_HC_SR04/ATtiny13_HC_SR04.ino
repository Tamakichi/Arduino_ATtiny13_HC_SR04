//
// 超音波距離センサHC-SR04を使った距離計測  
//
// ATMEL ATTINY13 / ARDUINO
// 利用パッケージ：https://github.com/MCUdude/MicroCore
//
//                 +-Ｖ-+
// Reset      PB5 1|    |8 Vcc
// Tx         PB3 2|    |7 PB2 
// Rx         PB4 3|    |6 PB1 ECHO
//            GND 4|    |5 PB0 TRIG
//                 +----+
//

// シリアル通信ライブラリ
//   AVR half-duplex software UART supporting single pin operation
//   http://nerdralph.blogspot.jp/2014/01/avr-half-duplex-software-uart.html
//
#define BAUD_RATE 38400
#include "lib/BasicSerial3/BasicSerial3.h"
#define Tx    PB3(変更する場合、BasicSerial3.S修正が必要)
#define Rx    PB4(変更する場合、BasicSerial3.S修正が必要)

// HC-SR04
#define TRIG  PB0 // 出力ピン
#define ECHO  PB1 // 入力ピン
#define TEMP  180 // 温度補正 気温(℃)*10

// 整数を10進数で出力
void OutDEC(uint16_t d) {
int8_t n =-1;
  uint16_t v = 10000;
  for (uint8_t i=0; i<5; i++) {
    if (d >= v) {
      TxByte (d/v + '0');
      d %= v;
      n=i;
    } else {
      if (n!=-1||i==4) TxByte ('0');
    }
    v/=10;
  }
}
void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // 超音波の出力終了
  digitalWrite(TRIG,LOW);
  delayMicroseconds(1);

  // 超音波を出力
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(11);
 
  // 超音波を出力終了
  digitalWrite(TRIG, LOW);

  // 出力した超音波が返って来る時間を計測
  uint16_t d = (uint16_t)pulseIn(ECHO, HIGH, 200000);

  // 計測した時間と音速(気温を考慮)から反射物までの距離を計算
  uint16_t k=(3315+TEMP*6)/20; // 係数
  uint16_t v=d/100*k;
  uint16_t h=v/100;
  uint16_t l=v%100;

  // 計算結果をシリアル通信で出力
  OutDEC(h); TxByte('.'); OutDEC(l);
  TxByte('\n');
  delay(250);
}
