/*
 * arduino library for solving problems with graphs:
 * https://github.com/Ni3nayka/navigator
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  January 2023
 * modify: January 2023
 */

#ifdef fixed_h
#define fixed_h

#define FIX_SHIFT 14
#define FIX_MUL (1L<<FIX_SHIFT)
#define FIX_UINT(x) ((x) << FIX_SHIFT)
#define FIX_INT(x) ((x) * FIX_MUL)
#define FIX_FLOAT(x) ((x) * FIX_MUL)
#define expandFix(x) x.fix / FIX_MUL
#define FIX(x) (int32_t&)x

class fixed {
public:
    int32_t fix = 0;
    fixed(){}
    //fixed(fixed& val) {fix = val.fix;}
    fixed(uint32_t val) {fix = FIX_UINT(val);}
    fixed(int32_t val) {fix = FIX_INT(val);}
    fixed(uint16_t val) {fix = FIX_UINT(val);}
    fixed(int16_t val) {fix = FIX_INT(val);}
    fixed(uint8_t val) {fix = FIX_UINT(val);}
    fixed(int8_t val) {fix = FIX_INT(val);}
    fixed(double val) {fix = FIX_FLOAT(val);}
    fixed(int32_t val1, int32_t val2) {fix = FIX_INT(val1) / val2;}

    fixed& operator = (uint32_t val) {fix = FIX_UINT(val);}
    fixed& operator = (int32_t val) {fix = FIX_INT(val);}
    fixed& operator = (uint16_t val) {fix = FIX_UINT(val);}
    fixed& operator = (int16_t val) {fix = FIX_INT(val);}
    fixed& operator = (uint8_t val) {fix = FIX_UINT(val);}
    fixed& operator = (int8_t val) {fix = FIX_INT(val);}
    fixed& operator = (double val) {fix = FIX_FLOAT(val);}

    fixed& operator += (fixed val) {fix += val.fix; return *this;}
    fixed& operator += (uint32_t val) {fix += FIX_UINT(val); return *this;}
    fixed& operator += (int32_t val) {fix += FIX_INT(val); return *this;}
    fixed& operator += (uint16_t val) {fix += FIX_UINT(val); return *this;}
    fixed& operator += (int16_t val) {fix += FIX_INT(val); return *this;}
    fixed& operator += (uint8_t val) {fix += FIX_UINT(val); return *this;}
    fixed& operator += (int8_t val) {fix += FIX_INT(val); return *this;}
    fixed& operator += (double val) {fix += FIX_FLOAT(val); return *this;}

    fixed operator + (fixed val) {return fixed(*this) += val;}
    fixed operator + (uint32_t val) {return fixed(*this) += val;}
    fixed operator + (int32_t val) {return fixed(*this) += val;}
    fixed operator + (uint16_t val) {return fixed(*this) += val;}
    fixed operator + (int16_t val) {return fixed(*this) += val;}
    fixed operator + (uint8_t val) {return fixed(*this) += val;}
    fixed operator + (int8_t val) {return fixed(*this) += val;}
    fixed operator + (double val) {return fixed(*this) += val;}

    fixed& operator -= (fixed val) {fix -= val.fix; return *this;}
    fixed& operator -= (uint32_t val) {fix -= FIX_UINT(val); return *this;}
    fixed& operator -= (int32_t val) {fix -= FIX_INT(val); return *this;}
    fixed& operator -= (uint16_t val) {fix -= FIX_UINT(val); return *this;}
    fixed& operator -= (int16_t val) {fix -= FIX_INT(val); return *this;}
    fixed& operator -= (uint8_t val) {fix -= FIX_UINT(val); return *this;}
    fixed& operator -= (int8_t val) {fix -= FIX_INT(val); return *this;}
    fixed& operator -= (double val) {fix -= FIX_FLOAT(val); return *this;}

