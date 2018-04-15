# Arduino_ATtiny13_HC_SR04
ATtiny13AでHC-SR04を使った距離計測

## 開発環境
Arduino 1.8.5にMicroCoreパッケージを追加  
https://github.com/MCUdude/MicroCore  

システムクロックは、9.6MHzで利用  

## 利用ライブラリ
シリアル出力はNerd Ralphさんが公開しているライブラリ、BasicSerial3 を利用しています。  

-  Nerd Ralph - AVR half-duplex software UART supporting single pin operation
  http://nerdralph.blogspot.jp/2014/01/avr-half-duplex-software-uart.html   
  BasicSerial3.Sのピン指定を修正して本ライブラリを添付しています。    
```
#define UART_Tx 3
#define UART_Rx 4
```
