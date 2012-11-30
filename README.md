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

メモ
----
### 全体戦略

イカの順番で削減検討を進める。

1. ルール2: 実行バイナリがリンクしているライブラリ数をダイエット
2. Fib.oの未解決シンボル数をダイエット
3. ルール3: 実行バイナリ内の未解決シンボル数をダイエット
4. ルール1: text/data/bssセクションの合計サイズをダイエット

1と2は同時実行かもしれない。

### v 作戦A: libgmpは不要ではないか？

SlimHaskell/FibHs4でやってみた。
CIntを使った計算なのであればそもそもlibgmpはいらなくて、
libHSinteger-gmp-0.5.0.0.aをリンクする必要ない？
もしくは非ボックス化された数値型を使ってHaskellコードを書く必要がある？

~~~ {.bash}
gcc -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads -o FibHs CMain.o Fib.o -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1 -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0 -lHSrts -lm -lrt -ldl -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o):(.text+0x35c): `__gmpz_init' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o):(.text+0x386): `__gmpz_add' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o):(.text+0x46c): `__gmpz_init' に対する定義されていない参照です
--snip--
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o):(.text+0x1518): `__gmpn_gcd_1' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o):(.text+0x1561): `__gmpn_gcd_1' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o):(.text+0x15f8): `__gmpn_cmp' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0/libHSinteger-gmp-0.5.0.0.a(cbits.o): 関数 `initAllocForGMP' 内:
cbits.c:(.text+0x87): `__gmp_set_memory_functions' に対する定義されていない参照です
~~~

イカのオブジェクトから参照されている。

* libHSinteger-gmp-0.5.0.0.a(gmp-wrappers.o)
* libHSinteger-gmp-0.5.0.0.a(cbits.o)

libHSinteger-gmp-0.5.0.0.a自体を削除できる、、と思うけれど簡単ではない。
nmで見てみるかぎり、baseパッケージから参照されている。イカはそのダンプ結果。
思ったより使ってる箇所が多い。

SlimHaskell/ghc_base_link-integerzmgmp_sorted.log

まずは、integer-gmpをinteger-simpleで置き換えた方がいいかもしれない。
もしくはIntegerをIntの別名にしてしまうか。。。
fromIntegerはDeSugarで使われてしまうようだ。

http://hackage.haskell.org/trac/ghc/wiki/Commentary/Libraries/Integer

このインターフェイスを満すようにしてしまえば騙せるのでは？
ある程度似せたなんちゃってinteger-gmpを作った。中身はInt。

https://gitorious.org/metasepi/integer-fake

### 作戦B: Fib.oを見て、使っているクロージャーを削減/置換する

~~~ {.bash}
$ nm Fib.o | grep "U "
                 U base_GHCziInt_I32zh_static_info
                 U base_GHCziInt_zdfNumInt32zuzdczp_closure
                 U base_GHCziList_znzn1_closure
                 U base_GHCziList_znznzusub_closure
                 U base_GHCziList_znznzusub_info
                 U base_GHCziList_zzipWith_info
                 U base_GHCziTopHandler_runIO_closure
                 U getStablePtr
                 U ghczmprim_GHCziTypes_ZC_static_info
                 U newCAF
                 U rts_apply
                 U rts_checkSchedStatus
                 U rts_evalIO
                 U rts_getInt32
                 U rts_lock
                 U rts_mkInt32
                 U rts_unlock
                 U stg_CAF_BLACKHOLE_info
                 U stg_ap_0_fast
                 U stg_bh_upd_frame_info
                 U stg_upd_frame_info
~~~

この中で不要な未解決シンボルがないか調べる。
base_GHCxxxxxなシンボルは削減検討できそう。
特にbase_GHCziInt_xxxxxは違うものに置き換えられないか？
base_GHCziTopHandler_runIO_closureはなんで使うんだろう？

### 作戦C: rts_xxxやstg_xxxを簡易なC言語/cmm言語実装に置き換える

今回のソースコードだけ動作すれば良いのであれば、簡易実装を作れないか？
この案はかなりウルトラCを要求される。
記事後半で使うべき技。

### v 作戦D: ビルドログの中で不要な静的ライブラリへのリンクがないか調べる

SlimHaskell/FibHs1でやってみた。
細かくリンクオプションを分割して、どれを外すとどーなるか調査できる。

### 作戦E: 地道にFib.cmmを読んで考える

~~~ {.bash}
$ make Fib.cmm
/usr/local/ghc7.6.1/bin/ghc -O2 -ddump-cmm -c Fib.hs > Fib.cmm
~~~

