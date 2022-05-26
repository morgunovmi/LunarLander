#pragma once 

#include <fstream>
#include <string_view>
#include <vector>

#include "renderer/RendererConstants.h"
#include "timer/Timer.h"

class Image {
public:
    Image() {}
    explicit Image(std::string_view ppmPath) : m_image() {
        loadFromPpm(ppmPath);
    }

    u16 width() const { return m_width; }
    u16 height() const { return m_height; }
    const std::vector<std::vector<Color>>& getImage() const { return m_image; }

private:
    void loadFromPpm(std::string_view ppmPath) {
        Timer t{};
        std::cout << "Loading image from ppm file " << ppmPath << '\n';
        if (auto ifs = std::ifstream{ ppmPath.data() }) {
            std::string temp{};
            std::getline(ifs, temp);
            std::cout << temp << '\n';
            std::getline(ifs, temp);
            std::cout << temp << '\n';

            ifs >> m_width >> m_height;
            u32 maxInt{};
            ifs >> maxInt;
            std::cout << maxInt << '\n';
            m_image.resize(m_height, std::vector<Color>(m_width));

            for (size_t y = 0; y < m_height; ++y) {
                for (size_t x = 0; x < m_width; ++x) {
                    if (ifs.eof()) {
                        std::cerr << "Corrupted ppm file << ppmPath" << '\n';
                        return;
                    }

                    Color c{0, 0, 0, 100};
                    u32 tempVal{};
                    ifs >> tempVal;
                    c.r = static_cast<double>(tempVal) / maxInt * 255; 
                    ifs >> tempVal;
                    c.g = static_cast<double>(tempVal) / maxInt * 255; 
                    ifs >> tempVal;
                    c.b = static_cast<double>(tempVal) / maxInt * 255; 
                    m_image[y][x] = c;
                }
            }
            std::cout << "Loaded image successfully" << ppmPath << '\n';
            std::cout << "Size is " << m_width << " x " << m_height << '\n';
            std::cout << "Image loading took " << t.stop() << '\n';
            return;
        }
        std::cerr << "Couldn't load file " << ppmPath << '\n';
    }

    std::vector<std::vector<Color>> m_image;
    u16 m_width;
    u16 m_height;
};
