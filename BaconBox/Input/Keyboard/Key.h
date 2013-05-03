/**
 * @file
 * @ingroup Input
 */
#ifndef BB_KEY_H
#define BB_KEY_H
namespace BaconBox {
	/**
	 * Key codes for keyboard input.
	 */
	struct Key {
		typedef int Enum;
		
		/**
		 * Get the char from a key.
		 * @param key Key to get the char of. Must be an alphabet letter (A-Z
		 * key codes).
		 * @return Char equivalent to the key. If the key received is not a
		 * letter from A to Z, it returns the null character '\0'.
		 */
		static char toChar(Enum key);
		
		static const Enum INVALID;
		static const Enum A;
		static const Enum ADD;
		static const Enum APPS;
		static const Enum ATTN;
		static const Enum B;
		static const Enum BACKSPACE;
		static const Enum BROWSER_BACK;
		static const Enum BROWSER_FAVORITES;
		static const Enum BROWSER_FORWARD;
		static const Enum BROWSER_HOME;
		static const Enum BROWSER_REFRESH;
		static const Enum BROWSER_SEARCH;
		static const Enum BROWSER_STOP;
		static const Enum C;
		static const Enum CAPS_LOCK;
		static const Enum CHAT_PAD_GREEN;
		static const Enum CHAT_PAD_ORANGE;
		static const Enum CRSEL;
		static const Enum D;
		static const Enum D0;
		static const Enum D1;
		static const Enum D2;
		static const Enum D3;
		static const Enum D4;
		static const Enum D5;
		static const Enum D6;
		static const Enum D7;
		static const Enum D8;
		static const Enum D9;
		static const Enum DECIMAL;
		static const Enum DELETEKEY;
		static const Enum DIVIDE;
		static const Enum DOWN;
		static const Enum E;
		static const Enum END;
		static const Enum ENTER;
		static const Enum ERASE_EOF;
		static const Enum ESCAPE;
		static const Enum EXECUTE;
		static const Enum EXSEL;
		static const Enum F;
		static const Enum F1;
		static const Enum F10;
		static const Enum F11;
		static const Enum F12;
		static const Enum F13;
		static const Enum F14;
		static const Enum F15;
		static const Enum F16;
		static const Enum F17;
		static const Enum F18;
		static const Enum F19;
		static const Enum F2;
		static const Enum F20;
		static const Enum F21;
		static const Enum F22;
		static const Enum F23;
		static const Enum F24;
		static const Enum F3;
		static const Enum F4;
		static const Enum F5;
		static const Enum F6;
		static const Enum F7;
		static const Enum F8;
		static const Enum F9;
		static const Enum G;
		static const Enum H;
		static const Enum HELP;
		static const Enum HOME;
		static const Enum I;
		static const Enum IME_CONVERT;
		static const Enum IME_NO_CONVERT;
		static const Enum INSERT;
		static const Enum J;
		static const Enum K;
		static const Enum KANA;
		static const Enum KANJI;
		static const Enum L;
		static const Enum LAUNCH_APPLICATION_1;
		static const Enum LAUNCH_APPLICATION_2;
		static const Enum LAUNCH_MAIL;
		static const Enum LEFT;
		static const Enum LEFT_ALT;
		static const Enum LEFT_CONTROL;
		static const Enum LEFT_SHIFT;
		static const Enum LEFT_WINDOWS;
		static const Enum M;
		static const Enum MEDIA_NEXT_TRACK;
		static const Enum MEDIA_PLAY_PAUSE;
		static const Enum MEDIA_PREVIOUS_TRACK;
		static const Enum MEDIA_STOP;
		static const Enum MULTIPLY;
		static const Enum N;
		static const Enum NONE;
		static const Enum NUM_LOCK;
		static const Enum NUM_PAD_0;
		static const Enum NUM_PAD_1;
		static const Enum NUM_PAD_2;
		static const Enum NUM_PAD_3;
		static const Enum NUM_PAD_4;
		static const Enum NUM_PAD_5;
		static const Enum NUM_PAD_6;
		static const Enum NUM_PAD_7;
		static const Enum NUM_PAD_8;
		static const Enum NUM_PAD_9;
		static const Enum O;
		static const Enum EXCLAM;
		static const Enum AUTO;
		static const Enum BACKSLASH;
		static const Enum CLEAR;
		static const Enum CLOSE_BRACKETS;
		static const Enum COMMA;
		static const Enum COPY;
		static const Enum ENL_W;
		static const Enum MINUS;
		static const Enum OPEN_BRACKETS;
		static const Enum PERIOD;
		static const Enum PIPE;
		static const Enum PLUS;
		static const Enum QUESTION;
		static const Enum QUOTES;
		static const Enum SEMICOLON;
		static const Enum TILDE;
		static const Enum P;
		static const Enum PA_1;
		static const Enum PAGE_DOWN;
		static const Enum PAGE_UP;
		static const Enum PAUSE;
		static const Enum PLAY;
		static const Enum PRINT;
		static const Enum PRINT_SCREEN;
		static const Enum PROCESS_KEY;
		static const Enum Q;
		static const Enum R;
		static const Enum RIGHT;
		static const Enum RIGHT_ALT;
		static const Enum RIGHT_CONTROL;
		static const Enum RIGHT_SHIFT;
		static const Enum RIGHT_WINDOWS;
		static const Enum S;
		static const Enum SCROLL;
		static const Enum SELECT;
		static const Enum SELECT_MEDIA;
		static const Enum SEPARATOR;
		static const Enum SLEEP;
		static const Enum SPACE;
		static const Enum SUBTRACT;
		static const Enum T;
		static const Enum TAB;
		static const Enum U;
		static const Enum UP;
		static const Enum V;
		static const Enum VOLUME_DOWN;
		static const Enum VOLUME_MUTE;
		static const Enum VOLUME_UP;
		static const Enum W;
		static const Enum X;
		static const Enum Y;
		static const Enum Z;
		static const Enum ZOOM;
		static const Enum SYSREQ;
		static const Enum NUMBER_SIGN;
		static const Enum DOLLAR;
		static const Enum PERCENT;
		static const Enum AMPERSAND;
		static const Enum APOSTROPHE;
		static const Enum OPEN_PAREN;
		static const Enum CLOSE_PAREN;
		static const Enum ASTERISK;
		static const Enum SLASH;
		static const Enum COLON;
		static const Enum LESS;
		static const Enum EQUAL;
		static const Enum GREATER;
		static const Enum AT;
		static const Enum CIRCUMFLEX;
		static const Enum UNDERSCORE;
		static const Enum OPEN_QUOTE;
		static const Enum OPEN_BRACE;
		static const Enum CLOSE_BRACE;
		static const Enum BAR;
		static const Enum NBSP;
		static const Enum GRAVE;
		static const Enum POWER;
		static const Enum NUM_PAD_ENTER;
		static const Enum NUM_PAD_PERIOD;
		static const Enum NUM_PAD_EQUAL;
		static const Enum UNDO;
		static const Enum REDO;
		static const Enum CUT;
		static const Enum PASTE;
		static const Enum FIND;
		static const Enum CANCEL;
		static const Enum EJECT;
		static const int NB_KEYS;
	};
}
 #endif
