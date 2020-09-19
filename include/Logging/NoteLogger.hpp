#pragma once
#include "beatsaber-hook/shared/utils/logging.hpp"

namespace Qosmetics
{
    class NoteLogger
    {
        public:
            static inline ModInfo modInfo = ModInfo();
            static const Logger& GetLogger()
            {
                static const Logger& log(modInfo);
                return log;
            }
    };
}