#include "FS.h"
#include "EPD_drive.h"
#include "EPD_drive_gpio.h"


unsigned char UNICODEbuffer[200];
String fontname;

Duck_EPD::Duck_EPD() {

}


void Duck_EPD::SetFont(FONT fontindex)
{
  FontIndex = fontindex;
  switch (fontindex)
  {
    case 1:
      fontname = "/font32"; fontwidth = 32; fontheight = 32; break;
    case 2:
      fontname = "/font10"; fontwidth = 10; fontheight = 10; break;
    case 3:
      fontname = "/font12"; fontwidth = 12; fontheight = 12; break;
    case 5:
      fontname = "/font70"; fontwidth = 70; fontheight = 70; break;
    case 12:
      fontname = "/weathericon80"; fontwidth = 80; fontheight = 80; break;
    case 13:
      fontname = "/weathericon32"; fontwidth = 32; fontheight = 32; break;
    case 14:
      fontname = "/weathericon50"; fontwidth = 50; fontheight = 50; break;
  }
}
void Duck_EPD::DrawCircle(int x, int y, int r, bool fill)
{
  if (fill == 0)
  {
    for (int i = 0; i < 360; i++)
    {
      SetPixel(round(cos(i)*r + x), round(sin(i)*r) + y);

    }
  }
  else
  {
    for (int j = 0; j < r; j++)
    {

      for (int i = 0; i < 360; i++)
      {
        SetPixel(round(cos(i)*j + x), round(sin(i)*j) + y);

      }
    }
  }
}

void Duck_EPD::DrawBox(byte x, int y, int w, int h)
{

  for (int i = x; i < x + h; i++)
  {
    DrawXline( y, y + w - 1,  i);
  }

}
void Duck_EPD::DrawEmptyBox(int x, int y, int w, int h)
{
  DrawXline(y, y + w, x);
  DrawXline(y, y + w, x + h);
  DrawYline(x, x + w, y);
  DrawYline(x, x + w, y + w);

}

