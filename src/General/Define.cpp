#include"../header/Define.h"

const unordered_map<string, ScriptTag> Define::tagToID = {
	{ "msw",ScriptTag::MESSAGE_CLICK_WAIT },
	{ "msp",ScriptTag::MESSAGE_RENEW_PAGE },
	{ "mws",ScriptTag::MESSAGE_WINDOW_SET },
	{ "mwd",ScriptTag::MESSAGE_WINDOW_DELETE },
	{ "nms",ScriptTag::NAME_SET },
	{ "nmd",ScriptTag::NAME_DELETE },
	{ "bgs",ScriptTag::BACK_GROND_SET },
	{ "bgd",ScriptTag::BACK_GROND_DELETE },
	{ "cgs",ScriptTag::CG_SET },
	{ "cgd",ScriptTag::CG_DELETE },
	{ "ses",ScriptTag::SCREEN_EFFECT_SET },
	{ "sed",ScriptTag::SCREEN_EFFECT_DELETE },
	{ "ims",ScriptTag::ITEM_SET },
	{ "imd",ScriptTag::ITEM_DELETE },
	{ "chs",ScriptTag::CHARA_SET },
	{ "chd",ScriptTag::CHARA_DELETE },
	{ "cha",ScriptTag::CHARA_ANIMATION },
	{ "sel",ScriptTag::SELECT },
	{ "selch",ScriptTag::CHOISE },
	{ "if",ScriptTag::IF },
	{ "elf",ScriptTag::ELSEIF },
	{ "els",ScriptTag::ELSE },
	{ "edf",ScriptTag::ENDIF },
	{ "jmp",ScriptTag::JUMP },
	{ "jmpt",ScriptTag::JUMP_TAG },
	{ "bgm",ScriptTag::BGM },
	{ "bgms",ScriptTag::BGM_STOP },
	{ "se",ScriptTag::SE },
	{ "vo",ScriptTag::VOICE },
	{ "stf",ScriptTag::STAND_FLAG },
	{ "cnf",ScriptTag::CANCEL_FLAG },
	{ "wtm",ScriptTag::WAIT_TIMER },
	{ "clk",ScriptTag::CLICK },
	{ "css",ScriptTag::CONSOLE_SET },
	{ "csd",ScriptTag::CONSOLE_DELETE },
	{ "prt",ScriptTag::PRINTF },
	{ "fdin",ScriptTag::FADE_IN },
	{ "fdout",ScriptTag::FADE_OUT },
	{ "trs",ScriptTag::TRANSIT_SCENE }
};