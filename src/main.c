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
		scanf("%s", &acct);
		sprintf(acct_addr, "~/.config/payroll-cli/db/%s.cfg");
		f_ptr = fopen(acct_addr, "r");
		if (f_ptr == NULL) {
			printf("\nThat account was not found! Would you like to create it? [Y/N]: ");
			while (acct_creation_loop) {
				scanf("%s", &buf);
				acct_creation_loop = 0;
				if (buf == 'Y' || buf == 'y') {
					printf("\nEnter the name of the account: ");
					scanf("%s", &acct_name);
				}
			}
		}
	}
}
