//
// Created by mdp on 01.10.2026.
//
#include "DataTypes.h"
#include "Node.h"

namespace {
    uint32_t UNIQUE_ID = 0;
}

uint32_t generateId() noexcept {
    return ++UNIQUE_ID;
};