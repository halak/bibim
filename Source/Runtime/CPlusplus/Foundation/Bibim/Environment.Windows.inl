namespace Bibim
{
    const String& Environment::GetWorkingDirectory()
    {
        return PrivateInstance.workingDirectory;
    }

    const String& Environment::GetLocaleName()
    {
        return PrivateInstance.localeName;
    }
}