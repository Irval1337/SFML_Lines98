#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <string>
#include <Windows.h>
#include "INIReader.h"
#include <fstream>
#include <direct.h>
#include <vector>
#include <algorithm>

class Top_scores_info {
public:
    std::vector<std::pair<int, int>> scores;
    int total_attemps, successful_attemps;
    size_t settings_hash;

    bool isExists() {
        std::string path = get_appdata() + "\\Irval.dev";
        if (!dir_exists(path)) return false;
        if (!dir_exists(path + "\\Scores\\" + std::to_string(settings_hash))) return false;
        if (!file_exists(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.dat")) return false;
        if (!file_exists(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.ini")) return false;

        INIReader reader(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.ini");
        if (reader.ParseError() < 0)
            return false;

        return true;
    }

    void setHash(size_t hash) {
        settings_hash = hash;
    }

    void loadConfig() {
        if (!isExists()) return;
        std::string path = get_appdata() + "\\Irval.dev";
        INIReader reader(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.ini");
        total_attemps = reader.GetInteger("statistics", "total_attemps", 0);
        successful_attemps = reader.GetInteger("statistics", "successful_attemps", 0);

        std::string s;
        std::ifstream file(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.dat");

        scores.clear();
        while (getline(file, s)) {
            int score = atoi(s.substr(0, s.find(" ")).c_str()), time = atoi(s.substr(s.find(" ") + 1).c_str());
            scores.push_back(std::make_pair(score, time));
        }

        file.close(); 
    }

    void saveConfig() {
        std::string path = get_appdata() + "\\Irval.dev";

        if (!dir_exists(path)) CreateDirectory(path.c_str(), NULL);
        if (!dir_exists(path + "\\Scores")) CreateDirectory((path + "\\Scores").c_str(), NULL);
        if (!dir_exists(path + "\\Scores\\" + std::to_string(settings_hash))) CreateDirectory((path + +"\\Scores\\" + std::to_string(settings_hash)).c_str(), NULL);

        std::ofstream out;
        out.open(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.ini");
        if (out.is_open())
        {
            out << "[statistics]" << "\n";
            out << "total_attemps=" << total_attemps << "\n";
            out << "successful_attemps=" << successful_attemps << "\n";
        }
        out.close();

        std::sort(scores.begin(), scores.end());
        std::reverse(scores.begin(), scores.end());

        out.open(path + "\\Scores\\" + std::to_string(settings_hash) + "\\top_score.dat");
        if (out.is_open())
        {
            for (auto score : scores) {
                out << score.first << " " << score.second << "\n";
            }
        }
        out.close();
    }

    void set_default() {
        total_attemps = 0, successful_attemps = 0;
        scores.clear();
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