さらっと読んで判断できないかと思うけど、中盤以降の方がいいかも。。。

### v 作戦F: hs_init()とhs_exit()関数の中で不要なものを削除する

SlimHaskell/FibHs8で実施。
つまりStgRunの手前までで不要なものをけずる。
シグナル関連やInCallの処理はまるごと不要なはず。
IO関連の処理も不要？selectやkqueueを使った待ち合わせも不要になるはず。

RTSにオブジェクト追加するにはtouch hoge.cするだけでOK。
なのだけれど、再コンパイルにエラい時間かかる。
これはズルする手を考えるか、ビルドサーバでやらないと無理だ。。。

hs_exit()は呼び出さないことにした。
hs_init()はhs_init_slim()という関数にして、中身を削減した。

### 作戦G: StgTSOのqueue管理を単純に

ケーパビリティとかこのプログラムなら不要じゃなイカ？

### 作戦H: GCを削る

やりすぎ？
完全にGCを削除したとしても41kB程度しか削減できないようだ。。。

### v 作戦I: 静的リンクライブラリをarでほどいて必要なオブジェクトを選別

最初にやった方がいいかも。

### 作戦J: Preludeのリストを使わずに、リスト型を自作する

baseパッケージの依存が減るのなら。

### 作戦K: 自然数型を自作

C言語から数を受け取るにはどうすれば。。。

### v 作戦L: libmいらなくない？

SlimHaskell/FibHs3で実施。
libHSbase-4.6.0.0.a(Float.o)が使ってるだけのようだ。

~~~ {.bash}
gcc -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads -o FibHs CMain.o Fib.o -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1 -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0 -lHSrts -lrt -ldl -lgmp -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0/libHSbase-4.6.0.0.a(Float.o): 関数 `sc08_info' 内:
(.text+0x2971): `pow' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0/libHSbase-4.6.0.0.a(Float.o): 関数 `sc14_info' 内:
(.text+0x2a54): `tanh' に対する定義されていない参照です
--snip--
/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0/libHSbase-4.6.0.0.a(Float.o): 関数 `saNY_info' 内:
(.text+0x14d86): `logf' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0/libHSbase-4.6.0.0.a(Float.o): 関数 `saNY_info' 内:
(.text+0x14da7): `logf' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0/libHSbase-4.6.0.0.a(Float.o):(.text+0x14dc7): `logf' に対する定義されていない参照がさらに続いています
collect2: error: ld returned 1 exit status
~~~

git@gitorious.org:metasepi/ghc-base-arafura.git
0b0f3b8e9a9522516fd6d2e057a4218cb4ca8466

でFloat関連を削除した。

### v 作戦M: librtいらなくない？

SlimHaskell/FibHs3の副作用で削除。
libHSrts.a(GetTime.o)とlibHSrts.a(Itimer.o)が使ってる。

~~~ {.bash}
gcc -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads -o FibHs CMain.o Fib.o -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1 -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0 -lHSrts -lm -ldl -lgmp -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0/libHSbase-4.6.0.0.a(Clock.o): 関数 `ghc_wrapper_d1iP_clock_gettime' 内:
(.text+0xd9d): `clock_gettime' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(GetTime.o): 関数 `getProcessCPUTime' 内:
GetTime.c:(.text+0x35): `clock_gettime' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(GetTime.o): 関数 `getMonotonicNSec' 内:
GetTime.c:(.text+0xcd): `clock_gettime' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(GetTime.o): 関数 `getThreadCPUTime' 内:
GetTime.c:(.text+0x164): `clock_gettime' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Itimer.o): 関数 `initTicker' 内:
Itimer.c:(.text+0x36): `timer_create' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Itimer.o): 関数 `startTicker' 内:
Itimer.c:(.text+0x105): `timer_settime' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Itimer.o): 関数 `stopTicker' 内:
Itimer.c:(.text+0x166): `timer_settime' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Itimer.o): 関数 `exitTicker' 内:
Itimer.c:(.text+0x198): `timer_delete' に対する定義されていない参照です
collect2: error: ld returned 1 exit status
~~~

### v 作戦N: libdlいらなくない？

作戦Oの副作用で削除された。
libHSrts.a(Linker.o)がdlopenとかを使ってる。

~~~ {.bash}
gcc -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads -o FibHs CMain.o Fib.o -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1 -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0 -lHSrts -lm -lrt -lgmp -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Linker.o): 関数 `internal_dlopen.part.7' 内:
Linker.c:(.text+0x35f): `dlerror' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Linker.o): 関数 `addDLL' 内:
Linker.c:(.text+0x1a4a): `dlopen' に対する定義されていない参照です
Linker.c:(.text+0x1b34): `dlopen' に対する定義されていない参照です
/usr/local/ghc7.6.1/lib/ghc-7.6.1/libHSrts.a(Linker.o): 関数 `lookupSymbol' 内:
Linker.c:(.text+0x5cc): `dlsym' に対する定義されていない参照です
collect2: error: ld returned 1 exit status
~~~

