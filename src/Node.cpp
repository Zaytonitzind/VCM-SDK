//
// Created by mdp on 29.09.2026.
//

#include "Node.h"
#include "ImNodes.h"


Node::Node() : m_id(generateId()) {
}


NodeId Node::id() const noexcept {return m_id;}

const std::vector<Pin> *Node::Pins() const noexcept {return &m_pins;}

Pin* Node::pin(PinId id) noexcept {
    for (auto& pin : m_pins) {
        if (pin.getId() == id) {
            return &pin;
        }
    }
    return nullptr;
}



const Pin * Node::pin(PinId id) const noexcept {
    for (const auto& pin : m_pins) {
        if (pin.getId() == id) {
            return &pin;
        }
    }
    return nullptr;
}

const Pin* Node::pin(std::string_view name) const {
    for (const auto& pin : m_pins) {
        if (pin.getName() == name) {
            return &pin;
        }
    }
    return nullptr;
}

Pin* Node::pin(std::string_view name) {
    for (auto& pin : m_pins) {
        if (pin.getName() == name) {
            return &pin;
        }
    }
    return nullptr;
}

void Node::draw() {
    ImNodes::BeginNode(m_id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Node %u", m_id);
    ImNodes::EndNodeTitleBar();

    for (const auto& pin : m_pins) {
        if (pin.getDirection() == PinDirection::Input) {
            ImNodes::BeginInputAttribute(pin.getId());
            ImGui::Text("Input %u", pin.getId());
            ImNodes::EndInputAttribute();
        }
        else {
            ImNodes::BeginOutputAttribute(pin.getId());
            ImGui::Text("Output %u", pin.getId());
            ImNodes::EndOutputAttribute();
        }
    }

    drawUI();
    ImNodes::EndNode();
}
