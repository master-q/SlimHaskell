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


FibHsXXX
--------
fib関数をreturn 0にしてみて、baseパッケージの何を使っているのか探ってみた。
Fib.oはbase_GHCziInt_I32zh_static_infoとbase_GHCziTopHandler_runIO_closureを
使うようだ。
さらにlibHSbase-4.6.0.0.aで必須のオブジェクトファイルを探してみる。
このディレクトリのソースは機能未達なので測定対象ではない。
