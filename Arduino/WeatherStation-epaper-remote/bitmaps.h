//体感温度
const unsigned char PROGMEM fl[24] = {/* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XC0, 0XFF, 0X20, 0X80, 0X10, 0XAA, 0X10, 0XFF, 0X20,
  0X00, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
};
//风向
const unsigned char PROGMEM dir[24] = { /* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X0F, 0X00, 0X30, 0XC0, 0X40, 0X20, 0X4C, 0X20, 0X9C, 0X10, 0XBF, 0XD0, 0XBF, 0XD0, 0X9C, 0X10,
  0X4C, 0X20, 0X40, 0X20, 0X30, 0XC0, 0X0F, 0X00,
};
//风力
const unsigned char PROGMEM sc[24] = {/* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XF0, 0XFE, 0X00, 0X7C, 0X00, 0X7C, 0X00, 0X38, 0X00,
  0X10, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
};
//降水量
const unsigned char PROGMEM pcpn[24] = {/* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X03, 0X00, 0X0F, 0XC0, 0X38, 0X60, 0X60, 0X20, 0XC0, 0X30, 0X80, 0X10, 0X8C, 0XD0, 0X47, 0XB0,
  0X60, 0X20, 0X38, 0X60, 0X0F, 0XC0, 0X03, 0X00,
};
//能见度
const unsigned char PROGMEM vis[24] = {/* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X04, 0X00, 0X1B, 0X00, 0X11, 0X00, 0X20, 0X80, 0X2E, 0X80, 0X2A, 0X80, 0X2A, 0X80, 0X2E, 0X80,
  0X20, 0X80, 0X11, 0X00, 0X1B, 0X00, 0X04, 0X00,
};
//气压
const unsigned char PROGMEM pres[24] = { /* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X06, 0X00, 0X0E, 0X00, 0X1C, 0X00, 0X38, 0X00, 0X30, 0X00, 0X70, 0XC0, 0X71, 0XC0, 0X72, 0X00,
  0X34, 0X00, 0X38, 0X00, 0X1C, 0X00, 0X2E, 0X00,
};

const unsigned char PROGMEM city_icon[24] = { /* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X00, 0X00, 0X1C, 0X00, 0X77, 0X00, 0X41, 0X80, 0X9C, 0X60, 0XA2, 0X30, 0XA2, 0X30, 0X9C, 0XC0,
  0X41, 0X80, 0X77, 0X00, 0X1C, 0X00, 0X00, 0X00,
};

const unsigned char PROGMEM batt_5[]  = { /* 0X01,0X01,0X14,0X00,0X10,0X00, */
  0X1E, 0X00, 0XFF, 0XC0, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40,
  0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40,
  0XBF, 0X40, 0X80, 0X40, 0XFF, 0XC0, 0X00, 0X00,
};
const unsigned char PROGMEM batt_4[] = { /* 0X01,0X01,0X14,0X00,0X0A,0X00, */
  0X1E, 0X00, 0XFF, 0XC0, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40,
  0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40,
  0XBF, 0X40, 0X80, 0X40, 0XFF, 0XC0, 0X00, 0X00,
};
const unsigned char PROGMEM batt_3[] = { /* 0X01,0X01,0X14,0X00,0X0A,0X00, */
  0X1E, 0X00, 0XFF, 0XC0, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40,
  0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40,
  0XBF, 0X40, 0X80, 0X40, 0XFF, 0XC0, 0X00, 0X00,
};
const unsigned char PROGMEM batt_2[] = { /* 0X01,0X01,0X14,0X00,0X0A,0X00, */
  0X1E, 0X00, 0XFF, 0XC0, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40,
  0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0XBF, 0X40, 0XBF, 0X40, 0X80, 0X40, 0XBF, 0X40,
  0XBF, 0X40, 0X80, 0X40, 0XFF, 0XC0, 0X00, 0X00,
};
const unsigned char PROGMEM batt_1[] = { /* 0X01,0X01,0X14,0X00,0X0A,0X00, */
  0X1E, 0X00, 0XFF, 0XC0, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40,
  0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0XBF, 0X40,
  0XBF, 0X40, 0X80, 0X40, 0XFF, 0XC0, 0X00, 0X00,
};
const unsigned char PROGMEM batt_0[] = { /* 0X01,0X01,0X14,0X00,0X0A,0X00, */
  0X1E, 0X00, 0XFF, 0XC0, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40,
  0X80, 0X40, 0XBD, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40, 0X80, 0X40,
  0X80, 0X40, 0X80, 0X40, 0XFF, 0XC0, 0X00, 0X00,
};

