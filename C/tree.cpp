#include <iostream>
#include <clocale>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "locale.h"
#include "string.h"


struct tree {
    int key;
    char surname[20];
    tree *left, *right;
};


tree *create_tree(tree *root) {
    int key;
    char surname[20];
    if (root) {
        printf("Binary tree has already existed!");
        return root;
    }
    root = new tree[1];
    printf("Enter key for root: \n");
    scanf("%d", &key);
    printf("Enter surname for root: \n");
    scanf("%s", surname);
    strcpy(root->surname, surname);
    root->key = key;
    root->left = NULL;
    root->right = NULL;
    return root;
}


void _add_new_node(tree *root, tree *new_node){
    if (new_node->key > root->key) {

        if(!root->right) {
            root->right = new_node;
        } else {
            _add_new_node(root->right, new_node);
        }

    } else if (new_node->key < root->key) {

        if(!root->left) {
            root->left = new_node;
        } else {
            _add_new_node(root->left, new_node);
        }

    } else {
        printf("Key must be greater or less then %d", root->key);
    }
}


void insert_new_data(tree *root) {
    int key;
    char surname[20];
    tree *new_node = new tree[1];
    printf("Enter key number: \n");
    scanf("%d", &key);
    printf("Enter surname: \n");
    scanf("%s", surname);

    new_node->key = key;
    strcpy(new_node->surname, surname);
    new_node->right = NULL;
    new_node->left = NULL;
    _add_new_node(root, new_node);
}


void search_by_key(tree *root, int key) {
    if (root->key == key) {
        printf("Data for key %d: \n", key);
        printf("Key: %d, Surname: %s", root->key, root->surname);
    } else if (!root->right && !root->left) {
        printf("Data for key %d was not found!!!!\n", key);
    }

    if (key < root->key && root->left) {
        search_by_key(root->left, key);
    } else if (key > root->key && root->right) {
        search_by_key(root->right, key);
    }

}


tree *find_min(tree *root){
    if (!root->left ){
        return root;
    }

    find_min(root->left);
}


tree *delete_by_key(tree *root, int key) {
    if (key < root->key && root->left) {
        delete_by_key(root->left, key);
    } else if (key > root->key && root->right) {
        delete_by_key(root->right, key);
    } else {

        if (root->left && root->right){
            tree *tempNode = find_min(root->right);
            root->key = tempNode->key;
            root->right = delete_by_key(root->right, tempNode->key);

        } else if (root->left) {
            root = root->left;

        } else if (root->right) {
            root = root->right;

        } else {
            delete root;
        }

    }
    return root;
}


void output_information(tree *root) {
    if (root->right && root->left) {
        printf("key: %d, surname:%s \n", root->key, root->surname);
        output_information(root->right);
        output_information(root->left);
    } else if (root->right) {
        printf("key: %d, surname:%s \n", root->key, root->surname);
        output_information(root->right);
    } else if (root->left) {
        printf("key: %d, surname:%s \n", root->key, root->surname);
        output_information(root->right);
    } else {
        printf("key: %d, surname:%s \n", root->key, root->surname);
    }
}


int node_count(tree *root) {
    int c =  1;
    if (root == NULL)
        return 0;

    else {
        c += node_count(root->left);
        c += node_count(root->right);
        return c;
    }
}


int calculate_right_node_count(tree *root) {
    int count = 0;
    if (!root->right) {
        return 0;
    }
    count = node_count(root->right);
    return count;
}


void free_memmory(tree *root) {
    if (root != NULL) {
        free_memmory(root->right);
        free_memmory(root->left);
        delete root;
        root = NULL;
    }
}


void padding ( char ch, int n ) {
    int i;
    for ( i = 0; i < n; i++ )
        putchar ( ch );
}


void structure (tree *root, int level ) {
    if ( root == NULL ) {
        padding ( '\t', level );
        puts("~");
    }
    else {
        structure ( root->right, level + 1 );
        padding ( '\t', level );
        printf ( "%d", root->key);
        structure ( root->left, level + 1 );
    }
}


int main() {
    int c = 0;
    int key;
    tree *root;
    root = NULL;
    int choice = NULL;
    printf("1 - create tree.\n");
    printf("2 - add node in tree.\n");
    printf("3 - find by key.\n");
    printf("4 - delete node by key.\n");
    printf("5 - output \n");
    printf("6 - output as tree \n");
    printf("7 - calculate right node count \n");
    printf("8 - exit and free memory \n");

    while (true) {
        printf("make choice\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = create_tree(root);
                break;
            case 2:
                insert_new_data(root);
                break;
            case 3:
                printf("enter key for searching: \n");
                scanf("%d\n" ,key);
                search_by_key(root, key);
                break;
            case 4:
                printf("enter key for deleting: \n");
                scanf("%d\n" ,key);
                root = delete_by_key(root, key);
            case 5:
                output_information(root);
                break;
            case 6:
                structure(root, 0);
                break;
            case 7:
                c = calculate_right_node_count(root);
                printf("count = %d\n", c);
                break;
            case 8:
                free_memmory(root);
                exit(0);
        }
    }


}