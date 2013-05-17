char jhc_c_compile[] = "gcc tmp/rts/profile.c tmp/rts/rts_support.c tmp/rts/gc_none.c tmp/rts/jhc_rts.c tmp/lib/lib_cbits.c tmp/rts/gc_jgc.c tmp/rts/stableptr.c -Itmp/cbits -Itmp hs_main.c -o hs_main.c '-std=gnu99' -D_GNU_SOURCE '-falign-functions=4' -ffast-math -Wextra -Wall -Wno-unused-parameter -fno-strict-aliasing -DNDEBUG -O3 '-D_JHC_GC=_JHC_GC_JGC'";
char jhc_command[] = "ajhc -fffi -fno-standalone --tdir=tmp -C -o hs_main.c Main.hs";
char jhc_version[] = "ajhc 0.8.0.5 (1de6d91b13a6b50f67a9aef9b7f91f21c278ee5c)";

#include "jhc_rts_header.h"
static struct s_cache *cCJhc_Prim_Prim_$x3a;
static struct s_cache *cCJhc_Type_Word_Int;
static struct s_cache *cFR$__fJhc_Basics_zipWith;
static struct s_cache *cFFib_fibonacci$d2;

enum {
    CJhc_Prim_Prim_$BE = 1,
    CJhc_Prim_Prim_$x3a = 0,
    CJhc_Type_Word_Int = 0
};
struct sCJhc_Prim_Prim_$x3a A_ALIGNED;
struct sCJhc_Type_Word_Int A_ALIGNED;
struct sFFib_fibonacci A_ALIGNED;
struct sFFib_fibonacci$d2 A_ALIGNED;
struct sFR$__fJhc_Basics_zipWith A_ALIGNED;

struct sCJhc_Prim_Prim_$x3a {
    sptr_t a1;
    sptr_t a2;
};

struct sCJhc_Type_Word_Int {
    uint32_t a1;
};

struct sFFib_fibonacci {
    fptr_t head;
};

struct sFFib_fibonacci$d2 {
    fptr_t head;
    sptr_t a1;
    sptr_t a2;
};

struct sFR$__fJhc_Basics_zipWith {
    fptr_t head;
    sptr_t a1;
    sptr_t a2;
};
void jhc_hs_init(void) ;
static wptr_t E__fFib_fibonacci(gc_t gc,struct sFFib_fibonacci* arg) A_STD A_FALIGNED;
static wptr_t E__fFib_fibonacci$d2(gc_t gc,struct sFFib_fibonacci$d2* arg) A_STD A_FALIGNED;
static wptr_t E__fR$__fJhc_Basics_zipWith(gc_t gc,struct sFR$__fJhc_Basics_zipWith* arg) A_STD A_FALIGNED;
void _amain(void) ;
static void b__main(gc_t gc) A_STD;
static uint32_t fFE$__CCall_fib(gc_t gc,uint32_t v8) A_STD;
static wptr_t fFib_fibonacci(gc_t gc) A_STD A_MALLOC;
static wptr_t fFib_fibonacci$d2(gc_t gc,sptr_t v38,sptr_t v42) A_STD A_MALLOC;
static wptr_t fR$__fJhc_Basics_zipWith(gc_t gc,sptr_t v182639120,sptr_t v194635132) A_STD A_MALLOC;
int fib(int x4) ;
static void ftheMain(gc_t gc) A_STD;
/* CAFS */
/* v-1427642909 = (FFib.fibonacci)*/
static node_t _g1427642909 = { .head = TO_FPTR(&E__fFib_fibonacci) };
#define g1427642909 (MKLAZY_C(&_g1427642909))

/* (HcNode CJhc.Type.Word.Int [Left 0],1) */
static const struct sCJhc_Type_Word_Int _c1 = {.a1 = 0};
#define c1 (TO_SPTR_C(P_WHNF, (sptr_t)&_c1))
/* (HcNode CJhc.Type.Word.Int [Left 1],2) */
static const struct sCJhc_Type_Word_Int _c2 = {.a1 = 1};
#define c2 (TO_SPTR_C(P_WHNF, (sptr_t)&_c2))

const void * const nh_stuff[] = {
&_g1427642909, &_c1, &_c2, NULL
};


void 
jhc_hs_init(void)
{
        find_cache(&cCJhc_Prim_Prim_$x3a,arena,TO_BLOCKS(sizeof(struct sCJhc_Prim_Prim_$x3a)),2);
        find_cache(&cCJhc_Type_Word_Int,arena,TO_BLOCKS(sizeof(struct sCJhc_Type_Word_Int)),0);
        find_cache(&cFR$__fJhc_Basics_zipWith,arena,TO_BLOCKS(sizeof(struct sFR$__fJhc_Basics_zipWith)),3);
        find_cache(&cFFib_fibonacci$d2,arena,TO_BLOCKS(sizeof(struct sFFib_fibonacci$d2)),3);
}