Linker.oは誰が使ってるの？

~~~ {.bash}
$ gcc -fno-stack-protector -Wl,--hash-size=31 -Wl,--reduce-memory-overheads -o FibHs CMain.o Fib.o rts/0Hash.o rts/0Unpack.o rts/Adjustor.o rts/Apply.o rts/Arena.o rts/AutoApply.o rts/BlockAlloc.o rts/Capability.o rts/ClosureFlags.o rts/Compact.o rts/Disassembler.o rts/Dist.o rts/Evac.o rts/EventLog.o rts/Exception.o rts/FileLock.o rts/FlagDefaults.o rts/FrontPanel.o rts/GC.o rts/GCAux.o rts/GCUtils.o rts/GetEnv.o rts/GetTime.o rts/Global.o rts/Globals.o rts/GranSim.o rts/HLComms.o rts/Hash.o rts/HeapStackCheck.o rts/Hpc.o rts/HsFFI.o rts/Inlines.o rts/Interpreter.o rts/Itimer.o rts/LLComms.o rts/LdvProfile.o rts/MBlock.o rts/MallocFail.o rts/MarkWeak.o rts/Messages.o rts/OSMem.o rts/OSThreads.o rts/OldARMAtomic.o rts/OnExit.o rts/OutOfHeap.o rts/Pack.o rts/Papi.o rts/ParInit.o rts/ParTicky.o rts/Parallel.o rts/ParallelDebug.o rts/PrimOps.o rts/Printer.o rts/ProfHeap.o rts/Profiling.o rts/Proftimer.o rts/RBH.o rts/RaiseAsync.o rts/RetainerProfile.o rts/RetainerSet.o rts/RtsAPI.o rts/RtsDllMain.o rts/RtsFlags.o rts/RtsMain.o rts/RtsMessages.o rts/RtsStartup.o rts/RtsUtils.o rts/STM.o rts/Sanity.o rts/Scav.o rts/Schedule.o rts/Select.o rts/Signals.o rts/Sparks.o rts/Stable.o rts/StackOverflow.o rts/Stats.o rts/StgCRun.o rts/StgMiscClosures.o rts/StgPrimFloat.o rts/StgStartup.o rts/StgStdThunks.o rts/Storage.o rts/Sweep.o rts/TTY.o rts/Task.o rts/ThreadLabels.o rts/ThreadPaused.o rts/Threads.o rts/Ticky.o rts/Timer.o rts/Trace.o rts/Updates.o rts/WSDeque.o rts/Weak.o rts/closures.o rts/ffi.o rts/ffi64.o rts/java_raw_api.o rts/prep_cif.o rts/raw_api.o rts/sysv.o rts/types.o rts/unix64.o -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/base-4.6.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/integer-gmp-0.5.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0 -L/usr/local/ghc7.6.1/lib/ghc-7.6.1 -lHSbase-4.6.0.0 -lHSinteger-gmp-0.5.0.0 -lHSghc-prim-0.3.0.0 -lm -lrt -lgmp -u base_GHCziConcziIO_ensureIOManagerIsRunning_closure
rts/RtsStartup.o: 関数 `hs_exit_' 内:
RtsStartup.c:(.text+0xb6): `exitLinker' に対する定義されていない参照です
collect2: error: ld returned 1 exit status
~~~

なるほど。RtsStartup.oをリンクするのを止めて、なおかつhs_exit()を小細工すればいいのか。

### v 作戦O: libHSrts.a中で小細工レベル修正で削除できる箇所がないか？

SlimHaskell/FibHs2で実施。
プログラムソースコード側でダミー関数を作って小細工。
それでもダメな部分はGHC RTSのソースコードをちょっと改変。
ダイエット効果は以下。

* セクション合計サイズ: 3122862 => 3046840
* 動的リンクライブラリ数: 9 => 8 (libdl.so.2へのリンク削除)
* 未解決シンボル数: 175 => 145

### x 作戦P: Haskellプログラム側コードをfib = return 0にしてみて依存調査

libHSbase-4.6.0.0.aの中が広いし、
Fib.cmmをシンプルにして解析するためにも一度やった方がいい。
が、その必要もないぐらい元のFib.cmmコードのまま削減してしまった。

