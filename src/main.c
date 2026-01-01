#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

enum EmployeeType {
	SALARY,
	HOURLY
};

struct Employee {
	char id[16];
	char name[32];
	char SSN[11];
	char address[128];
	float pay;
	enum EmployeeType type;
};

struct Account {
	char id[16];
	char name[32];
	char EIN[10];
	char address[128];
	struct Employee employees[128];
	uint8_t employeeCount = 0;
};

// I know this is inefficient, but I am too lazy to do anything but a brute-force approach
struct Employee* getEmployee(struct Employee* employees, char* id) {
	for (int i=0;i<employeeCount;i++) {
		if (!strcmp(employees[i]->id, id)) {
			return employees[i];
		}
	}
	return NULL;
}

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
	char acctEIN[11];
	char acctAddr[128];
	char acctAddress[128];
	char absLoc[128];
	char emp[16];
	char empName[32];
	char empAddr[128];
	char empPayStr[16];
	char *empPayStrEndPtr;
	float empPay;
	char empType[6];

	char buf[1];

	int acctInputLoop = 1;
	int acctCreationLoop = 1;
	int mainLoop = 1;
	int empLoop = 1;
	int empCreationLoop = 1;
	int empPayLoop = 1;

	struct Account account;
	struct Employee* employee;

	// Sets absLoc
	strcpy(absLoc, argv[0]);
	removePayrollCLI(absLoc);

	while (acctInputLoop) {
		printf("Input account id: ");
		memset(acct, '\0', sizeof(acct)); // Clears buffer
		scanf("%s", &acct);
		sprintf(acctAddr, "%s/data/%s->dat", absLoc, acct);
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
					strcpy(account->name, acctName);
					printf("Enter the EIN of the account (XX-XXXXXXX): ");
					memset(acctEIN, '\0', sizeof(acctEIN)); // Clears buffer
					scanf("%s", &acctEIN);
					strcpy(account->EIN, acctEIN);
					printf("Enter the address of the account: ");
					memset(acctAddress, '\0', sizeof(acctAddress)); // Clears buffer
					scanf("%s", &acctAddress);
					strcpy(account->address, acctAddress);
				}
				else if (buf[0] != 'N' && buf[0] != 'n') {
					acctCreationLoop = 1;
					printf("\"%s\" was not understood-> Would you like to create that account? [Y/N]: ", buf);
				}
			}
		}
		else {
			closeFile(fPtr);
			getAccount(account, acctAddr);
		}
		mainLoop = 1;
		while (mainLoop) {
			printf("What do you want to do?\n\t1-> Add new payroll batch\n\t2-> Edit/print old payroll sheets->\n\t3-> Edit/add employees->\n\t4-> View account info->\n\t5-> Save and exit->\n\t6-> Quit->\n[1, 2, 3, 4, 5, or 6]: ");
			memset(buf, '\0', sizeof(buf)); // Clears buffer
			scanf("%s", &buf);
			if (buf[0] == '1') {
			} else if (buf[0] == '2') {
			} else if (buf[0] == '3') {
				empLoop = 1;
				while (empLoop) {
					printf("Enter the employee's ID (enter '?' to list all employees): ");
					memset(emp, '\0', sizeof(emp)); // Clears buffer
					scanf("%s", &emp);
					employee = getEmployee(account->employees, emp);
					if (employee == NULL) { 
						printf("That employee was not found! Would you like to create it? [Y/N]: ");
						empCreationLoop = 1;
						while (empCreationLoop) {
							memset(buf, '\0', sizeof(buf)); // Clears buffer
							scanf("%s", &buf);
							empCreationLoop = 0;
							if (buf[0] == 'Y' || buf[0] == 'y') { 
								employee = account->employees[account->empCount];
								printf("Enter the employee's name: ");
								memset(empName, '\0', sizeof(empName)); // Clears buffer
								scanf("%s", &empName);
								strcpy(employee->name, empName);
								printf("Enter the employee's SSN (XXX-XXX-XXXX): ");
								memset(empSSN, '\0', sizeof(empSSN)); // Clears buffer
								scanf("%s", &empSSN);
								strcpy(employee->SSN, empSSN);
								printf("Enter the employee's address (enter '^' to use account's address): ");
								memset(empAddr, '\0', sizeof(empAddr)); // Clears buffer
								scanf("%s", &empAddr);
								strcpy(employee->address, empAddr);
								empPayLoop = 1;
								while (empPayLoop) {
									printf("Enter the employee's pay (USD): ");
									memset(empPayStr, '\0', sizeof(empPayStr)); // Clears buffer
									scanf("%s", &empPayStr);
									empPay = strtof(empPayStr, &empPayStrEndPtr);
									if (*empPayStrEndPtr == '\0') {
										employee->pay = empPay;
										empPayLoop = 0;
									} else {
										printf("\"%s\" was not recognized! ", empPayStrEndPtr);
									}
									printf("Enter the employee's type [S(alary)/H(ourly)]: ");
									memset(empType, '\0', sizeof(empType)); // Clears buffer
									scanf("%s", &empType);
									if (empType[0] == 'S' || empType[0] == 's') {
										employee->type = EmployeeType->SALARY;
									} else if (empType[0] == 'H' || empType[0] == 'h') {
										employee->type = EmployeeType->HOURLY;
									}
								}
							}
						}
					}

			} else if (buf[0] == '4') {
			} else if (buf[0] == '5') {
				printf("Saving account->->->\n");
				saveAccount(account, acctAddr);
				mainLoop = 0;
			} else if (buf[0] == '6') {
				printf("Quitting->->->\n");
				return 0;
			} else {
				printf("\"%s\" was not understood-> ", buf);
			}
		}
	}
}
