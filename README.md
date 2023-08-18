# BROlarla MİNİSHELL
./caf -disu
### YAPILACAKLAR
maygen
- tek node da tek bir redirection çalışıyo
- redirectionlarda nodeları güncelle
- infile ve outfile dosyaları access ile kontrol et
- cat | cat | ls sorulacak
- export unset yapılacak
- builtin executor seg kontrolü
- builtin executor leaks kontrolü

tdemir
-''leaks kontolü
-here leaks kontrolü 
- set ctrl d 
- lexer parser seg kontrolü

kim yaparsa
- $?
- exit bakılcak
- hata mesajları
### TAMAMLANANLAR
- cat < olmayan txt <!-- file acsess ile kontrol edilince düzelecek -->
- ./ ile yada / ile baslayınca farklı bir if ile çalışacak
- builtinler çıktıyı pipe a aktarmıyor
- lexer parser leaks kontrolü
- ""|""
- heredoc
- echo -n seg
- heredoc
## normu düzeltilen dosyalar
Lİb klasörünün tümü ok
parser/env_process.c ok

# freelenecek değerler
free(tokens)

int i = 0;
while(tokens[i].value)
{
    free(tokens[i].value); 
    i++;
}

# MINISHELL
Bu projede amaç kendi shell kabuğumuzu oluşturmak.
Shell, kullanıcı ile işletim sistemi çekirdeği arasında arayüz sağlayan bir programdır. Komutları alır, bunları işler, sonuçları görüntüler ve kullanıcıdan yeni komutları bekler. 
Shell, komutları yorumlar, işletim sistemi tarafından sağlanan kaynaklara erişim sağlar ve kullanıcıya geri bildirimde bulunur. Ayrıca ayrıca if, for, while, fonksiyonlar, değişkenler vb. gibi
programlama yapıları sağlar
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
talhaShell (tsh) <br>
Bunlara ek olarak, çoğu kullanıcı için bilgisayar kullanımını basitleştiren Windows Masaüstü, MacOS Finder veya Linux Gnome ve KDE gibi Grafik sheller de vardır.
Bir shell uygulaması üç bölüme ayrılmıştır; The Parser, The Executor, and Shell Subsystems.
Parser, komut satırını okuyan ve bunları ayrıştırarak bir veri yapısında (struct) tutan yazılım bileşenidir.
Executor, her bir komut için bir process oluşturur. (builtin komutlar hariç) Gerekirse, bir sürecin çıktısını bir sonrakinin girdisine iletmek için pipe() ile bağlantılar oluşturur. Ek olarak, herhangi bir yeniden yönlendirme varsa standart girdiyi, standart çıktıyı ve standart hatayı yeniden yönlendirir. Executor şuna benzer birşey olacak;
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void executeCommand() {
    int ret;
    for (int i = 0; i < _numberOfSimpleCommands; i++) { // kaç tane kod varsa o kadar fork yapılıyor ve exec e gönderiliyor
        ret = fork();
        if (ret == 0) {
            // Child process
            execvp(sCom[i]->_args[0], sCom[i]->_args);
            perror("execvp");
            _exit(1);
        } else if (ret < 0) {
            perror("fork");
            return;
        }
        // Parent shell continues
    }
    if (!background) {
        // Wait for the last process
        waitpid(ret, NULL, 0);
    }
}
```
Shell Subsystem ise env, wildcard, `` (backticks) değerlerinin kullanımını içerir
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

export komutu ile aşağıdaki gibi yeni envler oluşturabiliriz
`export my_env_variable="deneme"`
 
<hr>

### Built-in command
built-in komutlar, shell programının içinde yer alan ve direk olarak çalıştırılabilen yerleşik komutlar olarak tanımlanır. Örneğin, cd, echove pwd gibi komutlar built-in komutlardır. Bu komutlar, çalıştırılmadan önce sistemde ayrı bir program olarak aranmaz, yeni bir process oluşturulması gerekmez ve shell programı tarafından doğrudan işlenirler.
> bash  defines  the  following built-in commands: :, ., \[, alias, bg, bind, break, builtin, case, cd, command, compgen, complete, continue, declare, dirs, disown, echo, enable, eval, exec,  exit,  export,  fc,  fg,  getopts, hash, help, history, if, jobs, kill, let, local, logout, popd, printf, pushd, pwd, read,  readonly,  return,  set,  shift,  shopt,  source, suspend,  test,  times,  trap,  type, typeset, ulimit, umask, unalias, unset, until, wait, while

Built-in komutlarının her birinin çalışmasını biz kendimiz tanımlayacağız çünkü /bin/ içerisinde bu komutlar olmayabiliyor. Biz sadece built-in komutlarından bazılarını işleyeceğiz (echo, cd, pwd, export, unset, env, exit).
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
> * prototip : int dup2(int fildes, int fildes2);*

Bu fonksiyon ile fd lerii değiştirebiliyoruz,
Eğer fildes ve fildes2 eşitse, dup2() fonksiyonu sadece fildes2'yi döndürür; mevcut tanımlayıcı üzerinde başka bir değişiklik yapılmaz.
Ancak, eğer fildes2 tanımlayıcısı zaten kullanılıyorsa, öncelikle sanki bir close(2) çağrısı yapılmış gibi fildes2 tanımlayıcısı serbest bırakılır (dealloke edilir).
"Dealokasyon" terimi, ayrılmış bir kaynağın (bellek, dosya tanımlayıcı, ağ bağlantısı vb.) kullanımdan kaldırılması veya serbest bırakılması anlamına gelir. Kaynakların kullanımı bittikten sonra dealokasyon işlemi gerçekleştirilerek bu kaynaklar sisteme geri verilir.

**3 dup()**
> *prototip : int dup(int fildes);*

Bir fd nin kopyası yeni bir fd oluşturuluyor, oluşturulan bu newfd eski fd kaybolsa bile kullanılabiliyor. 
```C
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd_stdout = dup(STDOUT_FILENO);
    int fdn = open("talha.txt", O_WRONLY);
    dup2(fdn, 1);
    write(1, "xxxxx", 5); // talha.txt nin içine yazacak
    dup2(fd_stdout, 1); // fd_stdout'u tekrardan standart çıkışa yönlendir
    write(1, "talha", 5);
}

