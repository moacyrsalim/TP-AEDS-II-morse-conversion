#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct morse_map_node {
    char letter;
    char* morse;
    struct morse_map_node *left;
    struct morse_map_node *right;
} MorseTreeNode;

MorseTreeNode* new_node()  {
    MorseTreeNode* node = (MorseTreeNode*)malloc(sizeof(MorseTreeNode));
    node->letter = ' ';
    node->morse = ' ';
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
        } else if(*it == '-'){
            current = current->right;
        }
    }
    return current->letter;
}

char* convert_to_string(MorseTreeNode* root, char* str) {
    char* converted = "";
    for(char* it = str; *it != '\0'; it++) {
        strcat(converted, find_letter(root, *it));
    }
    return converted;
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

    FILE *fp;
    char str[1000];
    char* filename = "input.txt";
    fp = fopen(filename, "r");
    while (fgets(str, 1000, fp) != NULL);
    fclose(fp);

    char *morse_convert = convert_to_string(root, str);

    return 0;
}
