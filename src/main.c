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

uint16_t getStrLen(char* string) {
	int i;
	for (i=0;string[i]!='\0';i++) {}
	++i;
	return i;
}

void removePayrollCLI(char* arg) {
	uint16_t strLen = getStrLen(arg);
	arg[strLen - 16] = '\0';
}

// Checks to close the file
void closeFile(FILE* fPtr) {if (fPtr != NULL) {fclose(fPtr);}}

void getAccount(struct Account account, char* address) {
	FILE* fPtr = fopen(address, "r");
	fread(&account, sizeof(account), 1, fPtr);
	closeFile(fPtr);
}

void saveAccount(struct Account account, char* address) {
	FILE* fPtr = fopen(address, "w");
	fwrite(&account, sizeof(account), 1, fPtr);
	closeFile(fPtr);
}

int main(int argc, char **argv) {
	FILE* fPtr;
	char acct[16];
	char acctName[32];
	char acctEIN[9];
	char acctAddr[128];
	char acctAddress[128];
	char absLoc[128];

	char buf[1];

	int acctInputLoop = 1;
	int acctCreationLoop = 1;
	int mainLoop = 1;

	struct Account account;

	// Sets absLoc
	strcpy(absLoc, argv[0]);
	removePayrollCLI(absLoc);

	while (acctInputLoop) {
		printf("Input account id: ");
		memset(acct, '\0', sizeof(acct)); // Clears buffer
		scanf("%s", &acct);
		sprintf(acctAddr, "%s/data/%s.dat", absLoc, acct);
		fPtr = fopen(acctAddr, "r");
		if (fPtr == NULL) {
			closeFile(fPtr);
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
		else {
			closeFile(fPtr);
			getAccount(account, acctAddr);
		}
		mainLoop = 1;
		while (mainLoop) {
			printf("What do you want to do?\n\t1. Add new payroll batch\n\t2. Edit/print old payroll sheets.\n\t3. View statistics.\n\t4. Save.\n\t5. Quit.\n[1, 2, 3, 4, or 5]: ");
			memset(buf, '\0', sizeof(buf)); // Clears buffer
			scanf("%s", &buf);
			if (buf[0] == '1') {
			} else if (buf[0] == '2') {
			} else if (buf[0] == '3') {
			} else if (buf[0] == '4') {
				printf("Saving account...\n");
				saveAccount(account, acctAddr);
				mainLoop = 0;
			} else if (buf[0] == '5') {
				printf("Quitting...\n");
				return 0;
			} else {
				printf("\"%s\" was not understood. ", buf);
			}
		}
	}
}
