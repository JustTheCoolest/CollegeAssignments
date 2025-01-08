#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Critical: Bug in differentiating between the dereference operator and the multiplication operator.
// Can be implemented by having a state variable for the states: Start of Expression, Mid Expression, Not An Expression

/*
Not Implemented:
- Multiline comments
- Preprocessor directives other than #include (#define, etc.)
- Keyword list is probably incomplete
- Differentiating between < and <= and so on
- Validation of identifier and value for #define, and validation of module name for #include
- Validation of end of line for preprocessor directives
- A comprehensive not-implemented list is not implemented
- For unambigious tokens such as +=, unexpected occurences are not checked
*/

/*
Rewrite Suggestions:
- Increment the text variable itself, instead of the separate int *i
*/

/*
Mistakes:
- Operators and keywords must be labelled as an the category when tokenising.
*/

int streaming_strcmp(char *ar1, char *ar2, int len){
  for(int i=0; i<len; ++i){
    if(ar1[i] < ar2[i]){
      return -1;
    }
    else if(ar1[i] > ar2[i]){
      return 1;
    }
  }
  return 0;
}

void error(int i){
  printf("Compilation error at chracter %i\n", i);
  exit(1);
}

int isIndentifierChar(char c){
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c=='_';
}

int isEscapable(char c){
  return (c=='n' || c=='0' || c=='\"' || c=='\'' || c=='t');
}

// Flag: Refactor this func and the doubleCharOperators handler
void iteratePostIdentifier(int *i, char *text){
  while(text[*i]==' ') ++*i;
  char *ambiguousOperators[] = {"*=x", "/=x"};
  for(int j=0; j<sizeof(ambiguousOperators)/sizeof(char*); ++j){
    if(text[*i] != ambiguousOperators[j][0]){
      continue;
    }
    ++*i;
    char next = text[*i];
    char *iterator = ambiguousOperators[j];
    while(*iterator != 'x' && *iterator != '\0'){
      if(*iterator == next){
        printf("%c%c\n", ambiguousOperators[j][0], next);
        ++*i;
        return;
      }
      ++iterator;
    }
    if(*iterator=='x'){
      printf("%c\n", ambiguousOperators[j][0]);
      return;
    }
    error(*i);
  }
}