static wptr_t A_STD A_FALIGNED
E__fFib_fibonacci(gc_t gc,struct sFFib_fibonacci* arg)
{
        wptr_t r;
        r = fFib_fibonacci(gc);
        update(arg,r);
        gc_add_root(gc,(sptr_t)r);
        return r;
}

static wptr_t A_STD A_FALIGNED
E__fFib_fibonacci$d2(gc_t gc,struct sFFib_fibonacci$d2* arg)
{
        {   wptr_t r;
            gc_frame0(gc,1,MKLAZY(arg));
            r = fFib_fibonacci$d2(gc,arg->a1,arg->a2);
            update(arg,r);
            return r;
        }
}

static wptr_t A_STD A_FALIGNED
E__fR$__fJhc_Basics_zipWith(gc_t gc,struct sFR$__fJhc_Basics_zipWith* arg)
{
        {   wptr_t r;
            gc_frame0(gc,1,MKLAZY(arg));
            r = fR$__fJhc_Basics_zipWith(gc,arg->a1,arg->a2);
            update(arg,r);
            return r;
        }
}

void 
_amain(void)
{
        return (void)b__main(saved_gc);
}

static void A_STD
b__main(gc_t gc)
{
        return ftheMain(gc);
}

static uint32_t A_STD
fFE$__CCall_fib(gc_t gc,uint32_t v8)
{
        wptr_t v59;
        uint32_t v35;
        uint16_t v100016 = (((int32_t)0) <= ((int32_t)v8));
        if (0 == v100016) {
            v59 = PROMOTE(c1);
        } else {
            /* 1 */
            assert(1 == v100016);
            uint16_t v100018 = (((int32_t)40) >= ((int32_t)v8));
            if (0 == v100018) {
                v59 = PROMOTE(c1);
            } else {
                uint32_t v87;
                /* 1 */
                assert(1 == v100018);
                uint16_t v100020 = (((int32_t)0) > ((int32_t)v8));
                if (0 == v100020) {
                    wptr_t v100022;
                    sptr_t v115160438;
                    uint32_t v115160444;
                    uint32_t v124940224;
                    v115160438 = g1427642909;
                    v124940224 = v8;
                    fW$__fR$__fJhc_List_243__sub__2:;
                    {   wptr_t v100024 = eval(gc,v115160438);
                        if (SET_RAW_TAG(CJhc_Prim_Prim_$BE) == v100024) {
                            jhc_error("Prelude.error: Prelude.(!!): index too large");
                        } else {
                            sptr_t v132;
                            sptr_t v134;
                            /* ("CJhc.Prim.Prim.:" ni132 ni134) */
                            v132 = ((struct sCJhc_Prim_Prim_$x3a*)v100024)->a1;
                            v134 = ((struct sCJhc_Prim_Prim_$x3a*)v100024)->a2;
                            if (0 == v124940224) {
                                v100022 = eval(gc,v132);
                            } else {
                                uint32_t v178407644 = (v124940224 - 1);
                                v115160438 = v134;
                                v124940224 = v178407644;
                                goto fW$__fR$__fJhc_List_243__sub__2;
                            }
                        }
                    }
                    v115160444 = ((struct sCJhc_Type_Word_Int*)v100022)->a1;
                    v87 = v115160444;
                } else {
                    /* 1 */
                    assert(1 == v100020);
                    jhc_error("Prelude.error: Prelude.(!!): negative index");
                }
                wptr_t x3 = s_alloc(gc,cCJhc_Type_Word_Int);
                ((struct sCJhc_Type_Word_Int*)x3)->a1 = v87;
                v59 = x3;
            }
        }
        v35 = ((struct sCJhc_Type_Word_Int*)v59)->a1;
        return v35;
}

static wptr_t A_STD A_MALLOC
fFib_fibonacci(gc_t gc)
{
        sptr_t x9 = s_alloc(gc,cFR$__fJhc_Basics_zipWith);
        ((struct sFR$__fJhc_Basics_zipWith*)x9)->head = TO_FPTR(&E__fR$__fJhc_Basics_zipWith);
        sptr_t v1213995561 = MKLAZY(x9);
        {   gc_frame0(gc,1,v1213995561);
            wptr_t x10 = s_alloc(gc,cCJhc_Prim_Prim_$x3a);
            wptr_t v43 = x10;
            sptr_t v1216617003 = demote(v43);
            ((struct sFR$__fJhc_Basics_zipWith*)FROM_SPTR(v1213995561))->head = TO_FPTR(&E__fR$__fJhc_Basics_zipWith);
            ((struct sFR$__fJhc_Basics_zipWith*)FROM_SPTR(v1213995561))->a1 = g1427642909;
            ((struct sFR$__fJhc_Basics_zipWith*)FROM_SPTR(v1213995561))->a2 = v1216617003;
            ((struct sCJhc_Prim_Prim_$x3a*)FROM_SPTR(v1216617003))->a1 = c2;
            ((struct sCJhc_Prim_Prim_$x3a*)FROM_SPTR(v1216617003))->a2 = v1213995561;
            {   gc_frame0(gc,1,v1216617003);
                wptr_t x11 = s_alloc(gc,cCJhc_Prim_Prim_$x3a);
                ((struct sCJhc_Prim_Prim_$x3a*)x11)->a1 = c2;
                ((struct sCJhc_Prim_Prim_$x3a*)x11)->a2 = v1216617003;
                return x11;
            }
        }
}

