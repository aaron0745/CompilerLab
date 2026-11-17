#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[1000] = "", line[200], token[20];
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };
    int i = 0, j, k, flag;

    printf("Enter the program (Type END on a new line to finish):\n");

    while (1) {
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "END\n") == 0 || strcmp(line, "END") == 0) {
            break;
        }
        strcat(str, line);
    }

    printf("\nTokens:\n\n");

    while (str[i] != '\0') {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            i++;
            continue;
        }

        if (str[i] == '/' && str[i + 1] == '/') {
            while (str[i] != '\n' && str[i] != '\0') {
                i++;
            }
            continue;
        }

        if (str[i] == '/' && str[i + 1] == '*') {
            i += 2;
            while (str[i] != '\0' && !(str[i] == '*' && str[i + 1] == '/')) {
                i++;
            }
            if (str[i] != '\0') {
                i += 2;
            }
            continue;
        }

        if (isalpha((unsigned char)str[i])) {
            j = 0;
            while (isalnum((unsigned char)str[i])) {
                token[j++] = str[i++];
            }
            token[j] = '\0';

            flag = 0;
            for (k = 0; k < 32; k++) {
                if (strcmp(token, keywords[k]) == 0) {
                    flag = 1;
                    break;
                }
            }

            if (flag) {
                printf("%s : Keyword\n", token);
            } else {
                printf("%s : Identifier\n", token);
            }
        } else if (isdigit((unsigned char)str[i])) {
            j = 0;
            while (isdigit((unsigned char)str[i])) {
                token[j++] = str[i++];
            }
            token[j] = '\0';
            printf("%s : Number\n", token);
        } else if (strchr("+-*/=%<>", str[i])) {
            printf("%c : Operator\n", str[i]);
            i++;
        } else if (strchr("(){}[],;", str[i])) {
            printf("%c : Special Symbol\n", str[i]);
            i++;
        } else {
            printf("%c : Invalid Token\n", str[i]);
            i++;
        }
    }

    return 0;
}
