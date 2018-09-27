#include "Model.h"

namespace arch {

	void Model::AddMesh(Mesh mesh) {
		
	}

	void Model::Render() {
		for(auto& mesh : modelMeshes) {
			mesh.Render();
		}
	}
}