```
**4 ioctl()**
> *prototip : int ioctl(int fildes, unsigned long request, ...);*

ioctl() fonksiyonu, UNIX ve UNIX benzeri işletim sistemlerinde kullanılan bir sistem çağrısıdır. Bu fonksiyon, I/O kontrolü (input/output control) için kullanılır ve genellikle aygıtlarla etkileşimde bulunmak, aygıt sürücülerini yönetmek veya özel işlemler gerçekleştirmek için kullanılır.
Bir hata oluşmuşsa, -1 değeri döndürülür ve hatayı belirtmek için errno ayarlanır.
Örnek istekler;

- TIOCGETA: TTY aygıtının özelliklerini (terminal ayarları) almak için kullanılır.
- TIOCSETA: TTY aygıtının özelliklerini ayarlamak için kullanılır.
- TIOCGWINSZ: Terminal penceresinin boyutunu almak için kullanılır.
- TIOCSWINSZ: Terminal penceresinin boyutunu ayarlamak için kullanılır.

ioctl ile oynarken dikkat et!

```c
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main() {
    struct termios term;
    int fd = STDIN_FILENO; // STDIN_FILENO, standart giriş (stdin) dosya tanımlayıcısıdır

    // Terminal ayarlarını al
    if (ioctl(fd, TIOCGETA, &term) == -1) {
        perror("ioctl");
        return 1;
    }

    // ctrl-C, ctrl-D ve ctrl-\ komutlarını değiştir
    term.c_cc[VINTR] = '\n'; // ctrl-C için yeni satır karakteri
    term.c_cc[VEOF] = '\x04'; // ctrl-D için ASCII 4 (End of Transmission, EOT) karakteri
	term.c_cc[VQUIT] = 0; // VQUIT, ctrl-\ için karakter sabiti :D

    // Değiştirilmiş ayarları aygıta uygula
    if (ioctl(fd, TIOCSETA, &term) == -1) {
        perror("ioctl");
        return 1;
    }

    printf("Terminal ayarları değiştirildi.\n");
    printf("Yeni satırda yeni bir bilgi istemi (ctrl-C)\n");
    printf("Shell'den çıkış (ctrl-D)\n");
    printf("ctrl-\\ hiçbir işlem yapmıyor.\n");

    // Kullanıcıdan giriş al ve işle
    char input;
    while (1) {
        read(fd, &input, sizeof(char));
        if (input == '\n') {
            printf("Yeni satırda yeni bir bilgi istemi\n");
        } else if (input == '\x04') {
            printf("Shell'den çıkılıyor.\n");
            break;
        }
    }

    return 0;
}

