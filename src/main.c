#include <stdio.h>
#include <stdlib.h>

enum EmployeeType {
	SALARY,
	HOURLY
};

struct Employee {
	char id[16];
	char name[32];
	char ssn[9];
	char address[128];
	float pay;
	enum EmployeeType employeeType;
};

int main() {
	FILE* f_ptr;
	char acct[16];
	char acctName[32];
	char acctEIN[9];
	char acctAddr[68];
	char acctAddress[128];

	char buf[1];

	int acctInputLoop = 1;
	int acctCreationLoop = 1;
	int mainLoop = 1;

	struct Employee acctEmployees[128];

	while (acctInputLoop) {
		printf("Input account id: ");
		memset(acct, '\0', sizeof(acct)); // Clears buffer
		scanf("%s", &acct);
		sprintf(acctAddr, "~/.config/payroll-cli/db/%s/acct.dat");
		f_ptr = fopen(acctAddr, "r");
		if (f_ptr == NULL) {
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
					printf("Enter the EIN of the account (DO NOT include the dash): ");
					memset(acctEIN, '\0', sizeof(acctEIN)); // Clears buffer
					scanf("%s", &acctEIN);
					printf("Enter the address of the account: ");
					memset(acctAddress, '\0', sizeof(acctAddress)); // Clears buffer
					scanf("%s", &acctAddress);
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
