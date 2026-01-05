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
	char SSN[12];
	char address[128];
	float pay;
	enum EmployeeType type;
	float addlDeductions;
	uint8_t active;
	float YTD;
	float OTYTD;
	float grossYTD;
	float netYTD;
	float fedYTD;
	float SSYTD;
	float medYTD;
	float stateYTD;
	float addlYTD;
	float deductYTD;
};

struct Account {
	char id[16];
	char name[32];
	char EIN[11];
	char address[128];
	struct Employee employees[128];
	uint8_t employeeCount;
	uint8_t saveCount;

};

void getStr(char* buffer) {
	memset(buffer, '\0', sizeof(buffer)); // Clears buffer
	while (fgets(buffer, sizeof(buffer), stdin) == NULL || !strcmp(buffer,  "\n")) {}
	buffer[strcspn(buffer, "\n")] = 0;
}

// I know this is inefficient, but I am too lazy to do anything but a brute-force approach
struct Employee* getEmployee(struct Account* account, char* id) {
	for (int i=0;i<account->employeeCount;i++) {
		if (!strcmp(account->employees[i].id, id)) {
			return &account->employees[i];
		}
	}
	return NULL;
}

// Similar to getEmployee()
uint8_t deleteEmployee(struct Account* account, char* id) {
	uint8_t index = account->employeeCount + 1; // Sets to unreachable value
	for (int i=0;i<account->employeeCount;i++) {
		if (!strcmp(account->employees[i].id, id)) {
			index = i;
		}
		else if (index < i) {
			account->employees[i-1] = account->employees[i];
		}
	}
	account->employeeCount--;
	return index<account->employeeCount+1; // Checks if index is the unreachable value or not
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

void getAccount(struct Account* account, char* address) {
	FILE* fPtr = fopen(address, "rb");
	fread(account, sizeof(struct Account), 1, fPtr);
	closeFile(fPtr);
}

void saveAccount(struct Account* account, char* address) {
	account->saveCount += 1;
	FILE* fPtr = fopen(address, "wb");
	fwrite(account, sizeof(struct Account), 1, fPtr);
	closeFile(fPtr);
}

int main(int argc, char **argv) {
	FILE* fPtr;
	char acct[16];
	char acctName[32];
	char acctEIN[10];
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
	char empSSN[11];

	char buf[1];

	struct Employee notNULL;

	int acctInputLoop = 1;
	int acctCreationLoop = 1;
	int mainLoop = 1;
	int empLoop = 1;
	int empCreationLoop = 1;
	int empPayLoop = 1;
	int empMainLoop = 1;

	struct Account account;
	struct Employee* employee;

	// Sets absLoc
	strcpy(absLoc, argv[0]);
	removePayrollCLI(absLoc);

	while (acctInputLoop) {
		printf("Input account id (enter '.' to quit): ");
		getStr(acct);
		if (acct[0] == '.') {
			return 0;
		}
		sprintf(acctAddr, "%s/data/%s.dat", absLoc, acct);
		fPtr = fopen(acctAddr, "r");
		mainLoop = 0;
		if (fPtr == NULL) {
			closeFile(fPtr);
			printf("That account was not found! Would you like to create it? [Y/N]: ");
			acctCreationLoop = 1;
			while (acctCreationLoop) {
				getStr(buf);
				acctCreationLoop = 0;
				if (buf[0] == 'Y' || buf[0] == 'y') { 
					printf("Enter the name of the account: ");
					getStr(acctName);
					strcpy(account.name, acctName);
					printf("Enter the EIN of the account (XX-XXXXXXX): ");
					getStr(acctEIN);
					strcpy(account.EIN, acctEIN);
					printf("Enter the address of the account: ");
					getStr(acctAddress);
					strcpy(account.address, acctAddress);
					account.employeeCount = 0; // Needed bc I cannot set it in the struct
					mainLoop = 1;
				}
				else if (buf[0] != 'N' && buf[0] != 'n') {
					acctCreationLoop = 1;
					printf("\"%s\" was not understood. Would you like to create that account? [Y/N]: ", buf);
				}
			}
		}
		else {
			closeFile(fPtr);
			getAccount(&account, acctAddr);
			mainLoop = 1;
		}
		while (mainLoop) {
			printf("What do you want to do?\n\t1. Add new payroll batch.\n\t2. Edit/print old payroll sheets.\n\t3. Edit/add employees.\n\t4. View account info.\n\t5. Save and exit.\n\t6. Exit without saving.\n[1, 2, 3, 4, 5, or 6]: ");
			getStr(buf);
			if (buf[0] == '1') {
			} else if (buf[0] == '2') {
			} else if (buf[0] == '3') {
				empLoop = 1;
				while (empLoop) {
					printf("Enter the employee's ID (enter '?' to list all employees or enter '.' to exit): ");
					getStr(emp);
					employee = getEmployee(&account, emp);
					if (emp[0] == '.') {
						empLoop = 0;
						employee = &notNULL; // Random non-NULL employee
						empMainLoop = 0;
					}
					else if (emp[0] == '?') {
						for (int i=0;i<account.employeeCount;i++) {
							printf("#. id: name - SSN - address - pay\n");
							printf("%i. %s: %s - %s - %s - %f\n", i+1, account.employees[i].id, account.employees[i].name, account.employees[i].SSN, account.employees[i].address, account.employees[i].pay);
						}
						employee = &notNULL; // Random non-NULL employee
						empMainLoop = 0;
					}
					if (employee == NULL) { 
						printf("That employee was not found! Would you like to create it? [Y/N]: ");
						empCreationLoop = 1;
						while (empCreationLoop) {
							getStr(buf);
							empCreationLoop = 0;
							if (buf[0] == 'Y' || buf[0] == 'y') { 
								employee = &account.employees[account.employeeCount];
								strcpy(employee->id, emp);
								printf("Enter the employee's name: ");
								getStr(empName);
								strcpy(employee->name, empName);
								printf("Enter the employee's SSN (XXX-XX-XXXX): ");
								getStr(empSSN);
								strcpy(employee->SSN, empSSN);
								printf("Enter the employee's address (enter '^' to use account's address): ");
								getStr(empAddr);
								strcpy(employee->address, empAddr);
								empPayLoop = 1;
								while (empPayLoop) {
									printf("Enter the employee's pay (USD): ");
									getStr(empPayStr);
									empPay = strtof(empPayStr, &empPayStrEndPtr);
									if (*empPayStrEndPtr == '\0') {
										employee->pay = empPay;
										empPayLoop = 0;
									} else {
										printf("\"%s\" was not recognized! ", empPayStrEndPtr);
									}
									printf("Enter the employee's type [S(alary)/H(ourly)]: ");
									getStr(empType);
									if (empType[0] == 'S' || empType[0] == 's') {
										employee->type = SALARY;
									} else if (empType[0] == 'H' || empType[0] == 'h') {
										employee->type = HOURLY;
									}
								}
								account.employeeCount += 1;
							}
						}
						empMainLoop = 1;
					} else { // There are probably better ways of doing this but idc
						employee = getEmployee(&account, emp);
						if (employee != NULL) {
							empMainLoop = 1;
						} else {
							empMainLoop = 0;
						}
					}
					while (empMainLoop) {
						printf("What do you want to do?\n\t1. Change id.\n\t2. Change name.\n\t3. Change SSN.\n\t4. Change pay.\n\t5. Delete employee.\n\t6. View info.\n\t7. Exit.\n[1, 2, 3, 4, 5, 6, or 7]: ");
						getStr(buf);
						if (buf[0] == '1') {
							printf("Enter the employee's new id: ");
							getStr(emp);
						} else if (buf[0] == '2') {
							printf("Enter the employee's new name: ");
							getStr(empName);
						} else if (buf[0] == '3') {
							printf("Enter the employee's new SSN: ");
							getStr(empSSN);
						} else if (buf[0] == '4') {
							empPayLoop = 1;
							while (empPayLoop) {
								printf("Enter the employee's new pay (USD): ");
								getStr(empPayStr);
								empPay = strtof(empPayStr, &empPayStrEndPtr);
								if (*empPayStrEndPtr == '\0') {
									employee->pay = empPay;
									empPayLoop = 0;
								} else {
									printf("\"%s\" was not recognized! ", empPayStrEndPtr);
								}
								printf("Enter the employee's new type [S(alary)/H(ourly)]: ");
								getStr(empType);
								if (empType[0] == 'S' || empType[0] == 's') {
									employee->type = SALARY;
								} else if (empType[0] == 'H' || empType[0] == 'h') {
									employee->type = HOURLY;
								}
							}
						} else if (buf[0] == '5') {
							printf("Deleting employee...\n");
							if (deleteEmployee(&account, employee->id)) {
								empMainLoop = 0;
							} else {
								printf("Failed to delete employee!");
							}
						} else if (buf[0] == '6') {
							printf("id:\t\t%s\nname:\t\t%s\nSSN:\t\t%s\npay:\t\t%f\n", employee->id, employee->name, employee->SSN, employee->pay);
						} else if (buf[0] == '7') {
							empMainLoop = 0;
						}
					}
				}

			} else if (buf[0] == '4') {
				printf("%d\n", account.saveCount);
				printf("%s\n", account.name);
			} else if (buf[0] == '5') {
				printf("Saving account...\n");
				saveAccount(&account, acctAddr);
				mainLoop = 0;
			} else if (buf[0] == '6') {
				printf("exiting...\n");
				mainLoop = 0;
			} else {
				printf("\"%s\" was not understood. ", buf);
			}
		}
	}
}
