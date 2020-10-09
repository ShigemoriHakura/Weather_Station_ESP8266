#include "wifi_link_tool.h"

#include "Wire.h"
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include "EPD_drive.h"
#include "EPD_drive_gpio.h"
#include "bitmaps.h"
#include "FS.h"

#include "SHT20.h"

SHT20    sht20;

String header;

Duck_EPD EPD;
const int BATTERY_LEVEL_PIN = A0;
const char* wurl = "";
const char* token = "";
IPAddress ip;
const int CONFIG_HTTPPORT   = 80;
IPAddress timeServer( 120, 25, 115, 20 );                         /* 阿里云ntp服务器 如果失效可以使用 120.25.115.19   120.25.115.20 */
#define STD_TIMEZONE_OFFSET +8                                     /* 设置中国 */
const int timeZone = 8;                                            /* 修改北京时区 */
WiFiUDP   Udp;
unsigned long     previousMillis  = 0;
const long        interval  = 300000;        /* 300秒更新屏幕 */
unsigned long     previousMillis2 = 0;
const long        interval2 =3600000;      /* 一小时更新天气  */

unsigned int  localPort = 8266;                                 /* 修改udp 有些路由器端口冲突时修改 */

void setup() {
  WiFiServer    HTTPserver( CONFIG_HTTPPORT );
  //启动程序
  Serial.begin(115200);
  pinMode(CS, OUTPUT); //io初始化
  pinMode(DC, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(BUSY, INPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(BATTERY_LEVEL_PIN, INPUT);
  pinMode(5, INPUT_PULLUP);
  
  SPIFFS.begin();
  Serial.println("");
  Serial.printf("初始IO完成 %dms\n", millis());


  EPD.EPD_Set_Model();    //设置屏幕类型
  EPD.EPD_init_Full();         //全刷初始化，使用全刷波形
  EPD.clearbuffer();           //清空缓存(全白)
  EPD.fontscale = 2;           //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
  EPD.SetFont(FONT12);         //选择字体(仅FONT12支持中文)，字体可用群文件工具生成上传至spiffs使用

  EPD.DrawUTF(52, 0, "启动中");
  EPD.DrawUTF(78, 0, "如需重置则按下EN按键后");
  EPD.DrawUTF(104, 0, "再按住AP按键2秒");
  EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片刷新屏幕
  EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
  EPD.deepsleep();//睡眠 屏幕进入低功耗模式，屏幕用完后必须使用，否则图像会慢慢变色，唤醒可用Init函数

  Serial.printf("屏幕首刷完成 %dms\n", millis());
  
  rstb = 5;
  if (digitalRead(rstb) == LOW)
  {
    EPD.EPD_Set_Model();    //设置屏幕类型
    EPD.EPD_init_Full();         //全刷初始化，使用全刷波形
    EPD.clearbuffer();           //清空缓存(全白)
    EPD.fontscale = 2;           //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
    EPD.SetFont(FONT12);         //选择字体(仅FONT12支持中文)，字体可用群文件工具生成上传至spiffs使用
  
    EPD.DrawUTF(52, 0, "按住AP按键2秒来重置天气站");
    EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片刷新屏幕
    EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
    EPD.deepsleep();//睡眠 屏幕进入低功耗模式，屏幕用完后必须使用，否则图像会慢慢变色，唤醒可用Init函数
  
    Serial.printf("重置提示刷新完成 %dms\n", millis());
    blink(); 
  }
  
  /* 重置io */
  stateled = D4;
  Hostname = "NekoWeatherStation";
  /* 设备名称 允许中文名称 不建议太长 */
  wxscan = true;
  /* 是否被小程序发现设备 开启意味该设备具有后台 true开启 false关闭 */
  //blink();
  load();
  /* 初始化WiFi link tool */
  Serial.println( "设置 UDP" );
  Udp.begin( localPort );
  Serial.print( "Local port: " );
  Serial.println( Udp.localPort() );
  Serial.println( "正在等待同步" );
  
  if ( link() )
  {
    setSyncProvider( getNtpTime );
    fullRefreshDisplay();
    PartRefreshDisplay();
  }else{
    EPD.EPD_init_Full();         //全刷初始化，使用全刷波形
    EPD.clearbuffer();           //清空缓存(全白)
    EPD.fontscale = 2;           //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
    EPD.SetFont(FONT12);         //选择字体(仅FONT12支持中文)，字体可用群文件工具生成上传至spiffs使用
  
    EPD.DrawUTF(52, 0, "请连接 NekoStation 并配置Wifi");
    EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片刷新屏幕
    EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
    EPD.deepsleep();//睡眠 屏幕进入低功耗模式，屏幕用完后必须使用，否则图像会慢慢变色，唤醒可用Init函数
  }
}

void fullRefreshDisplay(){
  Serial.println("全刷开始");
  digitalWrite(12, HIGH);
  fullInitDisplay();
  digitalWrite(12, LOW);
  Serial.println("全刷完成");
}


void PartRefreshDisplay(){
  Serial.println("局刷开始");
  PartInitDisplay();
  Serial.println("局刷完成");
}

void PartInitDisplay(){
  digitalWrite(12, HIGH);
  digitalWrite (CLK, LOW);
  digitalWrite (DIN, LOW);
  delay(1000);
  Wire.begin(D7, D5) ;
  sht20.initSHT20(Wire);
  delay(100);
  sht20.checkSHT20();
  float humd = sht20.readHumidity();
  float temp = sht20.readTemperature();
  digitalWrite(12, LOW);
  Serial.println(String("Time:") + millis() + " Temperature:" + temp + "C" + " Humidity:" + humd + "%");
  pinMode(CLK, OUTPUT);
  pinMode(DIN, OUTPUT);
  EPD.EPD_init_Part();
  EPD.clearbuffer();
  EPD.fontscale = 1;
  EPD.SetFont(FONT12);
  if(temp != 998 && humd != 998){
    EPD.DrawUTF(75, 200, "室温 " + getFloatLong1(temp) + "°");
    EPD.DrawUTF(88, 200, "湿度 " + getFloatLong1(humd) + "%");
  }
  if (WiFi.status() == WL_CONNECTED) {
    String url = String("http://") + wurl + "/api/base?token=" + token;
    String timeStamp = httpGETRequest(url);
    Serial.println(timeStamp);
    if (timeStamp != "{}") {
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, timeStamp);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      }
      String temperature = doc["data"]["temperature"];
      String humidity = doc["data"]["humidity"];
      String icon = doc["data"]["icon"];
      String weather = doc["data"]["weather"];
      String winddirection = doc["data"]["winddirection"];
      String windpower = doc["data"]["windpower"];
      
      EPD.fontscale = 1;
      EPD.SetFont(ICON80);
      EPD.DrawUTF(15, 105, String(char(EPD.getIcon(icon.toInt()))));
      EPD.SetFont(FONT12);
      EPD.fontscale = 2;
      EPD.DrawUTF(18, 200, temperature + "°");
      EPD.DrawUTF(44, 200, weather );
      EPD.fontscale = 1;
      EPD.DrawXbm_P(20, 305, 12, 12, (unsigned char *)fl);
      EPD.DrawUTF(20, 318, "体感湿度" + humidity + "%");
      EPD.DrawXbm_P(34, 305, 12, 12, (unsigned char *)dir);
      EPD.DrawUTF(34, 318, "风向" + winddirection);
      EPD.DrawXbm_P(48, 305, 12, 12, (unsigned char *)sc);
      EPD.DrawUTF(48, 318, "风力" + windpower);
    }
  }
  EPD.DrawLine(20, 300, 100, 300);
  EPD.EPD_Dis_Part(15, 102, 105, 400, (unsigned char *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片刷新屏幕
  EPD.deepsleep();//睡眠 屏幕进入低功耗模式，屏幕用完后必须使用，否则图像会慢慢变色，唤醒可用Init函数
}

void loop() {
  pant(); /* WiFi link tool 服务维持函数  请勿修改位置 */
  if ( link() )
  {
    unsigned long currentMillis = millis();
    if ( currentMillis - previousMillis >= interval )
    {
      previousMillis = currentMillis;
      Serial.println( "刷新" );
      PartRefreshDisplay();
    }
    unsigned long currentMillis2 = millis();
    if ( currentMillis2 - previousMillis2 >= interval2 )
    {
      previousMillis2 = currentMillis2;
      Serial.println( "全部" );
      fullRefreshDisplay();
      PartRefreshDisplay();
    }
  }
}

void fullInitDisplay() {
  EPD.EPD_init_Full();
  EPD.clearbuffer();
  EPD.SetFont(FONT12);
  EPD.fontscale = 1;
  if (WiFi.status() == WL_CONNECTED) {
    //刷新天气
    String url = String("http://") + wurl + "/api/weather?token=" + token;
    String timeStamp = httpGETRequest(url);
    Serial.println(timeStamp);
    if (timeStamp != "{}") {
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, timeStamp);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      }
      String dayText = doc["data"]["dayText"];
      String timeText = doc["data"]["timestampText"];
      String dayTemp = doc["data"]["dayTemp"];
      String nightTemp = doc["data"]["nightTemp"];
      String code_d = doc["data"]["code_d"];
      String code_n = doc["data"]["code_n"];
      String text_d = doc["data"]["text_d"];
      String text_n = doc["data"]["text_n"];
      int point_n = doc["data"]["point_n"];
      int line_n = doc["data"]["line_n"];
      String date = doc["data"]["date"];
      String note = doc["data"]["note"];
      String city = doc["data"]["city"];
      EPD.DrawUTF(0, 14, city);
      EPD.DrawUTF(0, 60, note);
      EPD.fontscale = 2;
      EPD.DrawUTF(18, 2, dayText);
      EPD.fontscale = 1;
      EPD.DrawWeatherChart(190, 220, 25, 375, point_n, line_n, dayTemp, nightTemp, code_d, code_n, text_d, text_n, date);
      EPD.DrawUTF(0, 155, "更新于：" + timeText);
    }
  }
  
  byte level = batteryLevel();
  if(level <= 10){
    EPD.DrawXbm_P(0, 380, 20, 12, (unsigned char *)batt_0);
  }else if(level > 10 &&level <= 20){
    EPD.DrawXbm_P(0, 380, 20, 12, (unsigned char *)batt_1);
  }else if(level > 20 &&level <= 40){
    EPD.DrawXbm_P(0, 380, 20, 12, (unsigned char *)batt_2);
  }else if(level > 40 && level <= 60){
    EPD.DrawXbm_P(0, 380, 20, 12, (unsigned char *)batt_3);
  }else if(level > 60 && level <= 80){
    EPD.DrawXbm_P(0, 380, 20, 12, (unsigned char *)batt_4);
  }else if(level > 80){
    EPD.DrawXbm_P(0, 380, 20, 12, (unsigned char *)batt_5);
  }
  
  EPD.DrawXbm_P(0, 0, 12, 12, (unsigned char *)city_icon);
  EPD.Inverse(0, 13, 0, 400);
  EPD.DrawUTF(290, 0, "IP: " + WiFi.localIP().toString());

  EPD.DrawLine(20, 100, 100, 100);
  EPD.DrawLine(20, 300, 100, 300);
  //EPD.DrawLine(300, 50, 300, 100);

  EPD.EPD_Dis_Full((unsigned char *)EPD.EPDbuffer, 1);
  EPD.ReadBusy_long();
  EPD.deepsleep();
}

