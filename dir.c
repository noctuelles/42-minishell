#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define CURRENT_DIR "."
#define NO_MATCHE   "no matches found"

int main(void)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*test;
	char			dirtest[1000];

	getcwd(dirtest, 1000);
	printf("cur dir : %s\n", dirtest);
	dir = opendir(CURRENT_DIR);
	if (!dir)
	{
		perror("opendir");
		return (1);
	}
	errno = 0;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (errno == 0)
		{
			if (dirent->d_name[0] != '.')
			{
				if (dirent->d_type != DT_UNKNOWN)
				{
					test = dirent->d_name;
					puts(dirent->d_name);
				}
			}
		}
		else
		{
			perror("readdir");
			break ;
		}
	}
	closedir(dir);
	return (0);
}
