#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
	

struct Account
{
	char id[12];
	char name[40];
	char ph_no[11];
	float balance;
	char username[40];
	char password[40];
	char pin[5];
};
void create();
void login(struct Account *, int);
void generate_acc(char []);
void display();

void main()
{
	int choice;
	char ch;
	struct Account user;
	do
	{
		printf("Enter 1 to create account\nEnter 2 to login\n\n");
		scanf("%d",&choice);
		__fpurge(stdin);
		switch (choice)
		{
			case 1: 
				create();
				break;
			case 2: 
				login(&user, 0);
				break;
			case 100:
				display();
				break;
			default:
				printf("Invalid choice\n");
		}
		printf("Enter 'y' to continue\nEnter 'n' to exit\n");
		__fpurge(stdin);
		scanf("%c",&ch);
	}while(ch=='y');
}

void create()
{
	FILE *fp;
	struct Account customer;

	fp = fopen("Student.dat","a");            //Statement   1

	if(fp == NULL)
	{
		printf("\nCan't open file or file doesn't exist.");
		exit(0);
	}
	
	char acc_num[12];
	generate_acc(acc_num);
	strcpy(customer.id,acc_num);

	printf("Enter Name : ");
	scanf("%[^\n]s",customer.name);

	printf("Enter 10 digit phone number : ");
	int flag=0;
	do
	{
		scanf("%s",customer.ph_no);
		if (strlen(customer.ph_no)!=10)
		{
			printf("Invalid number, enter again\n");
			continue;
		}
		for(int i=0; i<10; i++)
		{
			if (customer.ph_no[i]<48 || customer.ph_no[i]>57)
			{
				printf("Invalid number, enter again\n");
				flag=1;
				break;
			}
		}
		if (flag==0)
			break;
		else
			flag=0;	
	}while(1);
	
	printf("Enter balance of atleast 10000 : ");
	int fail;
	do
	{
		fail=0;
		if ((scanf("%f", &customer.balance) != 1) || customer.balance<10000)
		{
			printf("Invalid entry. Enter balance again\n");
			fail=1;
			__fpurge(stdin);
		}
	}while(fail==1);
	/*scanf("%f",&customer.balance);
	while(customer.balance<10000)
	{
		printf("Insufficient Balance\n");
		scanf("%f",&customer.balance);
	}*/
	
	printf("Enter username : ");
	scanf("%s",customer.username);
	__fpurge(stdin);
	
	printf("Enter password : ");
	int k;
	do
	{
		k=0;
		scanf("%s",customer.password);
		if(strlen(customer.password)>=8)
			k++;
		for(int i=0; i<strlen(customer.password); i++)
		{
			if (customer.password[i]>=48 && customer.password[i]<=57)
			{
				k++;
				break;
			}
		}
		for(int i=0; i<strlen(customer.password); i++)
		{
			if (customer.password[i]>=65 && customer.password[i]<=90)
			{
				k++;
				break;
			}
		}
		for(int i=0; i<strlen(customer.password); i++)
		{
			if (customer.password[i]>=97 && customer.password[i]<=122)
			{
				k++;
				break;
			}
		}
		for(int i=0; i<strlen(customer.password); i++)
		{
			if (!(customer.password[i]>=48 && customer.password[i]<=57) && !(customer.password[i]>=65 && customer.password[i]<=90) && !(customer.password[i]>=97 && 			customer.password[i]<=122))
			{
				k++;
				break;
			}
		}
		if(k!=5)
			printf("Password too weak. Enter again\n");
		__fpurge(stdin);
	}while(k!=5);
	
	printf("Enter pin : ");
	flag=0;
	do
	{
		scanf("%s",customer.pin);
		if (strlen(customer.pin)!=4)
		{
			printf("Invalid number, enter again\n");
			continue;
		}
		for(int i=0; i<4; i++)
		{
			if (customer.pin[i]<48 || customer.pin[i]>57)
			{
				printf("Invalid number, enter again\n");
				flag=1;
				break;
			}
		}
		if (flag==0)
			break;
		else
			flag=0;	
	}while(1);
	
	printf("Your Account id is: %s\n",customer.id);

	fwrite(&customer,sizeof(struct Account),1,fp);
	printf("\nData written successfully...");

	fclose(fp);	      
}
void login(struct Account *user, int attempts)
{
	FILE *fp;
	char ch;
	char id[12];
	char username[40];
	char password[40];
	//struct Student Stu;
	struct Account customer;
	fp = fopen("Student.dat","r");            //Statement   1

	if(fp == NULL)
	{
                     printf("\nCan't open file or file doesn't exist.");
                     exit(0);
	}
	
	printf("Account number: ");
	scanf("%s",id);
	printf("Username: ");
	scanf("%s",username);
	printf("Password: ");
	scanf("%s",password);
	
	int flag=0;
	while(fread(&customer,sizeof(struct Account),1,fp)>0)
	{
		if(!strcmp(id,customer.id) && !strcmp(username,customer.username) && !strcmp(password,customer.password))
		{
			strcpy(user->id,customer.id);
			strcpy(user->name,customer.name);
			strcpy(user->ph_no,customer.ph_no);
			user->balance = customer.balance;
			strcpy(user->username,customer.username);
			strcpy(user->password,customer.password);
			strcpy(user->pin,customer.pin);
			flag=1;
			break;
		}
                  //printf("\t%s\t%s\t%s\t%f\t%s\t%s\t%s\n",customer.id,customer.name,customer.ph_no,customer.balance,customer.username,customer.password,customer.pin);  
	}
	fclose(fp);	
	if(flag!=1)
	{
		if(attempts>=2)
		{
			printf("Invalid entry.\nToo many attempts\n");
			return;
		}
		printf("Invalid Entry.\nPress 1 to try again\nPress any other key to exit.\n");
		__fpurge(stdin);
		scanf("%c",&ch);
		if (ch=='1')
			login(user,attempts+1);
		return;
	}
	return;
	
}
void generate_acc(char acc_num[12])
{
	FILE *check;
	struct Account customer;
	check = fopen("Student.dat","r");
	if(check == NULL)
	{
                     printf("\nCan't open file or file doesn't exist.");
                     exit(0);
	}
	
	char rand_num[5];
	int num = (rand() % (1000 - 0 + 1));  
	sprintf(rand_num, "%04d", num);
	
	strcpy(acc_num,"AXA2020");
	strcat(acc_num,rand_num);
	while(fread(&customer,sizeof(struct Account),1,check)>0)
		if (!strcmp(acc_num, customer.id))
		{
			fclose(check);
			generate_acc(acc_num);	
		}
	fclose(check);
	return;
}
void display()
{
	FILE *fp;
	struct Account customer;
	fp = fopen("Student.dat","r");           

	if(fp == NULL)
	{
                     printf("\nCan't open file or file doesn't exist.");
                     exit(0);
	}
	
	while(fread(&customer,sizeof(struct Account),1,fp)>0)
	{
                  printf("\t%s\t%s\t%s\t%f\t%s\t%s\t%s\n",customer.id,customer.name,customer.ph_no,customer.balance,customer.username,customer.password,customer.pin);  
	}
	fclose(fp);	
	return;	
}
