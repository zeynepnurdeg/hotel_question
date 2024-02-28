#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num;
	char type;
} room_t;

typedef struct {
	char name[30];
	int birthYear;
	int day;
	double pay;
	room_t roomInfo;
} customer_t;

void readFromFile(FILE* inp, int size, customer_t* arr) {
	int i = 0;
	while (i != size)
	{
		fscanf(inp, "%s %d %d %d %c %f", &arr[i].name, &arr[i].birthYear, &arr[i].day, &arr[i].roomInfo.num, &arr[i].roomInfo.type);
		i++;
	}
}

void displayAll(customer_t* arr, int size) {
	printf("\nName \t         Byear   Day   Room Num   Type    Payment");
	printf("\n----------------------------------------------------------------\n");
	int i;
	for (i = 0; i < size; i++) {
		switch (arr[i].roomInfo.type)
		{
		case 'S':
			arr[i].pay = 1000.0 * arr[i].day;
			break;
		case 'T':
			arr[i].pay = 2500.0 * arr[i].day;
			break;
		case 'D':
			arr[i].pay = 3500.0 * arr[i].day;
			break;
		}
		printf("%-14s %3d %6d      %5d     %c      %.2f\n", arr[i].name, arr[i].birthYear, arr[i].day, arr[i].roomInfo.num, arr[i].roomInfo.type, arr[i].pay);
	}
	printf("\n");
}

double calculateTotalEarnings(customer_t* arr, int size) {
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum = sum + arr[i].pay;
	return (sum);
}

int findCustomerMaxPayment(customer_t* arr, int size) {
	double maxPay = arr[0].pay;
	int i, maxPos = 0;
	for (i = 1; i < size; i++)
		if (maxPay < arr[i].pay)
		{
			maxPay = arr[i].pay;
			maxPos = i;
		}
	return (maxPos);
}

int main(void)
{
	FILE* inp;
	inp = fopen("customers.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		int num;
		do {
			printf("How many customer info will you read? (5 - 20)");
			scanf("%d", &num);
		} while (num < 5 || num > 20);

		customer_t* arr;
		arr = (customer_t*)malloc(sizeof(customer_t) * num);
		readFromFile(inp, num, arr);
		displayAll(arr, num);
		fclose(inp);

		double totalEarnings = calculateTotalEarnings(arr, num);
		printf("Total Earnings of the Hotel: %.2f TL\n", totalEarnings);
		printf("\n");

		int maxPos = findCustomerMaxPayment(arr, num);
		printf("The Customer having maximum payment for accommodation:\n");
		printf("%s with the price %.2f TL\n", arr[maxPos].name, arr[maxPos].pay);
		
		free(arr);
	}
	return 0;
}