void Duck_EPD::DrawChart(int x, int y, int w, int c1, int c2, int c3, int c4, int c5, int c6)
{

  int percent, sum, max_c = 0;
  sum = c1 + c2 + c3 + c4 + c5 + c6;
  if (sum == 0) sum = 1;
  max_c = max(c1, max_c); max_c = max(c2, max_c); max_c = max(c3, max_c);
  max_c = max(c4, max_c); max_c = max(c5, max_c); max_c = max(c6, max_c);
  if (max_c == 0) max_c = 1;
  w = w * sum / (2 * max_c);

  SetFont(FONT12);
  DrawUTF(x, y, ">0.3um");
  percent = w * c1 / sum;
  DrawBox(x + 1, y + 41, percent, 10);
  SetFont(FONT10);
  DrawUTF(x + 2, y + 41 + percent, String(c1));

  SetFont(FONT12);
  DrawUTF(x + 12, y, ">0.5um");
  percent = w * c2 / sum;
  DrawBox(x + 13, y + 41, percent, 10);
  SetFont(FONT10);
  DrawUTF(x + 14, y + 41 + percent, String(c2));

  SetFont(FONT12);
  DrawUTF(x + 24, y, ">1.0um");
  percent = w * c3 / sum;
  DrawBox(x + 25, y + 41, percent, 10);
  SetFont(FONT10);
  DrawUTF(x + 26, y + 41 + percent, String(c3));

  SetFont(FONT12);
  DrawUTF(x + 36, y, ">2.5um");
  percent = w * c4 / sum;
  DrawBox(x + 37, y + 41, percent, 10);
  SetFont(FONT10);
  DrawUTF(x + 38, y + 41 + percent, String(c4));

  SetFont(FONT12);
  DrawUTF(x + 48, y, ">5.0um");
  percent = w * c5 / sum;
  DrawBox(x + 49, y + 41, percent, 10);
  SetFont(FONT10);
  DrawUTF(x + 50, y + 41 + percent, String(c5));

  SetFont(FONT12);
  DrawUTF(x + 60, y, ">10um");
  percent = w * c6 / sum;
  DrawBox(x + 61, y + 41, percent, 10);
  SetFont(FONT10);
  DrawUTF(x + 62, y + 41 + percent, String(c6));


}
void Duck_EPD::DrawCircleChart(int x, int y, int r, int w, int c1, int c2, int c3)
{
  int sum = c1 + c2 + c3;
  if (sum == 0) sum = 1;
  for (int i = 0; i < 360; i++)
  {
    SetPixel(-round(cos(M_PI * i / 180)*r) + x, round(sin(M_PI * i / 180)*r) + y);

  }

  for (int i = 0; i < 360; i++)
  {
    SetPixel(-round(cos(M_PI * i / 180) * (r - w)) + x, round(sin(M_PI * i / 180) * (r - w)) + y);

  }

  for (int i = 0; i < c1 * 360 / sum; i++)
  {
    for (int j = 0; j < w; j++)
    {
      SetPixel(-round(cos(M_PI * i / 180) * (r - j)) + x, round(sin(M_PI * i / 180) * (r - j)) + y);
    }
  }

  for (int i = (c1 + c2) * 360 / sum - 1; i < (c1 + c2) * 360 / sum; i++)
  {

    for (int j = 0; j < w; j++)
    {
      SetPixel(-round(cos(M_PI * i / 180) * (r - j)) + x, round(sin(M_PI * i / 180) * (r - j)) + y);
    }
  }

  for (int i = (c1 + c2) * 360 / sum; i < 360; i += 10)
  {

    for (int j = 0; j < w; j++)
    {
      SetPixel(-round(cos(M_PI * i / 180) * (r - j)) + x, round(sin(M_PI * i / 180) * (r - j)) + y);
    }
  }

  y += 2;
  DrawBox(x - r, y + r + 2, 8, 8);
  SetFont(FONT12);
  DrawUTF(x - r - 2, y + r + 12, "PM1.0");
  SetFont(FONT12);
  DrawUTF(x - r - 2, y + r + 12 + 30, String(c1));


  SetFont(FONT12);
  DrawEmptyBox(x - r + 14, y + r + 2, 8, 8);
  DrawUTF(x - r + 12, y + r + 12, "PM2.5");

  SetFont(FONT12);
  DrawUTF(x - r + 12, y + r + 12 + 30, String(c2));
  DrawEmptyBox(x - r + 28, y + r + 2, 8, 8);
  for (int i = y + r + 2; i < y + r + 2 + 8; i += 2)
  {
    DrawYline(x - r + 28, x - r + 28 + 7, i);
  }
  SetFont(FONT12);
  DrawUTF(x - r + 26, y + r + 12, "PM10");
  SetFont(FONT12);
  DrawUTF(x - r + 26, y + r + 12 + 30, String(c3));


}
int Duck_EPD::getIcon(int weathercodeindex) {
  if (weathercodeindex == 0) return 12;
  if (weathercodeindex == 1) return 58;
  if (weathercodeindex == 2) return 58;
  if (weathercodeindex == 3) return 58;
  if (weathercodeindex == 4) return 54;
  if (weathercodeindex >= 5 && weathercodeindex <= 18) return 0;
  if (weathercodeindex >= 19 && weathercodeindex <= 32) return 19;
  if (weathercodeindex >= 33 && weathercodeindex <= 36)   return 5;
  if (weathercodeindex >= 37 && weathercodeindex <= 40)   return 16;
  if (weathercodeindex == 41) return 28;
  if (weathercodeindex == 42) return 28;
  if (weathercodeindex == 43) return 28;
  return 17;
}
void Duck_EPD::DrawWeatherChart(int xmin, int xmax, int ymin, int ymax, int point_n, int line_n, String tmax, String tmin, String code_d, String code_n, String text_d, String text_n, String date) //绘制天气温度变化曲线
{
  if (tmax == ",,,,,")
  {
    tmax = "5,5,5,5,5,5";
    tmin = "2,2,2,2,2,2";
    code_d = "0,0,0,0,0,0";
    code_n = "0,0,0,0,0,0";
    text_n = "晴,晴,晴,晴,晴,晴";
    text_d = "晴,晴,晴,晴,晴,晴";
    date = "1,2,3,4,5,6";
  }
  String code_d_a[point_n], code_n_a[point_n], text_d_a[point_n], text_n_a[point_n], date_a[point_n];

  int tmax_a[point_n], tmin_a[point_n];
  int min_data = 999, max_data = -999;
  int tmin_x_cord[point_n], tmax_x_cord[point_n]; //将数值转成屏幕坐标
  String temp_min[point_n];
  String temp_max[point_n];
  int j = 0, k = 0, l = 0;
  //分割tmax和tmin
  //Serial.println(tmax); Serial.println(tmin);
  //Serial.println(code_d);
  for (int i = 0; i < tmin.length(); i++)
  {
    temp_min[j] += tmin[i];

    if (tmin.charAt(i) == char(',')) j++;

  }
  for (int i = 0; i < tmax.length(); i++)
  {

    temp_max[k] += tmax[i];

    if (tmax.charAt(i) == char(',')) k++;
  }

  j = 0;
  //分割code_d
  for (int i = 0; i < code_d.length(); i++)
  {
    code_d_a[j] += code_d[i];
    if (code_d.charAt(i) == char(',')) j++;
  }
  //分割code_n
  j = 0;
  for (int i = 0; i < code_n.length(); i++)
  {
    code_n_a[j] += code_n[i];
    if (code_n.charAt(i) == char(',')) j++;
  }
  //分割text_d
  j = 0;
  for (int i = 0; i < text_d.length(); i++)
  {
    if (text_d.charAt(i) == char(',')) j++;
    else text_d_a[j] += text_d[i];
  }
  //分割text_n
  j = 0;
  for (int i = 0; i < text_n.length(); i++)
  {
    if (text_n.charAt(i) == char(',')) j++;
    else text_n_a[j] += text_n[i];
  }
  //分割date_n
  j = 0;
  for (int i = 0; i < date.length(); i++)
  {
    if (date.charAt(i) == char(',')) j++;
    else date_a[j] += date[i];
  }
  for (int i = 0; i < point_n; i++)
  {
    tmax_a[i] = temp_max[i].toInt(); //Serial.printf("max:%d\n",tmax_a[i]);
    tmin_a[i] = temp_min[i].toInt(); //Serial.printf("min:%d\n",tmin_a[i]);
  }
  //找出计算最大最小值
  for (int i = 0; i < point_n; i++)
  {
    if (tmax_a[i] > max_data) max_data = tmax_a[i];
    if (tmax_a[i] < min_data) min_data = tmax_a[i];
    if (tmin_a[i] > max_data) max_data = tmin_a[i];
    if (tmin_a[i] < min_data) min_data = tmin_a[i];
  }
  //转换坐标
  if ((max_data - min_data) != 0)
  {
    for (int i = 0; i < point_n; i++)
    {
      tmin_x_cord[i] = xmax - ((xmax - xmin) * (tmin_a[i] - min_data) / (max_data - min_data));
      tmax_x_cord[i] = xmax - ((xmax - xmin) * (tmax_a[i] - min_data) / (max_data - min_data));
    }
  }
  int dy = (ymax - ymin) / (point_n - 1);

  /*
    Spline line;
    float x[point_n];float y[point_n];
    for(int i=0;i<point_n;i++)
    {
    y[i]=*data;x[i]=ymin+dy*i;
    data++;
    }
    data=o;
    line.setPoints(x,y,point_n);
    line.setDegree(11);
    for(int i=ymin;i<ymax;i++)
    {
    SetPixel(line.value(i),i);

    }
  */
  //画折线
  for (int i = 0; i < point_n - 1; i++)
  {
    DrawLine(tmin_x_cord[i], ymin + dy * i, tmin_x_cord[i + 1], ymin + dy * (i + 1));
    DrawLine(tmax_x_cord[i], ymin + dy * i, tmax_x_cord[i + 1], ymin + dy * (i + 1));

    // DrawLine(tmin_x_cord[i]-1,ymin+dy*i,tmin_x_cord[i+1]-1,ymin+dy*(i+1));
    // DrawLine(tmax_x_cord[i]-1,ymin+dy*i,tmax_x_cord[i+1]-1,ymin+dy*(i+1));
  }
  //画圆圈，添加标注
  for (int i = 0; i < point_n; i++)
  {
    DrawCircle(tmin_x_cord[i], ymin + dy * i, 3, 1);
    DrawCircle(tmax_x_cord[i], ymin + dy * i, 3, 1);
    SetFont(FONT12); fontscale = 1;

    DrawUTF(tmax_x_cord[i] - 14, ymin + dy * i - 3 * (String(tmax_a[i]).length() + 1), String(tmax_a[i]) + "°");
    DrawUTF(tmin_x_cord[i] + 2, ymin + dy * i - 3 * (String(tmax_a[i]).length() + 1), String(tmin_a[i]) + "°");

    SetFont(ICON32); DrawUTF(xmin - 44, ymin + dy * i - 16, String(char(getIcon(code_d_a[i].toInt()))));
    SetFont(FONT12); DrawUTF(xmin - 56, ymin + dy * i - 2 * text_d_a[i].length(), text_d_a[i]);
    DrawUTF(xmin - 82, ymin + dy * i - 2 * date_a[i].length(), date_a[i]);

    SetFont(ICON32); DrawUTF(xmax + 14, ymin + dy * i - 16, String(char(getIcon(code_n_a[i].toInt()))));
    SetFont(FONT12); DrawUTF(xmax + 46, ymin + dy * i - 2 * text_n_a[i].length(), text_n_a[i]);



    //Serial.print("code_d:");
    //Serial.println(code_d_a[i]);
    //Serial.print("txt_n:");
    //Serial.println(text_n_a[i]);
  }
  Inverse(xmin - 83, xmin - 69, 0, 400);
}
void Duck_EPD::DrawXline(int start, int end, int x)
{
  for (int i = start; i <= end; i++)
  {
    SetPixel(x, i);
  }
}
void Duck_EPD::DrawYline(int start, int end,  int y)
{
  for (int i = start; i <= end; i++)
  {
    SetPixel(i, y);
  }
}
void Duck_EPD::DrawLine(int xstart, int ystart, int xend, int yend)
{

  int dx = abs(xend - xstart); int dy = abs(yend - ystart);
  if (dx >= dy)
  {
    if (xend > xstart)
    {
      for (int i = xstart; i <= xend; i++)
      {
        SetPixel(i, round((i - xstart) * (yend - ystart) / (xend - xstart)) + ystart);
      }
    }
    else
    {
      for (int i = xstart; i >= xend; i--)
      {
        SetPixel(i, round((i - xstart) * (yend - ystart) / (xend - xstart)) + ystart);
      }

    }
  }

  else
  {
    if (yend > ystart)
    {
      for (int i = ystart; i <= yend; i++)
      {
        SetPixel(round((i - ystart) * (xend - xstart) / (yend - ystart)) + xstart, i);
      }
    }
    else
    {
      for (int i = ystart; i >= yend; i--)
      {
        SetPixel(round((i - ystart) * (xend - xstart) / (yend - ystart)) + xstart, i);
      }

    }
  }
}

