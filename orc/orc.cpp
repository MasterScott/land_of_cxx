#include <iostream>
#include <algorithm>
#include <random>
namespace {
    std::random_device rd;
    std::mt19937 coin(rd());
    std::uniform_int_distribution<> flip(0, 1);
}

long constexpr START_HP = 20;

class Warrior {
    std::string const _name;
    long _hp;

    public:

        Warrior(std::string const& name, long hp=START_HP):
            _name(name),
            _hp(hp)
        {
        }

        Warrior(Warrior const&) = delete;

        void attack(Warrior& other) const {
            other._hp = std::max(0L, other._hp - 1);
        }

        std::string const& name() const {
            return _name;
        }

        explicit operator bool() const {
            return _hp;
        }
};

void fight(Warrior& self, Warrior& other) {
    while(self and other) {
        Warrior *first{&self}, *second{&other};
        if(flip(coin)) {
            using std::swap; // allows argument Dependent Lookup
            swap(first, second);
        }
        first->attack(*second);
        if(*second)
            second->attack(*first);
    }
}

static const char banner [] = R"(
  _______________________-------------------                       `\
 /:--__                                                              |
||< > |                                   ___________________________/
| \__/_________________-------------------                         |
|                                                                  |
 |                               ORC                                |
 |                                                                  |
  |                                              ____________________|_
  |  ___________________-------------------------                      `\
  |/`--_                                                                 |
  ||[ ]||                                            ___________________/
   \===/___________________--------------------------
)";

int main(int argc, char * argv[]) {
    std::cout << banner << std::endl;

    Warrior me{"me"}, other{"other"};

    fight(me, other);

    Warrior& winner = me ? me : other;
    std::cout << R"(The winner is \o/ )" << winner.name() << R"( \o/)" << std::endl;

    return 0;
}