```

**5 getcwd()**
> *prototip : char *getcwd(char *buf, size_t size);*

Çalışan programın mevcut çalışma dizinini öğrenmek için kullanılır. İlk parametre çalışma dizininin saklanacağı karakter dizisi, diğer parametre bu dizinin size ı dır. Eğer size ı ufak verirsek işlev başarısız olacak ve NULL dönecektir
```C
#include <stdio.h>
#include <unistd.h>
#include <limits.h> // path_max için 

int main() {
    char path[PATH_MAX]; // path_max ile tam size ı alabildik

    char * r = getcwd(path, sizeof(path));
    if (r != NULL)
    {
        printf("Mevcut çalışma dizini: %s\n", r); //bu kullanım saçma path ile aynı adreste tutulacak bir değişken oluşturmamıza gerek yok
        printf("Mevcut çalışma dizini: %s\n", path);
    } else {
        perror("getcwd hatası");
        return 1;
    }

    printf("   r:%p\n", &r);
    printf("path:%p\n", &path);
    return 0;
}
```

**6 chdir()**
> *prototip : int chdir(const char *path);*

Mevcut çalışma dizinini değiştirmek için kullanılır. Parametreye çalışma dizininin ne olmasını istiyorsanız onu verirsiniz. Başarılı sonlanır ise 0, hata durumu oluşursa 1 return eder. 
Örnek kullanım
```C
#include<stdio.h>
 
// chdir function is declared
// inside this header
#include<unistd.h>
int main()
{
    char s[100];
 
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
 
    // using the command
    chdir("/Users");
 
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
 
    // after chdir is executed
    return 0;
}
```

**7 execve()**
> *prototip : int execve(const char *pathname, char *const argv[], char *const envp[]);*

pathname; çalıştırılacak komutun dosya yolu
argv; Çalıştırılacak programın argümanlarını içeren bir karakter dizisi dizisi
envp; Çalıştırılacak programın envlerini içeren bir karakter dizisi dizisi

bu fonk. çalıştırıldığında mevcut processi sona erdirir, pathnamede verilen komutu çalıştırır
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int gc, char**gv) {
	char* home = getenv("HOME");
	if (!home)
		perror("getenv");
	char *const args[] = {"echo", home, "deneme", NULL};
	if (execve("/bin/echo", args, NULL))
		perror("execve");
	return 1;
}
```

**8 readline()**
> *prototip : char *readline(const char *line);*

Aldığı parametreyi (prompt) ekrana basar, kullanıcıdan bir girdi ister ve aldığı girdiyi return eder.
readline kullanılıyorsa mutlaka -ledit yada -lreadline flagleri ile derlenmeli
```C
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
int main() {
    char *input;

    // Prompt'u ayarlayın
    const char *prompt = "Girdi: ";

    // readline işlevini çağırın ve kullanıcının girdisini alın
    input = readline(prompt);

    // Girdiyi değerlendirin ve sonuçları yazdırın
    printf("input: %s\n", input);

    // Girdiyi readline kütüphanesi tarafından ayrılan belleği serbest bırakın
    free(input);
    return 0;
}
```

**9 getenv()**
> *prototip : char *getenv(const char *env_name);*

