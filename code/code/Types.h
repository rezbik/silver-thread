#pragma once

#include <string>

// Типы базовых ресурсов из GDD [cite: 26, 36]
enum class ResourceType {
  WILL,            // Воля [cite: 27]
  AWARENESS,       // Осознанность [cite: 28]
  THREAD_TENSION,  // Натяжение нити [cite: 29]
  THREAD_DARKNESS  // Чернота нити [cite: 54]
};

// Типы требований для совершения выбора (UML: RequirementType)
enum class RequirementType {
  AWARENESS_MIN,
  WILL_MIN,
  HAS_FLAG,
  HAS_ITEM,
  HAS_ANCHOR,
  THREAD_DARKNESS_MAX
};

// Структуры для квестовых элементов и записок
struct Anchor {
  std::string name;
  int actNumber;
  std::string description;
};

struct DreamerNote {
  int id;
  std::string location;
  std::string text;
};
