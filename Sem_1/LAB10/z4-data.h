#include <_mingw.h>

struct num8 {
    __int8 a;
    __int8 b;
};

union num16 {
    struct num8 st8;
    __int16 i16;
};