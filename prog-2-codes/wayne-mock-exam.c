#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct{
	char ID[16];
	char name[64];
	float balance;
}customer; //customer info

typedef struct{
	char ID[16];
	char name[64];
	float price;
	int qtyRemaining;
}product; //product info

typedef enum{
	PENDING, SUCCESS, OUT_OF_BAL, OUT_OF_STOCK, ERROR
}orderStatus; //order status

typedef enum{
	TRUE, FALSE
}boolean;

typedef struct{
	char customerID[16];
	char productID[16];
	int orderQty;
	int actualQty;
	float totalPrice;
	orderStatus status;
}order; //order info

typedef struct{
	customer cust[MAX];
	int count;
}customerList;

typedef struct{
	product prod[MAX];
	int count;
}productList;

/*********************************************/
/************ FUNCTION PROTOTYPES ************/
/*********************************************/

customerList initCustomerList();
productList initProductList();
void displayProductList(productList PL);
void displayCustomerList(customerList CL);

boolean findCustomer(customerList CL, char ID[]);
boolean findProduct(productList *PL, char ID[]);
void addProduct(productList *PL, product P);
void addCustomer(customerList *CL, customer C);
void reloadBalance(customerList *CL, char ID[], float amount);
void sortProductList(productList *PL);
order processOrder(customerList *CL, productList *PL, char custID[], char prodID[], int qty);
productList getItemsToRestock(productList *PL);
product getProduct(productList *PL, char ID[]);
void deleteProduct(productList *PL, char ID[]);

/*********************************************/
/*************** MAIN FUNCTION ***************/
/*********************************************/

