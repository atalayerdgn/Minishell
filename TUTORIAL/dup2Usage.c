#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
// dup2() is defined in unistd.h
// int	dup2(int oldfd, int newfd);
// dup2() newfd'yi oldfd'nin kopyası yapar, gerekirse önce newfd'yi kapatır.
// newfd, oldfd'nin kopyası olarak ayarlanır ve oldfd'nin önceki değeri döndürülür.
// Eğer oldfd geçerli bir dosya tanımlayıcısı değilse, dup2() -1 döndürür ve errno'yu ayarlar.
// Eğer oldfd geçerli bir dosya tanımlayıcısıysa ve newfd oldfd'ye eşitse, dup2() newfd'yi kapatır ve -1 döndürür.
// Eğer oldfd geçerli bir dosya tanımlayıcısıysa ve newfd oldfd'ye eşit değilse, newfd'yi kapatır ve oldfd'nin kopyasını yapar.
int	main()
{
	pid_t	pid;
	int		fd;

	fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		// child process
		dup2(fd, 1);
		printf("I am the child process\n");
	}
	else if (pid > 0)
	{
		// parent process
		printf("I am the parent process\n");
	}
	else
	{
		return (-1);
		// fork() failed
	}
}
