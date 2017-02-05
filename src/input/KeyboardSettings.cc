#include "KeyboardSettings.hh"
#include "memory.hh"

namespace openmsx {

static EnumSetting<Keys::KeyCode>::Map getAllowedKeysMap()
{
	return {
		{"RALT",        Keys::K_RALT},
		{"MENU",        Keys::K_MENU},
		{"RCTRL",       Keys::K_RCTRL},
		{"HENKAN_MODE", Keys::K_HENKAN_MODE},
		{"RSHIFT",      Keys::K_RSHIFT},
		{"RMETA",       Keys::K_RMETA},
		{"LMETA",       Keys::K_LMETA},
		{"LSUPER",      Keys::K_LSUPER},
		{"RSUPER",      Keys::K_RSUPER},
		{"HELP",        Keys::K_HELP},
		{"UNDO",        Keys::K_UNDO},
		{"END",         Keys::K_END},
		{"PAGEUP",      Keys::K_PAGEUP},
		{"PAGEDOWN",    Keys::K_PAGEDOWN}
	};
}

KeyboardSettings::KeyboardSettings(CommandController& commandController)
	: codeKanaHostKey(commandController,
		"kbd_code_kana_host_key",
		"Host key that maps to the MSX CODE/KANA key. Please note that the HENKAN_MODE key only exists on Japanese host keyboards)",
		Keys::K_RALT, getAllowedKeysMap())
	, kpEnterMode(commandController,
		"kbd_numkeypad_enter_key",
		"MSX key that the enter key on the host numeric keypad must map to",
		MSX_KP_COMMA, EnumSetting<KpEnterMode>::Map{
			{"KEYPAD_COMMA", MSX_KP_COMMA},
			{"ENTER",        MSX_ENTER}})
	, mappingMode(commandController,
		"kbd_mapping_mode",
		"Keyboard mapping mode",
		CHARACTER_MAPPING, EnumSetting<MappingMode>::Map{
			{"KEY",       KEY_MAPPING},
			{"CHARACTER", CHARACTER_MAPPING}})
	, alwaysEnableKeypad(commandController,
		"kbd_numkeypad_always_enabled",
		"Numeric keypad is always enabled, even on an MSX that does not have one",
		false)
	, traceKeyPresses(commandController,
		"kbd_trace_key_presses",
		"Trace key presses (show SDL key code, SDL modifiers and Unicode code-point value)",
		false, Setting::DONT_SAVE)
	, autoToggleCodeKanaLock(commandController,
		"kbd_auto_toggle_code_kana_lock",
		"Automatically toggle the CODE/KANA lock, based on the characters entered on the host keyboard",
		true)
{
	deadkeyHostKey[0] = make_unique<EnumSetting<Keys::KeyCode>>(
		commandController, "kbd_deadkey1_host_key",
		"Host key that maps to deadkey 1. Not applicable to Japanese and Korean MSX models",
		Keys::K_RCTRL, getAllowedKeysMap());

	deadkeyHostKey[1] = make_unique<EnumSetting<Keys::KeyCode>>(
		commandController, "kbd_deadkey2_host_key",
		"Host key that maps to deadkey 2. Only applicable to Brazilian MSX models (Sharp Hotbit and Gradiente)",
		Keys::K_PAGEUP, getAllowedKeysMap());

	deadkeyHostKey[2] = make_unique<EnumSetting<Keys::KeyCode>>(
		commandController, "kbd_deadkey3_host_key",
		"Host key that maps to deadkey 3. Only applicable to Brazilian Sharp Hotbit MSX models",
		Keys::K_PAGEDOWN, getAllowedKeysMap());
}

} // namespace openmsx
