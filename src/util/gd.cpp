#include "gd.hpp"

#include <defs/geode.hpp>

using namespace geode::prelude;

namespace util::gd {
    void reorderDownloadedLevel(GJGameLevel* level) {
        // thank you cvolton :D
        // this is needed so the level appears at the top of the saved list (unless Manual Level Order is enabled)

        auto* levels = GameLevelManager::get()->m_onlineLevels;

        bool putAtLowest = GameManager::get()->getGameVariable("0084");

        int idx = 0;
        for (const auto& [k, level] : CCDictionaryExt<::gd::string, GJGameLevel*>(levels)) {
            if (putAtLowest) {
                idx = std::min(idx, level->m_levelIndex);
            } else {
                idx = std::max(idx, level->m_levelIndex);
            }
        }

        if (putAtLowest) {
            idx -= 1;
        } else {
            idx += 1;
        }

        level->m_levelIndex = idx;
    }

    void openProfile(int accountId, int userId, const std::string& name) {
        bool myself = accountId == GJAccountManager::get()->m_accountID;
        if (!myself) {
            GameLevelManager::sharedState()->storeUserName(userId, accountId, name);
        }

        ProfilePage::create(accountId, myself)->show();
    }

    int calcLevelDifficulty(GJGameLevel* level) {
        int diff = 0;
        // "would a backwards wormhole be a whitehole or a holeworm?" - kiba 2024
        if (level->m_autoLevel) {
            diff = -1;
        } else if (level->m_ratingsSum != 0) {
            if (level->m_demon == 1){
                int fixedNum = level->m_demonDifficulty;

                if (fixedNum != 0) {
                    fixedNum -= 2;
                }

                diff = 6 + fixedNum;
            } else {
                diff = level->m_ratingsSum / level->m_ratings;
            }
        } else {
            diff = 0;
        }

        return diff;
    }
}
