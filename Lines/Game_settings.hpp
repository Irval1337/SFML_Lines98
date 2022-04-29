#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <string>
#include <Windows.h>
#include "INIReader.h"
#include <fstream>
#include <direct.h>
#include <unordered_map>

class Game_settings_info {
public:
    int field_size, color_count, new_balls_count;
    bool multicolor, zone_bomb, v_h_bomb;
    int prop_multi, prop_zone, prop_v_h;

    size_t getHash() {
        std::size_t hash = std::hash<std::string>{}(std::to_string(field_size) + "_" + std::to_string(color_count) + "_" + std::to_string(new_balls_count) 
            + "_" + std::to_string((int)multicolor) + "_" + std::to_string((int)zone_bomb) + "_" + std::to_string((int)v_h_bomb) 
            + "_" + std::to_string(prop_multi) + "_" + std::to_string(prop_zone) + "_" + std::to_string(prop_v_h));
        return hash;
    }

    bool isExists() {
        std::string path = get_appdata() + "\\Irval.dev";
        if (!dir_exists(path)) return false;
        if (!file_exists(path + "\\game_settings.ini")) return false;

        INIReader reader(path + "\\game_settings.ini");
        if (reader.ParseError() < 0)
            return false;

        return true;
    }

    void loadConfig() {
        if (!isExists()) return;
        std::string path = get_appdata() + "\\Irval.dev";
        INIReader reader(path + "\\game_settings.ini");
        field_size = reader.GetInteger("global", "field_size", 9);
        color_count = reader.GetInteger("global", "color_count", 7);
        new_balls_count = reader.GetInteger("global", "new_balls_count", 3);

        multicolor = reader.GetBoolean("special_balls", "multicolor", false);
        zone_bomb = reader.GetBoolean("special_balls", "zone_bomb", false);
        v_h_bomb = reader.GetBoolean("special_balls", "v_h_bomb", false);

        prop_multi = reader.GetInteger("probabilities", "multicolor", 0);
        prop_zone = reader.GetInteger("probabilities", "zone_bomb", 0);
        prop_v_h = reader.GetInteger("probabilities", "v_h_bomb", 0);
    }

    void saveConfig() {
        std::string path = get_appdata() + "\\Irval.dev";

        if (!dir_exists(path)) CreateDirectory(path.c_str(), NULL);

        std::ofstream out;
        out.open(path + "\\game_settings.ini");
        if (out.is_open())
        {
            out << "[global]" << "\n";
            out << "field_size=" << field_size << "\n";
            out << "color_count=" << color_count << "\n";
            out << "new_balls_count=" << new_balls_count << "\n";

            out << "\n[special_balls]" << "\n";
            out << "multicolor=" << (multicolor ? "true" : "false") << "\n";
            out << "zone_bomb=" << (zone_bomb ? "true" : "false") << "\n";
            out << "v_h_bomb=" << (v_h_bomb ? "true" : "false") << "\n";

            out << "\n[probabilities]" << "\n";
            out << "multicolor=" << prop_multi << "\n";
            out << "zone_bomb=" << prop_zone << "\n";
            out << "v_h_bomb=" << prop_v_h << "\n";

        }
        out.close();
    }

    void set_default() {
        std::string dir = get_work_dir();

        field_size = 9;
        color_count = 7;
        new_balls_count = 3;

        multicolor = false;
        zone_bomb = false;
        v_h_bomb = false;

        prop_multi = 0;
        prop_zone = 0;
        prop_v_h = 0;
    }
private:
    std::string get_appdata() {
        return getenv("appdata");
    }

    bool dir_exists(const std::string& dirName_in)
    {
        DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
    }

    bool file_exists(const std::string& name) {
        if (FILE* file = fopen(name.c_str(), "r")) {
            fclose(file);
            return true;
        }
        else {
            return false;
        }
    }

    std::string get_work_dir() {
        char current_work_dir[FILENAME_MAX];
        _getcwd(current_work_dir, sizeof(current_work_dir));
        return current_work_dir;
    }
};