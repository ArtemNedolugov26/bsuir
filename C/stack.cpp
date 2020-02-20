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


STACK *FIRST = NULL;


void create_stack(int N) {
    STACK  *tmp = NULL;
    for (int i = 0; i < N; i++) {
        tmp = FIRST;
        FIRST = new STACK;
        FIRST->next = tmp;
        FIRST->element = rand();
    }
}


void add_element_to_stack(int *N) {
    STACK *el = new STACK;
    if(FIRST) {
        el->next = FIRST;
    } else {
        FIRST = new STACK;
        el->next = NULL;
    }

    el->element = rand();
    FIRST = el;

    *N += 1;
}


void output_stack(int N) {
    STACK *tmp = NULL;
    tmp = FIRST;
    for (int i = 0; i < N; i++) {
        printf("%d -- %d \n", N - i, FIRST->element);
        FIRST = FIRST->next;
    }
    printf("--------------\n");
    FIRST = tmp;
}


double get_average_value(int N) {
    double sum = 0;
    STACK *tmp = NULL;
    tmp = FIRST;
    for (int i = 0; i < N; i++) {
        sum += FIRST->element;
        FIRST = FIRST->next;
    }
    FIRST = tmp;
    return sum/N;
}

int get_count_less_elements(int el, int N) {
    int count = 0;
    STACK *tmp = NULL;
    tmp = FIRST;
    for (int i = 0; i < N; i++) {
        if (FIRST->element < el){
            count++;
        }
        FIRST = FIRST->next;
    }
    FIRST = tmp;
    return count;
}


void delete_stack_el(STACK *el) {
    STACK *tmp;
    tmp = el;
    el = el->next;
    delete tmp;

}


void delete_all_list(int N) {
    for (int i = 0; i < N; i++) {
        delete_stack_el(FIRST);
        FIRST = FIRST->next;
    }
}


void delete_less_elements(double el, int *N) {
    STACK *tmp = NULL, *previous = NULL, *last = NULL;
    int count = 0;
    for (int i = 0; i < *N; i++) {
        if (FIRST->element >= el) {
            count++;

            if (count == 1) {
                last = FIRST;
                previous = FIRST;
            } else if (count == 2) {
                previous = FIRST;
                last->next = previous;
            } else {
                tmp = FIRST;
                previous->next = tmp;
                previous = tmp;
            }

        } else {
            delete_stack_el(FIRST);
        }
        FIRST = FIRST->next;
    }
    if (tmp){
        tmp->next = NULL;
    }
    FIRST = last;
    *N = count;
}


int main() {
    int N = 0, count;
    double average;
    int choice = NULL;
    printf("1 - create list.\n");
    printf("2 - see list.\n");
    printf("3 - add element to list.\n");
    printf("4 - seek and destroy.\n");
    printf("5 - exit\n");

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
                add_element_to_stack(&N);
                break;
            case 4:
                average = get_average_value(N);
                printf("average data = %.1lf \n", average);
                count = get_count_less_elements(average, N);
                printf("count less elements: %d \n", count);
                delete_less_elements(average, &N);
                break;
            case 5:
                delete_all_list(N);
                exit(0);
        }
    }
}
