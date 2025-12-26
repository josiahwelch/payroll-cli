#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* f_ptr;
	char acct[16];
	char acct_name[32];
	char acct_ein[9];
	char acct_addr[128];

	char buf[1];

	int acct_input_loop = 1;
	int acct_creation_loop = 1;
	int main_loop = 1;

	while (acct_input_loop) {
		printf("Input account id: ");
		memset(acct, '\0', sizeof(acct)); // Clears buffer
		scanf("%s", &acct);
		sprintf(acct_addr, "~/.config/payroll-cli/db/%s.cfg");
		f_ptr = fopen(acct_addr, "r");
		if (f_ptr == NULL) {
			printf("That account was not found! Would you like to create it? [Y/N]: ");
			acct_creation_loop = 1;
			while (acct_creation_loop) {
				memset(buf, '\0', sizeof(buf)); // Clears buffer
				scanf("%s", &buf);
				acct_creation_loop = 0;
				if (buf[0] == 'Y' || buf[0] == 'y') { 
					printf("Enter the name of the account: ");
					memset(acct_name, '\0', sizeof(acct_name)); // Clears buffer
					scanf("%s", &acct_name); 
					printf("Enter the EIN of the account (DO NOT include the dash): ");
					memset(acct_ein, '\0', sizeof(acct_ein)); // Clears buffer
					scanf("%s", &acct_ein);
					printf("Enter the address of the account: ");
					memset(acct_addr, '\0', sizeof(acct_addr)); // Clears buffer
					scanf("%s", &acct_addr);
				}
				else if (buf[0] != 'N' && buf[0] != 'n') {
					acct_creation_loop = 1;
					printf("\"%s\" was not understood. Would you like to create that account? [Y/N]: ", buf);
				}
			}
		}
		while (main_loop) {
			printf("What do you want to do?\n\t1. Add new payroll batch\n\t2. Edit/print old payroll sheets.\n\t3. View statistics.\n[1, 2, 3, or 4]: ");
			memset(buf, '\0', sizeof(buf)); // Clears buffer
			scanf("%s", &buf);
			if (buf[0] == '1') {
			} else if (buf[0] == '2') {
			} else if (buf[0] == '3') {
			} else if (buf[0] == '4') {
			} else {
				printf("\"%s\" was not understood. ", buf);
			}
		}
	}
}