void Duck_EPD::Inverse(int xStart, int xEnd, int yStart, int yEnd)
{
  for (int i = 0; i < (xEnd - xStart); i++)
  {
    for (int j = 0; j < (yEnd - yStart); j++)
    {
      InversePixel(xStart + i, yStart + j);
    }

  }

}
void Duck_EPD::DrawUTF(int16_t x, int16_t y, String code)
{
  char buffer[200];
  code.toCharArray(buffer, 200);
  DrawUTF(x, y, fontwidth, fontheight, (unsigned char *)buffer);
}
void Duck_EPD::DrawUTF(int16_t x, int16_t y, byte width, byte height, unsigned char *code)
{
  int charcount;
  charcount = UTFtoUNICODE((unsigned char*)code);
  DrawUnicodeStr(x, y, width, height, charcount, (unsigned char *)UNICODEbuffer);

}
int Duck_EPD::UTFtoUNICODE(unsigned char *code)
{
  int i = 0; int charcount = 0;
  while (code[i] != '\0')
  {
    //Serial.println("current codei");
    //Serial.println(code[i],HEX);
    //  Serial.println(code[i]&0xf0,HEX);
    if (code[i] <= 0x7f) //ascii
    {

      UNICODEbuffer[charcount * 2] = 0x00;
      UNICODEbuffer[charcount * 2 + 1] = code[i];
      // Serial.println("english or number");
      // Serial.println(UNICODEbuffer[charcount*2],HEX);
      //  Serial.println(UNICODEbuffer[charcount*2+1],HEX);
      i++; charcount++;

    }
    else if ((code[i] & 0xe0) == 0xc0)
    {

      UNICODEbuffer[charcount * 2 + 1] = (code[i] << 6) + (code[i + 1] & 0x3f);
      UNICODEbuffer[charcount * 2] = (code[i] >> 2) & 0x07;
      i += 2; charcount++;
      // Serial.println("two bits utf-8");
    }
    else if ((code[i] & 0xf0) == 0xe0)
    {

      UNICODEbuffer[charcount * 2 + 1] = (code[i + 1] << 6) + (code[i + 2] & 0x7f);
      UNICODEbuffer[charcount * 2] = (code[i] << 4) + ((code[i + 1] >> 2) & 0x0f);

      //Serial.println("three bits utf-8");
      // Serial.println(UNICODEbuffer[charcount*2],HEX);
      // Serial.println(UNICODEbuffer[charcount*2+1],HEX);
      i += 3; charcount++;
    }
    else
    {
      return 0;
    }
  }
  UNICODEbuffer[charcount * 2] = '\0';
  return charcount;
}
void Duck_EPD::DrawUnicodeChar(int16_t x, int16_t y, byte width, byte height, unsigned char *code)
{

  int offset;
  int sizeofsinglechar;
  if (height % 8 == 0) sizeofsinglechar = (height / 8) * width;
  else sizeofsinglechar = (height / 8 + 1) * width;
  offset = (code[0] * 0x100 + code[1]) * sizeofsinglechar;
  // Serial.println("code[1]");
  // Serial.println(code[1]);
  // Serial.println("sizeofsinglechar");
  // Serial.println(sizeofsinglechar);
  File f = SPIFFS.open(fontname, "r");
  f.seek(offset, SeekSet);
  char zi[sizeofsinglechar];
  f.readBytes(zi, sizeofsinglechar);
  /*for(int i=0;i<32;i++)
    {

    Serial.println(zi[i],HEX);
     }*/
  // Serial.println("offset");
  //Serial.println(offset);
  if (offset < 0xff * sizeofsinglechar && FontIndex < 10)
  {
    drawXbm(x, y, width, height, (unsigned char *)zi);
  }
  else  {
    drawXbm(x, y, width, height, (unsigned char *)zi);
  }

  //SPIFFS.end();
}

