#define WiFi_Logo_width 60
#define WiFi_Logo_height 36
const char WiFi_Logo_bits[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
    0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
    0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
    0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
    0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
    0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
    0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
    0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
    0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
    0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
    0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
    0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
    0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
    0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const char emptySymbol[] PROGMEM = {B00000000, B00000000, B00000000, B00000000,
                                    B00000000, B00000000, B00000000, B00000000};

const char activeSymbol[] PROGMEM = {B00000000, B00000000, B00011000,
                                     B00100100, B01000010, B01000010,
                                     B00100100, B00011000};

const char inactiveSymbol[] PROGMEM = {B00000000, B00000000, B00000000,
                                       B00000000, B00011000, B00011000,
                                       B00000000, B00000000};

#define temp_icon_width 32
#define temp_icon_height 32
const char temp_icon_bits[] PROGMEM = {
    0x00, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xE1, 0x07, 0x80, 0xFF, 0xF3, 0x0F,
    0xC0, 0xC3, 0xF3, 0x0F, 0xC0, 0x83, 0x03, 0x00, 0xC0, 0x81, 0x07, 0x00,
    0xC0, 0x01, 0xF7, 0x0F, 0xC0, 0x01, 0xF7, 0x0F, 0xC0, 0x01, 0xF7, 0x0F,
    0xC0, 0x01, 0x07, 0x00, 0xC0, 0x01, 0x07, 0x00, 0xC0, 0x01, 0xF7, 0x0F,
    0xC0, 0x01, 0xF7, 0x0F, 0xC0, 0x01, 0xF7, 0x0F, 0xC0, 0x39, 0x07, 0x00,
    0xC0, 0x3D, 0x07, 0x00, 0xC0, 0x7D, 0xF7, 0x0F, 0xC0, 0x7D, 0xF7, 0x0F,
    0xC0, 0x7D, 0xF7, 0x0F, 0xE0, 0x7D, 0x07, 0x00, 0xE0, 0x7D, 0x0F, 0x00,
    0xF0, 0xFE, 0x0F, 0x00, 0xF0, 0xFE, 0x0E, 0x00, 0x70, 0xFF, 0x1E, 0x00,
    0x70, 0xFF, 0x1E, 0x00, 0x70, 0xFF, 0x0E, 0x00, 0xF0, 0xFE, 0x0E, 0x00,
    0xE0, 0x7D, 0x0F, 0x00, 0xE0, 0x83, 0x07, 0x00, 0xC0, 0xFF, 0x07, 0x00,
    0x80, 0xFF, 0x03, 0x00, 0x00, 0xFF, 0x00, 0x00,
};

#define humidity_width 32
#define humidity_height 32
const char humidity_bits[] PROGMEM = {
    0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0xE0, 0x00, 0xE0, 0x03,
    0xF0, 0x00, 0xE0, 0x07, 0xF0, 0x01, 0xE0, 0x07, 0xF0, 0x01, 0xF0, 0x07,
    0xF8, 0x03, 0xF0, 0x0F, 0xF8, 0x03, 0xF0, 0x0F, 0xF8, 0x03, 0x78, 0x0F,
    0xFC, 0x07, 0x78, 0x1E, 0xBC, 0x07, 0x78, 0x1E, 0xBC, 0x07, 0x3C, 0x3E,
    0xFC, 0x07, 0x3C, 0x3C, 0xFC, 0x07, 0x3C, 0x3C, 0xF8, 0x73, 0x1C, 0x3C,
    0xF0, 0xF1, 0x1C, 0x3C, 0x00, 0xF8, 0x3C, 0x3C, 0x00, 0xF8, 0xFC, 0x3F,
    0x00, 0xF8, 0xF9, 0x1F, 0x00, 0xFC, 0xF1, 0x0F, 0x00, 0xFC, 0xE1, 0x07,
    0x00, 0xFC, 0x03, 0x00, 0x00, 0xDE, 0x03, 0x00, 0x00, 0xDE, 0x07, 0x00,
    0x00, 0x9E, 0x07, 0x00, 0x00, 0x8F, 0x07, 0x00, 0x00, 0x0F, 0x07, 0x00,
    0x00, 0x8F, 0x07, 0x00, 0x00, 0x9F, 0x07, 0x00, 0x00, 0xFE, 0x07, 0x00,
    0x00, 0xFE, 0x03, 0x00, 0x00, 0xF8, 0x01, 0x00,
};

#define pressure_width 32
#define pressure_height 32
const char pressure_bits[] PROGMEM = {
    0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0xFE, 0x03, 0x00, 0x00, 0xDF, 0x07,
    0x00, 0x00, 0x07, 0x07, 0x00, 0x80, 0x03, 0x3E, 0x00, 0xC0, 0x03, 0x7C,
    0x00, 0xF0, 0x01, 0xE0, 0x00, 0x70, 0x00, 0xC0, 0x00, 0x38, 0x00, 0xC0,
    0x00, 0x38, 0x00, 0xC0, 0x00, 0x38, 0x00, 0xC0, 0x00, 0x38, 0x00, 0xE0,
    0x00, 0xF0, 0xFF, 0x7F, 0x00, 0xE0, 0xFF, 0x3F, 0x00, 0x80, 0xFF, 0x0F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x03, 0x00,
    0xFF, 0xFF, 0x07, 0x00, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x80, 0x03, 0x00,
    0x00, 0x80, 0x31, 0x00, 0x00, 0x00, 0x70, 0x00, 0xF0, 0xFF, 0xFF, 0x00,
    0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x30, 0x0E,
    0x00, 0x00, 0x00, 0x1E, 0x00, 0xFC, 0xFF, 0x1F, 0x00, 0xFC, 0xFF, 0x1F,
    0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x04,
};
