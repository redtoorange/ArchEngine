#include "ShaderProgram.h"

namespace {
    const std::string TERRAIN_VERT = "";
    const std::string TERRAIN_FRAG = "";
}


namespace arch {
    TerrainShaderProgram::TerrainShaderProgram(): ShaderProgram(TERRAIN_VERT, TERRAIN_FRAG){
    }
    
    void TerrainShaderProgram::SetGlobalIllumination(bool enable){
    }

    void TerrainShaderProgram::SetTerrainAlbedoColor(const glm::vec4& color){
    }
}
