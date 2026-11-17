%{
#include <stdio.h>

int lines = 0, words = 0, chars = 0;
%}

%%
\n              { lines++; chars++; }
[ \t]+          { chars += yyleng; }
[^ \t\n]+      { words++; chars += yyleng; }
%%

int main() {
    printf("Enter text (Press Ctrl+D to finish):\n");
    yylex();

    printf("\nNumber of Lines : %d\n", lines);
    printf("Number of Words : %d\n", words);
    printf("Number of Characters : %d\n", chars);

    return 0;
}

int yywrap() {
    return 1;
}
