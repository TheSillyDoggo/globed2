#include "settings.hpp"

#include <asp/misc/traits.hpp>

using namespace geode::prelude;

GlobedSettings::GlobedSettings() {
    this->reload();
}

void GlobedSettings::reflect(TaskType taskType) {
    using SetMd = boost::describe::describe_members<GlobedSettings, boost::describe::mod_public>;

    // iterate through all categories
    boost::mp11::mp_for_each<SetMd>([&, this](auto cd) -> void {
        using CatType = typename asp::member_ptr_to_underlying<decltype(cd.pointer)>::type;
        auto catName = cd.name;

        auto& category = this->*cd.pointer;
        bool isFlag = std::string_view(catName) == "flags";

        // iterate through all settings in the category
        using CatMd = boost::describe::describe_members<CatType, boost::describe::mod_public>;
        boost::mp11::mp_for_each<CatMd>([&, this](auto setd) -> void {
            using SetTy = typename asp::member_ptr_to_underlying<decltype(setd.pointer)>::type;
            using InnerType = SetTy::Type;
            constexpr InnerType Default = SetTy::Default;

            auto setName = setd.name;

            std::string settingKey;
            if (isFlag) {
                settingKey = fmt::format("_gflag-{}", setName);
            } else {
                settingKey = fmt::format("_gsetting-{}{}", catName, setName);
            }

            auto& setting = category.*setd.pointer;

            // now, depending on whether we are saving settings or loading them, do the appropriate thing
            switch (taskType) {
                case TaskType::SaveSettings: {
                    if (this->has(settingKey) || setting.get() != Default || isFlag) {
                        this->store(settingKey, setting.get());
                    }
                } break;
                case TaskType::LoadSettings: {
                    this->loadOptionalInto(settingKey, setting.ref());
                } break;
                case TaskType::ResetSettings: {
                    // flags cant be cleared unless hard resetting
                    if (isFlag) break;
                } [[fallthrough]];
                case TaskType::HardResetSettings: {
                    setting.set(Default);
                    this->clear(settingKey);
                } break;
            }
        });
    });
}

void GlobedSettings::hardReset() {
    this->reflect(TaskType::HardResetSettings);
}

void GlobedSettings::reset() {
    this->reflect(TaskType::ResetSettings);
}

void GlobedSettings::reload() {
    this->reflect(TaskType::LoadSettings);
}

void GlobedSettings::save() {
    this->reflect(TaskType::SaveSettings);
}

bool GlobedSettings::has(std::string_view key) {
    return Mod::get()->hasSavedValue(key);
}

void GlobedSettings::clear(std::string_view key) {
    auto& container = Mod::get()->getSaveContainer();
    auto& obj = container.as_object();

    if (obj.contains(key)) {
        obj.erase(key);
    }
}

// verify that all members are serialized
#include <data/bytebuffer.hpp>
static void verifySettings() {
    globed::unreachable();

    GlobedSettings* ptr = nullptr;
    ByteBuffer bb;
    bb.writeValue(*ptr);
}
