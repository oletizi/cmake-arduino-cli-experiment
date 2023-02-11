//
// Created by Orion Letizi on 2/5/23.
//

#ifndef CPP_EXPERIMENT_DISPLAY_H
#define CPP_EXPERIMENT_DISPLAY_H

#include <string>

namespace oletizi::display {
    class Display {
    public:
        virtual void print(std::string msg) = 0;
    };

    class SerialDisplay : public Display {
    public:
        void print(std::string msg) override;
    };
}
#endif //CPP_EXPERIMENT_DISPLAY_H