#pragma once

#include "event.hpp"

namespace zz {
	inline LRESULT CALLBACK WindowProcedure(HWND handle, uint32_t message, uint64_t  wparam, int64_t lparam) noexcept ;

	class Application {
		friend inline LRESULT CALLBACK WindowProcedure(HWND handle, uint32_t message, uint64_t  wparam, int64_t lparam) noexcept ;
		
	protected :
		static inline bool g_is_running_ = false ;
		static inline std::unordered_map<HWND, Window*> g_windows_ {} ;
		static inline HINSTANCE g_hinstance_ = GetModuleHandleW(nullptr) ;
		static inline std::string g_class_name_ = "zketch_app" ;
		static inline bool g_class_name_was_registered_ = false ;

		static void RegisterWindow(HWND handle, Window* window) {
			if (handle && window) {
				g_windows_[handle] = window ;
			} else {
				throw handle ? Ex::application("HWND is Null!") : Ex::application("Window is Null!") ;
			}
		}

		static void UnregisterWindow(HWND handle) noexcept {
			if (handle) {
				auto it = g_windows_.find(handle) ;
				if (it != g_windows_.end()) {
					g_windows_.erase(it) ;

					#ifdef APPLICATION_DEBUG
						logger::info("Application::UnRegisterWindow - Erased window from g_windows_, current size: ", g_windows_.size()) ;
					#endif

				}
			}
		}

	public :
		static void QuitProgram() noexcept {
			std::vector<HWND> destroy_sequence ;
			destroy_sequence.reserve(g_windows_.size()) ;
			for (auto& w : g_windows_) {
				destroy_sequence.push_back(w.first) ;
			}

			for (auto& w : destroy_sequence) {
				if (IsWindow(w)) {
					DestroyWindow(w) ;
				}
			}

			g_windows_.clear() ;
			g_is_running_ = false ;
			PostQuitMessage(0) ;

			#ifdef APPLICATION_DEBUG
				logger::info("Application::QuitProgram - PostQuitMessage done.") ;
			#endif
		}

		static void SetWindowClass(const std::string_view& class_name) noexcept {
			if (g_class_name_was_registered_) {

				#ifdef APPREGISTRY_DEBUG
					logger::warning("AppRegistry::SetWindowClass - Failed to register window class name, window class name was registered.") ;
				#endif

				return ;
			} 
			g_class_name_ = class_name ;
		}

		static void RegisterWindowClass() {
			if (g_class_name_was_registered_) {

				#ifdef APPREGISTRY_DEBUG
					logger::warning("AppRegistry::RegisterWindowClass - Failed to register window class name, window class name was registered.") ;
				#endif

				return ;
			}

			WNDCLASSEX wc = {
				sizeof(wc),
				CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
				WindowProcedure,
				0,
				0,
				g_hinstance_,
				LoadIcon(nullptr, IDI_APPLICATION),
				LoadCursor(nullptr, IDC_ARROW),
				nullptr,
				nullptr,
				g_class_name_.c_str(),
				LoadIcon(nullptr, IDI_APPLICATION)
			} ;

			if (!RegisterClassEx(&wc)) {

				#ifdef APPREGISTRY_DEBUG
					logger::error("AppRegistry::RegisterWindowClass - Failed to register window class!") ;
				#endif

				return ;
			}

			#ifdef APPREGISTRY_DEBUG
				logger::info("AppRegistry::RegisterWindowClass - Successfully register window class.") ;
			#endif

			g_class_name_was_registered_ = true ;
		}

		static bool IsRunning() noexcept {
			return g_is_running_ ;
		}
	} ;
}