#pragma once

namespace st::cfg {

	//  Ресурсы 
	namespace res {
		inline constexpr int START_WILL = 100;
		inline constexpr int START_MAX_WILL = 100;
		inline constexpr int START_AWARENESS = 50;
		inline constexpr int MAX_AWARENESS = 100;
		inline constexpr int START_TENSION = 0;
		inline constexpr int START_DARKNESS = 0;
		inline constexpr int RESOURCE_CAP = 100;
		inline constexpr int MIN_MAX_WILL = 1;
	}

	//  Состояния Нити 
	namespace thread {
		inline constexpr int TENSION_WARNING = 80;   // Натянутая Нить
		inline constexpr int TENSION_BREAK = 100;  // Разрыв
		inline constexpr int DARKNESS_BLACKENING = 30;   // Почерневшая Нить
		inline constexpr int DARKNESS_BLACK = 70;   // Чёрная Нить
	}

	//  Инвентарь 
	namespace inv {
		inline constexpr int SLOTS = 4;
		inline constexpr int FORGET_DARKNESS = 5;  // ЧН за забывание предмета
	}

	//  Статусы 
	namespace statuscfg {
		inline constexpr int BLINDNESS_CHOICES = 2;   // «Слепота» на 2 выбора
		inline constexpr int PERMANENT = -1;  // бессрочный статус
	}

	//  Бой 
	namespace combatcfg {
		inline constexpr int SHADOW_HP = 10;
		inline constexpr int FIGURE_HP = 10;
		inline constexpr int ENEMY_AWARENESS_HIT = -5;
		inline constexpr int HAND_AWARENESS = -5;
		inline constexpr int HAND_DAMAGE = 0;
		inline constexpr int THREAD_TENSION = 10;
		inline constexpr int THREAD_DAMAGE = 5;
		inline constexpr int SCREAM_WILL = -5;
		inline constexpr int SCREAM_DAMAGE = 3;
		inline constexpr int MEMORY_FLASH_REQ = 15;
		inline constexpr int MEMORY_FLASH_COST = -15;
		inline constexpr int MEMORY_FLASH_DAMAGE = 10;
		inline constexpr int DENIAL_CHANCE = 50;
		inline constexpr int DENIAL_FAIL_WILL = -20;
	}

	//  Пролог 
	namespace prologue {
		inline constexpr int TOUCH_WILL = -15;
		inline constexpr int TOUCH_TENSION = 20;
		inline constexpr int STUDY_AWARE = 5;
		inline constexpr int LOOK_AWARE = 10;
		inline constexpr int LOOK_WILL = -5;
		inline constexpr int WHO_AWARE = 5;
		inline constexpr int HOW_AWARE = 2;
		inline constexpr int SILENT_WILL = 5;
	}

	//  Акт 1 
	namespace act1 {
		inline constexpr int ANCHORS_FOR_EXIT = 2;

		inline constexpr int CUP_AWARE = 10;
		inline constexpr int CUP_DARKNESS = -5;

		inline constexpr int GROUND_WILL = 20;
		inline constexpr int GROUND_AWARE = -5;

		inline constexpr int DENIAL_FAIL_WILL = -20;

		inline constexpr int DIARY_AWARE = 15;
		inline constexpr int DIARY_DARKNESS = -10;
		inline constexpr int IMPULSE_WILL = -15;
		inline constexpr int IMPULSE_TENSION = 10;
		inline constexpr int PARASITE_VISITS = 3;
		inline constexpr int PARASITE_MAX_WILL = -10;
		inline constexpr int PARASITE_DARKNESS = 5;

		inline constexpr int MIRROR_BREAK_WILL = -10;
		inline constexpr int MIRROR_BREAK_DARKNESS = -5;
		inline constexpr int LISTEN_AWARE = -20;
		inline constexpr int ABSORB_WILL = 30;
		inline constexpr int ABSORB_AWARE = 10;
		inline constexpr int ABSORB_DARKNESS = 25;

		inline constexpr int CAPTURE_DARKNESS = 20;
		inline constexpr int CAPTURE_AWARE_FLOOR = 10;

		inline constexpr int FLASH_REQ_AWARE = 15;
		inline constexpr int FLASH_AWARE = -15;
		inline constexpr int FLASH_DARKNESS = -10;
		inline constexpr int RIP_TENSION = 25;
		inline constexpr int RIP_WILL = -10;
		inline constexpr int RIP_DARKNESS = 10;
		inline constexpr int TRUTH_WILL = 20;
		inline constexpr int TRUTH_AWARE = -10;
		inline constexpr int TRUTH_DARKNESS = 25;
		inline constexpr int NAME_DARKNESS = -15;
		inline constexpr int NAME_AWARE = 20;
		inline constexpr int DENY_DARKNESS = 15;
		inline constexpr int DENY_FAIL_TENSION = 20;
		inline constexpr int DENY_FAIL_WILL = -10;
	}

	//  Акт 2 
	namespace act2 {
		inline constexpr int LOCATIONS_FOR_ECHO = 2;
		inline constexpr int SQUARE_AWARENESS_GATE = 40;

