#include "st/endings/FinalBattle.hpp"

#include "st/Constants.hpp"
#include "st/characters/Characters.hpp"
#include "st/core/Player.hpp"
#include "st/mechanics/Types.hpp"
#include "st/ui/ConsoleView.hpp"

namespace st {

using namespace cfg::finalcfg;

FinalBattle::FinalBattle(Player& player, ConsoleView& view,
                         const Mimicry& mimicry)
    : player_(player), view_(view), mimicry_(mimicry) {}

EndingType FinalBattle::run() {
  const auto statements = mimicry_.makeStatements();
  bool limited = false;
  bool exhaustionPenaltyPending = player_.hasStatus(StatusEffect::Exhaustion);

  std::size_t number = 1;
  for (const auto& statement : statements) {
    view_.showStatement(number++, statement.text());
    const auto answers = statement.availableAnswers(player_);
    const AnswerType answer = view_.readAnswer(answers);
    const auto result = statement.evaluate(player_, answer);

    if (result.correct) {
      player_.modifyDarkness(result.darknessDelta);
      player_.modifyAwareness(result.awarenessDelta);
      player_.registerCorrectFinalAnswer();
      view_.showSystemMessage(
          "Мимикри вздрагивает. Названная правда перестаёт притворяться.");
    } else {
      const int penalty =
          exhaustionPenaltyPending ? WRONG_AWARENESS_EXHAUST : WRONG_AWARENESS;
      exhaustionPenaltyPending = false;
      player_.modifyAwareness(penalty);
      view_.showSystemMessage(
          "Ошибка. Слова Мимикри въедаются в мысли, как крюки.");
    }

    if (player_.awareness() <= 0) {
      player_.modifyDarkness(ZERO_AWARENESS_DARKNESS);
      limited = true;
      view_.showSystemMessage(
          "Слова Мимикри становятся твоими мыслями раньше, чем ты успеваешь их "
          "услышать.");
      break;
    }
  }

  const auto allChoices = buildFinalChoices(limited);
  std::vector<const FinalChoice*> available;
  for (const auto& choice : allChoices) {
    if (choice.isAvailable(player_)) {
      available.push_back(&choice);
    }
  }

  view_.showFinalChoices(available);
  const std::size_t selected = view_.readFinalChoice(available.size());
  return available[selected]->execute(player_);
}

bool FinalBattle::trueMergeConditionsMet(const Player& player) {
  return player.anchorCount() >= TRUE_MERGE_ANCHORS &&
         player.hasFlag(std::string(flags::ECHO_SAVED)) &&
         player.hasFlag(std::string(flags::TWIST_READ)) &&
         player.noteCount() >= TRUE_MERGE_NOTES &&
         player.darkness() <= TRUE_MERGE_MAX_DARKNESS &&
         player.correctFinalAnswers() >= TRUE_MERGE_MIN_CORRECT;
}

std::vector<FinalChoice> FinalBattle::buildFinalChoices(bool limited) const {
  std::vector<FinalChoice> choices;

  if (!limited) {
    choices.emplace_back(
        "Обнять Мимикри и назвать его частью себя",
        [](const Player& p) {
          return p.hasFlag(std::string(flags::TWIST_READ)) &&
                 p.darkness() <= MERGE_MAX_DARKNESS &&
                 p.correctFinalAnswers() >= MERGE_MIN_CORRECT;
        },
        [](Player& p) {
          return trueMergeConditionsMet(p) ? EndingType::TrueMerge
                                           : EndingType::IncompleteMerge;
        });

    choices.emplace_back(
        "Разорвать проекцию Мимикри",
        [](const Player& p) {
          return p.awareness() >= DENIAL_MIN_AWARENESS &&
                 p.darkness() <= DENIAL_MAX_DARKNESS;
        },
        [](Player& p) {
          p.modifyTension(DENIAL_TENSION);
          return p.isThreadBroken() ? EndingType::ThreadBreak
                                    : EndingType::Denial;
        });
  }

  choices.emplace_back(
      "Принять Мимикри как новую версию себя",
      [](const Player&) { return true; },
      [](Player&) { return EndingType::Replacement; });

  choices.emplace_back(
      "Поглотить Мимикри",
      [limited](const Player& p) {
        return limited || p.darkness() >= ABSORB_MIN_DARKNESS;
      },
      [](Player& p) {
        const bool darkConditions =
            p.darkness() >= ABSORB_MIN_DARKNESS &&
            p.hasFlag(std::string(flags::ECHO_CONSUMED)) &&
            p.hasFlag(std::string(flags::CHILDREN_CONSUMED));
        if (darkConditions) {
          return EndingType::Absorption;
        }
        p.modifyTension(ABSORB_FAIL_TENSION);
        p.modifyWill(ABSORB_FAIL_WILL);
        return p.isThreadBroken() ? EndingType::ThreadBreak
                                  : EndingType::Replacement;
      });

  return choices;
}

}  // namespace st
