#include <unistd.h>

int main()
{
	char *str;

	write(2, "nice\n", 5);
	str = NULL;
	str[0] = 'i';
}
