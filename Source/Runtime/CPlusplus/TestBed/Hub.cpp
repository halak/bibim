#include <crtdbg.h>
using namespace Bibim;

int main(int argc, const char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::vector<const char*> args;
    args.reserve(argc);

    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    return 0;
}