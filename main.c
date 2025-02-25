#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define typename(x) _Generic((x),                                                 \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "other")

// Fun��es de apoio
void concatenar_string(char *a, char *b) {
    while(*a) a++;
    while(*b) {
        *a = *b;
        b++;
        a++;
    }
    *a = '\0';
}

void concatenar_char(char *a, char b) {
    while(*a) a++;
    *a = b;
    a++;
    *a = '\0';
}

void concatena_espaco(char* s) {
    int tam = strlen(s);
    memset(s+tam, ' ', 1);
    s[tam + 1] = '\0';
}

typedef struct morse_map_node {
    char letter;
    char* morse;
    struct morse_map_node *left;
    struct morse_map_node *right;
} MorseTreeNode;

MorseTreeNode* new_node()  {
    MorseTreeNode* node = (MorseTreeNode*)malloc(sizeof(MorseTreeNode));
    node->letter = ' ';
    node->morse = " ";
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_node(MorseTreeNode* root, char letter, char* morse) {
    MorseTreeNode* current = root;
    for(char *it = morse; *it != '\0'; it++) {
        if(*it == '.') {
            if(current->left == NULL) {
                current->left = new_node();
            }
            current = current->left;
        } else if(*it == '-') {
            if(current->right == NULL) {
                current->right = new_node();
            }
            current = current->right;
        }
    }
    current->letter = letter;
    current->morse = morse;
}

void create_tree(MorseTreeNode* root) {
    insert_node(root, 'E', ".");
    insert_node(root, 'T', "-");
    insert_node(root, 'I', "..");
    insert_node(root, 'A', ".-");
    insert_node(root, 'N', "-.");
    insert_node(root, 'M', "--");
    insert_node(root, 'S', "...");
    insert_node(root, 'U', "..-");
    insert_node(root, 'R', ".-.");
    insert_node(root, 'W', ".--");
    insert_node(root, 'D', "-..");
    insert_node(root, 'K', "-.-");
    insert_node(root, 'G', "--.");
    insert_node(root, 'O', "---");
    insert_node(root, 'H', "....");
    insert_node(root, 'V', "...-");
    insert_node(root, 'F', "..-.");
    insert_node(root, 'L', ".-..");
    insert_node(root, 'P', ".--.");
    insert_node(root, 'J', ".---");
    insert_node(root, 'B', "-...");
    insert_node(root, 'X', "-..-");
    insert_node(root, 'C', "-.-.");
    insert_node(root, 'Y', "-.--");
    insert_node(root, 'Z', "--..");
    insert_node(root, 'Q', "--.-");
    insert_node(root, '5', ".....");
    insert_node(root, '4', "....-");
    insert_node(root, '3', "...--");
    insert_node(root, '2', "..---");
    insert_node(root, '1', ".----");
    insert_node(root, '6', "-....");
    insert_node(root, '7', "--...");
    insert_node(root, '8', "---..");
    insert_node(root, '9', "----.");
    insert_node(root, '0', "-----");
}

char find_letter(MorseTreeNode* root, char* morse) {
    MorseTreeNode* current = root;
    for (char* it = morse; *it != '\0'; it++) {
        if(*it == '.') {
            current = current->left;
        } else if(*it == '-') {
            current = current->right;
        }
    }
    return current->letter;
}

char* find_morse(MorseTreeNode* root, char letter) {
    if (root->letter == letter) {
        return root->morse;
    } else {
        if (root->left != NULL) {
            MorseTreeNode* left = find_morse(root->left, letter);
            if (left != NULL) {
                return left;
            }
        }
        if (root->right != NULL) {
            return find_morse(root->right, letter);
        }
    }

    return NULL;
}

char* convert_to_text(MorseTreeNode* root, char* morse) {
    char* frase_texto = calloc(500, sizeof(char*));

    char* splitted = strtok(morse, " ");
    while(splitted != NULL) {
        char letter = find_letter(root, splitted);;
        if(splitted == "/") {
            concatena_espaco(frase_texto);
        } else {
            concatenar_char(frase_texto, letter);
        }
        splitted = strtok(NULL, " ");
    }
    return frase_texto;
}

char* convert_to_morse(MorseTreeNode* root, char* frase) {
    frase[strcspn(frase, "\n")] = 0;
    char* frase_morse = calloc(500, sizeof(char*));
    for(char* it = frase; *it != '\0'; it++) {
        char* morse = find_morse(root, *it);
        if(morse != NULL) {
            if(*it == ' ') {
                concatenar_string(frase_morse, " / ");
            } else {
                concatenar_string(frase_morse, morse);
                concatena_espaco(frase_morse);
            }
        }
    }
    return frase_morse;
}

void print_preorder(MorseTreeNode* root) {
    if (root == NULL) return;
    if(root->letter != ' ') printf("%c ", root->letter);
    print_preorder(root->left);
    print_preorder(root->right);
}

void print_inorder(MorseTreeNode* root) {
    if (root == NULL) return;
    print_inorder(root->left);
    if(root->letter != ' ') printf("%c ", root->letter);
    print_inorder(root->right);
}

void print_postorder(MorseTreeNode* root) {
    if (root == NULL) return;
    print_postorder(root->left);
    print_postorder(root->right);
    if(root->letter != ' ') printf("%c ", root->letter);
}

int main() {
    MorseTreeNode* root = new_node();
    create_tree(root);


    // Converter morse em texto
    FILE* file_morse;
    char* morse = calloc(500, sizeof(char*));

    file_morse = fopen("morses.txt", "r");
    char* tmp;

    while(fgets((char*)morse, 500, (FILE*) file_morse)) {
        morse[strcspn(morse, "\n")] = 0;

        tmp = malloc(sizeof(morse));
        strncpy(tmp, morse, strlen(morse));

        char* frase_texto = convert_to_text(root, morse);
        printf("\"%s\" = %s\n", tmp, frase_texto);

        free(tmp);
    }

    fclose(file_morse);


    printf("\n\n");


    // Conveter textos para morse
    FILE* file_text;
    char* frase = calloc(500, sizeof(char*));

    file_text = fopen("textos.txt", "r");

    while(fgets((char*)frase, 500, (FILE*) file_text)) {
        char* frase_morse = convert_to_morse(root, frase);
        printf("\"%s\" = %s\n", frase, frase_morse);
    }

    fclose(file_text);

    return 0;
}
