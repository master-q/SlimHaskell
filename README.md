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
fib関数をreturn 0にしてみて、baseパッケージの何を使っているのか探ってみた。
Fib.oはbase_GHCziInt_I32zh_static_infoとbase_GHCziTopHandler_runIO_closureを
使うようだ。
さらにlibHSbase-4.6.0.0.aで必須のオブジェクトファイルを探してみる。
このディレクトリのソースは機能未達なので測定対象ではない。
