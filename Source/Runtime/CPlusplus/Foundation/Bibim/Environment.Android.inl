namespace Bibim
{
    const String& Environment::GetLocaleName()
    {
        return PrivateInstance.localeName;
    }

    const String& Environment::GetWorkingDirectory()
    {
        return PrivateInstance.workingDirectory;
    }
}