/* vendingmachine.c
    A finite state machine as a vending machine */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 10

// define variables and default amounts
int products_total = 4;
int total_money_inserted;
int inserted_coin_value;
int product_selection;
int product_price;
int returned_money;
// define product structure
struct Products
{
    char name[20];
	int price;
};

struct Products arr_products[MAX_SIZE] =
{
    {"Fritos", 25},
    {"Cookie", 10},
    {"Donuts", 5},
    {"Starburst", 100},
};

// prototype functions 
void add_product(struct Products arr_products[MAX_SIZE]);
void print_product(struct Products arr_products[MAX_SIZE]);

// int argc and char *argv[] allow arguments to be passed in CLI during init
int main(int argc, char *argv[])
{
	int main_menu_selection;
	while(1)
	{
		printf("Welcome to CoinOnly Vending!\n");
		printf("Please choose an option by their corresponding number!\n");
		printf("[1] Purchase product [2] Add new product [3] Turn off machine\n");
		scanf("%d", &main_menu_selection);
		if(main_menu_selection == 1)
		{
			// Reset product_price so multiple purchases will not add to price
			int product_price = 0;
			
			printf("Please choose from one of the available products below!\n");
			print_product(arr_products);
			printf("Please make a selection by typing the product number!\n");
			scanf("%d", &product_selection);
			product_price += arr_products[product_selection].price;
			printf("Product selection: %d Product price in cents: %d\n", product_selection, product_price);
			printf("Please insert one of the following coins with their numerical value.\n");
			while(total_money_inserted < product_price)
			{
				printf("'1':penny, '5':nickle, '10':dime, '25':quarter\n");
				scanf("%d", &inserted_coin_value);
				total_money_inserted += inserted_coin_value;
				inserted_coin_value = 0;
			}
			if(total_money_inserted==product_price)
			{
				printf("%s vended. Enjoy!\n", arr_products[product_selection].name);
				total_money_inserted = 0;
				inserted_coin_value = 0;
			}
			else if (total_money_inserted > product_price)
			{
				returned_money += total_money_inserted - product_price;
				printf("%s vended. %d cents returned. Enjoy!\n", arr_products[product_selection].name, returned_money);
				returned_money = 0;
				total_money_inserted = 0;
				inserted_coin_value = 0;
			}
		}
		else if(main_menu_selection == 2)
		{
			add_product(arr_products);
		}
		else if(main_menu_selection == 3)
		{
			break;
		}
		else
		{
			printf("Invalid selection\n");
		}
		/* checks if command line argument was passed 
		if (argc == 2)
		{
			printf("The argument supplied is %s\n", argv[1]);
		}
		
		else if (argc > 2)
		{
			printf("Too many arguments supplied.\n");
		}
		else
		{
			printf("One argument expected.\n");
		}*/
    }
	return 0;
}

void add_product(struct Products arr_products[MAX_SIZE])
{
	int product_index = products_total;
	
	printf("Enter product name: \n");
	scanf("%s", arr_products[product_index].name);
	
	printf("Enter product price: \n");
	scanf("%d", &arr_products[product_index].price);
	
	printf("%s added. price in cents: %d\n", arr_products[product_index].name, arr_products[product_index].price);
	products_total += 1;
}

void print_product(struct Products arr_products[MAX_SIZE])
{
	int i;
	printf("List of products available\n");
    for(i = 0; i < MAX_SIZE; i++)
	{
		printf("[%d] %s price: %d cents\n", i, arr_products[i].name, arr_products[i].price);
    }
	printf("%d total products in the vending machine.\n", products_total);
	
}

