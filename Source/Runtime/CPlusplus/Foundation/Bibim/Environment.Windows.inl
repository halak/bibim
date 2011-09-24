namespace Bibim
{
    const String& Environment::GetWorkingDirectory()
    {
        return PrivateInstance.PrivateGetWorkingDirectory();
    }

    const String& Environment::PrivateGetWorkingDirectory() const
    {
        return workingDirectory;
    }
}