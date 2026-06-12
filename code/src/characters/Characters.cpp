#include "st/characters/Characters.hpp"

#include "st/Constants.hpp"
#include "st/core/Player.hpp"
#include "st/core/Random.hpp"
#include "st/mechanics/Types.hpp"
#include "st/story/Choice.hpp"

namespace st {

using namespace cfg::finalcfg;

Archivist::Archivist()
    : Character("Архивариус",
                "Фигура в плаще из бумажных страниц. Тот, кто остался, когда "
                "не успел вернуться.") {}

Echo::Echo()
    : Character(
          "Эхо",
          "Девочка лет десяти с жестяной звездой. Давно не видела живых.") {}

Doppelganger::Doppelganger()
    : Character("Тень-двойник",
                "Худшая версия тебя, выученная по твоим худшим ночам.") {}

Mimicry::Mimicry()
    : Character("Мимикри",
                "Отходы подавленных эмоций, обретшие форму и голод. Учится "
                "носить тебя.") {}

namespace {

std::vector<AnswerType> twoAnswers(const Player&) {
  return {AnswerType::Truth, AnswerType::Lie};
}

Statement::Evaluator correctIs(AnswerType expected) {
  return [expected](const Player&, AnswerType answer) {
    Statement::Evaluation evaluation;
    evaluation.correct = (answer == expected);
    if (evaluation.correct) {
      evaluation.darknessDelta = CORRECT_DARKNESS;
    }
    return evaluation;
  };
}

bool hasMimicryKnowledge(const Player& player) {
  return player.hasFlag(std::string(flags::TWIST_READ)) ||
         player.hasFlag(std::string(flags::KNOW_NO_DESTROY));
}

}  // namespace

std::vector<Statement> Mimicry::makeStatements() const {
  std::vector<Statement> statements;

  statements.emplace_back("«Они будут счастливее со мной.»", twoAnswers,
                          correctIs(AnswerType::Lie));

  statements.emplace_back("«Ты создал меня сам.»", twoAnswers,
                          correctIs(AnswerType::Truth));

  statements.emplace_back(
      "«Без меня ты не выживешь.»",
      [](const Player& player) {
        std::vector<AnswerType> answers{AnswerType::Truth, AnswerType::Lie};
        if (hasMimicryKnowledge(player)) {
          answers.push_back(AnswerType::HalfTruth);
        }
        return answers;
      },
      [](const Player& player, AnswerType answer) {
        Statement::Evaluation evaluation;
        if (player.darkness() >= BLACK_AUTOFAIL_DARKNESS) {
          return evaluation;
        }
        if (hasMimicryKnowledge(player)) {
          evaluation.correct = (answer == AnswerType::HalfTruth);
          if (evaluation.correct) {
            evaluation.darknessDelta = HALF_TRUTH_DARKNESS;
            evaluation.awarenessDelta = HALF_TRUTH_AWARE;
          }
          return evaluation;
        }
        const AnswerType expected = player.darkness() <= MERGE_MAX_DARKNESS
                                        ? AnswerType::Truth
                                        : AnswerType::Lie;
        evaluation.correct = (answer == expected);
        if (evaluation.correct) {
          evaluation.darknessDelta = CORRECT_DARKNESS;
        }
        return evaluation;
      });

  statements.emplace_back("«Твоя боль — это ты.»", twoAnswers,
                          correctIs(AnswerType::Lie));

  statements.emplace_back("«Ты можешь меня уничтожить полностью.»", twoAnswers,
                          correctIs(AnswerType::Lie));

  return statements;
}

std::size_t Mimicry::chooseFor(const std::vector<const Choice*>& choices,
                               Random& random) const {
  for (std::size_t i = 0; i < choices.size(); ++i) {
    if (choices[i]->isParasitic()) {
      return i;
    }
  }
  return random.index(choices.size());
}

}  // namespace st
