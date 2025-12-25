#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* f_ptr;
	char acct[16];
	char acct_addr[46];
	char acct_name[32];

	char buf[1];

	int acct_input_loop = 1;
	int acct_creation_loop = 1;

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
					printf("Enter the EIN of the account: ");
					memset(acct_name, '\0', sizeof(acct_name)); // Clears buffer
					scanf("%s", &acct_name);
					printf("Enter the address of the account: ");
					memset(acct_name, '\0', sizeof(acct_name)); // Clears buffer
					scanf("%s", &acct_name);
				}
				else if (buf[0] != 'N' && buf[0] != 'n') {
					acct_creation_loop = 1;
					printf("\"%s\" was not understood. Would you like to create that account? [Y/N]: ", buf);
				}
			}
		}
	}
}