byte batteryLevel(){
  //+-------+---------------+------+
  //| Input |    Output     | Bits |
  //+-------+---------------+------+
  //| 4.3v  | 1v            | 1023 |
  //| 4.2v  | 0.774v        |  774 |
  //| 3.7v  | 0.8604651163v |  880 |
  //| 3.3v  | 0.7674418605v |  785 |
  //| 3.2v  | 0.7441860465v |  761 |
  //| 3.1v  | 0.7209302326v |  738 |
  //| 3     | 0.6976744186v |  714 |
  //+-------+---------------+------+

  int val = analogRead(BATTERY_LEVEL_PIN);
  Serial.println(String("Battery:") + val);
  return map(val, 600, 774, 0, 100);
}

String httpGETRequest(String server) {
  String payload = "{}";

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.setTimeout(1500);
    http.begin(server);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      payload = http.getString();
    }
    http.end();
  }

  return payload;
}

String getFloatLong1(float value) {
  String gy;
  long tmp = value;  // 整数部分
  long yytmp = (value - tmp) * 10 + 0.5; // 小数, 四捨五入
  if (yytmp >= 10) { // 防错
    tmp += 1;    // 整数部分 + 1
    yytmp = 0;
  }
  gy += tmp; // 整数部分
  gy += ".";  // 小数点, 废话
  gy += yytmp;
  return gy;
}

