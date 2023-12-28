//execve() kullanımı
//int execve(const char *filename, char *const argv[], char *const envp[]);
//execve(), dosya adının işaret ettiği programı çalıştırır. dosya adı ya ikili bir çalıştırılabilir dosya ya da şu biçimde bir satırla başlayan bir komut dosyası olmalıdır:
//filename argümanı, çalıştırılacak programın tam yolunu içermelidir.
//argv argümanı, programın ana() işlevine geçirilecek komut satırı argümanlarının bir dizisidir. argv[0] genellikle programın adıdır. argv[0] NULL olmamalıdır.
//envp argümanı, programın ana() işlevine geçirilecek ortam değişkenlerinin bir dizisidir. envp NULL olmamalıdır.
//Başarı durumunda execve() asla geri dönmez. Eğer başarısız olursa, -1 döndürür ve errno'yu ayarlar.
#include <unistd.h>
#include <stdlib.h>
int	main(int ac, char **av, char **env)
{
	char	*args[] = {"/bin/ls", "-l", NULL};
	execve(args[0], args, env);// execve() dosya adının işaret ettiği programı çalıştırır.
	return (0);
}