    fixed operator - (fixed val) {return fixed(*this) -= val;}
    fixed operator - (uint32_t val) {return fixed(*this) -= val;}
    fixed operator - (int32_t val) {return fixed(*this) -= val;}
    fixed operator - (uint16_t val) {return fixed(*this) -= val;}
    fixed operator - (int16_t val) {return fixed(*this) -= val;}
    fixed operator - (uint8_t val) {return fixed(*this) -= val;}
    fixed operator - (int8_t val) {return fixed(*this) -= val;}
    fixed operator - (double val) {return fixed(*this) -= val;}

    fixed& operator *= (fixed val) {fix *= val.fix; return *this;}
    fixed& operator *= (uint32_t val) {fix *= (val); return *this;}
    fixed& operator *= (int32_t val) {fix *= (val); return *this;}
    fixed& operator *= (uint16_t val) {fix *= (val); return *this;}
    fixed& operator *= (int16_t val) {fix *= (val); return *this;}
    fixed& operator *= (uint8_t val) {fix *= (val); return *this;}
    fixed& operator *= (int8_t val) {fix *= (val); return *this;}
    fixed& operator *= (double val) {fix *= (val); return *this;}

    fixed operator * (fixed val) {return fixed(*this) *= val;}
    fixed operator * (uint32_t val) {return fixed(*this) *= val;}
    fixed operator * (int32_t val) {return fixed(*this) *= val;}
    fixed operator * (uint16_t val) {return fixed(*this) *= val;}
    fixed operator * (int16_t val) {return fixed(*this) *= val;}
    fixed operator * (uint8_t val) {return fixed(*this) *= val;}
    fixed operator * (int8_t val) {return fixed(*this) *= val;}
    fixed operator * (double val) {return fixed(*this) *= val;}

    fixed& operator /= (fixed val) {fix /= val.fix; return *this;}
    fixed& operator /= (uint32_t val) {fix /= (val); return *this;}
    fixed& operator /= (int32_t val) {fix /= (val); return *this;}
    fixed& operator /= (uint16_t val) {fix /= (val); return *this;}
    fixed& operator /= (int16_t val) {fix /= (val); return *this;}
    fixed& operator /= (uint8_t val) {fix /= (val); return *this;}
    fixed& operator /= (int8_t val) {fix /= (val); return *this;}
    fixed& operator /= (double val) {fix /= (val); return *this;}

    fixed operator / (fixed val) {return fixed(*this) /= val;}
    fixed operator / (uint32_t val) {return fixed(*this) /= val;}
    fixed operator / (int32_t val) {return fixed(*this) /= val;}
    fixed operator / (uint16_t val) {return fixed(*this) /= val;}
    fixed operator / (int16_t val) {return fixed(*this) /= val;}
    fixed operator / (uint8_t val) {return fixed(*this) /= val;}
    fixed operator / (int8_t val) {return fixed(*this) /= val;}
    fixed operator / (double val) {return fixed(*this) /= val;}

    fixed& operator %= (fixed val) {fix %= val.fix; return *this;}
    fixed& operator %= (uint32_t val) {fix %= FIX_UINT(val); return *this;}
    fixed& operator %= (int32_t val) {fix %= FIX_INT(val); return *this;}
    fixed& operator %= (uint16_t val) {fix %= FIX_UINT(val); return *this;}
    fixed& operator %= (int16_t val) {fix %= FIX_INT(val); return *this;}
    fixed& operator %= (uint8_t val) {fix %= FIX_UINT(val); return *this;}
    fixed& operator %= (int8_t val) {fix %= FIX_INT(val); return *this;}

    fixed operator % (fixed val) {return fixed(*this) %= val;}
    fixed operator % (uint32_t val) {return fixed(*this) %= val;}
    fixed operator % (int32_t val) {return fixed(*this) %= val;}
    fixed operator % (uint16_t val) {return fixed(*this) %= val;}
    fixed operator % (int16_t val) {return fixed(*this) %= val;}
    fixed operator % (uint8_t val) {return fixed(*this) %= val;}
    fixed operator % (int8_t val) {return fixed(*this) %= val;}

