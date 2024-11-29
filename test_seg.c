#include <unistd.h>

int main()
{
	int i;
	char *str;

	write(2, "nice\n", 5);
	str = NULL;
	i = 0;
	while(str[i])
		i++;
	write(1, "hello_world\n",12); 
}
