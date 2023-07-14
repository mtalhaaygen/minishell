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

# MINISHELL
Bu projede amaç kendi shell imizi oluşturmak.
Shell, bir kullanıcı ile bir işletim sistemi çekirdeği arasında bir arayüz sağlayan bir programdır. Temel işlevleri şu şekildedir;
- Dosya veya dizin oluşturma, silme, okuma, yazma, sıralama
- tarih ve zaman kontrolü (örnek komutlar `date +%d_%m_%Y` yada `date +"Ay:%m / Yıl:%y"`)
- kullanıcı işlemleri (kullanıcı oluşturma, güvenlik politikasına göre kullanıcıları yönetme)
- Kullanılabilir ve boş hafızayı öğrenme (free)
- Yerel veya uzak sunucular hakkında bilgi edinme
- otomasyon sağlama (crontab)
gibi bir dizi görevi gerçekleştirmemize izin verir.

Process ve file descriptor hakkında yeni şeyler öğrenilecek.

Minishell sayesinde zamanda yolculuk yapıp Windows olmadığı zamanlarda insanların karşılaştığı sorunlara geri dönebileceksiniz.

## Pipes
her hangi bir komut stdout'a bir şey basıyorsa bunları pipe sayesinde başka bir komutun stdin a aktarabiliriz. Örnekler;
```shell
cat my.txt | wc -l
ls -la | grep Makefile
cat Makefile | grep -i re --color
ps aux | grep minishell
```

## Temel linux komutları
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

**9. awk :**