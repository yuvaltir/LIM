# LIM (Less is More)

A text compression and mapping utility that enables efficient storage and indexing of large text files while maintaining full searchability and reversibility.

## Overview

LIM is designed to compress textual data by creating a mapping dictionary that replaces frequently occurring words and phrases with shorter tokens. This approach significantly reduces file size while preserving the ability to:

- **Index and search** through the compressed data
- **Fully reverse** the compression to recover the original text
- **Maintain readability** of timestamps and structural elements

The project is particularly useful for log files, large text datasets, and any scenario where storage space is at a premium but quick searchability is required.

## Key Features

- **Intelligent Word Mapping**: Analyzes text to identify frequently occurring words and replaces them with shorter tokens based on frequency and length
- **Bidirectional Conversion**: Supports both compression (original → compressed) and decompression (compressed → original)
- **DAWG-Based Dictionary**: Utilizes Directed Acyclic Word Graphs (DAWG) for efficient string matching and replacement
- **Preserves Structure**: Maintains timestamps and log structure for easy navigation
- **Configurable Separators**: Supports different tokenization strategies (default, XML-aware, comprehensive)
- **Fast Search**: Compressed data remains searchable without full decompression

## Architecture

The solution consists of several components:

### Core Components

1. **LIM.DAWG.Map** (C++/DLL)
   - Implements the core DAWG-based string replacement engine
   - Provides high-performance bidirectional text transformation
   - Uses the dawgdic library for efficient trie operations

2. **LIM** (C# Library)
   - `Mapper.cs`: Main orchestration class for the mapping process
   - `LIM.MAP.Importer.cs`: P/Invoke interface to the native DAWG library
   - `LimAppender.cs`: Log4net integration for transparent compression

3. **LIM.TestApp** (C# Console Application)
   - Command-line interface for processing files
   - Demonstration of the mapping workflow
   - Performance benchmarking utilities

## How It Works

### Compression Process

1. **Analysis Phase**
   - Parse the input text file
   - Tokenize text based on configurable separators
   - Count word frequency across the entire dataset
   - Calculate compression value (word_length × frequency) for each unique word

2. **Mapping Generation**
   - Generate short tokens (e.g., ~a, ~b, ~aa, ~ab, etc.)
   - Sort words by compression value (highest first)
   - Assign shorter tokens to high-value words
   - Create bidirectional mapping dictionary

3. **Compression**
   - Replace original words with their corresponding tokens
   - Preserve timestamps and structural prefixes
   - Write compressed output and mapping file

4. **Decompression**
   - Load mapping dictionary
   - Replace tokens with original words
   - Restore complete original text

### DAWG Implementation

The project uses Directed Acyclic Word Graphs for efficient string matching:

- **Prefix matching**: Quickly find the longest matching word from the current position
- **Memory efficient**: Shared prefix paths reduce memory footprint
- **Fast lookups**: O(k) complexity where k is the key length

## Getting Started

### Prerequisites

- .NET Framework (C# components)
- Visual Studio with C++ support (for building native components)
- Windows platform (due to P/Invoke dependencies)

### Building the Project

1. Open `ConsoleApplication1.sln` in Visual Studio
2. Build the solution (builds both C++ DLL and C# assemblies)
3. The compiled binaries will be in the `Release` or `Debug` folder

### Basic Usage

```bash
ConsoleApplication1.exe <input_file> [separator_type]
```

**Parameters:**
- `input_file`: Path to the text file to compress
- `separator_type` (optional): 
  - `0` = Default separators (space, comma, period, parentheses)
  - `1` = XML separators (includes < > / =)
  - `2` = Comprehensive (includes all special characters)

**Output Files:**
- `<filename>_org.log` - Copy of original file
- `<filename>_short.log` - Compressed version
- `<filename>_map.log` - Mapping dictionary (token,original_word pairs)
- `<filename>_new.log` - Decompressed file (verification)

### Programmatic Usage

```csharp
using LIM;

var mapper = new Mapper(
    inputFile: "path/to/logfile.log",
    outputDir: "path/to/output",
    seperatorArray: Mapper.DefSeperators_0,
    filter: new MessageFilter 
    { 
        IgnoreStart = 0, 
        IgnoreEnd = 0, 
        DtFormat = "yyyy-MM-dd HH:mm:ss,zzz" 
    }
);

MappingResult result = mapper.Map();
```

## Performance Characteristics

- **Compression Ratio**: Depends on text redundancy; log files typically see 30-60% size reduction
- **Processing Speed**: Parallel processing of messages for optimal performance
- **Memory Usage**: Scales with dictionary size and concurrent message count

## Technical Details

### Separator Configurations

```csharp
// Default - basic text tokenization
string[] DefSeperators_0 = { " ", ",", ".", "(", ")" };

// XML-aware - preserves XML structure
string[] XmlSeperators_1 = { " ", ",", ".", "(", ")", "<", "/>", "=" };

// Comprehensive - aggressive tokenization
string[] AllSeperators_2 = { " ", ",", ".", "(", ")", "<", "/>", "=", 
                              "[", "]", "{", "}", "$", "#", "@", "!", 
                              "%", "^", "&", "*", "_", "-", "+", ":", "'" };
```

### Token Generation Strategy

Tokens are generated in order of increasing length:
1. Single characters: `~a` through `~z`, `~0` through `~9`
2. Two characters: `~aa`, `~ab`, ..., `~99`
3. Three characters: `~aaa`, `~aab`, ..., `~zzz`

The special character `~` (configurable) is used as a prefix to distinguish tokens from regular text.

## License

This project incorporates the **dawgdic** library, which is licensed under the BSD 3-Clause License:

```
Copyright (c) 2009-2012, Susumu Yata
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, 
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, 
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.
- Neither the name of the University of Tokushima nor the names of its 
  contributors may be used to endorse or promote products derived from this 
  software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.
```

**LIM Project**: The original LIM code and wrapper implementations are similarly released under the BSD 3-Clause License to maintain compatibility with the underlying dawgdic library.

## Use Cases

- **Log File Management**: Compress verbose application logs while maintaining searchability
- **Data Archival**: Reduce storage costs for text-heavy datasets
- **Development and Testing**: Work with large log files on development machines with limited storage
- **Data Analysis**: Reduce I/O overhead when processing large text corpora

## Limitations

- Optimized for text with high redundancy (repeated words/phrases)
- Requires initial full-file analysis pass
- Platform-specific (Windows) due to native DLL
- Best results with structured text (logs, XML, JSON)

## Future Enhancements

Potential areas for improvement:
- Cross-platform support (Linux/macOS)
- Streaming compression for real-time logs
- Dictionary persistence and reuse across files
- Integration with more text processing pipelines
- Enhanced search capabilities on compressed data

## Contributing

Contributions are welcome! Areas of interest:
- Performance optimization
- Cross-platform support
- Additional separator configurations
- Improved compression algorithms
- Documentation and examples

## Acknowledgments

- **dawgdic library** by Susumu Yata - provides the core DAWG implementation
- IBM's open-source contributions - inspiration for the mapping approach

---

*Less is More - Compress intelligently, search efficiently, restore completely.*