static wptr_t A_STD A_MALLOC
fFib_fibonacci$d2(gc_t gc,sptr_t v38,sptr_t v42)
{
        {   gc_frame0(gc,1,v42);
            wptr_t v100004 = eval(gc,v38);
            {   uint32_t v115160440;
                uint32_t v29534740;
                gc_frame0(gc,1,v100004);
                wptr_t v100006 = eval(gc,v42);
                v115160440 = ((struct sCJhc_Type_Word_Int*)v100004)->a1;
                v29534740 = ((struct sCJhc_Type_Word_Int*)v100006)->a1;
                uint32_t v40405740 = (v115160440 + v29534740);
                wptr_t x5 = s_alloc(gc,cCJhc_Type_Word_Int);
                ((struct sCJhc_Type_Word_Int*)x5)->a1 = v40405740;
                return x5;
            }
        }
}

static wptr_t A_STD A_MALLOC
fR$__fJhc_Basics_zipWith(gc_t gc,sptr_t v182639120,sptr_t v194635132)
{
        {   gc_frame0(gc,1,v194635132);
            wptr_t v100000 = eval(gc,v182639120);
            if (SET_RAW_TAG(CJhc_Prim_Prim_$BE) == v100000) {
                return v100000;
            } else {
                sptr_t v40;
                sptr_t v40405742;
                /* ("CJhc.Prim.Prim.:" ni40405742 ni40) */
                v40405742 = ((struct sCJhc_Prim_Prim_$x3a*)v100000)->a1;
                v40 = ((struct sCJhc_Prim_Prim_$x3a*)v100000)->a2;
                {   gc_frame0(gc,2,v40,v40405742);
                    wptr_t v100002 = eval(gc,v194635132);
                    if (SET_RAW_TAG(CJhc_Prim_Prim_$BE) == v100002) {
                        return v100002;
                    } else {
                        sptr_t v194635134;
                        sptr_t v44;
                        /* ("CJhc.Prim.Prim.:" ni194635134 ni44) */
                        v194635134 = ((struct sCJhc_Prim_Prim_$x3a*)v100002)->a1;
                        v44 = ((struct sCJhc_Prim_Prim_$x3a*)v100002)->a2;
                        {   gc_frame0(gc,2,v44,v194635134);
                            sptr_t x6 = s_alloc(gc,cFFib_fibonacci$d2);
                            ((struct sFFib_fibonacci$d2*)x6)->head = TO_FPTR(&E__fFib_fibonacci$d2);
                            ((struct sFFib_fibonacci$d2*)x6)->a1 = v40405742;
                            ((struct sFFib_fibonacci$d2*)x6)->a2 = v194635134;
                            sptr_t v229109160 = MKLAZY(x6);
                            {   gc_frame0(gc,1,v229109160);
                                sptr_t x7 = s_alloc(gc,cFR$__fJhc_Basics_zipWith);
                                ((struct sFR$__fJhc_Basics_zipWith*)x7)->head = TO_FPTR(&E__fR$__fJhc_Basics_zipWith);
                                ((struct sFR$__fJhc_Basics_zipWith*)x7)->a1 = v40;
                                ((struct sFR$__fJhc_Basics_zipWith*)x7)->a2 = v44;
                                sptr_t v248061794 = MKLAZY(x7);
                                {   gc_frame0(gc,1,v248061794);
                                    wptr_t x8 = s_alloc(gc,cCJhc_Prim_Prim_$x3a);
                                    ((struct sCJhc_Prim_Prim_$x3a*)x8)->a1 = v229109160;
                                    ((struct sCJhc_Prim_Prim_$x3a*)x8)->a2 = v248061794;
                                    return x8;
                                }
                            }
                        }
                    }
                }
            }
        }
}

int 
fib(int x4)
{
        return (int)fFE$__CCall_fib(saved_gc,(uint32_t)x4);
}

static void A_STD
ftheMain(gc_t gc)
{
        return;
}
