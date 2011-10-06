#include <Bibim/PCH.h>
#include <Bibim/ScriptProcess.h>
#include <Bibim/Script.h>
#include <Bibim/SCriptingContext.h>

namespace Bibim
{
    ScriptProcess::ScriptProcess(Script* script)
        : script(script),
          position(0)
    {
        if (script)
            position = script->GetEntryPoint();
    }

    ScriptProcess::~ScriptProcess()
    {
    }

    void ScriptProcess::Resume()
    {
    }

    void ScriptProcess::Suspend()
    {
    }
}