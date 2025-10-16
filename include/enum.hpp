#pragma once

#include "debug.hpp"

namespace zz {

	// Enum WindowStyle dengan nama yang lebih mudah dipahami
	enum class WindowStyle : uint32_t {
		Basic             = WS_OVERLAPPED,           // jendela standar tanpa tambahan
		Popup             = WS_POPUP,                // jendela pop-up (tanpa border normal)
		Child             = WS_CHILD,                // jendela anak (tertanam di parent)
		Minimized         = WS_MINIMIZE,             // jendela dalam keadaan minimize
		Visible           = WS_VISIBLE,              // jendela terlihat
		Disabled          = WS_DISABLED,             // jendela nonaktif
		ClipSiblings      = WS_CLIPSIBLINGS,         // hindari gambar tumpang tindih antar child
		ClipChildren      = WS_CLIPCHILDREN,         // cegah parent menggambar di area child
		Maximized         = WS_MAXIMIZE,             // jendela dalam keadaan maximize
		TitleBar          = WS_CAPTION,              // judul + border atas
		Border            = WS_BORDER,               // border tipis
		DialogFrame       = WS_DLGFRAME,             // frame dialog
		VerticalScroll    = WS_VSCROLL,              // scrollbar vertikal
		HorizontalScroll  = WS_HSCROLL,              // scrollbar horizontal
		SystemMenu        = WS_SYSMENU,              // tombol sistem (close, minimize, dsb)
		ResizableFrame    = WS_THICKFRAME,           // border bisa di-resize (sizebox)
		MinimizeButton    = WS_MINIMIZEBOX,          // tombol minimize
		MaximizeButton    = WS_MAXIMIZEBOX,          // tombol maximize
		TabStop           = WS_TABSTOP,              // bisa diakses dengan Tab
		Group             = WS_GROUP,                // grup kontrol
		TiledLegacy       = WS_TILED,                // alias lama untuk OVERLAPPED
		OverlappedWindow  = WS_OVERLAPPEDWINDOW,     // jendela normal lengkap (title, border, dsb)
		PopupWindow       = WS_POPUPWINDOW,          // jendela pop-up dengan border & menu sistem
		ChildWindow       = WS_CHILDWINDOW,          // jendela anak (kombinasi child style)
		FixedWindow       = Basic | TitleBar | SystemMenu | MinimizeButton // non-resizable
	} ;

	enum class WindowShowMode : uint8_t {
		Hidden           = 0,  // SW_HIDE
		Normal           = 1,  // SW_SHOWNORMAL / SW_NORMAL
		Minimized        = 2,  // SW_SHOWMINIMIZED
		Maximized        = 3,  // SW_SHOWMAXIMIZED / SW_MAXIMIZE
		NoActivate       = 4,  // SW_SHOWNOACTIVATE
		Show             = 5,  // SW_SHOW
		Minimize         = 6,  // SW_MINIMIZE
		MinNoActivate    = 7,  // SW_SHOWMINNOACTIVE
		ShowNoActivate   = 8,  // SW_SHOWNA
		Restore          = 9,  // SW_RESTORE
		Default          = 10, // SW_SHOWDEFAULT
		ForceMinimize    = 11, // SW_FORCEMINIMIZE
		Max              = 11  // SW_MAX
	};

	enum class WindowState : uint8_t {
		None			= 0,
		Registered		= 1 << 0,
		Closed			= 1 << 1,
		Destroyed		= 1 << 2,
		Active			= 1 << 3,
	} ;

	enum class EventType : uint8_t {
		None,
		Window,
		Mouse,
		Key,
		Widget,
	} ;

	enum class WindowEvent : uint8_t {
		None,
		Close,
		Minimize,
		Maximize,
		Resize
	} ;

	enum class MouseEvent : uint8_t {
		None,
		Move,
		Up,
		Down,
		Middle,
		DoubleClick,
		Hover,
		Wheel
	} ;