void Duck_EPD::DrawUnicodeStr(int16_t x, int16_t y, byte width, byte height, byte strlength, unsigned char *code)
{
  int ymax = yDot;
  ymax = 400;

  CurrentCursor = 0;
  byte sizeofsinglechar;
  if (height % 8 == 0) sizeofsinglechar = (height / 8) * width;
  else sizeofsinglechar = (height / 8 + 1) * width;
  int ymove = 0;
  int xmove = 0;
  strlength *= 2;
  int i = 0;
  while (i < strlength)
  {
    int offset;
    offset = (code[i] * 0x100 + code[i + 1]) * sizeofsinglechar;
    if (offset < 0xff * sizeofsinglechar && fontscale == 1)
    {

      DrawUnicodeChar(x + xmove, y + ymove, width, height, (unsigned char *)code + i);
      ymove += CurrentCursor + 1;
      if ((y + ymove + width / 2) >= ymax - 1) {
        xmove += height + 1;
        ymove = 0;
        CurrentCursor = 0;
      }
    }
    else if (offset < 0xff * sizeofsinglechar && fontscale == 2)
    {
      DrawUnicodeChar(x + xmove, y + ymove, width, height, (unsigned char *)code + i);
      ymove += CurrentCursor + 2;
      if ((y + ymove + width) >= ymax - 1) {
        xmove += height + 1;
        ymove = 0;
        CurrentCursor = 0;
      }
    }
    else if (fontscale == 2)
    {
      DrawUnicodeChar(x + xmove, y + ymove, width, height, (unsigned char *)code + i);
      ymove += width * 2;
      if ((y + ymove + width * 2) >= ymax - 1) {
        xmove += height * 2 + 2;
        ymove = 0;
        CurrentCursor = 0;
      }
    }
    else
    {
      DrawUnicodeChar(x + xmove, y + ymove, width, height, (unsigned char *)code + i);
      ymove += width;
      if ((y + ymove + width) >= ymax - 1) {
        xmove += height + 1;
        ymove = 0;
        CurrentCursor = 0;
      }
    }
    i++; i++;
  }

}
void Duck_EPD::drawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, unsigned char *xbm) {
  int16_t heightInXbm = (height + 7) / 8;
  uint8_t Data;
  for (int16_t x = 0; x < width; x++) {
    for (int16_t y = 0; y < height; y++ ) {
      if (y & 7) {
        Data <<= 1; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = xbm[(y / 8) + x * heightInXbm];
      }
      // if there is a bit draw it
      if (((Data & 0x80) >> 7)) {
        if (fontscale == 1) {
          SetPixel(xMove + y, yMove + x);
          CurrentCursor = x;
        }
        if (fontscale == 2) {
          SetPixel(xMove + y * 2, yMove + x * 2);
          SetPixel(xMove + y * 2 + 1, yMove + x * 2);
          SetPixel(xMove + y * 2, yMove + x * 2 + 1);
          SetPixel(xMove + y * 2 + 1, yMove + x * 2 + 1);
          CurrentCursor = x * 2;
        }
        //if(fontscale==2) {SetPixel(xMove + y*2, yMove + x*2);CurrentCursor=x*2;}
      }
    }
  }
}

