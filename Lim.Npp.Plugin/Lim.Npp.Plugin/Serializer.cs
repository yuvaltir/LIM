using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Lim.Npp.Plugin
{
    public static class Serializer<T>
    {

        public static T Deserialize(string xmlString)
        {
            try
            {
                using (var stringReader = new StringReader(xmlString))
                {
                    var xmlSerializer = new XmlSerializer(typeof(T));
                    return (T)xmlSerializer.Deserialize(stringReader);
                }
            }
            catch (Exception ex)
            {
                return default(T);
            }
        }

        public static string Serialize(T obj)
        {
            try
            {
                if (obj == null)
                {
                    return string.Empty;
                }
                var returnStream = new StringWriter();
                var serializer = new XmlSerializer(obj.GetType());
                var settings = new XmlWriterSettings()
                {
                    Indent = true,
                    OmitXmlDeclaration = true
                };

                using (var writer = XmlWriter.Create(returnStream, settings))
                {
                    serializer.Serialize(writer, obj);
                    var res = returnStream.ToString();

                    return res;

                }
            }
            catch (Exception ex)
            {
                return string.Empty;
            }
        }
    }
}
