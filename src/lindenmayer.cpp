//
// Created by Niccolo on 28/03/2025.
//

#include "lindenmayer.h"

    std::string Lindenmayer::iterate(const std::string &current_string) {
        std::string next_string = "";
        for (char c : current_string) {
            auto it = production_rules.find(c);
            if (it != production_rules.end()) {
                next_string += it->second;
            }
            else {
                // Produzione identità
                next_string += c;
            }
        }
        return next_string;
    }

std::string Lindenmayer::cleanup(const std::string &current_string) {
        std::string next_string = "";
        for (char c : current_string) {
            if (c != 'X') {
                next_string += c;
            }
            else {
                next_string += 'F';
            }
        }
        return next_string;
}

std::string Lindenmayer::generate(const std::string &axiom, unsigned int n_iterations, bool need_cleanup) {
        std::string next = axiom;
        for (unsigned int i = 0; i < n_iterations; i++) {
            next = iterate(next);
        }
        if (need_cleanup) {
            next = cleanup(next);
        }
        return next;
    }

