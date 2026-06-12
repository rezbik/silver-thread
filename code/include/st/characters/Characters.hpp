#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "st/endings/Statement.hpp"

namespace st {

    class Choice;
    class Random;

    /// Ѕазовый персонаж.
    class Character {
    public:
        Character(std::string name, std::string description)
            : name_(std::move(name)), description_(std::move(description)) {
        }

        virtual ~Character() = default;

        [[nodiscard]] const std::string& name() const noexcept { return name_; }
        [[nodiscard]] const std::string& description() const noexcept { return description_; }

    private:
        std::string name_;
        std::string description_;
    };

    /// јрхивариус Ч бывший сп¤щий, хранитель чужих дорог.
    class Archivist final : public Character {
    public:
        Archivist();
    };

    /// Ёхо Ч девочка с жест¤ной звездой, потенциальный союзник.
    class Echo final : public Character {
    public:
        Echo();
    };

    /// “ень-двойник из гостиной.
    class Doppelganger final : public Character {
    public:
        Doppelganger();
    };

    /// ћимикри Ч финальный босс: утверждени¤ финала и захват выборов.
    class Mimicry final : public Character {
    public:
        Mimicry();

        /// 5 утверждений финальной битвы ѕравды и Ћжи.
        [[nodiscard]] std::vector<Statement> makeStatements() const;

        [[nodiscard]] std::size_t chooseFor(const std::vector<const Choice*>& choices,
            Random& random) const;
    };

    }  // namespace st