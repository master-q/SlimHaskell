SlimHaskell
===========

GHCがHaskellコードをコンパイルして吐き出すELF実行バイナリを
どこまでダイエットできるのか挑戦してみよう!

FibHs0
------
ダイエットする前のふつーのプログラム

FibHs1
------
ghcコマンドでリンクせずに、gccを使ってリンクするようにした。
その際、リンクオプションを分割してわかりやすくした。
どのオプションを外すとどんなエラーが出るのか試しやすくなった。

FibHs2
------
libHSrts.aライブラリの中で必須と思われるオブジェクトファイルだけを取り出してリンクするようにした。
このソースは
[ghc-arafuraのfeature/slimhaskellブランチ](https://gitorious.org/metasepi/ghc-arafura/commits/feature/slimhaskell)
がないとコンパイルできない。

FibHs3
------
baseパッケージからFloat関連を削除。
libm,librt,libpthreadにリンクしないようになった。
このソースは
[ghc-base-arafuraのfeature/slimhaskellブランチ](https://gitorious.org/metasepi/ghc-base-arafura/commits/feature/slimhaskell)
がないとコンパイルできない。

FibHs4
------
integer-gmpを
[なんちゃってライブラリ](https://gitorious.org/metasepi/integer-fake)
で置き換えた。
libgmpにリンクしないようになった。

FibHs5
------
baseパッケージから必須と思われるオブジェクトファイルだけを取り出してリンクするようにした。
かなりサイズ小さくなった。

FibHs6
------
未定義シンボルをできるかぎり除去した。

~~~
$ ldd FibHs
        linux-vdso.so.1 =>  (0x00007fff813f3000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7493bd3000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f7493f64000)
$ nm FibHs|sort|head -25
                 U __libc_start_main@@GLIBC_2.2.5
                 U bsearch@@GLIBC_2.2.5
                 U calloc@@GLIBC_2.2.5
                 U free@@GLIBC_2.2.5
                 U malloc@@GLIBC_2.2.5
                 U memcpy@@GLIBC_2.2.5
                 U memmove@@GLIBC_2.2.5
                 U memset@@GLIBC_2.2.5
                 U mmap@@GLIBC_2.2.5
                 U munmap@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
                 U realloc@@GLIBC_2.2.5
                 U sprintf@@GLIBC_2.2.5
                 U strcmp@@GLIBC_2.2.5
                 U strcpy@@GLIBC_2.2.5
                 U strlen@@GLIBC_2.2.5
                 U strrchr@@GLIBC_2.2.5
                 U usleep@@GLIBC_2.2.5
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
                 w __gmon_start__
00000000004007f8 T _init
0000000000400950 T main
~~~

FibHs7
------
sizeコマンドで取ったオブジェクトファイルサイズの大きいものから順に削減検討した。
やったことは要素数の多すぎるタプルのサポートを抑制。
mblock_cache[]のサイズを半分にへらした。(パフォーマンス低下？)
FibHs7/size.logに最終的なオブジェクトサイズをダンプした。
これ以上はライブラリの構造を見直さないかぎり、
抜本的なサイズ縮小は困難だと思われる。

FibHs8
------
RtsFlagsを静的に初期化。RtsStartupSlim.cから余計な関数を削除。
baseパッケージでコンパイル対象でないファイルをリポジトリから削除。
[数のクラス階層図](http://www.bucephalus.org/text/Haskell98numbers/Haskell98numbers.html)
を見て数関連のクラスを整理。以下の型を削除した。

* Complex    v
* Ratio      v
* Rational   v
* RealFloat  v
* Floating   v
* RealFrac   v
* Fractional v

FibHs9
------
CChar,CInt,CSize以外の型をForeign/C/Types.hsから削除。
size.logでデカいファイルを、激しいAPI変更を共なったとしても、削除をこころみた。
全体サイズが1MBを切ったので、ここらであきらめか。。。
