#include "st/core/Game.hpp"

#include "st/Constants.hpp"
#include "st/combat/Combat.hpp"
#include "st/endings/FinalBattle.hpp"
#include "st/items/ItemFactory.hpp"
#include "st/story/ChanceNode.hpp"
#include "st/story/CombatNode.hpp"
#include "st/story/EndingNode.hpp"
#include "st/story/FinalBattleNode.hpp"
#include "st/story/HubNode.hpp"
#include "st/story/SceneNode.hpp"

namespace st {

namespace {

std::string actTitle(ActStage act) {
  switch (act) {
    case ActStage::Prologue:
      return "ПРОЛОГ: РАЗРЫВ";
    case ActStage::Act1:
      return "АКТ 1: ЭХО ДОМА (Эфир)";
    case ActStage::Act2:
      return "АКТ 2: ГОРОД ТЕНЕЙ (Лимб)";
    case ActStage::Act3:
      return "АКТ 3: ВРАТА ПРОБУЖДЕНИЯ (Изнанка)";
    case ActStage::Ending:
      return {};
  }
  return {};
}

}  // namespace

Game::Game(std::unique_ptr<StoryTree> tree, std::unique_ptr<ConsoleView> view,
           std::unique_ptr<Random> random)
    : tree_(std::move(tree)),
      view_(std::move(view)),
      random_(std::move(random)) {}

void Game::run() {
  view_->showTitle();
  currentNodeId_ = tree_->startNodeId();

  while (running_) {
    const auto& node = tree_->getNode(currentNodeId_);
    handleActTransition(node->act());
    pendingNodeId_ = currentNodeId_;
    node->accept(*this);
    currentNodeId_ = pendingNodeId_;
  }
}

void Game::handleActTransition(ActStage nextAct) {
  if (nextAct == currentAct_ && actBannerShown_) {
    return;
  }
  if (nextAct != currentAct_) {
    currentAct_ = nextAct;
    player_.inventory().onActChanged();  // сброс предметов
  }
  const auto title = actTitle(currentAct_);
  if (!title.empty()) {
    view_->showActBanner(title);
  }
  actBannerShown_ = true;
}

bool Game::processEntry(Node& node) {
  if (node.entryEffect().has_value()) {
    applyEffect(*node.entryEffect(), false);
    if (checkCritical()) {
      return false;
    }
  }
  if (const auto redirect = node.checkRedirect(player_)) {
    pendingNodeId_ = *redirect;
    return false;
  }
  return true;
}

void Game::applyEffect(const Effect& effect, bool softenWhisper) {
  std::vector<std::string> messages;
  effect.apply(player_, softenWhisper, &messages);
  for (const auto& message : messages) {
    view_->showSystemMessage(message);
  }
  for (const int note : effect.notesAdded()) {
    view_->showNoteFound(note);
  }
  grantItems(effect);
}

void Game::grantItems(const Effect& effect) {
  for (const auto& itemId : effect.items()) {
    if (player_.inventory().contains(itemId)) {
      view_->showSystemMessage("Это уже с тобой.");
      continue;
    }
    while (player_.inventory().isFull()) {
      const auto index = view_->chooseItem(
          player_.inventory(), "Инвентарь полон. Что забыть навсегда?", false);
      auto forgotten = player_.inventory().removeAt(*index);
      player_.modifyDarkness(cfg::inv::FORGET_DARKNESS);
      view_->showItemForgotten(forgotten->name());
    }
    auto item = ItemFactory::create(itemId);
    view_->showItemGained(item->name());
    player_.inventory().add(std::move(item));
  }
}

bool Game::checkCritical() {
  if (!player_.isThreadBroken()) {
    return false;
  }
  if (checkpoint_.has_value()) {
    view_->showCheckpointReturn();
    player_ = checkpoint_->player();
    pendingNodeId_ = checkpoint_->nodeId();
  } else {
    pendingNodeId_ = endingNodeId(EndingType::ThreadBreak);
  }
  return true;
}

void Game::presentNode(Node& node) {
  view_->showNode(node.text(), player_);
  const auto choices = node.availableChoices(player_);
  if (choices.empty()) {
    running_ = false;  // защита от тупиков
    return;
  }
  const auto selected = selectChoice(choices);
  if (!selected.has_value()) {
    return;
  }
  applyChoice(*choices[*selected]);
}

std::optional<std::size_t> Game::selectChoice(
    const std::vector<const Choice*>& choices) {
  const bool blind = player_.hasStatus(StatusEffect::Blindness);
  const bool featherActive =
      !blind &&
      player_.inventory().contains(std::string(itemsid::ARCHIVIST_FEATHER));

  view_->showChoices(choices, featherActive);

  const bool alienHand = player_.hasStatus(StatusEffect::AlienHand) &&
                         currentAct_ == ActStage::Act2;
  if (player_.hasStatus(StatusEffect::MimicryControl) || alienHand) {
    if (player_.hasStatus(StatusEffect::MimicryControl)) {
      player_.removeStatus(StatusEffect::MimicryControl);
    } else {
      player_.removeStatus(StatusEffect::AlienHand);
    }
    const std::size_t index = mimicry_.chooseFor(choices, *random_);
    view_->showMimicryTakesControl(choices[index]->text());
    return index;
  }

  while (true) {
    const auto input = view_->readInput(choices.size());
    switch (input.kind) {
      case ConsoleView::Input::Kind::Choice:
        return input.index;
      case ConsoleView::Input::Kind::Inventory:
        if (handleInventory()) {
          return std::nullopt;
        }
        view_->showChoices(choices, featherActive);
        break;
      case ConsoleView::Input::Kind::Status:
        view_->showStatus(player_);
        break;
    }
  }
}

bool Game::handleInventory() {
  view_->showInventory(player_.inventory());
  if (player_.inventory().isEmpty()) {
    return false;
  }
  const auto index = view_->chooseItem(player_.inventory(),
                                       "Что использовать? (0 — назад)", true);
  if (!index.has_value()) {
    return false;
  }
  const auto item = player_.inventory().items()[*index];
  const auto result = item->use(player_);
  view_->showSystemMessage(result.text);
  if (result.consecrated) {
    checkpoint_.emplace(player_, currentNodeId_);
    view_->showCheckpointCreated();
  }
  return checkCritical();
}

void Game::applyChoice(const Choice& choice) {
  if (player_.hasStatus(StatusEffect::Blindness)) {
    player_.consumeStatusCharge(StatusEffect::Blindness);
  }

  if (choice.effect().has_value()) {
    const bool soften =
        choice.isWhisper() &&
        player_.inventory().contains(std::string(itemsid::MOTHER_CUP));
    if (soften) {
      view_->showSystemMessage(
          "Чашка матери теплеет в памяти — шёпот слабеет.");
    }
    applyEffect(*choice.effect(), soften);
    if (checkCritical()) {
      return;
    }
    if (player_.awareness() <= 0 && choice.awarenessZeroTarget().has_value()) {
      if (choice.awarenessZeroEffect().has_value()) {
        applyEffect(*choice.awarenessZeroEffect(), false);
        if (checkCritical()) {
          return;
        }
      }
      pendingNodeId_ = *choice.awarenessZeroTarget();
      return;
    }
  }
  pendingNodeId_ = choice.targetId();
}

void Game::visit(SceneNode& node) {
  if (!processEntry(node)) {
    return;
  }
  // штраф за трату времени в комнате.
  if (node.registerVisitAndCheckPenalty()) {
    view_->showSystemMessage(node.penaltyText());
    applyEffect(node.penaltyEffect(), false);
    if (checkCritical()) {
      return;
    }
  }
  presentNode(node);
}

void Game::visit(HubNode& node) {
  if (!processEntry(node)) {
    return;
  }
  presentNode(node);
}

void Game::visit(ChanceNode& node) {
  if (!processEntry(node)) {
    return;
  }
  view_->showNode(node.text(), player_);
  const bool success = random_->percent(node.successChance());
  if (success) {
    view_->showSystemMessage(node.successText());
    applyEffect(node.successEffect(), false);
    if (checkCritical()) {
      return;
    }
    pendingNodeId_ = node.successTarget();
  } else {
    view_->showSystemMessage(node.failText());
    applyEffect(node.failEffect(), false);
    if (checkCritical()) {
      return;
    }
    pendingNodeId_ = node.failTarget();
  }
}

void Game::visit(CombatNode& node) {
  if (!processEntry(node)) {
    return;
  }
  view_->showNode(node.text(), player_);

  Combat combat(player_, EnemyFactory::create(node.enemyId()), *view_,
                *random_);
  switch (combat.run()) {
    case CombatResult::Victory:
      applyEffect(node.victoryEffect(), false);
      if (checkCritical()) {
        return;
      }
      pendingNodeId_ = node.victoryTarget();
      break;
    case CombatResult::AwarenessCollapse:
      applyEffect(node.awarenessZeroEffect(), false);
      if (checkCritical()) {
        return;
      }
      pendingNodeId_ = node.awarenessZeroTarget();
      break;
    case CombatResult::ThreadBreak:
      (void)checkCritical();
      break;
  }
}

void Game::visit(EndingNode& node) {
  view_->showEnding(node.title(), node.text(), node.epilogue());
  running_ = false;
}

void Game::visit(FinalBattleNode& node) {
  if (!processEntry(node)) {
    return;
  }
  view_->showNode(node.text(), player_);

  FinalBattle battle(player_, *view_, mimicry_);
  const EndingType result = battle.run();
  if (result == EndingType::ThreadBreak && checkCritical()) {
    return;
  }
  pendingNodeId_ = endingNodeId(result);
}

}  // namespace st
