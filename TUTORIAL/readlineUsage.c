// readline terminalden bir satır okuyacak ve onu döndürecek.
// İşi bittiğinde çağıran serbest bırakmalıdır.  Döndürülen satırda
// son satır çizgisi kaldırılır, böylece yalnızca satırın metni kalır.
// Eğer EOF görülürse ve hiçbir karakter okunmazsa, NULL döndürülür.
// Eğer bir hata olursa, NULL döndürülür.
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;
	line = readline("prompt> ");
	if (line == NULL)
	{
		// EOF or error
		return (1);
	}
	printf("line: %s\n", line);
	free(line);
	return (0);
}

