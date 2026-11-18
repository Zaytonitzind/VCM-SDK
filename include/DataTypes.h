//
// Created by mdp on 29.09.2026.
//

#ifndef VCM_SDK_DATATYPES_H
#define VCM_SDK_DATATYPES_H
#include <cstdint>
#include <any>
#include <typeindex>
#include <typeinfo>


using DataType = std::type_index;

using RuntimeData = std::any;


using PinId = uint32_t;
using NodeId = uint32_t;
using LinkId = uint32_t;

class Graph;
class Pin;

struct PinEndpoint {
    NodeId nodeId;
    PinId pinId;

    PinEndpoint() : nodeId(0), pinId(0) {}
    PinEndpoint(NodeId nodeId, PinId pinId) :
    nodeId(nodeId), pinId(pinId) {}

    [[nodiscard]] Pin* getPin(Graph& graph) const;
    [[nodiscard]] const Pin* getPin(const Graph& graph) const;

    PinEndpoint(const Graph& graph, PinId pinId);

    bool operator==(const PinEndpoint&) const = default;
};

struct InputConnection
{
    PinId pinId;
    const Pin* sourcePin;
};

uint32_t generateId() noexcept;

#endif //VCM_SDK_DATATYPES_H
