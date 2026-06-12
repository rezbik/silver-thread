#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace st {

class Player;

/// Варианты ответа в битве Правды и Лжи
enum class AnswerType { Truth, Lie, HalfTruth };

[[nodiscard]] inline std::string answerLabel(AnswerType answer) {
  switch (answer) {
    case AnswerType::Truth:
      return "Правда";
    case AnswerType::Lie:
      return "Ложь";
    case AnswerType::HalfTruth:
      return "Полуправда: ты часть меня, но не весь я";
  }
  return {};
}

/// Утверждение Мимикри в финальной битве.
class Statement {
 public:
  struct Evaluation {
    bool correct{false};
    int darknessDelta{0};
    int awarenessDelta{0};
  };

  using AnswerProvider = std::function<std::vector<AnswerType>(const Player&)>;
  using Evaluator = std::function<Evaluation(const Player&, AnswerType)>;

  Statement(std::string text, AnswerProvider answers, Evaluator evaluator)
      : text_(std::move(text)),
        answers_(std::move(answers)),
        evaluator_(std::move(evaluator)) {}

  [[nodiscard]] const std::string& text() const noexcept { return text_; }
  [[nodiscard]] std::vector<AnswerType> availableAnswers(
      const Player& player) const {
    return answers_(player);
  }
  [[nodiscard]] Evaluation evaluate(const Player& player,
                                    AnswerType answer) const {
    return evaluator_(player, answer);
  }

 private:
  std::string text_;
  AnswerProvider answers_;
  Evaluator evaluator_;
};

}  // namespace st
