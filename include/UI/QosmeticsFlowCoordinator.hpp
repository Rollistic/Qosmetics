#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/NavigationController.hpp"
#include "HMUI/FlowCoordinator.hpp"

#include "UI/QosmeticsViewController.hpp"
#include "UI/SaberSwitcherViewController.hpp"
#include "UI/NoteSwitcherViewController.hpp"
#include "UI/WallSwitcherViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics, QosmeticsFlowCoordinator, HMUI::FlowCoordinator,
    
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, ActiveViewController);
    DECLARE_INSTANCE_FIELD(Qosmetics::QosmeticsViewController*, QosmeticsViewController);
    DECLARE_INSTANCE_FIELD_DEFAULT(Qosmetics::SaberSwitcherViewController*, SaberSwitcherViewController, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(Qosmetics::NoteSwitcherViewController*, NoteSwitcherViewController, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(Qosmetics::WallSwitcherViewController*, WallSwitcherViewController, nullptr);
    

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(QosmeticsFlowCoordinator,
        REGISTER_FIELD(ActiveViewController);
        REGISTER_FIELD(QosmeticsViewController);
        REGISTER_FIELD(SaberSwitcherViewController);
        REGISTER_FIELD(NoteSwitcherViewController);
        REGISTER_FIELD(WallSwitcherViewController);

        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)