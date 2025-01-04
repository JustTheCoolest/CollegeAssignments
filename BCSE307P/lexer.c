#include <stdio.h>
#include <string.h>

/*
Not Implemented:
- Multiline comments
- Preprocessor directives other than #include (#define, etc.)
- Keyword list is probably incomplete
*/

/*
Rewrite Suggestions:
- Increment the text variable itself, instead of the separate int *i
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
}

void iterate(int *i, char curr, char *text){
  int initial = *i;
  switch(curr){

    case ' ':
    case '\n':
    case '\t':
    ++*i;
    return;

    case '/':
    if(text[*i+1]=='/'){
      printf("comment ");
      while(text[*i] != '\n'){
        printf("%c", text[*i]);
        ++*i;
      }
      // does not handle the newline character at the end, for code simplicity
      printf("\n");
      return;
    }
    else{
      printf("division_operator\n");
      return;
    }

    case '#':
    if(streaming_strcmp(text+*i, "#include", 8)==0){
      *i += 8;
      printf("preprocessor_directive #include\n");
      while(text[*i]==' ') ++*i;
      char end;
      if(text[*i]=='<'){
        printf("builtin_module ");
        end = '>';
      }
      else if(text[*i]=='"'){
        printf("relative_module ");
      }
      else{
        error(*i);
      }
      while(text[*i] != end){
        ++*i;
        printf("%c", text[*i]);
      }
      printf("\n");
    }
    else{
      error(*i);
    }
    return;

    case '*':
    printf("dereference_operator\n");
    ++*i;
    return;

    default:
    char *keywords[] = {"char", "int", "float", "for", "while", "void", "return"};

  }
}

void lex(char* text){
    int i=0;
    char curr;
    while(curr != '\0'){
        char curr = text[i];
        iterate(&i, curr, text);
    }
}

int main(){
    // char name[] = "src1.cpp";
    // char text[] = getText(name); 
    // Flag: Implement File Handling
    // Flag: Optimality would be to traverse this char by char without loading fully
    char text1[] = ""; /*
    // Program to check for a palindrome string by reversing
// the string
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *strrev(char *str) {
    int len = strlen(str);
  
      // Temporary char array to store the
    // reversed string
    char *rev = (char *)malloc
      (sizeof(char) * (len + 1));
  
    // Reversing the string
    for (int i = 0; i < len; i++) {
        rev[i] = str[len - i - 1];
    }
    rev[len] = '\0';
    return rev;
}

void isPalindrome(char *str) {

    // Reversing the string
    char *rev = strrev(str);

    // Check if the original and reversed
      // strings are equal
    if (strcmp(str, rev) == 0)
        printf("\"%s\" is palindrome.\n",
               str);
    else
        printf("\"%s\" is not palindrome.\n",
               str);
}

int main() {
    
      // Cheking for palindrome strings
    isPalindrome("madam");
      isPalindrome("hello");

    return 0;
}
    */
    lex(text1);
    char text2[] = ""; /*
    // C program to multiply two matrices
#include <stdio.h>
#include <stdlib.h>

// matrix dimensions so that we dont have to pass them as
// parametersmat1[R1][C1] and mat2[R2][C2]
#define R1 2 // number of rows in Matrix-1
#define C1 2 // number of columns in Matrix-1
#define R2 2 // number of rows in Matrix-2
#define C2 3 // number of columns in Matrix-2

void multiplyMatrix(int m1[][C1], int m2[][C2])
{
	int result[R1][C2];

	printf("Resultant Matrix is:\n");

	for (int i = 0; i < R1; i++) {
		for (int j = 0; j < C2; j++) {
			result[i][j] = 0;

			for (int k = 0; k < R2; k++) {
				result[i][j] += m1[i][k] * m2[k][j];
			}

			printf("%d\t", result[i][j]);
		}

		printf("\n");
	}
}

// Driver code
int main()
{
	// R1 = 4, C1 = 4 and R2 = 4, C2 = 4 (Update these
	// values in MACROs)
	int m1[R1][C1] = { { 1, 1 }, { 2, 2 } };

	int m2[R2][C2] = { { 1, 1, 1 }, { 2, 2, 2 } };

	// if coloumn of m1 not equal to rows of m2
	if (C1 != R2) {
		printf("The number of columns in Matrix-1 must be "
			"equal to the number of rows in "
			"Matrix-2\n");
		printf("Please update MACROs value according to "
			"your array dimension in "
			"#define section\n");

		exit(EXIT_FAILURE);
	}

	// Function call
	multiplyMatrix(m1, m2);

	return 0;
}
    */
    lex(text2);
}