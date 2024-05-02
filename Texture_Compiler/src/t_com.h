#pragma once
#include <string>
#include <vector>
#include <filesystem>  // Include the filesystem header
namespace fs = std::filesystem;
namespace Tex_compiler
{
    struct Texture {
        int width, height, nrComponents;
        unsigned char* data, *compresseddata;
        std::string type;
        std::string path;
        std::string gamma;
        int BC = 3;
    };

   

    struct descriptor
    {
        std::string path_to_texture, folder_name, path_to_desc;

        struct parser
        {
            std::string target, desc_path, rsc_path, help;
        };

        void load();
        void TraverseDirectory(const fs::path& directoryPath);
        parser p_object;
        std::vector<Texture> textures;
        std::vector<Texture> textures_loaded;
        void output(std::string filepath);

    };
}