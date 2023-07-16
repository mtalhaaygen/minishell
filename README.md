# BROlarla MİNİSHELL

- herkes ayrı brachlerde çalışacak, anlamlı parçaları main brache merge edeceğiz.
- README.md içerisine konu hakkında notlar alıp, kaynak linkleri eklersek hepimiz yararlanmış oluruz.
- birbirimizin yazdıklarından ilham almış olacağız.
- ilerleyen zamanlarda proje bölümlere ayrılıp, herkese farklı görev verilebilir.
- Akşamları dc girip, muhabbet etsek fena mı olur, ortak vscode dan kod yazarız hem :D

> Saygılarımla maygen


# Kaynaklar

* https://heliotrope-garment-fdf.notion.site/Minishell-45aa5a4972724576ae21384eac3221cf güzel kaynak.
* https://www.youtube.com/playlist?list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW
* https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
* https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
* https://cdn.intra.42.fr/pdf/pdf/93003/en.subject.pdf (proje pdfi)
# MINISHELL
Bu projede amaç kendi shell imizi oluşturmak.
Shell, bir kullanıcı ile bir işletim sistemi çekirdeği arasında bir arayüz sağlayan bir programdır. Komutları alır, bunları işler, sonuçları görüntüler ve kullanıcıdan yeni komutları bekler. 
Shell, komutları yorumlar, işletim sistemi tarafından sağlanan kaynaklara erişim sağlar ve kullanıcıya geri bildirimde bulunur.
Temel işlevleri şu şekildedir;
- Dosya veya dizin oluşturma, silme, okuma, yazma, sıralama
- tarih ve zaman kontrolü (örnek komutlar `date +%d_%m_%Y` yada `date +"Ay:%m / Yıl:%y"`)
- kullanıcı işlemleri (kullanıcı oluşturma, güvenlik politikasına göre kullanıcıları yönetme)
- Kullanılabilir ve boş hafızayı öğrenme (free)
- Yerel veya uzak sunucular hakkında bilgi edinme
- otomasyon sağlama (crontab)
gibi bir dizi görevi gerçekleştirmemize izin verir.

Birçok farklı çeşidir var;
Bourne Again Shell (bash) <br>
C Shell (csh) <br>
Korn Shell (ksh) <br>
Z Shell (zsh) <br>
Command Prompt (cmd) <br>
PowerShell <br>

Linux'ta her şey bir dosyadır; donanım aygıtları da öyle. USB girişleri, seri ve paralel portlar, depolama ortamları, CD-ROM'lar vb... Bütün aygıtlar /dev klasörü altında tutulan dosyalardan ibarettir. Aynı şekilde her bir komutta bir dosya olarak /bin klasörünün içinde bulunur. 

## Projenin isterleri
- Output: minishell
- izin verilen fonksiyonlar ;
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write
access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit
getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty 
ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
- Yeni bir komut beklerken bir komut istemi görüntülenmeli
- Bir çalışma geçmişi olmalı (history)
- Doğru yürütülebilir dosyayı arayın ve başlatın (PATH değişkenine göre veya göreli veya mutlak bir yol kullanarak).
- Sadece bir tane global değişken kullanın. Bunu düşün. Amacını açıklamanız gerekecek.
- Kapanmamış alıntıları veya \ (ters eğik çizgi) veya ; gibi konunun gerektirmediği özel karakterleri yorumlamayın.
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- implements redirections ('<', '<<', '>>', '>')
- implements pipes; Ardışık düzendeki her komutun çıktısı, bir sonraki komutun girişine bir pipe aracılığıyla bağlanır.
- Environment variable ları ($ ardından bir karakter dizisi gelir) yönetin. which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- ctrl-C(yeni satıra geçer) ctrl-D(minishelli kapatır) ctrl-\ (hiçbirşey yapmaz) işlemlerini tanımlayın
- minishell'iniz şu komutları uygulamalıdır (-n argümanıyla echo, yalnızca göreli veya mutlak yolu olan cd komutu, argümansız olan komutlar; pwd, export, unset, env, exit)
- readline işlevi bellek sızıntılarına sebep olur, bunlar göz ardı edilecek

