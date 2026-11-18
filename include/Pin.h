//
// Created by mdp on 29.09.2026.
//

#ifndef VCM_SDK_PIN_H
#define VCM_SDK_PIN_H

#include <utility>
#include "DataTypes.h"
#include "array"
#include <string_view>
#include <stdexcept>

enum class PinDirection {
    Input,
    Output
};

enum class ConnectionMode {
    Single,
    Multiple
};


class Pin {
public:
    template<typename T>
    static Pin create(
        PinDirection direction,
        std::string_view name,
        ConnectionMode mode = ConnectionMode::Single)
    {
        return Pin(direction, name, typeid(T), mode);
    }



    [[nodiscard]] int getId() const noexcept { return static_cast<int>(m_id); }
    [[nodiscard]] std::string_view getName() const noexcept { return m_name.data(); }
    [[nodiscard]] PinDirection getDirection() const noexcept { return m_direction; }
    [[nodiscard]] ConnectionMode getConnectionMode() const noexcept { return m_connectionMode; }
    [[nodiscard]] const DataType& getDataType() const noexcept {return m_type; }

    template<typename T> 
    const T& value() const {return std::any_cast<const T&>(m_value); }


    [[nodiscard]] bool hasValue() const noexcept {
        return m_value.has_value();
    }

    void setValue(RuntimeData value) { m_value = std::move(value); }
    void clearValue() noexcept { m_value.reset(); }

    [[nodiscard]] bool connectable(const Pin& other) const noexcept { return this->m_type == other.m_type; }

private:
    RuntimeData m_value;
    DataType m_type;
    std::array<char, 16> m_name{};
    PinDirection m_direction;
    ConnectionMode m_connectionMode;
    PinId m_id;

    Pin(
        const PinDirection direction,
        std::string_view name,
        DataType type,
        const ConnectionMode connectionMode = ConnectionMode::Single) : m_type(type),
                                                                        m_direction(direction),
                                                                        m_connectionMode(connectionMode),
                                                                        m_id(generateId()) {

        if (name.size() > m_name.size()) {
            throw std::invalid_argument("name too long");
        }
        std::ranges::copy(name, m_name.begin());
    }

};

#endif //VCM_SDK_PIN_H
