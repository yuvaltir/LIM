using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Lim.Npp.Plugin
{
    [XmlRoot(ElementName = "PluginConfig")]
    public class PluginConfig
    {
        [XmlElement(ElementName = "ParsingRules")]
        public ParsingRules Parsing { get; set; }
    }

    [XmlRoot(ElementName = "ParsingRules")]
    public class ParsingRules
    {
        [XmlAttribute(AttributeName = "maxSelectionLength")]
        public string MaxSelectionLength { get; set; }

        [XmlIgnore]
        public int MaxSelectionLengthInt { get { return int.Parse(MaxSelectionLength); } }

        [XmlAttribute(AttributeName = "maxLineCount")]
        public string MaxLineCount { get; set; }

        [XmlIgnore]
        public int MaxLineCountInt
        {
            get { return int.Parse(MaxLineCount); }
        }
    }
}