### x 作戦Q: 最適化オプションを色々変えてサイズ比較

一番最後に苦し紛れに打つ手。-Omとかあるんかな。

http://www.kotha.net/ghcguide_ja/latest/options-optimise.html

* -O0: 全ての最適化を無効にせよ
* -funfolding-creation-threshold=n: 関数の展開候補(unfolding)に許される最大の大きさ
* -funfolding-use-threshold=n: これより小さい関数定義は呼び出し元に展開

なぜか、上記のオプションを適用するとサイズが増える。。。

~~~ {.bash}
$ git diff
diff --git a/FibHs8/size.log b/FibHs8/size.log
index a0f39eb..14ea089 100644
--- a/FibHs8/size.log
+++ b/FibHs8/size.log
@@ -23,7 +23,7 @@
     724              0       8     732     2dc rts/Weak.o
     733              0       0     733     2dd rts/WSDeque.o
     777              0       0     777     309 popcnt.o (ex libHSghc-prim-0.3.0.0.a)
-    869             48       0     917     395 Debug.o (ex libHSghc-prim-0.3.0.0.a)
+    853             56       0     909     38d Debug.o (ex libHSghc-prim-0.3.0.0.a)
     936              0       0     936     3a8 rts/GCUtils.o
    text           data     bss     dec     hex filename
    1036              0      28    1064     428 rts/MarkWeak.o
@@ -111,8 +111,8 @@
   45114          10960       0   56074    db0a Internal.o (ex libHSbase-4.6.0.0.a)
   49355           7392       0   56747    ddab Read.o (ex libHSbase-4.6.0.0.a)
   61129           9632       0   70761   11469 Word.o (ex libHSbase-4.6.0.0.a)
-  68305           2528       0   70833   114b1 Classes.o (ex libHSghc-prim-0.3.0.0.a)
   64406           8496       0   72902   11cc6 Lex.o (ex libHSbase-4.6.0.0.a)
+  70921           2816       0   73737   12009 Classes.o (ex libHSghc-prim-0.3.0.0.a)
   67296           9752       0   77048   12cf8 Int.o (ex libHSbase-4.6.0.0.a)
   73160           6552       0   79712   13760 Monoid.o (ex libHSbase-4.6.0.0.a)
  100167           8688       0  108855   1a937 Real.o (ex libHSbase-4.6.0.0.a)
~~~

### v 作戦R: libHSbase-4.6.0.0.a中で小細工レベル修正で削除できる箇所がないか？

SlimHaskell/FibHs5で実施。
たぶんここが一番デカい。デカいオブジェクトから削減検討すべき。

~~~ {.bash}
$ size libHSbase-4.6.0.0.a | sort | tail -20
  44954    4696       0   49650    c1f2 Sync.o (ex libHSbase-4.6.0.0.a)
  45042    2560       0   47602    b9f2 Text.o (ex libHSbase-4.6.0.0.a)
  45114   10960       0   56074    db0a Internal.o (ex libHSbase-4.6.0.0.a)
  47005    2952       0   49957    c325 Applicative.o (ex libHSbase-4.6.0.0.a)
  48111    9400       0   57511    e0a7 Generics.o (ex libHSbase-4.6.0.0.a)
  54084    4576       0   58660    e524 Handle.o (ex libHSbase-4.6.0.0.a)
  61129    9632       0   70761   11469 Word.o (ex libHSbase-4.6.0.0.a)
  63750    8496       0   72246   11a36 Lex.o (ex libHSbase-4.6.0.0.a)
  67296    9752       0   77048   12cf8 Int.o (ex libHSbase-4.6.0.0.a)
  70765       0       0   70765   1146d WCsubst.o (ex libHSbase-4.6.0.0.a)
  70891    5248       0   76139   1296b Enum.o (ex libHSbase-4.6.0.0.a)
  73160    6552       0   79712   13760 Monoid.o (ex libHSbase-4.6.0.0.a)
  74467    7472       0   81939   14013 Show.o (ex libHSbase-4.6.0.0.a)
  77137   42944       0  120081   1d511 Types.o (ex libHSbase-4.6.0.0.a)
  85203    2864       0   88067   15803 PSQ.o (ex libHSbase-4.6.0.0.a)
  93995    4936       0   98931   18273 Complex.o (ex libHSbase-4.6.0.0.a)
 100167    8688       0  108855   1a937 Real.o (ex libHSbase-4.6.0.0.a)
 101803    9984       0  111787   1b4ab Read.o (ex libHSbase-4.6.0.0.a)
 105849    4584       0  110433   1af61 Arr.o (ex libHSbase-4.6.0.0.a)
 238984   26104       0  265088   40b80 Data.o (ex libHSbase-4.6.0.0.a)
