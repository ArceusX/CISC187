//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#include "game.hpp"
#include "computer_player.hpp"

#include <iostream>
#include <string>
#include <random>
#include <vector>

using std::string;
using std::size_t;
using std::uint32_t;

static mesa::game game;

void make_players(const mesa::option& o) {
    if (o.has_ai) {
        game.player1 = get_entry("Human player name: ");
        game.player2 = "HAL 9000";
    } else {
        game.player1 = get_entry("First player name: ");
        game.player2 = get_entry("Second player name: ");
    }
}

void make_heaps(const mesa::option& o) {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    static std::uniform_int_distribution<> random_heaps {3, 13};
    static std::uniform_int_distribution<> random_stones{1, 17};

    if (o.piles && o.stones) {
        game.stones = std::vector<uint32_t> (o.piles, o.stones);
    } else if (o.piles) {
        for (auto i = 0u; i < o.piles; ++i) {
            game.stones.push_back(random_stones(gen));
        }
    } else if (o.stones) {
        game.stones = std::vector<uint32_t> (random_heaps(gen), o.stones);
    } else {
        for (auto i = 0; i < random_heaps(gen); ++i) {
            game.stones.push_back(random_stones(gen));
        }
    }
}

void play(const mesa::option& o) {
    make_heaps(o);

    while (!game.stones.empty()) {
        auto heap = 0u;
        auto take = 0u;

        print_stones();
        prompt_player();

        if (!game.player1_turn && o.has_ai) {
            evaluate(game.stones);
            heap = choose_heap(0);
            take = how_many();
            std::cout << game.player2 << " removed " 
                      << take << " stones from heap " << heap << ".\n";
        } else {
            heap = choose_heap();
            take = how_many(heap);
        }

        remove_from(heap, take);

        if (!game.stones.empty()) {
            game.player1_turn = !game.player1_turn;
        }
    }
    declare_winner();
}

void remove_from(const uint32_t pos, const uint32_t amount) {
    int count = game.stones[pos] - amount;

    if (count <= 0) {
        game.stones.erase(game.stones.begin() + pos);
    } else {
        game.stones[pos] = count;
    }
}

void print_stones() {
    std::cout << '\n';
    int c = -1;
    for (const auto& pile: game.stones) {
        std::cout << "Heap " << ++c << (pile<10?" [ ":" [") << pile << "]: ";
        std::cout << string(pile, '*') << '\n';;
    }
}

string get_entry (const string& prompt) {
    std::cout << prompt;
    string line;
    while (getline(std::cin, line)) {
        if (!line.empty()) break;
        line.clear();
    }
    return line;
}

uint32_t get_val (const string& prompt) {
    std::cout << prompt;
    string line;
    auto val = UINT32_MAX;
    while (getline(std::cin, line)) {
        try {
            val = std::stoul(line);
        } catch ( ... ) {
            std::cerr << "bad input. try again\n";
        }
        if (!line.empty()) break;

        line.clear();
    }
    return val;
}

void declare_winner() {
    if(game.player1_turn) {
        std::cout << game.player1;
    } else {
        std::cout << game.player2;
    }
    std::cout << " wins!!\n";
}

void prompt_player() {
    if(game.player1_turn) {
        std::cout << game.player1 << "'s turn\n";
    } else {
        std::cout << game.player2 << "'s turn\n";
    }
}


uint32_t choose_heap () {
    auto heap = 0u;
    if(game.stones.size() == 1ul) {
        return heap;
    }
    heap = UINT32_MAX;
    while (heap >= game.stones.size()) {
        heap = get_val("Which heap? ");
        if (heap >= game.stones.size()) {
            std::cout << "   No such heap.  Try again\n";
        }
    }
    return heap;
}

uint32_t how_many (size_t pos) {
    auto take = 0u;
    while (take == 0 || take > game.stones[pos]) {
        take = get_val("How many stones? ");

        if (take == 0) {
            std::cout << "   Must take at least 1 stone.\n";
        } else if (take > game.stones[pos]) {
            std::cout << "   There aren't that many stones in this heap.\n";
        }
    }
    return take;
}