envlerin tuttuğu veriyi geri döndürür. Kısaca tutulan veriyi string olarak alırsınız.
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path = getenv("PATH");
    if (path != NULL) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH environment variable not found.\n");
    }

    return 0;
}
```

**10 access()**
> *prototip : int access(const char *pathname, int mode);*

dosya sistemine erişim hakkını kontrol etmek için kullanılır. Belirtilen dosyanın var olup olmadığını yada okuma, yazma ve yürütme gibi belirli izinlerinin olup olmadığını kontrol etmek için kullanılabilir.
mode parametresi, erişim izinlerini belirten bir tamsayıdır. Bu tamsayı, R_OK, W_OK, X_OK veya F_OK sembollerini veya bu sembollerin birleşimini içerebilir. Örneğin, R_OK | W_OK dosyanın hem okunabilir hem de yazılabilir olup olmadığını kontrol etmek için kullanılır. 

R_OK: Dosyanın okunabilir (readable) olup olmadığını kontrol eder.
W_OK: Dosyanın yazılabilir (writable) olup olmadığını kontrol eder.
X_OK: Dosyanın çalıştırılabilir (executable) olup olmadığını kontrol eder. Bu genellikle yürütülebilir dosyalar (örneğin, programlar veya betikler) için kullanılır.
F_OK: Dosyanın varlığını kontrol eder.
```c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *file_path = "example.txt";

    if (access(file_path, R_OK | W_OK) == 0) {
        printf("Dosya okunabilir.\nDosya yazılabilir.\n");
    } else {
        if (errno == EACCES) {
            printf("Dosya okunabilir ya da yazılabilir değil, erişim izni yok.\n");
        } else if (errno == ENOENT) {
            printf("Dosya mevcut değil.\n");
        } else {
            perror("access");
        }
    }
    return 0;
}
```
**11 perror()**

```C
returnedPID = fork();
if (returnedPID < 0) /* error in the fork call*/
        perror("oopsy, my fork call failed: ");
//bu, yazdığımız "oopsy, my fork call failed:" şeklindeki mesajı içeren bir satırı ve ardından errno'daki değere karşılık gelen standart bir Unix hata mesajını, örneğin, "Out of memory" yazdıracak. O mesajdan sorunumu çözemezsem (büyük ihtimalle), en azından muhtemelen daha fazla yardım için web'de arama yapabileceğim bazı iyi anahtar kelimeler ve ifadeler bulurum.
```

**12 strerror()**

tıpkı perror gibi hata durumunu basacak lakin biraz daha manuel bir kullanımı var
```C
someErrorCode = pthread_create( ... )
printf(" Damn: %s", strerror(someErrorCode));
// burada someErrorCode dönüş değerini kaydettiğiniz herhangi bir değişkeninizin adıdır 
```

Bu videoda makro olarak harika bir fonksiyon yazılıyor ve sonuçta daha temiz bir kod ortaya çıkıyor [click](https://www.youtube.com/watch?v=IZiUT-ipnj0)
Linux işletim sistemindeki hata numaralarının listesi ve açıklamaları için errno.h dosyasına bak


**14 add_history()**
> *prototip : void add_history(const char *line);*

terminalde yukarı-aşağı ok tuşlarıyla historye ulaşabiliyoruz, bunu add_history komutu ile yapacağız. Aldığı parametreyi historye ekler
```C
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    // Kullanıcıdan girdiyi al
	while (1)
	{
		input = readline("Komut giriniz: ");

		// Girdiyi girdi geçmişine ekle
		add_history(input);

		// Kullanılmayan bellek alanını serbest bırak
		free(input);
	}
	return 0;
}
```

<hr>
fork() fonksiyonu için;

| Dönüş Değeri  | Tanım |
| ------------- | ------------- |
| Negatif değer  | Child process oluşturma başarısız.  |
| Sıfır (0)  | Yeni bir child process oluşturuldu.  |
| Pozitif değer  | Yeni oluşturulan child process'in ID'sini içerir.  |

<hr>

# Kaynaklar

* https://heliotrope-garment-fdf.notion.site/Minishell-45aa5a4972724576ae21384eac3221cf güzel kaynak.
* https://www.youtube.com/playlist?list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW
* https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
* https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
* https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus execvp kaynak.
* [proje pdfi](https://cdn.intra.42.fr/pdf/pdf/93003/en.subject.pdf)
* [exec_tr](https://bilgisayarkavramlari.com/2012/03/13/exec-fonksiyonlari/)
* [Write Your Own Shell (Youtube)](https://youtube.com/playlist?list=PLxIRFba3rzLzxxZMMbrm_-mkI7mV9G0pj)
