#The RSON data format

##Grammar

```
VALUE :=   "\x00"                                        // null
                | "\x01" BYTE                                // bool
                | "\x02" BYTE                                // int8
                | "\x03" BYTE*2                            // int16
                | "\x04" BYTE*4                            // int32
                | "\x05" BYTE*8                            // int64
                | "\x06" BYTE                                // uint8
                | "\x07" BYTE*2                            // uint16
                | "\x08" BYTE*4                            // uint32
                | "\x09" BYTE*8                            // uint64
                | "\x0A" BYTE*8                            // double
                | "\x0B" STRING                            // string
                | "\x0C" STRING                            // binary 
                | "\x0D" OBJECT                            // object
                | "\x0E" LEN LIST<VALUE>          // array of values
                | "\x0F" LEN LIST<BYTE>             // array of bools
                | "\x10" LEN LIST<BYTE>             // array of int8
                | "\x11" LEN LIST<BYTE>             // array of uint8
                | "\x12" LEN LIST<BYTE*2>         // array of int16
                | "\x13" LEN LIST<BYTE*2>         // array of uint16
                | "\x14" LEN LIST<BYTE*4>         // array of int32
                | "\x15" LEN LIST<BYTE*4>         // array of uint32
                | "\x16" LEN LIST<BYTE*8>         // array of int64
                | "\x17" LEN LIST<BYTE*8>         // array of uint64
                | "\x18" LEN LIST<BYTE*8>         // array of double
                | "\x19" LEN LIST<STRING>         // array of string
                | "\x1A" LEN LIST<STRING>         // array of binary
                | "\x1B" LEN LIST<OBJECT>         // array of object

STRING := LEN LIST<BYTE>

OBJECT := LEN KEY_VALUE_LIST

KEY_VALUE_LIST :=  CSTRING VALUE KEY_VALUE_LIST
                                | ""

CSTRING := BYTE* "\00"

LIST<T> := T LIST<T>
                  | ""

LEN := BYTE*4 // The length in bytes, which is needed to complete the current value
```