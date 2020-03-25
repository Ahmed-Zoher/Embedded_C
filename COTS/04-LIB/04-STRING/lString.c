#include "STD_TYPES.h"
#include "lString.h"


u8 String_Compare (u8* str1, u8* str2){
    u8 compare_output = 0;
    if (String_getLength(str1) == String_getLength(str2)){
      u8* ptr1 = str1;
      u8* ptr2 = str2;
      for (u8 i=0 ; *ptr1 != '\0' ; i++){
        if (*ptr1 ==  *ptr2)
            compare_output = 1;
        else 
          {compare_output = 0; break;}
        ptr1++;
        ptr2++;
      }

    }
    return compare_output;
}


u8 String_getLength (u8* str){
    u8* ptr_char = str;
    u8 length = 0;
    while (*ptr_char != '\0'){
        ptr_char++;
        length++;
    }
    return length;
}
