#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <gli/gl.hpp>
#include <gli/load.hpp> // load DDS, KTX or KMG textures from files or memory.
#include <gli/convert.hpp>
#include <gli/save.hpp> // save either a DDS, KTX or KMG file
#include <glm/glm.hpp>



#include "t_com.h"
namespace Tex_compiler 
{
    void descriptor::TraverseDirectory(const fs::path& directoryPath) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            const fs::path& entryPath = entry.path();

            if (fs::is_directory(entryPath)) {
                // Recursively traverse subdirectories
                TraverseDirectory(entryPath);
            }
            else if (fs::is_regular_file(entryPath)) {
                output(entryPath.string());
            }
        }
    }

    void descriptor::load()
    {
        auto texturePath = fs::current_path();
        TraverseDirectory(texturePath);
        //// Read the JSON file
        //std::ifstream file(this->p_object.desc_path);
        //if (!file.is_open()) {
        //    std::cerr << "Error: Failed to open file " << this->p_object.desc_path << std::endl;
        //    return;
        //}
        //json j;
        //file >> j;
        //// Process each object in the JSON array
        //for (const auto& config : j) {

        //    // Clear the existing texture_path vector for each object
        //    this->textures.clear();
        //    if (!config["textures"].is_null()) {
        //        for (const auto& texture : config["textures"]) {
        //            std::cout << "ENTER" << "\n";

        //            Texture tex;
        //            tex.path = texture["file_path"];
        //            tex.gamma = texture["format"];;
        //            tex.BC = texture["BC"];
        //            tex.type = texture["name"];
        //            textures.push_back(tex);
        //        }
        //    }
        //    this->folder_name = config["folder_name"];
        //    // Display the extracted values for each object
        //    std::cout << "Folder Name: " << this->folder_name << std::endl;



        //}
    }

    void descriptor::output(std::string filepath)
    {

        size_t lastSlashPos = filepath.find_last_of('\\');
        size_t secondLastSlashPos = filepath.find_last_of('\\', lastSlashPos - 1);
        size_t lastdotPos = filepath.find_last_of('.');
        std::string type = filepath.substr(lastSlashPos + 1, lastdotPos - lastSlashPos - 1);
        std::string output = filepath.substr(secondLastSlashPos + 1, lastSlashPos - secondLastSlashPos - 1);
        std::string input = filepath.substr(lastSlashPos + 1);
        std::string filetype = filepath.substr(lastdotPos + 1);
        if (filetype == "dds")
            return;
        //std::cout << filepath << "\n";
        //std::cout << type << "\n";
        //std::cout << output << "\n";
        //std::cout << input << "\n";

        //std::string outputPath = "output";  // Change this to your desired folder name

        //if (!fs::exists(outputPath)) {
        //    if (!fs::create_directory(outputPath)) {
        //        std::cerr << "Failed to create the folder." << std::endl;
        //        return;
        //    }
        //}


        //// Define the folder path where you want to store files
        //std::string folderPath = outputPath + "/" + folder_name;  // Change this to your desired folder name

        //// Create the folder if it doesn't exist
        //if (!fs::exists(folderPath)) {
        //    if (!fs::create_directory(folderPath)) {
        //        std::cerr << "Failed to create the folder." << std::endl;
        //        return;
        //    }
        //}

        std::hash<std::string> hashFunc;
        size_t hashValue = hashFunc(type);

        // Convert the hashValue to a uint32_t without data loss ensuring within range of uint32_t
        uint32_t GUID = static_cast<uint32_t>(hashValue % std::numeric_limits<uint32_t>::max());


        // -o output space input

        if (type == "normal")
            system(("texconv -f BC5_UNORM -y -px " + std::to_string(GUID) + "_" + " -o " + output + " " + (output + "/" + input)).c_str());
        else
            system(("texconv -srgb -f BC3_UNORM_SRGB -y -px " + std::to_string(GUID) + "_" + " -o " + output + " " + (output + "/" + input)).c_str());




        //for (auto& x : textures)
        //{
        //    switch (x.BC)
        //    {
        //    case 3:
        //        if (x.gamma == "SRGB")
        //            system(("texconv -srgb -f BC3_UNORM_SRGB -y -o " + type).c_str());
        //        else
        //            system(("texconv -f BC3_UNORM -y -o " + type).c_str());
        //        break;
        //    case 5:
        //            system(("texconv -f BC5_UNORM -y -o " + type).c_str());
        //        break;
        //    default:
        //        break;
        //    }
        //}

        //std::ofstream outFile(fs::path(folderPath) / fs::path(p_object.rsc_path), std::ios::binary);

        //if (!outFile.is_open()) {
        //    std::cerr << "Failed to open main file for writing." << std::endl;
        //    return;
        //}

        //size_t texturecount = textures.size();

        //// Write the texture count
        //outFile.write(reinterpret_cast<char*>(&texturecount), sizeof(texturecount));

        //for (auto& texture : textures)
        //{
        //    // Write the length of the type and path strings
        //    size_t typeLength = texture.type.length();
        //    outFile.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));

        //    // Write the type and path strings
        //    outFile.write(texture.type.c_str(), typeLength);
        //}

        //// clear texture data only now so that can write
        //for (auto& texture : textures)
        //{
        //    // Texture
        //    std::ofstream outFileT(fs::path(folderPath) / fs::path(texture.type + ".tex"), std::ios::binary);
        //    if (!outFileT.is_open()) {
        //        std::cerr << "Failed to open the file for writing." << std::endl;
        //        return;
        //    }

        //    // Create DDS image
        //    unsigned char cmpBuffer[16] = { 0 };
        //    // Compress the source into cmpBuffer
        //    gli::texture2d tex2d(gli::FORMAT_RGBA_DXT5_SRGB_BLOCK16, gli::extent2d(texture.width, texture.height));
        //    std::memcpy(tex2d.data(), cmpBuffer, sizeof(cmpBuffer));
        //    gli::save(tex2d, (fs::path(folderPath) / fs::path(texture.type + ".dds")).string());


        //    // Write the members of the Texture struct
        //    outFileT.write(reinterpret_cast<const char*>(&texture.width), sizeof(texture.width));
        //    outFileT.write(reinterpret_cast<const char*>(&texture.height), sizeof(texture.height));
        //    outFileT.write(reinterpret_cast<const char*>(&texture.nrComponents), sizeof(texture.nrComponents));

        //    // Write the length of the type and path strings
        //    size_t typeLength = texture.type.length();
        //    outFileT.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));

        //    // Write the type and path strings
        //    outFileT.write(texture.type.c_str(), typeLength);

        //    // Write the texture data
        //    size_t dataSize = texture.width * texture.height * texture.nrComponents;
        //    outFileT.write(reinterpret_cast<const char*>(texture.data), dataSize);
        //    stbi_image_free(texture.data);

        //    std::cout << "Texture Data written to: " << (fs::path(folderPath) / fs::path(texture.type + ".tex")).string() << std::endl;

        //    outFileT.close();
        //}

        //outFile.close();
        std::cout << "Texture Data written to: " << output << std::endl;
    }
}