#pragma once
#include <glm/glm.hpp>

namespace arch {
	class RenderSystem {
	public:
		static RenderSystem* singleton;

		RenderSystem();
		
		virtual ~RenderSystem();

		void ClearScreen();

	private:
		glm::vec4 m_clearColor{0.4f, 0.4f, 0.4f, 1};
	};
}
