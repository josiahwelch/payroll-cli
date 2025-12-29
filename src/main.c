#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum EmployeeType {
	SALARY,
	HOURLY
};

struct Employee {
	char id[16];
	char name[32];
	char ssn[10];
	char address[128];
	float pay;
	enum EmployeeType employeeType;
};

struct Account {
	char id[16];
	char name[32];
	char EIN[10];
	char address[128];
};

void getAccount(struct Account* account, char* address) {
	FILE* fPtr = fopen(address, "r");
	fread(account, sizeof(account), 1, fPtr);
	fclose(fPtr);
}

void saveAccount(struct Account* account, char* address) {
	FILE* fPtr = fopen(address, "w");
	fwrite(account, sizeof(account), 1, fPtr);
	fclose(fPtr);
}

int main() {
	FILE* fPtr;
	char acct[16];
	char acctName[32];
	char acctEIN[9];
	char acctAddr[68];
	char acctAddress[128];

	char buf[1];

	int acctInputLoop = 1;
	int acctCreationLoop = 1;
	int mainLoop = 1;

	struct Account account;

	while (acctInputLoop) {
		printf("Input account id: ");
		memset(acct, '\0', sizeof(acct)); // Clears buffer
		scanf("%s", &acct);
		sprintf(acctAddr, "~/.config/payroll-cli/db/%s/acct.dat");
		fPtr = fopen(acctAddr, "r");
		if (fPtr == NULL) {
			fclose(fPtr);
			free(fPtr);
			printf("That account was not found! Would you like to create it? [Y/N]: ");
			acctCreationLoop = 1;
			while (acctCreationLoop) {
				memset(buf, '\0', sizeof(buf)); // Clears buffer
				scanf("%s", &buf);
				acctCreationLoop = 0;
				if (buf[0] == 'Y' || buf[0] == 'y') { 
					printf("Enter the name of the account: ");
					memset(acctName, '\0', sizeof(acctName)); // Clears buffer
					scanf("%s", &acctName); 
					strcpy(account.name, acctName);
					printf("Enter the EIN of the account (XX-XXXXXXX): ");
					memset(acctEIN, '\0', sizeof(acctEIN)); // Clears buffer
					scanf("%s", &acctEIN);
					strcpy(account.EIN, acctEIN);
					printf("Enter the address of the account: ");
					memset(acctAddress, '\0', sizeof(acctAddress)); // Clears buffer
					scanf("%s", &acctAddress);
					strcpy(account.address, acctAddress);
				}
				else if (buf[0] != 'N' && buf[0] != 'n') {
					acctCreationLoop = 1;
					printf("\"%s\" was not understood. Would you like to create that account? [Y/N]: ", buf);
				}
			}
		}
		while (mainLoop) {
			printf("What do you want to do?\n\t1. Add new payroll batch\n\t2. Edit/print old payroll sheets.\n\t3. View statistics.\n[1, 2, or 3]: ");
			memset(buf, '\0', sizeof(buf)); // Clears buffer
			scanf("%s", &buf);
			if (buf[0] == '1') {
			} else if (buf[0] == '2') {
			} else if (buf[0] == '3') {
			} else {
				printf("\"%s\" was not understood. ", buf);
			}
		}
	}
}
