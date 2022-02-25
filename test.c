#include "libft.h"

int main(int argc, char **argv)
{
	char *str = ft_strtrim(argv[1], argv[2]);
	puts(str);
}