void iterate(int *i, char curr, char *text){
  int initial = *i;
  switch(curr){
    case '\0':
    printf("End of compilation, yay!\n");
    ++*i;
    return;

    case ' ':
    case '\n':
    case '\t': {
      ++*i;
      return;
    }

    case '/': {
      if(text[*i+1]=='/'){
        printf("comment ");
        *i += 2;
        while(text[*i] != '\n'){
          printf("%c", text[*i]);
          ++*i;
        }
        // does not handle the newline character at the end, for code simplicity
        printf("\n");
        return;
      }
      else{
        error(*i);
      }
    }

    // case '+':
    // case '-':
    // case '=': {
    //   char character = curr;
    //   if(text[*i+1]==character){
    //     printf("%c%c\n", character, character);
    //     *i += 2;
    //     return;
    //   }
    //   else{
    //     printf("%c\n", character);
    //     ++*i;
    //     return;
    //   }
    // }

    case '"': {
      printf("string ");
      char end = curr;
      ++*i;
      while(text[*i] != end){
        if(text[*i] == '\\'){
          ++*i;
          if(!isEscapable(text[*i])){
            error(*i);
          }
          // Flag: Printing does not differentiate if this exact pharse exists in the string.
          printf("<escape_sequence:%c%c>", text[*i-1], text[*i]);
          ++*i;
          continue;
        }
        printf("%c", text[*i]);
        ++*i;
      }
      ++*i;
      printf("\n");
      return;
    }

    case '\'': {
      // Flag: Refactor the common code with the string case into a common function
      printf("character ");
      ++*i;
      if(text[*i] == '\\'){
        ++*i;
        if(!isEscapable(text[*i])){
          error(*i);
        }
        // Flag: Printing does not differentiate if this exact pharse exists in the string.
        printf("<escape_sequence:%c%c>", text[*i-1], text[*i]);
      }
      else{
        printf("%c", text[*i+1]);
      }
      printf("\n");
      ++*i;
      if(text[*i] != '\''){
        error(*i);
      }
      ++*i;
      return;
    }

    case '#': {
      if(streaming_strcmp(text+*i, "#include", 8)==0){
        *i += 8;
        printf("preprocessor_directive #include\n");
        while(text[*i]==' ') ++*i;
        char end;
        if(text[*i]=='<'){
          printf("builtin_module <");
          end = '>';
        }
        else if(text[*i]=='"'){
          printf("relative_module \"");
          end = '"';
        }
        else{
          error(*i);
        }
        while(text[*i] != end){
          ++*i;
          printf("%c", text[*i]);
        }
        ++*i;
        printf("\n");
      }
      
      else if(streaming_strcmp(text+*i, "#define", 7)==0){
        *i += 7;
        printf("preprocessor_directive #define\n");
        while(text[*i]==' ') ++*i;
        printf("#define_identifier ");
        while(text[*i] != ' '){
          printf("%c", text[*i]);
          ++*i;
        }
        printf("\n");
        while(text[*i]==' ') ++*i;
        printf("#define_value ");
        while(text[*i] != '\n'){
          printf("%c", text[*i]);
          ++*i;
        }
        ++*i;
        printf("\n");
      }

      else{
        error(*i);
      }

      return;
    }

    case '*': {
      printf("dereference_operator\n");
      ++*i;
      return;
    }

    default: {
      // Flag: Implement as char array instead of string array
      char *punctuations[] = {"{", "}", "(", ")", "[", "]", ";", ",", "."};
      for(int j=0; j<sizeof(punctuations)/sizeof(punctuations[0]); ++j){
        if(curr == punctuations[j][0]){
          printf("%s\n", punctuations[j]);
          ++*i;
          return;
        }
      }

      // printf("Checking double char...\n");
      // printf("%c ", curr);

      char *doubleCharOperators[] = {"==x", "++=x", "--=x", "<=x", ">=x", "!=x", "&&x", "||x"};
      for(int j=0; j<sizeof(doubleCharOperators)/sizeof(char*); ++j){
        if(curr != doubleCharOperators[j][0]){
          // printf("%c", doubleCharOperators[j][0]);
          continue;
        }
        ++*i;
        char next = text[*i];
        char *iterator = doubleCharOperators[j];
        while(*iterator != 'x' && *iterator != '\0'){
          if(*iterator == next){
            printf("%c%c\n", curr, next);
            ++*i;
            return;
          }
          ++iterator;
        }
        if(*iterator=='x'){
          printf("%c\n", curr);
          return;
        }
        error(*i);
      } 

      // printf("\n... Checked double char\n");

      char *keywords[] = {"char", "int", "float", "for", "while", "void", "return", "sizeof"};
      for(int j=0; j<sizeof(keywords)/sizeof(keywords[0]); ++j){
        if(streaming_strcmp(text+*i, keywords[j], strlen(keywords[j]))==0){
          printf("keyword ");
          *i += strlen(keywords[j]);
          printf("%s\n", keywords[j]);
          return;
        }
      }

      if(curr >= '0' && curr <= '9'){
        printf("number ");
        int flag = 0;
        while(text[*i] >= '0' && text[*i] <= '9' || (text[*i]=='.') && flag==0){
          if(text[*i]=='.'){
            flag = 1;
          }
          printf("%c", text[*i]);
          ++*i;
        }
        printf("\n");
        return;
      }

      if(isIndentifierChar(curr)){
        printf("identifier ");
        while(isIndentifierChar(text[*i])){
          printf("%c", text[*i]);
          ++*i;
        }
        printf("\n");
        iteratePostIdentifier(i, text);
        return;
      }

      error(*i);
    }
  }
}

