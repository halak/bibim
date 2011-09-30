#include <Bibim/PCH.h>
#include <Bibim/ScriptProcess.h>
#include <Bibim/Script.h>
#include <Bibim/ScriptCallable.h>
#include <Bibim/SCriptingContext.h>

namespace Bibim
{
    ScriptProcess::ScriptProcess(Script* script)
        : script(script),
          position(0)
    {
    }

    ScriptProcess::~ScriptProcess()
    {
    }

    void ScriptProcess::Run()
    {
    }
}