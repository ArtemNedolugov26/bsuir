#include <iostream>
#include <clocale>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "locale.h"
#include "string.h"



struct STACK {
    int element;
    STACK *next;
};


STACK *FIRST;
STACK *LAST;


void create_stack(int N) {
    STACK  *tmp = NULL;
    FIRST = NULL;
    LAST = NULL;
    for (int i = 0; i < N; i++) {
        tmp = LAST;
        LAST = new STACK;
        LAST->next = tmp;
        LAST->element = rand()%100 + 1;
        if (!FIRST) {
            FIRST = LAST;
        }
    }
}


void output_stack(int N) {
    STACK *tmp = NULL;
    tmp = LAST;
    for (int i = 0; i < N; i++) {
        printf("%d -- %d \n", N - i, LAST->element);
        LAST = LAST->next;
    }
    printf("--------------\n");
    LAST = tmp;
}


void push_back(int el, int *N) {
    STACK *tmp, *element;
    tmp = LAST;
    element = new STACK;
    element->element = el;
    element->next = tmp;
    LAST = element;
    *N += 1;
}

void push_front(int el, int *N) {
    STACK *element;
    element = new STACK;
    FIRST->next = element;
    element->element = el;
    element->next = NULL;
    FIRST = element;
    *N += 1;
}


int get_min_index(int *list, int N) {
    int min, index_min;
    for(int i = 0; i < N; i++)  {
        if (i == 0) {
            min = *(list + i);
            index_min = i;
        }

        if (*(list + i) < min){
            min = *(list + i);
            index_min = i;
        }
    }

    return index_min;
}


int get_max_index(int *list, int N) {
    int max, index_max;
    for(int i = 0; i < N; i++) {
        if (i == 0) {
            max = *(list + i);
            index_max = i;
        }

        if (*(list + i) > max){
            max = *(list + i);
            index_max = i;
        }
    }

    return index_max;
}


void generate_second_list(int *list, int N){
    for (int i = 0; i < N; i++){
        *(list + i) = rand()%100 + 1;
    }
}


void insert_list_into_second(int *list, int min_index, int max_index, int *N){
    int tmp_len = *N;
    if(min_index < max_index) {
        for (int i = min_index; i >= 0; i--){
            push_front(*(list + i), N);
        }
        for (int i = max_index; i < tmp_len; i++){
            push_back(*(list + i), N);
        }
    } else {
        for (int i = max_index; i >= 0; i--){
            push_front(*(list + i), N);
        }
        for (int i = min_index; i < tmp_len; i++){
            push_back(*(list + i), N);
        }
    }
}


void print_second_list(int *list, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d    ", *(list + i));
    }
    printf("\n");
}


int main() {
    int N=10, max_index, min_index;
    int el;
    int choice;
    int *list;
    printf("1 - create first list.\n");
    printf("2 - see first list.\n");
    printf("3 - create second list");
    printf("4 - see second list.\n");
    printf("5 - push data to front of first list.\n");
    printf("6 - push data to back of first list.\n");
    printf("7 - merge two lists.\n");
    printf("8 - exit\n");

    while (true) {
        printf("make choice\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("enter element count:\n");
                scanf("%d", &N);
                create_stack(N);
                break;
            case 2:
                output_stack(N);
                break;
            case 3:
                list = new int[N];
                generate_second_list(list, N);
                break;
            case 4:
                print_second_list(list, N);
                break;
            case 5:
                printf("enter elemnt:\n");
                scanf("%d", &el);
                push_front(el, &N);
                break;
            case 6:
                printf("enter elemnt:\n");
                scanf("%d", &el);
                push_back(el, &N);
                break;
            case 7:
                min_index = get_min_index(list, N);
                max_index = get_max_index(list, N);
                printf("min index of second list: %d \n", min_index);
                printf("max index of second list: %d \n", max_index);
                insert_list_into_second(list, min_index, max_index, &N);
                break;
            case 8:
                exit(0);
            default:
                continue;
        }
    }


}