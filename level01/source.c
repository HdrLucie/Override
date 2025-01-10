int main(void)
{
	int ret;
	int n;
	int *ptr;
	char buffer [64];

	ptr = (int *)buffer;
	for (n = 16; n != 0; n = n + -1) {
		*ptr = 0;
		ptr = ptr + 1;
	}
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(&a_user_name,256,stdin);
	n = verify_user_name();
	if (n == 0) {
		puts("Enter Password: ");
		fgets(buffer,100,stdin);
		n = verify_user_pass(buffer);
		if ((n == 0) || (n != 0)) {
			puts("nope, incorrect password...\n");
			ret = 1;
		}
		else {
			ret = 0;
		}
	}
	else {
		puts("nope, incorrect username...\n");
		ret = 1;
	}
	return ret;
}
