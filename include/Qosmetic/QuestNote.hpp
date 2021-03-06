#pragma once
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp" 
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "bs-utils/shared/utils.hpp"

#include "GlobalNamespace/SimpleColorSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"

#include "Data/NoteData.hpp"
#include "Data/Descriptor.hpp"
#include "Config/NoteConfig.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"

#include <vector>
#include <map>

#include "Utils/FileUtils.hpp"
#include "Utils/NoteUtils.hpp"

#include "static-defines.hpp"

#include "Logging/NoteLogger.hpp"

namespace Qosmetics
{
    class QuestNote
    {
        public:
            static inline ModInfo modInfo = {string_format("%s Notes", ID), VERSION};
            static Logger& getLogger() 
            {
                return NoteLogger::GetLogger();
            };

            static inline std::vector<std::string> fileNames = {};

            /// @brief called at shader warmup scene
            /// @return false if 0 files found, thus making this part of the mod disabled in main
            static bool ShaderWarmup();

            /// @brief called at GameCore scene
            static void GameCore();

            /// @brief called at Health Warning scene
            static void HealthWarning();

            /// @brief called at menu scene
            static void MenuViewControllers();

            /// @brief disables score submission for scoresaber if ghost notes or disappearing arrows is selected as a modifier since these are not compatible with custom notes
            /// @param modifiers the modifier class used in this level
            static void ModifierScoreDisableCheck(GlobalNamespace::GameplayModifiers* modifiers);

            /// @brief sets the debris disable bool based on what reduce debris is
            /// @param playerSpecificSettings the currently active player settings
            static void ReducedDebrisDisableCheck(GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings)
            {
                // is reduce debris on or off?
                bool reduceDebris = playerSpecificSettings->get_reduceDebris();
                if (reduceDebris)
                {
                    getLogger().info("reduce debris was active! not spawning any custom debris");
                }
                else
                {
                    getLogger().info("reduce debris was not active, we can spawn custom debris now :)");
                }
                // if reduce debris is on, debris should be disabled
                disableDebris = reduceDebris;
            }

            /// @brief runs after the note controller init function
            static void NoteController_Init_Post(GlobalNamespace::NoteController* noteController);;

            /// @brief runs after the debris init function
            static void NoteDebris_Init_Post(GlobalNamespace::NoteDebris* noteDebris, GlobalNamespace::BeatmapSaveData::NoteType noteType, UnityEngine::Transform* initTransform, UnityEngine::Vector3 cutPoint, UnityEngine::Vector3 cutNormal);

            /// @brief runs after the bomb controller function
            static void BombController_Init_Post(GlobalNamespace::BombNoteController* noteController);

            static void ClearAllInternalPointers()
            {
                for (auto &pair : noteMap)
                {
                    pair.second->ClearActive();
                }
            }

            /// @brief handles the colors did change event for notes
            static void HandleColorsDidChangeEvent();

            /// @brief Sets the activeNote pointer to point to the note that should be active, or handles setting to nulltr (default)
            static void SetActiveNote(Descriptor* noteDescriptor, bool ifLoadAlsoAssets = false)
            {
                previousActiveNote = activeNote;
                if (noteDescriptor->get_type() == qosmeticsType::invalid)
                {
                    activeNote = nullptr;
                    OnActiveNoteSet(false);
                    return;
                }
                
                activeNote = noteMap[noteDescriptor];
                OnActiveNoteSet(ifLoadAlsoAssets);
            }
            
            /// @brief Sets the activeNote pointer to point to the note that should be active, or handles setting to nulltr (default)
            static void SetActiveNote(NoteData* note, bool ifLoadAlsoAssets = false)
            {
                previousActiveNote = activeNote;
                activeNote = note;
                OnActiveNoteSet(ifLoadAlsoAssets);
            }
            /// @brief gets called when the active note is set
            static void OnActiveNoteSet(bool ifLoadAlsoAssets);
            
            /// @brief gives the currently active note if needed
            static NoteData* GetActiveNote()
            {
                return activeNote;
            }

            static std::map<Descriptor*, NoteData*>& get_noteMap()
            {
                return noteMap;
            }

            /// @return true for different, false for same
            static bool DidSelectDifferentNote()
            {
                return activeNote != previousActiveNote;
            }

            static void SelectionDefinitive()
            {
                previousActiveNote = activeNote;
            }

        private:
            static inline std::map<Descriptor*, NoteData*> noteMap = {};
            static inline NoteData* activeNote = nullptr;
            static inline NoteData* previousActiveNote = nullptr;
            static inline bool setColors = false;
            static inline bool disableDebris = false;

            /// @brief makes the folder if not found
            static void makeFolder();
    };
}