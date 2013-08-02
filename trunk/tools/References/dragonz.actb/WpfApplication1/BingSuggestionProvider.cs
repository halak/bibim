using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Web;
using System.Web.Script.Serialization;
using dragonz.actb.provider;

namespace WpfApplication1
{
    internal class BingSuggestionProvider : IAutoCompleteDataProvider
    {
        private const string _uriFormat = "http://api.bing.net/osjson.aspx?query={0}";
        private readonly JavaScriptSerializer _jsonSerializer = new JavaScriptSerializer();

        public IEnumerable<string> GetItems(string textPattern)
        {
            WebRequest request = null;
            WebResponse response = null;
            try
            {
                var uri = new Uri(string.Format(_uriFormat, HttpUtility.UrlEncode(textPattern)));
                request = WebRequest.Create(uri);
                try
                {
                    response = request.GetResponse();
                }
                catch
                {
                    return null;
                }
                object[] jsonResult;
                using (var stream = response.GetResponseStream())
                {
                    var reader = new StreamReader(stream, Encoding.UTF8);
                    var json = reader.ReadToEnd();
                    jsonResult = _jsonSerializer.DeserializeObject(json) as object[];
                }
                if (jsonResult.Length != 2)
                {
                    return null;
                }
                var originalSearchString = jsonResult[0] as string;
                if (originalSearchString != textPattern)
                {
                    //yield break;
                }
                var suggestions = jsonResult[1] as object[];
                var result = new string[suggestions.Length];
                for (var n = 0; n < suggestions.Length; n++)
                {
                    result[n] = (string) suggestions[n];
                }
                return result;
            }
            finally
            {
                if(response != null)
                {
                    response.Close();
                }
                if(request != null)
                {
                    request.Abort();
                }
            }
        }
    }
}