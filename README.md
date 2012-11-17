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
