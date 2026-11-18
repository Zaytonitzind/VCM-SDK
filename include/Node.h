//
// Created by mdp on 29.09.2026.
//

#ifndef VCM_SDK_NODE_H
#define VCM_SDK_NODE_H

#include <vector>
#include <string>

#include "DataTypes.h"

#include "Pin.h"

class Node {
public:
    Node();
    virtual ~Node() = default;
    [[nodiscard]] virtual std::string name() const = 0;
    virtual void process (const std::vector<InputConnection>& inputs) = 0;

    template<typename T>
    void addInputPin(const std::string_view& name);

    template<typename T>
    void addOutputPin(const std::string_view& name, ConnectionMode mode = ConnectionMode::Single);

    [[nodiscard]] NodeId id() const noexcept;

    //Вопрос о необходимости доступа ко всем пинам
    [[nodiscard]] const std::vector<Pin>* Pins() const noexcept;
    [[nodiscard]] const Pin* pin(PinId id) const noexcept;
    [[nodiscard]] const Pin *pin(std::string_view name) const;

    Pin* pin(PinId id) noexcept;
    Pin* pin(std::string_view name);

    void draw();

    template<typename T>
    const T* getInput(const std::vector<InputConnection>& inputs, std::string_view name) {
        const auto id = pin(name)->getId();

        for (const auto& input : inputs) {
            if (id == input.pinId) {
                if (!input.sourcePin || !input.sourcePin->hasValue())
                    return nullptr;

                return &input.sourcePin->value<T>();
            }
        }
        return nullptr;
    }

protected:
    virtual void drawUI() = 0;
    NodeId m_id;
    std::vector<Pin> m_pins;
};


template<typename T>
void Node::addInputPin(const std::string_view &name) {
    m_pins.emplace_back(Pin::create<T>(PinDirection::Input, name));
}

template<typename T>
void Node::addOutputPin(const std::string_view &name, ConnectionMode mode) {
    m_pins.emplace_back(Pin::create<T>(PinDirection::Output, name, mode));
}

#endif //VCM_SDK_NODE_H
