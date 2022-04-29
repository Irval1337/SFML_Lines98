#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <string>
#include <Windows.h>
#include "INIReader.h"
#include <fstream>
#include <direct.h>

class Graphic_settings_info {
public:
    int jump, explosion, spawn, move;
    int max_fps;
    bool vsync;
    std::string balls, bombs, background;

    bool isExists() {
        std::string path = get_appdata() + "\\Irval.dev";
        if (!dir_exists(path)) return false;
        if (!file_exists(path + "\\graphic_settings.ini")) return false;

        INIReader reader(path + "\\graphic_settings.ini");
        if (reader.ParseError() < 0)
            return false;

        return true;
    }

    void loadConfig() {
        if (!isExists()) return;
        std::string path = get_appdata() + "\\Irval.dev";
        INIReader reader(path + "\\graphic_settings.ini");
        jump = reader.GetInteger("delays", "jump", 15);
        explosion = reader.GetInteger("delays", "explosion", 30);
        spawn = reader.GetInteger("delays", "spawn", 30);
        move = reader.GetInteger("delays", "move", 2);

        max_fps = reader.GetInteger("perfomance", "max_fps", 60);
        vsync = reader.GetBoolean("perfomance", "vsync", true);

        balls = reader.GetString("textures", "balls", "NULL");
        bombs = reader.GetString("textures", "bombs", "NULL");
        background = reader.GetString("textures", "background", "NULL");
    }

    void saveConfig() {
        std::string path = get_appdata() + "\\Irval.dev";

        if (!dir_exists(path)) CreateDirectory(path.c_str(), NULL);

        std::ofstream out;
        out.open(path + "\\graphic_settings.ini");
        if (out.is_open())
        {
            out << "[delays]" << "\n";
            out << "jump=" << jump << "\n";
            out << "explosion=" << explosion << "\n";
            out << "spawn=" << spawn << "\n";
            out << "move=" << move << "\n";

            out << "\n[perfomance]" << "\n";
            out << "max_fps=" << max_fps << "\n";
            out << "vsync=" << (vsync ? "true" : "false") << "\n";

            out << "\n[textures]" << "\n";
            out << "balls=" << balls << "\n";
            out << "bombs=" << bombs << "\n";
            out << "background=" << background << "\n";
        }
        out.close();
    }

    void set_default() {
        std::string dir = get_work_dir();

        jump = 15;
        explosion = 30;
        spawn = 30;
        move = 2;

        max_fps = 60;
        vsync = true;

        balls = dir + "\\res\\balls\\Normal";
        bombs = dir + "\\res\\balls\\Bombs";
        background = dir + "\\res\\background.png";
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