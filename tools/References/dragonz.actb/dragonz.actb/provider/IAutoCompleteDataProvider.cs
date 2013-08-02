using System.Collections.Generic;

namespace dragonz.actb.provider
{
    public interface IAutoCompleteDataProvider
    {
        IEnumerable<string> GetItems(string textPattern);
    }
}
