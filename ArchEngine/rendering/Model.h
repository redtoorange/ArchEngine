#pragma once
#include <vector>
#include "Mesh.h"

namespace arch {
	class Model {
	public:
		void AddMesh(Mesh mesh);

		void Render();

	private:
		std::vector<Mesh> modelMeshes;
	};
}
