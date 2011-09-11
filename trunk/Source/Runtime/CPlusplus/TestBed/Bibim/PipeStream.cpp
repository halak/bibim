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
        std::cout << "���ȴ�!" << std::endl;
        pipe->Close();
    }
    else
        std::cout << "�����-" << std::endl;
}