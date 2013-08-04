#include <Bibim/Config.h>
#include <Bibim/Performance.h>
#include <Bibim/BinaryWriter.h>
#include <Bibim/Diagnostics.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    void Performance::Report(const Sample& sample)
    {
        /*
        BinaryWriter::WriteTo(stream, static_cast<int>(Diagnostics::PerformanceProtocolID));
        BinaryWriter::WriteTo(stream, sample.Function);
        BinaryWriter::WriteTo(stream, sample.Filename);
        BinaryWriter::WriteTo(stream, sample.Line);
        BinaryWriter::WriteTo(stream, static_cast<int>(sample.EndTime - sample.StartTime));
        */
    }
}