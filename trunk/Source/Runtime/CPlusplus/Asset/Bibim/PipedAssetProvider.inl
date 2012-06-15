﻿namespace Bibim
{
    const String& PipedAssetProvider::GetClientName() const
    {
        return clientName;
    }

    const String& PipedAssetProvider::GetServerName() const
    {
        return serverName;
    }

    const String& PipedAssetProvider::GetPipeName() const
    {
        return pipeName;
    }

    const String& PipedAssetProvider::GetWorkingDirectory() const
    {
        return workingDirectory;
    }

    bool PipedAssetProvider::GetDumpCacheEnabled() const
    {
        return dumpCacheEnabled;
    }

    void PipedAssetProvider::SetDumpCacheEnabled(bool value)
    {
        dumpCacheEnabled = value;
    }
}