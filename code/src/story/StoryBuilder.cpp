#include "st/story/StoryBuilder.hpp"

#include "st/Constants.hpp"
#include "st/combat/Enemy.hpp"
#include "st/core/Player.hpp"
#include "st/story/ChanceNode.hpp"
#include "st/story/CombatNode.hpp"
#include "st/story/EndingNode.hpp"
#include "st/story/FinalBattleNode.hpp"
#include "st/story/HubNode.hpp"
#include "st/story/SceneNode.hpp"

namespace st {

namespace {
constexpr std::string_view kStartNode = "0_1";

int visitedLimboCount(const Player& p) {
  int count = 0;
  count += p.hasFlag(std::string(flags::VISITED_SQUARE)) ? 1 : 0;
  count += p.hasFlag(std::string(flags::VISITED_LIBRARY)) ? 1 : 0;
  count += p.hasFlag(std::string(flags::VISITED_BRIDGE)) ? 1 : 0;
  count += p.hasFlag(std::string(flags::VISITED_CAROUSEL)) ? 1 : 0;
  return count;
}
}  // namespace

std::unique_ptr<StoryTree> StoryBuilder::build() const {
  auto tree = std::make_unique<StoryTree>(std::string(kStartNode));
  buildPrologue(*tree);
  buildAct1(*tree);
  buildAct2(*tree);
  buildAct3(*tree);
  buildEndings(*tree);
  return tree;
}

void StoryBuilder::buildPrologue(StoryTree& tree) const {
  using namespace cfg::prologue;

  {
    auto node = std::make_shared<SceneNode>(
        "0_1", ActStage::Prologue,
        "Веки тяжелеют. Книга соскальзывает с груди. Часы в коридоре отбивают "
        "полночь —\n"
        "но звук растягивается, как жвачка...\n\nТик... таааак... тиииии...");
    node->addChoice(Choice("Провалиться в сон", "0_2"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "0_2", ActStage::Prologue,
        "Ты открываешь глаза и видишь потолок. Знакомую трещину в форме "
        "молнии.\n"
        "Только смотришь ты на неё снизу — а сам висишь под ней.\n\n"
        "В метре под тобой, на кровати, лежит твоё тело. Грудь поднимается "
        "слишком медленно.\n"
        "От твоей груди — здесь, наверху — тянется тонкая серебристая линия к "
        "его сердцу.\n\n"
        "В углу комнаты, в тени шкафа, что-то шевелится.");
    node->addChoice(Choice("Коснуться своего тела", "0_3a"));
    node->addChoice(Choice("Изучить Нить", "0_3b"));
    node->addChoice(Choice("Посмотреть в угол шкафа", "0_3c"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "0_3a", ActStage::Prologue,
        "Твоя ладонь проходит сквозь щёку спящего, как сквозь холодный туман.\n"
        "Что-то отталкивает тебя — резко, со звоном. Тебя отбрасывает к "
        "стене,\n"
        "нить дёргается, как леска с крупной рыбой.");
    node->setEntryEffect(Effect().will(TOUCH_WILL).tension(TOUCH_TENSION));
    node->addChoice(Choice("Прийти в себя", "0_4"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "0_3b", ActStage::Prologue,
        "Нить пульсирует в такт твоему — нет, его — сердцу. Пока она цела, ты "
        "можешь\n"
        "вернуться. Натянется слишком сильно — порвётся. Потускнеет — забудешь "
        "дорогу домой.\n\n"
        "Получено знание: «Механика Нити».");
    node->setEntryEffect(
        Effect().awareness(STUDY_AWARE).addFlag(flags::KNOW_THREAD));
    node->addChoice(Choice("Оторвать взгляд от Нити", "0_4"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "0_3c", ActStage::Prologue,
        "Из тени на тебя смотрит... ты. Сгусток черноты, принявший твою позу.\n"
        "Он медленно поднимает руку — и ты чувствуешь, как поднимается твоя.\n"
        "Он улыбается твоими губами, ещё не зная, как именно это делается.\n\n"
        "Получено знание: «Мимикри».");
    node->setEntryEffect(Effect()
                             .awareness(LOOK_AWARE)
                             .will(LOOK_WILL)
                             .addFlag(flags::KNOW_MIMICRY));
    node->addChoice(Choice("Отшатнуться", "0_4"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "0_4", ActStage::Prologue,
        "Сгусток отделяется от шкафа и делает шаг к кровати. Один.\n\n"
        "Ты слышишь голос — старый, шелестящий, будто из-за толстого стекла:\n"
        "— Беги, спящий. Или садись в кресло наблюдателя — навсегда.\n\n"
        "Из стены выступает фигура в плаще из бумажных страниц.\n"
        "Архивариус: «У тебя есть время до рассвета. Дверь твоей комнаты ведёт "
        "не в коридор. Иди.»");
    node->addChoice(Choice("Спросить, кто он", "0_5a"));
    node->addChoice(Choice("Спросить, как победить Мимикри", "0_5b"));
    node->addChoice(Choice("Молча идти к двери", "1_1")
                        .withEffect(Effect().will(SILENT_WILL)));
    tree.addNode(std::move(node));
  }
  {
    auto node =
        std::make_shared<SceneNode>("0_5a", ActStage::Prologue,
                                    "— Кто ты?\n\nБумага шуршит, будто кто-то "
                                    "перелистывает целую библиотеку сразу.\n"
                                    "— Тот, кто остался, когда не успел "
                                    "вернуться. Я — только память о выходе.\n\n"
                                    "«Твой враг не ломает двери. Он примеряет "
                                    "твоё лицо. Чем дольше ты здесь,\n"
                                    "тем лучше он носит тебя там.»");
    node->setEntryEffect(Effect().awareness(WHO_AWARE));
    node->addChoice(Choice("Идти к двери", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "0_5b", ActStage::Prologue,
        "— Как его победить?\n\n— Победить? Неверное слово. То, что выросло из "
        "тебя, нельзя\n"
        "убить без остатка. Можно выгнать — и потерять часть себя. Можно "
        "пустить внутрь — и\n"
        "утонуть. Можно назвать по имени — и тогда оно перестанет притворяться "
        "тобой.\n\n"
        "«Собирай Якоря. Вспоминай не только хорошее. Особенно — не только "
        "хорошее.»");
    node->setEntryEffect(Effect().awareness(HOW_AWARE));
    node->addChoice(Choice("Идти к двери", "1_1"));
    tree.addNode(std::move(node));
  }
}

// АКТ 1 ============================================================

void StoryBuilder::buildAct1(StoryTree& tree) const {
  using namespace cfg::act1;

  {
    auto hub = std::make_shared<HubNode>(
        "1_1", ActStage::Act1,
        "Дверь открывается в твою же квартиру — но вытянутую, как отражение в "
        "чайной ложке.\n"
        "Коридор бесконечен. Обои дышат. На полу — фотографии лицом вниз.");
    hub->addChoice(
        Choice("Кухня", "1_2")
            .require(Requirement::lacksAnchor(std::string(anchors::CUP))));
    hub->addChoice(
        Choice("Детская — старая комната", "1_3")
            .require(Requirement::lacksAnchor(std::string(anchors::DIARY))));
    hub->addChoice(Choice("Ванная", "1_4")
                       .require(Requirement::lacksFlag(
                           std::string(flags::BATHROOM_CLOSED))));
    hub->addChoice(Choice("Гостиная — выход в Лимб", "1_5")
                       .require(Requirement::minAnchors(ANCHORS_FOR_EXIT)));
    tree.addNode(std::move(hub));
  }
  // --- Кухня ---
  {
    auto node = std::make_shared<SceneNode>(
        "1_2", ActStage::Act1,
        "На столе — кружка с отбитым краем. Из неё поднимается пар, хотя чай "
        "давно холодный.\n"
        "На дне — что-то блестит.\n\nУ плиты стоит Тень-отголосок: фигура "
        "матери, повторяющая\n"
        "твои движения.");
    node->addChoice(Choice("Осмотреть пространство за холодильником", "1_2")
                        .require(Requirement::lacksNote(1))
                        .withEffect(Effect().addNote(1).message(
                            "За холодильником, среди пыли, лежит клочок "
                            "бумаги. Почерк чужой, "
                            "но дрожь в буквах знакомая.")));
    node->addChoice(Choice("Взять кружку и вспомнить", "1_2a"));
    node->addChoice(Choice("Заземлиться", "1_2b"));
    node->addChoice(Choice("Атаковать Тень: Вспышка памяти", "1_2c")
                        .require(Requirement::minAwareness(FLASH_REQ_AWARE)));
    node->addChoice(Choice("Атаковать Тень: Отрицание", "1_2d"));
    node->addChoice(Choice("Вернуться в коридор", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_2a", ActStage::Act1,
        "Тебе семь. Ты разбил эту кружку, ударившись локтем. Мать не ругала — "
        "собирала\n"
        "осколки, и её руки дрожали не от злости, а от усталости.\n"
        "Ты впервые понял, что взрослые тоже устают.\n\nПолучен Якорь: «Чашка "
        "матери».");
    node->setEntryEffect(Effect()
                             .awareness(CUP_AWARE)
                             .darkness(CUP_DARKNESS)
                             .addAnchor(anchors::CUP)
                             .giveItem(itemsid::MOTHER_CUP));
    node->addChoice(Choice("Вернуться в коридор", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_2b", ActStage::Act1,
        "Ты закрываешь глаза — если это вообще глаза — и вспоминаешь вес "
        "собственного тела.\n"
        "Мир вокруг гаснет. Когда открываешь глаза снова, кухня стала темнее, "
        "контуры\n"
        "расплылись. Зато внутри появилась тяжесть. Настоящая. Живая.\n\n"
        "Статус: «Слепота» на два следующих выбора.");
    node->setEntryEffect(Effect()
                             .will(GROUND_WILL)
                             .awareness(GROUND_AWARE)
                             .addStatus(StatusEffect::Blindness,
                                        cfg::statuscfg::BLINDNESS_CHOICES));
    node->addChoice(Choice("Открыть глаза", "1_2"));
    tree.addNode(std::move(node));
  }
  tree.addNode(
      std::make_shared<CombatNode>("1_2c", ActStage::Act1,
                                   "Из угла отделяется долговязое нечто. Оно "
                                   "тянет тонкие пальцы к твоей Нити.",
                                   std::string(enemyid::SHADOW_ECHO), "1_2a",
                                   Effect{}, "1_4_bad", Effect{}));
  tree.addNode(std::make_shared<ChanceNode>(
      "1_2d", ActStage::Act1, "«Тебя здесь нет. Тебя здесь нет.»",
      cfg::combatcfg::DENIAL_CHANCE, "Тень моргает — и исчезает.", Effect{},
      "1_2a", "Но тень повторяет вместе с тобой. И её голос звучит увереннее.",
      Effect().will(DENIAL_FAIL_WILL), "1_2a"));
  // --- Детская ---
  {
    auto node = std::make_shared<SceneNode>(
        "1_3", ActStage::Act1,
        "Шкаф в твоей старой комнате открыт. Внутри — дневник в кожаной "
        "обложке.\n"
        "Тот самый, который ты прятал от родителей.\n\nГде-то рядом тикает "
        "чужой отсчёт:\n"
        "Паразит-ловчий выбирает момент.");
    node->setVisitPenalty(
        PARASITE_VISITS,
        Effect().maxWill(PARASITE_MAX_WILL).darkness(PARASITE_DARKNESS),
        "Что-то маленькое и многоногое цепляется к Нити. Не рвёт — пьёт. Очень "
        "аккуратно.");
    node->addChoice(Choice("Прочитать дневник", "1_3a"));
    node->addChoice(Choice("Импульс по Нити", "1_3c"));
    node->addChoice(Choice("Уйти", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_3a", ActStage::Act1,
        "«12 марта. Сегодня ночью я снова видел его в углу. Мама говорит, это "
        "просто куртка\n"
        "на стуле. Но куртка не дышит. Я знаю, что куртки не дышат.»\n\n"
        "Ты вспоминаешь: ты всегда его видел. Мимикри не пришёл сегодня.\n"
        "Он жил с тобой всегда.\n\nПолучен Якорь: «Дневник детства».");
    node->setEntryEffect(Effect()
                             .awareness(DIARY_AWARE)
                             .darkness(DIARY_DARKNESS)
                             .addAnchor(anchors::DIARY)
                             .giveItem(itemsid::DIARY)
                             .addNote(2));
    node->addChoice(Choice("Вернуться в коридор", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_3c", ActStage::Act1,
        "Где-то далеко твоё тело вздрагивает. Палец дёргается.\n"
        "Мимикри в углу шипит — он почувствовал.\n\nЭффект: Мимикри замедлен.");
    node->setEntryEffect(Effect()
                             .will(IMPULSE_WILL)
                             .tension(IMPULSE_TENSION)
                             .addFlag(flags::MIMICRY_SLOWED));
    node->addChoice(Choice("Открыть дневник", "1_3a"));
    tree.addNode(std::move(node));
  }
  // --- Ванная ---
  {
    auto node = std::make_shared<SceneNode>(
        "1_4", ActStage::Act1,
        "В зеркале — не ты. Точнее, ты, но... правильнее. Аккуратнее.\n"
        "Он улыбается и медленно прижимает ладонь к стеклу изнутри.\n\n"
        "Шёпот: «Зачем тебе возвращаться? Посмотри на него — он лучше тебя.\n"
        "Он не плакал в 14 лет в этой ванной. Он не...»");
    node->addChoice(Choice("Разбить зеркало", "1_4a"));
    node->addChoice(Choice("Слушать дальше", "1_4b")
                        .whisper()
                        .withEffect(Effect().awareness(LISTEN_AWARE))
                        .onAwarenessZero("1_4_bad"));
    node->addChoice(Choice("Уйти", "1_1"));
    node->addChoice(Choice("Поглотить отражение", "1_4c"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_4a", ActStage::Act1,
        "Ты бьёшь по стеклу. Оно трескается не наружу, а внутрь — будто "
        "зеркало было\n"
        "поверхностью воды, а за ней кто-то тонул твоим лицом.\n\n"
        "Получен Якорь: «Зеркало ванной».");
    node->setEntryEffect(Effect()
                             .will(MIRROR_BREAK_WILL)
                             .darkness(MIRROR_BREAK_DARKNESS)
                             .addAnchor(anchors::MIRROR)
                             .giveItem(itemsid::MIRROR_SHARD)
                             .addFlag(flags::BATHROOM_CLOSED));
    node->addChoice(Choice("Вернуться в коридор", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node =
        std::make_shared<SceneNode>("1_4b", ActStage::Act1,
                                    "Ты слушаешь. Каждое слово — правда. "
                                    "Каждая правда — крюк в мясе твоей души.");
    node->addChoice(Choice("Уйти из ванной", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_4c", ActStage::Act1,
        "Ты прижимаешь ладонь к стеклу. Отражение улыбается шире, думая, что "
        "ты впускаешь его.\n"
        "Но ты тянешь.\n\nОно входит в тебя холодным дымом. На секунду "
        "становится легко.\n"
        "Слишком легко. Как будто кто-то вырезал изнутри лишние сомнения.");
    node->setEntryEffect(Effect()
                             .will(ABSORB_WILL)
                             .awareness(ABSORB_AWARE)
                             .darkness(ABSORB_DARKNESS)
                             .addFlag(flags::ABSORPTION_PATH)
                             .addFlag(flags::BATHROOM_CLOSED));
    node->addChoice(Choice("Вернуться в коридор", "1_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_4_bad", ActStage::Act1,
        "Ты слушаешь слишком долго. Сначала исчезает шум воды в трубах. Потом "
        "— запах\n"
        "сырости. Потом — мысль о том, зачем ты вообще пришёл сюда.\n\n"
        "В зеркале улыбаешься ты. По эту сторону тоже. На один миг ты "
        "перестаёшь понимать,\n"
        "где стекло.\n\nМимикри: «Ничего страшного. Я помогу. Ты ведь всегда "
        "хотел,\n"
        "чтобы кто-то выбирал за тебя.»\n\nСтатус: «Чужая рука».");
    node->setEntryEffect(Effect()
                             .darkness(CAPTURE_DARKNESS)
                             .floorAwareness(CAPTURE_AWARE_FLOOR)
                             .addStatus(StatusEffect::AlienHand));
    node->addChoice(Choice("Прийти в себя", "1_1"));
    tree.addNode(std::move(node));
  }
  // --- Гостиная: Двойник ---
  {
    auto node = std::make_shared<SceneNode>(
        "1_5", ActStage::Act1,
        "В гостиной сидит он. В твоём кресле. Скрюченный, с провалами вместо "
        "глаз — но это\n"
        "безусловно ты. Тень-двойник. Он смеётся твоим смехом, и смех "
        "получается всё точнее.\n\n"
        "Двойник: «Я слышал, ты собираешь свою жизнь по кусочкам. Я её прожил "
        "быстрее.\n"
        "Хочешь, расскажу, чем кончилось?»");
    node->addChoice(Choice("Вспышка памяти", "1_5a")
                        .require(Requirement::minAwareness(FLASH_REQ_AWARE)));
    node->addChoice(Choice("Разрыв проекции", "1_5b"));
    node->addChoice(Choice("Принять «правду» двойника", "1_5c"));
    node->addChoice(
        Choice("Заговорить с ним", "1_5d")
            .require(Requirement::hasAnchor(std::string(anchors::DIARY))));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_5a", ActStage::Act1,
        "Ты поднимаешь Чашку, Дневник, Осколок — всё, что ещё помнит тебя "
        "настоящего.\n"
        "Комната наполняется не светом, а подробностями. Двойник шипит. Его "
        "лицо перестаёт\n"
        "быть лицом и становится набором чужих ожиданий.\n\n"
        "«Не смей смотреть на меня так. Я красивее, когда ты "
        "отворачиваешься.»");
    node->setEntryEffect(
        Effect().awareness(FLASH_AWARE).darkness(FLASH_DARKNESS));
    node->addChoice(Choice("Идти дальше", "1_6"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_5b", ActStage::Act1,
        "Ты хватаешь Нить обеими руками и тянешь. Боль приходит не сюда — "
        "туда. В тело.\n"
        "Двойник рвётся посередине, как плохо склеенная фотография. На секунду "
        "ты видишь\n"
        "за ним пустоту, где кто-то огромный учится дышать твоими лёгкими.");
    node->setEntryEffect(
        Effect().tension(RIP_TENSION).will(RIP_WILL).darkness(RIP_DARKNESS));
    node->addChoice(Choice("Идти дальше", "1_6"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_5c", ActStage::Act1,
        "— Расскажи, — говоришь ты.\n\nОн говорит твоим голосом о том, как "
        "устал быть слабым.\n"
        "Как удобно быть ровным. Как легко жить, если заранее вырезать из себя "
        "всё, что болит.\n\n"
        "Ты слушаешь. И часть тебя кивает.");
    node->setEntryEffect(Effect()
                             .will(TRUTH_WILL)
                             .awareness(TRUTH_AWARE)
                             .darkness(TRUTH_DARKNESS)
                             .addFlag(flags::DOPPEL_TRUTH));
    node->addChoice(Choice("Идти дальше", "1_6"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_5d", ActStage::Act1,
        "— Ты не я. Ты то, что я о себе думал в худшие ночи.\n"
        "— Какая разница? Думал — значит, ты меня создал. Ты мой отец, спящий. "
        "Папа.");
    node->addChoice(Choice("«Ты прав. Прости. Иди ко мне.»", "1_5d_accept"));
    node->addChoice(Choice("«Ты ошибка. Тебя не было.»", "1_5d_deny"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_5d_accept", ActStage::Act1,
        "Двойник впервые перестаёт улыбаться. Он делает шаг, второй — и "
        "растворяется\n"
        "не в свете, а в тебе. Как боль, которую наконец назвали болью.");
    node->setEntryEffect(Effect()
                             .darkness(NAME_DARKNESS)
                             .awareness(NAME_AWARE)
                             .addFlag(flags::SHADOW_NAMED));
    node->addChoice(Choice("Идти дальше", "1_6"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_5d_deny", ActStage::Act1,
        "Двойник раскрывает рот, и из него выходит твой детский плач.\n"
        "Ты говоришь, что его не было. Плач становится громче.");
    node->setEntryEffect(Effect().darkness(DENY_DARKNESS));
    node->addRedirect(Requirement::minAwareness(FLASH_REQ_AWARE), "1_5a");
    node->addChoice(Choice("Отступить", "1_5d_deny_fail"));
    tree.addNode(std::move(node));
  }
  {
    auto node =
        std::make_shared<SceneNode>("1_5d_deny_fail", ActStage::Act1,
                                    "Плач заполняет комнату. Нить дёргается. "
                                    "Ты отступаешь, не оборачиваясь.");
    node->setEntryEffect(
        Effect().tension(DENY_FAIL_TENSION).will(DENY_FAIL_WILL));
    node->addChoice(Choice("Идти дальше", "1_6"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "1_6", ActStage::Act1,
        "Дверь в гостиной, ведущая на балкон, теперь ведёт... наружу.\n"
        "В город, которого нет. Серое небо без солнца. Здания, сложенные из "
        "чужих воспоминаний.");
    node->addChoice(Choice("Шагнуть наружу", "2_1"));
    tree.addNode(std::move(node));
  }
}

//  АКТ 2 ============================================================

void StoryBuilder::buildAct2(StoryTree& tree) const {
  using namespace cfg::act2;

  {
    auto hub = std::make_shared<HubNode>(
        "2_1", ActStage::Act2,
        "Город дышит. Вывески написаны на языках, которые ты не знал, но "
        "почему-то понимаешь.\n"
        "На скамейке сидит девочка лет десяти. Она крутит в руках жестяную "
        "звезду.\n\n"
        "Эхо: «Ты живой? Я давно не видела живых. Тех, у кого нить ещё "
        "серебряная, а не седая.»");
    hub->addChoice(
        Choice("Площадь забытых имён", "2_2")
            .require(Requirement::lacksFlag(std::string(flags::SQUARE_DONE))));
    hub->addChoice(Choice("Библиотека Архивариуса", "2_3"));
    hub->addChoice(
        Choice("Мост над Чёрной рекой", "2_4")
            .require(Requirement::lacksFlag(std::string(flags::BRIDGE_DONE))));
    hub->addChoice(Choice("Карусель", "2_5")
                       .require(Requirement::lacksFlag(
                           std::string(flags::CAROUSEL_DONE))));
    hub->addChoice(Choice("Идти с Эхо", "2_6")
                       .require(Requirement::custom(
                           [](const Player& p) {
                             return visitedLimboCount(p) >= LOCATIONS_FOR_ECHO;
                           },
                           "посещено 2+ локации Лимба")));
    tree.addNode(std::move(hub));
  }
  // --- Площадь ---
  {
    auto node = std::make_shared<SceneNode>(
        "2_2", ActStage::Act2,
        "Памятник без таблички. Вокруг — фигуры людей из чёрной плоти, "
        "повторяющие одно и то же\n"
        "движение: тянутся к табличке и опускают руки.");
    node->setEntryEffect(Effect().addFlag(flags::VISITED_SQUARE));
    node->addRedirect(Requirement::custom(
                          [](const Player& p) {
                            return p.awareness() < SQUARE_AWARENESS_GATE;
                          },
                          "О < 40"),
                      "2_2_fight");
    node->addChoice(
        Choice("Свечение", "2_2a").withEffect(Effect().awareness(LUMI_COST)));
    node->addChoice(Choice("Прикоснуться к фигуре", "2_2b"));
    node->addChoice(Choice("Уйти", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node =
        std::make_shared<SceneNode>("2_2a", ActStage::Act2,
                                    "Нить разгорается, и мгла отступает.\n\nНа "
                                    "табличке твоё имя. И дата — сегодняшняя.\n"
                                    "Если ты не вернёшься, ты станешь ещё "
                                    "одной фигурой, тянущейся в пустоту.");
    node->setEntryEffect(Effect()
                             .awareness(SQUARE_TRUTH_AWARE)
                             .tension(SQUARE_TRUTH_TENSION)
                             .addFlag(flags::SQUARE_DONE));
    node->addChoice(Choice("Вернуться к скамейке", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_2b", ActStage::Act2,
        "Ты касаешься плеча фигуры. Плоть холодная, как мокрая глина. Фигура "
        "замирает.\n"
        "Потом медленно поворачивает к тебе лицо без глаз. И открывает рот.\n\n"
        "Из её рта выходят ещё двое — как слова, которые никто не сказал "
        "вслух.\n"
        "Ты понимаешь: забвение размножается прикосновением.");
    node->setEntryEffect(Effect()
                             .will(TOUCH_FIGURE_WILL)
                             .awareness(TOUCH_FIGURE_AWARE)
                             .darkness(TOUCH_FIGURE_DARKNESS));
    node->addChoice(Choice("Вернуться к скамейке", "2_1"));
    tree.addNode(std::move(node));
  }
  tree.addNode(std::make_shared<CombatNode>(
      "2_2_fight", ActStage::Act2,
      "Мглы слишком много, и одна из фигур замечает тебя. Она перестаёт "
      "тянуться к табличке\n"
      "и тянется к тебе.",
      std::string(enemyid::FORGOTTEN_FIGURE), "2_1",
      Effect().awareness(FIGHT_WIN_AWARE), "2_1",
      Effect()
          .darkness(FIGHT_LOSE_DARKNESS)
          .addStatus(StatusEffect::MimicryControl)
          .message("Темнота на миг гуще тебя. Мимикри получает контроль над "
                   "следующим выбором.")));
  // --- Библиотека ---
  {
    auto node = std::make_shared<SceneNode>(
        "2_3", ActStage::Act2,
        "Архивариус сортирует пепельные страницы.\n"
        "— А, спящий. Хочешь узнать, как он строит из тебя себя?\n\n"
        "Перед ним лежит Книга Подмены.");
    node->setEntryEffect(Effect().addFlag(flags::VISITED_LIBRARY));
    node->addChoice(
        Choice("«Расскажи о Мимикри»", "2_3a")
            .require(Requirement::minAwareness(TWIST_REQ_AWARE))
            .require(Requirement::lacksFlag(std::string(flags::TWIST_READ))));
    node->addChoice(Choice("«Как мне его убить?»", "2_3b")
                        .require(Requirement::minWill(KILL_REQ_WILL))
                        .require(Requirement::lacksFlag(
                            std::string(flags::KNOW_NO_DESTROY))));
    node->addChoice(
        Choice("«Кто ты?»", "2_3c").require(Requirement::lacksNote(3)));
    node->addChoice(
        Choice("Украсть страницу", "2_3d")
            .require(Requirement::lacksFlag(std::string(flags::PAGE_STOLEN))));
    node->addChoice(Choice("Уйти", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_3a", ActStage::Act2,
        "«Он не пришёл извне, спящий. Ты копил его. Каждый раз, когда ты "
        "улыбался вместо\n"
        "того, чтобы плакать. Каждый раз, когда говорил „всё нормально“. Эти "
        "кусочки оседали\n"
        "в тебе, как сажа в трубе. Однажды трубу прочистило сном — и сажа "
        "вышла.\n"
        "С формой. С голодом.»\n\nОткрыта возможность концовки: «Слияние».");
    node->setEntryEffect(
        Effect().awareness(TWIST_AWARE).addFlag(flags::TWIST_READ));
    node->addChoice(Choice("Вернуться в город", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_3b", ActStage::Act2,
        "— Полностью — никак. Можно выжечь, но вместе с ним сгорит память. "
        "Можно запереть,\n"
        "но он будет стучать изнутри. Можно проглотить, но тогда уже не он "
        "станет похож на\n"
        "тебя, а ты на него.\n\n«Если хочешь вернуться собой — не ищи нож. Ищи "
        "имя.»");
    node->setEntryEffect(Effect()
                             .will(KILL_WILL)
                             .awareness(KILL_AWARE)
                             .addFlag(flags::KNOW_NO_DESTROY));
    node->addChoice(Choice("Вернуться в город", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_3c", ActStage::Act2,
        "— Когда-то я тоже спал. Тоже слышал, как моим голосом отвечают "
        "живым.\n"
        "Я собирал знания вместо Якорей. К утру знал всё — кроме дороги "
        "назад.\n\n"
        "Он улыбается сухо, как старая страница.\n"
        "— Теперь я храню чужие дороги. Своя мне больше не нужна.");
    node->setEntryEffect(Effect().awareness(WHO_AWARE).addNote(3));
    node->addChoice(Choice("Вернуться в город", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_3d", ActStage::Act2,
        "Пока Архивариус отворачивается, ты вырываешь из книги страницу. Она "
        "не рвётся —\n"
        "она стонет. У груди страница сворачивается в тонкое пепельное "
        "перо.\n\n"
        "Архивариус, не оборачиваясь: «Украденное знание всегда пишет и на "
        "воре тоже.»");
    node->setEntryEffect(Effect()
                             .darkness(STEAL_DARKNESS)
                             .awareness(STEAL_AWARE)
                             .addFlag(flags::PAGE_STOLEN)
                             .giveItem(itemsid::ARCHIVIST_FEATHER));
    node->addChoice(Choice("Вернуться в город", "2_1"));
    tree.addNode(std::move(node));
  }
  // --- Мост ---
  {
    const Effect zeroEffect =
        Effect()
            .darkness(BRIDGE_ZERO_DARKNESS)
            .addStatus(StatusEffect::MimicryControl)
            .message("Шёпот становится твоим внутренним голосом.");
    auto node = std::make_shared<SceneNode>(
        "2_4", ActStage::Act2,
        "Под мостом течёт что-то, похожее на нефть. В нефти плавают лица. Они "
        "смотрят на\n"
        "тебя без злобы — с интересом.\n\nМимикри-Эхо шепчет. Выбери свою "
        "настоящую мысль:");
    node->setEntryEffect(Effect().addFlag(flags::VISITED_BRIDGE));
    node->addChoice(Choice("«Я не достоин возвращаться»", "2_4_wrong")
                        .whisper()
                        .withEffect(Effect()
                                        .awareness(BRIDGE_WRONG_AWARE)
                                        .addFlag(flags::BRIDGE_DONE))
                        .onAwarenessZero("2_1", zeroEffect));
    node->addChoice(Choice("«Я хочу домой»", "2_4_right")
                        .withEffect(Effect()
                                        .awareness(BRIDGE_RIGHT_AWARE)
                                        .addNote(4)
                                        .addFlag(flags::BRIDGE_DONE)));
    node->addChoice(Choice("«Они там без меня лучше»", "2_4_wrong")
                        .whisper()
                        .withEffect(Effect()
                                        .awareness(BRIDGE_WRONG_AWARE)
                                        .addFlag(flags::BRIDGE_DONE))
                        .onAwarenessZero("2_1", zeroEffect));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_4_right", ActStage::Act2,
        "Фраза выходит тихо. Почти стыдно. Но Чёрная река слышит.\n"
        "Лица в воде закрывают глаза, будто им стало легче.");
    node->addChoice(Choice("Вернуться к скамейке", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node =
        std::make_shared<SceneNode>("2_4_wrong", ActStage::Act2,
                                    "Шёпот радуется. Он не становится громче — "
                                    "он становится твоим внутренним голосом.");
    node->addChoice(Choice("Уйти с моста", "2_1"));
    tree.addNode(std::move(node));
  }
  // --- Карусель ---
  {
    auto node =
        std::make_shared<SceneNode>("2_5", ActStage::Act2,
                                    "Карусель крутится без музыки. На лошадках "
                                    "— дети.\n\nОни не двигаются.");
    node->setEntryEffect(Effect().addFlag(flags::VISITED_CAROUSEL));
    node->addChoice(
        Choice("Раскрутить карусель в обратную сторону", "2_5a")
            .require(Requirement::minAwareness(CAROUSEL_REQ_AWARE)));
    node->addChoice(Choice("Поглотить эхо детей", "2_5b"));
    node->addChoice(Choice("Уйти", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_5a", ActStage::Act2,
        "Ты толкаешь карусель против её мёртвого хода. Сначала она "
        "сопротивляется. Потом\n"
        "скрипит. Потом из её механизма вырывается первый детский вдох.\n\n"
        "Дети начинают исчезать — не как пепел, а как сон, который наконец "
        "досмотрели.\n"
        "Один ребёнок шепчет: «Мы были не едой. Спасибо, что понял.»");
    node->setEntryEffect(Effect()
                             .awareness(FREE_AWARE)
                             .darkness(FREE_DARKNESS)
                             .addNote(5)
                             .addFlag(flags::CHILDREN_FREED)
                             .addFlag(flags::CAROUSEL_DONE));
    node->addChoice(Choice("Вернуться к скамейке", "2_1"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_5b", ActStage::Act2,
        "Ты открываешь рот — и понимаешь, что рот здесь не нужен. Голод "
        "открывается глубже.\n"
        "Их жестяные голоса, их непрожитые утренники, их забытые имена — всё "
        "входит в тебя\n"
        "тёплым потоком.\n\nКарусель останавливается. На одной из пустых "
        "лошадок теперь сидит\n"
        "твоя тень. Маленькая. Сытая.");
    node->setEntryEffect(Effect()
                             .will(EAT_KIDS_WILL)
                             .awareness(EAT_KIDS_AWARE)
                             .darkness(EAT_KIDS_DARKNESS)
                             .removeNote(5)
                             .addFlag(flags::CHILDREN_CONSUMED)
                             .addFlag(flags::CAROUSEL_DONE));
    node->addChoice(Choice("Вернуться к скамейке", "2_1"));
    tree.addNode(std::move(node));
  }
  // --- Эхо: решающий выбор ---
  {
    auto node = std::make_shared<SceneNode>(
        "2_6", ActStage::Act2,
        "Эхо устала. Её жестяная звезда тускнеет.\n\n"
        "— Я не дойду до Ворот сама. Помоги мне. Или... возьми, что у меня "
        "есть.\n"
        "Всё равно я уже почти не я.");
    node->addChoice(Choice("Отдать ей частицу Осознанности", "2_6a"));
    node->addChoice(Choice("Поглотить её энергию", "2_6b"));
    node->addChoice(Choice("Уйти, не выбирая", "2_6c"));
    node->addChoice(
        Choice("Сказать ей правду о её смерти", "2_6_truth").parasitic());
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_6a", ActStage::Act2,
        "Ты протягиваешь Эхо не руку — мысль. Самую ясную из тех, что "
        "остались:\n"
        "«Я хочу домой».\n\nЖестяная звезда вспыхивает. Девочка вздрагивает, "
        "будто впервые\n"
        "за долгое время вспомнила, как быть настоящей.\n\n"
        "Эхо: «Ты отдал мне кусочек дороги. Я верну, когда станет темно.»");
    node->setEntryEffect(
        Effect()
            .awareness(ECHO_GIVE_AWARE)
            .darkness(ECHO_GIVE_DARKNESS)
            .addFlag(flags::ECHO_SAVED)
            .giveItem(itemsid::TIN_STAR)
            .when(Requirement::custom(
                      [](const Player& p) { return p.awareness() <= 0; },
                      "О <= 0"),
                  Effect()
                      .addStatus(StatusEffect::Exhaustion)
                      .message("Истощение: в финальной битве первая ошибка "
                               "будет стоить дороже.")));
    node->addChoice(Choice("Идти дальше", "2_7"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_6b", ActStage::Act2,
        "— Прости, — говоришь ты. И это почти правда.\n\nЕё свет втягивается в "
        "тебя тонкой,\n"
        "дрожащей струной. Она становится прозрачной. Ещё прозрачнее. Потом "
        "остаётся только\n"
        "жестяная звезда, пустая и холодная.\n\nНить у твоей груди темнеет на "
        "один оборот.");
    node->setEntryEffect(Effect()
                             .will(ECHO_EAT_WILL)
                             .awareness(ECHO_EAT_AWARE)
                             .darkness(ECHO_EAT_DARKNESS)
                             .addFlag(flags::ECHO_CONSUMED));
    node->addChoice(Choice("Идти дальше", "2_7"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_6c", ActStage::Act2,
        "Ты делаешь шаг назад. Эхо всё понимает не сразу.\n\n"
        "— Ничего, — говорит она. — Я привыкла, что взрослые уходят, когда "
        "страшно.\n\n"
        "Когда ты оборачиваешься снова, на скамейке лежит только ржавый след в "
        "форме звезды.");
    node->setEntryEffect(Effect()
                             .awareness(ECHO_LEAVE_AWARE)
                             .darkness(ECHO_LEAVE_DARKNESS)
                             .addFlag(flags::ECHO_LEFT));
    node->addChoice(Choice("Идти дальше", "2_7"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_6_truth", ActStage::Act2,
        "Слова выходят раньше, чем ты успеваешь их остановить. Эхо смотрит на "
        "тебя.\n"
        "Долго. Потом смотрит на свои руки — и сквозь них видно скамейку.\n\n"
        "Она не кричит. Она просто рассыпается, как имя, которое никто больше "
        "не произнесёт.");
    node->setEntryEffect(Effect()
                             .darkness(ECHO_TRUTH_DARKNESS)
                             .awareness(ECHO_TRUTH_AWARE)
                             .addFlag(flags::ECHO_DESTROYED));
    node->addChoice(Choice("Идти дальше", "2_7"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "2_7", ActStage::Act2,
        "Где-то далеко — ты слышишь голос матери. Она зовёт твоё имя. Тебя — "
        "спящего.\n\n"
        "Мимикри отзывается. Голосом, похожим на твой.\n\n"
        "Только мама кивает и улыбается. Она верит ему.");
    node->setEntryEffect(Effect().will(VOICE_WILL).tension(VOICE_TENSION));
    node->addChoice(Choice("Идти к Вратам", "3_1"));
    tree.addNode(std::move(node));
  }
}

//  АКТ 3 ============================================================

void StoryBuilder::buildAct3(StoryTree& tree) const {
  using namespace cfg::act3;

  {
    auto node = std::make_shared<SceneNode>(
        "3_1", ActStage::Act3,
        "Мир за мостом перестал притворяться местом.\n\n"
        "Это лабиринт из зеркал, отражающих тебя в разные моменты жизни. В "
        "каждом отражении —\n"
        "момент, когда ты молчал, хотя хотел кричать.");
    node->addChoice(Choice("Войти в лабиринт", "3_1a"));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "3_1a", ActStage::Act3,
        "ЗЕРКАЛО СТЫДА.\n\nТы в школе. Тебя унизили. Ты промолчал.");
    node->addChoice(
        Choice("Принять воспоминание", "3_1b")
            .withEffect(
                Effect()
                    .darkness(SHAME_ACCEPT_DARKNESS)
                    .awareness(SHAME_ACCEPT_AWARE)
                    .message("Ты смотришь на ребёнка в отражении и впервые не "
                             "требуешь от него быть сильным. Он был один. "
                             "Он выжил как смог.")));
    node->addChoice(
        Choice("Отвернуться", "3_1b")
            .withEffect(
                Effect()
                    .will(SHAME_TURN_WILL)
                    .darkness(SHAME_TURN_DARKNESS)
                    .message("Отражение остаётся за спиной, но его стыд идёт "
                             "следом.")));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "3_1b", ActStage::Act3,
        "ЗЕРКАЛО ВИНЫ.\n\nТы не пришёл к умирающему другу.");
    node->addChoice(
        Choice("Признать вину", "3_1c")
            .withEffect(Effect()
                            .darkness(GUILT_ADMIT_DARKNESS)
                            .awareness(GUILT_ADMIT_AWARE)
                            .message("Ты говоришь: «Я виноват». И зеркало не "
                                     "разбивается. Оно становится дверью.")));
    node->addChoice(
        Choice("Оправдаться", "3_1c")
            .withEffect(
                Effect()
                    .darkness(GUILT_EXCUSE_DARKNESS)
                    .message("Ты объясняешь, почему не мог. Отражение слушает. "
                             "И стареет на глазах.")));
    tree.addNode(std::move(node));
  }
  {
    auto node =
        std::make_shared<SceneNode>("3_1c", ActStage::Act3,
                                    "ЗЕРКАЛО ЛЮБВИ.\n\nКто-то говорил тебе: «Я "
                                    "тебя люблю», а ты не ответил.");
    node->addChoice(
        Choice("Ответить сейчас", "3_2")
            .withEffect(
                Effect()
                    .will(LOVE_ANSWER_WILL)
                    .darkness(LOVE_ANSWER_DARKNESS)
                    .addNote(6)
                    .message("Ты говоришь это в пустоту. Неловко. Поздно. "
                             "Но слова всё равно доходят. Где-то далеко кто-то "
                             "во сне перестаёт плакать.")
                    .when(Requirement::hasItem(std::string(itemsid::TIN_STAR)),
                          Effect()
                              .awareness(LOVE_STAR_AWARE)
                              .message("Звезда в кармане теплеет. За плечом на "
                                       "миг появляется Эхо: «Скажи. Даже если "
                                       "поздно. Особенно если поздно.»"))));
    node->addChoice(
        Choice("Снова промолчать", "3_2")
            .withEffect(
                Effect()
                    .will(LOVE_SILENT_WILL)
                    .darkness(LOVE_SILENT_DARKNESS)
                    .message("Ты молчишь. Зеркало тоже. И в этом молчании "
                             "кто-то навсегда остаётся ждать ответа.")));
    tree.addNode(std::move(node));
  }
  {
    auto node = std::make_shared<SceneNode>(
        "3_2", ActStage::Act3,
        "В центре лабиринта — огромное зеркало в раме из костей серебра.\n"
        "По ту сторону — твоя комната. У кровати стоят люди. Мама. Друг. "
        "Сестра.\n"
        "Все смотрят на твоё тело — и улыбаются. Тело улыбается им в ответ.\n"
        "Слишком ровно. Слишком правильно.\n\nМимикри выходит из зеркала.\n\n"
        "«Ты опоздал, спящий. Они уже выбрали меня. Я не злой. Я просто — без "
        "зазубрин.\n"
        "Зачем ты хочешь вернуться в это грязное, слабое тело?»");
    node->addChoice(Choice("Шагнуть навстречу", "3_3"));
    tree.addNode(std::move(node));
  }
  tree.addNode(std::make_shared<FinalBattleNode>(
      "3_3", ActStage::Act3,
      "БИТВА ПРАВДЫ ПРОТИВ ЛЖИ.\n\nМимикри произнесёт пять утверждений.\n"
      "Назови каждое правдой или ложью. Ошибка ест Осознанность."));
}

// КОНЦОВКИ ============================================================

void StoryBuilder::buildEndings(StoryTree& tree) const {
  tree.addNode(std::make_shared<EndingNode>(
      "ending_a", "КОНЦОВКА А: ЗАМЕЩЕНИЕ — «Тихий компромисс»",
      "Ты протягиваешь руку. Мимикри делает шаг вперёд — и растворяется в "
      "тебе,\n"
      "как сахар в чае.\n\nТы делаешь вдох. Открываешь глаза. Потолок. "
      "Трещина-молния.\n"
      "Мама плачет рядом: «Ты так долго не просыпался...»\n\n"
      "Ты улыбаешься. Ровно. Правильно.\n\n"
      "Ты не помнишь, чего боялся в детстве. Не помнишь, как пахла бабушкина "
      "чашка.\n"
      "Зато ты больше не плачешь по ночам.\n\nЭто ведь хорошо, правда?",
      "Герой живёт. Холодно, но стабильно. В зеркалах иногда мелькает кто-то "
      "ещё.",
      EndingType::Replacement));

  tree.addNode(std::make_shared<EndingNode>(
      "ending_b", "КОНЦОВКА Б: ОТРИЦАНИЕ — «Чистый лист»",
      "Ты сжигаешь всё, что помнишь. Дневник. Чашку. Лицо матери. Лицо Эхо. "
      "Своё имя.\n"
      "Огонь Осознанности обращается на Мимикри — и на тебя. Вы сгораете "
      "вместе.\n\n"
      "Ты просыпаешься. Белый потолок. Белые стены. Кто-то сидит рядом и "
      "держит тебя\n"
      "за руку.\n\nТы не знаешь, кто это. Ты не знаешь, кто ты.\n\nНо Мимикри "
      "тоже не знает.",
      "Героя выписывают как пациента с амнезией. Он начинает жизнь заново.\n"
      "Серебряная нить теперь белая, как бумага.",
      EndingType::Denial));

  tree.addNode(std::make_shared<EndingNode>(
      "ending_v", "КОНЦОВКА В: СЛИЯНИЕ — «Осознанный сновидец»",
      "— Ты не враг. Ты — то, что я не позволял себе чувствовать. Иди сюда.\n"
      "Не как хозяин. Как часть.\n\nМимикри впервые плачет — твоими слезами.\n"
      "Ты обнимаешь его, как обнимают младшего брата, которого долго не "
      "пускали к столу.\n"
      "Вы становитесь одним — но ты остаёшься главным.\n\n"
      "Ты открываешь глаза. Видишь маму: «С возвращением, родной.»\n"
      "Ты улыбаешься. Криво, как всегда.\n\n"
      "Ночью ты снова закрываешь глаза — и в Астрале тебя ждёт Эхо.\n"
      "Она машет жестяной звездой: «Пойдём гулять, спящий?»",
      "Герой становится проводником между мирами. Он помогает другим заблудшим "
      "душам\n"
      "найти путь домой.",
      EndingType::TrueMerge));

  tree.addNode(std::make_shared<EndingNode>(
      "ending_v2", "КОНЦОВКА В2: НЕПОЛНОЕ СЛИЯНИЕ — «Шрам, который говорит»",
      "Ты протягиваешь руку. Мимикри долго смотрит на неё.\n\n"
      "— Я не знаю, как быть частью, — говорит он твоим голосом.\n"
      "— Я тоже, — отвечаешь ты. — Научимся.\n\n"
      "Он входит в тебя не мягко. Больно. Как возвращается кровь в затёкшую "
      "руку.\n"
      "Ты просыпаешься с криком. Мама плачет. Ты тоже. И впервые за долгое "
      "время\n"
      "не извиняешься за это.\n\nИногда ночью ты слышишь шёпот. Но теперь ты "
      "отвечаешь ему.\n"
      "Не как врагу. Как себе, которому ещё страшно.",
      "Герой возвращается к жизни, но путь исцеления только начинается.",
      EndingType::IncompleteMerge));

  tree.addNode(std::make_shared<EndingNode>(
      "ending_g", "КОНЦОВКА Г: ПОГЛОЩЕНИЕ — скрытая тёмная",
      "Зачем сражаться, если можно съесть?\n\nТы раскрываешь рот — и Мимикри "
      "понимает\n"
      "за секунду до. Слишком поздно.\n\nТы возвращаешься в тело. Сильнее, чем "
      "был.\n"
      "Голоднее, чем был.\n\nМама обнимает тебя. Ты слышишь, как стучит её "
      "сердце.\n"
      "Такое хрупкое. Такое... питательное.\n\nСеребряная нить почернела "
      "навсегда.\n"
      "Но теперь у тебя много новых нитей. Тонких. Ведущих к каждому, кто "
      "рядом.",
      "Герой стал новым Мимикри. Цикл повторится.", EndingType::Absorption));

  tree.addNode(std::make_shared<EndingNode>(
      "ending_d", "КОНЦОВКА Д: РАЗРЫВ НИТИ",
      "Нить лопается с тонким звоном.\n\nТы слышишь, как далеко-далеко — в "
      "комнате\n"
      "с трещиной-молнией на потолке — кто-то делает первый вдох новой "
      "жизнью.\n\n"
      "Это не ты.\n\nТебя больше нет.",
      "Game Over. Совет: освящённый Осколок зеркала создаёт точку якорения,\n"
      "к которой Нить вернёт тебя после разрыва.",
      EndingType::ThreadBreak));
}

}  // namespace st
