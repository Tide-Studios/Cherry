
#pragma once
#include "Events.h"
namespace Cherry {
	namespace Base {
		Events::Event Events::WindowEvents::CHERRY_WINDOW_RESIZE{
			0,
			false
		};
		bool Events::ReceiveCallBack(Event events) {
			if (events.active) {
				return true;
			}
			else {
				return false;
			}
		}
		void Events::SendCallBack(Event& events) {
			events.active = true;
		}
	}
}