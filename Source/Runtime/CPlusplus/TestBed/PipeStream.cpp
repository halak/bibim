#include <Bibim/TestBed.h>
#include <Bibim/PipeClientStream.h>
#include <iostream>
using namespace Bibim;

void Bibim::TestBed::PipeStream(CommandLines commands)
{
    PipeClientStreamPtr pipe = new PipeClientStream("Echo", PipeStream::ReadAndWrite);
    pipe->Connect();
    if (pipe->IsConnected())
    {
        const char* s = "Hello";
        pipe->Write(s, strlen(s) + 1);

        char r[100];
        int c = pipe->Read(r, 100);
        std::cout << "열렸다!" << std::endl;
        pipe->Disconnect();
    }
    else
        std::cout << "열어라-" << std::endl;
}