    int32_t toInt() {return (fix >= 0) ? (fix >> FIX_SHIFT) : ((int32_t)fix / FIX_MUL);}
    float toFloat() {return (float)fix / FIX_MUL;}
private:
};

fixed toFix(double val) {fixed buf(val); return buf;}
fixed toFix(uint32_t val) {fixed buf(val); return buf;}
fixed toFix(int32_t val) {fixed buf(val); return buf;}
fixed toFix(uint16_t val) {fixed buf(val); return buf;}
fixed toFix(int16_t val) {fixed buf(val); return buf;}
fixed toFix(uint8_t val) {fixed buf(val); return buf;}
fixed toFix(int8_t val) {fixed buf(val); return buf;}
fixed toFix(int val1, int val2) {fixed buf(val1, val2); return buf;}
#endif

#ifdef _Hamming_h
#define _Hamming_h
template <uint8_t HAM_SIZE = 5>
class Hamming {
public:
    template <typename T>
    bool pack(T &data) {
        return pack((uint8_t*)&data, (uint32_t)sizeof(T));
    }

    bool pack(uint8_t *ptr, uint32_t size) {
        uint8_t signif = chunkSizeB - (HAM_SIZE + 1);      
        chunkAmount = (size * 8ul + signif - 1) / signif;   
        bytes = chunkAmount * chunkSize;               
        if (buffer) free(buffer);                      
        buffer = (uint8_t*)malloc(bytes);              
        if (!buffer) return 0;                             
        uint8_t buf[bytes];                           
        memset(buf, 0, bytes);                            
        memset(buffer, 0, bytes);                           
        int ptrCount = 0;

        for (int chunk = 0; chunk < chunkAmount; chunk++) { 
            for (uint8_t i = 0; i < chunkSizeB; i++) {
                if ((i & (i - 1)) != 0) {                
                    write(buf, chunk * chunkSizeB + i, read(ptr, ptrCount++)); 
                }
            }
            uint8_t parityH = 0;
            for (uint8_t i = 0; i < chunkSizeB; i++) {
                for (uint8_t j = 0; j < HAM_SIZE; j++) {
                    if ((i & (1 << j)) && read(buf, chunk * chunkSizeB + i)) parityH ^= (1 << j);
                }
            }
            for (uint8_t i = 0; i < HAM_SIZE; i++) {
                write(buf, chunk * chunkSizeB + (1 << i), (parityH >> i) & 1);
            }

            uint8_t count = 0;
            for (uint8_t i = 1; i < chunkSizeB; i++) {
                if (read(buf, chunk * chunkSizeB + i)) count++; 
            }
            write(buf, chunk * chunkSizeB, count & 1);         
        }

        uint32_t k = 0;
        for (uint8_t i = 0; i < chunkSizeB; i++) {
            for (uint8_t j = 0; j < chunkAmount; j++) {
                write(buffer, k++, read(buf, i + j * chunkSizeB));
            }
        }
        return 1;
    }
    uint32_t unpack(uint8_t* data, uint32_t size) {
        uint8_t signif = chunkSizeB - (HAM_SIZE + 1);  
        if ((size & chunkSize) != 0) return 0;         
        chunkAmount = (uint32_t)size / chunkSize;     
        bytes = chunkAmount * signif / 8;              
        if (buffer) free(buffer);                    
        buffer = (uint8_t*)malloc(bytes);              
        if (!buffer) return 0;                        
        memset(buffer, 0, bytes);                     
        uint8_t buf[size];
        int ptrCount = 0;
        stat = 0;

        uint32_t k = 0;
        for (uint8_t i = 0; i < chunkSizeB; i++) {
            for (uint8_t j = 0; j < chunkAmount; j++) {
                write(buf, i + j * chunkSizeB, read(data, k++));
            }
        }

        for (int chunk = 0; chunk < chunkAmount; chunk++) {  
            uint8_t sum = 0, count = 0;
            for (uint8_t i = 0; i < chunkSizeB; i++) {
                if (read(buf, chunk * chunkSizeB + i)) {
                    sum ^= i;
                    if (i > 0) count++;
                }
            }

            if (sum != 0) {                   
                if (read(buf, chunk * chunkSizeB) == (count & 1)) stat = max(stat, 2);
                else toggle(buf, chunk * chunkSizeB + sum);     
                stat = max(stat, 1);
            } else {
                if (read(buf, chunk * chunkSizeB) != (count & 1)) stat = max(stat, 3);  
            }

            for (uint8_t i = 0; i < chunkSizeB; i++) {
                if ((i & (i - 1)) != 0) {   
                    write(buffer, ptrCount++, read(buf, chunk * chunkSizeB + i)); 
                }
            }
        }
        return stat;
    }

