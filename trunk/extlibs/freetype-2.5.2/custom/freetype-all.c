#include "../src/autofit/autofit.c"
/* #include "../src/bdf/bdf.c" */
/* #include "../src/cff/cff.c" */
#include "../src/base/ftbase.c"
#include "../src/base/ftbitmap.c"
/* #include "../src/cache/ftcache.c" */
#include "../src/base/ftfstype.c"
#include "../src/base/ftgasp.c"
#include "../src/base/ftglyph.c"
#if (defined(WIN32))
#include "../builds/windows/ftdebug.c"
#else
#include "../src/base/ftdebug.c"
#endif

#include "../src/gzip/ftgzip.c"
#undef bits
#undef exop
#undef local

#include "../src/base/ftinit.c"
#include "../src/lzw/ftlzw.c"
#include "../src/base/ftstroke.c"
#include "../src/base/ftsystem.c"
#include "../src/smooth/smooth.c"

// MODULES
#include "../src/base/ftbbox.c"
#include "../src/base/ftmm.c"
/* #include "../src/base/ftpfr.c" */
#include "../src/base/ftsynth.c"
/* #include "../src/base/fttype1.c" */
#include "../src/base/ftwinfnt.c"
#include "../src/base/ftxf86.c"
#include "../src/base/ftlcdfil.c"
#include "../src/base/ftgxval.c"
#include "../src/base/ftotval.c"
#include "../src/base/ftpatent.c"
/* #include "../src/pcf/pcf.c" */
/* #include "../src/pfr/pfr.c" */
#include "../src/psaux/psaux.c"
#include "../src/pshinter/pshinter.c"
#include "../src/psnames/psmodule.c"
#include "../src/raster/raster.c"
#include "../src/sfnt/sfnt.c"
#include "../src/truetype/truetype.c"
/* #include "../src/type1/type1.c" */
/* #include "../src/cid/type1cid.c" */
/* #include "../src/type42/type42.c" */
#include "../src/winfonts/winfnt.c"