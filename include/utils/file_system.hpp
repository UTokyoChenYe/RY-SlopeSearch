#pragma once

#include <string>
#include <vector>
#include <tuple>

// Function to load DNA sequences from a single FASTA file
std::vector<std::string> load_sequences(const std::string& file_path);

// Function to load sequences and names for evaluation from a single FASTA file
std::tuple<std::vector<std::string>, std::vector<std::string>> load_sequences_for_evaluation(const std::string& file_path);

// Function to load sequences and names for evaluation from multiple FASTA files in a directory
std::tuple<std::vector<std::string>, std::vector<std::string>> load_sequences_from_multiple_files(const std::string& directory);