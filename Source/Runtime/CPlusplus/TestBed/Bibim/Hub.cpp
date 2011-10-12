#include <Bibim/TestBed.h>
#include <Bibim/Startup.h>
#include <windows.h>
#include <crtdbg.h>
using namespace Bibim;
using namespace Bibim::TestBed;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    CommandLines args;
    //args.reserve(argc);

    //for (int i = 0; i < argc; i++)
    //    args.push_back(argv[i]);

    Bibim::Startup::All();
    Bibim::TestBed::UI(args);

    return 0;
}