const int NTP_PACKET_SIZE = 48;
byte    packetBuffer[NTP_PACKET_SIZE];

time_t getNtpTime()
{
  while ( Udp.parsePacket() > 0 )
    ;
  Serial.println( "连接时间服务器" );
  sendNTPpacket( timeServer );
  uint32_t beginWait = millis();
  while ( millis() - beginWait < 1500 )
  {
    int size = Udp.parsePacket();
    if ( size >= NTP_PACKET_SIZE )
    {
      Serial.println( "时间服务器应答" );
      Udp.read( packetBuffer, NTP_PACKET_SIZE );
      unsigned long secsSince1900;
      /* convert four bytes starting at location 40 to a long integer */
      secsSince1900 = (unsigned long) packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long) packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long) packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long) packetBuffer[43];
      return(secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR);
    }
  }
  Serial.println( "No NTP Response :-(" );
  return(0);
}


void sendNTPpacket( IPAddress &address )
{
  memset( packetBuffer, 0, NTP_PACKET_SIZE );

  packetBuffer[0] = 0b11100011;
  packetBuffer[1] = 0;
  packetBuffer[3] = 0xEC;

  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  Udp.beginPacket( address, 123 );
  Udp.write( packetBuffer, NTP_PACKET_SIZE );
  Udp.endPacket();
}
