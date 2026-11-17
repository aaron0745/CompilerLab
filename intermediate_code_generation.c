#include <stdio.h>
#include <ctype.h>
#include <string.h>

char expr[100];
int tempCount = 1;

void newTemp(char *temp) {
    sprintf(temp, "t%d", tempCount++);
}

int precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }

    if (op == '+' || op == '-') {
        return 1;
    }

    return 0;
}

void generateIC() {
    char operands[50][20];
    char operators[50];
    int topOperand = -1, topOperator = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace((unsigned char)expr[i])) {
            continue;
        }

        if (isalnum((unsigned char)expr[i])) {
            char operand[20];
            int j = 0;

            while (isalnum((unsigned char)expr[i])) {
                operand[j++] = expr[i++];
            }

            operand[j] = '\0';
            strcpy(operands[++topOperand], operand);
            i--;
        } else if (expr[i] == '(') {
            operators[++topOperator] = expr[i];
        } else if (expr[i] == ')') {
            while (topOperator >= 0 && operators[topOperator] != '(') {
                char op = operators[topOperator--];
                char right[20], left[20], temp[20];

                strcpy(right, operands[topOperand--]);
                strcpy(left, operands[topOperand--]);
                newTemp(temp);

                printf("%s = %s %c %s\n", temp, left, op, right);
                strcpy(operands[++topOperand], temp);
            }

            topOperator--;
        } else if (strchr("+-*/", expr[i])) {
            while (topOperator >= 0 &&
                   precedence(operators[topOperator]) >= precedence(expr[i]) &&
                   operators[topOperator] != '(') {
                char op = operators[topOperator--];
                char right[20], left[20], temp[20];

                strcpy(right, operands[topOperand--]);
                strcpy(left, operands[topOperand--]);
                newTemp(temp);

                printf("%s = %s %c %s\n", temp, left, op, right);
                strcpy(operands[++topOperand], temp);
            }

            operators[++topOperator] = expr[i];
        }
    }

    while (topOperator >= 0) {
        char op = operators[topOperator--];
        char right[20], left[20], temp[20];

        strcpy(right, operands[topOperand--]);
        strcpy(left, operands[topOperand--]);
        newTemp(temp);

        printf("%s = %s %c %s\n", temp, left, op, right);
        strcpy(operands[++topOperand], temp);
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%99[^\n]", expr);

    printf("\nIntermediate Code:\n");
    generateIC();

    return 0;
}
