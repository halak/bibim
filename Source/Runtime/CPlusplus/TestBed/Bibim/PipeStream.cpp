#include <Bibim/TestBed.h>
#include <Bibim/PipeClientStream.h>
#include <iostream>
using namespace Bibim;

void Bibim::TestBed::PipeStream(CommandLines commands)
{
    PipeClientStreamPtr pipe = new PipeClientStream();

    pipe->Open("Echo", PipeStream::ReadAndWrite);
    if (pipe->IsOpen())
    {
        std::cout << "열렸다!" << std::endl;
        pipe->Close();
    }
    else
        std::cout << "열어라-" << std::endl;
}