int main(){
	customerList CL;
	productList PL;
	productList toRestock;
	customer tempCust;
	product tempProd;
	order tempOrder;
	float tempVal;
	char tempProdID[16], tempCustID[16];
	int tempQty;
	
	char choice = -1;
	float bal = 0;
	int numItems = 0;
	float rev = 0;
	
	CL = initCustomerList();
	PL = initProductList();
	
	do{
		system("cls");
		printf("\n==========================================");
        printf("\n                MAIN MENU                 ");
        printf("\n==========================================");
        printf("\n| Total amount reloaded: Php %5.2f        ",bal);
        printf("\n| Total items sold:      %d               ",numItems);
        printf("\n| Total revenue:         Php %5.2f        ",rev);
        printf("\n==========================================");
        printf("\n| [ 1 ]    Display product list          |");
        printf("\n| [ 2 ]    Display customer list         |");
        printf("\n| [ 3 ]    Add product                   |");
        printf("\n| [ 4 ]    Add customer                  |");
        printf("\n| [ 5 ]    Reload balance                |");
        printf("\n| [ 6 ]    Sort products by price        |");
        printf("\n| [ 7 ]    Process an order              |");
        printf("\n| [ 8 ]    Get items to restock          |");
        printf("\n| [ 9 ]    Display items to restock      |");
        printf("\n| [ 0 ]    Exit                          |");
        printf("\n==========================================");
        printf("\n\nYour Choice: ");

        fflush(stdin);
        scanf("%c", &choice);
        
        switch (choice){
        case '1':
			displayProductList(PL);
            break;
        case '2':
			displayCustomerList(CL);
			break;
        case '3':
        	// Change the condition below to trigger the following statement if the product list is full
        	if(PL.count >= MAX){
        		printf("\n ERROR: List out of space!\n");
			}else{
	        	printf("\n Enter new product ID:");
	        	fflush(stdin);
	        	scanf("%s",tempProd.ID);
	        	printf("\n Enter new product name:");
	        	fflush(stdin);
				scanf("%s",tempProd.name);
				printf("\n Enter new product price:");
	        	fflush(stdin);
				scanf("%f",&tempProd.price);
				printf("\n Enter new product quantity:");
	        	fflush(stdin);
				scanf("%d",&tempProd.qtyRemaining);
	            // Add the function call for inserting the product into the list
	            addProduct(&PL, tempProd);
	            
	        }
            break;
        case '4':
        	// Change the condition below to trigger the following statement if the customer list is full
        	if(CL.count >= MAX){
        		printf("\n ERROR: List out of space!\n");
			}else{
	        	printf("\n Enter new customer ID:");
	        	fflush(stdin);
	        	scanf("%s",tempCust.ID);
	        	printf("\n Enter new customer name:");
	        	fflush(stdin);
				scanf("%s",tempCust.name);
				tempCust.balance = 0.0;
	            // Add the function call for inserting the customer into the list
	            addCustomer(&CL, tempCust);
	            
	        }
            break;
        case '5':
        	printf("\n Enter customer ID to reload:");
        	fflush(stdin);
        	scanf("%s",tempCustID);
        	// Change the condition below to trigger the following statement if the customer ID inputted does not exist in the list
        	if(findCustomer(CL, tempCustID) == FALSE){
        		printf("\n ERROR: Customer not found!\n");
			}else{
				printf("\n Enter amount to reload:");
	        	fflush(stdin);
				scanf("%f",&tempVal);
	            reloadBalance(&CL,tempCustID,tempVal);
	            bal += tempVal;
			}
            break;
        case '6':
            sortProductList(&PL);
            break;
		case '7':
			printf("\n Enter customer ID:");
        	fflush(stdin);
        	scanf("%s",tempCustID);
        	printf("\n Enter product ID:");
        	fflush(stdin);
			scanf("%s",tempProdID);
			printf("\n Enter quantity to order:");
        	fflush(stdin);
			scanf("%d",&tempQty);	
			// Uncomment and complete the code fragment below by adding the function call for processing the order.
				 
            tempOrder = processOrder(&CL,&PL,tempCustID,tempProdID,tempQty);
            numItems+=tempOrder.actualQty;
            rev+=tempOrder.totalPrice;
            switch(tempOrder.status){
            	case SUCCESS: printf("\n Order successful!"); break;
            	case OUT_OF_BAL: printf("\n Error: Insufficient balance!"); break;
            	case OUT_OF_STOCK: printf("\n Error: Item out of stock!"); break;
            	case ERROR: printf("\nError: Item or customer not found!"); break;
			}
			
			
            break;
        case '8':
        	// Uncomment and complete the function call below for getting the items to restock
		
			toRestock = getItemsToRestock(&PL);

			break;
		case '9':
			// Uncomment the line below when the function for getting items to restock is finished.
			 displayProductList(toRestock);
            break;
		case '0':
            printf("\nPress any key to exit program...");
            break;
        default:
            printf("\nInvalid Choice - Please use digits only");
            break;
        }

		if(choice != '0'){
			printf("\n\nPress any key to continue...");   
		}
		fflush(stdin);
		getch();
	}while(choice!='0');
	
	return 0;
}

customerList initCustomerList(){
	//initializes the customer list
	customerList CL = 
	{
	{{"111111","Customer 1",0.0},
	 {"222222","Customer 2",50.0},
	 {"333333","Customer 3",150.0},
	 {"444444","Customer 4",250.0},
	 {"555555","Customer 5",0.0},
	 {"666666","Customer 6",50.0},
	 {"777777","Customer 7",150.0},
	 {"888888","Customer 8",250.0},
	}
	,8};
	return CL;
}

productList initProductList(){
	//initializes the product list
	productList PL = 
	{
	{{"111111","Product 1",20.0,5},
	 {"222222","Product 2",50.0,5},
	 {"333333","Product 3",70.0,5},
	 {"444444","Product 4",100.0,5},
	 {"555555","Product 5",10.0,5},
	 {"666666","Product 6",40.0,5},
	 {"777777","Product 7",60.0,5},
	 {"888888","Product 8",150.0,5},
	}
	,8};
	return PL;
}