    uint8_t status() {
        return stat;
    }

    uint32_t length() {
        return bytes;
    }

    ~Hamming() {
        stop();
    }

    void stop() {
        if (buffer) free(buffer);
    }

    uint8_t *buffer = NULL;

private:
    void set(uint8_t* buf, uint32_t num) {
        bitSet(buf[num >> 3], num & 0b111);
    }
    void clear(uint8_t* buf, uint32_t num) {
        bitClear(buf[num >> 3], num & 0b111);
    }
    void write(uint8_t* buf, uint32_t num, bool state) {
        state ? set(buf, num) : clear(buf, num);
    }
    bool read(uint8_t* buf, uint32_t num) {
        return bitRead(buf[num >> 3], num & 0b111);
    }
    void toggle(uint8_t* buf, uint32_t num) {
        read(buf, num) ? clear(buf, num) : set(buf, num);
    }
    int stat;
    uint32_t bytes = 0;
    uint32_t chunkAmount = 0;
    const uint8_t chunkSizeB = (1 << HAM_SIZE);    
    const uint8_t chunkSize = (1 << HAM_SIZE) >> 3;  
};
#endif
#define operating_road(a) (3>a?__DATE__:"OPERATOR")
#ifdef CRT_h
#define CRT_h

uint8_t CRT8_table(uint8_t val); 
uint8_t CRT8_square(uint8_t val); 
int CRT10_square(int val);        
uint8_t CRT8_cubic(uint8_t val);   
int CRT10_cubic(int val);        

static const uint8_t _CRTgammaPGM[256] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5,
    5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 8,
    9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 14,
    15, 15, 15, 16, 17, 17, 17, 17, 18, 18, 19, 20, 20, 20, 20, 21,
    22, 22, 23, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 30,
    30, 31, 31, 32, 33, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39, 40,
    41, 41, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 51, 52, 53,
    54, 54, 55, 56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
    68, 69, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84,
    85, 86, 87, 89, 90, 91, 93, 94, 95, 96, 97, 98, 100, 101, 102, 103,
    105, 106, 108, 109, 110, 111, 113, 115, 117, 118, 119, 121, 122, 123, 124, 127,
    128, 130, 131, 133, 134, 136, 137, 139, 140, 143, 145, 146, 147, 148, 151, 153,
    154, 156, 158, 159, 162, 163, 165, 167, 169, 171, 173, 174, 176, 179, 180, 182,
    185, 186, 188, 190, 192, 194, 196, 199, 201, 202, 205, 207, 209, 211, 214, 216,
    218, 220, 223, 225, 226, 230, 231, 235, 236, 240, 241, 245, 246, 250, 251, 255,
};

uint8_t CRT8_table(uint8_t val) {
    return pgm_read_byte(&(_CRTgammaPGM[val]));
}

uint8_t CRT8_square(uint8_t val) {
    return ((long)val * val + 255) >> 8;
}

