#include <unistd.h>
#include <stdio.h>
    //  fork() yeni bir sürecin oluşturulmasına neden olur.  Yeni süreç (çocuk süreç)
    //  dışında çağıran sürecin (ana süreç) tam bir kopyasıdır.
    //  aşağıdaki:

    //        - Alt sürecin benzersiz bir süreç kimliği vardır.

    //        - Alt sürecin farklı bir üst süreç kimliğine sahip olması (yani
    //            ana sürecin süreç kimliği).

    //        - Çocuk süreç, ebeveynin tanımlayıcılarının kendi kopyasına sahiptir.
    //            Bu tanımlayıcılar aynı temel nesnelere başvurur, bu nedenle
    //            Örneğin, dosya nesnelerindeki dosya işaretçileri paylaşılır
    //            çocuk ve ebeveyn arasında, böylece bir lseek(2) üzerinde bir
    //            alt süreçteki tanımlayıcı sonraki bir okuma veya
    //            ebeveyn tarafından yazılır.  Bu tanımlayıcı kopyalama aynı zamanda
    //            için standart girdi ve çıktı oluşturmak üzere kabuk
    //            oluşturulan süreçlerin yanı sıra boruları ayarlamak için.

    //        - Alt süreçlerin kaynak kullanımları 0 olarak ayarlanır.
	//			Hata Durumunda -1 döndürür.
	//			Çocuk süreç için 0 döndürür.
	//			Ebeveyn süreç için çocuk sürecin PID'sini döndürür.
// fork() is defined in unistd.h
int	main(void)
{
	pid_t	pid;

	pid = fork();// fork(), çağıran süreci çoğaltarak yeni bir süreç oluşturur
	if (pid == 0)
	{
		// child process
		printf("I am the child process\n");
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);// waitpid() bekleyen bir çocuk sürecin durumunu alır
		// parent process
		printf("I am the parent process\n");
	}
	else
	{
		return (-1);
		// fork() failed
	}
}