void lex(char* text){
    int i=0;
    char curr = 'a';
    while(curr != '\0'){
        curr = text[i];
        iterate(&i, curr, text);
    }
}

int main(){
    // char name[] = "src1.cpp";
    // char text[] = getText(name); 
    // Flag: Implement File Handling
    // Flag: Optimality would be to traverse this char by char without loading fully
    printf("Q1:\n");
    char text1[] = "\
    // Program to check for a palindrome string by reversing\n\
    // the string\n\
    #include <stdio.h>\n\
    #include <string.h>\n\
    #include <stdbool.h>\n\
    #include <stdlib.h>\n\
    \n\
    char *strrev(char *str) {\n\
        int len = strlen(str);\n\
    \n\
        // Temporary char array to store the\n\
        // reversed string\n\
        char *rev = (char *)malloc(sizeof(char) * (len + 1));\n\
    \n\
        // Reversing the string\n\
        for (int i = 0; i < len; i++) {\n\
            rev[i] = str[len - i - 1];\n\
        }\n\
        rev[len] = '\\0';\n\
        return rev;\n\
    }\n\
    \n\
    void isPalindrome(char *str) {\n\
        // Reversing the string\n\
        char *rev = strrev(str);\n\
    \n\
        // Check if the original and reversed strings are equal\n\
        if (strcmp(str, rev) == 0)\n\
            printf(\"\\\"%s\\\" is palindrome.\\n\", str);\n\
        else\n\
            printf(\"\\\"%s\\\" is not palindrome.\\n\", str);\n\
    }\n\
    \n\
    int main() {\n\
        // Checking for palindrome strings\n\
        isPalindrome(\"madam\");\n\
        isPalindrome(\"hello\");\n\
    \n\
        return 0;\n\
    }\n\
    ";
    lex(text1);
    
    printf("\n\nQ2:\n");
    char text2[] = "\
    // C program to multiply two matrices\n\
    #include <stdio.h>\n\
    #include <stdlib.h>\n\
    \n\
    // matrix dimensions so that we dont have to pass them as\n\
    // parametersmat1[R1][C1] and mat2[R2][C2]\n\
    #define R1 2 // number of rows in Matrix-1\n\
    #define C1 2 // number of columns in Matrix-1\n\
    #define R2 2 // number of rows in Matrix-2\n\
    #define C2 3 // number of columns in Matrix-2\n\
    \n\
    void multiplyMatrix(int m1[][C1], int m2[][C2]) {\n\
        int result[R1][C2];\n\
    \n\
        printf(\"Resultant Matrix is:\\n\");\n\
    \n\
        for (int i = 0; i < R1; i++) {\n\
            for (int j = 0; j < C2; j++) {\n\
                result[i][j] = 0;\n\
    \n\
                for (int k = 0; k < R2; k++) {\n\
                    result[i][j] += m1[i][k] * m2[k][j];\n\
                }\n\
    \n\
                printf(\"%d\\t\", result[i][j]);\n\
            }\n\
    \n\
            printf(\"\\n\");\n\
        }\n\
    }\n\
    \n\
    int main() {\n\
        int m1[R1][C1] = { { 1, 1 }, { 2, 2 } };\n\
        int m2[R2][C2] = { { 1, 1, 1 }, { 2, 2, 2 } };\n\
    \n\
        if (C1 != R2) {\n\
            printf(\"The number of columns in Matrix-1 must be \"\n\
                \"equal to the number of rows in \"\n\
                \"Matrix-2\\n\");\n\
            printf(\"Please update MACROs value according to \"\n\
                \"your array dimension in \"\n\
                \"#define section\\n\");\n\
    \n\
            exit(EXIT_FAILURE);\n\
        }\n\
    \n\
        multiplyMatrix(m1, m2);\n\
        return 0;\n\
    }\n\
    ";
    lex(text2);
    return 0;
}