## Kavramlar
### Redirects (yönlendirme karakterleri)
Komut satırında çalıştırılan her program belirli veri akışına sahiptir;

- STDIN (file descriptor 0): Standart giriş, çalıştırılan program için gerekli girdiler.
- STDOUT (file descriptor 1): Standart çıktı, program tarafından ekrana ve kullanıcıya iletilen veri.
- STDERR (file descriptor 2): Standart hata, programın oluşturduğu ve yansıtabildiği terminal varsayılan hataları.

Output'u yeniden yönlendirmenin birden çok yolu vardır. 

> **'>'**	dosya oluşturulmadıysa dosyayı oluşturur, dosyanın içeriğinin üzerine yazar. Dosyayı açarken open() fonksiyonunda flag olarak ***O_TRUNC*** kullanmalıyız, bu dosyanın içeriğinin silinmesine neden olur
```shell
$ echo deneme > talha   
$ cat talha 
deneme
```

> **'>>'**	dosya oluşturulmadıysa dosyayı oluşturur, içeriği silmeden dosyanın sonuna yazar. Dosyayı açarken open() fonksiyonunda flag olarak ***O_APPEND*** kullanmalıyız, bu dosyaya yapılan tüm yazmaların dosyanın sonunda yapılmasını sağlar
```shell
$ cat talha
deneme
$ echo deneme basarili >> talha
$ cat talha
deneme
deneme basarili
```
> **'<'**	dosyadan veriyi girdi olarak alma
```shell
$ cat > talha
selamın aleyküm
aleyküm selam
^C
$ cat < talha
selamın aleyküm
aleyküm selam
```

> **'<<'**	(heredoc) shell scriptleri yazarken tee , cat veya sftp gibi etkileşimli bir komuta çok satırlı bir metin veya kod bloğu geçirmeniz gereken bir durumda olabilirsiniz. Bash ve Zsh gibi diğer shelllerde, bir Here document (Heredoc), bir komuta birden fazla giriş satırı geçirmenize izin veren bir yeniden yönlendirme türüdür.

```Shell
$ cat <<EOF
This is a heredoc string.
It can contain multiple lines.
EOF
```

