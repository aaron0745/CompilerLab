%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%
expr
    : expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | NUMBER
    ;
%%

int main() {
    printf("Enter an arithmetic expression:\n");

    if (yyparse() == 0) {
        printf("Valid Arithmetic Expression\n");
    }

    return 0;
}

void yyerror(const char *s) {
    printf("Invalid Arithmetic Expression\n");
}
