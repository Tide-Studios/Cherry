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
			 static struct WindowEvents {
				int CHERRY_WINDOW_RESIZE;
			};
			 /*
			 * 
			 * @param events A Event that happens in the window
			 * 
			 */
			void ReceiveCallBack(WindowEvents events);
		private:
			void SendCallBack(); // Sends a Callback
		};
	}
}
