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
        std::cout << "���ȴ�!" << std::endl;
        pipe->Disconnect();
    }
    else
        std::cout << "�����-" << std::endl;
}