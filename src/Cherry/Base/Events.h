/**
 * @file
 * Events for Cherry
 */
#pragma once
#include "Window.h"
namespace Cherry {
	namespace Base {
		class Events {
		public:
			struct Event {
				int id;
				 bool active;
			};
			
			struct WindowEvents {
				static Event CHERRY_WINDOW_RESIZE;
				
			};
			 
			 /*
			 * 
			 * @param events A Event that happens in the window
			 * @note notes that workdozyg
			 */
			static bool ReceiveCallBack(Event events);
			static void SendCallBack(Event& events); // Sends a Callback
		};
	}
}
