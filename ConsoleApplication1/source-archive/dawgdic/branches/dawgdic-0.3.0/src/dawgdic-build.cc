#include "dawgdic/dawg-builder.h"
#include "dawgdic/dictionary-builder.h"

#include <fstream>
#include <iostream>

// Builds a dictionary from a sorted lexicon.
bool BuildDictionary(const char *lexicon_file_name, dawgdic::Dictionary *dic)
{
	std::cerr << "input: " << lexicon_file_name << std::endl;

	// Opens an input file.
	std::ifstream lexicon_file(lexicon_file_name, std::ios::binary);
	if (!lexicon_file.is_open())
	{
		std::cerr << "error: failed to open file: "
			<< lexicon_file_name << std::endl;
		return false;
	}

	// Reads keys and inserts them into a dawg.
	dawgdic::DawgBuilder dawg_builder;
	std::string key;
	std::size_t key_count = 0;
	while (std::getline(lexicon_file, key))
	{
		if (!dawg_builder.Insert(key.c_str()))
		{
			std::cerr << "error: failed to insert key: " << key << std::endl;
			return false;
		}

		if (++key_count % 10000 == 0)
			std::cerr << "no. keys: " << key_count << '\r';
	}
	dawgdic::Dawg dawg;
	dawg_builder.Finish(&dawg);

	std::cerr << "no. keys: " << key_count << std::endl;
	std::cerr << "no. states: "
		<< dawg.num_of_states() << std::endl;
	std::cerr << "no. transitions: "
		<< dawg.num_of_transitions() << std::endl;
	std::cerr << "no. merged states: "
		<< dawg.num_of_merged_states() << std::endl;
	std::cerr << "no. merging states: "
		<< dawg.num_of_merging_states() << std::endl;

	// Builds a dictionary from a dawg.
	dawgdic::BaseType num_of_unused_units;
	if (!dawgdic::DictionaryBuilder::Build(dawg, dic, &num_of_unused_units))
	{
		std::cerr << "error: failed to build dictionary" << std::endl;
		return false;
	}
	double unused_ratio = 100.0 * num_of_unused_units / dic->size();

	std::cerr << "no. elements: " << dic->size() << std::endl;
	std::cerr << "no. unused elements: " << num_of_unused_units
		<< " (" << unused_ratio << "%)" << std::endl;
	std::cerr << "dictionary size: " << dic->total_size() << std::endl;

	return true;
}

// Writes a dictionary to a file.
bool SaveDictionary(const dawgdic::Dictionary &dic,
	const char *dic_file_name)
{
	std::cerr << "output: " << dic_file_name << std::endl;

	// Creates an output file.
	std::ofstream dic_file(dic_file_name, std::ios::binary);
	if (!dic_file.is_open())
	{
		std::cerr << "error: failed to open file: "
			<< dic_file_name << std::endl;
		return false;
	}

	if (!dic.Write(&dic_file))
	{
		std::cerr << "error: failed to write dictionary to file: "
			<< dic_file_name << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	// Checks arguments.
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0]
			<< " LexiconFile DicFile" << std::endl;
		return 1;
	}

	const char *lexicon_file_name = argv[1];
	const char *dic_file_name = argv[2];

	dawgdic::Dictionary dic;
	if (!BuildDictionary(lexicon_file_name, &dic))
		return 1;

	if (!SaveDictionary(dic, dic_file_name))
		return 1;

	return 0;
}