void displayProductList(productList PL){
	int x;
	int count = PL.count;
	system("cls");
	printf("\nNumber of products: %d\n",count);
	for(x=0;x<count;x++){
		printf("\n %s \t %s \t %7.2f \t Remaining: %d",PL.prod[x].ID,PL.prod[x].name,PL.prod[x].price,PL.prod[x].qtyRemaining);
	}
}

void displayCustomerList(customerList CL){
	int x;
	int count = CL.count;
	system("cls");
	printf("\nNumber of customers: %d\n",count);
	for(x=0;x<count;x++){
		printf("\n %s \t %s \t %7.2f",CL.cust[x].ID,CL.cust[x].name,CL.cust[x].balance);
	}
}

/* 5 POINTS */
boolean findCustomer(customerList CL, char ID[]){
	//Returns TRUE is the customer record with the given ID is in the list and FALSE otherwise.
	int i;
	for(i=0;i<CL.count&& strcmp(CL.cust[i].ID, ID)!=0;i++){}
	return (i>=CL.count)? FALSE:TRUE;
}

boolean findProduct(productList *PL, char ID[]){
	int i;
	for(i=0;i<PL->count&& strcmp(PL->prod[i].ID, ID)!=0;i++){}
	return (i>=PL->count)? FALSE:TRUE;
}

/* 5 POINTS */
void addProduct(productList *PL, product P){
	//Adds the given product record to the end of the product list only if it has not yet found in the list.
	//Otherwise, if the product record is already present, modify the record by adding the quantity found in the parameter
	//to the quantity recorded in the product list for the given item.
	
	// is there a function that finds the product for us?
	int i;
	if(findProduct(PL,P.ID) == TRUE){
		printf("Product ID already exists! Increasing the quantity instead.");
		for(i=0;i<PL->count&& strcmp(PL->prod[i].ID, P.ID)!=0;i++){}
		PL->prod[i].qtyRemaining += P.qtyRemaining;
		
	}else{
		PL->prod[PL->count++] = P;
	}
	
	// if there is: modify the quantity 
	// else: add it at the end of the list
}

/* 10 POINTS */
void addCustomer(customerList *CL, customer C){
	//Inserts the given customer info into its proper sorted position in the customer list ONLY if
	//the customer info is not yet present in the list. Invoke function findCustomer() whenever necessary.
	if(findCustomer(*CL, C.ID) == FALSE){
		CL->cust[CL->count++]=C;
		printf("Customer succesfully added.");
	}else{
		printf("Customer ID is already taken");
	}
}

/* 10 POINTS */
void reloadBalance(customerList *CL, char ID[], float amount){
	//Adds the given balance into the given customer's record in the customer list.
	//In addition, this function shall output 4 lines of display:
	//(1) the customer name, 
	//(2) the customer's old balance, 
	//(3) the balance added,
	//(4) the customer's new balance.
	int i;
	for(i=0;i<CL->count&& strcmp(CL->cust[i].ID, ID)!=0;i++){}
	printf("Name: %s\n", CL->cust[i].name);
	printf("Old Balance: %.2f\n", CL->cust[i].balance);
	printf("Balance to be added: %.2f\n \n", amount);
	CL->cust[i].balance += amount;
	printf("New amount: %.2f", CL->cust[i].balance);
}

/* 10 POINTS */
void sortProductList(productList *PL){
	//Sorts the product list by increasing order of price.
	int i, j, min;
	product temp;
	
	for(i=0;i<PL->count;i++){
		min = i;
		for(j=i+1;j<PL->count;j++){
			if(PL->prod[j].price < PL->prod[min].price){
				min = j;
			}
		}
		temp = PL->prod[min];
		PL->prod[min] = PL->prod[i];
		PL->prod[i] = temp;
	}
	printf("\nSuccesfully Sorted by Price");
}

