#include "UnorderedMap.h"
#include "hash_functions.h"

#include <random>
#include <limits>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <array>

constexpr size_t MAX_TERMINAL_WIDTH = 80;
constexpr size_t N_ELEMENTS = 1e4;

static void print_sep() {
    std::cout << std::endl;
    for(size_t i = 0; i < MAX_TERMINAL_WIDTH; i++)
        std::cout << '-';
    std::cout << std::endl << std::endl;
}

struct zero_hash {
    size_t operator() (std::string const & str) const {
        return 0;
    }
};

struct first_character_hash  {
    size_t operator() (std::string const & str) const {
        if(str.length() == 0)
            return 0ull;

        return str[0];
    }
};

enum class HashType {
    ZERO,
    FIRST_CHARACTER,
    POLYNOMIAL_ROLLING,
    FNV1A
};

struct hash_selector {
    zero_hash _zero_hash;
    first_character_hash _first_char_hash;
    polynomial_rolling_hash _poly_rolling_hash;
    fnv1a_hash _fnv1a_hash;
    HashType _htype;

    public:

    hash_selector(HashType htype) 
        : _htype(htype)
    {}

    size_t operator() (std::string const & str) const {
        switch(_htype) {
            case HashType::ZERO:
                return _zero_hash(str);
            case HashType::FIRST_CHARACTER:
                return _first_char_hash(str);
            case HashType::POLYNOMIAL_ROLLING:
                return _poly_rolling_hash(str);
            case HashType::FNV1A:
                return _fnv1a_hash(str);
        }

        return 0;
    }
};

HashType prompt_hash_type() {
    using std::cin, std::cout, std::endl, std::ios;

    cout << "Which hash would you like to use:" << endl;

    struct HashChoice {
        std::string label;
        HashType type; 
    };

    std::array<HashChoice const, 4> choices = {
        HashChoice {
            .label = "Zero Hash",
            .type = HashType::ZERO,
        },
        HashChoice {
            .label = "First Character Hash",
            .type = HashType::FIRST_CHARACTER,
        },
        HashChoice {
            .label = "Polynomial Rolling Hash",
            .type = HashType::POLYNOMIAL_ROLLING,
        },
        HashChoice {
            .label = "FNV-1A",
            .type = HashType::FNV1A,
        }
    };

    for(size_t i = 0; i < choices.size(); i++)
        cout << "(" << i << "). " << choices[i].label << endl;
    

    cout << endl;

    size_t choice;

    do {
        cout << "Enter your selection: ";
        if(!(cin >> choice)) {
            cin.clear(cin.rdstate() & ~ios::failbit);

            continue;
        }

        if(choice >= choices.size())
            continue;
        
        break;
    } while(true);

    return choices[choice].type;
}

namespace fs = std::filesystem;

class AnimalDistribution {
    std::vector<std::string> animals;
    std::vector<std::string> adjectives;

    public:
    
    AnimalDistribution(fs::path const adjectives_path, fs::path const animals_path) {
        std::ifstream adjectives_file(adjectives_path);
        std::ifstream animals_file(animals_path);

        std::string line;

        while(std::getline(adjectives_file, line))
            adjectives.push_back(line);
        
        while(std::getline(animals_file, line))
            animals.push_back(line);
    }

    template<class Generator>
    std::string operator()(Generator & g) const {
        std::string animal, adjective;

        std::sample(adjectives.cbegin(), adjectives.cend(), &adjective, 1, g);
        std::sample(animals.cbegin(), animals.cend(), &animal, 1, g);

        adjective[0] = std::toupper(adjective[0]);
        
        return adjective + " " + animal;
    }

};

constexpr size_t N_SAMPLE_HASHES = 5;

int main() {
    fs::path data_files = fs::path("..") / "data_files";

    fs::path animals = data_files / "animals.txt";
    fs::path adjectives = data_files / "adjectives.txt";

    HashType htype = prompt_hash_type();

    std::random_device rd;
    std::mt19937 generator(rd());

    hash_selector hash (htype);

    AnimalDistribution distribution(adjectives, animals);

    std::cout << std::endl;
    std::cout << "Example hashes:" << std::endl;
    for(size_t i = 0; i < N_SAMPLE_HASHES; i++) {
        std::string animal = distribution(generator);
        std::cout << animal << ": " << hash(animal) << std::endl;
    }

    UnorderedMap<std::string, int, hash_selector> map(30, hash);

    for(size_t i = 0; i < N_ELEMENTS; i++) {
        map.insert({distribution(generator), 0});
    }

    std::vector<size_t> bucket_sizes(map.bucket_count());
    size_t max_count = std::numeric_limits<size_t>::min();
    for(size_t bucket = 0; bucket < map.bucket_count(); bucket++) {
        bucket_sizes[bucket] = map.bucket_size(bucket);
        max_count = std::max(max_count, bucket_sizes[bucket]);
    }

    double load_variance = std::numeric_limits<double>::max();
    if(map.size() > 1) {
        load_variance = 0;
        double res;
        for(size_t i = 0; i < map.bucket_count(); i++) {
            res = bucket_sizes[i] - map.load_factor();
            load_variance += res * res;
        }
        load_variance /= map.size() - 1;
    }

    print_sep();

    for(size_t bucket = 0; bucket < map.bucket_count(); bucket++) {
        std::cout << std::setw(5) << bucket << ": ";
        
        size_t width = MAX_TERMINAL_WIDTH * 
            (static_cast<float>(bucket_sizes[bucket]) / static_cast<float>(max_count));
    
        for(size_t i = 0; i < width; i++) {
            std::cout << "#";
        }

        std::cout << std::endl;
    }

    print_sep();

    std::cout << "  Size: " << map.size() << std::endl;
    std::cout << "  Buckets: " << map.bucket_count() << std::endl;
    std::cout << "  Load factor: " << map.load_factor() << std::endl;
    std::cout << "  Load variance: " << load_variance << std::endl;

    return 0;
}