void Duck_EPD::DrawXbm_P(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const unsigned char *xbm) {
  int16_t heightInXbm = (height + 7) / 8;
  uint8_t Data;
  //unsigned char temp[heightInXbm*width];
  //memcpy_P(temp, xbm, heightInXbm*width);

  for (int16_t x = 0; x < width; x++) {
    for (int16_t y = 0; y < height; y++ ) {
      if (y & 7) {
        Data <<= 1; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = pgm_read_byte(xbm + (y / 8) + x * heightInXbm);
      }
      // if there is a bit draw it
      if (((Data & 0x80) >> 7)) {
        if (fontscale == 1) {
          SetPixel(xMove + y, yMove + x);
          CurrentCursor = x;
        }
        if (fontscale == 2) {
          SetPixel(xMove + y * 2, yMove + x * 2);
          SetPixel(xMove + y * 2 + 1, yMove + x * 2);
          SetPixel(xMove + y * 2, yMove + x * 2 + 1);
          SetPixel(xMove + y * 2 + 1, yMove + x * 2 + 1);
        }
      }
    }
  }
}
void Duck_EPD::DrawXbm_p_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const unsigned char *xbm, byte level)
{
  int16_t heightInXbm = (height + 1) / 2;
  uint8_t Data;


  for (int16_t x = 0; x < width; x++) {
    for (int16_t y = 0; y < height; y++ ) {
      if (y % 2 != 0) {
        Data <<= 4; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = pgm_read_byte(xbm + (y / 2) + x * heightInXbm);
      }
      // if there is a bit draw it
      if (((Data & 0xf0) >> 4 == level)) {
        SetPixel(xMove + y, yMove + x);
        CurrentCursor = x;
      }
    }
  }

}
void Duck_EPD::DrawXbm_spiff_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, byte level)
{
  File f = SPIFFS.open("/pic.xbm", "r");

  int16_t heightInXbm = (height + 1) / 2;
  uint8_t Data;


  for (int16_t x = 0; x < width; x++) {
    for (int16_t y = 0; y < height; y++ ) {
      if (y % 2 != 0) {
        Data <<= 4; // Move a bit
      } else {  // Read new Data every 8 bit
        Data = ~f.read();
      }
      // if there is a bit draw it
      if (((Data & 0xf0) >> 4 == level)) {
        SetPixel(xMove + y, yMove + x);
        CurrentCursor = x;
      }
    }
  }
  f.close();
}
void Duck_EPD::SetPixel(int16_t x, int16_t y)
{
  int16_t temp = x;
  x = y; y = yDot - 1 - temp;
  if (x < xDot && y < yDot)  EPDbuffer[x / 8 + y * xDot / 8] &= ~(0x80 >> x % 8) ;
}

