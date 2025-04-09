//
// Created by Niccolo on 28/03/2025.
//

#ifndef LINDENMAYER_H
#define LINDENMAYER_H
#include <map>
#include <set>
#include <string>


class Lindenmayer {
public:
    Lindenmayer(const std::set<char> &alphabeth, const std::map<char, std::string> &production_rules)
        : alphabeth(alphabeth),
          production_rules(production_rules) {
    }

    std::string iterate(const std::string &current_string);

    std::string cleanup(const std::string &current_string);

    std::string generate(const std::string &axiom, unsigned int n_iterations, bool need_cleanup = false);
private:
    std::set<char> alphabeth;
    std::map<char, std::string> production_rules;
};



#endif //LINDENMAYER_H
