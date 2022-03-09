#pragma once

#define ARRAY_COUNT(Array) (sizeof(Array) / sizeof((Array)[0]))

#define IS_NUMBER(String) ((*(String)) >= '0' && (*(String)) <= '9')

#define GET_ELEMENT(Struct, Element) ((unsigned long long)(&(((Struct*)(0))->Element)))

#define INSERT_INLINECODE_8_BIT_ARRAY(Code, ...) ((unsigned char)((Code) << 8)) | __VA_ARGS__
#define INSERT_INLINECODE_16_BIT_ARRAY(Code, ...) ((unsigned short)((Code) << 16)) | __VA_ARGS__
#define INSERT_INLINECODE_32_BIT_ARRAY(Code, ...) ((unsigned long)((Code) << 32)) | __VA_ARGS__
#define INSERT_INLINECODE_64_BIT_ARRAY(Code, ...) ((unsigned __int64)((Code) << 64)) | __VA_ARGS__