void Duck_EPD::InversePixel(int16_t x, int16_t y)
{
  int16_t temp = x;
  x = y; y = yDot - 1 - temp;
  if (x < xDot && y < yDot)  EPDbuffer[x / 8 + y * xDot / 8] ^= (0x80 >> x % 8) ;
}
void Duck_EPD::clearbuffer()
{
  for (int i = 0; i < (xDot * yDot / 8); i++) EPDbuffer[i] = 0xff;
}
void Duck_EPD::EPD_Set_Model()
{
  xDot = 400; yDot = 300;
}
unsigned char Duck_EPD::ReadBusy(void)
{
  unsigned long i = 0;
  for (i = 0; i < 100; i++) {
    //	println("isEPD_BUSY = %d\r\n",isEPD_CS);
    if (isEPD_BUSY == EPD_BUSY_LEVEL) {
      //Serial.println("Busy is Low \r\n");
      return 1;
    }
    delay(2);
    //Serial.println("epd is Busy");
  }
  return 0;
}
unsigned char Duck_EPD::ReadBusy_long(void)
{
  unsigned long i = 0;
  for (i = 0; i < 2000; i++) {
    //  println("isEPD_BUSY = %d\r\n",isEPD_CS);
    if (isEPD_BUSY == EPD_BUSY_LEVEL) {
      //Serial.println("Busy is Low \r\n");
      return 1;
    }
    delay(2);
    //Serial.println("epd is Busy");
  }
  return 0;
}
void Duck_EPD::EPD_WriteCMD(unsigned char command)
{
  ReadBusy();
  EPD_CS_0;
  EPD_DC_0;    // command write
  SPI_Write(command);
  EPD_CS_1;
}
void Duck_EPD::EPD_WriteData (unsigned char Data)
{

  EPD_CS_0;
  EPD_DC_1;
  SPI_Write(Data);
  EPD_CS_1;
}

void Duck_EPD::EPD_WriteCMD_p1(unsigned char command, unsigned char para)
{
  ReadBusy();
  EPD_CS_0;
  EPD_DC_0;    // command write
  SPI_Write(command);
  EPD_DC_1;		// command write
  SPI_Write(para);
  EPD_CS_1;
}

void Duck_EPD::deepsleep(void)
{
  ReadBusy_long();
  EPD_WriteCMD_p1(0x10, 0x01);
  //EPD_WriteCMD_p1(0x22,0xc0);//power off
  //EPD_WriteCMD(0x20);
}


void Duck_EPD::EPD_Write(unsigned char *value, unsigned char Datalen)
{

  unsigned char i = 0;
  unsigned char *ptemp;
  ptemp = value;
  ReadBusy();
  EPD_CS_0;
  EPD_DC_0;		// When DC is 0, write command
  SPI_Write(*ptemp);	//The first byte is written with the command value
  ptemp++;
  EPD_DC_1;		// When DC is 1, write Data
  for (i = 0; i < Datalen - 1; i++) {	// sub the Data
    SPI_Write(*ptemp);
    ptemp++;
  }
  EPD_CS_1;
}