		inline constexpr int LUMI_COST = -10;
		inline constexpr int SQUARE_TRUTH_AWARE = 10;
		inline constexpr int SQUARE_TRUTH_TENSION = 5;
		inline constexpr int TOUCH_FIGURE_WILL = -5;
		inline constexpr int TOUCH_FIGURE_AWARE = -10;
		inline constexpr int TOUCH_FIGURE_DARKNESS = 5;
		inline constexpr int FIGHT_WIN_AWARE = 5;
		inline constexpr int FIGHT_LOSE_DARKNESS = 15;

		inline constexpr int TWIST_REQ_AWARE = 15;
		inline constexpr int TWIST_AWARE = 20;
		inline constexpr int KILL_REQ_WILL = 10;
		inline constexpr int KILL_WILL = -10;
		inline constexpr int KILL_AWARE = 10;
		inline constexpr int WHO_AWARE = 5;
		inline constexpr int STEAL_DARKNESS = 10;
		inline constexpr int STEAL_AWARE = 10;

		inline constexpr int BRIDGE_RIGHT_AWARE = 15;
		inline constexpr int BRIDGE_WRONG_AWARE = -30;
		inline constexpr int BRIDGE_ZERO_DARKNESS = 15;

		inline constexpr int CAROUSEL_REQ_AWARE = 20;
		inline constexpr int FREE_AWARE = -20;
		inline constexpr int FREE_DARKNESS = -20;
		inline constexpr int EAT_KIDS_WILL = 50;
		inline constexpr int EAT_KIDS_AWARE = 30;
		inline constexpr int EAT_KIDS_DARKNESS = 40;

		inline constexpr int ECHO_GIVE_AWARE = -25;
		inline constexpr int ECHO_GIVE_DARKNESS = -20;
		inline constexpr int ECHO_EAT_WILL = 40;
		inline constexpr int ECHO_EAT_AWARE = 30;
		inline constexpr int ECHO_EAT_DARKNESS = 35;
		inline constexpr int ECHO_LEAVE_AWARE = -10;
		inline constexpr int ECHO_LEAVE_DARKNESS = 10;
		inline constexpr int ECHO_TRUTH_DARKNESS = 20;  // паразитический выбор
		inline constexpr int ECHO_TRUTH_AWARE = -20;

		inline constexpr int VOICE_WILL = -15;
		inline constexpr int VOICE_TENSION = 15;
	}

	//  Акт 3 
	namespace act3 {
		inline constexpr int SHAME_ACCEPT_DARKNESS = -10;
		inline constexpr int SHAME_ACCEPT_AWARE = 5;
		inline constexpr int SHAME_TURN_WILL = -10;
		inline constexpr int SHAME_TURN_DARKNESS = 5;

		inline constexpr int GUILT_ADMIT_DARKNESS = -15;
		inline constexpr int GUILT_ADMIT_AWARE = 10;
		inline constexpr int GUILT_EXCUSE_DARKNESS = 10;

		inline constexpr int LOVE_ANSWER_WILL = 20;
		inline constexpr int LOVE_ANSWER_DARKNESS = -20;
		inline constexpr int LOVE_STAR_AWARE = 5;
		inline constexpr int LOVE_SILENT_WILL = -15;
		inline constexpr int LOVE_SILENT_DARKNESS = 15;
	}

	// Финальная битва и концовки 
	namespace finalcfg {
		inline constexpr int STATEMENT_COUNT = 5;
		inline constexpr int CORRECT_DARKNESS = -5;
		inline constexpr int WRONG_AWARENESS = -15;
		inline constexpr int WRONG_AWARENESS_EXHAUST = -25;
		inline constexpr int ZERO_AWARENESS_DARKNESS = 20;
		inline constexpr int HALF_TRUTH_DARKNESS = -10;
		inline constexpr int HALF_TRUTH_AWARE = 5;
		inline constexpr int BLACK_AUTOFAIL_DARKNESS = 70;

		inline constexpr int TRUE_MERGE_ANCHORS = 3;
		inline constexpr int TRUE_MERGE_NOTES = 6;
		inline constexpr int TRUE_MERGE_MAX_DARKNESS = 15;
		inline constexpr int TRUE_MERGE_MIN_CORRECT = 4;

		inline constexpr int MERGE_MAX_DARKNESS = 30;
		inline constexpr int MERGE_MIN_CORRECT = 3;

		inline constexpr int DENIAL_MIN_AWARENESS = 70;
		inline constexpr int DENIAL_MAX_DARKNESS = 20;
		inline constexpr int DENIAL_TENSION = 30;

		inline constexpr int ABSORB_MIN_DARKNESS = 70;
		inline constexpr int ABSORB_FAIL_TENSION = 50;
		inline constexpr int ABSORB_FAIL_WILL = -50;
	}

	// Предметы 
	namespace itemcfg {
		inline constexpr int DIARY_USE_AWARE = 5;
		inline constexpr int SHARD_CONSECRATE_AWARE = -10;
		inline constexpr int SHARD_CONSECRATE_WILL = -5;
		inline constexpr int CUP_WHISPER_DIVISOR = 2;  // Чашка ослабляет шёпот вдвое
	}

} // namespace st::cfg