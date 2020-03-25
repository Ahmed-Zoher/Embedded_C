#include <stdio.h>

char String_getLength (char* str){
    char* ptr_char = str;
    char length = 0;
    while (*ptr_char != '\0'){
        ptr_char++;
        length++;
    }
    return length;
}


char String_Compare (char* str1, char* str2){
    char compare_output = 0;
    if (String_getLength(str1) == String_getLength(str2)){
      char* ptr1 = str1;
      char* ptr2 = str2;
      for (char i=0 ; *ptr1 != '\0' ; i++){
        if (*ptr1 ==  *ptr2)
            compare_output = 1;
        else 
          {compare_output = 0; break;}
       *ptr1++;
       *ptr2++;
      }
    }
    return compare_output;
}


int main (){
printf("%d",String_Compare("waled","waled"));
return 0;
}