void Duck_EPD::EPD_WriteDispRam(unsigned int XSize, unsigned int YSize, unsigned char *Dispbuff, unsigned int offset, byte label)
{

  int i = 0, j = 0;
  ReadBusy();
  EPD_DC_0;    //command write
  EPD_CS_0;
  SPI_Write(0x24);
  EPD_DC_1;		//Data write
  //Serial.printf("Xsize=%dYsize=%d\r\n",XSize,YSize);

  if (label != 1)
  {
    for (i = 0; i < YSize; i++) {
      for (j = 0; j < XSize; j++) {
        SPI_Write(label);

      }
    }

  }
  else
  {
    Dispbuff += offset;
    for (i = 0; i < YSize; i++) {
      for (j = 0; j < XSize; j++) {
        SPI_Write(*Dispbuff);
        Dispbuff++;
      }
      Dispbuff += xDot / 8 - XSize;
    }
  }


  EPD_CS_1;

}

void Duck_EPD::EPD_WriteDispRam_Old(unsigned int XSize, unsigned int YSize, unsigned char *Dispbuff, unsigned int offset, byte label)
{

  int i = 0, j = 0;
  ReadBusy();
  EPD_DC_0;    //command write
  EPD_CS_0;
  SPI_Write(0x26);
  EPD_DC_1;   //Data write
  //Serial.printf("Xsize=%dYsize=%d\r\n",XSize,YSize);

  if (label != 1)
  {
    for (i = 0; i < YSize; i++) {
      for (j = 0; j < XSize; j++) {
        SPI_Write(label);

      }
    }

  }
  else
  {
    Dispbuff += offset;
    for (i = 0; i < YSize; i++) {
      for (j = 0; j < XSize; j++) {
        SPI_Write(*Dispbuff);
        Dispbuff++;
      }
      Dispbuff += xDot / 8 - XSize;
    }
  }


  EPD_CS_1;

}



void Duck_EPD::EPD_SetRamArea(uint16_t Xstart, uint16_t Xend,
                              unsigned char Ystart, unsigned char Ystart1, unsigned char Yend, unsigned char Yend1)
{
  unsigned char RamAreaX[3];	// X start and end
  unsigned char RamAreaY[5]; 	// Y start and end
  RamAreaX[0] = 0x44;	// command
  RamAreaX[1] = Xstart / 8;
  RamAreaX[2] = Xend / 8;
  RamAreaY[0] = 0x45;	// command
  RamAreaY[1] = Ystart;
  RamAreaY[2] = Ystart1;
  RamAreaY[3] = Yend;
  RamAreaY[4] = Yend1;
  EPD_Write(RamAreaX, sizeof(RamAreaX));
  EPD_Write(RamAreaY, sizeof(RamAreaY));
  //Serial.printf("set ram area%d %d %d %d %d %d %d %d %d\n",RamAreaX[0],RamAreaX[1],RamAreaX[2],RamAreaY[0],RamAreaY[1],RamAreaY[2],RamAreaY[3],RamAreaY[4]);
}

void Duck_EPD::EPD_SetRamPointer(uint16_t addrX, unsigned char addrY, unsigned char addrY1)
{
  unsigned char RamPointerX[2];  // default (0,0)
  unsigned char RamPointerY[3];
  //Set RAM X address counter
  RamPointerX[0] = 0x4e;
  RamPointerX[1] = addrX;
  //RamPointerX[1] = 0xff;
  //Set RAM Y address counter
  RamPointerY[0] = 0x4f;
  RamPointerY[1] = addrY;
  RamPointerY[2] = addrY1;
  //RamPointerY[1] = 0x2b;
  //RamPointerY[2] = 0x02;

  EPD_Write(RamPointerX, sizeof(RamPointerX));
  EPD_Write(RamPointerY, sizeof(RamPointerY));
}


void Duck_EPD::EPD_Init(void)
{
  EPD_RST_0;
  driver_delay_xms(5);
  EPD_RST_1;
  //driver_delay_xms(100);

  EPD_WriteCMD(0x74);       //
  EPD_WriteData(0x54);    //
  EPD_WriteCMD(0x7E);       //
  EPD_WriteData(0x3B);    //
  EPD_WriteCMD(0x01);       //
  EPD_WriteData(0x2B);    //
  EPD_WriteData(0x01);
  EPD_WriteData(0x00);    //

  EPD_WriteCMD(0x0C);       //
  EPD_WriteData(0x8B);    //
  EPD_WriteData(0x9C);    //
  EPD_WriteData(0xD6);    //
  EPD_WriteData(0x0F);    //

  EPD_WriteCMD(0x3A);       //
  EPD_WriteData(0x21);    //
  EPD_WriteCMD(0x3B);       //
  EPD_WriteData(0x06);    //
  EPD_WriteCMD(0x3C);       //
  EPD_WriteData(0x03);    //

  EPD_WriteCMD(0x11);       // data enter mode
  EPD_WriteData(0x01);    // 01 –Y decrement, X increment,

  EPD_WriteCMD(0x2C);       //
  EPD_WriteData(0x15);    //fff


  EPD_WriteCMD(0x37);       //
  EPD_WriteData(0x00);    //
  EPD_WriteData(0x00);    //
  EPD_WriteData(0x00);    //
  EPD_WriteData(0x00);    //
  EPD_WriteData(0x80);    //

  EPD_WriteCMD(0x21);       //
  EPD_WriteData(0x40);    //
  EPD_WriteCMD(0x22);
  EPD_WriteData(0xc7);    //c5forgraymode//
}
void Duck_EPD::EPD_Set_Contrast(byte vcom)
{
  EPD_WriteCMD(0x2C);       //
  EPD_WriteData(vcom);    //fff
}