![fd'yi değiştirmek!](https://heliotrope-garment-fdf.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F94c75a67-4cd4-436c-b20c-f7461a20d538%2Fmain.png?id=62511366-ded2-439b-b30f-61aced34c962&table=block&spaceId=e9825bf3-7545-4a15-9867-eda0ee1ebd06&width=1920&userId=&cache=v2 "dup")
bu yönlendirmeler kullanılırken stdout'a yazdırmak yerine dup, dup2 gibi fonksiyonlarla STDOUT (file descriptor 1)'i dosyanın fd si ile değiştirebiliriz.
```C
    int dup(int oldfd);
    int dup2(int oldfd, int newfd);

```
##### STDOUT'u yeniden yönlendirme
```Shell
$ ls file* > my_stdout.txt # stdout'u bir dosyaya yönlendirdik

$ cat my_stdout.txt 
file1.txt
file2.txt
file3.txt

```
##### STDERR'yi yeniden yönlendirme
![STDERR'u yeniden yönlendirme!](https://www.redhat.com/sysadmin/sites/default/files/styles/embed_large/public/2022-04/Redirect-error.png?itok=xJ2zUY8a "STDERR")

##### STDOUT ve STDERR'yi aynı dosyaya gönderme
`2>&1` yapısı, "STDERR'yi STDOUT'u gönderdiğiniz yere gönderin" anlamına gelir.
```Shell
$ ls file* non-existing-file* > my_consolidated_output.txt 2>&1

$ cat my_consolidated_output.txt 
ls: cannot access 'non-existing-file*': No such file or directory
file1.txt
file2.txt
file3.txt
```
##### STDOUT'u yeniden yönlendirin ancak dosyanın sonua ekleyin
```Shell
$ echo "Adding stuff to the end of a file" >> my_output.txt

$ cat my_output.txt 
file1.txt
file2.txt
file3.txt
Adding stuff to the end of a file
```
##### Başka bir komuta veya hiçbir yere yönlendirme
Yukarıdaki örnekler çıktının bir dosyaya yönlendirilmesini kapsar, ancak çıktıları pipe diğer işlemlere veya dev/null'a da yönlendirebilirsiniz. dev/null a yönlendirirsen çıktı hiçbiryere yazılmaz
```Shell
ps -ef | grep chrome | grep -v grep | wc -l
```
pipe detaylı şekilde aşağıda incelendi

<hr>

### Pipes

Her hangi bir komut stdout'a bir şey basıyorsa bunları pipe sayesinde başka bir komutun stdin a aktarabiliriz. Örnekler;
```shell
$ cat my.txt | wc -l
$ ls -la | grep Makefile
$ cat Makefile | grep -i re --color
$ ps aux | grep minishell
```

Birde pipe() fonksiyonu var, ona fonksiyonlar kısmında değindik.
<hr>

### errno

Errno (error number), bir program veya sistem çağrısı sırasında oluşan hata durumlarını tanımlamak için kullanılan bir değişkendir. Her hata durumunda, sistem veya işletim sistemi bir hata kodu döndürür ve bu kod, errno değişkeninde saklanır.

Bu hata kodları, genellikle sistem veya işletim sistemi tarafından tanımlanmış olan standart hata kodlarıdır. Örneğin, Linux sistemlerinde, errno değişkeni "errno.h" başlıklı bir dosyada tanımlanmıştır ve bu dosya içinde hata kodları ve tanımları için makrolar tanımlanmıştır.

Errno değişkeni, genellikle C ve C++ gibi düşük seviyeli programlama dillerinde kullanılır, ancak diğer dillerde de kullanılabilir. Örneğin python'da errno adında bir modül vardır ve işletim sistemi tarafından döndürülen hata kodlarını okumak için kullanılabilir.

********************errno = 126;********************

126 exit kodu, bir Unix veya Linux sisteminde bir komutun çalışması için gerekli olan yetkiye sahip olmadığını gösterir. Bu, genellikle "permission denied" (izin reddedildi) hatasıyla ilişkilendirilir

********************errno = 258;********************

"çalışan bir işlem var" hatasını gösteren bir hata kodudur. Bu hata kodu, genellikle bir işletim sistemi çağrısı sırasında oluşur ve bir programın bir işlemi başlatma çağrısı yaparken çalışan bir işlem olduğunu gösterir.

************************errno = 127;************************

127 exit kodu, bir Unix veya Linux sisteminde belirtilen komutun bulunamadığını gösterir. Bu, genellikle "command not found" (komut bulunamadı) hatasıyla ilişkilendirilir. Bu exit kodu, komutu çalıştıran shell veya terminal tarafından döndürülür.

********************errno = 1;********************

1 exit kodu, bir Unix veya Linux sisteminde bir komutun veya programın hata ile sonlandığını gösterir. Bu exit kodu genellikle bir hata mesajı ile birlikte döndürülür ve programın beklenmedik bir şekilde sonlandığını gösterir.
<hr>

### Environment variables
Ortam değişkenleri, sistem veya uygulama tarafından kullanılan değerleri içerir. Tıpkı makrolar gibi tanımlanır. `env` komutu ile sistemdeki tüm bu değişkenleri görebiliriz. Yine bu komut ile ortam değişkenlerinin değerlerini değiştirebiliriz.
`env PATH=/new/path example`
PATH ortam değişkeni, sistem tarafından çalıştırılacak programların aranacağı klasörleri belirtir.
PATH değişkenini görüntülemek için;
````shell
echo $PATH
````
HOME, PATH, LOGNAME gibi envlerin anlamları standarttır. Bu onları daima ortam değişkenleri olarak belirtilebileceği anlamına gelmez; sadece bu değişkenlerle belirtildiklerinde hep aynı anlama gelirler. Bu ortam değişkenlerinin isimlerini başka amaçlarla kullanmayı denememelisiniz.
 
<hr>

### Sinyaller hakkında
**SIGINT:**
SIGINIT, Unix ve Linux işletim sistemlerinde bir sinyaldir ve “Interrupt” (Kesinti) anlamına gelir. Genellikle kullanıcının klavyedeki “CTRL+C” tuş kombinasyonunu basması durumunda oluşturulur ve çalışan bir işlemi veya komutu kesmeye yarar. Bir işlem SIGINT sinyalini alırken, kontrollü bir şeklilde kendini sonlandırması beklenir, kaynakları serbest bırakır ve açık dosyaları ve bağlantıları kapatır. 
<br>

**SIG_IGN**:

SIG_IGN Unix ve Linux işletim sistemlerinde "ignore" (yoksay) anlamına gelen bir sabittir. İşaretleri işleme fonksiyonlarında bir programın belirli bir sinyali yoksayacağını belirtmek için özel bir değer olarak kullanılır.
<br>

**SIGQUIT**:
SIGINT’e göre, kaynakları temizlemek ve açık dosyaları veya bağlantıları kapatmak için izin vermeyen SIGQUIT, işlemi hemen sonlandırmak için tasarlandı.
Aşağıda bu sinyallerin işlevinin yeniden düzenlenilmesi gösteriliyor.
```C
#include <signal.h>

void sigint_handler(int signum)
{
    printf("SIGINT alındı, kapatılıyor...\n");
    exit(0);
}

void sigquit_handler(int signum)
{
    printf("SIGQUIT alındı, sonlandırılıyor...\n");
    exit(3);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler2);
    signal(SIGKILL, SIG_IGN); // SIGKILL sinyali gelirse bu durum yok sayılacak

    // Programın geri kalanı burada...
}
```
<hr>
### Temel linux komutları

**1. man :** man ile kullanımını hatırlayamadığınız yada öğrenmek istediğiniz aşağıdaki konularda bilgi edinebilirsiniz.
        <ul>
            <li> Executable programs or shell commands </li>
            <li> System calls (functions provided by the kernel) </li>
            <li> Library calls (functions within program libraries) </li>
            <li> Games </li>
            <li> Special files (usually found in /dev) </li>
            <li> File formats and conventions eg /etc/passwd </li>
            <li> Miscellaneous (including macro packages and conventions), e.g. groff(7) </li>
            <li> System administration commands (usually only for root) </li>
            <li> Kernel routines [Non standard] </li>
        </ul>
Örnek kullanımlar;
```shell
man chmod # komut olan chmoda bu şekilde ulaşabiliyoruz
man 2 chmod # for system calls 
man pthread_detach # her zaman kaçıncı bölümü okumak istediğimizi belirtmemize gerek yok bir tane pthread_detach var
man 3 pthread_detach
```
man sayfasının sonundaki `see also` kısmında eğer komut başka bölümlerde varsa orada gösterilir 
```
SEE ALSO
       chmod(2)

       Full documentation <https://www.gnu.org/software/coreutils/chmod>
       or available locally via: info '(coreutils) chmod invocation'

```
man sayfalarında arama yapmak için `/aranacakkelimeler` şeklinde slash karakteri ile arama yapılabilir

**2. cat :** Genelde stdout da bir dosyanın içeriğini görmek için kullanılır. Ancak yalnızca stdout a değil dosyadan dosya içerisinede yazma işlemi gerçekleştirilebilir. Dosyanın içeriğinin üzerinede yazabiliriz, altına eklemede yapabiliriz. Örnekler;
```shell
cat > dosyaadi # yeni bir dosya oluşturur, ve dosyanın içine yazmamıza olanak sağlar ctrl + d ile çıkarsak yazdıklarımız kaydedilmiş olur.
cat talha.txt # dosya içeriğini stdout a yazar
cat dosyaadi1 dosyaadi2> dosyaadi3 # iki dosyayı (1 ve 2) birleştir ve sonucu yeni bir dosyada (3) depolar
cat dosyadi | tr a-z A-Z >sonuc.txt # bir dosyayı büyük veya küçük karakterli olarak değiştirmek için
cat dosya1 >> dosya2 # dosya2 nin sonuna dosya1 i yazar
cat -n deneme.txt # numaralı şekilde dosya içeriğini stdout a yazar
```
**3. grep :** dosyaların içeriklerini aramak için kullanılır. grep ve regex birlikte çok daha güçlü
```shell
grep talha minishell/deneme.c # deneme.c içerisinde "talha" ile birebir eşleşen satırları ekrana basar
grep -i talha minishell/deneme.c # deneme.c içerisinde "talha" ile eşleşen (-i parametresinden dolayı küçük büyük harf farketmez) satırları ekrana basar
grep -n talha minishell/deneme.c # -n argümanıylada satır numarası ile birlikte basar
grep -C talha gizli.txt # talha kelimesinin bulunduğu satırı altındaki ve üstündeki satırla birlikte basar
grep hello hello.c --color # environment variableda ayarlanmadıysa bu argümanla çıktıyı renklendirebiliriz.
grep func -r minishell # minishell klasörünün tamamında func ile eşleşen satırlar basılır
grep func -r minishell -l # -l argümanıyla satırları değil içeren dosyaları ekrana basar
grep func -r minishell -w # -w argümanıyla sadece eşleşen kelimeler 4 harfli "func" olanlar olacak yani "function" kelimesiyle eşleşmeyecek
grep -i "kahve.*sütsüz" deneme.txt # regex ve grep :D
grep -i "kahve.*sütsüz" deneme.txt -o # o argümanıyla ekrana tüm satır değil eşleşen kısım basılmış olur.
```
**4. find :** bir dizin hiyerarşisindeki dosyaları aramak için kullanılır. Örnekler;
```shell
find Desktop -print # desktoptaki tüm klasör ve dosyaları alt dizinlerle yazdırır -print gibi herhangi bir işlem vermediğimizde -print ön tanımlı olarak kabul ediliyor
find Desktop -name README.md # desktop ve alt klasörlerindeki tüm README dosyalarının yolunu yazdırır
find Desktop -name "*.png" # regex ilede kullanılabilir
find Desktop -path "*/push_swap/*.c" # push_swap adlı klasör varsa içerisindeki C dosyalarının yolunu yazdırır
find Downloads -path "*/wordpress-6.2.2/*" -delete # normalde varsayılan olan -print işlemi yerine -delete işlemi ile sildik
find Desktop -type f # yada -type d ile dosya yada klasör olarak sınırlandırabiliyoruz
find Desktop -not -type f # file olmayanları listeledi
find minishell/src -not -name "*.c" -type f #
find libft -name "*.a" -exec mv {} ~/Desktop \; # libftdeki .a uzantılı kütüphane dosyasını masaüstüne taşıdık, std outputa yazdırmak yerine -exec ile devamında gelen komutda '{}' işaretleri arasına bu çıktıyı vermiş olduk
```
**5. locate :** Locate komutu, Linux'ta dosyaları ada göre bulmak için kullanılır. Kullanıcıların erişebileceği en yaygın kullanılan iki dosya arama yardımcı programı vardır, bunlar *find* ve *locate* olarak adlandırılır. locate , find komutundan daha iyi ve daha hızlı çalışır çünkü bir dosya araması başlatıldığında dosya sisteminde arama yapmak yerine bir veritabanına bakar. Bu veritabanı, sisteminizdeki dosyaların bitlerini ve bölümlerini ve bunlara karşılık gelen yolları içerir. Varsayılan olarak, find komutu, veritabanında bulunan dosyaların hala var olup olmadığını kontrol etmez ve ilgili veritabanının en son güncellemesinden sonra oluşturulan dosyaları asla raporlamaz.
```shell

```
**6. cp :**
```shell
 cp ornek.jpg /home/talha/Pictures # ornek.jpg dosyasının Pictures dizininde bir kopyasını oluşturur.
```

**7. top :** Linux üzerinde sistem kaynaklarınızı tüketen yazılımları izlemek için kullanılan en pratik programlardan birisi top programıdır. Program doğrudan CPU kullanımına göre sıralandırılmış sonuçlar döndürür.

**8. ps :**

**9. kill :**

**10. awk :**

## Kullanabileceğimiz Fonksiyonlar

**1. pipe()**
> *prototip : int pipe( int pipefd[2] );*

iki process arasında veri iletişimini iki file descriptor ile sağlar.
parametre olarak verilen fd[2], index 0’da okunan ve index 1’de yazdırılan fd yi tutuyor sahip.
return değeri başarı durumunda 0, hata durumunda ise 1 dir.

Birde codeValut'dan dinlemek isterseniz; [CodeValut / pipe](https://www.youtube.com/watch?v=Mqb2dVRe0uo "C Hub").

```C
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buf[30];

    // Pipe oluşturma
    if (pipe(pipefd) == -1) { // Pipe'a pipefd vererek artık pipefd ile processlerin yazma ve okuma yerlerini kontorl edebiliriz
        fprintf(stderr, "Pipe oluşturulamadı\n");
        return 1;
    }

    // Yeni bir Child process oluşturma
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Child process oluşturulamadı\n");
        return 1;
    }

    if (pid > 0) {
        // Parent processdeyiz
        printf("parent pid:%d",pid);

        // Pipe'ın okuma tarafını kapatma
        close(pipefd[0]);
        // Veri yazma
        char *data = "Merhaba, çocuk!";
        write(pipefd[1], data, strlen(data) + 1);
        close(pipefd[1]);// artık buradan yazacak birşeyimiz olmadığından kapatabiliriz

        // Child processin tamamlanmasını bekliyoruz
        wait(NULL);
    } else if {
        // Child processindeyiz
        printf("child pid:%d",pid);

        // Pipe'ın yazma tarafını kapatma
        close(pipefd[1]);

        // Veri okuma
        read(pipefd[0], buf, sizeof(buf));
        printf("Alınan veri: %s\n", buf);
        close(pipefd[0]);// artık buradan okuyacak birşeyimiz olmadığından kapatabiliriz
    }

    return 0;
}
```
**2 dup2()**
**3 dup()**
**4 ioctl()**
> *prototip : int ioctl(int fildes, unsigned long request, ...);*

ioctl() fonksiyonu, UNIX ve UNIX benzeri işletim sistemlerinde kullanılan bir sistem çağrısıdır. Bu fonksiyon, I/O kontrolü (input/output control) için kullanılır ve genellikle aygıtlarla etkileşimde bulunmak, aygıt sürücülerini yönetmek veya özel işlemler gerçekleştirmek için kullanılır.
Bir hata oluşmuşsa, -1 değeri döndürülür ve hatayı belirtmek için errno ayarlanır.
İşlem, request parametresi ile belirtilen bir isteğe dayanır. Örneğin, Linux kerneli üzerinde çalışan bir karakter aygıt sürücüsünde kullanılan bazı yaygın ioctl istekleri şunlardır:

- FIONREAD: Giriş tamponunda bekleyen okunmamış bayt sayısını almak için kullanılır.
- FIONBIO: Bloklama olmadan giriş/çıkış işlemlerini gerçekleştirmek için soketi ayarlar.
- TIOCGWINSZ: Terminal penceresinin boyutunu almak için kullanılır.
- TIOCSWINSZ: Terminal penceresinin boyutunu ayarlamak için kullanılır.