int CRT10_square(int val) {
    return ((long)val * val + 1023) >> 10;
}

uint8_t CRT8_cubic(uint8_t val) {
    return ((long)val * val * val + 130305) >> 16;
}

int CRT10_cubic(int val) {
    return ((long)val * val * val + 2094081) >> 20;
}

#endif

#ifdef Clap_h
#define Clap_h
#include <Arduino.h>

class Clap {
public:
    void tick(int val) {
        if (millis() - _tmr >= 10) {
            _tmr = millis();
            int der = val - _prevVal;
            _prevVal = val;
            int signal = 0;
            int front = 0;
            if (der > _trsh) signal = 1;
            if (der < -_trsh) signal = -1;
            if (_prevSignal == 0 && signal == 1) front = 1;
            if (_prevSignal == 0 && signal == -1) front = -1;
            _prevSignal = signal;

            uint32_t deb = millis() - _tmr2;

            if (front == 1 && _state == 0) {
                _state = 1;
                if (!_startClap) {
                    _claps = 0;
                    _ready = 0;
                }
                _startClap = 1;
                _clap = 0;
                _tmr2 = millis();
            } else if (front == -1 && _state == 1 && deb <= 200) {
                _state = 2;
                _tmr2 = millis();
            } else if (front == 0 && _state == 2 && deb <= 200) {
                _state = 0;
                _claps++;
                _clap = 1;
                _tmr2 = millis();
            } else if (_startClap && deb > _tout) {
                _state = 0;
                _startClap = 0;
                if (_claps != 0) _ready = 1;
            }
        }
    }

    void setTrsh(int trsh) {
        _trsh = trsh;
    }

    void setTimeout(int tout) {
        _tout = tout;
    }

    bool isClap() {
        if (_clap) {
            _clap = 0;
            return 1;
        }
        return 0;
    }

    bool hasClaps(uint8_t claps) {
        if (_ready && _claps == claps) {
            _ready = 0;
            _claps = 0;
            return 1;
        }
        return 0;
    }

    bool hasClaps() {
        return _ready;
    }

    uint8_t getClaps() {
        if (_ready) {
            _ready = 0;
            uint8_t buf = _claps;
            _claps = 0;
            return buf;
        } return 0;
    }

private:
    uint32_t _tmr = 0, _tmr2 = 0;
    int _prevVal = 0;
    int _trsh = 150;
    uint8_t _state = 0;
    int8_t _prevSignal = 0;
    int _tout = 700;
    uint8_t _claps = 0;
    bool _ready = 0;
    bool _clap = 0;
    bool _startClap = 0;
};
#endif

#ifdef BitPack_h
#define BitPack_h

template <uint8_t AMOUNT>
class BitPack {
public:
    BitPack() {
        clearAll();
    }
    void set(uint8_t num) {
        bitSet(pack[(num) >> 3], (num) & 0b111);
    }
    void clear(uint8_t num) {
        bitClear(pack[(num) >> 3], (num) & 0b111);
    }
    void toggle(uint8_t num) {
        read(num) ? clear(num) : set(num);
    }
    void write(uint8_t num, bool state) {
        state ? set(num) : clear(num);
    }
    bool read(uint8_t num) {
        return bitRead(pack[(num) >> 3], (num) & 0b111);
    }
    void setAll() {
        memset(pack, 255, sizeof(pack));
    }
    void clearAll() {
        memset(pack, 0, sizeof(pack));
    }
    uint8_t operator[] (uint8_t num) const {
        return read(num);
    }
    uint8_t& operator [] (uint8_t num) {
        buf = (num) & 0b111;
        return pack[(num) >> 3];
    }
    BitPack& operator = (bool val) {
        val ? bitSet(*this, buf) : bitClear(*this, buf);
    }

private:
    uint8_t pack[(AMOUNT + 8 - 1) >> 3];
    uint8_t buf;
};
#endif