~~~

### v 作戦S: IOマネージャ削除

SlimHaskell/FibHs3の副作用で削除。
GHC.Event以下をまるごと削除した。

### v 作戦T: ghc-prim中で小細工レベル修正で削除できる箇所がないか？

SlimHaskell/FibHs7で実施。

~~~ {.bash}
$ pwd
/home/kiwamu/src/ghc-7.6.1.orig/libraries/ghc-prim-slim
$ git diff
diff --git a/Setup.hs b/Setup.hs
index 5e736ab..39e61ad 100644
--- a/Setup.hs
+++ b/Setup.hs
@@ -23,8 +23,8 @@ main = do let hooks = simpleUserHooks {
                           $ regHook simpleUserHooks,
                   buildHook = build_primitive_sources
                             $ buildHook simpleUserHooks,
-                  makefileHook = build_primitive_sources
-                               $ makefileHook simpleUserHooks,
+--                  makefileHook = build_primitive_sources
+--                               $ makefileHook simpleUserHooks,
                   haddockHook = addPrimModuleForHaddock
                               $ build_primitive_sources
                               $ haddockHook simpleUserHooks }
$ cp ../../utils/genprimopcode/dist/build/tmp/genprimopcode ../../utils/genprimopcode/
$ ./Setup configure
$ ./Setup build
$ sudo cp -a dist/build/{GHC,HSghc-prim-0.3.0.0.o,libHSghc-prim-0.3.0.0.a} /usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0/
$ cp dist/build/libHSghc-prim-0.3.0.0.a /home/kiwamu/src/SlimHaskell/FibHs7/
~~~

要素数の多すぎるタプルのサポートを削除。
ghc-prim-slim/GHC/Classes.hsを修正してタプルのコンストラクタを減らすと、
シンボルの意味が変化するので、
/usr/local/ghc7.6.1/lib/ghc-7.6.1/ghc-prim-0.3.0.0/
にインストールする必要がある。

### x 作戦U: baseパッケージ内のINLINE宣言をはずす

が、全部はずすと逆にデカくなった。。

~~~ {.bash}
$ for i in `find . -name "*hs"`
for> sed -i -e "s/{-# INLINE/-- {-# INLINE/g" $i
~~~

### 気づいたこと

#### ghcのコンパイル

ghc/ghc-tarballsはsync-allで取ってくるよりも、リリースされているソースtar玉からコピーした方が楽。
というかリリースタグでsync-allする方法がよくわからない。。。

~~~ {.bash}
$ sudo apt-get install happy alex
$ cp mk/build.mk.sample mk/build.mk
$ vi mk/build.mk
--snip--
BuildFlavour = quick
--snip--
$ cp -a ../ghc-7.6.1.orig/ghc-tarballs ./
$ cp -a ../ghc-7.6.1.orig/utils/* ./utils/
$ cp -a ../ghc-7.6.1.orig/libraries/* ./libraries/
$ ./configure --prefix=/usr/local/ghc7.6.1
$ make
$ sudo make install
~~~

#### baseパッケージのコンパイル

libHSbase-4.6.0.0.aはarで開いて、再度arで戻してもリンクできないみたい。
素直にghc-pkgとしてコンパイルした方が良さそう。

~~~ {.bash}
### ghc-7.6.1をふつーにコンパイルしておく
$ pwd
/home/kiwamu/src/ghc-7.6.1/libraries
$ git clone git://github.com/ghc/packages-base.git base-slim
$ base-slim
$ git checkout ghc-7.6.1-release
$ autoreconf -i
$ ghc -i Setup.hs
$ ./Setup clean
$ ./Setup configure
$ ./Setup build
$ ls dist/build/libHSbase-4.6.0.0.a
dist/build/libHSbase-4.6.0.0.a
~~~

-iオプションがポイントか。
include/HsBaseConfig.h.inはautoreconf -iすれば生成される。
ghc-7.6.1/librariesディレクトリの外でビルドするとこける。。。

~~~ {.bash}
$ ./Setup build
Building base-4.6.0.0...
Preprocessing library base-4.6.0.0...

GHC/Constants.hs:9:0:
     fatal error: ../../../compiler/stage1/ghc_boot_platform.h: No such file or directory
compilation terminated.
$ grep GHC.Constants base.cabal
            GHC.Constants,
~~~

GHC.Constantsがしれっとコンパイル対象になっている時点で回避不能か。。。
