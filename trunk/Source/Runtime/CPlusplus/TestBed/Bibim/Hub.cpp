#include <Bibim/TestBed.h>
#include <crtdbg.h>
using namespace Bibim;
using namespace Bibim::TestBed;

int main(int argc, const char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    CommandLines args;
    args.reserve(argc);

    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    Bibim::TestBed::PipeStream(args);

    return 0;
}