void Duck_EPD::EPD_Update(void)
{
  EPD_WriteCMD(0x20);
}
void Duck_EPD::EPD_Update_Part(void)
{
  EPD_WriteCMD(0x20);
}

void Duck_EPD::EPD_init_Full(void)
{
  EPD_Init();
  EPD_Write((unsigned char *)LUTDefault_full_opm42, sizeof(LUTDefault_full_opm42));
}


void Duck_EPD::EPD_init_Part(void)
{
  EPD_Init();
  EPD_WriteCMD(0x21);
  EPD_WriteData(0x00);
  EPD_Write((unsigned char *)LUTDefault_part_opm42, sizeof(LUTDefault_part_opm42));
}

void Duck_EPD::EPD_Dis_Full(unsigned char *DisBuffer, unsigned char Label)
{
  unsigned int yStart = 0;
  unsigned int yEnd = yDot - 1;
  unsigned int xStart = 0;
  unsigned int xEnd = xDot - 1;
  unsigned long temp = yStart;

  yStart = yDot - 1 - yEnd; yEnd = yDot - 1 - temp;
  EPD_SetRamPointer(xStart / 8, yEnd % 256, yEnd / 256);
  EPD_SetRamArea(xStart, xEnd, yEnd % 256, yEnd / 256, yStart % 256, yStart / 256);

  if (Label == 2) {
    EPD_WriteDispRam(xDot / 8, yDot, (unsigned char *)DisBuffer, 0, 0x00);	// white
  }
  else if (Label == 3)
  {
    EPD_WriteDispRam(xDot / 8, yDot, (unsigned char *)DisBuffer, 0, 0xff); // black
  }
  else {
    EPD_WriteDispRam(xDot / 8, yDot, (unsigned char *)DisBuffer, 0, 1);
  }
  EPD_Update();
  ReadBusy_long();
  EPD_SetRamPointer(xStart / 8, yEnd % 256, yEnd / 256);
  EPD_WriteDispRam(xDot / 8, yDot, (unsigned char *)DisBuffer, 0, 1);
}


void Duck_EPD::EPD_Dis_Part(int xStart, int xEnd, int yStart, int yEnd, unsigned char *DisBuffer, unsigned char Label)
{
  int temp1 = xStart, temp2 = xEnd;
  xStart = yStart; xEnd = yEnd;
  yEnd = yDot - temp1 - 2; yStart = yDot - temp2 - 3;
  unsigned int Xsize = xEnd - xStart;
  unsigned int Ysize = yEnd - yStart + 1;
  if (Xsize % 8 != 0) {
    Xsize = Xsize + (8 - Xsize % 8);
  }
  Xsize = Xsize / 8;
  unsigned int offset = yStart * xDot / 8 + xStart / 8;
  unsigned long temp = yStart;
  yStart = yDot - 1 - yEnd; yEnd = yDot - 1 - temp;

  EPD_SetRamArea(xStart, xEnd, yEnd % 256, yEnd / 256, yStart % 256, yStart / 256);
  EPD_SetRamPointer(xStart / 8, yEnd % 256, yEnd / 256);
  if (Label == 2)  EPD_WriteDispRam(xEnd - xStart, yEnd - yStart + 1, (unsigned char *)DisBuffer, offset, 0x00);
  else if (Label == 3) EPD_WriteDispRam(xEnd - xStart, yEnd - yStart + 1, (unsigned char *)DisBuffer, offset, 0xff);
  else  EPD_WriteDispRam(Xsize, Ysize, (unsigned char *)DisBuffer, offset, 1);
  EPD_Update_Part();
  ReadBusy();
  EPD_WriteDispRam_Old(Xsize, Ysize, (unsigned char *)DisBuffer, offset, 1);
  //ReadBusy();
  //EPD_SetRamArea(xStart,xEnd,yEnd%256,yEnd/256,yStart%256,yStart/256);
  //EPD_SetRamPointer(xStart/8,yEnd%256,yEnd/256);
  //EPD_WriteDispRam(Xsize, Ysize,(unsigned char *)DisBuffer,offset,1);
}
