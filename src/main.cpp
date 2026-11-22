#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <deque>

using namespace geode::prelude;

struct QueuedInput {
    int dueStep;
    bool down;
    int button;
    bool isPlayer1;
};

static std::deque<QueuedInput> g_queue;
static int g_step = 0;
static bool g_flushing = false;

static int getDelay() {
    auto mod = Mod::get();
    if (!mod->getSettingValue<bool>("enabled")) return 0;
    return numFromString<int>(mod->getSettingValue<std::string>("frames")).unwrapOr(0);
}

class $modify(AlignLayer, GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        int delay = getDelay();
        if (g_flushing || delay == 0) {
            GJBaseGameLayer::handleButton(down, button, isPlayer1);
            return;
        }
        // hold the input until `delay` physics steps from now
        g_queue.push_back({ g_step + delay, down, button, isPlayer1 });
    }

    void processCommands(float dt) {
        g_step++;
        g_flushing = true;
        while (!g_queue.empty() && g_queue.front().dueStep <= g_step) {
            auto q = g_queue.front();
            g_queue.pop_front();
            GJBaseGameLayer::handleButton(q.down, q.button, q.isPlayer1);
        }
        g_flushing = false;
        GJBaseGameLayer::processCommands(dt);
    }
};

class $modify(AlignPlayLayer, PlayLayer) {
    void resetLevel() {
        g_queue.clear();
        g_step = 0;
        PlayLayer::resetLevel();
    }
};
