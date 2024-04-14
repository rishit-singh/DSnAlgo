#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Defines the size of the alphabet for bucket size.
 */
constexpr unsigned int BucketSize = 26;

/**
 * @brief Trim whitespace from the beginning of a string.
 * 
 * @param s The string to trim.
 */
inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

/**
 * @brief Trim whitespace from the end of a string.
 * 
 * @param s The string to trim.
 */
inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

/**
 * @brief Perform counting sort on an array of strings based on a specific position.
 * 
 * @param arr The array of strings to be sorted.
 * @param position The position in the strings to consider for sorting.
 */
void countingSort(std::vector<std::string>& arr, const int position)
{
    std::vector<int> counts(BucketSize, 0); /**< Array to store counts for each character. */
    std::vector<std::string> output(arr.size()); /**< Array to store the sorted output. */

    // Count occurrences of each character at the given position
    for (int x = 0; x < arr.size(); x++)
        counts[(position < arr.size()) ? arr[x][position] - 'a' : 0]++;

    // Compute cumulative counts
    for (int x = 1; x < counts.size(); x++)
        counts[x] += counts[x - 1];

    // Place elements in the correct position in the output array
    for (int x = arr.size() - 1; x >= 0; x--)
    {
        int index = (position < arr.size()) ? arr[x][position] - 'a' : 0;
        output[counts[index] - 1] = arr[x];
        counts[index]--;
    }

    // Update the input array with the sorted output
    arr = output;
}

/**
 * @brief Perform radix sort on an array of strings with a given maximum length.
 * 
 * @param arr The array of strings to be sorted.
 * @param max The maximum length of the strings.
 */
void radixSort(std::vector<std::string> &arr, const int max)
{
    // Iterate over each position from the end of the strings
    for (int x = max - 1; x >= 0; x--)
        countingSort(arr, x);
}

/**
 * @brief Load names from a file and return them as a vector of strings.
 * 
 * @param path The path to the file containing the names.
 * @return std::vector<std::string> Vector of strings containing the loaded names.
 */
std::vector<std::string> loadNames(const std::string path)
{
    // Open the file
    std::ifstream fp(path);

    // Initialize a vector to store names
    std::vector<std::string> names;

    // Temporary variable to store each name read from the file
    std::string name;

	if (!fp.is_open())
		throw std::runtime_error("Failed to open the file");

    // Read names from the file line by line
    while (std::getline(fp, name))
    {
        // Trim leading and trailing whitespace from the name
        ltrim(name);
        rtrim(name);

        // Add the trimmed name to the vector
        names.push_back(name);
    }

    // Close the file
    fp.close();

    // Return the vector of names
    return names;
}


int main()
{
	std::vector<std::string> names = loadNames("names.txt");

	std::cout << "\nThe size of vector is: " << names.size() << "\n";
	std::cout << "\nThe elements before sorting: \n";
	
	for (auto name : names)
		std::cout << name << ' ';
	
	radixSort(names, 5);

	std::cout << "\nThe elements after sorting: \n";
	
	for (auto name : names)
		std::cout << name << ' ';
	
	// time complexity of radix sort: O(5n)
	return 0;
}