/* 30 POINTS */
order processOrder(customerList *CL, productList *PL, char custID[], char prodID[], int qty){
	//Create an order item that records the customer transacting, the product and its quantity being ordered.
	//**Process order only if both product ID and customer ID exist in the lists.
	//**If there's insufficient balance for the requested quantity, do not process the order at all. 
	//**Otherwise, supply whatever is available in stock.
	//Update the affected customer and product records accordingly by decreasing the balance and remaining quantity
	//of the customer and product.
	//Record the actual quantity supplied based on the available stock and the customer's balance.
	//Record the appropriate order status (SUCCESS/OUT_OF_BAL - insufficient balance/OUT_OF_STOCK - incomplete stock/ERROR - item not found)
	//Return the order item to the calling function.
	
	/*
	Test cases:
	1. Customer has enough balance and product has enough quantity - SUCCESS
	2. Customer does not have enough balance but product has enough quantity - OUT_OF_BAL
	3. Customer does not have enough balance and product does not have enough qty - OUT_OF_BAL (Bal is calculated first)
	4. Customer has enough balance but product have zero quantity - OUT_OF_STOCK
	5. Customer has enough balance but requested productQty does not reach product stock - OUT_OF_STOCK but order is still processed
	6. Product and Customer does not exist - ERROR
	*/
	
	int i,j;
	order OTP;
	strcpy(OTP.customerID, custID);
	strcpy(OTP.productID, prodID);
	OTP.orderQty = qty;
	OTP.actualQty = 0;
	OTP.totalPrice = 0;
	
	if(findCustomer(*CL, custID) == TRUE && findProduct(PL, prodID)==TRUE){
		// searches and gets product and customer
		for(i=0;i<PL->count&& strcmp(PL->prod[i].ID, prodID)!=0;i++){}
		for(j=0;j<CL->count&& strcmp(CL->cust[j].ID, custID)!=0;j++){}
		
		// calculates total price
		OTP.totalPrice = qty * PL->prod[i].price;
			
		// checks customer balance
		if(CL->cust[j].balance < OTP.totalPrice){
			OTP.status = OUT_OF_BAL;
			return OTP;
		}
		
		// checks for product quantity
		if(PL->prod[i].qtyRemaining == 0){
			OTP.status = OUT_OF_STOCK;
			return OTP;
		}
		
		if(qty <= PL->prod[i].qtyRemaining){
			OTP.actualQty = qty;
		}else{
			OTP.actualQty = PL->prod[i].qtyRemaining;
		}

		// deduct productQty and customer balance		
		CL->cust[j].balance -= OTP.totalPrice;
		PL->prod[i].qtyRemaining -= qty;
		
		// in case if product qty is subtracted to below zero
		if(PL->prod[i].qtyRemaining < 0){
			PL->prod[i].qtyRemaining = 0;
			OTP.status = OUT_OF_STOCK;
			return OTP;
		}
		
		OTP.status = SUCCESS;
		
	}else{
		OTP.status = ERROR;
	}
	
	return OTP;
}

/* 30 POINTS */
productList getItemsToRestock(productList *PL){
	//Transfers the product records with quantity of 0 to a new list which represents the items need to be restocked
	//Note: Items that are transferred must be deleted from the original product list.
	//Return the newly created list to the calling function.
	productList toRestock;
	toRestock.count = 0;
	int i;
	
	for(i=0;i<PL->count;i++){
		if(PL->prod[i].qtyRemaining == 0){
			toRestock.prod[toRestock.count++] = PL->prod[i];
			deleteProduct(PL, PL->prod[i].ID);
		}
	}
	return toRestock;
}

void deleteProduct(productList *PL, char ID[]){
	int i;
	for(i=0;i<PL->count && strcmp(PL->prod[i].ID, ID) != 0;i++){}
	i++;
	for(;i<PL->count;i++){
		PL->prod[i-1] = PL->prod[i];
	}
	PL->count--;
}
