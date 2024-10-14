/* 
Author: Jakob Huffman
KUID: 2975499
Date: 10/13/2024
Lab: lab05
Last modified: 10/13/2024
Purpose: Using file I/O to generate a monthly sales report.
*/

#include <stdio.h>
#include <stdlib.h>
#define MONTHS_AMT 12


const char* month_name(int index) {
    const char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return months[index];
}



int main() {
    FILE *file_input = fopen("sales.txt", "r");
    if (file_input == NULL) {
        printf("Wrong file input must be sales.txt\n");
        return 1;
    }

    double sales[MONTHS_AMT];
    for (int i = 0; i < MONTHS_AMT; i++) {
        fscanf(file_input, "%lf", &sales[i]);
    }
    fclose(file_input);




    print_sales_report(sales);
    print_sales_summary(sales);
    print_average_report(sales);
    print_high_to_low(sales);




    return 0;
}

void print_sales_report(double sales[]) {
    printf("Monthly Sales Report for 2024\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS_AMT; i++) {
        printf("%-10s\t%.2f\n", month_name(i), sales[i]);
    }
    printf("\n");
}





void print_sales_summary(double sales[]) {
    double min = sales[0], max = sales[0], total = 0;
    int min_index = 0, max_index = 0;
    
    for (int i = 0; i < MONTHS_AMT; i++) {
        if (sales[i] < min) {
            min = sales[i];
            min_index = i;
        }
        if (sales[i] > max) {
            max = sales[i];
            max_index = i;
        }
        total += sales[i];
    }

    double average = total / MONTHS_AMT;

    printf("Sales summary report:\n");
    printf("Minimum sales: %.2f (%s)\n", min, month_name(min_index));
    printf("Maximum sales: %.2f (%s)\n", max, month_name(max_index));
    printf("Average sales: %.2f\n\n", average);
}




void print_average_report(double sales[]) {
    printf("Six-Month moving average report:\n");
    for (int i = 0; i <= MONTHS_AMT - 6; i++) {
        double sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        double moving_average = sum / 6;
        printf("%s-%s\t%.2f\n", month_name(i), month_name(i + 5), moving_average);
    }
    printf("\n");
}




void print_high_to_low(double sales[]) {
    struct m_sales {
        int month_index;
        double sales_value;
    };



    struct m_sales month_sales[MONTHS_AMT];
    for (int i = 0; i < MONTHS_AMT; i++) {
        month_sales[i].month_index = i;
        month_sales[i].sales_value = sales[i];
    }


    for (int i = 0; i < MONTHS_AMT - 1; i++) {
        for (int j = i + 1; j < MONTHS_AMT; j++) {
            if (month_sales[i].sales_value < month_sales[j].sales_value) {
                struct m_sales temp = month_sales[i];
                month_sales[i] = month_sales[j];
                month_sales[j] = temp;
            }
        }
    }

    printf("Sales report (highest to lowest):\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS_AMT; i++) {
        printf("%-10s\t$%.2f\n", month_name(month_sales[i].month_index), month_sales[i].sales_value);
    }
}