const unsigned char PROGMEM message[24] = { /* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
  0X00, 0X00, 0X1F, 0X80, 0X00, 0X00, 0X1F, 0X80, 0X3F, 0XC0, 0X7F, 0XE0, 0X00, 0X00, 0X10, 0X80,
  0X4F, 0X20, 0X20, 0X40, 0X1F, 0X80, 0X00, 0X00,
};

const unsigned char PROGMEM phone[] = { /* 0X01,0X01,0X46,0X00,0X74,0X00, */
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X07,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X1F, 0XFF,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X80, 0X3C, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0XC0, 0X70, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XE0, 0X60, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X60, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X70, 0XC0, 0X1F, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X80, 0X30, 0XC0, 0X3F, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X80, 0X30, 0XC0, 0X30, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02, 0X00, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X01, 0X8E, 0X30, 0XC0, 0X33, 0X02, 0X01, 0X20, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X01, 0X88, 0X30, 0XC0, 0X30, 0XE2, 0X02, 0X40, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X01, 0X8A, 0X30, 0XC0, 0X30, 0X1A, 0X02, 0X88, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X8A, 0X30, 0XC0, 0X30, 0XE2, 0X04, 0X90, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X88,
  0X30, 0XC0, 0X33, 0X02, 0X04, 0X92, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X8E, 0X30,
  0XC0, 0X30, 0XE2, 0X04, 0X90, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0,
  0X30, 0X1A, 0X02, 0X88, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30,
  0XE2, 0X02, 0X40, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X33, 0X02,
  0X01, 0X20, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02, 0X00,
  0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X33, 0XFA, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02, 0X18, 0X0C, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X33, 0XFA, 0X07, 0X03, 0X80, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC4, 0X32, 0X42, 0X1E, 0X0F, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC4, 0X32, 0X42, 0X07, 0X03, 0X80, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X01, 0X80, 0X30, 0XC4, 0X32, 0X42, 0X18, 0X0C, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X01, 0X80, 0X30, 0XC4, 0X30, 0X02, 0X0E, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X01, 0X80, 0X30, 0XC4, 0X30, 0X02, 0X15, 0X08, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X8C, 0X30, 0XC4, 0X33, 0XFA, 0X15, 0X2F, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X92,
  0X30, 0XC4, 0X30, 0X02, 0X0D, 0X00, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30,
  0XC4, 0X30, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4,
  0X30, 0X02, 0X0B, 0X07, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30,
  0X02, 0X15, 0X08, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30, 0X02,
  0X15, 0X28, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30, 0X02, 0X1F,
  0X3F, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30, 0X02, 0X01, 0X00,
  0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30, 0X02, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30, 0X02, 0X10, 0X0F, 0XC0, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XA1, 0X30, 0XC4, 0X30, 0X02, 0X7F, 0X0D, 0X40, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X01, 0X92, 0X30, 0XC4, 0X30, 0X02, 0X11, 0X0C, 0XC0, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X01, 0X8C, 0X30, 0XC4, 0X30, 0X02, 0X00, 0X08, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X01, 0X80, 0X30, 0XC4, 0X30, 0X02, 0X41, 0X07, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X01, 0X80, 0X30, 0XC4, 0X30, 0X02, 0X7F, 0X0A, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X01, 0X80, 0X30, 0XC4, 0X30, 0X02, 0X11, 0X0A, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X80, 0X30, 0XC0, 0X30, 0X02, 0X1F, 0X06, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80,
  0X30, 0XC0, 0X30, 0X02, 0X01, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30,
  0XC0, 0X30, 0X02, 0X0E, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0,
  0X30, 0X02, 0X15, 0X08, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30,
  0X02, 0X15, 0X3F, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02,
  0X0D, 0X08, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X02, 0X11, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X89, 0X30, 0XC0, 0X30, 0X02, 0X1F, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X9D, 0X30, 0XC0, 0X30, 0X02, 0X11, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X89, 0X30, 0XC0, 0X30, 0X02, 0X10, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X01, 0X89, 0X30, 0XC0, 0X30, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X01, 0X8F, 0X30, 0XC0, 0X30, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X01, 0X80, 0X30, 0XC6, 0X30, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X01, 0X80, 0X30, 0XC0, 0X30, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X01, 0X80, 0X30, 0XC0, 0X30, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X80, 0X30, 0XC0, 0X3F, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X80,
  0X30, 0XC0, 0X1F, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X80, 0X30,
  0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X70, 0X60,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X60, 0X70, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XE0, 0X3C, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0XC0, 0X1F, 0XFF, 0XFF, 0XFF,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X80, 0X07, 0XFF, 0XFF, 0XFF, 0XFF,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFE, 0X00,
};
