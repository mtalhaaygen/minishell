#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT
} TokenType;

typedef struct {
    TokenType type;
    char* content;
} Token;

Token getNextToken(char* input) {
    static char* currentPos = NULL;

    if (currentPos == NULL) {
        currentPos = input;
    }

    while (isspace(*currentPos)) {
        currentPos++;
    }

    if (*currentPos == '\0') {
        Token token;
        token.type = TOKEN_EOF;
        token.content = NULL;
        return token;
    }

    if (*currentPos == '|') {
        Token token;
        token.type = TOKEN_PIPE;
        token.content = NULL;
        currentPos++;
        return token;
    }

    if (*currentPos == '<') {
        Token token;
        token.type = TOKEN_REDIRECT_IN;
        token.content = NULL;
        currentPos++;
        return token;
    }

    if (*currentPos == '>') {
        Token token;
        token.type = TOKEN_REDIRECT_OUT;
        token.content = NULL;
        currentPos++;
        return token;
    }

    char* start = currentPos;
    while (*currentPos != '\0' && !isspace(*currentPos) && *currentPos != '|' && *currentPos != '<' && *currentPos != '>') {
        currentPos++;
    }

    int length = currentPos - start;
    char* word = (char*)malloc(length + 1);
    strncpy(word, start, length);
    word[length] = '\0';

    Token token;
    token.type = TOKEN_WORD;
    token.content = word;
    return token;
}

void freeToken(Token token) {
    free(token.content);
}

typedef struct {
    Token* tokens;
    int currentToken;
} Parser;

Parser* createParser(Token* tokens) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->currentToken = 0;
    return parser;
}

void destroyParser(Parser* parser) {
    free(parser);
}

Token getCurrentToken(Parser* parser) {
    return parser->tokens[parser->currentToken];
}

void consumeToken(Parser* parser) {
    parser->currentToken++;
}

void parseCommand(Parser* parser) {
    Token currentToken = getCurrentToken(parser);
    if (currentToken.type == TOKEN_WORD) {
        printf("Command: %s\n", currentToken.content);
        consumeToken(parser);
    }
}

void parsePipeline(Parser* parser) {
    parseCommand(parser);
    Token currentToken = getCurrentToken(parser);
    while (currentToken.type == TOKEN_PIPE) {
        consumeToken(parser);
        parseCommand(parser);
        currentToken = getCurrentToken(parser);
    }
}

void parseInput(Parser* parser) {
    parsePipeline(parser);
    Token currentToken = getCurrentToken(parser);
    if (currentToken.type != TOKEN_EOF) {
        printf("Syntax Error: Unexpected token\n");
    }
}

void executeCommand(char* command) {
    char* args[64];
    int numArgs = 0;

    char* token = strtok(command, " ");
    while (token != NULL) {
        args[numArgs] = token;
        numArgs++;
        token = strtok(NULL, " ");
    }
    args[numArgs] = NULL;

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[100];
    while (1) {
        printf("Bir komut girin: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        Token tokens[100];
        int numTokens = 0;

        Token token;
        do {
            token = getNextToken(input);
            if (token.type != TOKEN_EOF) {
                tokens[numTokens] = token;
                numTokens++;
            }
            freeToken(token);
        } while (token.type != TOKEN_EOF);

        Parser* parser = createParser(tokens);
        parseInput(parser);
        destroyParser(parser);

        executeCommand(input);
    }

    return 0;
}


/*
Bu örnekte, bir Bash kabuğu benzeri bir program sunulmuştur. Program, kullanıcıdan komut girişi alır ve hem lexer hem de parser kullanarak komutları analiz eder. Ayrıca, girilen komutları yürütmek için bir executer mekanizması vardır.

Kullanıcının komut girişi kabul edilirken, lexer tarafından tokenlara ayrıştırılır ve parser ile analiz edilir. Ardından, parse edilen komutlar yürütülür. Komutlar, executeCommand fonksiyonu kullanılarak yeni bir süreç olarak yürütülür.

Ana döngü, kullanıcının "exit" komutunu girdiğinde sonlanır. Ayrıca, girilen komutlar hem parse edilir hem de yürütülür.

Bu örneği derleyip çalıştırdığınızda, Bash kabuğu benzeri bir deneyim yaşayabilirsiniz. Komutları girerek çalıştırabilirsiniz. Örneğin, "ls", "pwd", "echo Hello, World!" gibi basit komutlar girilebilir. Kabuktan çıkmak için "exit" komutunu kullanabilirsiniz.

Bu örnekte, temel bir Bash kabuğu oluşturulmuştur. İhtiyaçlarınıza bağlı olarak, özellikleri ve işlevselliği geliştirebilirsiniz. Örneğin, değişken yönetimi, kabuk betikleri, akış kontrolü, kabuk değişkenleri, hata işleme vb. gibi özellikleri ekleyebilirsiniz.*/