	enum class MouseButton : uint8_t {
		None,
		Left,
		Right,
		Middle,
		Undefined
	} ;

	enum class KeyEvent : uint8_t {
		None,
		Up,
		Down
	} ;

	enum class KeyCode : uint16_t {
		// CONTROL & NAVIGATION
		None		= 0,
		Back		= 8,
		Tab			= 9,
		Enter		= 13,
		Shift		= 16,
		Control		= 17,
		Alt			= 18,    // Alt
		Pause		= 19,
		CapsLock	= 20,
		Escape		= 27,
		Space		= 32,
		PageUp		= 33,
		PageDown	= 34,
		End			= 35,
		Home		= 36,
		Left		= 37,
		Up			= 38,
		Right		= 39,
		Down		= 40,
		Insert		= 45,
		Delete		= 46,

		// NUMBER KEYS (TOP)
		Number0 = 48,
		Number1 = 49,
		Number2 = 50,
		Number3 = 51,
		Number4 = 52,
		Number5 = 53,
		Number6 = 54,
		Number7 = 55,
		Number8 = 56,
		Number9 = 57,

		// LETTER KEYS (A–Z)
		A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72,
		I = 73, J = 74, K = 75, L = 76, M = 77, N = 78, O = 79, P = 80,
		Q = 81, R = 82, S = 83, T = 84, U = 85, V = 86, W = 87, X = 88,
		Y = 89, Z = 90,

		// WINDOWS & MENU
		LeftWindows  = 91,
		RightWindows = 92,
		Application  = 93,

		// NUMPAD SECTION
		NumPad0 = 96,
		NumPad1 = 97,
		NumPad2 = 98,
		NumPad3 = 99,
		NumPad4 = 100,
		NumPad5 = 101,
		NumPad6 = 102,
		NumPad7 = 103,
		NumPad8 = 104,
		NumPad9 = 105,

		Multiply	= 106,
		Add			= 107,
		Separator	= 108, // Enter (numeric)
		Subtract	= 109,
		Decimal		= 110,
		Divide		= 111,
		NumLock		= 144,

		// FUNCTION KEYS
		F1 = 112, F2 = 113, F3 = 114, F4 = 115, F5 = 116, F6 = 117,
		F7 = 118, F8 = 119, F9 = 120, F10 = 121, F11 = 122, F12 = 123,
		F13 = 124, F14 = 125, F15 = 126, F16 = 127, F17 = 128, F18 = 129,
		F19 = 130, F20 = 131, F21 = 132, F22 = 133, F23 = 134, F24 = 135,

		// MODIFIER KEYS
		LeftShift		= 160,
		RightShift		= 161,
		LeftControl		= 162,
		RightControl	= 163,
		LeftAlt			= 164,
		RightAlt		= 165,

		// GAMEPAD / CONTROLLER
		GamepadA						= 195,
		GamepadB						= 196,
		GamepadX						= 197,
		GamepadY						= 198,
		GamepadRightShoulder			= 199,
		GamepadLeftShoulder				= 200,
		GamepadLeftTrigger				= 201,
		GamepadRightTrigger				= 202,
		GamepadDPadUp					= 203,
		GamepadDPadDown					= 204,
		GamepadDPadLeft					= 205,
		GamepadDPadRight				= 206,
		GamepadMenu						= 207,
		GamepadView						= 208,
		GamepadLeftThumbstickButton		= 209,
		GamepadRightThumbstickButton	= 210,
		GamepadLeftThumbstickUp			= 211,
		GamepadLeftThumbstickDown		= 212,
		GamepadLeftThumbstickRight		= 213,
		GamepadLeftThumbstickLeft		= 214,
		GamepadRightThumbstickUp		= 215,
		GamepadRightThumbstickDown		= 216,
		GamepadRightThumbstickRight		= 217,
		GamepadRightThumbstickLeft		= 218
	} ;
}